include "RRISCVInstrFormats.td"

def imm12 : Operand<i32>, ImmLeaf<i32, [{return isInt<12>(Imm);}]>;
def imm20 : Operand<i32>, ImmLeaf<i32, [{return isInt<20>(Imm);}]>;
def imm32 : Operand<i32>, ImmLeaf<i32, [{return isInt<32>(Imm);}]>;

def mem : Operand<iPTR> {
  let MIOperandInfo = (ops GPR, imm12);
  let PrintMethod = "printMemOperand";  
}

def mem_stack : Operand<iPTR> {
  let MIOperandInfo = (ops GPR, imm12);
  let PrintMethod = "printMemStackOperand";
}

class ArithLogicI <string inst, SDNode node>:
      InstI<(outs GPR:$rd), (ins GPR:$rs1, imm12:$imm),
      !strconcat(inst, "\t$rd, $rs1, $imm"),
      [(set GPR:$rd, (node GPR:$rs1, imm12:$imm))],
      IIAlu>;

def ADDI : ArithLogicI<"addi", add>;
def ANDI : ArithLogicI<"andi", and>;
def ORI : ArithLogicI<"ori", or>;
def XORI : ArithLogicI<"xori", xor>;

class ArithLogicR <string inst, SDNode node>:
      InstI<(outs GPR:$rd), (ins GPR:$rs1, GPR:$rs2),
      !strconcat(inst, "\t$rd, $rs1, $rs2"),
      [(set GPR:$rd, (node GPR:$rs1, GPR:$rs2))],
      IIAlu>;

def ADD : ArithLogicR<"add", add>;
def MUL : ArithLogicR<"mul", mul>;
def DIV : ArithLogicR<"div", sdiv>;
def REM : ArithLogicR<"rem", srem>;
def AND : ArithLogicR<"and", and>;
def OR  : ArithLogicR<"or", or>;
def XOR : ArithLogicR<"xor", xor>;

def SLT : InstR<(outs GPR:$rd),(ins GPR:$rs1, GPR:$rs2),
            "slt \t$rd, $rs1, $rs2", [], IIAlu>;

def : Pat<(setgt GPR:$lhs, GPR:$rhs), (SLT GPR:$rhs, GPR:$lhs)>;
def : Pat<(setlt GPR:$lhs, GPR:$rhs), (SLT GPR:$lhs, GPR:$rhs)>;
def : Pat<(seteq GPR:$lhs, GPR:$rhs), (SLT (XOR GPR:$lhs, GPR:$rhs), 1)>;
def : Pat<(setne GPR:$lhs, GPR:$rhs), (SLT ZERO, (XOR GPR:$lhs, GPR:$rhs))>;
def : Pat<(setge GPR:$rs1, GPR:$rs2), (XORI (SLT GPR:$rs1, GPR:$rs2), 1)>;
def : Pat<(setle GPR:$rs1, GPR:$rs2), (XORI (SLT GPR:$rs2, GPR:$rs1), 1)>;

def LUI : InstU<(outs GPR:$rd), (ins imm20:$imm),
          "lui $rd, $imm", [], IIAlu>;

def AddrFI : ComplexPattern<iPTR, 2, "SelectAddrFI", [frameindex], [SDNPWantParent]>;

// def STOREFI : RRISCVInst<(outs), (ins GPR:$ra, mem:$addr), "sw \t$ra, $addr", [], IIAlu>;
// def STORE : RRISCVInst<(outs), (ins GPR:$ra, GPR:$rb), "sw \t$ra, 0($rb)", [], IIAlu>;


// def LOADFI : RRISCVInst<(outs GPR:$ra), (ins mem:$addr), "lw \t$ra, $addr", [], IIAlu>;
// def LOAD : RRISCVInst<(outs GPR:$ra), (ins GPR:$x), "lw \t$ra, 0($x)", [], IIAlu>;

def : Pat<(i32 imm12:$in),
          (ADDI ZERO, imm12:$in)>;

// def : Pat<(store GPR:$ra, AddrFI:$addr),
//           (STOREFI GPR:$ra, AddrFI:$addr)>;

// def : Pat<(store GPR:$x, GPR:$y),
//          (STORE GPR:$x, GPR:$y)>;

// NOTE: using Pat is equivalent to the following LOAD definition
// def LOAD : RRISCVInst<(outs GPR:$ra), (ins mem:$addr), "lw \t$ra, $addr",
//          [(set GPR:$ra, (load AddrFI:$addr))],
//          IIAlu>;
// def : Pat<(load AddrFI:$addr),
//          (LOADFI AddrFI:$addr)>;

