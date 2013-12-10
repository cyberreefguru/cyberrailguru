/*
 * LedShieldDriver.cpp
 *
 *  Created on: Dec 8, 2013
 *      Author: tsasala
 */

#include "LedShieldDriver.h"

Tlc5947Driver lsd = Tlc5947Driver();
HighSideDriver hsd = HighSideDriver();

/**
 * Constructor
 */
LedShieldDriver::LedShieldDriver()
{
//	buf1 = 0;
//	buf2 = 0;
	rows = 0;
	cols = 0;
//	frameBuf = 0;
//	driveBuf = 0;
	frameIndex = 0;
	driveIndex = 1;

}

/**
 * Initializes the shield driver
 *
 * NOTE: Must call initialize, initializeHighSideDriver, and initializeLowSideDriver
 *       for this class to work properly
 */
boolean LedShieldDriver::initialize(uint8_t r, uint8_t c)
{
	boolean b = false;
	rows = r;
	cols = c;

//	// Allocate buffer to hold intensity values if buf is null
//	if( !buf1)
//	{
//#ifdef __DEBUG
//	Serial.print("Allocating buf1 columns: ");
//	Serial.print( r );
//	Serial.print("x");
//	Serial.println( c );
//#endif
//		**buf1 = (unsigned int)calloc(c, sizeof(unsigned int*));
//		if (!buf1)
//		{
//#ifdef __DEBUG
//		Serial.print("ERROR-1: buf1 allocation failed: ");
//		Serial.print( c );
//		Serial.print(" - ");
//		Serial.println( sizeof(unsigned int*) );
//#endif
//			return false;
//		}
//
//#ifdef __DEBUG
//		Serial.println("Allocating buf1 rows");
//#endif
//
//		for(uint8_t i = 0; i < r; i++)
//		{
//			buf1[i] = (uint16_t *)calloc(r, sizeof(uint16_t));
//			if( !buf1[i] )
//			{
//#ifdef __DEBUG
//		Serial.print("ERROR-1: buf1 row allocation failed: ");
//		Serial.print( i );
//		Serial.print(" - ");
//		Serial.print( r );
//		Serial.print(" - ");
//		Serial.println( sizeof(unsigned int) );
//#endif
//				return false;
//			}
//		} // end for
//	}
//	else
//	{
//#ifdef __DEBUG
//		Serial.println("buf1 allocated already");
//#endif
//	}
//
//#ifdef __DEBUG
//	Serial.println("buf1 successfully allocated");
//#endif
//
//
//	// Allocate buffer to hold intensity values if buf is null
//	if( !buf2)
//	{
//#ifdef __DEBUG
//	Serial.print("Allocating buf2 columns: ");
//	Serial.print( r );
//	Serial.print("x");
//	Serial.println( c );
//#endif
//		**buf2 = (unsigned int)calloc(c, sizeof(unsigned int*));
//		if (!buf2)
//		{
//#ifdef __DEBUG
//		Serial.print("ERROR-1: buf2 allocation failed: ");
//		Serial.print( c );
//		Serial.print(" - ");
//		Serial.println( sizeof(unsigned int*) );
//#endif
//			return false;
//		}
//
//#ifdef __DEBUG
//		Serial.println("Allocating buf2 rows");
//#endif
//
//		for(uint8_t i = 0; i < r; i++)
//		{
//			buf2[i] = (uint16_t *)calloc(r, sizeof(uint16_t));
//			if( !buf2[i] )
//			{
//#ifdef __DEBUG
//		Serial.print("ERROR-1: buf2 row allocation failed: ");
//		Serial.print( i );
//		Serial.print(" - ");
//		Serial.print( r );
//		Serial.print(" - ");
//		Serial.println( sizeof(unsigned int) );
//#endif
//				return false;
//			}
//		} // end for
//	}
//	else
//	{
//#ifdef __DEBUG
//		Serial.println("buf2 allocated already");
//#endif
//	}
//
//#ifdef __DEBUG
//	Serial.println("buf2 successfully allocated");
//#endif

//	frameBuf = (uint16_t **)&buf1;
//	driveBuf = (uint16_t **)&buf2;
//
//	Serial.print("buf1=");
//	Serial.print((uint32_t)&buf1, HEX);
//	Serial.print(" ");
//	Serial.print("buf2=");
//	Serial.print((uint32_t)&buf2, HEX);
//	Serial.print(" ");
//	Serial.print("fb=");
//	Serial.print((uint32_t)frameBuf, HEX);
//	Serial.print(" ");
//	Serial.print("db=");
//	Serial.println((uint32_t)driveBuf, HEX);
//
//	Serial.print("buf1=");
//	Serial.print((uint32_t)&buf1[0][0], HEX);
//	Serial.print(" ");
//	Serial.print("buf2=");
//	Serial.print((uint32_t)&buf2[0][0], HEX);
//	Serial.print(" ");
//	Serial.print("fb=");
//	Serial.print((uint32_t)&(frameBuf[0][0]), HEX);
//	Serial.print(" ");
//	Serial.print("db=");
//	Serial.println((uint32_t)&(driveBuf[0][0]), HEX);

	return true;
}

