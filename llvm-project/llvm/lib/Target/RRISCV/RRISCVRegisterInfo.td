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

  def FT0:   RRISCVReg<"ft0">,    DwarfRegNum<[0]>;
  def FT1:   RRISCVReg<"ft1">,    DwarfRegNum<[1]>;
  def FT2:   RRISCVReg<"ft2">,    DwarfRegNum<[2]>;
  def FT3:   RRISCVReg<"ft3">,    DwarfRegNum<[3]>;
  def FT4:   RRISCVReg<"ft4">,    DwarfRegNum<[4]>;
  def FT5:   RRISCVReg<"ft5">,    DwarfRegNum<[5]>;
  def FT6:   RRISCVReg<"ft6">,    DwarfRegNum<[6]>;
  def FT7:   RRISCVReg<"ft7">,    DwarfRegNum<[7]>;
  def FS0:   RRISCVReg<"fs0">,    DwarfRegNum<[8]>;
  def FS1:   RRISCVReg<"fs1">,    DwarfRegNum<[9]>;
  def FA0:   RRISCVReg<"fa0">,    DwarfRegNum<[10]>;
  def FA1:   RRISCVReg<"fa1">,    DwarfRegNum<[11]>;
  def FA2:   RRISCVReg<"fa2">,    DwarfRegNum<[12]>;
  def FA3:   RRISCVReg<"fa3">,    DwarfRegNum<[13]>;
  def FA4:   RRISCVReg<"fa4">,    DwarfRegNum<[14]>;
  def FA5:   RRISCVReg<"fa5">,    DwarfRegNum<[15]>;
  def FA6:   RRISCVReg<"fa6">,    DwarfRegNum<[16]>;
  def FA7:   RRISCVReg<"fa7">,    DwarfRegNum<[17]>;
  def FS2:   RRISCVReg<"fs2">,    DwarfRegNum<[18]>;
  def FS3:   RRISCVReg<"fs3">,    DwarfRegNum<[19]>;
  def FS4:   RRISCVReg<"fs4">,    DwarfRegNum<[20]>;
  def FS5:   RRISCVReg<"fs5">,    DwarfRegNum<[21]>;
  def FS6:   RRISCVReg<"fs6">,    DwarfRegNum<[22]>;
  def FS7:   RRISCVReg<"fs7">,    DwarfRegNum<[23]>;
  def FS8:   RRISCVReg<"fs8">,    DwarfRegNum<[24]>;
  def FS9:   RRISCVReg<"fs9">,    DwarfRegNum<[25]>;
  def FS10:  RRISCVReg<"fs10">,   DwarfRegNum<[26]>;
  def FS11:  RRISCVReg<"fs11">,   DwarfRegNum<[27]>;
  def FT8:   RRISCVReg<"ft8">,    DwarfRegNum<[28]>;
  def FT9:   RRISCVReg<"ft9">,    DwarfRegNum<[29]>;
  def FT10:  RRISCVReg<"ft10">,   DwarfRegNum<[30]>;
  def FT11:  RRISCVReg<"ft11">,   DwarfRegNum<[31]>;

}

def GPR:RegisterClass<"RRISCV", [i32], 32, (add
  ZERO, RA, SP,
  T0, T1, T2,
  S0, S1,
  A0, A1, A2, A3, A4, A5, A6, A7)>;

def FPR:RegisterClass<"RRISCV", [f32], 32, (add
  FT0, FT1, FT2, FT3, FT4, FT5, FT6, FT7,
  FS0, FS1,
  FA0, FA1, FA2, FA3, FA4, FA5, FA6, FA7,
  FS2, FS3, FS4, FS5, FS6, FS7, FS8, FS9, FS10, FS11,
  FT8, FT9, FT10, FT11)>;