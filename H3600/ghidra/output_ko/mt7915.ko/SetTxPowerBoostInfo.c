// module: mt7915.ko
// function: SetTxPowerBoostInfo @ 0xedeb0
// size: 296 bytes
//

bool SetTxPowerBoostInfo(int *param_1)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = *(uint *)(*param_1 + 0x3c);
  iVar1 = hc_get_arch_ops(param_1[0x29e5e8]);
  uVar2 = uVar2 & 0xff;
  if (uVar2 < *(byte *)((int)param_1 + 0x2b7242)) {
    HcGetBandByWdev(param_1 + uVar2 * 0x160d + 0xadc92);
    uVar2 = HcGetBandByWdev(param_1 + 0xdb6d6);
    if (uVar2 < 2) {
      if (((0 < DebugLevel) &&
          (printk("=======================================================\n"), 0 < DebugLevel)) &&
         (printk("Power Up Table (Band%d)\n",uVar2), 0 < DebugLevel)) {
        printk("=======================================================\n");
      }
      if ((iVar1 != 0) && (*(code **)(iVar1 + 0x1f8) != (code *)0x0)) {
        iVar1 = (**(code **)(iVar1 + 0x1f8))(param_1,uVar2);
        return iVar1 != 0;
      }
      return true;
    }
    if (-1 < DebugLevel) {
      printk("Invalid Band Index!!!\n");
    }
  }
  return false;
}

