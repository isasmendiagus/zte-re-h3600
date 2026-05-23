// module: mt7915.ko
// function: Set_BndStrg_RssiHigh @ 0x9bccc
// size: 260 bytes
//

undefined4
Set_BndStrg_RssiHigh(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  
  cVar2 = simple_strtol(param_2,0,10,param_4,param_4);
  get_wdev_by_ioctl_idx_and_iftype
            (param_1,*(undefined1 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar3 = HcGetBandByWdev();
  if (0 < DebugLevel) {
    printk("%s band %u\n","Set_BndStrg_RssiHigh",uVar3);
  }
  if (uVar3 < 2) {
    if (100 < (byte)(cVar2 + 100U)) {
      return 0;
    }
    if (param_1[uVar3 * 0x425 + 0xdb24f] != 0) {
      (**(code **)(param_1[uVar3 * 0x425 + 0xdb24f] + 0x28))
                (param_1 + uVar3 * 0x425 + 0xdae49,(int)cVar2);
    }
    iVar1 = DebugLevel;
    *(char *)(param_1 + uVar3 * 0x425 + 0xdb252) = cVar2;
    if (0 < iVar1) {
      printk("%s(): ssiHigh = %d\n","Set_BndStrg_RssiHigh",(int)cVar2);
    }
  }
  return 1;
}

