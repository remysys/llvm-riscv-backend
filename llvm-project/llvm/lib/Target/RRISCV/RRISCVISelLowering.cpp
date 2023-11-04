#include "RRISCVISelLowering.h"

using namespace llvm;

RRISCVTargetLowering::RRISCVTargetLowering(const TargetMachine &TM,
                                     const RRISCVSubtarget &STI)
    : TargetLowering(TM) {}

SDValue RRISCVTargetLowering::LowerFormalArguments(
    SDValue Chain, CallingConv::ID CallConv, bool IsVarArg,
    const SmallVectorImpl<ISD::InputArg> &Ins, const SDLoc &DL,
    SelectionDAG &DAG, SmallVectorImpl<SDValue> &InVals) const {
  return Chain;
}

SDValue RRISCVTargetLowering::LowerReturn(SDValue Chain, CallingConv::ID CallConv,
                               bool IsVarArg,
                               const SmallVectorImpl<ISD::OutputArg> &Outs,
                               const SmallVectorImpl<SDValue> &OutVals,
                               const SDLoc &DL, SelectionDAG &DAG) const {
  return Chain;
}