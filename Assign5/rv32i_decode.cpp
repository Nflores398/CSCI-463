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
#include "rv32i_decode.h"
//decode opcode
string rv32i_decode::decode(uint32_t addr, uint32_t insn)
{
    switch (get_opcode(insn)) //get opcode from insn
    {
    default:                    return render_illegal_insn(insn);
    case opcode_lui:            return render_lui(insn); //lui insn
    case opcode_auipc:          return render_auipc(insn); //auipc insn
    case opcode_jal:            return render_jal(addr,insn); //jal insn
    case opcode_jalr:           return render_jalr(insn); //jalr insn
    case opcode_btype:          //btype insn
        switch (get_funct3(insn)) //get funct3
        {
        default:                return render_illegal_insn(insn); //if ins doesnt exsit
        case funct3_beq:        return render_btype(addr,insn,"beq");
        case funct3_bge:        return render_btype(addr,insn,"bge");
        case funct3_bgeu:       return render_btype(addr,insn,"bgeu");
        case funct3_blt:        return render_btype(addr,insn,"blt");
        case funct3_bltu:       return render_btype(addr,insn,"bltu");
        case funct3_bne:        return render_btype(addr,insn,"bne");
        }
        assert(0 && "unrecognized funct3"); // impossible
    case opcode_rtype:          //rtype insn
        switch (get_funct3(insn)) //get funct3
        {
        case funct3_and:        return render_rtype(insn,"and");    
        case funct3_or:         return render_rtype(insn,"or");
        case funct3_sll:        return render_rtype(insn,"sll");
        case funct3_slt:        return render_rtype(insn,"slt");
        case funct3_sltu:       return render_rtype(insn,"sltu");
        case funct3_xor:        return render_rtype(insn,"xor");
        case funct3_add:
            switch (get_funct7(insn)) //get funct7
            {
            case funct7_add:    return render_rtype(insn,"add");
            case funct7_sub:    return render_rtype(insn,"sub");
            default:            return render_illegal_insn(insn);
            }
            assert(0 && "unrecognized funct7"); // impossible
        case funct3_srx:    
            switch (get_funct7(insn)) //get funct7
            {
            case funct7_srl:    return render_rtype(insn,"srl");
            case funct7_sra:    return render_rtype(insn,"sra");
            default:            return render_illegal_insn(insn);
            }
            assert(0 && "unrecognized funct7"); // impossible
        default:                return render_illegal_insn(insn);
        }
    case opcode_system:     //system insn
        switch (get_funct3(insn))
        {
        case funct3_csrrc:          return render_csrrx(insn,"csrrc");
        case funct3_csrrs:          return render_csrrx(insn,"csrrs");
        case funct3_csrrw:          return render_csrrx(insn,"csrrw");
        case funct3_csrrci:         return render_csrrxi(insn,"csrrci");
        case funct3_csrrsi:         return render_csrrxi(insn,"csrrsi");
        case funct3_csrrwi:         return render_csrrxi(insn,"csrrwi");
        }
        switch (insn)               //check by insn
        {
        case insn_ecall:            return render_ecall(insn);
        case insn_ebreak:           return render_ebreak(insn);
        
        default:                    return render_illegal_insn(insn);
        }
        assert(0 && "unrecognized funct3"); // impossible             
    case opcode_stype:              //s type insn
        switch (get_funct3(insn))   //get funct3
        {
        case funct3_sb:         return render_stype(insn,"sb");
        case funct3_sh:         return render_stype(insn,"sh");
        case funct3_sw:         return render_stype(insn,"sw");
        default:                return render_illegal_insn(insn);
        }
        assert(0 && "unrecognized funct3"); // impossible
    case opcode_load_imm:           //i type load insn
        switch (get_funct3(insn))   //get funct3
        {
        default:                return render_illegal_insn(insn);  
        case funct3_lb:         return render_itype_load(insn, "lb");
        case funct3_lh:         return render_itype_load(insn, "lh");; 
        case funct3_lhu:        return render_itype_load(insn, "lhu");;
        case funct3_lw:         return render_itype_load(insn, "lw");;
        case funct3_lbu:        return render_itype_load(insn, "lbu");;
        }
        assert(0 && "unrecognized funct3"); // impossible
    case opcode_alu_imm:        //i type alu insn
        switch (get_funct3(insn))   //get funct 3
        {
        default:                return render_illegal_insn(insn);
        case funct3_add:        return render_itype_alu(insn, "addi", get_imm_i(insn));
        case funct3_sll:        return render_itype_alu(insn, "slli", get_imm_i(insn) % XLEN);
        case funct3_and:        return render_itype_alu(insn, "andi", get_imm_i(insn));
        case funct3_or:         return render_itype_alu(insn, "ori", get_imm_i(insn));
        case funct3_sltu:       return render_itype_alu(insn, "sltiu", get_imm_i(insn));
        case funct3_slt:        return render_itype_alu(insn, "slti", get_imm_i(insn));
        case funct3_xor:        return render_itype_alu(insn, "xori", get_imm_i(insn));

        case funct3_srx: 
            switch (get_funct7(insn))   //get funct7
            {
            default:            return render_illegal_insn(insn);
            case funct7_sra:    return render_itype_alu(insn, "srai", get_imm_i(insn) % XLEN);
            case funct7_srl:    return render_itype_alu(insn, "srli", get_imm_i(insn) % XLEN);
            }
            assert(0 && "unrecognized funct7"); // impossible
        }
        assert(0 && "unrecognized funct3"); // impossible
        //case
    }
    assert(0 && "unrecognized opcode"); // It should be impossible to ever get here!
}
//if the function doesn't exist
string rv32i_decode::render_illegal_insn(uint32_t insn)
{
    (void)insn; //not used so voided
    return "ERROR: UNIMPLEMENTED INSTRUCTION";
}
std::string rv32i_decode::render_lui(uint32_t insn)
{
    //get rd register
    uint32_t rd = get_rd(insn);
    //get imm u of u type
    int32_t imm_u = get_imm_u(insn);
    std::ostringstream os;
    //formate string and return it
    os << render_mnemonic("lui") << render_reg(rd) << ","
       << hex::to_hex0x20((imm_u >> 12) & 0x0fffff);
    return os.str();
}
uint32_t rv32i_decode::get_rd(uint32_t insn)
{
    //shift and to get rd
    return (insn & 0x00000f80) >> 7;
}

