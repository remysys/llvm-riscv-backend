#include "RRISCVAsmBackend.h"
#include "RRISCVELFObjectWriter.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCFixupKindInfo.h"

using namespace llvm;

const MCFixupKindInfo &
RRISCVAsmBackend::getFixupKindInfo(MCFixupKind Kind) const {

  const static MCFixupKindInfo Infos[RRISCV::NumTargetFixupKinds] = {
      // name offset bits flags
      {"fixup_riscv_hi20", 12, 20, 0},
      {"fixup_riscv_lo12_i", 20, 12, 0},
  };

  if (Kind < FirstTargetFixupKind)
    return MCAsmBackend::getFixupKindInfo(Kind);

  assert(unsigned(Kind - FirstTargetFixupKind) < getNumFixupKinds() &&
         "invalid kind!");
  return Infos[Kind - FirstTargetFixupKind];
}

static std::unique_ptr<MCObjectTargetWriter>
createRRISCVELFObjectWriter(const Triple &TT) {
  uint8_t OSABI = MCELFObjectTargetWriter::getOSABI(TT.getOS());
  bool IsN64 = false;
  bool HasRelocationAddend = false;
  return std::make_unique<RRISCVELFObjectWriter>(OSABI, HasRelocationAddend,
                                                 IsN64);
}

std::unique_ptr<MCObjectTargetWriter>
RRISCVAsmBackend::createObjectTargetWriter() const {
  return createRRISCVELFObjectWriter(TheTriple);
}