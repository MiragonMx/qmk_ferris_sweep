// This file contains the v1 iteration of my ferris sweep layout.
//
// miragonmx, 2022-04-06

#include QMK_KEYBOARD_H
#include "keymap_german.h"

enum eLayers {
    _QWERTZ,
    _SYMBOLS,
    _NAV,
    _NUMBERS
};

enum eTapDances {
    TD_A_AUML   ,
    TD_O_OUML   ,
    TD_U_UUML   ,
    TD_Q_AT     ,
    TD_P_SS     ,
    TD_Y_TAB    ,
    TD_CSSL     ,
    TD_AEX      ,
    TD_ARPR     ,
    TD_GQU      ,
    TD_GLPR     ,
    TD_CTDQ     ,
    TD_CARET    , // ^
    TD_GRAVE    , // `
    TD_ACUTE    , // ´
    TD_LCURL_LT ,
    TD_RCURL_GT
};

typedef enum {
  _TD_NONE,
  _TD_UNKNOWN,
  _TD_SINGLE_TAP,
  _TD_SINGLE_HOLD,
  _TD_DOUBLE_TAP
} td_state_t;

// first layer mod taps
#define DE_SG_S LSG_T(DE_S)
#define DE_SG_L RSG_T(DE_L)
#define DE_ALTD LALT_T(DE_D)
#define DE_ALTK LALT_T(DE_K)
#define DE_GUIF LGUI_T(DE_F)
#define DE_GUIJ RGUI_T(DE_J)
#define DE_SHEN SFT_T(KC_ENT)
#define DE_SH_H SFT_T(DE_H)
#define DE_CTBS CTL_T(KC_BSPC)
// Tap dance macros
#define DE_A_AE TD(TD_A_AUML)
#define DE_O_OE TD(TD_O_OUML)
#define DE_U_UE TD(TD_U_UUML)
#define DE_Q_AT TD(TD_Q_AT)
#define DE_P_SS TD(TD_P_SS)
#define DE_Y_TB TD(TD_Y_TAB)
#define DE_CSSL TD(TD_CSSL)  //RCS_T(DE_SLSH)

// second layer mod taps
// Tap dance macros
#define DE_AEX  TD(TD_AEX)  //LALT_T(DE_EXLM)
#define DE_ARPR TD(TD_ARPR) //LALT_T(DE_RPRN)
#define DE_GQU  TD(TD_GQU)  //LGUI_T(DE_QUES)
#define DE_GLPR TD(TD_GLPR) //RGUI_T(DE_LPRN)
#define DE_CTDQ TD(TD_CTDQ) //CTL_T(DE_DQUO)
#define DE_CAR  TD( TD_CARET )
#define DE_GRAV TD( TD_GRAVE )
#define DE_ACT  TD( TD_ACUTE )
#define DE_LCUR TD( TD_LCURL_LT )
#define DE_RCUR TD( TD_RCURL_GT )

// third layer mod taps
#define KC_GDWN RGUI_T(KC_DOWN)
#define KC_A_UP LALT_T(KC_UP)
#define KC_GUIS LSG(KC_NO)
#define KC_CTRS RCS(KC_NO)