int32_t rv32i_decode::get_imm_u(uint32_t insn)
{
    //and to get imm u
    return insn & 0xfffff000;
}

uint32_t rv32i_decode::get_opcode(uint32_t insn)
{
    //and to get opcode
    return (insn & 0x0000007f);
}
string rv32i_decode::render_auipc(uint32_t insn)
{
    //get rd
    uint32_t rd = get_rd(insn);
    //get immu
    int32_t imm_u = get_imm_u(insn);
    std::ostringstream os;
    //formate string and return it
    os << render_mnemonic("auipc") << render_reg(rd) << ","
       << hex::to_hex0x20((imm_u >> 12) & 0x0fffff);
    return os.str();
}
string rv32i_decode::render_jal(uint32_t addr, uint32_t insn)
{
    //get rd
    uint32_t rd = get_rd(insn);
    //get imm j
    int32_t imm_j = get_imm_j(insn);
    std::ostringstream os;
    //formate string and return it
    os << render_mnemonic("jal") << render_reg(rd) << ","
       << hex::to_hex0x32(imm_j+addr);
    return os.str();

}
int32_t rv32i_decode::get_imm_j(uint32_t insn)
{
    //shift and or to get imm j
    int32_t imm_j = insn & 0x000FF000;//mnopqrst
    imm_j |= (insn & 0x00100000) >> (20-11); //l
    imm_j |= (insn & 0x00200000) >> 20; //k
    imm_j |= (insn & 0x00400000) >> 20; //j
    imm_j |= (insn & 0x00800000) >> 20; //i
    imm_j |= (insn & 0x01000000) >> 20; //h
    imm_j |= (insn & 0x02000000) >> 20; //g
    imm_j |= (insn & 0x04000000) >> 20; //f
    imm_j |= (insn & 0x08000000) >> 20; //e
    imm_j |= (insn & 0x10000000) >> 20; //d
    imm_j |= (insn & 0x20000000) >> 20; //c
    imm_j |= (insn & 0x40000000) >> 20; //b
    imm_j |= (insn & 0x80000000) >> (31-20); //a
    //used to sign extend
    if(imm_j & 0x00100000)
    {
        return imm_j | 0xFFE00000;
    }
    else
    {
        return imm_j;
    }
}
uint32_t rv32i_decode::get_funct3(uint32_t insn)
{
    //shift and to get funct3
    return (insn & 0x0007000) >> 12;
}
uint32_t rv32i_decode::get_funct7(uint32_t insn)
{
    //shift and to get funct7
    return (insn & 0x7F000000) >> 25;
}
string rv32i_decode::render_rtype(uint32_t insn, const char *mnemonic)
{
    //get rd
    uint32_t rd = get_rd(insn);
    //get rs1
    uint32_t rs1 = get_rs1(insn);
    //get rs2
    int32_t rs2 = get_rs2(insn);
    std::ostringstream os;
    //formate string and return it
    os << render_mnemonic(mnemonic) << render_reg(rd) << ","
       << render_reg(rs1) << "," << render_reg(rs2);
    return os.str();
}

