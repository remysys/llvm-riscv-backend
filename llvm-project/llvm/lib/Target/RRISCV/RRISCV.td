include "llvm/Target/Target.td"
include "RRISCVRegisterInfo.td"

def : ProcessorModel<"generic-rrv32", NoSchedModel, []>;


def RRISCVInstrInfo : InstrInfo;

def RRISCV : Target {
  let InstructionSet = RRISCVInstrInfo;
}