// def : Pat<(load GPR:$x),
//          (LOAD GPR:$x)>;

def RRISCVRET : SDNode<"RRISCVISD::Ret", SDTNone,
                             [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

def JALR : InstI<(outs GPR:$rd),(ins GPR:$rs1, imm12:$imm12),
           "jalr $rd, ${imm12}(${rs1})", [],
           IIAlu>;

// def RET : InstI<(outs),(ins), "jalr zero, 0(ra)", [(RRISCVRET)], IIAlu>;
let isReturn=1, isTerminator=1, hasDelaySlot=1, isBarrier=1, hasCtrlDep=1 in
def RET : Pseudo<(outs), (ins), [(RRISCVRET)]>, PseudoInstExpansion<(JALR ZERO, RA, 0)>;


def SDT_Call : SDTypeProfile<0, 1, [SDTCisVT<0, iPTR>]>;

def RRISCVCall : SDNode<"RRISCVISD::Call", SDT_Call,
                             [SDNPHasChain, SDNPOutGlue, SDNPOptInGlue, SDNPVariadic]>;

/*
def CALL : InstI<(outs),(ins GPR:$rs1), "jalr ra, 0($rs1)", [(RRISCVCall GPR:$rs1)], IIAlu>;
def CALL : Pseudo<(outs), (ins GPR:$rs1), [(RRISCVCall GPR:$rs1)]>, PseudoInstExpansion<(JALR RA, GPR:$rs1, 0)> {
  let isCall = 1;
}
*/

def calltarget  : Operand<iPTR>;
def CALL : InstI<(outs),(ins calltarget:$rs1), "call\t$rs1", [], IIAlu> {
  let isCall = 1;
}
def : Pat<(RRISCVCall tglobaladdr:$rs1), (CALL calltarget:$rs1)>;
def : Pat<(RRISCVCall texternalsym:$rs1), (CALL calltarget:$rs1)>;

// for br

def brtarget : Operand<OtherVT>;

def J : InstJ<(outs),(ins brtarget:$imm12),
           "j ${imm12}", [],
           IIAlu> {
  let isTerminator = 1;
}

def : Pat<(br bb:$imm), (J brtarget:$imm)>;

// for brcond

def BLT : InstB<(outs),(ins GPR:$rs1, GPR:$rs2, brtarget:$imm), "blt \t$rs1, $rs2, $imm", [], IIAlu>;
def BNE : InstB<(outs),(ins GPR:$rs1, GPR:$rs2, brtarget:$imm), "bne \t$rs1, $rs2, $imm", [], IIAlu>;
def BEQ : InstB<(outs),(ins GPR:$rs1, GPR:$rs2, brtarget:$imm), "beq \t$rs1, $rs2, $imm", [], IIAlu>;

def : Pat<(brcond (i32 (setlt GPR:$lhs, GPR:$rhs)), bb:$dst), (BLT GPR:$lhs, GPR:$rhs, brtarget:$dst)>;
def : Pat<(brcond (i32 (setne GPR:$lhs, GPR:$rhs)), bb:$dst), (BNE GPR:$rhs, GPR:$lhs, brtarget:$dst)>;
def : Pat<(brcond (i32 (seteq GPR:$lhs, GPR:$rhs)), bb:$dst), (BEQ GPR:$rhs, GPR:$lhs, brtarget:$dst)>;
def : Pat<(brcond (i32 (setgt GPR:$lhs, GPR:$rhs)), bb:$dst), (BLT GPR:$rhs, GPR:$lhs, brtarget:$dst)>;

multiclass STORE<PatFrag op, string asm, DAGOperand ty> {
  def FI : InstS<(outs), (ins ty:$ra, mem:$addr), !strconcat(asm, "\t$ra, $addr"), [(op ty:$ra, AddrFI:$addr)], IIAlu>;
  def R : InstS<(outs), (ins ty:$ra, GPR:$rb), !strconcat(asm, "\t$ra, 0($rb)"), [(op ty:$ra, GPR:$rb)], IIAlu>;
}

defm STOREW:STORE<store, "sw", GPR>;
defm STOREH:STORE<truncstorei16, "sh", GPR>;
defm STOREB:STORE<truncstorei8, "sb", GPR>;
defm STOREF:STORE<store, "fsw", FPR>;
defm STORED:STORE<store, "fsd", FPR64>;

multiclass LOAD<PatFrag op, string asm, DAGOperand ty> {
  def FI : InstI<(outs ty:$ra), (ins mem:$addr), !strconcat(asm, "\t$ra, $addr"), [(set ty:$ra, (op AddrFI:$addr))], IIAlu>;
  def R : InstI<(outs ty:$ra), (ins GPR:$rb), !strconcat(asm, "\t$ra, 0($rb)"), [(set ty:$ra, (op GPR:$rb))], IIAlu>;
}

defm LOADW:LOAD<load, "lw", GPR>;
defm LOADH:LOAD<extloadi16, "lh", GPR>;
defm LOADSH:LOAD<sextloadi16, "lh", GPR>;
defm LOADZH:LOAD<zextloadi16, "lh", GPR>;
defm LOADB:LOAD<extloadi8, "lb", GPR>;
defm LOADSB:LOAD<sextloadi8, "lb", GPR>;
defm LOADZB:LOAD<zextloadi8, "lb", GPR>;
defm LOADF:LOAD<load, "flw", FPR>;
defm LOADFD:LOAD<load, "fld", FPR64>;

def LEA : InstI<(outs GPR:$rd),(ins calltarget:$rs1), "la\t$rd, $rs1", [], IIAlu>;
def LEA_STACK : InstI<(outs GPR:$rd),(ins mem_stack:$mem), "addi \t$rd, $mem", [(set GPR:$rd, AddrFI:$mem)], IIAlu>;


def LI : InstI<(outs GPR:$rd),(ins imm32:$rs1), "li\t$rd, $rs1", [], IIAlu>;
def : Pat<(i32 imm32:$in), (LI imm32:$in)>;


class ArithLogicF <string inst, SDNode node>:
      InstR<(outs FPR:$rd), (ins FPR:$rs1, FPR:$rs2),
      !strconcat(inst, "\t$rd, $rs1, $rs2"),
      [(set FPR:$rd, (node FPR:$rs1, FPR:$rs2))],
      IIAlu>;

def FADDS : ArithLogicF<"fadd.s", fadd>;

class FSETCC <string asm, PatFrag node>:
    InstR<(outs GPR:$rd),(ins FPR:$rs1, FPR:$rs2),
    !strconcat(asm, "\t$rd, $rs1, $rs2"),
    [(set GPR:$rd, (node FPR:$rs1, FPR:$rs2))], IIAlu>;

def FEQS:FSETCC<"feq.s", seteq>;
def FLTS:FSETCC<"flt.s", setlt>;
def FLES:FSETCC<"fle.s", setle>;

def : Pat<(setune FPR:$lhs, FPR:$rhs), (XORI (FEQS FPR:$lhs, FPR:$rhs), 1)>;
def : Pat<(setuge FPR:$lhs, FPR:$rhs), (XORI (FLTS FPR:$lhs, FPR:$rhs), 1)>;
def : Pat<(setugt FPR:$lhs, FPR:$rhs), (FLTS FPR:$rhs, FPR:$lhs)>;
def : Pat<(setule FPR:$lhs, FPR:$rhs), (FLES FPR:$lhs, FPR:$rhs)>;
def : Pat<(setult FPR:$lhs, FPR:$rhs), (FLTS FPR:$lhs, FPR:$rhs)>;
def : Pat<(setoeq FPR:$lhs, FPR:$rhs), (FEQS FPR:$lhs, FPR:$rhs)>;

def : Pat<(brcond GPR:$cond, bb:$dst), (BEQ GPR:$cond, (LI 1), brtarget:$dst)>;


def FCVTSD : InstR<(outs FPR:$rd), (ins FPR64:$rs1),
    "fcvt.s.d\t$rd, $rs1",
    [(set FPR:$rd, (fpround FPR64:$rs1))],
    IIAlu>;

def FCVTDS : InstR<(outs FPR64:$rd), (ins FPR:$rs1),
    "fcvt.d.s\t$rd, $rs1",
    [(set FPR64:$rd, (fpextend FPR:$rs1))],
    IIAlu>;

class ArithLogicF64 <string inst, SDNode node>:
    InstR<(outs FPR64:$rd), (ins FPR64:$rs1, FPR64:$rs2),
    !strconcat(inst, "\t$rd, $rs1, $rs2"),
    [(set FPR64:$rd, (node FPR64:$rs1, FPR64:$rs2))],
    IIAlu>;

def FADDD : ArithLogicF64<"fadd.d", fadd>;
