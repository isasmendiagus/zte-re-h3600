// module: mt7915.ko
// function: ScanParmFill @ 0x144638
// size: 80 bytes
//

void ScanParmFill(undefined4 param_1,int param_2,void *param_3,size_t param_4,undefined1 param_5,
                 undefined1 param_6)

{
  __memzero((void *)(param_2 + 9),0x20,param_3,param_4,param_4);
  if (0x1f < param_4) {
    param_4 = 0x20;
  }
  *(char *)(param_2 + 8) = (char)param_4;
  memmove((void *)(param_2 + 9),param_3,param_4);
  *(undefined1 *)(param_2 + 6) = param_5;
  *(undefined1 *)(param_2 + 7) = param_6;
  return;
}

