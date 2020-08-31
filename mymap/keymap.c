//#include "keymap_jp.h"

#include QMK_KEYBOARD_H
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  AJUST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

// common
#define KC_ KC_TRNS
#define KC_XXXX KC_NO
#define KC_RST RESET
#define KC_VU KC__VOLUP
#define KC_VD KC__VOLDOWN
#define KC_A_L LOPT(KC_LEFT)
#define KC_A_R LOPT(KC_RGHT)
#define KC_IME LOPT(KC_GRV) //IME Change
#define KC_WSS LOPT(KC_PSCR) //Window screenshot
#define KC_LANG G(KC_SPC) //Language Change
#define KC_C_L C(KC_LEFT)
#define KC_C_R C(KC_RGHT)

// layer
#define KC_L_1 MO(_RAISE)
#define KC_L_2 MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_kc( \
  //,----+----+----+----+----+----.     ,----+----+----+----+----+----.
     LANG, Q  , W  , E  , R  , T  ,       Y  , U  , I  , O  , P  ,BSPC,
  //|----+----+----+----+----+----|     |----+----+----+----+----+----|
     TAB , A  , S  , D  , F  , G  ,       H  , J  , K  , L  ,SCLN,ENT ,
  //|----+----+----+----+----+----+     |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,       N  , M  ,COMM,DOT ,SLSH,QUOT,
  //`----+----+----+----+----+----/     \----+----+----+----+----+----'
               LGUI,LCTL,LALT,L_1 ,      L_2 ,SPC ,RCTL,RSFT
  //          `----+----+----+----'     `----+----+----+----'
  ),

  /*
   ~ ! @ # $ % ,      ^ & * ( )
       ← ↑ →   ,      { } \ - +
         ↓ end ,
  */
  [1] = LAYOUT_kc( \
  //,----+----+----+----+----+----.     ,----+----+----+----+----+----.
     GRV ,EXLM,AT  ,HASH,DLR ,PERC,      CIRC,AMPR,ASTR,LPRN,RPRN,    ,
  //|----+----+----+----+----+----|     |----+----+----+----+----+----|
         ,C_L ,LEFT,UP  ,RGHT,C_R ,      LCBR,RCBR,JYEN,MINS,PLUS,    ,
  //|----+----+----+----+----+----|     |----+----+----+----+----+----|
         ,HOME,A_L ,DOWN,A_R ,END ,      XXXX,LBRC,RBRC,UNDS,EQL ,    ,
  //`----+----+----+----+----+----/     \----+----+----+----+----+----'
                   ,    ,    ,    ,          ,    ,    ,   
  //          `----+----+----+----'     `----+----+----+----'
  ),

  [2] = LAYOUT_kc( \
  //,----+----+----+----+----+----.     ,----+----+----+----+----+----.
     ESC ,KANA, F1 , F2 , F3 , F4 ,       0  , 1  , 2  , 3  ,MUTE,DEL ,
  //|----+----+----+----+----+----|     |----+----+----+----+----+----|
         ,LANG5,F5 , F6 , F7 , F8 ,      PSCR, 4  , 5  , 6  ,VU  ,SPC ,
  //|----+----+----+----+----+----|     |----+----+----+----+----+----|
         ,IME , F9 ,F10 ,F11 ,F12 ,      WSS , 7  , 8  , 9  ,VD  ,    ,
  //`----+----+----+--+-+----+----/     \----+----+----+----+----+----'
                   ,    ,    ,    ,          ,    ,    ,    
  //          `----+----+----+----'     `----+----+----+----'
  ),

  [3] = LAYOUT_kc( \
  //,----+----+----+----+----+----.     ,----+----+----+----+----+----.
     ESC ,P1  ,P2  ,P3  ,P4  ,P5  ,      P6  ,P7  ,P8  ,P9  ,P0  ,DEL ,
  //|----+----+----+----+----+----|     |----+----+----+----+----+----|
     F1  ,F2  ,F3  ,F4  ,F5  ,F6  ,      F7  ,F8  ,F9  ,F10 ,F11 ,F12 ,
  //|----+----+----+----+----+----|     |----+----+----+----+----+----|
         ,IME ,KANA,LANG5,   ,    ,      PSCR,WSS ,LNUM,    ,    ,    ,
  //`----+----+----+--+-+----+----/     \----+----+----+----+----+----'
                   ,    ,    ,    ,          ,    ,    ,   
  //          `----+----+----+----'     `----+----+----+----'
  ),

};

void matrix_init_user(void) {
  //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
  #ifdef SSD1306OLED
    iota_gfx_init(!has_usb());   // turns on the display
  #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
  iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(0);
      }
      return false;
      break;

    case LOWER:
      if (record->event.pressed) {
        layer_on(1);
      } else {
        layer_off(1);
      }
      return false;
      break;
    
    case RAISE:
      if (record->event.pressed) {
        layer_on(2);
      } else {
        layer_off(2);
      }
      return false;
      break;
    
    case AJUST:
      if (record->event.pressed) {
        layer_on(3);
      } else {
        layer_off(3);
      }
      return false;
      break;  
    }

  return true;
}

