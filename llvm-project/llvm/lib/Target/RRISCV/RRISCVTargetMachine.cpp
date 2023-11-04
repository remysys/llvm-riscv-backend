#include "RRISCVTargetMachine.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

extern Target TheRRISCVTarget;

extern "C" void LLVMInitializeRRISCVTarget() {
  RegisterTargetMachine<RRISCVTargetMachine> X(TheRRISCVTarget);
}

RRISCVTargetMachine::RRISCVTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                   StringRef FS, TargetOptions const &Options,
                   Optional<Reloc::Model> RM,
                   Optional<CodeModel::Model> CM, CodeGenOpt::Level OL,
                   bool JIT)
    : LLVMTargetMachine(T, "e-m:m-p:32:32-i8:8:32-i16:16:32-i64:64-n32-S64", TT,
                        CPU, FS, Options, Reloc::Static, CodeModel::Small, OL) {
  initAsmInfo();
}