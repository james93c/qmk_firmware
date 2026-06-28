#include QMK_KEYBOARD_H

// Define names for layers
#define DVORAK 0
#define FUNCTION 1
#define QWERTY 2

#define FNC FUNCTION
#define QTY QWERTY

// Shorthand custom key code defs
#define CC_PLUS LSFT(KC_EQL)
#define CC_PIPE LSFT(KC_BSLS)
#define CC_LBRA LSFT(KC_LBRC)
#define CC_RBRA LSFT(KC_RBRC)

#define FNC_SPC LT(FNC, KC_SPC)
#define GUI_ENT MT(MOD_LGUI, KC_ENT)
#define SFT_ENT MT(MOD_LSFT, KC_ENT)

// Custom keycodes for Programmer Dvorak-style number row
enum custom_keycodes {
    CK_1 = SAFE_RANGE,
    CK_2,
    CK_3,
    CK_4,
    CK_5,
    CK_6,
    CK_7,
    CK_8,
    CK_9,
    CK_0,
    // CK_HASH,
    // CK_PERC,
    // CK_DLLR
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DVORAK] = LAYOUT_5x6(
        KC_GRV, CK_1,   CK_2,   CK_3,   CK_4,   CK_5,           CK_6,   CK_7,   CK_8,   CK_9,   CK_0,   KC_F12,
        KC_TAB, KC_QUOT,KC_COMM,KC_DOT, KC_P,   KC_Y,           KC_F,   KC_G,   KC_C,   KC_R,   KC_L,   KC_SLSH,
        KC_ESC, KC_A,   KC_O,   KC_E,   KC_U,   KC_I,           KC_D,   KC_H,   KC_T,   KC_N,   KC_S,   KC_MINS,
        KC_LSFT,KC_SCLN,KC_Q,   KC_J,   KC_K,   KC_X,           KC_B,   KC_M,   KC_W,   KC_V,   KC_Z,   SFT_ENT,
                        KC_LEFT,KC_RGHT,                                        KC_UP,  KC_DOWN,
                                        KC_BSPC,FNC_SPC,        GUI_ENT,KC_RSFT,
                                           KC_DEL, KC_LCTL,  KC_TAB, KC_LALT,
                                           KC_PAUS,KC_HOME,  KC_END, KC_PSCR
    ),
    [FUNCTION] = LAYOUT_5x6(
        KC_F12, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,          KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,
        _______,KC_PGUP,KC_HOME,KC_UP,  KC_END, _______,        _______,S(KC_2),CC_PIPE,S(KC_7),S(KC_6),_______,
        _______,KC_PGDN,KC_LEFT,KC_DOWN,KC_RGHT,KC_ENT,         _______,S(KC_3),KC_BSLS,S(KC_5),S(KC_4),_______,
        _______,_______,_______,_______,_______,_______,        _______,_______,_______,_______,_______,_______,
                        KC_HOME,KC_END,                                         KC_PGUP,KC_PGDN,
                                        _______,_______,        _______,_______,
                                           _______,_______,  _______,_______,
                                           _______,_______,  TG(QTY), _______
    ),
    [QWERTY] = LAYOUT_5x6(
        KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,           KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_F12,
        KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,           KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_MINS,
        KC_ESC, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,           KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
        KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,           KC_N,   KC_M,   KC_T,   KC_G,   KC_B,   KC_LSFT,
                        KC_LEFT,KC_RGHT,                                        KC_UP,  KC_DOWN,
                                        KC_BSPC,KC_SPC,         KC_ENT, KC_DEL,
                                           _______,KC_LCTL,  KC_LGUI,KC_COMM,
                                           _______,_______,  TG(QTY),KC_DOT
    ),
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t mods          = get_mods() | get_oneshot_mods(); // Capture current mods
    bool    shift_pressed = mods & MOD_MASK_SHIFT;

    if (record->event.pressed) {
        switch (keycode) {
            case CK_1:
            case CK_2:
            case CK_3:
            case CK_4:
            case CK_5:
            case CK_6:
            case CK_7:
            case CK_8:
            case CK_9:
            case CK_0: {
                // case CK_HASH: case CK_PERC: case CK_DLLR: {
                if (shift_pressed) {
                    del_mods(MOD_MASK_SHIFT);         // Temporarily remove shift
                    set_mods(mods & ~MOD_MASK_SHIFT); // Update mods state
                }

                switch (keycode) {
                    case CK_1:
                        tap_code16(shift_pressed ? KC_1 : S(KC_1));
                        break;
                    case CK_2:
                        tap_code16(shift_pressed ? KC_2 : KC_LBRC);
                        break;
                    case CK_3:
                        tap_code16(shift_pressed ? KC_3 : S(KC_LBRC));
                        break;
                    case CK_4:
                        tap_code16(shift_pressed ? KC_4 : S(KC_9));
                        break;
                    case CK_5:
                        tap_code16(shift_pressed ? KC_5 : S(KC_EQL));
                        break;
                    case CK_6:
                        tap_code16(shift_pressed ? KC_6 : KC_EQL);
                        break;
                    case CK_7:
                        tap_code16(shift_pressed ? KC_7 : S(KC_0));
                        break;
                    case CK_8:
                        tap_code16(shift_pressed ? KC_8 : S(KC_RBRC));
                        break;
                    case CK_9:
                        tap_code16(shift_pressed ? KC_9 : KC_RBRC);
                        break;
                    case CK_0:
                        tap_code16(shift_pressed ? KC_0 : S(KC_8));
                        break;
                        // case CK_HASH:   tap_code16(shift_pressed ? S(KC_2) : S(KC_3));break;
                        // case CK_PERC:   tap_code16(shift_pressed ? S(KC_5) : S(KC_7));break;
                        // case CK_DLLR:   tap_code16(shift_pressed ? S(KC_4) : S(KC_6));break;
                }

                if (shift_pressed) {
                    set_mods(mods); // Restore shift and any other mods
                }

                return false; // Skip default processing
            }

            default:
                return true; // Let other keys through
        }
    }

    return true; // Process key release normally
}

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    // Empty unless you have encoders
};
#endif
