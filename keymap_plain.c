/*
Copyright 2016 Fred Sundvik <fsundvik@gmail.com>
Jun Wako <wakojun@gmail.com>

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

#include "keymap_common.h"

const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    KEYMAP(  // layer 0 : default
        // left hand
        EQL, 1,   2,   3,   4,   5,   ESC,
        BSLS,Q,   W,   E,   R,   T,   FN1,
        TAB, A,   S,   D,   F,   G,
        LSFT,Z,   X,   C,   V,   B,   FN0,
        LGUI,GRV, BSLS,LEFT,RGHT,
                                      LCTL,LALT,
                                           HOME,
                                 BSPC,DEL, END,
        // right hand
             FN2, 6,   7,   8,   9,   0,   MINS,
             LBRC,Y,   U,   I,   O,   P,   RBRC,
                  H,   J,   K,   L,   SCLN,QUOT,
             FN0, N,   M,   COMM,DOT, SLSH,RSFT,
                       LEFT,DOWN,UP,  RGHT,RGUI,
        RALT,RCTL,
        PGUP,
        PGDN,ENT, SPC
    ),

    KEYMAP(  // layer 1 : function and symbol keys
        // left hand
        TRNS,F1,  F2,  F3,  F4,  F5,  F11,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,FN3,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             F12, F6,  F7,  F8,  F9,  F10, TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

    KEYMAP(  // layer 2 : keyboard functions
        // left hand
        BTLD,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, FN3,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             TRNS, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),

    KEYMAP(  // layer 3: numpad
        // left hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             TRNS,NLCK,PSLS,PAST,PAST,PMNS,BSPC,
             TRNS,NO,  P7,  P8,  P9,  PMNS,BSPC,
                  NO,  P4,  P5,  P6,  PPLS,PENT,
             TRNS,NO,  P1,  P2,  P3,  PPLS,PENT,
                       P0,  PDOT,SLSH,PENT,PENT,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),
};
/* id for user defined functions */
enum function_id {
    TEENSY_KEY,
};

/*
 * Fn action definition
 */
const uint16_t PROGMEM fn_actions[] = {
    ACTION_FUNCTION(TEENSY_KEY),                    // FN0 - Teensy key
    ACTION_LAYER_MOMENTARY(1),                      // FN1 - switch to Layer1
    ACTION_LAYER_SET(2, ON_PRESS),                  // FN2 - push Layer2
    ACTION_LAYER_SET(3, ON_PRESS),                  // FN3 - push Layer3
    ACTION_LAYER_SET(0, ON_PRESS),                  // FN4 - push Layer0
};

void action_function(keyrecord_t *event, uint8_t id, uint8_t opt)
{
    if (id == TEENSY_KEY) {
        clear_keyboard();
        print("\n\nJump to bootloader... ");
        _delay_ms(250);
        bootloader_jump(); // should not return
        print("not supported.\n");
    }
}

#endif


#define KEYMAPS_SIZE    (sizeof(keymaps) / sizeof(keymaps[0]))
#define FN_ACTIONS_SIZE (sizeof(fn_actions) / sizeof(fn_actions[0]))

void var_dump_keyrecord(keyrecord_t *record)
{
  keyevent_t event = record->event;
  tap_t tap = record->tap;
  
  xprintf("keyRecord:\n\
    keyEvent:\n\
        \tpressed: %d\n\
        \ttime: %u\n\
        \tkey:\n\
        \t\trow: %d\n\
        \t\tcol: %d\n\
    tap:\n\
        \tinterrupted: %d\n\
        \treserved2: %d\n\
        \treserved1: %d\n\
        \treserved0: %d\n\
        \ttap_count: %d\n\
        "
    ,event.pressed, event.time, event.key.row, event.key.col, tap.interrupted, tap.reserved2, tap.reserved1, tap.reserved0, tap.count);
}
//TODO: Make this take the modifier key.  Figure out if this should handle the event with a name like add.
void handle_one_shot_mod_action(keyrecord_t *record)
{  
  dprint("HOSMA");
  keyevent_t event = record->event;
  tap_t tap = record->tap;
  key_t key = event.key;
  uint8_t pressed_keycode = keymap_key_to_keycode(ONESHOTMOD_REFERENCE_LAYER, key);
  uint8_t mod_key = MOD_BIT(pressed_keycode);

  var_dump_keyrecord(record);
  xprintf("pressed_keycode is: %d. mod_key is %d\n",pressed_keycode, mod_key);


// for some reason, the released key sent to the os is the lower case version
  // also, if key is held, the OS does not receive it until another key is pressed.  This affects shift clicking.
  if IS_MOD(pressed_keycode){

    if (event.pressed) {
      register_code(pressed_keycode);
      if (tap.count == 0 || tap.interrupted) {
        xprintf("** adding mod, should be holding key\n");
      } else {
        add_oneshot_mods(mod_key);
        xprintf("** setting mod, should be tapping key. tap.count was %d\n",tap.count);
      }
    } else {
      unregister_code(pressed_keycode);
      if (tap.count == 0 || tap.interrupted) {
        xprintf("** deleting mod, should be releasing from heldkey\n");
      }
      else{
        //clear_oneshot_mods(mod_key);
        xprintf("** mod_key should be releasing. No action required\n tap.count was %d\n",tap.count);
      }
    }
  }
  else
  {
    xprintf("Was not a mod key");
  }
} 

