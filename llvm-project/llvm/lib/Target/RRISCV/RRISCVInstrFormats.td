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
}

class InstI<dag outs, dag ins, string asm, list<dag> pattern,
      InstrItinClass itin>: RRISCVInst<outs, ins, asm, pattern, itin> {}

class InstR<dag outs, dag ins, string asm, list<dag> pattern,
      InstrItinClass itin>: RRISCVInst<outs, ins, asm, pattern, itin> {}

class InstU<dag outs, dag ins, string asm, list<dag> pattern,
      InstrItinClass itin>: RRISCVInst<outs, ins, asm, pattern, itin> {}

class InstB<dag outs, dag ins, string asm, list<dag> pattern,
      InstrItinClass itin>: RRISCVInst<outs, ins, asm, pattern, itin>{}

class InstJ<dag outs, dag ins, string asm, list<dag> pattern,
      InstrItinClass itin>: RRISCVInst<outs, ins, asm, pattern, itin>{}

class InstS<dag outs, dag ins, string asm, list<dag> pattern,
      InstrItinClass itin>: RRISCVInst<outs, ins, asm, pattern, itin>{}

class Pseudo<dag outs, dag ins, list<dag> pattern>
    : RRISCVInst<outs, ins, "", pattern, IIAlu> {
  let isPseudo = 1;
  let isCodeGenOnly = 1;
}