; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc -aarch64-sve-vector-bits-min=256  < %s | FileCheck %s -check-prefixes=CHECK,VBITS_GE_256
; RUN: llc -aarch64-sve-vector-bits-min=512  < %s | FileCheck %s -check-prefixes=CHECK,VBITS_GE_512
; RUN: llc -aarch64-sve-vector-bits-min=2048 < %s | FileCheck %s -check-prefixes=CHECK,VBITS_GE_512

target triple = "aarch64-unknown-linux-gnu"

define void @store_trunc_v2i64i8(<2 x i64>* %ap, <2 x i8>* %dest) vscale_range(2,0) #0 {
; CHECK-LABEL: store_trunc_v2i64i8:
; CHECK:       // %bb.0:
; CHECK-NEXT:    ldr q0, [x0]
; CHECK-NEXT:    ptrue p0.d, vl2
; CHECK-NEXT:    st1b { z0.d }, p0, [x1]
; CHECK-NEXT:    ret
  %a = load <2 x i64>, <2 x i64>* %ap
  %val = trunc <2 x i64> %a to <2 x i8>
  store <2 x i8> %val, <2 x i8>* %dest
  ret void
}

define void @store_trunc_v4i64i8(<4 x i64>* %ap, <4 x i8>* %dest) vscale_range(2,0) #0 {
; CHECK-LABEL: store_trunc_v4i64i8:
; CHECK:       // %bb.0:
; CHECK-NEXT:    ptrue p0.d, vl4
; CHECK-NEXT:    ld1d { z0.d }, p0/z, [x0]
; CHECK-NEXT:    st1b { z0.d }, p0, [x1]
; CHECK-NEXT:    ret
  %a = load <4 x i64>, <4 x i64>* %ap
  %val = trunc <4 x i64> %a to <4 x i8>
  store <4 x i8> %val, <4 x i8>* %dest
  ret void
}

define void @store_trunc_v8i64i8(<8 x i64>* %ap, <8 x i8>* %dest) #0 {
; VBITS_GE_256-LABEL: store_trunc_v8i64i8:
; VBITS_GE_256:       // %bb.0:
; VBITS_GE_256-NEXT:    mov x8, #4
; VBITS_GE_256-NEXT:    ptrue p0.d, vl4
; VBITS_GE_256-NEXT:    ld1d { z0.d }, p0/z, [x0, x8, lsl #3]
; VBITS_GE_256-NEXT:    ld1d { z1.d }, p0/z, [x0]
; VBITS_GE_256-NEXT:    ptrue p0.s, vl4
; VBITS_GE_256-NEXT:    uzp1 z0.s, z0.s, z0.s
; VBITS_GE_256-NEXT:    uzp1 z1.s, z1.s, z1.s
; VBITS_GE_256-NEXT:    splice z1.s, p0, z1.s, z0.s
; VBITS_GE_256-NEXT:    ptrue p0.s, vl8
; VBITS_GE_256-NEXT:    st1b { z1.s }, p0, [x1]
; VBITS_GE_256-NEXT:    ret
;
; VBITS_GE_512-LABEL: store_trunc_v8i64i8:
; VBITS_GE_512:       // %bb.0:
; VBITS_GE_512-NEXT:    ptrue p0.d, vl8
; VBITS_GE_512-NEXT:    ld1d { z0.d }, p0/z, [x0]
; VBITS_GE_512-NEXT:    st1b { z0.d }, p0, [x1]
; VBITS_GE_512-NEXT:    ret
  %a = load <8 x i64>, <8 x i64>* %ap
  %val = trunc <8 x i64> %a to <8 x i8>
  store <8 x i8> %val, <8 x i8>* %dest
  ret void
}

define void @store_trunc_v16i64i8(<16 x i64>* %ap, <16 x i8>* %dest) vscale_range(8,0) #0 {
; CHECK-LABEL: store_trunc_v16i64i8:
; CHECK:       // %bb.0:
; CHECK-NEXT:    ptrue p0.d, vl16
; CHECK-NEXT:    ld1d { z0.d }, p0/z, [x0]
; CHECK-NEXT:    st1b { z0.d }, p0, [x1]
; CHECK-NEXT:    ret
  %a = load <16 x i64>, <16 x i64>* %ap
  %val = trunc <16 x i64> %a to <16 x i8>
  store <16 x i8> %val, <16 x i8>* %dest
  ret void
}

define void @store_trunc_v32i64i8(<32 x i64>* %ap, <32 x i8>* %dest) vscale_range(16,0) #0 {
; CHECK-LABEL: store_trunc_v32i64i8:
; CHECK:       // %bb.0:
; CHECK-NEXT:    ptrue p0.d, vl32
; CHECK-NEXT:    ld1d { z0.d }, p0/z, [x0]
; CHECK-NEXT:    st1b { z0.d }, p0, [x1]
; CHECK-NEXT:    ret
  %a = load <32 x i64>, <32 x i64>* %ap
  %val = trunc <32 x i64> %a to <32 x i8>
  store <32 x i8> %val, <32 x i8>* %dest
  ret void
}

