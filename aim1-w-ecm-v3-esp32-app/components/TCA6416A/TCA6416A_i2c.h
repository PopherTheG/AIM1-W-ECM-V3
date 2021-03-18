#ifndef COMPONENTS_TCA6416A_TCA6416A_I2C
#define COMPONENTS_TCA6416A_TCA6416A_I2C

#include <stdint.h>
#define I2C_OPERATION_FAIL -1
#define I2C_OPERATION_SUCCESSFUL 0

int8_t I2C_Write(uint8_t byte_count, uint8_t slave_addr, uint8_t reg_addr, uint8_t *reg_data, uint8_t offset, uint8_t i2c_num);
int8_t I2C_Read(uint8_t byte_count, uint8_t slave_addr, uint8_t reg_addr, uint8_t *reg_data, uint8_t i2c_num);
uint8_t I2C_Read_Byte(uint8_t slave_addr, uint8_t reg_addr, uint8_t i2c_num);

#endif /*COMPONENTS_TCA6416A_TCA6416A_I2C*/