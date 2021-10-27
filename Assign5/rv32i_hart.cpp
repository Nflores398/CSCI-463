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
void rv32i_hart::exec(uint32_t insn, std ::ostream * pos)
{
    switch (get_opcode(insn)) //get opcode from insn
    {
    default:                    exec_illegal_insn (insn,pos); return;
    case opcode_lui:            exec_lui (insn,pos); return;
    case opcode_auipc:          exec_auipc (insn,pos); return; //auipc insn
    case opcode_jal:            exec_jal (insn,pos); return; //jal insn
    case opcode_jalr:           exec_jalr (insn,pos); return; //jalr insn
    case opcode_btype:          //btype insn
        switch (get_funct3(insn)) //get funct3
        {
        default:                exec_illegal_insn (insn,pos); return; //if ins doesnt exsit
        case funct3_beq:        exec_beq(insn,pos); return;
        case funct3_bge:        exec_bge(insn,pos); return;
        case funct3_bgeu:       exec_bgeu(insn,pos); return;
        case funct3_blt:        exec_blt(insn,pos); return;
        case funct3_bltu:       exec_bltu(insn,pos); return;
        case funct3_bne:        exec_bne(insn,pos); return;
        }
        assert(0 && "unrecognized funct3"); // impossible
    case opcode_rtype:          //rtype insn
        switch (get_funct3(insn)) //get funct3
        {
        case funct3_and:        exec_and(insn,pos); return;
        case funct3_or:         exec_or(insn,pos); return;
        case funct3_sll:        exec_sll(insn,pos); return;
        case funct3_slt:        exec_slt(insn,pos); return;
        case funct3_sltu:       exec_sltu(insn,pos); return;
        case funct3_xor:        exec_xor(insn,pos); return;
        case funct3_add:
            switch (get_funct7(insn)) //get funct7
            {
            case funct7_add:    exec_add(insn,pos); return;
            case funct7_sub:    exec_sub(insn,pos); return;
            default:            exec_illegal_insn (insn,pos); return;
            }
            assert(0 && "unrecognized funct7"); // impossible
        case funct3_srx:    
            switch (get_funct7(insn)) //get funct7
            {
            case funct7_srl:    exec_srl(insn,pos); return;
            case funct7_sra:    exec_sra(insn,pos); return;
            default:            exec_illegal_insn (insn,pos); return;
            }
            assert(0 && "unrecognized funct7"); // impossible
        default:                exec_illegal_insn (insn,pos); return;
        }
    case opcode_system:     //system insn
        switch (get_funct3(insn))
        {
        case funct3_csrrc:          exec_csr(insn,pos); return;
        case funct3_csrrs:          exec_csrrs(insn,pos); return;
        case funct3_csrrw:          exec_csr(insn,pos); return;
        case funct3_csrrci:         exec_csr(insn,pos); return;
        case funct3_csrrsi:         exec_csr(insn,pos); return;
        case funct3_csrrwi:         exec_csr(insn,pos); return;
        }
        switch (insn)               //check by insn
        {
        case insn_ecall:            exec_ecall(insn,pos); return;
        case insn_ebreak:           exec_ebreak(insn,pos); return;
        
        default:                    exec_illegal_insn (insn,pos); return;
        }
        assert(0 && "unrecognized funct3"); // impossible             
    case opcode_stype:              //s type insn
        switch (get_funct3(insn))   //get funct3
        {
        case funct3_sb:        exec_sb(insn,pos); return;
        case funct3_sh:        exec_sh(insn,pos); return;
        case funct3_sw:        exec_sw(insn,pos); return;
        default:               exec_illegal_insn (insn,pos); return;
        }
        assert(0 && "unrecognized funct3"); // impossible
    case opcode_load_imm:           //i type load insn
        switch (get_funct3(insn))   //get funct3
        {
        default:                exec_illegal_insn (insn,pos); return; 
        case funct3_lb:         exec_lb(insn,pos); return;
        case funct3_lh:         exec_lh(insn,pos); return; 
        case funct3_lhu:        exec_lhu(insn,pos); return;
        case funct3_lw:         exec_lw(insn,pos); return;
        case funct3_lbu:        exec_lbu(insn,pos); return;
        }
        assert(0 && "unrecognized funct3"); // impossible
    case opcode_alu_imm:        //i type alu insn
        switch (get_funct3(insn))   //get funct 3
        {
        default:                exec_illegal_insn (insn,pos); return;
        case funct3_add:        exec_addi(insn,pos); return;
        case funct3_sll:        exec_slli(insn,pos); return;
        case funct3_and:        exec_andi(insn,pos); return;
        case funct3_or:         exec_ori(insn,pos); return;
        case funct3_sltu:       exec_sltui(insn,pos); return;
        case funct3_slt:        exec_slti(insn,pos); return;
        case funct3_xor:        exec_xori(insn,pos); return;

        case funct3_srx: 
            switch (get_funct7(insn))   //get funct7
            {
            default:            exec_illegal_insn (insn,pos); return;
            case funct7_sra:    exec_srai(insn,pos); return;
            case funct7_srl:    exec_srli(insn,pos); return;
            }
            assert(0 && "unrecognized funct7"); // impossible
        }
        assert(0 && "unrecognized funct3"); // impossible
        //case
    }
    assert(0 && "unrecognized opcode"); // It should be impossible to ever get here!
}
void rv32i_hart::exec_lui(uint32_t insn, std::ostream* pos)
{
    //get needed valus
    uint32_t rd =  get_rd(insn);
    int32_t imm_u = get_imm_u(insn);
    
    //if show insn
    if(pos)
    {
        std ::string s = render_lui(insn);
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// "  << render_reg(rd) << " = " << to_hex0x32(imm_u);
    }
    //set reg rd to immu
    regs.set(rd,imm_u);
    
    //increase counter
    pc += 4;

}
void rv32i_hart::exec_auipc(uint32_t insn, std::ostream* pos)
{
    //get needed values
    uint32_t rd =  get_rd(insn);
    int32_t imm_u = get_imm_u(insn);
    //if show insn
    if(pos)
    {
        std ::string s = render_auipc(insn);
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// "  << render_reg(rd) << " = " << to_hex0x32(pc) << " + " << to_hex0x32(imm_u)
        << " = " << to_hex0x32(imm_u + pc);
    }
    //set immu + pc counter
    imm_u += pc;
    //set reg rd to immu
    regs.set(rd,imm_u);
    //incrase counter
    pc += 4;

}
void rv32i_hart::exec_jal(uint32_t insn, std::ostream* pos)
{
    //get need values
    uint32_t rd =  get_rd(insn);
    int32_t imm_j = get_imm_j(insn);
    //set regs rd to pc + 4
    regs.set(rd,pc+4);
    //if show insn
    if(pos)
    {
        std ::string s = render_jal(pc,insn);
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// "  << render_reg(rd) << " = " << to_hex0x32(pc+4) << ",  pc = " 
        << to_hex0x32(pc) << " + " << to_hex0x32(imm_j) << " = " << to_hex0x32((pc+imm_j));
    }
    //set pc counter to imm_j + pc
    pc = (imm_j + pc);
    

}
void rv32i_hart::exec_jalr(uint32_t insn, std::ostream* pos)
{
    //get the values needed for insn
    uint32_t rd = get_rd(insn);
    int32_t imm_i = get_imm_i(insn);
    int32_t rs1 = regs.get(get_rs1(insn));

    //execture the instruction
    int32_t val = (rs1 + imm_i) & ~0x1;

    if(pos)
    {
        std::string s = render_jalr(insn);
        *pos << std::setw(instruction_width) << std::setfill(' ') <<std::left << s;
        *pos << "// " << render_reg(rd) << " = " << to_hex0x32(pc +4)  << ",  pc = (" << to_hex0x32(imm_i) << " + " << to_hex0x32(rs1)<<
        ") & " << to_hex0x32(~0x1) << " = " << to_hex0x32(val);
    }

    //set it to the next value
    regs.set(rd, pc+4);
    pc = val;

}
void rv32i_hart::exec_beq(uint32_t insn, std::ostream* pos)
{
    //get values needed for insn
    uint32_t rs1 =  get_rs1(insn);
    uint32_t rs2 =  get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    uint32_t temppc = pc;
    //if regs equal
    if(regs.get(rs1) == regs.get(rs2))
    {
        //add imm_b
        pc += imm_b;
    }
    else
    {
        //else add +4
        pc += 4;
    }
    //if show insn
    if(pos)
    {
        std ::string s = render_btype(temppc,insn,"beq");
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << "pc += ("<< to_hex0x32(regs.get(rs1)) << " == " <<to_hex0x32(regs.get(rs2))
         << " ? " << to_hex0x32(imm_b) << " : 4) = " << to_hex0x32(pc);
    }  

}
void rv32i_hart::exec_bgeu(uint32_t insn, std::ostream* pos)
{
    //get values needed for insn
    uint32_t rs1 =  get_rs1(insn);
    uint32_t rs2 =  get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    uint32_t regrs1 = regs.get(rs1);
    uint32_t regrs2 = regs.get(rs2);
    uint32_t temppc = pc;
    //if >= unsingned
    if(regrs1 >= regrs2)
    {
        //add imm_b 
        pc += imm_b;
    }
    else
    {
        //next insn
        pc += 4;
    }
    if(pos)
    {
        std ::string s = render_btype(temppc,insn,"bgeu");
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << "pc += ("<< to_hex0x32(regs.get(rs1)) << " >=U " <<to_hex0x32(regs.get(rs2))
         << " ? " << to_hex0x32(imm_b) << " : 4) = " << to_hex0x32(pc);
    }  

}
void rv32i_hart::exec_bge(uint32_t insn, std::ostream* pos)
{
    //values needed 
    uint32_t rs1 =  get_rs1(insn);
    uint32_t rs2 =  get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    int32_t regrs1 = regs.get(rs1);
    int32_t regrs2 = regs.get(rs2);
    uint32_t temppc = pc;
    //if signed >=
    if(regrs1 >= regrs2)
    {
        //add imm_b to pc
        pc += imm_b;
    }
    else
    {
        //add +4
        pc += 4;
    }
    //if show insn
    if(pos)
    {
        std ::string s = render_btype(temppc,insn,"bge");
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << "pc += ("<< to_hex0x32(regs.get(rs1)) << " >= " <<to_hex0x32(regs.get(rs2))
         << " ? " << to_hex0x32(imm_b) << " : 4) = " << to_hex0x32(pc);
    }  

}
void rv32i_hart::exec_blt(uint32_t insn, std::ostream* pos)
{
    //values needed
    uint32_t rs1 =  get_rs1(insn);
    uint32_t rs2 =  get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    int32_t regrs1 = regs.get(rs1);
    int32_t regrs2 = regs.get(rs2);
    uint32_t temppc = pc;

    //if regs1 < regs2
    if(regrs1 < regrs2)
    {
        //add imm_b to pc
        pc += imm_b;
    }
    else
    {
        //add +4
        pc += 4;
    }
    //if show insn
    if(pos)
    {
        std ::string s = render_btype(temppc,insn,"blt");
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << "pc += ("<< to_hex0x32(regs.get(rs1)) << " < " <<to_hex0x32(regs.get(rs2))
         << " ? " << to_hex0x32(imm_b) << " : 4) = " << to_hex0x32(pc);
    }  

}
void rv32i_hart::exec_bltu(uint32_t insn, std::ostream* pos)
{
    //values needed
    uint32_t rs1 =  get_rs1(insn);
    uint32_t rs2 =  get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    uint32_t regrs1 = regs.get(rs1);
    uint32_t regrs2 = regs.get(rs2);
    uint32_t temppc = pc;
    // < unsigned
    if(regrs1 < regrs2)
    {
        //add imm_b to pc
        pc += imm_b;
    }
    else
    {
        //add +4
        pc += 4;
    }
    //if show insn
    if(pos)
    {
        std ::string s = render_btype(temppc,insn,"bltu");
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << "pc += ("<< to_hex0x32(regs.get(rs1)) << " <U " <<to_hex0x32(regs.get(rs2))
         << " ? " << to_hex0x32(imm_b) << " : 4) = " << to_hex0x32(pc);
    }  

}
void rv32i_hart::exec_bne(uint32_t insn, std::ostream* pos)
{
    //values needed 
    uint32_t rs1 =  get_rs1(insn);
    uint32_t rs2 =  get_rs2(insn);
    int32_t imm_b = get_imm_b(insn);
    int32_t regrs1 = regs.get(rs1);
    int32_t regrs2 = regs.get(rs2);
    uint32_t temppc = pc;
    //if they dont equal
    if(regrs1 != regrs2)
    {
        //add imm_b to pc
        pc += imm_b;
    }
    else
    {
        //add +4 to pc
        pc += 4;
    }
    //if show insn
    if(pos)
    {
        std ::string s = render_btype(temppc,insn,"bne");
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << "pc += ("<< to_hex0x32(regs.get(rs1)) << " != " <<to_hex0x32(regs.get(rs2))
         << " ? " << to_hex0x32(imm_b) << " : 4) = " << to_hex0x32(pc);
    }  

}
void rv32i_hart::exec_and(uint32_t insn, std::ostream* pos)
{
    //values neeed
    uint32_t rs1 =  get_rs1(insn);
    uint32_t rs2 =  get_rs2(insn);
    uint32_t rd = get_rd(insn);
    // and the two reg values
    int32_t val = (regs.get(rs1) & regs.get(rs2));
    //if show insn
    if(pos)
    {
        std ::string s = render_rtype(insn,"and");
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << render_reg(rd) << " = " << to_hex0x32(regs.get(rs1)) << " & " 
        << to_hex0x32(regs.get(rs2)) << " = " << to_hex0x32(val);
    }  
    //set rd to val
    regs.set(rd,val);
    //pc +4
    pc += 4;

}
void rv32i_hart::exec_or(uint32_t insn, std::ostream* pos)
{
    //values needed
    uint32_t rs1 =  get_rs1(insn);
    uint32_t rs2 =  get_rs2(insn);
    uint32_t rd = get_rd(insn);
    // or regs togehter
    int32_t val = (regs.get(rs1) | regs.get(rs2));
    
    if(pos)
    {
        std ::string s = render_rtype(insn,"or");
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << render_reg(rd) << " = " << to_hex0x32(regs.get(rs1)) << " | " 
        << to_hex0x32(regs.get(rs2)) << " = " << to_hex0x32(val);
    }
    //set rd to val 
    regs.set(rd,val);
    pc += 4;

}
void rv32i_hart::exec_sll(uint32_t insn, std::ostream* pos)
{
    //values needed
    uint32_t rs1 =  get_rs1(insn);
    uint32_t rs2 =  get_rs2(insn);
    uint32_t rd = get_rd(insn);
    // logic shift left rs1 by rs2 
    int32_t val = (regs.get(rs1) << (regs.get(rs2) & 0x0000001f));
    
    if(pos)
    {
        std ::string s = render_rtype(insn,"sll");
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << render_reg(rd) << " = " << to_hex0x32(regs.get(rs1)) << " << " 
        << (regs.get(rs2) & 0x0000001f)  << " = " << to_hex0x32(val);
    }
    //set rd to val 
    regs.set(rd,val); 
    pc += 4;

}
void rv32i_hart::exec_sltu(uint32_t insn, std ::ostream *pos)
{
    //values needed
    uint32_t rd =  get_rd(insn);
    uint32_t rs1 = regs.get(get_rs1(insn));
    uint32_t rs2 = regs.get(get_rs2(insn));
    //if rs1 is < rs2 val =1 or = 0
    uint32_t val = (rs1 < rs2) ? 1 : 0;
    //if show insn
    if (pos)
    {
        std ::string s = render_rtype(insn, "sltu");
        *pos << std ::setw(instruction_width) << std ::setfill(' ') << std ::left << s;
        *pos << "// " << render_reg(rd) << " = (" << hex ::to_hex0x32(rs1) << " <U " << hex ::to_hex0x32(rs2) << ") ? 1 : 0 = " << hex ::to_hex0x32(val);
    }
    //set rd to val
    regs.set(rd, val);
    pc += 4;
}
void rv32i_hart::exec_xor(uint32_t insn, std ::ostream *pos)
{
    //values needed
    uint32_t rs1 =  get_rs1(insn);
    uint32_t rs2 =  get_rs2(insn);
    uint32_t rd = get_rd(insn);
    //xor two regs together
    int32_t val = (regs.get(rs1) ^ regs.get(rs2));
    //if show insn
    if(pos)
    {
        std ::string s = render_rtype(insn,"xor");
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << render_reg(rd) << " = " << to_hex0x32(regs.get(rs1)) << " ^ " 
        << to_hex0x32(regs.get(rs2)) << " = " << to_hex0x32(val);
    } 
    //set rd to val 
    regs.set(rd,val);
    pc += 4;

}
void rv32i_hart::exec_add(uint32_t insn, std ::ostream *pos)
{
    //values needed
    uint32_t rs1 =  get_rs1(insn);
    uint32_t rs2 =  get_rs2(insn);
    uint32_t rd = get_rd(insn);
    //add reg1 to reg2
    int32_t val = (regs.get(rs1) + regs.get(rs2));
    //if show insn
    if(pos)
    {
        std ::string s = render_rtype(insn,"add");
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << render_reg(rd) << " = " << to_hex0x32(regs.get(rs1)) << " + " 
        << to_hex0x32(regs.get(rs2)) << " = " << to_hex0x32(val);
    }  
    //set rd to val
    regs.set(rd,val);
    pc += 4;

}
void rv32i_hart::exec_sub(uint32_t insn, std ::ostream *pos)
{
    //values needed
    uint32_t rs1 =  get_rs1(insn);
    uint32_t rs2 =  get_rs2(insn);
    uint32_t rd = get_rd(insn);
    //subtract regs from each other
    int32_t val = (regs.get(rs1) - regs.get(rs2));
    //if show insn
    if(pos)
    {
        std ::string s = render_rtype(insn,"sub");
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << render_reg(rd) << " = " << to_hex0x32(regs.get(rs1)) << " - " 
        << to_hex0x32(regs.get(rs2)) << " = " << to_hex0x32(val);
    }  
    //set rd to val
    regs.set(rd,val);
    pc += 4;

}
void rv32i_hart::exec_srl(uint32_t insn, std ::ostream *pos)
{
    //values needed
    uint32_t rs1 =  get_rs1(insn);
    uint32_t rs2 =  get_rs2(insn);
    uint32_t rd = get_rd(insn);
    uint32_t tempr1 = regs.get(rs1);
    uint32_t tempr2 = regs.get(rs2) & 0x0000001f;
    //shift logic right 
    uint32_t val = (tempr1 >> tempr2);
    
    if(pos)
    {
        std ::string s = render_rtype(insn,"srl");
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << render_reg(rd) << " = " << to_hex0x32(regs.get(rs1)) << " >> " 
        << (regs.get(rs2) & 0x0000001f)  << " = " << to_hex0x32(val);
    } 
    //set rd to val
    regs.set(rd,val); 
    pc += 4;

}
void rv32i_hart::exec_sra(uint32_t insn, std ::ostream *pos)
{
    //values needed
    uint32_t rs1 =  get_rs1(insn);
    uint32_t rs2 =  get_rs2(insn);
    uint32_t rd = get_rd(insn);
    //shift right arth 
    int32_t val = (regs.get(rs1) >> (regs.get(rs2) & 0x0000001f));
    //if show insn
    if(pos)
    {
        std ::string s = render_rtype(insn,"sra");
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << render_reg(rd) << " = " << to_hex0x32(regs.get(rs1)) << " >> " 
        << (regs.get(rs2) & 0x0000001f)  << " = " << to_hex0x32(val);
    } 
    //set rd to val
    regs.set(rd,val); 
    pc += 4;

}
void rv32i_hart::exec_sb(uint32_t insn, std ::ostream *pos)
{
    //values need
    int32_t rs1 =  get_rs1(insn);
    int32_t rs2 =  get_rs2(insn);
    int32_t imm_s = get_imm_s(insn);
    //get addrs
    uint32_t addrs = (regs.get(rs1) + imm_s);
    
    if(pos)
    {
        std ::string s = render_stype(insn,"sb");
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << "m8" << "(" << to_hex0x32(regs.get(rs1)) << " + " 
        << to_hex0x32(imm_s) << ") = " << to_hex0x32(regs.get(rs2) & 0x000000ff);
    }
    //set 8 bits at addres with values from rs2 reg
    mem.set8(addrs,regs.get(rs2) & 0x000000ff); 
    pc += 4;


}
void rv32i_hart::exec_sh(uint32_t insn, std ::ostream *pos)
{
    //values needed
    uint32_t rs1 =  get_rs1(insn);
    uint32_t rs2 =  get_rs2(insn);
    int32_t imm_s = get_imm_s(insn);
    //get addrs 
    int32_t addrs = (regs.get(rs1) + imm_s);
    
    if(pos)
    {
        std ::string s = render_stype(insn,"sh");
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << "m16" << "(" << to_hex0x32(regs.get(rs1)) << " + " 
        << to_hex0x32(imm_s) << ") = " << to_hex0x32(regs.get(rs2) & 0x0000ffff);
    }
    //set 16 bits at addr and values rs2 reg
    mem.set16(addrs,regs.get(rs2) & 0x0000ffff); 
    pc += 4;

}
void rv32i_hart::exec_sw(uint32_t insn, std ::ostream *pos)
{
    //values needed
    uint32_t rs1 =  get_rs1(insn);
    uint32_t rs2 =  get_rs2(insn);
    int32_t imm_s = get_imm_s(insn);
    //get addrs
    int32_t addrs = (regs.get(rs1) + imm_s);
    
    if(pos)
    {
        std ::string s = render_stype(insn,"sw");
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << "m32" << "(" << to_hex0x32(regs.get(rs1)) << " + " 
        << to_hex0x32(imm_s) << ") = " << to_hex0x32(regs.get(rs2));
    }
    //set 32 bits at addrs and values rs2 reg
    mem.set32(addrs,regs.get(rs2)); 
    pc += 4;

}
void rv32i_hart::exec_lb(uint32_t insn, std ::ostream *pos)
{
    //values needed
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);
    //get 8 bits from memory
    int32_t val = mem.get8_sx((imm_i+regs.get(rs1)));

    if(pos)
    {
        std ::string s = render_itype_load(insn,"lb");
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << render_reg(rd) << " = " << "sx(m8(" << to_hex0x32(regs.get(rs1)) << " + "
        << to_hex0x32(imm_i) << ")) = " << to_hex0x32(val); 
    }
    //set red to 8 bit val
    regs.set(rd,val);
    pc += 4;

}
void rv32i_hart::exec_lh(uint32_t insn, std ::ostream *pos)
{
    // values needed
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);
    //get 16 bits from memory at address
    int32_t val = mem.get16_sx((imm_i+regs.get(rs1)));


    if(pos)
    {
        std ::string s = render_itype_load(insn,"lh");
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << render_reg(rd) << " = " << "sx(m16(" << to_hex0x32(regs.get(rs1)) << " + "
        << to_hex0x32(imm_i) << ")) = " << to_hex0x32(val); 
    }
    //set rd to 16 bit val
    regs.set(rd,val);
    pc += 4;

}
void rv32i_hart::exec_lhu(uint32_t insn, std ::ostream *pos)
{
    //values needed
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);
    //get 16 bits unsigned from memory at addrs
    uint32_t val = mem.get16((imm_i+regs.get(rs1)));


    if(pos)
    {
        std ::string s = render_itype_load(insn,"lhu");
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << render_reg(rd) << " = " << "zx(m16(" << to_hex0x32(regs.get(rs1)) << " + "
        << to_hex0x32(imm_i) << ")) = " << to_hex0x32(val); 
    }
    //set rd to 16 bit unsigned value
    regs.set(rd,val);
    pc += 4;

}
void rv32i_hart::exec_lbu(uint32_t insn, std ::ostream *pos)
{
    //values neded
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);
    //get 8 unsigned bits from memory
    uint32_t val = mem.get8((imm_i+regs.get(rs1)));


    if(pos)
    {
        std ::string s = render_itype_load(insn,"lbu");
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << render_reg(rd) << " = " << "zx(m8(" << to_hex0x32(regs.get(rs1)) << " + "
        << to_hex0x32(imm_i) << ")) = " << to_hex0x32(val); 
    }
    //set rd to val
    regs.set(rd,val);
    pc += 4;

}
void rv32i_hart::exec_lw(uint32_t insn, std ::ostream *pos)
{
    //values needed
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);
    //get 32 bit from memory
    int32_t val = mem.get32_sx((imm_i+regs.get(rs1)));


    if(pos)
    {
        std ::string s = render_itype_load(insn,"lw");
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << render_reg(rd) << " = " << "sx(m32(" << to_hex0x32(regs.get(rs1)) << " + "
        << to_hex0x32(imm_i) << ")) = " << to_hex0x32(val); 
    }
    //set rd to val
    regs.set(rd,val);
    pc += 4;

}
void rv32i_hart::exec_addi(uint32_t insn, std ::ostream *pos)
{
    //values needed
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);
    //add rs1 to imm_i
    int32_t val = regs.get(rs1) + imm_i;

    if(pos)
    {
        std ::string s = render_itype_alu(insn,"addi",imm_i);
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << render_reg(rd) << " = " << to_hex0x32(regs.get(rs1)) << " + "
        << to_hex0x32(imm_i) << " = " << to_hex0x32(val); 
    }
    //set rd to val
    regs.set(rd,val);
    pc += 4;

}
void rv32i_hart::exec_slli(uint32_t insn, std ::ostream *pos)
{
    //values needed
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);
    //shift left logic
    int32_t val = regs.get(rs1) << imm_i % XLEN;

    if(pos)
    {
        std ::string s = render_itype_alu(insn,"slli",imm_i % XLEN);
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << render_reg(rd) << " = " << to_hex0x32(regs.get(rs1)) << " << "
        << std::dec << imm_i << " = " << to_hex0x32(val); 
    }
    //set rd to val
    regs.set(rd,val);
    pc += 4;

}
void rv32i_hart::exec_andi(uint32_t insn, std ::ostream *pos)
{
    //values needed
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);
    //and to values together
    int32_t val = regs.get(rs1) & imm_i;

    if(pos)
    {
        std ::string s = render_itype_alu(insn,"andi",imm_i);
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << render_reg(rd) << " = "<< to_hex0x32(regs.get(rs1)) << " & "
        << to_hex0x32(imm_i) << " = " << to_hex0x32(val); 
    }
    //set rd to val
    regs.set(rd,val);
    pc += 4;

}
void rv32i_hart::exec_ori(uint32_t insn, std ::ostream *pos)
{
    //values needed
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);
    //or the values together
    int32_t val = regs.get(rs1) | imm_i;

    if(pos)
    {
        std ::string s = render_itype_alu(insn,"ori",imm_i);
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << render_reg(rd) << " = " << to_hex0x32(regs.get(rs1)) << " | "
        << to_hex0x32(imm_i) << " = " << to_hex0x32(val); 
    }
    //set rd to val
    regs.set(rd,val);
    pc += 4;

}
void rv32i_hart::exec_sltui(uint32_t insn, std ::ostream *pos)
{
    //values needed
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t imm_i = get_imm_i(insn);
    uint32_t temprs1 = regs.get(rs1);
    //if greater than set 1 or if not set 0 unsigned
    uint32_t val = (temprs1 < imm_i) ? 1 : 0;

    if(pos)
    {
        std ::string s = render_itype_alu(insn,"sltiu",imm_i);
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << render_reg(rd) << " = " << "(" << to_hex0x32(regs.get(rs1)) << " <U "
        << std::dec <<  imm_i << ") ? 1 : 0 = " << to_hex0x32(val); 
    }
    //set rd to val
    regs.set(rd,val);
    pc += 4;

}
void rv32i_hart::exec_slti(uint32_t insn, std ::ostream *pos)
{
    //values needed
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);
    ////if greater than set 1 or if not set 0 
    int32_t val = (regs.get(rs1) < imm_i) ? 1 : 0;

    if(pos)
    {
        std ::string s = render_itype_alu(insn,"slti",imm_i);
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << render_reg(rd) << " = " << "(" << to_hex0x32(regs.get(rs1)) << " < "
        << std::dec << imm_i << ") ? 1 : 0 = " << to_hex0x32(val); 
    }
    //set rd to val
    regs.set(rd,val);
    pc += 4;

}
void rv32i_hart::exec_xori(uint32_t insn, std ::ostream *pos)
{
    //values needed
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);
    //xor values 
    int32_t val = (regs.get(rs1) ^ imm_i);

    if(pos)
    {
        std ::string s = render_itype_alu(insn,"xori",imm_i);
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << render_reg(rd) << " = " << to_hex0x32(regs.get(rs1)) << " ^ "
        << to_hex0x32(imm_i) << " = " << to_hex0x32(val); 
    }
    //set rd to val
    regs.set(rd,val);
    pc += 4;

}
void rv32i_hart::exec_srai(uint32_t insn, std ::ostream *pos)
{
    //values needed
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    int32_t imm_i = get_imm_i(insn);
    int32_t temp = regs.get(rs1);
    //shift temp right by imm_i
    int32_t val = (temp >> (imm_i % XLEN));

    if(pos)
    {
        std ::string s = render_itype_alu(insn,"srai",imm_i % XLEN);
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << render_reg(rd) << " = " << to_hex0x32(regs.get(rs1)) << " >> "
        << (imm_i % XLEN)  << " = " << to_hex0x32(val); 
    }
    //set rd to val
    regs.set(rd,val);
    pc += 4;

}
void rv32i_hart::exec_srli(uint32_t insn, std ::ostream *pos)
{
    //values needed
    uint32_t rd = get_rd(insn);
    uint32_t rs1 = get_rs1(insn);
    uint32_t imm_i = get_imm_i(insn);
    uint32_t temp = regs.get(rs1);
    //shift temp right by imm_i unsigned
    uint32_t val = (temp >> imm_i % XLEN);

    if(pos)
    {
        std ::string s = render_itype_alu(insn,"srli",imm_i % XLEN);
        *pos << std::setw(instruction_width) << setfill(' ') << left << s;
        *pos << "// " << render_reg(rd) << " = " << to_hex0x32(regs.get(rs1)) << " >> "
        << (imm_i % XLEN) << " = " << to_hex0x32(val); 
    }
    //set rd to val
    regs.set(rd,val);
    pc += 4;

}
void rv32i_hart::exec_slt(uint32_t insn, std ::ostream *pos)
{
    //values needed
    uint32_t rd = get_rd ( insn );
    uint32_t rs1 = get_rs1 ( insn ) ;
    uint32_t rs2 = get_rs2 ( insn ) ;
    //if rs1 is < rs2 then 1 or 0
    int32_t val = ( regs . get ( rs1 ) < regs . get ( rs2 )) ? 1 : 0;

    if ( pos )
    {
        std :: string s = render_rtype ( insn , "slt") ;
        * pos << std :: setw ( instruction_width ) << std :: setfill (' ') << std :: left << s;
        * pos << "// " << render_reg ( rd ) << " = (" << hex :: to_hex0x32 ( regs . get ( rs1 ) ) << " < " << hex ::
        to_hex0x32 ( regs . get ( rs2 )) << ") ? 1 : 0 = " << hex :: to_hex0x32 ( val );
    }
    //set rd to val
    regs . set (rd , val );
    pc += 4;
}

