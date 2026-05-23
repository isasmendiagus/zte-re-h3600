// module: mt7915.ko
// function: Set_BndStrg_Loading_Method @ 0x9e148
// size: 332 bytes
//

undefined4 Set_BndStrg_Loading_Method(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  
  iVar2 = simple_strtol(param_2,0,10);
  get_wdev_by_ioctl_idx_and_iftype
            (param_1,*(undefined1 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar3 = HcGetBandByWdev();
  if (0 < DebugLevel) {
    printk("%s band %u\n","Set_BndStrg_Loading_Method",uVar3);
  }
  iVar1 = DebugLevel;
  if (uVar3 < 2) {
    piVar5 = param_1 + uVar3 * 0x425 + 0xdae49;
    iVar4 = param_1[uVar3 * 0x425 + 0xdb24f];
    if (iVar4 != 0) {
      if (iVar2 == 1) {
        (**(code **)(iVar4 + 0x48))(param_1,piVar5,700000,1);
        iVar4 = param_1[uVar3 * 0x425 + 0xdb24f];
      }
      else if (iVar2 == 0) {
        (**(code **)(iVar4 + 0x48))(param_1,piVar5,2000,1);
        iVar4 = param_1[uVar3 * 0x425 + 0xdb24f];
      }
      else if (iVar2 - 2U < 2) {
        *(char *)(param_1 + uVar3 * 0x425 + 0xdb26a) = (char)iVar2;
        if (iVar1 < 1) {
          return 1;
        }
        printk("Set_BndStrg_Loading_Method-5g method=%d\n",iVar2);
        return 1;
      }
      (**(code **)(iVar4 + 0x48))(param_1,piVar5,iVar2,0);
      return 1;
    }
  }
  return 1;
}