string rv32i_decode::render_mnemonic(const std::string &m)
{
    //formate name of insn
    std::ostringstream os;
    //if insn is ebreak or ecall
    if(m == "ebreak" || m == "ecall")
    {
        os << left << m;
        return os.str();
    }
    else
    {
        //ever other insn name
       os << left << setw(mnemonic_width) << m;
        return os.str(); 
    }
}

uint32_t rv32i_decode::get_rs1(uint32_t insn)
{
    //shift and get rs1
    return (insn & 0x000F8000) >> 15;
}

uint32_t rv32i_decode::get_rs2(uint32_t insn)
{
    //shift and get rs2
    return (insn & 0x01F00000) >> 20;
}
string rv32i_decode::render_itype_alu(uint32_t insn, const char *mnemonic, int32_t imm_i)
{
    //get rd
    uint32_t rd = get_rd(insn);
    //get rs1
    int32_t rs1 = get_rs1(insn);
    std::ostringstream os;
    //formate string and return it
    os << render_mnemonic(mnemonic) << render_reg(rd) << ","
       << render_reg(rs1) << "," << imm_i;
    return os.str();

}
string rv32i_decode::render_itype_load(uint32_t insn, const char *mnemonic)
{
    //get rd
    uint32_t rd = get_rd(insn);
    //get rs1
    uint32_t rs1 = get_rs1(insn);
    //get imm i
    int32_t imm_i = get_imm_i(insn);
    std::ostringstream os;
    //formate string and return it
    os << render_mnemonic(mnemonic) << render_reg(rd) << ","
       << render_base_disp(rs1,imm_i);
    return os.str();
}
int32_t rv32i_decode::get_imm_i(uint32_t insn)
{
    //shift and to get immi
    int32_t immi = (insn & 0xfff00000) >> 20;
    //and for sign extened
    if(immi & 0x00000800)
    {
        return immi | 0xfffff000;
    }
    else
    {
        return immi;
    }
}
string rv32i_decode::render_reg(int r)
{
    //formate register by adding x#
    std::ostringstream os;
    os << "x" << r;
    return os.str();
}
string rv32i_decode::render_stype(uint32_t insn, const char *mnemonic)
{
    //get rs2
    int32_t rs2 = get_rs2(insn);
    //get rs1
    int32_t rs1 = get_rs1(insn);
    //get imm s
    int32_t imm_s = get_imm_s(insn);
    //formate string and return it
    std::ostringstream os;
    os << render_mnemonic(mnemonic) << render_reg(rs2) << ","
       << render_base_disp(rs1,imm_s);
    return os.str();
    
}
int32_t rv32i_decode::get_imm_s(uint32_t insn)
{
    //shift and get imm s
    int32_t imm_s = (insn & 0xfe000000) >> (25-5);
    imm_s |= (insn & 0x00000f80) >> (7-0);
    //for sign extended
    if (insn & 0x80000000)
    imm_s |= 0xfffff000; // sign-extend the left
    return imm_s;
}
string rv32i_decode::render_jalr(uint32_t insn)
{
    //get rd
    uint32_t rd = get_rd(insn);
    //get rs1
    uint32_t rs1 = get_rs1(insn);
    //imm i
    int32_t imm_i = get_imm_i(insn);
    //formate string and return it
    std::ostringstream os;
    os << render_mnemonic("jalr") << render_reg(rd) << ","
       << render_base_disp(rs1,imm_i);
    return os.str();
}
string rv32i_decode::render_ecall(uint32_t insn)
{
    //void insn since its not needed
    (void)insn;
    std::ostringstream os;
    //formate string and return it
    os << render_mnemonic("ecall");
    return os.str();
}
string rv32i_decode::render_ebreak(uint32_t insn)
{
    //void insn since its not needed
    (void)insn;
    std::ostringstream os;
    //formate string and return it
    os << render_mnemonic("ebreak");
    return os.str();
}
string rv32i_decode::render_csrrxi(uint32_t insn, const char *mnemonic)
{
    //get rd
    uint32_t rd = get_rd(insn);
    //get zimm
    int32_t zimm = get_rs1(insn);
    //get csr
    int32_t csr = get_imm_i(insn);
    std::ostringstream os;
    //formate string and return it
    os << render_mnemonic(mnemonic) << render_reg(rd) << ","
       << to_hex0x12((csr) & 0x0fff) << "," << zimm;
    return os.str();
}
string rv32i_decode::render_csrrx(uint32_t insn, const char *mnemonic)
{
    //get rd
    uint32_t rd = get_rd(insn);
    //get rs1
    int32_t rs1 = get_rs1(insn);
    //get csr
    int32_t csr = get_imm_i(insn);
    std::ostringstream os;
    //formate string and return it
    os << render_mnemonic(mnemonic) << render_reg(rd) << ","
       << hex::to_hex0x12((csr) & 0x0fff) << "," << render_reg(rs1);
    return os.str();
}
int32_t rv32i_decode::get_imm_b(uint32_t insn)
{
    //and shift to get imm b
    int32_t imm_b = (insn & 0x00000080) << 4;
    imm_b |= (insn & 0x00000f00) >> 7;
    imm_b |= (insn & 0x7E000000) >> 20;
    imm_b |= (insn & 0x80000000) >> 19;
    //and to sign extended if needed
    if(imm_b & 0x00001000)
    {
        return imm_b | 0xfffff000;
    }
    else
    {
        return imm_b;
    }
}
string rv32i_decode::render_btype(uint32_t addr, uint32_t insn, const char *mnemonic)
{
    //get rs1
    int32_t rs1 = get_rs1(insn);
    //get rs2
    int32_t rs2 = get_rs2(insn);
    //get imm b
    int32_t imm_b = get_imm_b(insn);
    std::ostringstream os;
    //formate string and return it
    os << render_mnemonic(mnemonic) << render_reg(rs1) << ","
       << render_reg(rs2) << "," << hex::to_hex0x32(addr + imm_b);
    return os.str();
}
string rv32i_decode::render_base_disp(uint32_t base, int32_t disp)
{
    //formate base disp and return disp(x#)
    std::ostringstream os;
    os << disp << "(" << render_reg(base) << ")";
    return os.str();
}
