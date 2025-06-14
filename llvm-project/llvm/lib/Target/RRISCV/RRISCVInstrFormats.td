class RRISCVInst<dag outs, dag ins, string asm, list<dag> pattern,
       InstrItinClass itin>: Instruction
{
  let Namespace = "RRISCV";

  let OutOperandList = outs;
  let InOperandList = ins;

  let AsmString = asm;
  let Pattern = pattern;
  let Itinerary = itin;

  let DecoderNamespace = "RRISCV";

  bits<32> Inst;
  bits<7> Opcode = 0;
  let Inst{6-0} = Opcode;
}

class InstI<bits<7> opcode, bits<3> funct3, dag outs, dag ins, string asm, list<dag> pattern,
  InstrItinClass itin> : RRISCVInst<outs, ins, asm, pattern, itin> {
  let Opcode = opcode;

  bits<5> rd;
  bits<5> rs1;
  bits<12> imm;

  let Inst{31-20} = imm;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = rd;
}

class InstR<bits<7> opcode, bits<7> funct7, bits<3> funct3, dag outs,
            dag ins, string asm, list<dag> pattern, InstrItinClass itin>
  : RRISCVInst<outs, ins, asm, pattern, itin> {
  let Opcode = opcode;

  bits<5> rd;
  bits<5> rs1;
  bits<5> rs2;

  let Inst{31-25} = funct7;
  let Inst{24-20} = rs2;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = rd;
}

class InstR4<bits<7> opcode, bits<2> funct2, bits<3> funct3, dag outs,
            dag ins, string asm, list<dag> pattern, InstrItinClass itin>
      : RRISCVInst<outs, ins, asm, pattern, itin> {
  let Opcode = opcode;
  bits<5> rs3;
  bits<5> rs2;
  bits<5> rs1;
  bits<5> rd;

  let Inst{31-27} = rs3;
  let Inst{26-25} = funct2;
  let Inst{24-20} = rs2;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = rd;
}

class InstU<bits<7> opcode, dag outs, dag ins, string asm, list<dag> pattern,
      InstrItinClass itin> : RRISCVInst<outs, ins, asm, pattern, itin> {
  let Opcode = opcode;

  bits<5> rd;
  bits<20> imm;

  let Inst{31-12} = imm;
  let Inst{11-7} = rd;
}

class InstB<bits<7> opcode, bits<3> funct3, dag outs, dag ins, string asm, list<dag> pattern,
      InstrItinClass itin> : RRISCVInst<outs, ins, asm, pattern, itin> {
  let Opcode = opcode;
  bits<5> rs2;
  bits<5> rs1;
  bits<12> imm12;

  let Inst{31} = imm12{11};
  let Inst{30-25} = imm12{9-4};
  let Inst{24-20} = rs2;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-8} = imm12{3-0};
  let Inst{7} = imm12{10};
}

class InstJ<bits<7> opcode, dag outs, dag ins, string asm, list<dag> pattern,
      InstrItinClass itin>: RRISCVInst<outs, ins, asm, pattern, itin> {
  let Opcode = opcode;
  bits<20> imm20;
  bits<5> rd;

  let Inst{31} = imm20{19};
  let Inst{30-21} = imm20{9-0};
  let Inst{20} = imm20{10};
  let Inst{19-12} = imm20{18-11};
  let Inst{11-7} = rd;
}

class InstS<bits<7> opcode, bits<3> funct3, dag outs, dag ins, string asm, list<dag> pattern,
  InstrItinClass itin> : RRISCVInst<outs, ins, asm, pattern, itin> {
  let Opcode = opcode;
  bits<5> rs1;
  bits<5> rs2;
  bits<12> imm;

  let Inst{31-25} = imm{11-5};
  let Inst{24-20} = rs2;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = imm{4-0};
}

class RRISCVPseudo<dag outs, dag ins, string asm, list<dag> pattern>
    : RRISCVInst<outs, ins, asm, pattern, IIAlu> {
  // let isPseudo = 1;
  let isCodeGenOnly = 1;
}