/**
 * Initializes the high side driver
 *
 * NOTE: Must call initialize, initializeHighSideDriver, and initializeLowSideDriver
 *       for this class to work properly
 */
boolean LedShieldDriver::initializeHighSideDriver(uint8_t num, uint8_t clk,
		uint8_t data, uint8_t lat, uint8_t clr, uint8_t oe)
{
	boolean b = hsd.initialize( num, clk, data, lat, clr, oe);

	// TODO: where should turning on column drivers be done? ISR?
	if(b)
	{
#ifdef __DEBUG
	Serial.println("Enabling columns");
#endif
	hsd.setValue(0, 0x1f); // turn on all columns
	hsd.write();
	}
	return b;
}

/**
 * Initializes the low side driver
 *
 * NOTE: Must call initialize, initializeHighSideDriver, and initializeLowSideDriver
 *       for this class to work properly
 */
boolean LedShieldDriver::initializeLowSideDriver(uint8_t num, uint8_t clk,
		uint8_t data, uint8_t lat, uint8_t clr, uint8_t oe)
{
	boolean b = lsd.initialize( num, clk, data, lat, clr, oe);

	// TODO where should turning on row drivers be done? ISR?
	if(b)
	{

#ifdef __DEBUG
	Serial.println("Clearing TLC");
#endif
	lsd.setBlank(false);
	lsd.clear();
	}
	return b;
}

/**
 * Returns the frame buffer for direct manipulation
 *
 */
uint16_t** LedShieldDriver::getBuffer()
{
	return 0;
//	return frameBuf;
}

/**
 * Writes the frame buffer to the drivers
 *
 */
void LedShieldDriver::write()
{
	// update low side buffer
//	noInterrupts();
//	if( driveBuf == (uint16_t **)&buf1 )
//	{
//		driveBuf = (uint16_t **)&buf2;
//		frameBuf = (uint16_t **)&buf1;
//	}
//	else
//	{
//		driveBuf = (uint16_t **)&buf1;
//		frameBuf = (uint16_t **)&buf2;
//	}

	frameIndex = frameIndex%2;
	driveIndex = driveIndex%2;

//	interrupts();


//	Serial.print("buf1=");
//	Serial.print((uint32_t)&buf1, HEX);
//	Serial.print(" ");
//	Serial.print("buf2=");
//	Serial.print((uint32_t)&buf2, HEX);
//	Serial.print(" ");
//	Serial.print("fb=");
//	Serial.print((uint32_t)frameBuf, HEX);
//	Serial.print(" ");
//	Serial.print("db=");
//	Serial.println((uint32_t)driveBuf, HEX);


	// TEMP: simulate output as built
	for(uint8_t i = 0; i< cols; i++)
	{
		lsd.setIntensity(i, buffer[driveIndex][i][i]);
	}
	lsd.write();

}

/**
 * Clears all drivers
 *
 * true = clear; disables high and low side drives
 * false = unclear; return last pattern driven
 *
 * NOTE: this function does NOT change the underlying data buffers
 */
void LedShieldDriver::clear(boolean b)
{
	if( b )
	{
		hsd.setOutputEnable(false);
		lsd.setBlank(true);
	}
	else
	{
		hsd.setOutputEnable(true);
		lsd.setBlank(false);
	}
}

/**
 * Clears the values driven
 *
 * NOTE: This function clears all underlying data buffers
 */
void LedShieldDriver::clearAll()
{
	lsd.clear();
	hsd.clear();
}

/**
 * Sets the specified value
 *
 * NOTE: this routine does NOT check the row/col values; don't do anything stupid
 */
void LedShieldDriver::setValue(uint8_t row, uint8_t col, uint16_t value)
{
	buffer[frameIndex][row][col] = value;

//#ifdef __DEBUG
//	Serial.print("v(");
//	Serial.print( row );
//	Serial.print( ",");
//	Serial.print( col);
//	Serial.print(")=");
//	Serial.println( buffer[frameIndex][row][col]);
//#endif
}

/**
 * Returns the specified value.
 *
 * NOTE: this routine does NOT check the row/col values; don't do anything stupid
 */
uint16_t LedShieldDriver::getValue(uint8_t row, uint8_t col)
{
	return buffer[frameIndex][row][col];
}

/**
 * Sets the entire row to the value.
 *
 * NOTE: this routine does NOT check the row value; don't do anything stupid
 */
void LedShieldDriver::setRow(uint8_t row, uint16_t value)
{
	for(uint8_t i=0; i<cols; i++)
	{
		buffer[frameIndex][row][i] = value;
	}
}

/**
 * Sets the entire column to the value.
 *
 * NOTE: this routine does NOT check the col value; don't do anything stupid
 */
void LedShieldDriver::setColumn(uint8_t col, uint16_t value)
{
	for(uint8_t i=0; i<rows; i++)
	{
		buffer[frameIndex][i][col] = value;
	}
}

Tlc5947Driver LedShieldDriver::getLowSideDriver()
{
	return lsd;
}

HighSideDriver LedShieldDriver::getHighSideDriver()
{
	return hsd;
}
