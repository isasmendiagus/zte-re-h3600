// module: mt7915.ko
// function: LowPowerDebug @ 0x1291a4
// size: 300 bytes
//

void LowPowerDebug(int param_1,int param_2)

{
  if (DebugLevel < 3) {
    return;
  }
  printk("\n************ Previous Setting **************************\n");
  if (2 < DebugLevel) {
    printk("%s::pStaCfg(0x%p)\n","LowPowerDebug",param_2);
    if (DebugLevel < 3) {
      return;
    }
    printk("%s::pStaCfg->WindowsBatteryPowerMode(%lu)\n","LowPowerDebug",
           *(undefined4 *)(param_2 + 0x2124b0));
    if (DebugLevel < 3) goto LAB_001292b4;
    printk("%s::pStaCfg->WindowsPowerMode(%lu)\n","LowPowerDebug",
           *(undefined4 *)(param_2 + 0x2124ac));
    if (DebugLevel < 3) {
      return;
    }
    printk("%s::pAd->CommonCfg.bAPSDForcePowerSave(%d)\n","LowPowerDebug",
           *(undefined1 *)(param_1 + 0x794cc6));
  }
  if (DebugLevel < 3) {
    return;
  }
  printk("%s::pStaCfg->PwrMgmt.bDoze(%d)\n","LowPowerDebug",*(undefined1 *)(param_2 + 0x2124c0));
  if (DebugLevel < 3) {
    return;
  }
  printk("%s::pStaCfg->PwrMgmt.psm(%d)\n","LowPowerDebug",*(undefined2 *)(param_2 + 0x2124b8));
LAB_001292b4:
  if (DebugLevel < 3) {
    return;
  }
  printk("*****************************************************\n\n");
  return;
}

