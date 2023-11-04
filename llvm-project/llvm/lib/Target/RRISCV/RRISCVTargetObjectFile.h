#ifndef LLVM_LIB_TARGET_RRISCV_RRISCVTARGETOBJECTFILE_H
#define LLVM_LIB_TARGET_RRISCV_RRISCVTARGETOBJECTFILE_H

#include <llvm/CodeGen/TargetLoweringObjectFileImpl.h>
#include <llvm/MC/MCContext.h>
#include <llvm/Target/TargetMachine.h>

namespace llvm {

class RRISCVTargetObjectFile : public TargetLoweringObjectFileELF {
public:
  void Initialize(MCContext &Ctx, TargetMachine const &TM) override;
};
} // namespace llvm

#endif // LLVM_LIB_TARGET_RRISCV_RRISCVTARGETOBJECTFILE_H