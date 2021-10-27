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
#include "rv32i_hart.h"
/**
 * A single hart that executes instructions
 ********************************************************************************/
class cpu_single_hart : public rv32i_hart
{
public:
    /**
     * @brief the constructor of the single hart
     *
     *	 the constructor of the single hart
     *
     * @param mem memory of the program being passed
     * 
     ********************************************************************************/
    cpu_single_hart(memory &mem) : rv32i_hart(mem) {}
    /**
     * @brief run an instructions
     *
     *	 run an instructions 
     *
     * @param exec_limit sets the limit of instructions to run. set to zero by default
     * 
     ********************************************************************************/
    void run(uint64_t exec_limit);
};