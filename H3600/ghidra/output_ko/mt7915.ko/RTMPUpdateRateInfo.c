// module: mt7915.ko
// function: RTMPUpdateRateInfo @ 0xdbe20
// size: 680 bytes
//

void RTMPUpdateRateInfo(uint param_1,undefined1 *param_2,undefined4 param_3,undefined4 param_4)

{
  ushort uVar1;
  
  __memzero(param_2 + 1,0xc,param_3,param_4,param_4);
  __memzero(param_2 + 0xe,0xc);
  __memzero(param_2 + 0x1a,0xc);
  if (param_1 < 0x12) {
    if (0xf < param_1) {
LAB_000dbef8:
      param_2[0x2c] = param_2[0x2c] & 0xc0;
      uVar1 = *(ushort *)(param_2 + 0x2c);
      param_2[0xd] = 0;
      *(short *)(param_2 + 0x2c) = (short)(uVar1 & 0xfffffe7f);
      param_2[1] = 0x8c;
      param_2[2] = 0x12;
      param_2[0x1b] = 0x12;
      param_2[3] = 0x98;
      param_2[0x2d] = (byte)((uVar1 & 0xfffffe7f) >> 8) & 0x1f | 0x20;
      param_2[5] = 0xb0;
      param_2[4] = 0x24;
      param_2[0x1d] = 0x24;
      param_2[6] = 0x48;
      param_2[0x1f] = 0x48;
      param_2[7] = 0x60;
      param_2[0x20] = 0x60;
      param_2[8] = 0x6c;
      param_2[0x21] = 0x6c;
      *param_2 = 8;
      param_2[0x1a] = 0xc;
      param_2[0x1c] = 0x18;
      param_2[0x1e] = 0x30;
      return;
    }
    if (param_1 < 9) {
      if (param_1 < 6) {
        if (param_1 == 2) {
          param_2[0x2c] = param_2[0x2c] & 0xc0;
          uVar1 = *(ushort *)(param_2 + 0x2c);
          param_2[0xd] = 0;
          *(short *)(param_2 + 0x2c) = (short)(uVar1 & 0xfffffe7f);
          param_2[1] = 0x82;
          param_2[4] = 0x96;
          param_2[0x2d] = (byte)((uVar1 & 0xfffffe7f) >> 8) & 0x1f;
          param_2[0x1a] = 2;
          param_2[2] = 0x84;
          param_2[3] = 0x8b;
          *param_2 = 4;
          param_2[0x1b] = 4;
          param_2[0x1c] = 0xb;
          param_2[0x1d] = 0x16;
          return;
        }
        if (param_1 != 4) {
          if (param_1 != 1) {
            return;
          }
          goto LAB_000dbef8;
        }
      }
    }
    else if ((param_1 != 0xc) && (param_1 != 0xe)) {
      return;
    }
  }
  else if (param_1 < 0x32) {
    if ((0x2f < param_1) || (param_1 == 0x1d)) goto LAB_000dbef8;
    if (param_1 != 0x1f) {
      return;
    }
  }
  else if (param_1 != 0x4e) {
    if (param_1 == 0xb1) goto LAB_000dbef8;
    if (param_1 != 0x3f) {
      return;
    }
  }
  param_2[0x2c] = param_2[0x2c] & 0xc0;
  uVar1 = *(ushort *)(param_2 + 0x2c);
  param_2[1] = 0x82;
  *(short *)(param_2 + 0x2c) = (short)(uVar1 & 0xfffffe7f);
  param_2[2] = 0x84;
  param_2[3] = 0x8b;
  param_2[4] = 0x96;
  param_2[5] = 0x12;
  param_2[0x2d] = (byte)((uVar1 & 0xfffffe7f) >> 8) & 0x1f;
  param_2[0x1f] = 0x12;
  param_2[6] = 0x24;
  param_2[0x21] = 0x24;
  param_2[7] = 0x48;
  param_2[0x23] = 0x48;
  param_2[8] = 0x6c;
  param_2[0x25] = 0x6c;
  *param_2 = 8;
  param_2[0xe] = 0xc;
  param_2[0x1e] = 0xc;
  param_2[0xf] = 0x18;
  param_2[0x20] = 0x18;
  param_2[0x10] = 0x30;
  param_2[0x22] = 0x30;
  param_2[0x11] = 0x60;
  param_2[0x24] = 0x60;
  param_2[0xd] = 4;
  param_2[0x1b] = 4;
  param_2[0x1a] = 2;
  param_2[0x1c] = 0xb;
  param_2[0x1d] = 0x16;
  return;
}

