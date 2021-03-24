#ifndef _IRTRANSMITTER_H
#define _IRTRANSMITTER_H
#include <stdint.h>

/**
 * @brief       Initialization of IR peripheral to drive the IR LED
 */ 
void rmt_tx_init(void);

/*** SAMSUNG START ***/

/**
 * The functions samsung_cool_lowfan, samsung_cool_medfan, 
 * samsung_cool_highfan, samsung_cool_autofan, samsung_dry,
 * samsung_fan_lowfan, samsung_fan_medfan, samsung_fan_highfan,
 * samsung_fan_autofan, and samsung_auto sends the while data 
 * packets for the mode, temperature and the fan speed settings.

 * The functions samsung_toggle_air_direction, samsung_toggle_swing
 * and samsung_toggle_turbo are just modifiers to the current setting.

 * Further explanation on this is found in samsung_ir_codes.h
 */

/**
 * @brief Command for samsung to set the mode to COOL and fan speed to LOW.
 * @param temp Desired temperature
 */  
void samsung_cool_lowfan(uint8_t temp);

/**
 * @brief Command for samsung to set the mode to COOL and fan speed to MED.
 * @param temp Desired temperature.
 */
void samsung_cool_medfan(uint8_t temp);

/**
 * @brief Command for samsung to set the mode to COOL and fan speed to HIGH.
 * @param temp Desired temperature.
 */
void samsung_cool_highfan(uint8_t temp);

/**
 * @brief Command for samsung to set the mode to COOL and fan speed to AUTO.
 * @param temp Desired temperature.
 */
void samsung_cool_autofan(uint8_t temp);

/**
 * @brief Command for samsunt to set the mode to DRY. There is no fan speed 
 * control for DRY mode.
 * @param temp Desired temperature.
 */ 
void samsung_dry(uint8_t temp);

/**
 * @brief Command for samsung to set the mode to FAN with a fan speed of LOW.
 */ 
void samsung_fan_lowfan();

/**
 * @brief Command for samsung to set the mode to FAN with a fan speed of MED.
 */ 
void samsung_fan_medfan();

/**
 * @brief Command for samsung to set the mode to FAN with a fan speed of HIGH.
 */ 
void samsung_fan_highfan();

/**
 * @brief Command for samsung to set the mode to FAN with a fan speed of AUTO.
 */ 
void samsung_fan_autofan();

/**
 * @brief Command for samsung to set the mode to AUTO. There is no fan speed
 * control for AUTO mode.
 * @param temp Desired temperature.
 */ 
void samsung_auto(uint32_t temp);

/**
 * @brief Command for samsung to toggle the air direction. Every toggle of this 
 * moves the fan blades.
 */ 
void samsung_toggle_air_direction();

/**
 * @brief Command for samsung to toggle the fan blades to swing or not to swing.
 */ 
void samsung_toggle_swing();

/**
 * @brief Command for samsung to toggle the turbo mode. This is a modifier to a
 * setting (only works for AUTO and COOL mode) where it tries to achieve the desired
 * temperature at the shortest possible time.
 */ 
void samsung_toggle_turbo();

/**
 * @brief Command for samsung to turn of the air conditioner.
 */ 
void samsung_off();


/*** SAMSUNG END ***/

#endif