///////
void rv32i_hart::exec_illegal_insn(uint32_t insn, std ::ostream * pos)
{
    //void insn not needed
    (void) insn ;
    if ( pos )
    * pos << render_illegal_insn ( insn );
    //set halt to true
    halt = true ;
    //set reason for halt
    halt_reason = " Illegal instruction ";
}

void rv32i_hart::exec_csrrs(uint32_t insn, std ::ostream *pos)
{
    uint32_t rd =  get_rd(insn);
    if (pos)
    {
        std ::string s = render_csrrx(insn, "csrrs");
        *pos << std ::setw(instruction_width) << std ::setfill(' ') << std ::left << s;
        *pos << "// " << render_reg(rd) << " = " << mhartid;
    }
    //set rd to mhartid
    regs.set(rd, mhartid);
    pc += 4;
}
void rv32i_hart::exec_ebreak(uint32_t insn,std::ostream * pos)
{
    //Ebreak insn
    if (pos)
    {
        std :: string s = render_ebreak ( insn );
        * pos << std :: setw ( instruction_width ) << std::setfill (' ') << std :: left << s;
        * pos << "// HALT";
    }
    //set halt to true
    halt = true;
    //set reason
    halt_reason = "EBREAK instruction";
}
void rv32i_hart::exec_ecall(uint32_t insn,std::ostream * pos)
{
    //ecall insn
    if (pos)
    {
        std :: string s = render_ecall(insn);
        * pos << std :: setw ( instruction_width ) << std::setfill (' ') << std :: left << s;
        * pos << "//ECALL";
    }
    //set halt to true
    halt = true;
    //set reason
    halt_reason = "ECALL instruction";
}
void rv32i_hart::exec_csr(uint32_t insn,std::ostream * pos)
{
    //if system insn executed
    if (pos)
    {
        std :: string s = render_csrrx(insn,"csr");
        * pos << std :: setw (instruction_width) << std::setfill (' ') << std :: left << s;
        * pos << "// HALT";
    }
    //halt
    halt = true;
    //set reason for halt
    halt_reason = "Illegal CSR in CRRSS instruction";
}
void rv32i_hart::dump(const string &hdr) const
{
    //dump regs
    regs.dump(hdr);
    //print pc counter
    cout << " pc " << to_hex32(pc) << endl;
}
void rv32i_hart::reset()
{
    //reset pc 
    pc = 0;
    //reset reg
    regs.reset();
    //reset insn counter
    insn_counter = 0;
    //stop halt
    halt = false;
    //set reason
    halt_reason = "none";
}
void rv32i_hart::tick(const std ::string &hdr = "")
{
    //tick
    uint32_t insn;
    //if halted
    if(halt)
    {
        return;
    }
    //set counter +1
    insn_counter += 1;
    //if show regs 
    if(show_registers)
    {
        //dump regs
        regs.dump(hdr);
        //show pc counter
        cout << " pc " << to_hex32(pc) << endl;
    }
    //get insn from memory at pc
    insn = mem.get32(pc);
    //if show insn
    if(show_instructions)
    {
        //print pc counter ans insn
        cout << hex::to_hex32(pc) << ": " << hex::to_hex32(insn) << "  "; 
        //exec insn
        exec(insn,&std::cout);
        cout << endl;
    }
    else
    {
        //exec insn no insn printed
        exec(insn,nullptr);
    }

}