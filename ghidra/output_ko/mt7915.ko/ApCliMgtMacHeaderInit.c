// module: mt7915.ko
// function: ApCliMgtMacHeaderInit @ 0x6b03c
// size: 152 bytes
//

void ApCliMgtMacHeaderInit
               (int param_1,byte *param_2,char param_3,byte param_4,undefined4 *param_5,
               undefined4 *param_6,ushort param_7)

{
  __memzero(param_2,0x18);
  param_2[1] = param_2[1] & 0xfe | param_4 & 1;
  *param_2 = *param_2 & 3 | param_3 << 4;
  param_1 = param_1 + (uint)param_7 * 0x2137b0;
  *(undefined4 *)(param_2 + 4) = *param_5;
  *(undefined2 *)(param_2 + 8) = *(undefined2 *)(param_5 + 1);
  *(undefined4 *)(param_2 + 10) = *(undefined4 *)(&DAT_0036db73 + param_1);
  *(undefined2 *)(param_2 + 0xe) = *(undefined2 *)(&DAT_0036db77 + param_1);
  *(undefined4 *)(param_2 + 0x10) = *param_6;
  *(undefined2 *)(param_2 + 0x14) = *(undefined2 *)(param_6 + 1);
  return;
}

