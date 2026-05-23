// module: mt7915.ko
// function: construct_mic_header1 @ 0xb6530
// size: 148 bytes
//

void construct_mic_header1(undefined1 *param_1,int param_2,byte *param_3)

{
  int iVar1;
  
  iVar1 = param_2 + -2;
  param_1[1] = (char)iVar1;
  if (iVar1 < 0) {
    iVar1 = param_2 + 0xfd;
  }
  *param_1 = (char)((uint)iVar1 >> 8);
  param_1[2] = *param_3 & 0xcf;
  param_1[3] = param_3[1] & 199;
  param_1[4] = param_3[4];
  param_1[5] = param_3[5];
  param_1[6] = param_3[6];
  param_1[7] = param_3[7];
  param_1[8] = param_3[8];
  param_1[9] = param_3[9];
  param_1[10] = param_3[10];
  param_1[0xb] = param_3[0xb];
  param_1[0xc] = param_3[0xc];
  param_1[0xd] = param_3[0xd];
  param_1[0xe] = param_3[0xe];
  param_1[0xf] = param_3[0xf];
  return;
}

