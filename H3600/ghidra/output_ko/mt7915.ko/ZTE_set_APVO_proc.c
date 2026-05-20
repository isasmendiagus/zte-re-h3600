// module: mt7915.ko
// function: ZTE_set_APVO_proc @ 0x1590e4
// size: 160 bytes
//

undefined4 ZTE_set_APVO_proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar1 == 0) {
    printk("ZTE_set_APVO_proc para error %p\n",0);
  }
  else {
    FUN_00155cf8(param_1,param_2,param_1 + (uint)*(byte *)(iVar1 + 0x8d7) * 9 + 0x1e5421,3);
    uVar2 = HcGetEdca(param_1,iVar1);
    iVar3 = FUN_00155cf8(param_1,param_2,uVar2,3);
    if (iVar3 == 1) {
      HcSetEdca(iVar1);
      return 1;
    }
  }
  return 1;
}

