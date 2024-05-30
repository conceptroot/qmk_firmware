#include QMK_KEYBOARD_H


enum ferris_layers {
//   _COLEMAK_DH,
  _QWERTY,
  _PUNCTUATION,
  _NUM_MEDIA,
  _F_KEYS,
  _NAVIGATION,
  _DEBUG
};

// Добавляю tapping term для отдельных клавиш. Шифты
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(_PUNCTUATION, KC_ENT):
            return 120;
        case LT(_NUM_MEDIA, KC_ESC):
            return 120;
        default:
            return TAPPING_TERM;
    }
}

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
};


// Добавляю кастомные кейкоды для горячих клавиш
enum custom_keycodes {
    GO_RUSSIAN = SAFE_RANGE,
    GO_ENGLISH,
};
// Обрабатываю кастомный кейкоды для горячих клавиш
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case GO_RUSSIAN:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
			register_code(KC_LSFT);
			register_code(KC_LALT);
			register_code(KC_LCTL);
			register_code(KC_MINS);
			unregister_code(KC_LSFT);
			unregister_code(KC_LALT);
			unregister_code(KC_LCTL);
			unregister_code(KC_MINS);
        } else {
            // when keycode QMKBEST is released
        }
        break;
	case GO_ENGLISH:
        if (record->event.pressed) {
			register_code(KC_LSFT);
			register_code(KC_LALT);
			register_code(KC_LCTL);
			register_code(KC_BSLS);
			unregister_code(KC_LSFT);
			unregister_code(KC_LALT);
			unregister_code(KC_LCTL);
			unregister_code(KC_BSLS);
        } else {
            // when keycode QMKBEST is released
        }
        break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_QWERTY] = LAYOUT(
		KC_Q,   			KC_W,    KC_E,    KC_R,    		  KC_T,               KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,
		KC_A,    			KC_S,    KC_D,    KC_F,  		  KC_G,               KC_H,     KC_J,    KC_K,    KC_L,    KC_SCLN,
		KC_Z,      			KC_X,    KC_C,    KC_V,    		  KC_B,               KC_N,     KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
		                             // LT(_NUM_MEDIA, KC_ESC), MEH_T(KC_SPC),	      LT(_NAVIGATION, KC_BSPC),  LT(_PUNCTUATION, KC_ENT)
		                             MO(_NUM_MEDIA), MEH_T(KC_SPC),	      LT(_NAVIGATION, KC_BSPC),  MO(_PUNCTUATION)
  ),

    // правый слой - символы
	[_PUNCTUATION] = LAYOUT(
		KC_EXLM,   KC_AT,   KC_HASH, KC_DLR,  		KC_PERC,             KC_CIRC,   KC_AMPR, KC_ASTR, KC_LCBR, KC_RCBR,
		XXXXXXX,   KC_TILD, KC_MINS, KC_PLUS,  	    KC_LPRN,             KC_RPRN,   KC_LCMD, KC_LALT, KC_RCTL, KC_RSFT,
		KC_GRV,    KC_PIPE, KC_UNDS, KC_EQL, 		KC_LBRC,             KC_RBRC,   KC_QUOT, KC_DQUO, XXXXXXX, KC_BSLS,
		                             MO(_F_KEYS), 	KC_TAB,              KC_TRNS,   KC_TRNS
  ),

    // левый слой - цифры
	[_NUM_MEDIA] = LAYOUT(
		KC_MPRV,   KC_MNXT, KC_VOLD, KC_VOLU, 	KC_MPLY,              XXXXXXX,    KC_7,    KC_8,    KC_9,    XXXXXXX,
		KC_LSFT,   KC_LCTL, KC_LALT, KC_LCMD, 	XXXXXXX,              XXXXXXX,    KC_4,    KC_5,    KC_6,    KC_0,
		XXXXXXX,   KC_DEL,  KC_BSPC, KC_ENT, 	KC_TAB,               XXXXXXX,    KC_1,    KC_2,    KC_3,    KC_PDOT,
		                             KC_TRNS,  	KC_TRNS,              KC_TRNS,    MO(_F_KEYS)
  ),
    // слой ф клавиш
	[_F_KEYS] = LAYOUT(
		KC_F12,   KC_F7, KC_F8, KC_F9, 	KC_TRNS,            			XXXXXXX,   XXXXXXX, XXXXXXX,   XXXXXXX,  XXXXXXX,
		KC_F10,   KC_F4, KC_F5, KC_F6, 	KC_TRNS,            			XXXXXXX,   XXXXXXX, XXXXXXX,   XXXXXXX,  XXXXXXX,
		KC_F11,   KC_F1, KC_F2, KC_F3, 	KC_TRNS,            			XXXXXXX,   XXXXXXX, XXXXXXX,   XXXXXXX,  XXXXXXX,
		                       KC_TRNS, KC_TRNS,            		    XXXXXXX,   XXXXXXX
  ),
    // бэкспейс слой - навигация
	[_NAVIGATION] = LAYOUT(
		XXXXXXX,   	XXXXXXX, XXXXXXX,  XXXXXXX, 	  XXXXXXX,          KC_HOME,   KC_PGDN, KC_PGUP,   KC_END,  XXXXXXX,
		XXXXXXX,   	XXXXXXX, XXXXXXX,  XXXXXXX, 	  XXXXXXX,          KC_LEFT,   KC_DOWN, KC_UP,     KC_RGHT, XXXXXXX,
		MO(_DEBUG), XXXXXXX, XXXXXXX,  XXXXXXX,   	  XXXXXXX,          KC_TRNS,   KC_ACL2, KC_ACL1,   KC_ACL0, KC_BTN1,
		                               TO(_QWERTY),   KC_TRNS,          KC_TRNS,   TO(_QWERTY)
  ),
	[_DEBUG] = LAYOUT(
		QK_REBOOT, QK_DEBUG_TOGGLE, RGB_TOG, RGB_RMOD, RGB_MOD,            XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,
		XXXXXXX,   XXXXXXX,         XXXXXXX, RGB_VAD,  RGB_VAI,            XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,
		KC_TRNS,   XXXXXXX,         XXXXXXX, XXXXXXX,  XXXXXXX,            RGB_M_P,  RGB_M_B, RGB_M_R, RGB_M_SW,  RGB_M_SN,
		                            XXXXXXX, XXXXXXX,  XXXXXXX,            XXXXXXX
  )

};