define void @store_trunc_v8i64i16(<8 x i64>* %ap, <8 x i16>* %dest) #0 {
; Currently does not use the truncating store
; VBITS_GE_256-LABEL: store_trunc_v8i64i16:
; VBITS_GE_256:       // %bb.0:
; VBITS_GE_256-NEXT:    mov x8, #4
; VBITS_GE_256-NEXT:    ptrue p0.d, vl4
; VBITS_GE_256-NEXT:    ld1d { z0.d }, p0/z, [x0, x8, lsl #3]
; VBITS_GE_256-NEXT:    ld1d { z1.d }, p0/z, [x0]
; VBITS_GE_256-NEXT:    uzp1 z0.s, z0.s, z0.s
; VBITS_GE_256-NEXT:    uzp1 z1.s, z1.s, z1.s
; VBITS_GE_256-NEXT:    uzp1 z0.h, z0.h, z0.h
; VBITS_GE_256-NEXT:    uzp1 z1.h, z1.h, z1.h
; VBITS_GE_256-NEXT:    mov v1.d[1], v0.d[0]
; VBITS_GE_256-NEXT:    str q1, [x1]
; VBITS_GE_256-NEXT:    ret
;
; VBITS_GE_512-LABEL: store_trunc_v8i64i16:
; VBITS_GE_512:       // %bb.0:
; VBITS_GE_512-NEXT:    ptrue p0.d, vl8
; VBITS_GE_512-NEXT:    ld1d { z0.d }, p0/z, [x0]
; VBITS_GE_512-NEXT:    st1h { z0.d }, p0, [x1]
; VBITS_GE_512-NEXT:    ret
  %a = load <8 x i64>, <8 x i64>* %ap
  %val = trunc <8 x i64> %a to <8 x i16>
  store <8 x i16> %val, <8 x i16>* %dest
  ret void
}

define void @store_trunc_v8i64i32(<8 x i64>* %ap, <8 x i32>* %dest) #0 {
; VBITS_GE_256-LABEL: store_trunc_v8i64i32:
; VBITS_GE_256:       // %bb.0:
; VBITS_GE_256-NEXT:    mov x8, #4
; VBITS_GE_256-NEXT:    ptrue p0.d, vl4
; VBITS_GE_256-NEXT:    ld1d { z0.d }, p0/z, [x0, x8, lsl #3]
; VBITS_GE_256-NEXT:    ld1d { z1.d }, p0/z, [x0]
; VBITS_GE_256-NEXT:    ptrue p0.s, vl4
; VBITS_GE_256-NEXT:    uzp1 z0.s, z0.s, z0.s
; VBITS_GE_256-NEXT:    uzp1 z1.s, z1.s, z1.s
; VBITS_GE_256-NEXT:    splice z1.s, p0, z1.s, z0.s
; VBITS_GE_256-NEXT:    ptrue p0.s, vl8
; VBITS_GE_256-NEXT:    st1w { z1.s }, p0, [x1]
; VBITS_GE_256-NEXT:    ret
;
; VBITS_GE_512-LABEL: store_trunc_v8i64i32:
; VBITS_GE_512:       // %bb.0:
; VBITS_GE_512-NEXT:    ptrue p0.d, vl8
; VBITS_GE_512-NEXT:    ld1d { z0.d }, p0/z, [x0]
; VBITS_GE_512-NEXT:    st1w { z0.d }, p0, [x1]
; VBITS_GE_512-NEXT:    ret
  %a = load <8 x i64>, <8 x i64>* %ap
  %val = trunc <8 x i64> %a to <8 x i32>
  store <8 x i32> %val, <8 x i32>* %dest
  ret void
}

