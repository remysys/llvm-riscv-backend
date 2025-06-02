#include "RRISCVISelLowering.h"
#include "RRISCVSubtarget.h"
#include "TargetDesc/RRISCVBaseInfo.h"
#include "TargetDesc/RRISCVTargetDesc.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAGNodes.h"
#include "llvm/CodeGen/TargetCallingConv.h"
#include <deque>

using namespace llvm;

RRISCVTargetLowering::RRISCVTargetLowering(const TargetMachine &TM,
                                           const RRISCVSubtarget &STI)
    : TargetLowering(TM), Subtarget(STI) {
  addRegisterClass(MVT::i32, &RRISCV::GPRRegClass);
  addRegisterClass(MVT::f32, &RRISCV::FPRRegClass);
  addRegisterClass(MVT::f64, &RRISCV::FPR64RegClass);
  setOperationAction(ISD::GlobalAddress, MVT::i32, Custom);
  setOperationAction(ISD::ConstantPool, MVT::i32, Custom);
  setOperationAction(ISD::Constant, MVT::i32, Custom);
  // expand br_cc to setcc and brcond instructions
  setOperationAction(ISD::BR_CC, MVT::i32, Expand);
  setOperationAction(ISD::BR_CC, MVT::f32, Expand);
  setOperationAction(ISD::BR_CC, MVT::f64, Expand);
  computeRegisterProperties(STI.getRegisterInfo());

  setTruncStoreAction(MVT::f64, MVT::f32, Expand);
  setLoadExtAction(ISD::EXTLOAD, MVT::f64, MVT::f32, Expand);

  setOperationAction(ISD::FMAXNUM, MVT::f32, Legal);
  setOperationAction(ISD::FMINNUM, MVT::f32, Legal);
}

#include "RRISCVGenCallingConv.inc"
void analyzeFormalArguments(const SmallVectorImpl<ISD::InputArg> &Args,
                            CCState &CCInfo) {
  unsigned NumArgs = Args.size();

  for (unsigned I = 0; I != NumArgs; ++I) {
    MVT ArgVT = Args[I].VT;
    ISD::ArgFlagsTy ArgFlags = Args[I].Flags;
    RRISCVCC(I, ArgVT, ArgVT, CCValAssign::Full, ArgFlags, CCInfo);
  }
}

void analyzeCallOperands(const SmallVectorImpl<ISD::OutputArg> &Args,
                         CCState &CCInfo) {
  unsigned NumArgs = Args.size();

  for (unsigned I = 0; I != NumArgs; ++I) {
    MVT ArgVT = Args[I].VT;
    ISD::ArgFlagsTy ArgFlags = Args[I].Flags;
    RRISCVCC(I, ArgVT, ArgVT, CCValAssign::Full, ArgFlags, CCInfo);
  }
}

void analyzeCallResult(const SmallVectorImpl<ISD::InputArg> &Args,
                       CCState &CCInfo) {
  unsigned NumArgs = Args.size();

  for (unsigned I = 0; I != NumArgs; ++I) {
    MVT ArgVT = Args[I].VT;
    ISD::ArgFlagsTy ArgFlags = Args[I].Flags;
    RRISCVCC(I, ArgVT, ArgVT, CCValAssign::Full, ArgFlags, CCInfo);
  }
}

void analyzeReturn(const SmallVectorImpl<ISD::OutputArg> &Args,
                   CCState &CCInfo) {
  unsigned NumArgs = Args.size();

  for (unsigned I = 0; I != NumArgs; ++I) {
    MVT ArgVT = Args[I].VT;
    ISD::ArgFlagsTy ArgFlags = Args[I].Flags;
    RRISCVCC(I, ArgVT, ArgVT, CCValAssign::Full, ArgFlags, CCInfo);
  }
}

