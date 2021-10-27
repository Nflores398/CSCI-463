#include "hex.h"
#include "rv32i_decode.h"
#include "memory.h"
#include "registerfile.h"
/**
* Execute instruction from memory
********************************************************************************/
class rv32i_hart : public rv32i_decode
{

public:
    /**
     * @brief Constructor of the rv321i_hart
     *
     *	 Contructor of the hart takes memory class
     *
     * @param memory class memory that is passed to the constructor
     *
     ********************************************************************************/
    rv32i_hart(memory &m) : mem(m){};
    /**
     * @brief set_show_x
     *
     *	 Bool that is used to toggle showing the instructions or register
     *    when running
     *
     * @param b flag that tells if the option is on or off
     *
     *@{
     ********************************************************************************/
    void set_show_instructions(bool b) { show_instructions = b; }
    void set_show_registers(bool b) { show_registers = b; }
    /**@}*/

    /**
     * @brief Checks if the cpu has halted
     *
     *	 Checks if the cpu has haletd by true is halted
     *
     * @return halt flag
     *
     ********************************************************************************/
    bool is_halted() const { return halt; }
    /**
     * @brief gives reason why the cpu was halted
     *
     *	 Gives reason why the cpu was halted
     *
     * @return halt_reason which is the reason the program was halted
     *
     ********************************************************************************/
    const std ::string &get_halt_reason() const { return halt_reason; }
    /**
     * @brief get the instruction counter
     *
     *	 returns the instruction counteer
     *
     * @return insn_counter the amount of instructions ran
     *
     ********************************************************************************/
    uint64_t get_insn_counter() const { return insn_counter; }
    /**
     * @brief sets the hart id
     *
     *	 sets hart id
     *
     * @param i which is the id of the hart
     *
     ********************************************************************************/
    void set_mhartid(int i) { mhartid = i; }
    /**
     * @brief tick which execute the insn from memory
     *
     *	 tick which execute the insn from memory
     *
     * @param hdr is the header of the hart
     *
     ********************************************************************************/
    void tick(const std ::string &hdr);
    /**
     * @brief print out all the hart registers and pc counter
     *
     *	  print out all the hart registers and pc counter
     *
     * @param hdr is the header of the hart
     *
     ********************************************************************************/
    void dump(const std ::string &hdr) const;
    /**
     * @brief resets the registers and pc counter and halt status
     *
     ********************************************************************************/
    void reset();

private:
    static constexpr int instruction_width = 35;
    /**
     * @brief excute an instruction
     *
     *	  determines which insruction is executed by getting opcode
     *
     * @param insn  the insn from memeory to execute
     *
     * @param pos   used if show instruction flag is true
     *
     ********************************************************************************/
    void exec(uint32_t insn, std ::ostream *);
    /**
     * @brief excute if the instruction is illegal
     *
     *	  excute if the instruction is illegal
     *
     * @param insn  the insn from memeory to execute
     *
     * @param pos   used if show instruction flag is true
     *
     ********************************************************************************/
    void exec_illegal_insn(uint32_t insn, std ::ostream *);
    /**
     * @brief exec_xxx simulates an instruction given by its opcode
     *
     *	executes an instruction based off the opcode
     *
     * @param insn the instruction to be executed
     *
     * @param pos the output of the instruction if the flag is set to show
     *
     *@{
     ********************************************************************************/
    void exec_lui(uint32_t insn, std::ostream *pos);   // lui
    void exec_auipc(uint32_t insn, std::ostream *pos); // auipc
    void exec_jal(uint32_t insn, std::ostream *pos);   // jal
    void exec_jalr(uint32_t insn, std::ostream *pos);  // jalr

    void exec_beq(uint32_t insn, std::ostream *pos);  // b type  beq
    void exec_bge(uint32_t insn, std::ostream *pos);  // bge
    void exec_bgeu(uint32_t insn, std::ostream *pos); // bgeu
    void exec_blt(uint32_t insn, std::ostream *pos);  // blt
    void exec_bltu(uint32_t insn, std::ostream *pos); // bltu
    void exec_bne(uint32_t insn, std::ostream *pos);  // bne

    void exec_and(uint32_t insn, std::ostream *pos);  // r type and
    void exec_or(uint32_t insn, std::ostream *pos);   // or
    void exec_sll(uint32_t insn, std::ostream *pos);  // sll
    void exec_sltu(uint32_t insn, std::ostream *pos); // sltu
    void exec_xor(uint32_t insn, std::ostream *pos);  // xor
    void exec_add(uint32_t insn, std::ostream *pos);  // add
    void exec_sub(uint32_t insn, std::ostream *pos);  // sub
    void exec_srl(uint32_t insn, std::ostream *pos);  // srl
    void exec_sra(uint32_t insn, std::ostream *pos);  // sra
    void exec_slt(uint32_t insn, std ::ostream *pos); // slt

    void exec_sb(uint32_t insn, std::ostream *pos); // s type sb
    void exec_sh(uint32_t insn, std::ostream *pos); // sh
    void exec_sw(uint32_t insn, std::ostream *pos); // sw

    void exec_lb(uint32_t insn, std::ostream *pos);  // i load type lb
    void exec_lh(uint32_t insn, std::ostream *pos);  // lh
    void exec_lhu(uint32_t insn, std::ostream *pos); // lhu
    void exec_lw(uint32_t insn, std::ostream *pos);  // lw
    void exec_lbu(uint32_t insn, std::ostream *pos); // lbu

    void exec_csrrs(uint32_t insn, std::ostream *pos); // system type csrrs
    void exec_csr(uint32_t insn, std::ostream *pos);   // everyother csr insn

    void exec_ebreak(uint32_t insn, std::ostream *pos); // ebreak
    void exec_ecall(uint32_t insn, std::ostream *pos);  // ecall

    void exec_addi(uint32_t insn, std::ostream *pos);  // i type addi
    void exec_slli(uint32_t insn, std::ostream *pos);  // slli
    void exec_andi(uint32_t insn, std::ostream *pos);  // andi
    void exec_ori(uint32_t insn, std::ostream *pos);   // ori
    void exec_sltui(uint32_t insn, std::ostream *pos); // sltui
    void exec_slti(uint32_t insn, std::ostream *pos);  // slti
    void exec_xori(uint32_t insn, std::ostream *pos);  // xori
    void exec_srai(uint32_t insn, std::ostream *pos);  // srai
    void exec_srli(uint32_t insn, std::ostream *pos);  // srli
    /**@}*/

    bool halt = {false};                   // halt flag
    bool show_instructions = false;        // show insn flag
    bool show_registers = false;           // show regs flag
    std ::string halt_reason = {" none "}; // halt reason

    uint64_t insn_counter = {0}; // insn counter
    uint32_t pc = {0};           // pc counter
    uint32_t mhartid = {0};      // hart id

protected:
    registerfile regs;
    memory &mem;
};