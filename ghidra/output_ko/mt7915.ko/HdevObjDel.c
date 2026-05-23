// module: mt7915.ko
// function: HdevObjDel @ 0xae38c
// size: 84 bytes
//

void HdevObjDel(int param_1,int param_2)

{
  *(undefined1 *)(param_2 + 0x1c) = 0;
  *(undefined4 *)(param_2 + 8) = 0;
  if (*(int *)(param_2 + 0x14) != 0) {
    *(undefined4 *)(*(int *)(param_2 + 0x14) + 4) = *(undefined4 *)(param_2 + 0x18);
  }
  if (*(undefined4 **)(param_2 + 0x18) != (undefined4 *)0x0) {
    **(undefined4 **)(param_2 + 0x18) = *(undefined4 *)(param_2 + 0x14);
  }
  *(int *)(param_2 + 0xc) = param_2 + 0xc;
  *(undefined4 *)(param_2 + 0x14) = 0;
  *(undefined4 *)(param_2 + 0x18) = 0;
  *(int *)(param_2 + 0x10) = param_2 + 0xc;
  *(char *)(param_1 + 0x14) = *(char *)(param_1 + 0x14) + -1;
  return;
}

