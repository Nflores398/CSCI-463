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
#include "memory.h"
#include "rv32i_decode.h"
/**
 * @brief Explains how to run the program properly
 * 
 *	Tells user how to properly run the program from the command line and then
 *	exits
 *
 ********************************************************************************/
static void usage()
{
	cerr << "Usage: rv32i [-m hex-mem-size] infile" << endl;
	cerr << "    -m specify memory size (default = 0x100)" << endl;
	exit(1);
}
/**
 * @brief Reads values from standard input and put them into memory
 * 
 * Program reads a binary file and puts into vector to be used as memory.
 * The program will then dump memory, read from memory, and store new stuff
 * into memory.
 * 
 * @param argc	used to get memory size from command line 
 * 
 * @param argv used to get file name from command line 
 * 
 * @return 0
 ********************************************************************************/
static void disassemble(const memory &mem)
{
	rv32i_decode rv;
	for (size_t i = 0; i < mem.get_size(); i+=4)
	{
		cout << hex::to_hex32(i) << ": " << hex::to_hex32(mem.get32(i)) << "  " <<rv.decode(i,mem.get32(i)) << endl;
	}
	return;
}
int main(int argc, char **argv)
{
	uint32_t memory_limit = 0x100; // default memory size = 256 bytes
	int opt;
	while ((opt = getopt(argc, argv, "m:")) != -1)
	{
		switch (opt)
		{
		case 'm':
		{
			std::istringstream iss(optarg);
			iss >> std::hex >> memory_limit;
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
	disassemble(mem);
	mem.dump();
	return 0;
}