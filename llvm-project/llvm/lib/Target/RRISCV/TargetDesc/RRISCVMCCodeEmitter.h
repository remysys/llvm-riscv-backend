#ifndef LLVM_LIB_TARGET_RRISCV_MCTARGETDESC_RRISCVMCCodeEmitter_H
#define LLVM_LIB_TARGET_RRISCV_MCTARGETDESC_RRISCVMCCodeEmitter_H

#include "llvm/MC/MCCodeEmitter.h"
using namespace llvm;

namespace llvm {
class MCInstrInfo;
class MCContext;
class MCInst;

class RRISCVMCCodeEmitter : public MCCodeEmitter {
public:
  RRISCVMCCodeEmitter(const MCInstrInfo &mcii, MCContext &Ctx) {}

  ~RRISCVMCCodeEmitter() override {}

  void encodeInstruction(const MCInst &MI, raw_ostream &OS,
                         SmallVectorImpl<MCFixup> &Fixups,
                         const MCSubtargetInfo &STI) const override;
};
} // namespace llvm

#endif // LLVM_LIB_TARGET_RRISCV_MCTARGETDESC_RRISCVMCCodeEmitter_H