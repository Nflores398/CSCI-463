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
#include "hex.h"

string hex::to_hex8(uint8_t i)
{
    std::ostringstream os;
    //Converts i into a hex 8
    os << std::hex << std::setfill('0') << std::setw(2) << static_cast<uint16_t>(i);
    //return as a string
    return os.str();
}
string hex::to_hex32(uint32_t i)
{
    std::ostringstream os;
    //convert into a hex 32
    os << std::hex << std::setfill('0') << std::setw(8) << i;
    //return as a string
    return os.str();
}
string hex::to_hex0x32(uint32_t i)
{
    //add 0x and get convert value to hex 32
    return std::string("0x") + to_hex32(i);
}