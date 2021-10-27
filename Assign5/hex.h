//***************************************************************************
//
//  Noah Flores
//  z1861588
//  CSCI-463-1
//
//  I certify that this is my own work and where appropriate an extension
//  of the starter code provided for the assignment.
//
//***************************************************************************
#ifndef HEX_H
#define HEX_H
#include <iostream>
#include <string>
#include <unistd.h>
#include <sstream>
#include <iomanip>
#include <vector>
#include "ctype.h"
#include <fstream>
#include <assert.h>
using namespace std;
/**
* Convert values into different forms of hex
********************************************************************************/
class hex
{
public:
/**
* @defgroup convert to different forms of hex
* 
* Converts uint_t to hex to a 2,3,5,8 digit hex value.
*
* @param i a value that is converted to a 2,3,5,8 digit hex
* 
* @return a string with exactly 2,3,5,8 hex digits representing the 8 or 32 bits.
* 
*@{
********************************************************************************/
    static string to_hex8(uint8_t i);     ///< Convert to 8-bit/ 2 digit hex value
    static string to_hex32(uint32_t i);   ///< Convert to 32-bit/ 8 digit hex value
    static string to_hex0x32(uint32_t i); ///< Convert to 0x 8 digit hex value
    static string to_hex0x20(uint32_t i); ///< Convert to 0x 5 digit hex value
    static string to_hex0x12(uint32_t i); ///< Convert to 0x 3 digit hex value
/**@}*/

};

#endif