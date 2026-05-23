// module: mt7915.ko
// function: WscDelListEntryByMAC @ 0x1eec04
// size: 264 bytes
//

void WscDelListEntryByMAC(int *param_1,undefined1 *param_2)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  
  piVar2 = (int *)WscFindPeerEntry();
  if (piVar2 == (int *)0x0) {
    return;
  }
  if (2 < DebugLevel) {
    printk("WscDelListEntryByMAC : pMacAddr = %02x:%02x:%02x:%02x:%02x:%02x\n",*param_2,param_2[1],
           param_2[2],param_2[3],param_2[4],param_2[5]);
  }
  piVar3 = (int *)*param_1;
  if (piVar3 != (int *)0x0) {
    if (piVar2 == piVar3) {
      iVar5 = *piVar2;
      *param_1 = iVar5;
      if (iVar5 == 0) {
        param_1[1] = 0;
      }
LAB_001eeca4:
      *(char *)(param_1 + 2) = (char)param_1[2] + -1;
      os_free_mem(piVar2);
      return;
    }
    piVar1 = (int *)*piVar3;
    piVar4 = piVar2;
    while (piVar1 != (int *)0x0) {
      if (piVar2 == piVar1) {
        *piVar3 = *piVar4;
        if (piVar2 == (int *)param_1[1]) {
          param_1[1] = (int)piVar3;
        }
        goto LAB_001eeca4;
      }
      piVar4 = (int *)*piVar1;
      piVar3 = piVar1;
      piVar1 = piVar4;
    }
  }
  os_free_mem(piVar2);
  return;
}

