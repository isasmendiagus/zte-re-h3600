// module: mt7915.ko
// function: Set_BndStrg_ClearEntry @ 0x9b95c
// size: 160 bytes
//

undefined4
Set_BndStrg_ClearEntry(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *param_1;
  get_wdev_by_ioctl_idx_and_iftype
            (param_1,*(undefined1 *)(iVar2 + 0x3c),*(undefined4 *)(iVar2 + 0x38),iVar2,param_4);
  uVar1 = HcGetBandByWdev();
  if (0 < DebugLevel) {
    printk("%s band %u\n","Set_BndStrg_ClearEntry",uVar1);
  }
  if (uVar1 < 2) {
    if (param_1[uVar1 * 0x425 + 0xdb24f] != 0) {
      (**(code **)(param_1[uVar1 * 0x425 + 0xdb24f] + 8))(param_1 + uVar1 * 0x425 + 0xdae49);
      return 1;
    }
  }
  return 1;
}

