#include "llvm/IR/Module.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;
Target TheRRISCVTarget;

extern "C" void LLVMInitializeRRISCVTargetInfo() {
  RegisterTarget<Triple::rriscv, true> X(TheRRISCVTarget, "rriscv", "Remy's RISC-V backend",
                                      "RRISCV");
}