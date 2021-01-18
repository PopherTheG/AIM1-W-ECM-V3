#ifndef _SAMSUNG_TEST_H
#define _SAMSUNG_TEST_H
#include <stdint.h>

/**
 * @brief       Runs a test on Samsung air condition IR protocol, that sends
 * IR signals to set the mode to COOL at a LOW fan speed and increments the
 * temperature from 17 to 30.
 */ 
void samsung_test_cool_lowfan();

/**
 * @brief       Runs a test on Samsung air condition IR protocol, that sends
 * IR signals to set the mode to COOL at a MED fan speed and increments the
 * temperature from 17 to 30.
 */ 
void samsung_test_cool_medfan();

/**
 * @brief       Runs a test on Samsung air condition IR protocol, that sends
 * IR signals to set the mode to COOL at a HIGH fan speed and increments the
 * temperature from 17 to 30.
 */ 
void samsung_test_cool_highfan();

/**
 * @brief       Runs a test on Samsung air condition IR protocol, that sends
 * IR signals to set the mode to COOL at a AUTO fan speed and increments the
 * temperature from 17 to 30.
 */ 
void samsung_test_cool_autofan();

/**
 * @brief       Runs a test on Samsung air condition IR protocol, that sends
 * IR signals to set the mode to DRY and increments the temperature from 17 to 30.
 */ 
void samsung_test_dry();

/**
 * @brief       Runs a test on the Samsung air conditioner IR protocol, that sends
 * IR signals to set the mode to FAN and changes the fan speed from LOW, MED, HIGH,
 * to AUTO.
 */ 
void samsung_test_fan();

/**
 * @brief      Runs a test on the Samsung air conditioner IR protocol, that sends 
 * IR signals to set the mode to AUTO and increments the temperature from 17 to 30.
 */ 
void samsung_test_auto();

/**
 * @brief       Runs a test on the Samsung air conditioner IR protocol, that sends
 * IR signals to toggle the air direction. The number of times that it will be toggled 
 * depends on the argument you pass in 'uint32_t times' parameter.
 * 
 * @param times     number of times to toggle air direction.
 */ 
void samsung_test_toggle_air_direction(uint32_t times);

/**
 * @brief       Runs a test on the Samsung air conditioner IR protocol, that sends 
 * IR signals to toggle swing. The number of times that it will be toggles depends
 * on the argument you pass in 'uint32_t times' parameter.
 * 
 * @param times     number of times to toggle swing.
 */ 
void samsung_test_toggle_swing(uint32_t times);
#endif