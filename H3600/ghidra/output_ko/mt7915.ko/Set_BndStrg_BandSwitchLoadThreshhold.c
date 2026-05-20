// module: mt7915.ko
// function: Set_BndStrg_BandSwitchLoadThreshhold @ 0x9bf6c
// size: 192 bytes
//

undefined4
Set_BndStrg_BandSwitchLoadThreshhold
          (int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = simple_strtol(param_2,0,10,param_4,param_4);
  get_wdev_by_ioctl_idx_and_iftype
            (param_1,*(undefined1 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar3 = HcGetBandByWdev();
  if (0 < DebugLevel) {
    printk("%s band %u\n","Set_BndStrg_BandSwitchLoadThreshhold",uVar3);
  }
  iVar1 = DebugLevel;
  if ((uVar3 < 2) && (*(char *)((int)param_1 + uVar3 * 0x1094 + 0x36c992) != '\x01')) {
    param_1[uVar3 * 0x425 + 0xdb26d] = iVar2;
    if (0 < iVar1) {
      printk("%s(): ulBandSwitchLoadThreshhold = %d\n","Set_BndStrg_BandSwitchLoadThreshhold",iVar2)
      ;
    }
  }
  return 1;
}