// fourth layer mod taps
#define KC_CTTB CTL_T(KC_TAB)
#define KC_GUIDOT LGUI_T(DE_DOT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTZ] = LAYOUT(
    DE_Q_AT,    DE_W,       DE_E,       DE_R,       DE_T,            DE_Z,     DE_U_UE,  DE_I,    DE_O_OE,   DE_P_SS,
    DE_A_AE,    DE_SG_S,    DE_ALTD,    DE_GUIF,    DE_G,            DE_SH_H,  DE_GUIJ,  DE_ALTK, DE_SG_L,   DE_CSSL,
    DE_Y_TB,    DE_X,       DE_C,       DE_V,       DE_B,            DE_N,     DE_M,     DE_COMM, DE_DOT,    DE_MINS,
                                           DE_CTBS, DE_SHEN,    KC_SPC,    TO(_SYMBOLS)
  ),

  [_SYMBOLS] = LAYOUT(
    KC_ESC,     DE_PIPE,    DE_EURO,    DE_DLR,     DE_PERC,         DE_CAR,   DE_LBRC,  DE_RBRC, DE_ACT,  KC_DEL,
    KC_TAB,     DE_EQL,     DE_AEX,     DE_GQU,     DE_AMPR,         DE_ASTR,  DE_GLPR,  DE_ARPR, DE_QUOT,   DE_CTDQ,
    KC_CAPS,    DE_TILD,    DE_HASH,    DE_BSLS,    DE_DEG,          DE_PLUS,  DE_LCUR,  DE_RCUR, DE_GRAV,   DE_SECT,
                                       TO(_QWERTZ), DE_SHEN,    TO(_NAV), TO(_NUMBERS)
  ),

  [_NAV] = LAYOUT(
    KC_NO,      KC_WH_L,    KC_MS_U,    KC_WH_R,    KC_NO,            KC_MUTE,  KC_VOLD,  KC_VOLU, KC_BRID,  KC_BRIU,
    KC_GUIS,    KC_MS_L,    KC_MS_D,    KC_MS_R,    KC_LCTL,          KC_LEFT,  KC_GDWN,  KC_A_UP, KC_RGHT,  KC_TRNS,
    KC_CTRS,    KC_NO,      KC_WH_U,    KC_WH_D,    KC_NO,            KC_NO,    KC_HOME,  KC_END,  KC_NO,    KC_NO,
                                       TO(_QWERTZ), KC_BTN1,    KC_BTN2,  TO(_SYMBOLS)
  ),

  [_NUMBERS] = LAYOUT(
    DE_1,       DE_2,       DE_3,       DE_4,       DE_5,            DE_6,     DE_7,      DE_8,    DE_9,      DE_0,
    KC_CTTB,    KC_BSPC,    KC_LALT,    KC_GUIDOT,  KC_F11,          KC_F12,   KC_GUIDOT, KC_LALT, KC_DEL,    KC_RCTL,
    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,           KC_F6,    KC_F7,     KC_F8,   KC_F9,     KC_F10,
                                       TO(_QWERTZ), DE_SHEN,    KC_SPC,    TO(_SYMBOLS)
  ),
};


// Create a global instance of the tapdance state type
static td_state_t td_state;

// Declare your tapdance functions:

// Function to determine the current tapdance state
td_state_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
// a/ä
void aae_finished(qk_tap_dance_state_t *state, void *user_data);
void aae_reset(qk_tap_dance_state_t *state, void *user_data);
// o/ö
void ooe_finished(qk_tap_dance_state_t *state, void *user_data);
void ooe_reset(qk_tap_dance_state_t *state, void *user_data);
// u/ü
void uue_finished(qk_tap_dance_state_t *state, void *user_data);
void uue_reset(qk_tap_dance_state_t *state, void *user_data);
// q/@
void qat_finished(qk_tap_dance_state_t *state, void *user_data);
void qat_reset(qk_tap_dance_state_t *state, void *user_data);
// p/ß
void pss_finished(qk_tap_dance_state_t *state, void *user_data);
void pss_reset(qk_tap_dance_state_t *state, void *user_data);
// y/tab
void ytab_finished(qk_tap_dance_state_t *state, void *user_data);
void ytab_reset(qk_tap_dance_state_t *state, void *user_data);
// slash/ctrl+shift
void ctsl_finished(qk_tap_dance_state_t *state, void *user_data);
void ctsl_reset(qk_tap_dance_state_t *state, void *user_data);
// !/alt
void aex_finished(qk_tap_dance_state_t *state, void *user_data);
void aex_reset(qk_tap_dance_state_t *state, void *user_data);
// )/Alt
void arpr_finished(qk_tap_dance_state_t *state, void *user_data);
void arpr_reset(qk_tap_dance_state_t *state, void *user_data);
// ?/GUI
void gqu_finished(qk_tap_dance_state_t *state, void *user_data);
void gqu_reset(qk_tap_dance_state_t *state, void *user_data);
// (/GUI
void glpr_finished(qk_tap_dance_state_t *state, void *user_data);
void glpr_reset(qk_tap_dance_state_t *state, void *user_data);
// "/ctrl
void ctdq_finished(qk_tap_dance_state_t *state, void *user_data);
void ctdq_reset(qk_tap_dance_state_t *state, void *user_data);
// ^(dead)/^
void caret_finished(qk_tap_dance_state_t *state, void *user_data);
void caret_reset(qk_tap_dance_state_t *state, void *user_data);
// `(dead)/`
void grave_finished(qk_tap_dance_state_t *state, void *user_data);
void grave_reset(qk_tap_dance_state_t *state, void *user_data);
// ´(dead)/´
void acute_finished(qk_tap_dance_state_t *state, void *user_data);
void acute_reset(qk_tap_dance_state_t *state, void *user_data);
// {/<
void lcurllt_finished(qk_tap_dance_state_t *state, void *user_data);
void lcurllt_reset(qk_tap_dance_state_t *state, void *user_data);
// }/>
void rcurlgt_finished(qk_tap_dance_state_t *state, void *user_data);
void rcurlgt_reset(qk_tap_dance_state_t *state, void *user_data);