SDValue RRISCVTargetLowering::LowerFormalArguments(
    SDValue Chain, CallingConv::ID CallConv, bool IsVarArg,
    const SmallVectorImpl<ISD::InputArg> &Ins, const SDLoc &DL,
    SelectionDAG &DAG, SmallVectorImpl<SDValue> &InVals) const {
  MachineFunction &MF = DAG.getMachineFunction();

  MachineFrameInfo &MFI = MF.getFrameInfo();

  SmallVector<CCValAssign, 16> ArgLocs;
  CCState CCInfo(CallConv, IsVarArg, DAG.getMachineFunction(), ArgLocs,
                 *DAG.getContext());

  analyzeFormalArguments(Ins, CCInfo);

  for (unsigned i = 0, e = ArgLocs.size(); i != e; ++i) {
    CCValAssign &VA = ArgLocs[i];
    MVT RegVT = VA.getLocVT();
    EVT ValVT = VA.getValVT();
    if (VA.isRegLoc()) {
      MVT RegVT = VA.getLocVT();
      unsigned ArgReg = VA.getLocReg();
      const TargetRegisterClass *RC = getRegClassFor(RegVT);

      unsigned VReg = MF.getRegInfo().createVirtualRegister(RC);
      MF.getRegInfo().addLiveIn(ArgReg, VReg);
      SDValue ArgValue = DAG.getCopyFromReg(Chain, DL, VReg, RegVT);
      InVals.push_back(ArgValue);
    } else {
      MVT LocVT = VA.getLocVT();
      int FI = MFI.CreateFixedObject(ValVT.getSizeInBits() / 8,
                                     VA.getLocMemOffset(), true);

      SDValue FIN = DAG.getFrameIndex(FI, getPointerTy(DAG.getDataLayout()));
      SDValue Load = DAG.getLoad(
          LocVT, DL, Chain, FIN,
          MachinePointerInfo::getFixedStack(DAG.getMachineFunction(), FI));
      InVals.push_back(Load);
    }
  }
  return Chain;
}

SDValue
RRISCVTargetLowering::LowerReturn(SDValue Chain, CallingConv::ID CallConv,
                                  bool IsVarArg,
                                  const SmallVectorImpl<ISD::OutputArg> &Outs,
                                  const SmallVectorImpl<SDValue> &OutVals,
                                  const SDLoc &DL, SelectionDAG &DAG) const {
  SmallVector<CCValAssign, 2> RVLocs;
  CCState CCInfo(CallConv, IsVarArg, DAG.getMachineFunction(), RVLocs,
                 *DAG.getContext());
  analyzeReturn(Outs, CCInfo);
  SDValue Glue;
  SmallVector<SDValue, 4> Ops(1, Chain);
  for (unsigned i = 0, e = RVLocs.size(); i != e; ++i) {
    CCValAssign &VA = RVLocs[i];
    assert(VA.isRegLoc());
    unsigned RVReg = VA.getLocReg();
    Chain = DAG.getCopyToReg(Chain, DL, RVReg, OutVals[i], Glue);
    Glue = Chain.getValue(1);
    Ops.push_back(DAG.getRegister(VA.getLocReg(), VA.getLocVT()));
  }

  Ops[0] = Chain;
  if (Glue.getNode()) {
    Ops.push_back(Glue);
  }
  return DAG.getNode(RRISCVISD::Ret, DL, MVT::Other, Ops);
}

SDValue RRISCVTargetLowering::LowerOperation(SDValue Op,
                                             SelectionDAG &DAG) const {
  switch (Op.getOpcode()) {
  case ISD::GlobalAddress:
    return lowerGlobalAddress(Op, DAG);
  case ISD::ConstantPool:
    return lowerConstantPool(Op, DAG);
  case ISD::Constant:
    return lowerConstant(Op, DAG);
  }
  return SDValue();
}

SDValue RRISCVTargetLowering::lowerGlobalAddress(SDValue Op,
                                                 SelectionDAG &DAG) const {
  EVT Ty = Op.getValueType();
  GlobalAddressSDNode *N = cast<GlobalAddressSDNode>(Op);
  int64_t Offset = N->getOffset();
  SDLoc DL(N);
  SDValue Hi =
      DAG.getTargetGlobalAddress(N->getGlobal(), DL, Ty, 0, RRISCVII::MO_HI);
  SDValue Lo =
      DAG.getTargetGlobalAddress(N->getGlobal(), DL, Ty, 0, RRISCVII::MO_LO);

  SDValue MNHi = SDValue(DAG.getMachineNode(RRISCV::LUI, DL, Ty, Hi), 0);

  SDValue Addr = SDValue(DAG.getMachineNode(RRISCV::ADDI, DL, Ty, MNHi, Lo), 0);
  if (Offset != 0) {
    return DAG.getNode(ISD::ADD, DL, Ty, Addr, DAG.getConstant(Offset, DL, Ty));
  }
  return Addr;
}

