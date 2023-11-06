#include "RRISCVInstrInfo.h"

#define GET_INSTRINFO_CTOR_DTOR
#include "RRISCVGenInstrInfo.inc"

using namespace llvm;

RRISCVInstrInfo::RRISCVInstrInfo() : RRISCVGenInstrInfo() {}