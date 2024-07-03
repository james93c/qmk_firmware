#include QMK_KEYBOARD_H

// define names for layers
#define DVORAK 0
#define QWERTY 1
#define FUNCTION 2

// shorthand to keep grid spacing
#define DVK DVORAK
#define QTY QWERTY
#define FNC FUNCTION

// custom key code defs
#define CC_PLUS LSFT(KC_EQL)
#define CC_PIPE LSFT(KC_BSLS)
#define CC_LBRA LSFT(KC_LBRC)
#define CC_RBRA LSFT(KC_RBRC)

#define FNC_SPC LT(FNC, KC_SPC)
#define GUI_ENT MT(MOD_LGUI, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[DVORAK] = LAYOUT_5x6(
        KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                           KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_F12,
        KC_TAB, KC_QUOT,KC_COMM,KC_DOT, KC_P,   KC_Y,                           KC_F,   KC_G,   KC_C,   KC_R,   KC_L,   KC_SLSH,
        KC_ESC, KC_A,   KC_O,   KC_E,   KC_U,   KC_I,                           KC_D,   KC_H,   KC_T,   KC_N,   KC_S,   KC_MINS,
        KC_LSFT,KC_SCLN,KC_Q,   KC_J,   KC_K,   KC_X,                           KC_B,   KC_M,   KC_W,   KC_V,   KC_Z,   KC_RSFT,
                        KC_LEFT,KC_RGHT,                                                        KC_UP,  KC_DOWN,
                                        KC_BSPC,FNC_SPC,                        GUI_ENT, KC_RSFT,
                                                KC_DEL, KC_LCTL,        KC_TAB, KC_LALT,
                                                KC_BSLS,KC_EQL,         KC_LBRC,KC_RBRC
                                        // MO(FNC),KC_SPC,                         KC_ENT, KC_DEL,
                                        //         KC_BSPC,KC_LCTL,        KC_LGUI,KC_LBRC,
                                        //         KC_DEL, KC_ENT,         KC_LALT,KC_RBRC
    ),
	[QWERTY] = LAYOUT_5x6(
        KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                           KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_F12,
        KC_TAB, KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,                           KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_MINS,
        KC_ESC, KC_LSFT,KC_A,   KC_S,   KC_D,   KC_F,                           KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,
        KC_LSFT,KC_LCTL,KC_X,   KC_C,   KC_V,   KC_DOT,                         KC_N,   KC_M,   KC_T,   KC_G,   KC_Z,   KC_LSFT,
                        KC_LEFT,KC_RGHT,                                                        KC_UP,  KC_DOWN,
                                        KC_BSPC,KC_SPC,                         KC_ENT, KC_DEL,
                                                _______,KC_LCTL,        KC_LGUI,KC_COMM,
                                                _______,_______,        TG(QTY),KC_DOT
    ),
	[FUNCTION] = LAYOUT_5x6(
        KC_F12, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                          KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,
        _______,KC_PGUP,KC_HOME,KC_UP,  KC_END, _______,                        _______,CC_PLUS,CC_PIPE,CC_LBRA,CC_RBRA,_______,
        _______,KC_PGDN,KC_LEFT,KC_DOWN,KC_RGHT,KC_ENT,                         _______,KC_EQL, KC_BSLS,KC_LBRC,KC_RBRC,_______,
        _______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______,_______,

                        KC_HOME,KC_END,                                                         KC_PGUP,KC_PGDN,
                                        _______,_______,                        _______,_______,
                                                _______,_______,        _______,_______,
                                                _______,_______,        TG(QTY), _______
    )
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
