// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

#include <default_keyboard.h>
#include <keycodes.h>
#include <stdint.h>
#include <avr/pgmspace.h>
#include <quantum.h>
#include <process_tap_dance.h>
#include <led.h>

#define INDICATOR_BRIGHTNESS 30

#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s , Override
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv,Override)

// Light combinations
#define SET_INDICATORS(hsv) \
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {35+0, 1, hsv}
#define SET_UNDERGLOW(hsv) \
	{1, 6, hsv}, \
    {35+1, 6,hsv}
#define SET_NUMPAD(hsv)     \
	{35+15, 5, hsv},\
	  {35+22, 3, hsv},\
	  {35+27, 3, hsv}
#define SET_NUMROW(hsv) \
	{10, 2, hsv}, \
		{20, 2, hsv}, \
		{30, 2, hsv}, \
	  {35+ 10, 2, hsv}, \
	  {35+ 20, 2, hsv}, \
	  {35+ 30, 2, hsv}
#define SET_INNER_COL(hsv)	\
	{33, 4, hsv}, \
	  {35+ 33, 4, hsv}

#define SET_OUTER_COL(hsv) \
	{7, 4, hsv}, \
	  {35+ 7, 4, hsv}
#define SET_THUMB_CLUSTER(hsv) 	\
	{25, 2, hsv}, \
	  {35+ 25, 2, hsv}
#define SET_LAYER_ID(hsv) 	\
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {35+0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
		{1, 6, hsv}, \
    {35+1, 6, hsv}, \
		{7, 4, hsv}, \
	  {35+ 7, 4, hsv}, \
		{25, 2, hsv}, \
	  {35+ 25, 2, hsv}


enum sofle_layers
{
  _QWERTY,
  _NULLED,
  _NUMPAD,
  _LOWER,
  _RAISE,
  _ADJUST,
  _SWITCH
};

// Tap Dance declarations
enum
{
  TD_LSFT_CAP,
  TD_LCTL_WIN,
  TD_RCTL_ESC,
  TD_RSFT_WIN,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
  [TD_LSFT_CAP] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
  [TD_LCTL_WIN] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_LWIN),
  [TD_RCTL_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_ESC),
  [TD_RSFT_WIN] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_RWIN),
};

