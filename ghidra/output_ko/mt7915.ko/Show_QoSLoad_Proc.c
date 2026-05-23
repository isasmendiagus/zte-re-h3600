// module: mt7915.ko
// function: Show_QoSLoad_Proc @ 0x27670
// size: 292 bytes
//

undefined4 Show_QoSLoad_Proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  int iVar7;
  
  iVar1 = HcGetQloadCtrl();
  uVar5 = (uint)((int)((ulonglong)*(ushort *)(&DAT_00794c50 + param_1) * 0xcccccccd >> 0x20) << 0xc)
          >> 0x10;
  if (0 < DebugLevel) {
    printk("\n\tPrimary Busy Time\tTimes\n");
  }
  puVar6 = (undefined4 *)(iVar1 + 0x20);
  iVar3 = 1;
  iVar4 = 0;
  iVar2 = DebugLevel;
  do {
    iVar7 = uVar5 + iVar4;
    if (0 < iVar2) {
      printk("\t%dms ~ %dms\t\t%d\n",iVar4,iVar7,*puVar6,param_4);
      iVar2 = DebugLevel;
    }
    iVar3 = iVar3 + 1;
    puVar6 = puVar6 + 1;
    iVar4 = iVar7;
  } while (iVar3 != 0x15);
  if (0 < iVar2) {
    printk("\n\tSecondary Busy Time\tTimes\n");
    iVar2 = DebugLevel;
  }
  puVar6 = (undefined4 *)(iVar1 + 0x70);
  iVar4 = 1;
  iVar1 = 0;
  do {
    iVar3 = uVar5 + iVar1;
    if (0 < iVar2) {
      printk("\t%dms ~ %dms\t\t%d\n",iVar1,iVar3,*puVar6);
      iVar2 = DebugLevel;
    }
    iVar4 = iVar4 + 1;
    puVar6 = puVar6 + 1;
    iVar1 = iVar3;
  } while (iVar4 != 0x15);
  if (0 < iVar2) {
    printk(&_LC7);
  }
  return 1;
}