void action_shift_key(keyrecord_t *record)
{
  keyevent_t event = record->event;
  tap_t tap = record->tap;
  key_t key = event.key;
  uint8_t pressed_keycode = keymap_key_to_keycode(SHIFT_KEY_REFERENCE_LAYER, key);
  uint8_t mod_key = MOD_BIT(KC_LSFT);

  //var_dump_keyrecord(record);
  //xprintf("pressed_keycode is: %d. mod_key is %d\n, amk= %d\n",pressed_keycode, mod_key, ACTION_MODS_KEY(MOD_LSFT, mod_key));
  //print("mod_bit ");phex(MOD_BIT(KC_LSFT)); print("\n"); 
  //print("pressed_keycode ");phex(pressed_keycode); print("\n"); 
  //print("key ");phex(key); print("\n"); 
  //print("mod_bit<<8 ");phex(MOD_BIT(KC_LSFT)<<8); print("\n"); 
  //print("mod_bit<<8|pressed_keycode ");phex(MOD_BIT(KC_LSFT)<<8|pressed_keycode); print("\n"); 
  //print("ACTION_MODS_KEY ");phex( ACTION_MODS_KEY(MOD_BIT(KC_LSFT), pressed_keycode)); print("\n"); 

  // for some reason, the released key sent to the os is the lower case version
  // also, if key is held, the OS does not receive it until another key is pressed.  This affects shift clicking.
  if (event.pressed) {
    //print("event.pressed\n");
    add_oneshot_mods(mod_key);
    register_code(pressed_keycode);
  } else {
    //print("event.pressed broke\n");
    unregister_code(pressed_keycode);
  }
}

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    keyevent_t event = record->event;
    tap_t tap = record->tap;

    print("action_function called\n");
    print("id  = "); phex(id); print("\n");
    print("opt = "); phex(opt); print("\n");
    switch (id) {
        case TEENSY_KEY:
            clear_keyboard();
            print("\n\nJump to bootloader... ");
            _delay_ms(250);
            bootloader_jump(); // should not return
            print("not supported.\n");
            break;

        //case TAPSHOT_HOLD_TOGGLE_LAYER:  
            // TODO:
            // - Write some code to do tap one shot hold momentary toggle on layers.
            // - convert ONE_SHOT_MOD to use ACTION_MODS_ONESHOT if possible.  Might save space
            // - remove unused debug statements.
            break;
        case ESCAPE_WRAPPER:
            {
                if (event.pressed) {
                    uint8_t osm = has_any_oneshot_mods();
                    xprintf("escape_wrapper called\n Oneshot mods are: %d\n", get_oneshot_mods());
                    if (osm !=0)
                    {
                      xprintf("clearing oneshot mods\n");
                      clear_oneshot_mods();
                      xprintf("oneshot mods are now %d\n", get_oneshot_mods());
                    }
                    else
                    {
                      xprintf("exec escape\n");
                      add_key(KC_ESC);
                      send_keyboard_report();
                    }
                } else {
                      del_key(KC_ESC);
                      send_keyboard_report();

                  // key was released
                }

            }
            break;
        case ONE_SHOT_MOD:
            // NOTE: cant use register_code to avoid conflicting with magic key bind
            //this is basically how ACTION_MODS_TAP_KEY works.
            handle_one_shot_mod_action(record);
            break;
        case SHIFT_KEY:
            action_shift_key(record);
            break;
    }
}
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    keyevent_t event = record->event;
    tap_t tap = record->tap;

    switch (id) {
        case FAT_ARROW:
            return (event.pressed ?
                    MACRO( T(SPACE), T(EQUAL), D(LSHIFT), T(DOT), U(LSHIFT), T(SPACE), END ) : MACRO_NONE);
            break;
        case THIN_ARROW:
                return (event.pressed ?
                        MACRO( T(SPACE), T(MINS), D(LSHIFT), T(DOT), U(LSHIFT),T(SPACE), END ) : MACRO_NONE);
            break;
        case LSHIFT_LBRACE:
            if (tap.count > 0 && !tap.interrupted) {
                return (event.pressed ?
                        MACRO( D(LSHIFT), T(LBRC), U(LSHIFT), END ) : MACRO_NONE);
            } else {
                return (event.pressed ?
                        MACRO( D(LSHIFT), END ) : MACRO( U(LSHIFT), END ) );
            }
            break;
        case LSHIFT_RBRACE:
            if (tap.count > 0 && !tap.interrupted) {
                return (event.pressed ?
                        MACRO( D(RSHIFT), T(RBRC), U(RSHIFT), END ) : MACRO_NONE);
            } else {
                return (event.pressed ?
                        MACRO( D(RSHIFT), END ) : MACRO( U(RSHIFT), END ) );
            }
            break;
        case LSHIFT_LT:
            if (tap.count > 0 && !tap.interrupted) {
                return (event.pressed ?
                        MACRO( D(LSHIFT), T(COMMA), U(LSHIFT), END ) : MACRO_NONE);
            } else {
                return (event.pressed ?
                        MACRO( D(LSHIFT), END ) : MACRO( U(LSHIFT), END ) );
            }
            break;
        case LSHIFT_GT:
            if (tap.count > 0 && !tap.interrupted) {
                return (event.pressed ?
                        MACRO( D(RSHIFT), D(DOT), U(DOT), U(RSHIFT), END ) : MACRO_NONE);
            } else {
                return (event.pressed ?
                        MACRO( D(RSHIFT), END ) : MACRO( U(RSHIFT), END ) );
            }
            break;
        case HELLO:
            return (event.pressed ?
                    MACRO( I(0), T(H), T(E), T(L), T(L), W(255), T(O), END ) :
                    MACRO_NONE );
            break;
        case VOLUP:
            return (event.pressed ?
                    MACRO( D(VOLU), U(VOLU), END ) :
                    MACRO_NONE );
            break;
    }
    return MACRO_NONE;
}