#define KC_QWERTY PDF(_QWERTY)
#define KC_NULLED PDF(_NULLED)
#define KC_NUMPAD PDF(_NUMPAD)
#define KC_C_P LT(_SWITCH, KC_P)
#define KC_SWITCH LT(_SWITCH, XXXXXXX)
#define KC_LSFT_CAP TD(TD_LSFT_CAP)
#define KC_LCTL_WIN TD(TD_LCTL_WIN)
#define KC_RCTL_ESC TD(TD_RCTL_ESC)
#define KC_RSFT_WIN TD(TD_RSFT_WIN)
#define KC_LALT_TILDE LALT_T(KC_TILDE)
#define KC_RALT_B RALT_T(KC_B)
#define KC_RALT_ESC RALT_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /*
   * QWERTY
   * ,-----------------------------------------.                    ,-----------------------------------------.
   * |  -   |  -   |  -   |  -   |  -   |  -   |                    |  -   |  -   |  -   |  -   |  -   |  -   |
   * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
   * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |  P/6 | Bspc |
   * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
   * |LSFT/CAP| A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |  ; |RSFT/WIN|
   * |------+------+------+------+------+------|  MUTE |    | PAUSE |------+------+------+------+------+------|
   * |LCTL/WIN| Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |  / |RCTL/ESC|
   * `-----------------------------------------/       /     \      \-----------------------------------------'
   *          |      |      | LALT/` |LOWER | / SPACE /       \ ENTER\  |RAISE | RALT/B |      |      |
   *          |      |      |        |      |/       /         \      \ |      |        |      |      |
   *          `-------------------------------------'           '------''-----------------------------'
   */

  [_QWERTY] = LAYOUT(
    XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_C_P,  KC_BSPC,
    KC_LSFT_CAP, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, MT(MOD_RALT, KC_ESC),
    KC_LCTL_WIN, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE,     KC_MPLY, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RALT_ESC,
          XXXXXXX, XXXXXXX, KC_LALT_TILDE, TL_LOWR, KC_SPC,                 KC_ENT, TL_UPPR, KC_RALT_B, XXXXXXX, XXXXXXX
  ),

  /*
   * NULLED
   * ,-----------------------------------------.                    ,-----------------------------------------.
   * |  -   |  -   |  -   |  -   |  -   |  -   |                    |  -   |  -   |  -   |  -   |  -   |  -   |
   * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
   * | TAB  |  LMS |  PMS |  MMS |  NMS |  RMS |                    |  SCL |  SCD |  SCU |  SCR | -/6  | Bspc |
   * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
   * |LSFT/CAP| -  |  -   |  -   |  -   |  -   |-------.    ,-------| LEFT | DOWN |  UP  | RIGHT|  - |RSFT/WIN|
   * |------+------+------+------+------+------|  MUTE |    | PAUSE |------+------+------+------+------+------|
   * |LSFT/WIN| -  |  -   |  -   |  -   |  -   |-------|    |-------|  -   |  -   |  -   |  -   |  - |RCTL/ESC|
   * `-----------------------------------------/       /     \      \-----------------------------------------'
   *          |      |      | LALT/` |LOWER | / SPACE /       \ ENTER\  |RAISE | RALT/B |      |      |
   *          |      |      |        |      |/       /         \      \ |      |        |      |      |
   *          `-------------------------------------'           '------''-----------------------------'
   */

  [_NULLED] = LAYOUT(
    XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_TAB,      MS_BTN1, MS_BTN4, MS_BTN3, MS_BTN5, MS_BTN2,                            MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLD, KC_SWITCH, KC_BSPC,
    KC_LSFT_CAP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT_WIN,
    KC_LCTL_WIN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE,          KC_MPLY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT_ESC,
                XXXXXXX, XXXXXXX, KC_LALT_TILDE, TL_LOWR, KC_SPC,                    KC_ENT, TL_UPPR, KC_RALT_B, XXXXXXX, XXXXXXX
  ),
  /*
   * NUMPAD
   * ,-----------------------------------------.                    ,-----------------------------------------.
   * |  -   |  -   |  -   |  -   |  -   |  -   |                    |  -   |  -   |  -   |  -   |  -   |  -   |
   * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
   * | TAB  |  -   |  9   |  8   |  7   | NUM  |                    | NUM  |  7   |  8   |  9   | -/6  | Bspc |
   * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
   * |  /   |  +   |  6   |  5   |  4   |  .   |-------.    ,-------|  .   |  4   |  5   |  6   |  +   |   /  |
   * |------+------+------+------+------+------|  MUTE |    | PAUSE |------+------+------+------+------+------|
   * |  ^   |  *   |  3   |  2   |  1   |  0   |-------|    |-------|  0   |  1   |  2   |  3   |  *   |  ^   |
   * `-----------------------------------------/       /     \      \-----------------------------------------'
   *          |      |      | LALT/` |LOWER | / SPACE /       \ ENTER\  |RAISE | RALT/B |      |      |
   *          |      |      |        |      |/       /         \      \ |      |        |      |      |
   *          `-------------------------------------'           '------''-----------------------------'
   */

  [_NUMPAD] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_TAB,  KC_PMNS, KC_P9,   KC_P8,   KC_P7,   KC_NUM,                      KC_NUM, KC_P7, KC_P8, KC_P9, KC_SWITCH, KC_BSPC,
    KC_PSLS, KC_PPLS, KC_P6,   KC_P5,   KC_P4,   KC_PDOT,                     KC_PDOT, KC_P4, KC_P5, KC_P6, KC_PPLS, KC_PSLS,
    S(KC_6), KC_PAST, KC_P3,   KC_P2,   KC_P1,   KC_P0, KC_MUTE,     KC_MPLY, KC_P0, KC_P1, KC_P2, KC_P3, KC_PAST, S(KC_6),
            XXXXXXX, XXXXXXX, KC_LALT_TILDE, TL_LOWR, KC_SPC,           KC_PENT, TL_UPPR, KC_RALT_B, XXXXXXX, XXXXXXX
  ),
  /* LOWER
   * ,-----------------------------------------.                    ,-----------------------------------------.
   * |  -   |  -   |  -   |  -   |  -   |  -   |                    |  -   |  -   |  -   |  -   |  -   |  -   |
   * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
   * | ESC  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | DEL  |
   * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
   * |      |   1  |   2  |   3  |   4  |   5  |-------.    ,-------|   6  |   7  |   8  |   9  |   0  | F11  |
   * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
   * |      |   !  |   @  |   #  |   $  |   %  |-------|    |-------|   ^  |   &  |   *  |   (  |   )  | F12  |
   * `-----------------------------------------/       /     \      \-----------------------------------------'
   *            |      |      |      |      | / Enter /       \Space \  |      |      |      |      |
   *            |      |      |      |      |/       /         \      \ |      |      |      |      |
   *            `----------------------------------'           '------''---------------------------'
   */
  [_LOWER] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_DEL,
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F11,
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______,      _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_F12,
                  _______, _______, _______, _______, KC_ENT,              KC_SPC, _______, _______, _______, _______
  ),
  /* RAISE
   * ,----------------------------------------.                    ,-----------------------------------------.
   * |  -   |  -   |  -   |  -   |  -   |  -   |                    |  -   |  -   |  -   |  -   |  -   |  -   |
   * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
   * | ESC  |  -   |  _   |  [   |   ]  |  \   |                    |  !   |  &   |  *   |   (  |  )   | DEL  |
   * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
   * |      |  =   |  +   |  {   |   }  |  |   |-------.    ,-------| LEFT | DOWN |  UP  | RIGHT|  ;   |      |
   * |------+------+------+------+------+------|        |   |       |------+------+------+------+------+------|
   * |      |  <   |  >   |  ?   |   '  |  "   |-------|    |-------| INST | HOME |  END | PG_UP| PG_DN|      |
   * `-----------------------------------------/       /     \      \-----------------------------------------'
   *            |      |      |      |      | / Enter /       \Space \  |      |      |      |      |
   *            |      |      |      |      |/       /         \      \ |      |      |      |      |
   *            `----------------------------------'            '------''---------------------------'
   */
  [_RAISE] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,    XXXXXXX,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_ESC,  KC_MINS, KC_UNDS, KC_LBRC,    KC_RBRC,    KC_BSLS,                         KC_EXLM, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
    _______, KC_EQL,  KC_LCTL, S(KC_LBRC), S(KC_RBRC), KC_PIPE,                         KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_SCLN, _______,
    _______, KC_LABK, KC_RABK, KC_QUES,    KC_QUOT,    KC_DQUO, _______,       _______, KC_INS, KC_HOME, KC_END, KC_PGUP, KC_PGDN, _______,
                         _______, _______, _______, _______, KC_ENT,               KC_SPC, _______, _______, _______, _______
  ),
  /* ADJUST
   * ,-----------------------------------------.                    ,-----------------------------------------.
   * |  -   |  -   |  -   |  -   |  -   |  -   |                    |  -   |  -   |  -   |  -   |  -   |  -   |
   * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
   * | ESC  |      |      |      |      |      |                    | NUMP | BRDWN|      | BRUP | CAPS | DEL  |
   * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
   * |      |      |      |      |      |      |-------.    ,-------| SLCK | VOLDO| MUTE | VOLUP| CAPSW|      |
   * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
   * |      |      |      |      |      |      |-------|    |-------|  REP | PREV | PLAY | NEXT | PSCRN|      |
   * `-----------------------------------------/       /     \      \-----------------------------------------'
   *            |      |      |      |      | / Enter /       \Space \  |      |      |      |      |
   *            |      |      |      |      |/       /         \      \ |      |      |      |      |
   *            `----------------------------------'           '------''---------------------------'
   */
  [_ADJUST] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           KC_NUM,  KC_BRID, XXXXXXX, KC_BRIU, KC_CAPS, KC_DEL,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                           KC_SCRL, KC_VOLD, KC_MUTE, KC_VOLU, CW_TOGG, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,         _______, QK_REP,  KC_MPRV, KC_MPLY, KC_MNXT, KC_PSCR, XXXXXXX,
                   _______, _______, _______, _______, KC_ENT,                KC_SPC, _______, _______, _______, _______
  ),

  /* SWITCH
  * ,-----------------------------------------.                    ,-----------------------------------------.
  * |  -   |  -   |  -   |  -   |  -   |  -   |                    |  -   |  -   |  -   |  -   |  -   |  -   |
  * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
  * | ESC  |   0  |  1   |  2   |      |      |                    |      |      |      |      |      | DEL  |
  * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
  * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
  * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
  * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
  * `-----------------------------------------/       /     \      \-----------------------------------------'
  *            |      |      |      |      | / Enter /       \Space \  |      |      |      |      |
  *            |      |      |      |      |/       /         \      \ |      |      |      |      |
  *            `----------------------------------'           '------''---------------------------'
  */
  [_SWITCH] = LAYOUT(
    XXXXXXX, XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX, XXXXXXX,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_ESC,  DF(_QWERTY), DF(_NULLED), DF(_NUMPAD), _______, _______,                        _______, _______, _______, _______, _______, KC_DEL,
    _______, _______,     _______,     _______,     _______, _______,                        _______, _______, _______, _______, _______, _______,
    _______, _______,     _______,     _______,     _______, _______, _______,      _______, _______, _______, _______, _______, _______, _______,
                               _______, _______, _______, _______, KC_ENT,              KC_SPC, _______, _______, _______, _______
  )
};