// combos
enum ferris_combos {
	// Enter
	ENTER,
	ESCAPE,

	// Переключение языка
	MCOMA_QWERTY,
	CV_QWERTY,
	// Нужно доделать переключение языка в слое навигации
	ACL2ACL1ACL0_QWERTY,

	// Контрол ц, котрол в и контрол икс
	QWERTY_COPY,
	QWERTY_PASTE,
	// CUT,

	// Навигация по окнам в макоси
	QWERTY_CTRL_RIGHT,
	QWERTY_CTRL_LEFT,
	QWERTY_CTRL_UP,

	// Переключение в режим навигации. (Мышь + стрелки)
	QWERTY_UI_NAV_LAYER,

	// Переключение в слой без хоум моуд для Игр
	GAME_ON,
	GAME_OFF,

	// Хак для того чтобы не указывать вручную количество комбо настроек
	COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM mcoma_combo[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM cv_combo[] = {KC_C, KC_V, COMBO_END};

// Enter
const uint16_t PROGMEM enter_combo[] = {KC_COMMA, KC_DOT, COMBO_END};
const uint16_t PROGMEM escape_combo[] = {KC_X, KC_C, COMBO_END};

// Переход из навигацион слоя в кврети или колемак
const uint16_t PROGMEM acl2acl1acl0_combo[] = {KC_ACL2, KC_ACL1, COMBO_END};

// Контрол ц, котрол в и контрол икс
const uint16_t PROGMEM qwerty_copy_combo[] = {KC_X, KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM qwerty_paste_combo[] = {KC_Z, KC_C, KC_V, COMBO_END};
//вместо этого будет ESC. const uint16_t PROGMEM cut_combo[] = {KC_X, KC_C, COMBO_END};

// Навигация по окнам в макоси
const uint16_t PROGMEM qwerty_ctrl_right[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM qwerty_ctrl_left[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM qwerty_ctrl_up[] = {KC_W, KC_E, KC_R, COMBO_END};

// Переключение в режим навигации. (Мышь + стрелки)
const uint16_t PROGMEM qwerty_ui_nav_layer[] = {KC_U, KC_I, COMBO_END};

// Переключение в слой без хоум моуд для Игр
const uint16_t PROGMEM game_off[] = {KC_Q, KC_W, KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM game_on[] = {KC_U, KC_I, KC_O, KC_P, COMBO_END};

combo_t key_combos[] = {
	// Enter и Esc
	[ENTER] = COMBO(enter_combo, KC_ENTER),
	[ESCAPE] = COMBO(escape_combo, KC_ESCAPE),


	// Переключение языка
	[MCOMA_QWERTY] = COMBO(mcoma_combo, GO_RUSSIAN),
	[CV_QWERTY] = COMBO(cv_combo, GO_ENGLISH),

	// нужно доделать переход на слой кверти и переключение языка
	[ACL2ACL1ACL0_QWERTY] = COMBO(acl2acl1acl0_combo, TO(_QWERTY)),

	// Контрол ц, котрол в и контрол икс
	[QWERTY_COPY] = COMBO(qwerty_copy_combo, LGUI(KC_C)),
	[QWERTY_PASTE] = COMBO(qwerty_paste_combo, LGUI(KC_V)),
	// [CUT] = COMBO(cut_combo, LGUI(KC_X)),

	// Навигация по окнам в макоси
	[QWERTY_CTRL_RIGHT] = COMBO(qwerty_ctrl_right, LCTL(KC_RGHT)),
	[QWERTY_CTRL_LEFT] = COMBO(qwerty_ctrl_left, LCTL(KC_LEFT)),
	[QWERTY_CTRL_UP] = COMBO(qwerty_ctrl_up, LCTL(KC_UP)),

	// Переключение в режим навигации. (Мышь + стрелки)
	[QWERTY_UI_NAV_LAYER] = COMBO(qwerty_ui_nav_layer, TO(_NAVIGATION)),
		//
};
