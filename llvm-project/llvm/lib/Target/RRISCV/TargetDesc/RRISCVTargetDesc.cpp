#include "RRISCVTargetDesc.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/ADT/None.h"
#include "RRISCVInstPrinter.h"

#define GET_INSTRINFO_MC_DESC
#define ENABLE_INSTR_PREDICATE_VERIFIER
#include "RRISCVGenInstrInfo.inc"

#define GET_REGINFO_MC_DESC
#include "RRISCVGenRegisterInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "RRISCVGenSubtargetInfo.inc"

using namespace llvm;

extern Target TheRRISCVTarget;

static MCAsmInfo *createRRISCVMCAsmInfo(MCRegisterInfo const &MRI,
                                     Triple const &TT,
                                     MCTargetOptions const &Options) {
  MCAsmInfo *x = new MCAsmInfo();
  return x;
}

static MCSubtargetInfo *createRRISCVMCSubtargetInfo(Triple const &TT,
                                                 StringRef CPU, StringRef FS) {
  return createRRISCVMCSubtargetInfoImpl(TT, CPU, CPU, FS);
}

static MCInstrInfo *createRRISCVMCInstrInfo() {
  MCInstrInfo *x = new MCInstrInfo();
  return x;
}

static MCRegisterInfo *createRRISCVMCRegisterInfo(Triple const &TT) {
  MCRegisterInfo *x = new MCRegisterInfo();
  return x;
}

static MCInstPrinter *createRRISCVInstPrinter(Triple const &T,
                                           unsigned SyntaxVariant,
                                           MCAsmInfo const &MAI,
                                           MCInstrInfo const &MII,
                                           MCRegisterInfo const &MRI) {
  return new RRISCVInstPrinter(MAI, MII, MRI);
}

extern "C" void LLVMInitializeRRISCVTargetMC() {
  TargetRegistry::RegisterMCRegInfo(TheRRISCVTarget, createRRISCVMCRegisterInfo);
  TargetRegistry::RegisterMCInstrInfo(TheRRISCVTarget, createRRISCVMCInstrInfo);
  TargetRegistry::RegisterMCSubtargetInfo(TheRRISCVTarget,
                                          createRRISCVMCSubtargetInfo);
  TargetRegistry::RegisterMCAsmInfo(TheRRISCVTarget, createRRISCVMCAsmInfo);
  TargetRegistry::RegisterMCInstPrinter(TheRRISCVTarget, createRRISCVInstPrinter);
}