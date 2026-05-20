// module: tm.ko
// function: tm_devIoctl @ 0x10010
// size: 312 bytes
//

int tm_devIoctl(undefined4 param_1,int param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined1 auStack_38 [44];
  
  __memzero(auStack_38,0x28);
  if (param_2 == 0x6040) {
    uVar4 = *(uint *)(((uint)&local_40 & 0xffffe000) + 8);
    uVar2 = param_3 + 8;
    uVar3 = uVar2;
    if (param_3 < 0xfffffff8) {
      uVar3 = uVar2 - (uVar4 + 1);
    }
    if (param_3 < 0xfffffff8 && uVar2 <= uVar4) {
      uVar4 = 0;
    }
    if (uVar4 == 0) {
      iVar1 = __copy_from_user(&local_40,param_3,8);
      if (iVar1 == 0) {
        iVar1 = ztePonCfgPrbsRxBist(local_40,uStack_3c);
        if (iVar1 != 0) {
          printk("ZTE_PON_PRBS_RXBIST_S error\n");
        }
        return iVar1;
      }
    }
    else {
      __memzero(&local_40,8,uVar3);
    }
  }
  else {
    if (param_2 != 0x6041) {
      printk("ERROR: Error cmd 0x%x\n",param_2);
      return 0;
    }
    uVar4 = *(uint *)(((uint)&local_40 & 0xffffe000) + 8);
    uVar2 = param_3 + 4;
    uVar3 = uVar2;
    if (param_3 < 0xfffffffc) {
      uVar3 = uVar2 - (uVar4 + 1);
    }
    if (param_3 < 0xfffffffc && uVar2 <= uVar4) {
      uVar4 = 0;
    }
    if (uVar4 == 0) {
      iVar1 = __copy_from_user(&local_40,param_3,4);
      if (iVar1 == 0) {
        iVar1 = ztePonGetPrbsCounters(local_40);
        if (iVar1 == 0) {
          return 0;
        }
        printk("ZTE_PON_PRBS_CNT_G error\n");
        return iVar1;
      }
    }
    else {
      __memzero(&local_40,4,uVar3);
    }
  }
  return -0xe;
}

