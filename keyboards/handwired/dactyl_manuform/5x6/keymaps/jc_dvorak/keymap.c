#include QMK_KEYBOARD_H

#define DVORAK 0
#define QWERTY 1
#define FUNCTION 2

#define DVK DVORAK
#define QTY QWERTY
#define FNC FUNCTION

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[DVORAK] = LAYOUT_5x6(
        KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                           KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_F12,
        KC_TAB, KC_QUOT,KC_COMM,KC_DOT, KC_P,   KC_Y,                           KC_F,   KC_G,   KC_C,   KC_R,   KC_L,   KC_SLSH,
        KC_ESC, KC_A,   KC_O,   KC_E,   KC_U,   KC_I,                           KC_D,   KC_H,   KC_T,   KC_N,   KC_S,   KC_MINS,
        KC_LSFT,KC_SCLN,KC_Q,   KC_J,   KC_K,   KC_X,                           KC_B,   KC_M,   KC_W,   KC_V,   KC_Z,   KC_LSFT,
                        KC_LEFT,KC_RGHT,                                                        KC_UP,  KC_DOWN,
                                        KC_BSPC,KC_SPC,                         KC_ENT, KC_DEL,
                                                KC_EQL, KC_LCTL,        KC_LGUI,KC_LBRC,
                                                KC_BSLS,MO(FNC),        KC_LALT,KC_RBRC
    ),
	[QWERTY] = LAYOUT_5x6(
        KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                           KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_F12,
        KC_TAB, KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,                           KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_MINS,
        KC_ESC, KC_LSFT,KC_A,   KC_S,   KC_D,   KC_F,                           KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
        KC_LSFT,KC_LCTL,KC_X,   KC_C,   KC_V,   KC_DOT,                         KC_N,   KC_M,   KC_T,   KC_G,   KC_Z,   KC_LSFT,
                        KC_LEFT,KC_RGHT,                                                        KC_UP,  KC_DOWN,
                                        KC_BSPC,KC_SPC,                         KC_ENT, KC_DEL,
                                                KC_TRNS,KC_LCTL,        KC_LGUI,KC_COMM,
                                                KC_TRNS,KC_TRNS,        TG(QTY),  KC_DOT
    ),
	[FUNCTION] = LAYOUT_5x6(
        KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,                          KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                        KC_HOME,KC_END,                                                         KC_PGUP,KC_PGDN,
                                        KC_TRNS,KC_TRNS,                        KC_TRNS,KC_TRNS,
                                                KC_TRNS,KC_TRNS,        KC_TRNS,KC_TRNS,
                                                KC_TRNS,KC_TRNS,        TG(QTY),  KC_TRNS
    )
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)





