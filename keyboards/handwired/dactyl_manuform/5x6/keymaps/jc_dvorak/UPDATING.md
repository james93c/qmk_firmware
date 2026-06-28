# Updating QMK for the `jc_dvorak` Dactyl Manuform 5x6

Notes for keeping this keymap building against the latest QMK, plus the
specific traps this exact build hits. Written after a long debugging session —
read the **Landmines** section before assuming a problem is hardware.

## Context / how this is set up

- **Board:** handwired Dactyl Manuform 5x6, split, two **Pro Micro (atmega32u4)**
  controllers, `caterina` bootloader, single-wire **soft serial** over TRRS.
- **This keymap is fully self-contained** in
  `keyboards/handwired/dactyl_manuform/5x6/keymaps/jc_dvorak/`. It only *adds*
  files — it never edits shared upstream files. That is what makes updates easy.
- Handedness is set with `EE_HANDS` (stored in each half's EEPROM), not baked
  into the firmware.
- `origin` = personal fork (`james93c/qmk_firmware`), `upstream` = `qmk/qmk_firmware`.
  `master` tracks upstream with this one keymap commit rebased on top.

## Basic update process

```bash
# 1. Get latest upstream QMK
git fetch upstream

# 2. Replay the keymap commit on top of fresh upstream
git rebase upstream/master            # ~zero conflict risk: our files are isolated

# 3. Sync submodules to the new QMK (LUFA / ChibiOS / etc.)
git submodule update --init --recursive

# 4. Build to confirm it still compiles
qmk compile -kb handwired/dactyl_manuform/5x6 -km jc_dvorak

# 5. Publish to the fork (rebase rewrites history, so force is expected)
git push --force-with-lease origin master
```

## Flashing

Normal day-to-day flash (handedness already in EEPROM, untouched by a plain flash):

```bash
qmk flash -kb handwired/dactyl_manuform/5x6 -km jc_dvorak   # reset one half
qmk flash -kb handwired/dactyl_manuform/5x6 -km jc_dvorak   # reset the other half
```

Always flash **both** halves. Reset each controller when it prints
`Waiting for USB serial port`. The split is wired single-wire serial on **pin
`3` = D0** (Arduino "3"/"D3" silk = AVR `PD0` = QMK `D0`).

To (re)write handedness — needed after a big QMK jump if a half comes up
wrong-handed (see Landmines):

```bash
qmk flash -kb handwired/dactyl_manuform/5x6 -km jc_dvorak -bl avrdude-split-right  # right half
qmk flash -kb handwired/dactyl_manuform/5x6 -km jc_dvorak -bl avrdude-split-left   # left half
```

> ⚠️ **Always unplug USB before connecting/disconnecting the TRRS cable.**
> Hot-plugging can momentarily short VCC↔GND and kill a Pro Micro.

---

## Landmines

### 1. Toolchain too new for an old QMK checkout
`avr-gcc 16` (and newer) breaks pre-2025 QMK. Symptoms:
- `quantum/send_string/send_string.c: error: 'TCNT0' undeclared` (missing
  `<avr/io.h>` include that newer avr-libc no longer pulls in transitively).
- `error: variable 'ConfigSuccess' set but not used [-Werror=...]` and similar,
  because QMK builds with `-Werror` and the new compiler adds warnings.

**Do not patch core files or paper over it with `-e ALLOW_WARNINGS=yes`.**
The real fix is to **update QMK** (the basic process above). Current QMK builds
clean on this toolchain with no hacks.

### 2. Handedness EEPROM wiped by a QMK version jump
A large QMK update can change the EEPROM layout, so on first boot the firmware
resets EEPROM and **forgets which half is left/right**. If a half comes up with
the wrong columns after an update, re-run the `-bl avrdude-split-left` /
`-bl avrdude-split-right` flashes once per half (see Flashing).

### 3. Clone Pro Micros need `SPLIT_USB_DETECT` — THE big one
Symptom: each half works fine on its own over USB, but as a **slave** (the half
without USB) it is **totally silent** — symmetric, regardless of cable/pin/wiring.
All the wiring can test perfect (5 V at the slave, common ground, data
continuity, no shorts) and it still fails.

Cause: these clone Pro Micros have unreliable USB VBUS detection, so the
non-USB half can't tell it should be the slave; it acts as a would-be master and
never listens on the serial line. Fix (already in `config.h`):

```c
#define SPLIT_USB_DETECT
```

This costs a ~2 s boot delay on the slave before it comes alive — normal.
**If you ever rip this out, the split breaks again.**

### 4. `clang-format` on save eats commas in `LAYOUT` blocks
There is a format-on-save hook. When the `LAYOUT_5x6(...)` blocks were edited it
reflowed them to one line and dropped commas, producing:
`error: macro 'LAYOUT_5x6' requires 64 arguments, but only 61 given`.

The keymaps array is wrapped in `// clang-format off` / `// clang-format on` to
prevent this. **Keep those guards.** If you add a layer, keep it inside them and
double-check every key has a trailing comma.

### 5. Don't edit `keyboard.json` for per-keymap tweaks
`keyboard.json` is a shared upstream file. Editing it (e.g. changing the serial
pin) creates a diff that will conflict on `git rebase upstream/master`. Put
overrides in this keymap's `config.h` instead. (Note: a few data-driven defines
like `SOFT_SERIAL_PIN` are emitted unconditionally and can't be overridden from
`config.h` — if you genuinely must change one, that's the rare exception, and
expect to re-apply it after each rebase.)

### 6. Fork history divergence → force push
After rebasing onto upstream, local `master` will read "ahead N, behind tens of
thousands" vs `origin/master`. That's expected. Push with
`git push --force-with-lease origin master`.

### 7. Pin-name confusion (PD0 vs "D3" vs "3")
The serial data pin is silk-screened **`3`** and some pinouts label it **`D3`**
(Arduino numbering) — but it is **`PD0`**, which QMK calls **`D0`**. The config
value is `D0`. Do **not** move it to QMK `D3` (that's `PD3` / a different pin).
