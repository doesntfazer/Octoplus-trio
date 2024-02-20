#include QMK_KEYBOARD_H
#include "pointing_device.h"

// Required includes
#include "artsey.h"
#include "keymap_combo.h"
#include "artsey.c"
#include "timer.h" // Include timer support



// Global timer variable for mouse activity tracking
static uint16_t mouse_timer;
static bool mouse_active_previously = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_A_BASE] = LAYOUT(
        A_BASE_S,A_BASE_T,A_BASE_R,A_BASE_A,
        A_BASE_O,A_BASE_I,A_BASE_Y,A_BASE_E,
        KC_LSHIFT, KC_BSPC, KC_SPACE
    ),

    [_A_NUM] = LAYOUT(
        A_NUM_S,A_NUM_T,A_NUM_R,A_NUM_A,
        A_NUM_O,A_NUM_I,A_NUM_Y,A_NUM_E,
        KC_LSHIFT, KC_BSPC, KC_SPACE
    ),

    [_A_NAV] = LAYOUT(
        A_NAV_S,A_NAV_T,A_NAV_R,A_NAV_A,
        A_NAV_O,A_NAV_I,A_NAV_Y,A_NAV_E,
        KC_LSHIFT, KC_BSPC, KC_SPACE
    ),

    [_A_SYM] = LAYOUT(
        A_SYM_S,A_SYM_T,A_SYM_R,A_SYM_A,
        A_SYM_O,A_SYM_I,A_SYM_Y,A_SYM_E,
        KC_LSHIFT, KC_BSPC, KC_SPACE
    ),

    [_A_BRAC] = LAYOUT(
        A_BRAC_S,A_BRAC_T,A_BRAC_R,A_BRAC_A,
        A_BRAC_O,A_BRAC_I,A_BRAC_Y,A_BRAC_E,
        KC_LSHIFT, KC_BSPC, KC_SPACE
    ),

    [_A_MOU] = LAYOUT(
        A_MOU_S,A_MOU_T,A_MOU_R,A_MOU_A,
        A_MOU_O,A_MOU_I,A_MOU_Y,A_MOU_E,
        KC_LSHIFT, KC_MS_BTN2, KC_MS_BTN1
    ),

    [_A_CUSTOM] = LAYOUT(
        A_CUSTOM_S,A_CUSTOM_T,A_CUSTOM_R,A_CUSTOM_A,
        A_CUSTOM_O,A_CUSTOM_I,A_CUSTOM_Y,A_CUSTOM_E,
        KC_LSHIFT, KC_BSPC, KC_SPACE
    ),
};

void keyboard_post_init_user(void) {
    // Initialize mouse timer
    mouse_timer = timer_read();
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // Check if the mouse is moving or any button is pressed
    if (mouse_report.x != 0 || mouse_report.y != 0 || mouse_report.buttons) {
        if (!mouse_active_previously) {
            // Mouse just became active, switch to layer 5 (_A_MOU)
            layer_on(_A_MOU);
            mouse_active_previously = true;
        }
        // Reset the timer on any mouse activity
        mouse_timer = timer_read();
    } else if (mouse_active_previously && timer_elapsed(mouse_timer) > 4000) {
        // No mouse activity for 4 seconds, switch back
        layer_off(_A_MOU);
        mouse_active_previously = false;
    }

    // Always return the mouse report
    return mouse_report;
}