#ifdef RGBLIGHT_ENABLE
char layer_state_str[70];
// Now define the array of layers. Later layers take precedence

// QWERTY,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_qwerty_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_LAYER_ID(HSV_RED)

);
const rgblight_segment_t PROGMEM layer_colemakdh_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_LAYER_ID(HSV_PINK)
);

// _NUM,
// Light on outer column and underglow
const rgblight_segment_t PROGMEM layer_num_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_LAYER_ID(HSV_TEAL)

);
// _SYMBOL,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_symbol_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_LAYER_ID(HSV_BLUE)

);
// _COMMAND,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_command_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_LAYER_ID(HSV_PURPLE)
);

//_NUMPAD
const rgblight_segment_t PROGMEM layer_numpad_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_INDICATORS(HSV_ORANGE),
  SET_UNDERGLOW(HSV_ORANGE),
  SET_NUMPAD(HSV_BLUE),
  {7, 4, HSV_ORANGE},
  {25, 2, HSV_ORANGE},
  {35+6, 4, HSV_ORANGE},
  {35+25, 2, HSV_ORANGE}
);
// _SWITCHER   // light up top row
const rgblight_segment_t PROGMEM layer_switcher_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_LAYER_ID(HSV_GREEN),
  SET_NUMROW(HSV_GREEN)
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
  layer_qwerty_lights,
  layer_num_lights, // overrides layer 1
  layer_symbol_lights,
  layer_command_lights,
  layer_numpad_lights,
  layer_switcher_lights, // Overrides other layers
  layer_colemakdh_lights
);

