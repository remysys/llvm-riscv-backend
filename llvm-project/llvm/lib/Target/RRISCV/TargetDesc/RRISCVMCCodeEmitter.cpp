#include "RRISCVMCCodeEmitter.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

void RRISCVMCCodeEmitter::encodeInstruction(const MCInst &MI, raw_ostream &OS,
                                            SmallVectorImpl<MCFixup> &Fixups,
                                            const MCSubtargetInfo &STI) const {
  errs() << MI << "\n";
  uint32_t Binary = getBinaryCodeForInstr(MI, Fixups, STI);

  for (int i = 0; i < 4; ++i) {
    unsigned Shift = i * 8;
    OS << (char)((Binary >> Shift) & 0xff);
  }
}

unsigned
RRISCVMCCodeEmitter::getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                                       SmallVectorImpl<MCFixup> &Fixups,
                                       const MCSubtargetInfo &STI) const {
  if (MO.isReg()) {
    unsigned Reg = MO.getReg();
    unsigned RegNo = Ctx.getRegisterInfo()->getEncodingValue(Reg);
    return RegNo;
  } else if (MO.isImm()) {
    return static_cast<unsigned>(MO.getImm());
  }
  // MO must be an Expr.
  assert(MO.isExpr());
  return 0;
}

#include "RRISCVGenMCCodeEmitter.inc"