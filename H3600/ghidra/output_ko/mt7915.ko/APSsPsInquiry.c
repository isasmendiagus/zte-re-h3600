// module: mt7915.ko
// function: APSsPsInquiry @ 0x151d4
// size: 212 bytes
//

void APSsPsInquiry(int param_1,byte *param_2,undefined4 *param_3,undefined2 *param_4,
                  undefined1 *param_5,undefined1 *param_6)

{
  int iVar1;
  
  if ((*param_2 & 1) == 0) {
    iVar1 = MacTableLookup();
    if (iVar1 != 0) {
      *param_3 = *(undefined4 *)(iVar1 + 0xfc);
      *param_4 = *(undefined2 *)(iVar1 + 0xf8);
      *param_5 = *(undefined1 *)(iVar1 + 0xaf8);
      if (((*(uint *)(iVar1 + 0x17c) & 0x12cf8) != 0) && (*(char *)(iVar1 + 0x515) != '\x01')) {
        *param_6 = *(undefined1 *)(param_1 + 0x794cd5);
        return;
      }
      *param_6 = *(undefined1 *)(iVar1 + 0xb7f);
      return;
    }
    *param_3 = 0;
    *param_4 = 0;
  }
  else {
    *param_3 = 2;
    *param_4 = 0;
  }
  *param_5 = 0;
  *param_6 = *(undefined1 *)(param_1 + 0x794cd5);
  return;
}

