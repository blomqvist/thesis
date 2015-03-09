/**
 * signals.h
 * Keeps a list of available signals and numbers them
 * */
 
#ifndef SIGNALS_H_
#define SIGNALS_H_


/**
 * We end each name with datatype so we know how to handle
 */
typedef enum {
    CURRENT_SPEED = 0, // Just set first index to zero, so we're sure.
    HAL_IS_BELLY_BUTTON_ACTIVATED_BOOL,
    HAL_GET_LED_BLINK_TIMER,
    HAL_GET_HORN,
    HAL_GET_HORN_POS_FLANK,
    HAL_GET_LIFT_LOWER_BUTTON,
    HAL_GET_OPTION_BUTTON,
    HAL_GET_KEYBOARD,
    HAL_GET_POS_FLANK_KEYBOARD,
    HAL_GET_ANALOG_VALUE,
    HAL_GET_ANALOG_VOLT,
    HAL_GET_GET_BFLY_POSITION,
    HAL_IS_BFLY_ZERO,
    HAL_IS_BFLY_AFFECTED,
    HAL_IS_BFLY_STEP_UP,
    HAL_IS_BFLY_STEP_DN,
    
    
    SIGNALS_COUNT // Make sure this is last
} SIGNALS;



 #endif // SIGNALS_H