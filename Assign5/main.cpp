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

/**
 * @brief Explains how to run the program properly
 *
 *	Tells user how to properly run the program from the command line and then
 *	exits
 *
 ********************************************************************************/
static void usage()
{
	cerr << "Usage:  rv32i [-d] [-i] [-r] [-z] [-l exec-limit] [-m hex-mem-size] infile" << endl;
	cerr << "    -d show disassembly before program execution" << endl;
	cerr << "    -i show instruction printing during execution" << endl;
	cerr << "    -l maximum number of instructions to exec" << endl;
	cerr << "    -m specify memory size (default = 0x100)" << endl;
	cerr << "    -r show register printing during execution" << endl;
	cerr << "    -z show a dump of the regs & memory after simulation" << endl;
	exit(1);
}
/**
 * @brief used to disassemble instruction from memory
 *
 * used to disassemble instruction from memory and print them out
 *
 * @param mem the memory vector that holds the memory of the program
 *
 ********************************************************************************/
static void disassemble(const memory &mem)
{
	// create class object
	rv32i_decode rv;
	// loop of the size of memory
	for (size_t i = 0; i < mem.get_size(); i += 4)
	{
		// print out memory instruction and decode instruction
		cout << hex::to_hex32(i) << ": " << hex::to_hex32(mem.get32(i)) << "  " << rv.decode(i, mem.get32(i)) << endl;
	}
	return;
}
/**
 * @brief Reads values from standard input and put them into memory
 *
 * Program reads a binary file and puts into vector to be used as memory.
 * The program will then dump memory, read from memory, and store new stuff
 * into memory. Then execute instructions from memory.
 *
 * @param argc	used to get memory size from command line
 *
 * @param argv used to get file name from command line
 *
 * @return 0
 ********************************************************************************/
int main(int argc, char **argv)
{
	uint32_t memory_limit = 0x100; // default memory size = 256 bytes
	int opt;
	bool i = false; // insn flag
	bool d = false; // decoder flag
	bool r = false; // reg flag
	bool z = false; // dump end flag
	uint32_t exec_limit = 0;
	while ((opt = getopt(argc, argv, "m:l:dirz")) != -1)
	{

		switch (opt)
		{
		case 'm':
		{
			std::istringstream iss(optarg);
			iss >> std::hex >> memory_limit;
		}
		break;
		case 'd':
		{
			d = 'd';
		}
		break;
		case 'i':
		{
			i = 'i';
		}
		break;
		case 'l':
		{
			std::istringstream iss(optarg);
			iss >> exec_limit;
		}
		break;
		case 'r':
		{
			r = 'r';
		}
		break;
		case 'z':
		{
			z = 'z';
		}
		break;
		default: /* ’?’ */
			usage();
		}
	}
	if (optind >= argc)
		usage(); // missing filename
	memory mem(memory_limit);
	if (!mem.load_file(argv[optind]))
		usage();

	cpu_single_hart cpu(mem);
	// User wants to see disassembled insn
	if (d == true)
		disassemble(mem);
	// if users want to see regs during execute
	if (r == true)
		cpu.set_show_registers(true);
	// if user want instructions showed during execution
	if (i == true)
		cpu.set_show_instructions(true);

	// run instructions
	cpu.run(exec_limit);
	// if user wants to dump regs and memory at end
	if (z == true)
	{
		// dump regs
		cpu.dump("");
		// dump memory
		mem.dump();
	}

	return 0;
}