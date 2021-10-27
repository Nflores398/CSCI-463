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
/**
* Simulated memory that stores values into it and can retrieve these values
********************************************************************************/
class memory : public hex
{
public:

/**
* @brief Constructor that sets simulated memory vector and fills it
* 
*	Constructor that sets simulated memory vector and fills it with a default 
*  value of a5
* 
* @param s the size that the vector will be set to.
*
********************************************************************************/
    memory(uint32_t s);
/**
* @brief destructor that clears out simulated memory vector
* 
*	Destructor that clears out simulated memory vector at the end of the program
*
********************************************************************************/
    ~memory();
/**
* @brief Checks if address is out of range for the memory vector
* 
* Dump the contents of the simulated memory which is a vector named mem
*
* @param addr the address of the first simulated memory address 
*
* @return a true if the addr is out of range and false if in range
*
********************************************************************************/
    bool check_illegal(uint32_t addr) const;
/**
* @brief Gets the size of the simulated memory vector
* 
*	Gets the size of the simulated memory vector and returns it
*
* @return the size of the simulated memory vector
*
********************************************************************************/
    uint32_t get_size() const;
/**
* @defgroup getX get little-endian value
*
* Read and return little-endian value from memory
*
* @param addr the address of the first simulated memory address 
* 
* @return a little-endian value from simulated memory starting at address
* 
*@{
********************************************************************************/
    uint8_t get8(uint32_t addr) const;      ///< Get an 8-bit value from memory
    uint16_t get16(uint32_t addr) const;    ///< Get a 16-bit value from memory
    uint32_t get32(uint32_t addr) const;    ///< Get a 32-bit value from memory
/**@}*/

/**
* @defgroup getx get little-endian value with sigh extension
* 
* Read and return little-endian value from memory with sigh extension
*
* @param addr the address of the first simulated memory address 
* 
* @return  a little-endian value from simulated memory starting at address
* 
*@{
********************************************************************************/
    int32_t get8_sx(uint32_t addr) const;   ///< Get an 8-bit value from memory with sigh extension
    int32_t get16_sx(uint32_t addr) const;  ///< Get an 16-bit value from memory with sigh extension
    int32_t get32_sx(uint32_t addr) const;  ///< Get an 32-bit value from memory with sigh extension
/**@}*/

/**
* @defgroup setx set a value into memory at an address
* 
* Set value at an address in the simulated memory
*
* @param addr the address of the first simulated memory address 
*
* @param val the value that is to be set at an address in memory
* 
*@{
********************************************************************************/
    void set8(uint32_t addr, uint8_t val);      ///< Set 8-bits into memory
    void set16(uint32_t addr, uint16_t val);    ///< Set 16-bits into memory
    void set32(uint32_t addr, uint32_t val);    ///< Set 32-bits into memory
/**@}*/

/**
 * @brief Dump the contents of the simulated memory
 * 
 *	Dump the contents of the simulated memory which is a vector named mem
 *
 ********************************************************************************/
    void dump() const;
/**
 * @brief Dump the contents of the simulated memory
 * 
 *	Dump the contents of the simulated memory which is a vector named mem
 *
 * @param fname a string which the name of the file that is being passed in
 * 
 * @return a false if fails and true if opening/reading was a success
 *
 ********************************************************************************/
    bool load_file(const std ::string &fname);

private:
    std ::vector<uint8_t> mem;  //simulated memory vector
};