const char *RRISCVTargetLowering::getTargetNodeName(unsigned Opcode) const {
  switch (Opcode) {
  case RRISCVISD::Hi:
    return "RRISCVISD::Hi";
  case RRISCVISD::Lo:
    return "RRISCVISD::Lo";
  case RRISCVISD::Ret:
    return "RRISCVISD::Ret";
  case RRISCVISD::Call:
    return "RRISCVISD::Call";
  default:
    return NULL;
  }
}

SDValue
RRISCVTargetLowering::LowerCall(TargetLowering::CallLoweringInfo &CLI,
                                SmallVectorImpl<SDValue> &InVals) const {
  SelectionDAG &DAG = CLI.DAG;
  SDLoc DL = CLI.DL;
  SDValue Chain = CLI.Chain;
  SDValue Callee = CLI.Callee;

  CallingConv::ID CallConv = CLI.CallConv;
  bool IsVarArg = CLI.IsVarArg;

  MachineFunction &MF = DAG.getMachineFunction();
  MachineFrameInfo &MFI = MF.getFrameInfo();

  SmallVectorImpl<ISD::OutputArg> &Outs = CLI.Outs;
  SmallVectorImpl<ISD::InputArg> &Ins = CLI.Ins;
  SmallVectorImpl<SDValue> &OutVals = CLI.OutVals;

  SmallVector<CCValAssign, 2> ArgLocs;
  CCState CCInfo(CallConv, IsVarArg, DAG.getMachineFunction(), ArgLocs,
                 *DAG.getContext());
  analyzeCallOperands(Outs, CCInfo);
  std::deque<std::pair<unsigned, SDValue>> RegsToPass;

  for (unsigned i = 0, e = ArgLocs.size(); i != e; ++i) {
    CCValAssign &VA = ArgLocs[i];
    if (VA.isRegLoc()) {
      RegsToPass.push_back(std::make_pair(VA.getLocReg(), OutVals[i]));
    } else if (VA.isMemLoc()) {
      SDValue StackPtr = DAG.getCopyFromReg(Chain, DL, RRISCV::SP,
                                            getPointerTy(DAG.getDataLayout()));

      SDValue PtrOff =
          DAG.getNode(ISD::ADD, DL, getPointerTy(DAG.getDataLayout()), StackPtr,
                      DAG.getIntPtrConstant(VA.getLocMemOffset(), DL));
      Chain = DAG.getStore(Chain, DL, OutVals[i], PtrOff, MachinePointerInfo());

      MFI.setOffsetAdjustment(VA.getLocMemOffset() + 4);
    }
  }

  if (GlobalAddressSDNode *N = dyn_cast<GlobalAddressSDNode>(Callee)) {
    EVT Ty = getPointerTy(DAG.getDataLayout());
    SDLoc DL(N);
    SDValue Hi =
        DAG.getTargetGlobalAddress(N->getGlobal(), DL, Ty, 0, RRISCVII::MO_HI);
    SDValue Lo =
        DAG.getTargetGlobalAddress(N->getGlobal(), DL, Ty, 0, RRISCVII::MO_LO);

    SDValue MNHi = SDValue(DAG.getMachineNode(RRISCV::LUI, DL, Ty, Hi), 0);

    Callee = SDValue(DAG.getMachineNode(RRISCV::ADDI, DL, Ty, MNHi, Lo), 0);

  } else if (ExternalSymbolSDNode *S = dyn_cast<ExternalSymbolSDNode>(Callee)) {
    const char *Sym = S->getSymbol();
    EVT Ty = getPointerTy(DAG.getDataLayout());
    SDValue Hi = DAG.getTargetExternalSymbol(
        Sym, getPointerTy(DAG.getDataLayout()), RRISCVII::MO_HI);
    SDValue Lo = DAG.getTargetExternalSymbol(
        Sym, getPointerTy(DAG.getDataLayout()), RRISCVII::MO_LO);
    SDValue MNHi = SDValue(DAG.getMachineNode(RRISCV::LUI, DL, Ty, Hi), 0);
    Callee = SDValue(DAG.getMachineNode(RRISCV::ADDI, DL, Ty, MNHi, Lo), 0);
  }

  SmallVector<SDValue, 8> Ops(1, Chain);
  Ops.push_back(Callee);
  SDValue Glue;
  for (unsigned i = 0, e = RegsToPass.size(); i != e; ++i) {
    Chain = DAG.getCopyToReg(Chain, DL, RegsToPass[i].first,
                             RegsToPass[i].second, Glue);
    Glue = Chain.getValue(1);
    Ops.push_back(DAG.getRegister(RegsToPass[i].first,
                                  RegsToPass[i].second.getValueType()));
  }

  const TargetRegisterInfo *TRI = Subtarget.getRegisterInfo();
  const uint32_t *Mask =
      TRI->getCallPreservedMask(DAG.getMachineFunction(), CallConv);
  Ops.push_back(DAG.getRegisterMask(Mask));

  if (Glue.getNode()) {
    Ops.push_back(Glue);
  }

  SDVTList NodeTys = DAG.getVTList(MVT::Other, MVT::Glue);
  Chain = DAG.getNode(RRISCVISD::Call, DL, NodeTys, Ops);

  {
    SDValue Glue = Chain.getValue(1);
    SmallVector<CCValAssign, 2> RVLocs;
    CCState CCInfo(CallConv, IsVarArg, DAG.getMachineFunction(), RVLocs,
                   *DAG.getContext());
    analyzeCallResult(Ins, CCInfo);

    for (unsigned i = 0, e = RVLocs.size(); i != e; ++i) {
      CCValAssign &VA = RVLocs[i];
      assert(VA.isRegLoc());
      unsigned RVReg = VA.getLocReg();
      SDValue Val =
          DAG.getCopyFromReg(Chain, DL, RVReg, RVLocs[i].getLocVT(), Glue);
      Chain = Val.getValue(1);
      Glue = Val.getValue(2);
      InVals.push_back(Val);
    }
  }

  return Chain;
}

