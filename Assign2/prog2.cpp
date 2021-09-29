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
#include <iostream>
#include <iomanip>

/**
 * @brief This funcation will take in a hex value and print its floating 
 * point binary equivalent
 *
 * This funcation takes an unsigned int x and will prints outs out the 32bit hex
 * and then in binary. Then the sign, exponenet, significand and finally the full
 * value of the number in binary.
 *
 * @param x An hex IEEE-754 number.
 ********************************************************************************/
void printBinFloat(uint32_t x)
{
    int i = 0; //counting variables
    int j = 0; //counting variables

    int32_t exp = 0; //<stores exponenet
    uint32_t y = 0x80000000;
    uint32_t sig = 0; //<stores significand
    //Set fillspace to 0's
    std::cout << std::setfill('0');
    //Print out x in hex
    std::cout << "0x" << std::setw(8) << std::hex << x << " = ";
    //Loop to print out binary number
    while (i != sizeof(x) * 8) //Stop when all digits of binary are prinited
    {
        //print out the on digit of binary number
        std::cout << (x & y >> i ? '1' : '0');
        //Space add space every 4 digits
        if (j == 3 && i != (sizeof(x) * 8) - 1)
        {
            std::cout << " ";
            j = -1;
        }
        j++;
        i++;
    }
    //print out the sign value
    std::cout << "\nsign: " << (x & y ? '1' : '0') << std::endl;
    //get and store the exponenet
    exp = ((x & 0x7f800000) >> 23) - 127;
    //print out exponenet
    std::cout << " exp: "
              << "0x" << std::hex << std::setw(8) << exp << " (" << std::dec << exp << ")\n";
    //stores significand
    sig = (x & 0x007fffff);
    //print out significand digits
    std::cout << " sig: "
              << "0x" << std::hex << std::setw(8) << sig;
    //If sign value is negative
    if ((x & y ? '1' : '0') == '1')
    {
        //print minus sign at start of line
        std::cout << "\n-";
    }
    else
    {
        //print plus sign start of line
        std::cout << "\n+";
    }
    //if the exponenet is = 128/infinite then print inf
    if (exp == 128)
    {
        std::cout << "inf\n";
        return;
    }
    //if the exponenet is = -128/ then print 0
    if (exp == -127)
    {
        std::cout << "0\n";
        return;
    }
    //reset counter
    i = 0;
    //if exp is less then 0
    if (exp <= 0)
    {
        //Loop until i is no longer less then oppsite of value of exp
        while (i < -(exp))
        {
            //print out 0
            std::cout << "0";
            //i is == 0 then print out a binary point
            if (i == 0)
            {
                std::cout << ".";
            }
            i++;
        }
        //reset counter
        i = 0;
        //print out the starting l of the normalized floating point numbers
        std::cout << "1";
        //if exp is == 0 then print binary point
        if (exp == 0)
        {
            std::cout << ".";
        }
        //while i is less then 23/ lenght of the significands
        while (i < 23)
        {
            //print out the digits of the significands
            std::cout << (x & y >> (9 + i) ? '1' : '0');
            i++;
        }
    }
    else
    {
        //print out the starting l of the normalized floating point numbers
        std::cout << "1";
        //while i is less then 23/ lenght of the significands
        while (i < 23)
        {
            //print out the digits of the significands
            std::cout << (x & y >> (9 + i) ? '1' : '0');
            i++;
        }
        //reset counter
        i = 0;
        //loop while is i less than value of exponents - mantissa
        while (i < exp - 23)
        {
            //print out 0
            std::cout << "0";
            i++;
        }
        //print out binary point and 0
        std::cout << ".0";
    }
    //print out new line
    std::cout << std::endl;
    return;
}
/**
 * @brief Reads values from standard input
 * 
 * Program reads in 32-bit hex values and decodes them
 *
 * @return 0
 ********************************************************************************/

int main()
{
    uint32_t x; //<store 32-bit hex value
    //loop until finish reading file
    while (std::cin >> std::hex >> x)
    {
        //pass x into printBinFloat
        printBinFloat(x);
    }
    return 0;
    //end
}
