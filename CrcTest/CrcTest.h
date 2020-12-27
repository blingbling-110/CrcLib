#pragma once

#include<iostream>
#include<iomanip>

#define WIDTH 16
#define POLY 0x1021     
#define INIT 0xffff     
#define REFIN false
#define REFOUT false
#define XOROUT 0x0000     

#ifdef WIDTH
#if WIDTH <= 8
typedef unsigned char crcType;
#elif WIDTH > 8 && WIDTH <= 16
typedef unsigned short crcType;
#elif WIDTH > 16 && WIDTH <= 32
typedef unsigned int crcType;
#elif WIDTH > 32 && WIDTH <= 64
typedef unsigned long long crcType;
#endif // WIDTH <= 8
#endif // WIDTH

void testCalculateCrc();
void testCalculateCrcTable();