// module: mt7915.ko
// function: DfsPrimToCent @ 0x22fe24
// size: 276 bytes
//

uint DfsPrimToCent(uint param_1,uint param_2)

{
  uint uVar1;
  undefined4 uVar2;
  byte local_32 [26];
  
  local_32[0xd] = 0x28;
  local_32[0xe] = 0x30;
  local_32[0xf] = 0x38;
  local_32[0x10] = 0x40;
  local_32[0x11] = 0x68;
  local_32[0x12] = 0x70;
  local_32[0x13] = 0x78;
  local_32[0x14] = 0x80;
  local_32[0x15] = 0x88;
  local_32[0x16] = 0x90;
  local_32[0x17] = 0x99;
  local_32[0x18] = 0xa1;
  local_32[0x19] = 0;
  local_32[0] = 0x24;
  local_32[1] = 0x2c;
  local_32[2] = 0x34;
  local_32[3] = 0x3c;
  local_32[4] = 100;
  local_32[5] = 0x6c;
  local_32[6] = 0x74;
  local_32[7] = 0x7c;
  local_32[8] = 0x84;
  local_32[9] = 0x8c;
  local_32[10] = 0x95;
  local_32[0xb] = 0x9d;
  local_32[0xc] = 0;
  if (param_2 != 0) {
    if (param_2 != 1) {
      if ((param_2 & 0xfb) == 2) {
        uVar2 = 1;
      }
      else {
        if (param_2 != 3) {
          return param_1;
        }
        uVar2 = 2;
      }
      uVar1 = vht_cent_ch_freq(param_1,uVar2,1);
      return uVar1;
    }
    if (param_1 == 0x24) {
LAB_0022ff20:
      param_1 = param_1 + 2 & 0xff;
    }
    else {
      if (param_1 != 0x28) {
        uVar1 = 0;
        do {
          uVar1 = uVar1 + 1 & 0xff;
          if (local_32[uVar1] == 0) {
            return param_1;
          }
          if (param_1 == local_32[uVar1]) goto LAB_0022ff20;
        } while (local_32[uVar1 + 0xd] != param_1);
      }
      param_1 = param_1 - 2 & 0xff;
    }
  }
  return param_1;
}

