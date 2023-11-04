#include "RRISCVTargetObjectFile.h"

using namespace llvm;

void RRISCVTargetObjectFile::Initialize(MCContext &Ctx, TargetMachine const &TM) {
  TargetLoweringObjectFileELF::Initialize(Ctx, TM);
  InitializeELF(false);
}