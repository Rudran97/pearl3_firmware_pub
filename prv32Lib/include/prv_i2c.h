/**
 * @file    prv_i2c.h
 * @brief   Defines toplevel I2C Master Interface APIs.
 * @version 0.1
 * @date    2023-06-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _PRV_I2C_H_
#define _PRV_I2C_H_

#include "prv_i2c_master.h"

/**
 * @brief API to send 1 byte - Blocking.
 * 
 * @param address Device address
 * @param data    data to send
 */
void i2c_write1Byte(uint8_t address, uint8_t data);

/**
 * @brief API to send N bytes - Blocking
 * 
 * @param address  Device address
 * @param data     Void Pointer to the data that must be sent
 * @param data_len Number of bytes to send
 */
void i2c_writeNBytes(uint8_t address, void* data, size_t data_len);

/**
 * @brief API to receive 1 byte of data from the device
 * 
 * @param address  Device address to read from
 * @param reg      Device register to read from
 * @return uint8_t Read value from Device
 */
uint8_t i2c_read1ByteRegister(uint8_t address, uint8_t reg);

/**
 * @brief API to receive N bytes of data from the device
 * 
 * @param address  Device address to read from
 * @param data     Void Pointer to the buffer to store the incoming data
 * @param data_len Number of bytes to read from device
 */
void i2c_readNBytes(uint8_t address, void* data, size_t data_len);

#endif /* _PRV_I2C_H_ */