define void @store_trunc_v16i32i8(<16 x i32>* %ap, <16 x i8>* %dest) #0 {
; Currently does not use the truncating store
; VBITS_GE_256-LABEL: store_trunc_v16i32i8:
; VBITS_GE_256:       // %bb.0:
; VBITS_GE_256-NEXT:    mov x8, #8
; VBITS_GE_256-NEXT:    ptrue p0.s, vl8
; VBITS_GE_256-NEXT:    ld1w { z0.s }, p0/z, [x0, x8, lsl #2]
; VBITS_GE_256-NEXT:    ld1w { z1.s }, p0/z, [x0]
; VBITS_GE_256-NEXT:    uzp1 z0.h, z0.h, z0.h
; VBITS_GE_256-NEXT:    uzp1 z1.h, z1.h, z1.h
; VBITS_GE_256-NEXT:    uzp1 z0.b, z0.b, z0.b
; VBITS_GE_256-NEXT:    uzp1 z1.b, z1.b, z1.b
; VBITS_GE_256-NEXT:    mov v1.d[1], v0.d[0]
; VBITS_GE_256-NEXT:    str q1, [x1]
; VBITS_GE_256-NEXT:    ret
;
; VBITS_GE_512-LABEL: store_trunc_v16i32i8:
; VBITS_GE_512:       // %bb.0:
; VBITS_GE_512-NEXT:    ptrue p0.s, vl16
; VBITS_GE_512-NEXT:    ld1w { z0.s }, p0/z, [x0]
; VBITS_GE_512-NEXT:    st1b { z0.s }, p0, [x1]
; VBITS_GE_512-NEXT:    ret
  %a = load <16 x i32>, <16 x i32>* %ap
  %val = trunc <16 x i32> %a to <16 x i8>
  store <16 x i8> %val, <16 x i8>* %dest
  ret void
}

define void @store_trunc_v16i32i16(<16 x i32>* %ap, <16 x i16>* %dest) #0 {
; VBITS_GE_256-LABEL: store_trunc_v16i32i16:
; VBITS_GE_256:       // %bb.0:
; VBITS_GE_256-NEXT:    mov x8, #8
; VBITS_GE_256-NEXT:    ptrue p0.s, vl8
; VBITS_GE_256-NEXT:    ld1w { z0.s }, p0/z, [x0, x8, lsl #2]
; VBITS_GE_256-NEXT:    ld1w { z1.s }, p0/z, [x0]
; VBITS_GE_256-NEXT:    ptrue p0.h, vl8
; VBITS_GE_256-NEXT:    uzp1 z0.h, z0.h, z0.h
; VBITS_GE_256-NEXT:    uzp1 z1.h, z1.h, z1.h
; VBITS_GE_256-NEXT:    splice z1.h, p0, z1.h, z0.h
; VBITS_GE_256-NEXT:    ptrue p0.h, vl16
; VBITS_GE_256-NEXT:    st1h { z1.h }, p0, [x1]
; VBITS_GE_256-NEXT:    ret
;
; VBITS_GE_512-LABEL: store_trunc_v16i32i16:
; VBITS_GE_512:       // %bb.0:
; VBITS_GE_512-NEXT:    ptrue p0.s, vl16
; VBITS_GE_512-NEXT:    ld1w { z0.s }, p0/z, [x0]
; VBITS_GE_512-NEXT:    st1h { z0.s }, p0, [x1]
; VBITS_GE_512-NEXT:    ret
  %a = load <16 x i32>, <16 x i32>* %ap
  %val = trunc <16 x i32> %a to <16 x i16>
  store <16 x i16> %val, <16 x i16>* %dest
  ret void
}

define void @store_trunc_v32i16i8(<32 x i16>* %ap, <32 x i8>* %dest) #0 {
; VBITS_GE_256-LABEL: store_trunc_v32i16i8:
; VBITS_GE_256:       // %bb.0:
; VBITS_GE_256-NEXT:    mov x8, #16
; VBITS_GE_256-NEXT:    ptrue p0.h, vl16
; VBITS_GE_256-NEXT:    ld1h { z0.h }, p0/z, [x0, x8, lsl #1]
; VBITS_GE_256-NEXT:    ld1h { z1.h }, p0/z, [x0]
; VBITS_GE_256-NEXT:    ptrue p0.b, vl16
; VBITS_GE_256-NEXT:    uzp1 z0.b, z0.b, z0.b
; VBITS_GE_256-NEXT:    uzp1 z1.b, z1.b, z1.b
; VBITS_GE_256-NEXT:    splice z1.b, p0, z1.b, z0.b
; VBITS_GE_256-NEXT:    ptrue p0.b, vl32
; VBITS_GE_256-NEXT:    st1b { z1.b }, p0, [x1]
; VBITS_GE_256-NEXT:    ret
;
; VBITS_GE_512-LABEL: store_trunc_v32i16i8:
; VBITS_GE_512:       // %bb.0:
; VBITS_GE_512-NEXT:    ptrue p0.h, vl32
; VBITS_GE_512-NEXT:    ld1h { z0.h }, p0/z, [x0]
; VBITS_GE_512-NEXT:    st1b { z0.h }, p0, [x1]
; VBITS_GE_512-NEXT:    ret
  %a = load <32 x i16>, <32 x i16>* %ap
  %val = trunc <32 x i16> %a to <32 x i8>
  store <32 x i8> %val, <32 x i8>* %dest
  ret void
}

attributes #0 = { "target-features"="+sve" }