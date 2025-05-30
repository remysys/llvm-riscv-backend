#ifndef LLVM_LIB_TARGET_RRISCV_MCTARGETDESC_RRISCVMCCodeEmitter_H
#define LLVM_LIB_TARGET_RRISCV_MCTARGETDESC_RRISCVMCCodeEmitter_H

#include "RRISCVTargetDesc.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCInst.h"

using namespace llvm;

namespace llvm {
class MCInstrInfo;
class MCContext;
class MCInst;

class RRISCVMCCodeEmitter : public MCCodeEmitter {
  MCContext &Ctx;

public:
  RRISCVMCCodeEmitter(const MCInstrInfo &mcii, MCContext &Ctx) : Ctx(Ctx) {}

  ~RRISCVMCCodeEmitter() override {}

  void encodeInstruction(const MCInst &MI, raw_ostream &OS,
                         SmallVectorImpl<MCFixup> &Fixups,
                         const MCSubtargetInfo &STI) const override;
  // autogen in "RRISCVGenMCCodeEmitter.inc"
  uint64_t getBinaryCodeForInstr(const MCInst &MI,
                                 SmallVectorImpl<MCFixup> &Fixups,
                                 const MCSubtargetInfo &STI) const;
  // autogen in "RRISCVGenMCCodeEmitter.inc"
  unsigned getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                             SmallVectorImpl<MCFixup> &Fixups,
                             const MCSubtargetInfo &STI) const;
};
} // namespace llvm

#endif // LLVM_LIB_TARGET_RRISCV_MCTARGETDESC_RRISCVMCCodeEmitter_H