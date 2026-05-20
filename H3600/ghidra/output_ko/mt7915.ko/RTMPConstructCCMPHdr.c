// module: mt7915.ko
// function: RTMPConstructCCMPHdr @ 0xb7030
// size: 92 bytes
//

void RTMPConstructCCMPHdr(char param_1,undefined1 *param_2,undefined1 *param_3)

{
  undefined1 uVar1;
  
  __memzero(param_3,8);
  *param_3 = *param_2;
  uVar1 = param_2[1];
  param_3[3] = param_1 << 6 | 0x20;
  param_3[1] = uVar1;
  param_3[4] = param_2[2];
  param_3[5] = param_2[3];
  param_3[6] = param_2[4];
  param_3[7] = param_2[5];
  return;
}

