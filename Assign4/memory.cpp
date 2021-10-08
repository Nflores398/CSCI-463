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
#include "memory.h"

memory::memory(uint32_t siz)
{
    siz = (siz + 15) & 0xfffffff0;
    //set size of mem vector
    mem.resize(siz);
    //loop to fill the vector with a5
    for (uint i = 0; i <= mem.size(); i++)
    {
        mem[i] = 0xa5;
    }
}
memory::~memory()
{
    //clear vector at end of program
    mem.clear();
}
bool memory::check_illegal(uint32_t i) const
{
    //address out of range
    if (i >= get_size())
    {
        //print when address is out of range
        cout << "WARNING: Address out of range: " << hex::to_hex0x32(i) << endl;
        //return true because the value is illegal
        return true;
    }
    else
    {
        //else address value is in range
        return false;
    }
}
uint32_t memory::get_size() const
{
    //return the size of the memory vector
    return mem.size();
}
uint8_t memory::get8(uint32_t addr) const
{
    //if address is illegal
    if (check_illegal(addr) == true)
    {
        return 0;
    }
    else
    {
        //else return the value at address
        return mem[addr];
    }
}
uint16_t memory::get16(uint32_t addr) const
{
    //return a 16 bit hex value
    return get8(addr) + (get8(addr + 1) << 8);
}
uint32_t memory::get32(uint32_t addr) const
{
    //return a 32 bit hex value
    return get16(addr) + (get16(addr + 2) << 16);
}
int32_t memory::get8_sx(uint32_t addr) const
{
    //get value and store it
    uint32_t temp = get8(addr);
    //check bit 8 to see if its a 1
    if (temp & 0x00000080)
    {
        //then or with temp and return it
        return temp | 0xffffff00;
    }
    else
    {
        //eles return value
        return temp;
    }
}
int32_t memory::get16_sx(uint32_t addr) const
{
    //get value and store it
    uint32_t temp = get16(addr);
    //check bit 16 to see if its a 1
    if (temp & 0x00008000)
    {
        //then or with temp and return it
        return temp | 0xffff0000;
    }
    else
    {
        //eles return value
        return temp;
    }
}
int32_t memory::get32_sx(uint32_t addr) const
{
    //return 32 bit hex value at address
    return get32(addr);
}
void memory::set8(uint32_t addr, uint8_t val)
{
    //check if address is out of range
    if (check_illegal(addr) == true)
    {
        return;
    }
    else
    {
        //else set value at selected address
        mem[addr] = val;
    }
}
void memory::set16(uint32_t addr, uint16_t val)
{
    //set first 8 bits 
    set8(addr, val);
    //set other 8 bits
    set8(addr + 1, (val & 0xff00) >> 8);
    return;
}
void memory::set32(uint32_t addr, uint32_t val)
{
    //set first 16 bits 
    set16(addr, val);
    //set other 16 bits
    set16(addr + 2, (val & 0xffff0000) >> 16);
    return;
}
void memory::dump() const
{
    uint8_t ch;
    //counter for hex dump
    uint32_t counter = 0;
    //counter for memory dump
    uint32_t counter2 = 0;
    //set fill to 0
    cout << setfill('0');
    //while counter is less then the memory
    while (counter < get_size())
    {
        //loop though 16 hex digits
        for (uint32_t i = 0; i <= 15; i++)
        {
            //print row value counter
            if (i == 0 || i % 16 == 0)
            {
                //new line
                if (i == 0 && counter != 0)
                {
                    cout << endl;
                }
                //print starting value of each row
                cout << setw(8) << hex::to_hex32(counter) << ": ";
            }
            //space out every 8 hex digits
            if (i == 8)
            {
                cout << " ";
            }
            //print out value of hex at address
            cout << hex::to_hex8(get8(counter)) << " ";
            //increase count
            counter++;
        }
        //print out the contents of memory
        for (uint32_t j = 0; j <= 15; j++)
        {
            //get value at address
            ch = get8(counter2);
            ch = isprint(ch) ? ch : '.';
            //print at start of content dump
            if (j == 0)
            {
                cout << "*";
            }
            //print value 
            cout << ch;
            //increase counter
            counter2++;
        }
        //print at end of content dump row
        cout << "*";
    }
    //go back to priniting in decimal
    cout << endl;
    //return back
    return;
}
bool memory::load_file(const std::string &fname)
{
    //open file in binary mode
    std::ifstream infile(fname, std::ios::in | std::ios::binary);
    //check if file open failed
    if (infile.bad())
    {
        cerr << "Can’t open file " << fname <<" for reading.\n";
        return false;
    }
    //value being read in
    uint8_t i = 0;
    infile >> std::noskipws;
    //read in values of fil,e
    for (uint32_t addr = 0; infile >> i; ++addr)
    {
        //check if file is too big for the memory
        if (check_illegal(addr))
        {
            cerr << "Program too big.\n";
            //return as fail
            return false;
        }
        //set value at address
        set8(addr, i);
    }
    //clode file
    infile.close();
    //return as success
    return true;
}