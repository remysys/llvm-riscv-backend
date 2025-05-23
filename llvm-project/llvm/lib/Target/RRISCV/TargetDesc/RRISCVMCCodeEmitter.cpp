#include "RRISCVMCCodeEmitter.h"

using namespace llvm;

void RRISCVMCCodeEmitter::encodeInstruction(const MCInst &MI, raw_ostream &OS,
                                            SmallVectorImpl<MCFixup> &Fixups,
                                            const MCSubtargetInfo &STI) const {}