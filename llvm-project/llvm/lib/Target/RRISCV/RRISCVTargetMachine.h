
#ifndef LLVM_LIB_TARGET_RRISCV_RRISCVTARGETMACHINE_H
#define LLVM_LIB_TARGET_RRISCV_RRISCVTARGETMACHINE_H

#include "llvm/Target/TargetMachine.h"
#include "RRISCVTargetObjectFile.h"
#include "RRISCVSubtarget.h"

namespace llvm {
class RRISCVTargetMachine : public LLVMTargetMachine {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  std::unique_ptr<RRISCVSubtarget> Subtarget;
public:
  RRISCVTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                   StringRef FS, TargetOptions const &Options,
                   Optional<Reloc::Model> RM,
                   Optional<CodeModel::Model> CM, CodeGenOpt::Level OL,
                   bool JIT);

  ~RRISCVTargetMachine() {}

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }

  const RRISCVSubtarget *getSubtargetImpl(const Function &F) const override;
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
};
} // namespace llvm

#endif // LLVM_LIB_TARGET_RRISCV_RRISCVTARGETMACHINE_H