SDValue RRISCVTargetLowering::lowerConstantPool(SDValue Op,
                                                SelectionDAG &DAG) const {
  EVT Ty = Op.getValueType();
  ConstantPoolSDNode *N = cast<ConstantPoolSDNode>(Op);
  SDLoc DL(N);

  SDValue Hi = DAG.getTargetConstantPool(N->getConstVal(), Ty, N->getAlign(),
                                         N->getOffset(), RRISCVII::MO_HI);
  SDValue Lo = DAG.getTargetConstantPool(N->getConstVal(), Ty, N->getAlign(),
                                         N->getOffset(), RRISCVII::MO_LO);
  SDValue MNHi = SDValue(DAG.getMachineNode(RRISCV::LUI, DL, Ty, Hi), 0);
  SDValue Addr = SDValue(DAG.getMachineNode(RRISCV::ADDI, DL, Ty, MNHi, Lo), 0);

  return Addr;
}

/*
#define RISCV_CONST_HIGH_PART(VALUE) (((VALUE) + (1 << 11)) & 0xfffff000)
#define RISCV_CONST_LOW_PART(VALUE) ((VALUE)-RISCV_CONST_HIGH_PART(VALUE))
*/

#define RISCV_CONST_HIGH_PART(VALUE) (VALUE & 0xfffff000)
#define RISCV_CONST_LOW_PART(VALUE)  (VALUE & 0x00000fff)

SDValue RRISCVTargetLowering::lowerConstant(SDValue Op,
                                            SelectionDAG &DAG) const {
  SDLoc DL(Op);
  EVT VT = Op.getValueType();

  int32_t Imm = cast<ConstantSDNode>(Op)->getSExtValue();

  if (isInt<12>(Imm)) {
    SDValue SDImm = DAG.getTargetConstant(Imm, DL, VT);
    SDValue Op =
        SDValue(DAG.getMachineNode(RRISCV::ADDI, DL, VT,
                                   DAG.getRegister(RRISCV::ZERO, VT), SDImm),
                0);
    return Op;
  } else {
    uint32_t Hi = RISCV_CONST_HIGH_PART(Imm);
    uint32_t Lo = RISCV_CONST_LOW_PART(Imm);
    SDValue SDImmHi = DAG.getTargetConstant(Hi >> 12, DL, VT);
    SDValue SDImmLo = DAG.getTargetConstant(Lo, DL, VT);
    SDValue LuiOp =
        SDValue(DAG.getMachineNode(RRISCV::LUI, DL, VT, SDImmHi), 0);
    SDValue AddiOp =
        SDValue(DAG.getMachineNode(RRISCV::ADDI, DL, VT, LuiOp, SDImmLo), 0);
    return AddiOp;
  }
  return SDValue();
}