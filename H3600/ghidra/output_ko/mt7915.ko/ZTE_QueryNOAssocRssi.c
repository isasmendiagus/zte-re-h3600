// module: mt7915.ko
// function: ZTE_QueryNOAssocRssi @ 0x159e64
// size: 324 bytes
//

undefined4 ZTE_QueryNOAssocRssi(int *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if ((iVar1 == 0) || (*(int *)(param_2 + 0x10) == 0)) {
    if (-1 < DebugLevel) {
      printk("%s : parameter error length=%d\n","ZTE_QueryNOAssocRssi",
             *(undefined2 *)(param_2 + 0x14));
    }
  }
  else {
    uVar2 = HcGetBandByWdev();
    if (0 < DebugLevel) {
      printk("%s : band_idx value=%d\n","ZTE_QueryNOAssocRssi",uVar2);
    }
    if (uVar2 < 2) {
      if (9 < *(ushort *)(param_2 + 0x14)) {
        uVar3 = *(uint *)(param_2 + 0x10);
        *(undefined2 *)(param_2 + 0x14) = 10;
        uVar4 = *(uint *)(((uint)&stack0xfffffff0 & 0xffffe000) + 8);
        if (uVar3 < 0xfffffff6 && uVar3 + 10 <= uVar4) {
          uVar4 = 0;
        }
        if ((uVar4 == 0) && (iVar1 = __copy_to_user(uVar3,uVar2 * 10 + 0x5f4530), iVar1 == 0)) {
          return 0;
        }
        if (-1 < DebugLevel) {
          printk("Get::%s error!! Status=%d\n","ZTE_QueryNOAssocRssi");
          return 1;
        }
      }
    }
    else if (-1 < DebugLevel) {
      printk("%s : band_idx error value=%d\n","ZTE_QueryNOAssocRssi",uVar2);
      return 1;
    }
  }
  return 1;
}

