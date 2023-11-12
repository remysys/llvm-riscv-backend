#include "RRISCVISelLowering.h"

using namespace llvm;

RRISCVTargetLowering::RRISCVTargetLowering(const TargetMachine &TM,
                                           const RRISCVSubtarget &STI)
    : TargetLowering(TM) {
  setOperationAction(ISD::GlobalAddress, MVT::i32, Custom);
}

SDValue RRISCVTargetLowering::LowerFormalArguments(
    SDValue Chain, CallingConv::ID CallConv, bool IsVarArg,
    const SmallVectorImpl<ISD::InputArg> &Ins, const SDLoc &DL,
    SelectionDAG &DAG, SmallVectorImpl<SDValue> &InVals) const {
  return Chain;
}

SDValue
RRISCVTargetLowering::LowerReturn(SDValue Chain, CallingConv::ID CallConv,
                                  bool IsVarArg,
                                  const SmallVectorImpl<ISD::OutputArg> &Outs,
                                  const SmallVectorImpl<SDValue> &OutVals,
                                  const SDLoc &DL, SelectionDAG &DAG) const {
  return Chain;
}

SDValue RRISCVTargetLowering::LowerOperation(SDValue Op,
                                             SelectionDAG &DAG) const {
  switch (Op.getOpcode()) {
  case ISD::GlobalAddress:
    return lowerGlobalAddress(Op, DAG);
  }
  return SDValue();
}

SDValue RRISCVTargetLowering::lowerGlobalAddress(SDValue Op,
                                                 SelectionDAG &DAG) const {
  EVT Ty = Op.getValueType();
  GlobalAddressSDNode *N = cast<GlobalAddressSDNode>(Op);
  SDLoc DL(N);
  SDValue Hi = DAG.getTargetGlobalAddress(N->getGlobal(), DL, Ty, 0, 1);
  SDValue Lo = DAG.getTargetGlobalAddress(N->getGlobal(), DL, Ty, 0, 2);
  return DAG.getNode(ISD::ADD, DL, Ty, DAG.getNode(RRISCVISD::Hi, DL, Ty, Hi),
                     DAG.getNode(RRISCVISD::Lo, DL, Ty, Lo));
}

const char *RRISCVTargetLowering::getTargetNodeName(unsigned Opcode) const {
  switch (Opcode) {
  case RRISCVISD::Hi:
    return "RRISCVISD::Hi";
  case RRISCVISD::Lo:
    return "RRISCVISD::Lo";
  default:
    return NULL;
  }
}