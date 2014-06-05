/*
 * Copyright (c) 2013 by Felix Rusu <felix@lowpowerlab.com>
 * Library for facilitating wireless programming using an WildFire_RFM69 transceiver (get library at: https://github.com/LowPowerLab/WildFire_RFM69)
 * and the SPI Flash memory library for arduino/moteino (get library at: http://github.com/LowPowerLab/WildFire_SPIFlash)
 * DEPENDS ON the two libraries mentioned above
 * Install all three of these libraries in your Arduino/libraries folder ([Arduino > Preferences] for location of Arduino folder)
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#ifndef _WILDFIRE_WirelessHEX69_H_
#define _WILDFIRE_WirelessHEX69_H_
#define LED 9 //LED by default on digital pin 9
#define SHIFTCHANNEL //shift frequency of HEX transmission to keep original channel free of the intense traffic

#ifndef DEFAULT_TIMEOUT
  #define DEFAULT_TIMEOUT 3000
#endif

#ifndef ACK_TIMEOUT
  #define ACK_TIMEOUT 20
#endif

#include <WildFire_RFM69.h>
#include <WildFire_SPIFlash.h>

//functions used in the REMOTE node
void CheckForWirelessHEX(WildFire_RFM69 radio, WildFire_SPIFlash flash, boolean DEBUG=false, byte LEDpin=LED);
void resetUsingWatchdog(boolean DEBUG=false);

boolean HandleWirelessHEXData(WildFire_RFM69 radio, byte remoteID, WildFire_SPIFlash flash, boolean DEBUG=false, byte LEDpin=LED);
#ifdef SHIFTCHANNEL
boolean HandleWirelessHEXDataWrapper(WildFire_RFM69 radio, byte remoteID, WildFire_SPIFlash flash, boolean DEBUG=false, byte LEDpin=LED);
#endif

//functions used in the MAIN node
boolean CheckForSerialHEX(byte* input, byte inputLen, WildFire_RFM69 radio, byte targetID, uint16_t TIMEOUT=DEFAULT_TIMEOUT, uint16_t ACKTIMEOUT=ACK_TIMEOUT, boolean DEBUG=false);
boolean HandleSerialHandshake(WildFire_RFM69 radio, byte targetID, boolean isEOF, uint16_t TIMEOUT=DEFAULT_TIMEOUT, uint16_t ACKTIMEOUT=ACK_TIMEOUT, boolean DEBUG=false);
boolean HandleSerialHEXData(WildFire_RFM69 radio, byte targetID, uint16_t TIMEOUT=DEFAULT_TIMEOUT, uint16_t ACKTIMEOUT=ACK_TIMEOUT, boolean DEBUG=false);
#ifdef SHIFTCHANNEL
boolean HandleSerialHEXDataWrapper(WildFire_RFM69 radio, byte targetID, uint16_t TIMEOUT=DEFAULT_TIMEOUT, uint16_t ACKTIMEOUT=ACK_TIMEOUT, boolean DEBUG=false);
#endif
boolean waitForAck(WildFire_RFM69 radio, uint8_t fromNodeID, uint16_t ACKTIMEOUT=ACK_TIMEOUT);

byte validateHEXData(void* data, byte length);
byte prepareSendBuffer(char* hexdata, byte*buf, byte length, uint16_t seq);
boolean sendHEXPacket(WildFire_RFM69 radio, byte remoteID, byte* sendBuf, byte hexDataLen, uint16_t seq, uint16_t TIMEOUT=DEFAULT_TIMEOUT, uint16_t ACKTIMEOUT=ACK_TIMEOUT, boolean DEBUG=false);
byte BYTEfromHEX(char MSB, char LSB);
byte readSerialLine(char* input, char endOfLineChar=10, byte maxLength=64, uint16_t timeout=1000);
void PrintHex83(byte* data, byte length);

#endif
