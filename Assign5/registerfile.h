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

class registerfile
{
public:
    /**
     * @brief Constructor of registerfile
     *
     *	 Constructor of registerfile
     ********************************************************************************/
    registerfile();
    /**
     * @brief reset and set the register to default values
     *
     *	 reset and set the register to default values
     ********************************************************************************/
    void reset();
    /**
     * @brief set a value in a selected register
     *
     *	 set a value in a selected register
     *
     * @param r the selected register
     * 
     * @param val the value to set the register 
     ********************************************************************************/
    void set(uint32_t r, int32_t val);
    /**
     * @brief get a value from a selected register and return it
     *
     *	 get a value from a selected register and return it
     *
     * @param r the selected register
     * 
     * @return the value of the register
     ********************************************************************************/
    int32_t get(uint32_t r) const;
    /**
     * @brief dump the values of all registers 
     *
     *	 dump the values of all registers 
     *
     * @param hdr the header for the registers being dumped  
     * 
     ********************************************************************************/
    void dump(const std::string &hdr) const;

private:
    std::vector<int32_t> registers; //vector that holds all the values of the registers
};