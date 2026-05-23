// module: mt7915.ko
// function: RTMPConstructCCMPAAD @ 0xb6ee4
// size: 192 bytes
//

void RTMPConstructCCMPAAD
               (byte *param_1,int param_2,uint param_3,uint param_4,byte *param_5,
               undefined4 *param_6)

{
  byte bVar1;
  undefined4 uVar2;
  
  bVar1 = *param_1;
  if (param_2 != 0) {
    bVar1 = bVar1 & 0x8f;
  }
  *param_5 = bVar1;
  param_5[1] = param_1[1] & 199 | 0x40;
  memmove(param_5 + 2,param_1 + 4,0x12);
  bVar1 = param_1[0x16];
  param_5[0x15] = 0;
  param_5[0x14] = bVar1 & 0xf;
  if (param_3 == 0) {
    if ((param_4 & 1) == 0) {
      uVar2 = 0x16;
    }
    else {
      bVar1 = param_1[0x18];
      uVar2 = 0x18;
      param_5[0x17] = 0;
      param_5[0x16] = bVar1 & 0xf;
    }
  }
  else {
    memmove(param_5 + 0x16,param_1 + 0x18,6);
    if ((param_3 & param_4) != 0) {
      bVar1 = param_1[0x1e];
      param_5[0x1d] = 0;
      param_5[0x1c] = bVar1 & 0xf;
      *param_6 = 0x1e;
      return;
    }
    uVar2 = 0x1c;
  }
  *param_6 = uVar2;
  return;
}

