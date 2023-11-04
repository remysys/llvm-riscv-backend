
#ifndef LLVM_LIB_TARGET_RRISCV_RRISCVTARGETMACHINE_H
#define LLVM_LIB_TARGET_RRISCV_RRISCVTARGETMACHINE_H

#include "llvm/Target/TargetMachine.h"

namespace llvm {
class RRISCVTargetMachine : public LLVMTargetMachine {
public:
  RRISCVTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                   StringRef FS, TargetOptions const &Options,
                   Optional<Reloc::Model> RM,
                   Optional<CodeModel::Model> CM, CodeGenOpt::Level OL,
                   bool JIT);

  ~RRISCVTargetMachine() {}
};
} // namespace llvm

#endif // LLVM_LIB_TARGET_RRISCV_RRISCVTARGETMACHINE_H