// Determine the tapdance state to return
td_state_t cur_dance(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return _TD_SINGLE_TAP;
    else return _TD_SINGLE_HOLD;
  }
  else if (state->count == 2) {
    return _TD_DOUBLE_TAP;
  }
  else return _TD_UNKNOWN;
}

// Handle the possible states for each tapdance keycode you define:
void aae_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case _TD_SINGLE_TAP:
            register_code(DE_A);
            break;
        case _TD_SINGLE_HOLD:
            register_code(DE_ADIA);
            break;
        case _TD_DOUBLE_TAP:
            tap_code(DE_A);
            register_code(DE_A);
            break;
        default:
            tap_code(DE_A);
            break;
    }
}
void aae_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case _TD_SINGLE_TAP:
            unregister_code(DE_A);
            break;
        case _TD_SINGLE_HOLD:
            unregister_code(DE_ADIA);
            break;
        case _TD_DOUBLE_TAP:
            unregister_code(DE_A);
            break;
        default:
            break;
    }
}

void ooe_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case _TD_SINGLE_TAP:
            register_code(DE_O);
            break;
        case _TD_SINGLE_HOLD:
            register_code(DE_ODIA);
            break;
        case _TD_DOUBLE_TAP:
            tap_code(DE_O);
            register_code(DE_O);
            break;
        default:
            tap_code(DE_O);
            break;
    }
}
void ooe_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case _TD_SINGLE_TAP:
            unregister_code(DE_O);
            break;
        case _TD_SINGLE_HOLD:
            unregister_code(DE_ODIA);
            break;
        case _TD_DOUBLE_TAP:
            unregister_code(DE_O);
            break;
        default:
            break;
    }
}

void uue_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case _TD_SINGLE_TAP:
            register_code(DE_U);
            break;
        case _TD_SINGLE_HOLD:
            register_code(DE_UDIA);
            break;
        case _TD_DOUBLE_TAP:
            tap_code(DE_U);
            register_code(DE_U);
            break;
        default:
            tap_code(DE_U);
            break;
    }
}
void uue_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case _TD_SINGLE_TAP:
            unregister_code(DE_U);
            break;
        case _TD_SINGLE_HOLD:
            unregister_code(DE_UDIA);
            break;
        case _TD_DOUBLE_TAP:
            unregister_code(DE_U);
            break;
        default:
            break;
    }
}

void qat_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case _TD_SINGLE_TAP:
            register_code(DE_Q);
            break;
        case _TD_SINGLE_HOLD:
            register_code16(DE_AT);
            break;
        default:
            break;
    }
}
void qat_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case _TD_SINGLE_TAP:
            unregister_code(DE_Q);
            break;
        case _TD_SINGLE_HOLD:
            unregister_code16(DE_AT);
            break;
        default:
            break;
    }
}

