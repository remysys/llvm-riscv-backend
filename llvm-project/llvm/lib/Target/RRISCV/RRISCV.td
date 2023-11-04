include "llvm/Target/Target.td"

def : ProcessorModel<"generic-rrv32", NoSchedModel, []>;

def RRISCV : Target {}

