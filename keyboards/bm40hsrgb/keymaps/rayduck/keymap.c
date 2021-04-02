/* Copyright 2020 tominabox1
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layers {
  _QWERTY,
  _SYMBOL,
  _NUMBER,
  _ADJUST,
  _NUMPAD,
  _FNKEY,
  _MOUSE,
  _COMMAND,
};

// Tap Dance keycodes
enum td_keycodes {
  TD_SFT_COLON,
};

typedef enum {
  TD_NONE,
  TD_UNKNOWN,
  TD_SINGLE_TAP,
  TD_SINGLE_HOLD,
  TD_DOUBLE_SINGLE_TAP
} td_state_t;

static td_state_t td_state;

// Tap Dance functions
td_state_t cur_dance(qk_tap_dance_state_t *state);

void sftcln_finished(qk_tap_dance_state_t *state, void *user_data);
void sftcln_reset(qk_tap_dance_state_t *state, void *user_data);

// lower tapping term
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TD(TD_SFT_COLON):
      return 100;
    default:
      return TAPPING_TERM;
  }
}



// Layout
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | G/Esc|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   '  |^/Ent |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | S/:  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Numpad| Ctrl | Alt  |S/Bksp|Symbol|    Space    |Number|S/Left|A/Down| ^/Up  |Fn/Rt |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_mit(
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
    LGUI_T(KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_QUOT, LCTL_T(KC_ENT),
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC,
    MO(_NUMPAD), KC_LCTL, KC_LALT, LSFT_T(KC_BSPC), MO(_SYMBOL), KC_SPC, MO(_NUMBER), RSFT_T(KC_LEFT), RALT_T(KC_DOWN), RSFT_T(KC_UP), LT(_FNKEY,KC_RGHT)
),

/* Symbol
 * ,-----------------------------------------------------------------------------------.
 * | S+Tab|      |   @  |   #  |      |      |      |      |   [  |   ]  |      | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   !  |   $  |   %  |   ^  |      |      |   (  |   )  |   {  |   }  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   ~  |      |      |   &  |      |      |   *  |   <  |   >  |   ?  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |Commnd|      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMBOL] = LAYOUT_planck_mit(
    LSFT(KC_TAB), KC_NO, KC_AT, KC_HASH, KC_NO, KC_NO, KC_NO, KC_NO, KC_LBRC, KC_RBRC, KC_NO, KC_DEL,
    KC_TRNS, KC_EXLM, KC_DLR, KC_PERC, KC_CIRC, KC_NO, KC_NO, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_PIPE,
    KC_TRNS, KC_TILD, KC_NO, KC_NO, KC_AMPR, KC_NO, KC_NO, KC_ASTR, KC_LT, KC_GT, KC_QUES, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

/* Number
 * ,-----------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   1  |   4  |   5  |   6  |      |      |   +  |   -  |   =  |   :  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   `  |      |      |   7  |      |      |   0  |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |S/Del |Commnd|             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMBER] = LAYOUT_planck_mit(
    KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL,
    KC_TRNS, KC_1, KC_4, KC_5, KC_6, KC_NO, KC_NO, KC_PLUS, KC_MINS, KC_EQL, KC_COLON, KC_BSLS,
    KC_TRNS, KC_GRAVE, KC_NO, KC_NO, KC_7, KC_NO, KC_NO, KC_0, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, LSFT_T(KC_DEL), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

/* Adjust
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |QWERTY|      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_mit(
    KC_TRNS, RESET, DEBUG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS,
    TO(_QWERTY), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

[_NUMPAD] = LAYOUT_planck_mit(KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P7, KC_P8, KC_P9, KC_PPLS, KC_TRNS, TG(_NUMPAD), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P4, KC_P5, KC_P6, KC_PMNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P1, KC_P2, KC_P3, KC_PAST, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0, KC_PDOT, KC_PEQL, KC_PSLS, KC_TRNS),

[_FNKEY] = LAYOUT_planck_mit(KC_F11, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F12, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),


[_MOUSE] = LAYOUT_planck_mit(KC_NO, KC_NO, KC_NO, KC_MS_U, KC_NO, KC_NO, KC_NO, KC_NO, KC_WH_D, KC_NO, KC_ACL0, KC_NO, TO(_QWERTY), KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO, KC_NO, KC_BTN1, KC_BTN2, KC_WH_U, KC_ACL1, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_ACL2, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),

/* Command
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |   _  |   |  |   ;  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Mouse|      |      |   \  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |    Config   |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_COMMAND] = LAYOUT_planck_mit(
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_UNDS, KC_PIPE, KC_SCLN, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(_MOUSE), KC_NO, KC_NO, KC_BSLS, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, TO(_ADJUST), KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO)

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _SYMBOL, _NUMBER, _COMMAND);
};


// Determine the tapdance state to return
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) return TD_DOUBLE_SINGLE_TAP;
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

// Handle the possible states for each tapdance keycode you define:

void sftcln_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_COLON);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow 2 consecutive colons `::` within tapping term
            tap_code16(KC_COLON);
            register_code16(KC_COLON);
        default:
            break;
    }
}

void sftcln_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_COLON);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_COLON);
        default:
            break;
    }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_SFT_COLON] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sftcln_finished, sftcln_reset)
};

