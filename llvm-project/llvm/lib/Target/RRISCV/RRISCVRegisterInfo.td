let Namespace = "RRISCV" in {
  class RRISCVReg<string n> : Register<n>;
}

let Namespace = "RRISCV" in {
  def ZERO : RRISCVReg<"zero">,  DwarfRegNum<[0]>;
  def RA :   RRISCVReg<"ra">,    DwarfRegNum<[1]>;
  def SP :   RRISCVReg<"sp">,    DwarfRegNum<[2]>;
  def T0 :   RRISCVReg<"t0">,    DwarfRegNum<[5]>;
  def T1 :   RRISCVReg<"t1">,    DwarfRegNum<[6]>;
  def T2 :   RRISCVReg<"t2">,    DwarfRegNum<[7]>;
  def S0 :   RRISCVReg<"s0">,    DwarfRegNum<[8]>;
  def S1 :   RRISCVReg<"s1">,    DwarfRegNum<[9]>;
  def A0 :   RRISCVReg<"a0">,    DwarfRegNum<[10]>;
  def A1 :   RRISCVReg<"a1">,    DwarfRegNum<[11]>;
  def A2 :   RRISCVReg<"a2">,    DwarfRegNum<[12]>;
  def A3 :   RRISCVReg<"a3">,    DwarfRegNum<[13]>;
  def A4 :   RRISCVReg<"a4">,    DwarfRegNum<[14]>;
  def A5 :   RRISCVReg<"a5">,    DwarfRegNum<[15]>;
  def A6 :   RRISCVReg<"a6">,    DwarfRegNum<[16]>;
  def A7 :   RRISCVReg<"a7">,    DwarfRegNum<[17]>;
}

def GPR:RegisterClass<"RRISCV", [i32], 32, (add
  ZERO, RA, SP,
  T0, T1, T2,
  S0, S1,
  A0, A1, A2, A3, A4, A5, A6, A7)>;