/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "quantum.h"
#include QMK_KEYBOARD_H

enum msk_keycodes {
  KC_MSK_KNOB_BTN = SAFE_RANGE,
  KC_MSK_VIM_TGL_BTN
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,           KC_MSK_KNOB_BTN,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        _______, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, _______, _______, _______, _______, KC_PSCR,          _______,
        _______, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MSK_VIM_TGL_BTN,           KC_INSERT,
        _______, _______, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,            _______,
        _______, _______, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, RGB_HUI, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, RGB_MOD, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),


};
// clang-format on

/////
///// CUSTOM KNOB MACROS
/////

// update KNOB_MODE_COUNT to match
// # of elements in enum KNOB_MODE

// knob button stuff
const uint16_t MACRO_TAP_THRESHOLD = 300;

deferred_token callback_token = 0; // typedef uint8_t deferred_token
int presses_count = 0;
bool isVerticalScroll = true;
bool isHoldForMute = false;
bool knob_btn_held = false;
bool fn_btn_held = false;

/////
///// CUSTOM VIM MACROS
/////
bool vimCapsMode = false;

// playback mode callback
uint32_t knob_playback_callback(uint32_t trigger_time, void *cb_arg)
{
  if (knob_btn_held && presses_count == 1)
  {
    if (!isHoldForMute)
    {
      isHoldForMute = true;
      return 600 - MACRO_TAP_THRESHOLD;
    }
    else
    {
      tap_code(KC_MUTE);
      isHoldForMute = false;
    }
  }
  else
  {
    switch (presses_count)
    {
      case 1:
        tap_code(KC_MPLY);
        break;
      case 2:
        tap_code(KC_MNXT);
        break;
      case 3:
        tap_code(KC_MPRV);
        break;
      default:
        tap_code(KC_MUTE);
        break;
    }
  }
  presses_count = 0;
  callback_token = INVALID_DEFERRED_TOKEN;
  return 0; // if ≠ 0, repeat after n milliseconds. otherwise, end.
}

// handle button event
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode)
  {
    case KC_MSK_KNOB_BTN:
      knob_btn_held = record->event.pressed;
      if (record->event.pressed) // on key down
      {
        presses_count++;
        if (callback_token == INVALID_DEFERRED_TOKEN)
          callback_token = defer_exec(MACRO_TAP_THRESHOLD, knob_playback_callback, NULL);
        else
          extend_deferred_exec(callback_token, MACRO_TAP_THRESHOLD);
        break;
      }
      return false; // Skip all further processing of this key
    case KC_MSK_VIM_TGL_BTN:
      if (record->event.pressed) {
        vimCapsMode = !vimCapsMode;
      }
      return false;
    case KC_CAPS:
      if (!vimCapsMode) return true;
      else
      {
        record->event.pressed ? register_code16(KC_ESC) : unregister_code16(KC_ESC);
        return false;
      }
      break;
    case KC_ESC:
      if (!vimCapsMode) return true;
      else
      {
        record->event.pressed ? register_code16(KC_CAPS) : unregister_code16(KC_CAPS);
        return false;
      }
    case MO(1):
      fn_btn_held = record->event.pressed;
      return true;
  }
  return true;
}


#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (fn_btn_held)
  {
    tap_code(clockwise ? KC_PAUS : KC_SLCK);
    return false; // prevent unwanted volume change
  }
  
  tap_code(clockwise ? KC_VOLU : KC_VOLD);
  return false;
}
#endif // ENCODER_ENABLE


///
/// LEDs
///
const uint8_t MODE_LED_IDX = 69; // nice

bool flash_state = false;
uint8_t on_brightness = 255;
deferred_token mode_led_token = 0;

uint32_t mode_led_callback(uint32_t trigger_time, void *cb_arg)
{
  uint32_t delay_time = 100;
  if (!vimCapsMode)
  {
    flash_state = true;
  }
  else
  {
    flash_state = !flash_state;
    delay_time = 500;
  }
  return delay_time;
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max)
{
  /* mode LED */
  if (mode_led_token == INVALID_DEFERRED_TOKEN)
    mode_led_token = defer_exec(100, mode_led_callback, NULL);
  
  if (flash_state)
  {
    RGB_MATRIX_INDICATOR_SET_COLOR(MODE_LED_IDX, on_brightness, on_brightness, on_brightness);
  }
  else
  {
    RGB_MATRIX_INDICATOR_SET_COLOR(MODE_LED_IDX, 0, 0, 0);
  }

  /* Caps Lock */
  if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
    RGB_MATRIX_INDICATOR_SET_COLOR(67, on_brightness, on_brightness, on_brightness);
    RGB_MATRIX_INDICATOR_SET_COLOR(70, on_brightness, on_brightness, on_brightness);
    RGB_MATRIX_INDICATOR_SET_COLOR(73, on_brightness, on_brightness, on_brightness);
    RGB_MATRIX_INDICATOR_SET_COLOR(76, on_brightness, on_brightness, on_brightness);
    RGB_MATRIX_INDICATOR_SET_COLOR(80, on_brightness, on_brightness, on_brightness);
    RGB_MATRIX_INDICATOR_SET_COLOR(83, on_brightness, on_brightness, on_brightness);
    RGB_MATRIX_INDICATOR_SET_COLOR(87, on_brightness, on_brightness, on_brightness);
    RGB_MATRIX_INDICATOR_SET_COLOR(91, on_brightness, on_brightness, on_brightness);
    RGB_MATRIX_INDICATOR_SET_COLOR(0, on_brightness, on_brightness, on_brightness);
    RGB_MATRIX_INDICATOR_SET_COLOR(1, on_brightness, on_brightness, on_brightness);
    RGB_MATRIX_INDICATOR_SET_COLOR(2, on_brightness, on_brightness, on_brightness);
    RGB_MATRIX_INDICATOR_SET_COLOR(3, on_brightness, on_brightness, on_brightness);
    RGB_MATRIX_INDICATOR_SET_COLOR(4, on_brightness, on_brightness, on_brightness);
    RGB_MATRIX_INDICATOR_SET_COLOR(5, on_brightness, on_brightness, on_brightness);
    RGB_MATRIX_INDICATOR_SET_COLOR(11, on_brightness, on_brightness, on_brightness);
    RGB_MATRIX_INDICATOR_SET_COLOR(17, on_brightness, on_brightness, on_brightness);
    // rgb_matrix_set_color_all(RGB_WHITE);
  }
}