void pss_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case _TD_SINGLE_TAP:
            register_code(DE_P);
            break;
        case _TD_SINGLE_HOLD:
            register_code(DE_SS);
            break;
        case _TD_DOUBLE_TAP:
            tap_code(DE_P);
            register_code(DE_P);
            break;
        default:
            tap_code(DE_P);
            break;
    }
}
void pss_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case _TD_SINGLE_TAP:
            unregister_code(DE_P);
            break;
        case _TD_SINGLE_HOLD:
            unregister_code(DE_SS);
            break;
        case _TD_DOUBLE_TAP:
            unregister_code(DE_P);
            break;
        default:
            break;
    }
}

void ytab_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case _TD_SINGLE_TAP:
            register_code(DE_Y);
            break;
        case _TD_SINGLE_HOLD:
            register_code(KC_TAB);
            break;
        case _TD_DOUBLE_TAP:
            tap_code(DE_Y);
            register_code(DE_Y);
            break;
        default:
            tap_code(DE_Y);
            break;
    }
}
void ytab_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case _TD_SINGLE_TAP:
            unregister_code(DE_Y);
            break;
        case _TD_SINGLE_HOLD:
            unregister_code(KC_TAB);
            break;
        case _TD_DOUBLE_TAP:
            unregister_code(DE_Y);
            break;
        default:
            break;
    }
}

void ctsl_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case _TD_SINGLE_TAP:
            register_code16(DE_SLSH);
            break;
        case _TD_SINGLE_HOLD:
            register_code(KC_RCTL);
            register_code(KC_RSFT);
            break;
        default:
            break;
    }
}
void ctsl_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case _TD_SINGLE_TAP:
            unregister_code16(DE_SLSH);
            break;
        case _TD_SINGLE_HOLD:
            unregister_code(KC_RCTL);
            unregister_code(KC_RSFT);
            break;
        default:
            break;
    }
}

void aex_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case _TD_SINGLE_TAP:
            register_code16(DE_EXLM);
            break;
        case _TD_SINGLE_HOLD:
            register_code(KC_LALT);
            break;
        default:
            break;
    }
}
void aex_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case _TD_SINGLE_TAP:
            unregister_code16(DE_EXLM);
            break;
        case _TD_SINGLE_HOLD:
            unregister_code(KC_LALT);
            break;
        default:
            break;
    }
}

void arpr_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case _TD_SINGLE_TAP:
            register_code16(DE_RPRN);
            break;
        case _TD_SINGLE_HOLD:
            register_code(KC_LALT);
            break;
        default:
            break;
    }
}
void arpr_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case _TD_SINGLE_TAP:
            unregister_code16(DE_RPRN);
            break;
        case _TD_SINGLE_HOLD:
            unregister_code(KC_LALT);
            break;
        default:
            break;
    }
}

void gqu_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case _TD_SINGLE_TAP:
            register_code16(DE_QUES);
            break;
        case _TD_SINGLE_HOLD:
            register_code(KC_LGUI);
            break;
        default:
            break;
    }
}
void gqu_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case _TD_SINGLE_TAP:
            unregister_code16(DE_QUES);
            break;
        case _TD_SINGLE_HOLD:
            unregister_code(KC_LGUI);
            break;
        default:
            break;
    }
}

void glpr_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case _TD_SINGLE_TAP:
            register_code16(DE_LPRN);
            break;
        case _TD_SINGLE_HOLD:
            register_code(KC_RGUI);
            break;
        default:
            break;
    }
}
void glpr_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case _TD_SINGLE_TAP:
            unregister_code16(DE_LPRN);
            break;
        case _TD_SINGLE_HOLD:
            unregister_code(KC_RGUI);
            break;
        default:
            break;
    }
}

