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