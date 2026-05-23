// module: mt7915.ko
// function: DisplayTxAgg @ 0xea064
// size: 152 bytes
//

void DisplayTxAgg(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int local_40;
  int local_3c;
  int aiStack_38 [8];
  
  AsicReadAggCnt(param_1,&local_40,10);
  if (local_3c + local_40 != 0) {
    piVar3 = aiStack_38;
    iVar2 = 1;
    do {
      if (0 < DebugLevel) {
        iVar4 = *piVar3;
        uVar1 = __aeabi_uidiv(iVar4 * 100,local_3c + local_40);
        printk("\t%d MPDU=%ld (%ld%%)\n",iVar2,iVar4,uVar1);
      }
      iVar2 = iVar2 + 1;
      piVar3 = piVar3 + 1;
    } while (iVar2 != 9);
  }
  printk("====================\n");
  return;
}

