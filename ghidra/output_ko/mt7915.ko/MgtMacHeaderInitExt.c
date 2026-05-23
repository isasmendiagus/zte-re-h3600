// module: mt7915.ko
// function: MgtMacHeaderInitExt @ 0x12cea4
// size: 120 bytes
//

void MgtMacHeaderInitExt(undefined4 param_1,byte *param_2,uint param_3,undefined4 param_4,
                        undefined4 *param_5,undefined4 *param_6,undefined4 *param_7)

{
  __memzero(param_2,0x18,param_3,param_4,param_4);
  *param_2 = *param_2 & 3 | (byte)((param_3 & 0xf) << 4);
  param_2[1] = param_2[1] & 0xfe | (byte)param_4 & 1;
  *(undefined4 *)(param_2 + 4) = *param_5;
  *(undefined2 *)(param_2 + 8) = *(undefined2 *)(param_5 + 1);
  *(undefined4 *)(param_2 + 10) = *param_6;
  *(undefined2 *)(param_2 + 0xe) = *(undefined2 *)(param_6 + 1);
  *(undefined4 *)(param_2 + 0x10) = *param_7;
  *(undefined2 *)(param_2 + 0x14) = *(undefined2 *)(param_7 + 1);
  return;
}