void ctdq_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case _TD_SINGLE_TAP:
            register_code16(DE_DQUO);
            break;
        case _TD_SINGLE_HOLD:
            register_code(KC_RCTL);
            break;
        default:
            break;
    }
}
void ctdq_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case _TD_SINGLE_TAP:
            unregister_code16(DE_DQUO);
            break;
        case _TD_SINGLE_HOLD:
            unregister_code(KC_RCTL);
            break;
        default:
            break;
    }
}

void caret_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case _TD_SINGLE_TAP:
            register_code16(DE_CIRC);
            break;
        case _TD_SINGLE_HOLD:
            register_code16(DE_CIRC);
            tap_code(KC_SPC);
            break;
        default:
            break;
    }
}
void caret_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case _TD_SINGLE_TAP:
            unregister_code16(DE_CIRC);
            break;
        case _TD_SINGLE_HOLD:
            unregister_code16(DE_CIRC);
            break;
        default:
            break;
    }
}

void grave_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case _TD_SINGLE_TAP:
            register_code16(DE_GRV);
            break;
        case _TD_SINGLE_HOLD:
            register_code16(DE_GRV);
            tap_code(KC_SPC);
            break;
        default:
            break;
    }
}
void grave_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case _TD_SINGLE_TAP:
            unregister_code16(DE_GRV);
            break;
        case _TD_SINGLE_HOLD:
            unregister_code16(DE_GRV);
            break;
        default:
            break;
    }
}

void acute_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case _TD_SINGLE_TAP:
            register_code(DE_ACUT);
            break;
        case _TD_SINGLE_HOLD:
            register_code(DE_ACUT);
            tap_code(DE_ACUT);
            break;
        default:
            break;
    }
}
void acute_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case _TD_SINGLE_TAP:
            unregister_code(DE_ACUT);
            break;
        case _TD_SINGLE_HOLD:
            unregister_code(DE_ACUT);
            break;
        default:
            break;
    }
}

void lcurllt_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case _TD_SINGLE_TAP:
            register_code16(DE_LCBR);
            break;
        case _TD_SINGLE_HOLD:
            register_code(DE_LABK);
            break;
        default:
            break;
    }
}
void lcurllt_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case _TD_SINGLE_TAP:
            unregister_code16(DE_LCBR);
            break;
        case _TD_SINGLE_HOLD:
            unregister_code(DE_LABK);
            break;
        default:
            break;
    }
}

void rcurlgt_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case _TD_SINGLE_TAP:
            register_code16(DE_RCBR);
            break;
        case _TD_SINGLE_HOLD:
            register_code16(DE_RABK);
            break;
        default:
            break;
    }
}
void rcurlgt_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case _TD_SINGLE_TAP:
            unregister_code16(DE_RCBR);
            break;
        case _TD_SINGLE_HOLD:
            unregister_code16(DE_RABK);
            break;
        default:
            break;
    }
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode,
// passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_A_AUML  ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, aae_finished,      aae_reset),
    [TD_O_OUML  ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ooe_finished,      ooe_reset),
    [TD_U_UUML  ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, uue_finished,      uue_reset),
    [TD_Q_AT    ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, qat_finished,      qat_reset),
    [TD_P_SS    ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pss_finished,      pss_reset),
    [TD_Y_TAB   ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ytab_finished,     ytab_reset),
    [TD_CSSL    ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctsl_finished,     ctsl_reset),
    [TD_AEX     ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, aex_finished,      aex_reset),
    [TD_ARPR    ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, arpr_finished,     arpr_reset),
    [TD_GQU     ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, gqu_finished,      gqu_reset),
    [TD_GLPR    ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, glpr_finished,     glpr_reset),
    [TD_CTDQ    ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctdq_finished,     ctdq_reset),
    [TD_CARET   ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, caret_finished,    caret_reset),
    [TD_GRAVE   ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, grave_finished,    grave_reset),
    [TD_ACUTE   ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, acute_finished,    acute_reset),
    [TD_LCURL_LT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lcurllt_finished,  lcurllt_reset),
    [TD_RCURL_GT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rcurlgt_finished,  rcurlgt_reset)
};

