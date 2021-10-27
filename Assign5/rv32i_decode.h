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
* Decode instruction from memory 
********************************************************************************/
class rv32i_decode : public hex 
{
public:

/**
* @brief Decode the passed in instruction
* 
*	 Decode the passed in instruction and determine the type of instruction
*
* @param insn the name of the instruction to be decoded
*
* @param addr The memory address where the insn is stored.
* 
* @return a string of the formated instruction
*
********************************************************************************/	
	static std::string decode(uint32_t addr, uint32_t insn);

protected:
	//max with of insn name
	static constexpr int mnemonic_width             = 8;
	//All opcodes
	static constexpr uint32_t opcode_lui			= 0b0110111;
	static constexpr uint32_t opcode_auipc			= 0b0010111;
	static constexpr uint32_t opcode_jal			= 0b1101111;
	static constexpr uint32_t opcode_jalr			= 0b1100111;
	static constexpr uint32_t opcode_btype			= 0b1100011;
	static constexpr uint32_t opcode_load_imm		= 0b0000011;
	static constexpr uint32_t opcode_stype			= 0b0100011;
	static constexpr uint32_t opcode_alu_imm		= 0b0010011;
	static constexpr uint32_t opcode_rtype			= 0b0110011;
	static constexpr uint32_t opcode_system			= 0b1110011;
	//btype
	static constexpr uint32_t funct3_beq			= 0b000;
	static constexpr uint32_t funct3_bne			= 0b001;
	static constexpr uint32_t funct3_blt			= 0b100;
	static constexpr uint32_t funct3_bge			= 0b101;
	static constexpr uint32_t funct3_bltu			= 0b110;
	static constexpr uint32_t funct3_bgeu			= 0b111;
	//itype
	static constexpr uint32_t funct3_lb				= 0b000;
	static constexpr uint32_t funct3_lh				= 0b001;
	static constexpr uint32_t funct3_lw				= 0b010;
	static constexpr uint32_t funct3_lbu			= 0b100;
	static constexpr uint32_t funct3_lhu			= 0b101;
	//stype
	static constexpr uint32_t funct3_sb				= 0b000;
	static constexpr uint32_t funct3_sh				= 0b001;
	static constexpr uint32_t funct3_sw				= 0b010;
	//itype/rtype
	static constexpr uint32_t funct3_add			= 0b000;
	static constexpr uint32_t funct3_sll			= 0b001;
	static constexpr uint32_t funct3_slt			= 0b010;
	static constexpr uint32_t funct3_sltu			= 0b011;
	static constexpr uint32_t funct3_xor			= 0b100;
	static constexpr uint32_t funct3_srx			= 0b101;
	static constexpr uint32_t funct3_or				= 0b110;
	static constexpr uint32_t funct3_and			= 0b111;
	//itype funct7
	static constexpr uint32_t funct7_srl			= 0b0000000;
	static constexpr uint32_t funct7_sra			= 0b0100000;
	//itype funct7
	static constexpr uint32_t funct7_add			= 0b0000000;
	static constexpr uint32_t funct7_sub			= 0b0100000;
	//system type
	static constexpr uint32_t insn_ecall			= 0x00000073;
	static constexpr uint32_t insn_ebreak			= 0x00100073;
	//system type
	static constexpr uint32_t funct3_csrrw			= 0b001;
	static constexpr uint32_t funct3_csrrs			= 0b010;
	static constexpr uint32_t funct3_csrrc			= 0b011;
	static constexpr uint32_t funct3_csrrwi			= 0b101;
	static constexpr uint32_t funct3_csrrsi			= 0b110;
	static constexpr uint32_t funct3_csrrci			= 0b111;

/**
* @defgroup get value from encoded instruction 
*
* Get different pieces of a 32bit hex number and return them
*
* @param insn the instruction that will be decoded 
* 
* @return the part of the instruction that the function is looking for.
* 
*@{
********************************************************************************/
	static uint32_t get_opcode(uint32_t insn);	///< Get opcode from instruction
	static uint32_t get_rd(uint32_t insn);		///< Get rd from instruction
	static uint32_t get_funct3(uint32_t insn);	///< Get funct3 from instruction
	static uint32_t get_rs1(uint32_t insn);		///< Get rs1 from instruction
	static uint32_t get_rs2(uint32_t insn);		///< Get rs2 from instruction
	static uint32_t get_funct7(uint32_t insn);	///< Get funct7 from instruction
	static int32_t get_imm_i(uint32_t insn);	///< Get i type from instruction
	static int32_t get_imm_u(uint32_t insn);	///< Get u type from instruction
	static int32_t get_imm_b(uint32_t insn);	///< Get b type from instruction
	static int32_t get_imm_s(uint32_t insn);	///< Get s type from instruction
	static int32_t get_imm_j(uint32_t insn);	///< Get j type from instruction
/**@}*/

