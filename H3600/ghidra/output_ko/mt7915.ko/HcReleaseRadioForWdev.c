// module: mt7915.ko
// function: HcReleaseRadioForWdev @ 0xa8bc4
// size: 128 bytes
//

undefined4 HcReleaseRadioForWdev(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = *(int *)(param_2 + 0xabc);
  iVar2 = iVar1 + 0x20;
  uVar3 = *(undefined4 *)(param_1 + 0xa797a0);
  OS_SPIN_LOCK(iVar2);
  if (*(char *)(iVar1 + 0x1d) != '\0') {
    if (0 < DebugLevel) {
      printk("%s(): there are other link reference the Obj\n","HcReleaseRadioForWdev");
    }
    OS_SPIN_UNLOCK(iVar2);
    return 0;
  }
  OS_SPIN_UNLOCK(iVar2);
  RcReleaseBandForObj(uVar3,iVar1);
  return 0;
}

