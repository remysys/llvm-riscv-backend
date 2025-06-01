#include "RRISCVMCCodeEmitter.h"
#include "RRISCVFixupKinds.h"
#include "RRISCVMCExpr.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/EndianStream.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

void RRISCVMCCodeEmitter::encodeInstruction(const MCInst &MI, raw_ostream &OS,
                                            SmallVectorImpl<MCFixup> &Fixups,
                                            const MCSubtargetInfo &STI) const {
  errs() << MI << "\n";
  uint32_t Binary = getBinaryCodeForInstr(MI, Fixups, STI);

  /*
  for (int i = 0; i < 4; ++i) {
    unsigned Shift = i * 8;
    OS << (char)((Binary >> Shift) & 0xff);
  } */

  // write it out (little-endian).
  support::endian::write(OS, Binary, support::little);
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

  const MCExpr *Expr = MO.getExpr();
  const RRISCVMCExpr *RRISCVExpr = cast<RRISCVMCExpr>(Expr);
  RRISCV::Fixups FixupKind = RRISCV::Fixups::fixup_riscv_invalid;
  switch (RRISCVExpr->getKind()) {
  case RRISCVMCExpr::TEK_HI:
    FixupKind = RRISCV::Fixups::fixup_riscv_hi20;
    break;
  case RRISCVMCExpr::TEK_LO:
    FixupKind = RRISCV::Fixups::fixup_riscv_lo12_i;
    break;
  case RRISCVMCExpr::TEK_JAL:
    FixupKind = RRISCV::Fixups::fixup_riscv_jal;
    break;
  case RRISCVMCExpr::TEK_BRANCH:
    FixupKind = RRISCV::Fixups::fixup_riscv_branch;
    break;
  }

  Fixups.push_back(MCFixup::create(0, Expr, MCFixupKind(FixupKind)));
  return 0;
}

#include "RRISCVGenMCCodeEmitter.inc"