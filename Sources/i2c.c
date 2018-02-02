/*
 * i2c.c
 *
 *  Created on: Dec 4, 2017
 *      Author: Ricod
 */
#include "i2c.h"
#include <stdio.h>
#include "IO_Map.h"
#define SDA PTCD_PTCD0
#define SCL PTCD_PTCD1

void init_i2c(void) {
	PTCDD_PTCDD0 = 1; //je met en sortie la broche PTCD2
	PTCDD_PTCDD1 = 1; //je met en sortie la broche PTCD3
	SDA = 1;
	SCL = 1;
}

void delay(char var) {
	unsigned char i2 = 0;
	for (i2 = 0; i2 < var; i2++)
		;
}

void start_master_i2c(void) {
	SCL = 0;
	delay(0x55);
	SCL = 1;
	SDA = 0;
	delay(0x55);
	SCL = 0;
}

void stop_master_i2c(void) {
	SDA = 0;
	SCL = 0;
	SCL = 1;
	delay(0x55);
	SDA = 1;
}

void ack_from_master_i2c(void) {
	PTCDD_PTCDD0 = 1;
	PTCDD_PTCDD1 = 1;
	SDA=1;
	SCL=1;
	delay(0x55);
	SDA=1;
	SCL=0;

}
void nack_from_master_i2c(void) {
	delay(0x55);
	SCL = 1;
	SDA = 0;
	delay(0x55);
	SCL = 0;
}
void ack_from_slave_i2c(void) {
	delay(0x55);
	SCL = 1;
	SDA = 1;
	delay(0x55);
	SCL = 0;
	PTCDD_PTCDD0 = 0x00;
	while (SDA == 1) {
		delay(0x55);
		SCL = 1;
		delay(0x55);
		SCL = 0;
	}
	PTCDD_PTCDD0 = 1;
}
void read_byte_i2c(unsigned char *octet) {
	unsigned char i, var;
	for (i = 0; i <= 7; i++) {
		var = *octet << (7 - i);
		var = var & 0x1;
		SDA = var;
		delay(0x55);
	}
}
void send_byte_i2c(unsigned char *octet) {
	unsigned char i, var;
	for (i = 0; i <= 7; i++) {
		delay(0x55);
		SCL = 1;
		if (i < 6) {
			var = 0;
		} else if (i == 6) {
			var = 1;
		} else if (i == 7) {
			var = 0;
		}
		SDA = var;
		delay(0x55);
		SCL = 0;
	}
	ack_from_master_i2c();
	ack_from_slave_i2c();
	for (i = 0; i <= 7; i++) {
		delay(0x55);
		SCL = 1;
		var = *octet;
		var = var >> (7 - i);
		var = var & (0x1);
		SDA = var;
		delay(0x55);
		SCL = 0;
	}
}