layer_state_t layer_state_set_user(layer_state_t state)
{
  rgblight_set_layer_state(0, layer_state_cmp(default_layer_state, _QWERTY));
  rgblight_set_layer_state(7, layer_state_cmp(default_layer_state, _NULLED));
  rgblight_set_layer_state(4, layer_state_cmp(default_layer_state, _NUMPAD));


  rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
  rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
  rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
  rgblight_set_layer_state(5, layer_state_cmp(state, _SWITCH));
  return state;
}

void keyboard_post_init_user(void)
{
  // Enable the LED layers
  rgblight_layers = my_rgb_layers;

  rgblight_mode(10); // haven't found a way to set this in a more useful way
}
#endif

#ifdef OLED_ENABLE

static void render_logo(void)
{
  /*static const char PROGMEM qmk_logo[] = {
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92,
    0x93, 0x94,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2,
    0xB3, 0xB4,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2,
    0xD3, 0xD4, 0x00
  };

  oled_write_P(qmk_logo, false);*/

  uint8_t mods = get_mods();
  oled_write_ln_P(PSTR("-----"), true);
  oled_write_ln_P(PSTR("ALT  \n"), mods & MOD_MASK_ALT);
  oled_write_ln_P(PSTR("SHIFT\n"), mods & MOD_MASK_SHIFT);
  oled_write_ln_P(PSTR("CTRL \n"), mods & MOD_MASK_CTRL);
  oled_write_ln_P(PSTR("SUPER"), mods & MOD_MASK_GUI);
  oled_write_ln_P(PSTR("-----"), true);
}

static void print_status_narrow(void)
{
  // Print current mode
  oled_write_P(PSTR("\n\n"), false);
  oled_write_ln_P(PSTR("ARC\nORIUM"), false);

  oled_write_ln_P(PSTR(""), false);

  switch (get_highest_layer(default_layer_state))
  {
  case _QWERTY:
    oled_write_ln_P(PSTR("Qwrt"), false);
    break;
  case _NULLED:
    oled_write_ln_P(PSTR("Null"), false);
    break;
  case _NUMPAD:
    oled_write_ln_P(PSTR("Nump"), false);
    break;

  default:
    oled_write_ln_P(PSTR("Undef"), false);
  }
  oled_write_P(PSTR("\n\n"), false);
  // Print current layer
  oled_write_ln_P(PSTR("LAYER"), false);
  switch (get_highest_layer(layer_state))
  {
  case _QWERTY:
  case _NULLED:
  case _NUMPAD:
    oled_write_P(PSTR("Base\n"), false);
    break;
  case _RAISE:
    oled_write_P(PSTR("Raise"), false);
    break;
  case _LOWER:
    oled_write_P(PSTR("Lower"), false);
    break;
  case _ADJUST:
    oled_write_P(PSTR("Adj\n"), false);
    break;
  case _SWITCH:
    oled_write_P(PSTR("Swit\n"), false);
    break;
  default:
    oled_write_ln_P(PSTR("Undef"), false);
  }

  // Host Keyboard LED Status
  led_t led_state = host_keyboard_led_state();
  if (led_state.num_lock) {
   oled_write_ln_P(PSTR("NUM"), false);
  }
  if (led_state.caps_lock) {
   oled_write_ln_P(PSTR("CAP"), false);
  }
  if (led_state.scroll_lock) {
   oled_write_ln_P(PSTR("SCR"), false);
  }

}

