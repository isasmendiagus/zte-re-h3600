// module: mt7915.ko
// function: CMTimerExec @ 0x17d7c
// size: 208 bytes
//

void CMTimerExec(undefined4 param_1,int param_2)

{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  
  uVar4 = 0;
  (&DAT_003687e5)[param_2] = 0;
  uVar3 = 0;
  piVar2 = (int *)(param_2 + 0xa1d20);
  while( true ) {
    uVar1 = HcGetMaxStaNum(param_2);
    bVar5 = uVar1 <= uVar3;
    uVar3 = uVar3 + 1;
    if (bVar5) break;
    if ((*piVar2 == 0x20001) && ((char)piVar2[0x2b6] == '\x01')) {
      *(undefined1 *)(piVar2 + 0x2b6) = 0;
      uVar4 = uVar4 + 1;
    }
    piVar2 = piVar2 + 0x530;
  }
  if (1 < uVar4) {
    if (DebugLevel < 0) {
      (&DAT_003687e4)[param_2] = 0;
      return;
    }
    printk("Find more than one entry which generated MIC Fail ..\n");
  }
  bVar5 = DebugLevel < 0;
  (&DAT_003687e4)[param_2] = 0;
  if (bVar5) {
    return;
  }
  printk("Counter measure timer expired, resume connection access.\n");
  return;
}