	static constexpr uint32_t XLEN = 32; //XLEN represents the number of bits in RV32I CPU registers
/**
* @brief Prints out that instruction does not exist
* 
*	Prints out that instruction does not exist
*
* @param insn the instruction from memory
*
* @return a string that states the instruction doesnt exist
*
********************************************************************************/
	static std::string render_illegal_insn(uint32_t insn);
/**
* @brief Render lui Load upper immediate
* 
*	Prints out lui a U type instruction
*
* @param insn the instruction for lui
*
* @return a string of the instruction formated
*
********************************************************************************/
	static std::string render_lui(uint32_t insn);
/**
* @brief Render auipc add upper immediate to PC
* 
*	Prints out auipc a U type instruction
*
* @param insn the instruction for auipc
*
* @return a string of the instruction formated
*
********************************************************************************/
	static std::string render_auipc(uint32_t insn);
/**
* @brief Render jal jump and link
* 
*	Prints out jal a j type instruction
*
* @param insn the instruction for jal
*
* @param addr location of the instruction in memory
*
* @return a string of the instruction formated
*
********************************************************************************/	
	static std::string render_jal(uint32_t addr, uint32_t insn);
/**
* @brief Render jalr jump and link register
* 
*	Prints out jalr a I type instruction
*
* @param insn the instruction for jalr
*
* @return a string of the instruction formated
*
********************************************************************************/
	static std::string render_jalr(uint32_t insn);
/**
* @brief Render b type instructions
* 
*	Prints out b type instructions
*
* @param insn a b type instructions 
*
* @param addr The memory address where the insn is stored.
*
* @return a string of the instruction formated
*
********************************************************************************/	
	static std::string render_btype(uint32_t addr, uint32_t insn, const char *mnemonic);
/**
* @brief Render i type load instructions
* 
*	Prints out i type load instructions
*
* @param insn a i type load instructions 
*
* @param mnemonic the name of the instruction
*
* @return a string of the instruction formated
*
********************************************************************************/	
	static std::string render_itype_load(uint32_t insn, const char *mnemonic);
/**
* @brief Render s type instructions
* 
*	Prints out s type instructions
*
* @param insn a s type instructions 
*
* @param mnemonic the name of the instruction
*
* @return a string of the instruction formated
*
********************************************************************************/	
	static std::string render_stype(uint32_t insn, const char *mnemonic);
/**
* @brief Render i type aui instructions
* 
*	Prints out i type aui instructions
*
* @param insn a i type aui instructions 
*
* @param mnemonic the name of the instruction
*
* @param imm_i the decoded imm_i of the instruction
*
* @return a string of the instruction formated
*
********************************************************************************/	
	static std::string render_itype_alu(uint32_t insn, const char *mnemonic, int32_t imm_i);
/**
* @brief Render r type instructions
* 
*	Prints out r type instructions
*
* @param insn a r type instructions 
*
* @param mnemonic the name of the instruction
*
* @return a string of the instruction formated
*
********************************************************************************/
	static std::string render_rtype(uint32_t insn, const char *mnemonic);
/**
* @brief Render ecall
* 
*	Prints out ecall instruction
*
* @param insn a ecall type instructions 
*
*
* @return a string of the instruction formated
*
********************************************************************************/
	static std::string render_ecall(uint32_t insn);
/**
* @brief Render ebreak
* 
*	Prints out ebreak instruction to stop program
*
* @param insn a ebreak instructions 
*
* @return a string of the instruction formated
*
********************************************************************************/
	static std::string render_ebreak(uint32_t insn);
/**
* @brief Render I type system instructions
* 
*	 Render I type system instructions
*
* @param insn a I type system  instructions 
*
* @param mnemonic the name of the instruction
*
* @return a string of the instruction formated
*
********************************************************************************/
	static std::string render_csrrx(uint32_t insn, const char *mnemonic);
/**
* @brief Render I type system i instructions
* 
*	 Render I type system i instructions
*
* @param insn a I type system i instructions 
*
* @param mnemonic the name of the instruction
*
* @return a string of the instruction formated
*
********************************************************************************/
	static std::string render_csrrxi(uint32_t insn, const char *mnemonic);
/**
* @brief Render register formatted
* 
*	 Render register formatted
*
* @param r the number of the register
*
* @return a string of the formated register
*
********************************************************************************/
	static std::string render_reg(int r);
/**
* @brief Render base disp
* 
*	 Render base disp
*
* @param base base register 
*
* @param disp displacement off of the register
*
* @return a string of the formated base displacement
*
********************************************************************************/
	static std::string render_base_disp(uint32_t base, int32_t disp);
/**
* @brief Render mnemonic
* 
*	 Render mnemonic and formate the name of the instruction
*
* @param m the name of the instruction
*
* @return a string of the formated mnemonic
*
********************************************************************************/	
	static std::string render_mnemonic(const std::string &m);
};