
class RRISCVReg<bits<5> Enc, string n> : Register<n> {
  let HWEncoding{4-0} = Enc;
  let Namespace = "RRISCV";
}

def ZERO : RRISCVReg<0, "zero">,   DwarfRegNum<[0]>;
def RA :   RRISCVReg<1, "ra">,     DwarfRegNum<[1]>;
def SP :   RRISCVReg<2, "sp">,     DwarfRegNum<[2]>;
def T0 :   RRISCVReg<5, "t0">,     DwarfRegNum<[5]>;
def T1 :   RRISCVReg<6, "t1">,     DwarfRegNum<[6]>;
def T2 :   RRISCVReg<7, "t2">,     DwarfRegNum<[7]>;
def S0 :   RRISCVReg<8, "s0">,     DwarfRegNum<[8]>;
def S1 :   RRISCVReg<9, "s1">,     DwarfRegNum<[9]>;
def A0 :   RRISCVReg<10, "a0">,    DwarfRegNum<[10]>;
def A1 :   RRISCVReg<11, "a1">,    DwarfRegNum<[11]>;
def A2 :   RRISCVReg<12, "a2">,    DwarfRegNum<[12]>;
def A3 :   RRISCVReg<13, "a3">,    DwarfRegNum<[13]>;
def A4 :   RRISCVReg<14, "a4">,    DwarfRegNum<[14]>;
def A5 :   RRISCVReg<15, "a5">,    DwarfRegNum<[15]>;
def A6 :   RRISCVReg<16, "a6">,    DwarfRegNum<[16]>;
def A7 :   RRISCVReg<17, "a7">,    DwarfRegNum<[17]>;

def FT0:   RRISCVReg<0, "ft0">,     DwarfRegNum<[0]>;
def FT1:   RRISCVReg<1, "ft1">,     DwarfRegNum<[1]>;
def FT2:   RRISCVReg<2, "ft2">,     DwarfRegNum<[2]>;
def FT3:   RRISCVReg<3, "ft3">,     DwarfRegNum<[3]>;
def FT4:   RRISCVReg<4, "ft4">,     DwarfRegNum<[4]>;
def FT5:   RRISCVReg<5, "ft5">,     DwarfRegNum<[5]>;
def FT6:   RRISCVReg<6, "ft6">,     DwarfRegNum<[6]>;
def FT7:   RRISCVReg<7, "ft7">,     DwarfRegNum<[7]>;
def FS0:   RRISCVReg<8, "fS0">,     DwarfRegNum<[8]>;
def FS1:   RRISCVReg<9, "fS1">,     DwarfRegNum<[9]>;
def FA0:   RRISCVReg<10, "fa0">,    DwarfRegNum<[10]>;
def FA1:   RRISCVReg<11, "fa1">,    DwarfRegNum<[11]>;
def FA2:   RRISCVReg<12, "fa2">,    DwarfRegNum<[12]>;
def FA3:   RRISCVReg<13, "fa3">,    DwarfRegNum<[13]>;
def FA4:   RRISCVReg<14, "fa4">,    DwarfRegNum<[14]>;
def FA5:   RRISCVReg<15, "fa5">,    DwarfRegNum<[15]>;
def FA6:   RRISCVReg<16, "fa6">,    DwarfRegNum<[16]>;
def FA7:   RRISCVReg<17, "fa7">,    DwarfRegNum<[17]>;
def FS2:   RRISCVReg<18, "fs2">,    DwarfRegNum<[18]>;
def FS3:   RRISCVReg<19, "fs3">,    DwarfRegNum<[19]>;
def FS4:   RRISCVReg<20, "fs4">,    DwarfRegNum<[20]>;
def FS5:   RRISCVReg<21, "fs5">,    DwarfRegNum<[21]>;
def FS6:   RRISCVReg<22, "fs6">,    DwarfRegNum<[22]>;
def FS7:   RRISCVReg<23, "fs7">,    DwarfRegNum<[23]>;
def FS8:   RRISCVReg<24, "fs8">,    DwarfRegNum<[24]>;
def FS9:   RRISCVReg<25, "fs9">,    DwarfRegNum<[25]>;
def FS10:  RRISCVReg<26, "fs10">,   DwarfRegNum<[26]>;
def FS11:  RRISCVReg<27, "fs11">,   DwarfRegNum<[27]>;
def FT8:   RRISCVReg<28, "ft8">,    DwarfRegNum<[28]>;
def FT9:   RRISCVReg<29, "ft9">,    DwarfRegNum<[29]>;
def FT10:  RRISCVReg<30, "ft10">,   DwarfRegNum<[30]>;
def FT11:  RRISCVReg<31, "ft11">,   DwarfRegNum<[31]>;


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

def FPR64:RegisterClass<"RRISCV", [f64], 64, (add
  FT0, FT1, FT2, FT3, FT4, FT5, FT6, FT7,
  FS0, FS1,
  FA0, FA1, FA2, FA3, FA4, FA5, FA6, FA7,
  FS2, FS3, FS4, FS5, FS6, FS7, FS8, FS9, FS10, FS11,
  FT8, FT9, FT10, FT11)>;