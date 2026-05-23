// module: mt7915.ko
// function: Set_BndStrg_DetectInterval @ 0x9bdd4
// size: 240 bytes
//

undefined4
Set_BndStrg_DetectInterval(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = simple_strtol(param_2,0,10,param_4,param_4);
  get_wdev_by_ioctl_idx_and_iftype
            (param_1,*(undefined1 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar3 = HcGetBandByWdev();
  if (0 < DebugLevel) {
    printk("%s band %u\n","Set_BndStrg_DetectInterval",uVar3);
  }
  if (uVar3 < 2) {
    if (param_1[uVar3 * 0x425 + 0xdb24f] != 0) {
      (**(code **)(param_1[uVar3 * 0x425 + 0xdb24f] + 0x2c))
                (param_1 + uVar3 * 0x425 + 0xdae49,iVar2);
    }
    iVar1 = DebugLevel;
    param_1[uVar3 * 0x425 + 0xdb26b] = iVar2;
    if (0 < iVar1) {
      printk("%s(): ulSteeringDetectInterval = %d\n","Set_BndStrg_DetectInterval",iVar2);
    }
  }
  return 1;
}

