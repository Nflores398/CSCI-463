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
#include "registerfile.h"

registerfile::registerfile()
{
    //set register 32 size
    registers.resize(32);
    //reset regs
    reset();
}

void registerfile::reset()
{
    //clear regs
    registers.clear();
    //loop and fill regs
    for (int i = 0; i <= 31; i++)
    {
        //reg 0 is always 0
        if (i == 0)
        {
            registers[i] = 0x0;
        }
        else
        {
            registers[i] = 0xf0f0f0f0;
        }
    }
}
void registerfile::dump(const std::string &hdr) const
{
    int counter = 0;
    //set fill
    cout << setfill('0');
    //loop for the size of regiser vector
    for (int i = 0; i <= 31; i++)
    {
        //print headers
        if (i % 8 == 0 || i == 0)
        {
            if(hdr == "HEADER-")
            {
                cout << setw(8) << hdr << " ";
            }
            //regs greater than 10
            if(i >= 10)
            {
                cout << std::dec;
                cout << "x" << setw(2) << i << " ";
            }
            //less than 10
            else
            {
                cout << std::dec;
                cout << " " <<std::setfill('x') << right << setw(2) << i << " ";
            }
            
            cout << setfill('0');
        }
        //space every for 4 regs
        if (counter == 4)
        {
            cout << " ";
        }
        //print regs
        cout << std::hex << setw(8) << registers[i];
        //space if not 7
        if (counter != 7)
        {
            cout << " ";
            counter++;
        }
        //else new line
        else
        {
            cout << endl;
            //reset counter
            counter = 0;
        }
    }
    //return to dec
    cout << std::dec;

}
int32_t registerfile::get(uint32_t r) const
{
    //return value of r
    return registers[r];
}
void registerfile::set(uint32_t r, int32_t val)
{
    //set value if to reg if its not reg 0
    if(r != 0)
        registers[r] = val;
    
}