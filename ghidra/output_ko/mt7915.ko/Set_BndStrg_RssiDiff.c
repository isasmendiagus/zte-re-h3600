// module: mt7915.ko
// function: Set_BndStrg_RssiDiff @ 0x9bacc
// size: 244 bytes
//

undefined4
Set_BndStrg_RssiDiff(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = *param_1;
  uVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined1 *)(iVar4 + 0x3c),*(undefined4 *)(iVar4 + 0x38),iVar4,
                     param_4);
  cVar1 = simple_strtol(param_2,0,10);
  uVar3 = HcGetBandByWdev(uVar2);
  if (0 < DebugLevel) {
    printk("%s band %u\n","Set_BndStrg_RssiDiff",uVar3);
  }
  if (uVar3 < 2) {
    if (param_1[uVar3 * 0x425 + 0xdb24f] != 0) {
      (**(code **)(param_1[uVar3 * 0x425 + 0xdb24f] + 0x20))
                (param_1 + uVar3 * 0x425 + 0xdae49,(int)cVar1);
    }
    iVar4 = DebugLevel;
    *(char *)((int)param_1 + uVar3 * 0x1094 + 0x36c946) = cVar1;
    if (0 < iVar4) {
      printk("%s(): RssiCheck = %u\n","Set_BndStrg_RssiDiff",(int)cVar1);
    }
  }
  return 1;
}