oled_rotation_t oled_init_user(oled_rotation_t rotation)
{
  // if (is_keyboard_master())
  // {
    return OLED_ROTATION_270;
  // }
  // return rotation;
}

bool oled_task_user(void)
{
  if (is_keyboard_master())
  {
    print_status_narrow();
  }
  else
  {
    render_logo();
  }
  return false;
}

#endif

/*
bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
  switch (keycode)
  {
  case KC_PRVWD:
    if (record->event.pressed)
    {
      if (keymap_config.swap_lctl_lgui)
      {
        register_mods(mod_config(MOD_LALT));
        register_code(KC_LEFT);
      }
      else
      {
        register_mods(mod_config(MOD_LCTL));
        register_code(KC_LEFT);
      }
    }
    else
    {
      if (keymap_config.swap_lctl_lgui)
      {
        unregister_mods(mod_config(MOD_LALT));
        unregister_code(KC_LEFT);
      }
      else
      {
        unregister_mods(mod_config(MOD_LCTL));
        unregister_code(KC_LEFT);
      }
    }
    break;
  case KC_NXTWD:
    if (record->event.pressed)
    {
      if (keymap_config.swap_lctl_lgui)
      {
        register_mods(mod_config(MOD_LALT));
        register_code(KC_RIGHT);
      }
      else
      {
        register_mods(mod_config(MOD_LCTL));
        register_code(KC_RIGHT);
      }
    }
    else
    {
      if (keymap_config.swap_lctl_lgui)
      {
        unregister_mods(mod_config(MOD_LALT));
        unregister_code(KC_RIGHT);
      }
      else
      {
        unregister_mods(mod_config(MOD_LCTL));
        unregister_code(KC_RIGHT);
      }
    }
    break;
  case KC_LSTRT:
    if (record->event.pressed)
    {
      if (keymap_config.swap_lctl_lgui)
      {
        //CMD-arrow on Mac, but we have CTL and GUI swapped
        register_mods(mod_config(MOD_LCTL));
        register_code(KC_LEFT);
      }
      else
      {
        register_code(KC_HOME);
      }
    }
    else
    {
      if (keymap_config.swap_lctl_lgui)
      {
        unregister_mods(mod_config(MOD_LCTL));
        unregister_code(KC_LEFT);
      }
      else
      {
        unregister_code(KC_HOME);
      }
    }
    break;
  case KC_LEND:
    if (record->event.pressed)
    {
      if (keymap_config.swap_lctl_lgui)
      {
        //CMD-arrow on Mac, but we have CTL and GUI swapped
        register_mods(mod_config(MOD_LCTL));
        register_code(KC_RIGHT);
      }
      else
      {
        register_code(KC_END);
      }
    }
    else
    {
      if (keymap_config.swap_lctl_lgui)
      {
        unregister_mods(mod_config(MOD_LCTL));
        unregister_code(KC_RIGHT);
      }
      else
      {
        unregister_code(KC_END);
      }
    }
    break;
  }
  return true;
}
*/

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise)
{
  // LEFT
  if (index == 0)
  {
    if (clockwise)
    {
      tap_code(KC_VOLU);
    }
    else
    {
      tap_code(KC_VOLD);
    }
  }
  // RIGHT
  else if (index == 1)
  {
    switch (get_highest_layer(layer_state))
    {
    case _QWERTY:
    case _NULLED:
    case _NUMPAD:
      if (clockwise)
      {
        tap_code(KC_VOLD);
      }
      else
      {
        tap_code(KC_VOLU);
      }
      break;
    case _RAISE:
    case _LOWER:
    case _ADJUST:
    case _SWITCH:
      if (clockwise)
      {
        tap_code(KC_VOLD);
      }
      else
      {
        tap_code(KC_VOLU);
      }
      break;
    default:
      if (clockwise)
      {
        tap_code(KC_WH_D);
      }
      else
      {
        tap_code(KC_WH_U);
      }
      break;
    }
  }
  return true;
}

#endif
