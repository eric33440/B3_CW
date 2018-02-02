/*
 * i2c.h
 *
 *  Created on: Dec 4, 2017
 *      Author: Ricod
 */

#ifndef I2C_H_
#define I2C_H_
void init_i2c(void);
void start_master_i2c(void);
void stop_master_i2c(void);
void ack_from_master_i2c(void);
void nack_from_master_i2c(void);
void ack_from_slave_i2c(void);
void read_byte_i2c(unsigned char *octet);

void send_byte_i2c(unsigned char *octet);

#endif /* I2C_H_ */
