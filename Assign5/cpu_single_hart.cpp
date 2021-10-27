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
#include "cpu_single_hart.h"

void cpu_single_hart::run(uint64_t exec_limit)
{
    //set fill
    cout << std::setfill('0');
    //set size of mem to reg 2
    regs.set(2, mem.get_size());
    //loop until halt
    while (exec_limit == 0)
    {
        //tick
        tick("");
        //if halted
        if (is_halted() == true)
        {
            //show reason for halt
            cout << "Execution terminated. Reason: " << get_halt_reason() << endl;
            //print insn counter
            cout << get_insn_counter() << " instructions executed\n";
            return;
        }
    }
    while (exec_limit != 0)
    {
        //tick
        tick("");
        //if program is halted OR exec limit is met
        if (get_insn_counter() == exec_limit || is_halted() == true)
        {
            //if halted 
            if (is_halted() == true)
            {
                //print reason
                cout << "Execution terminated. Reason: " << get_halt_reason() << endl;
            }
            //print insn counter
            cout << get_insn_counter() << " instructions executed\n";
            return;
        }
    }
}