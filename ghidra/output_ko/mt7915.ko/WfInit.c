// module: mt7915.ko
// function: WfInit @ 0xb2f00
// size: 408 bytes
//

int WfInit(int param_1)

{
  int iVar1;
  
  AsicTOPInit();
  if (0 < DebugLevel) {
    printk("Top Init Done!\n");
  }
  iVar1 = WfHifInit(param_1);
  if (iVar1 == 0) {
    if (0 < DebugLevel) {
      printk("Hif Init Done!\n");
    }
    iVar1 = WfMcuInit(param_1);
    if (iVar1 == 0) {
      if (0 < DebugLevel) {
        printk("MCU Init Done!\n");
      }
      iVar1 = WfEPROMInit(param_1);
      if (iVar1 == 0) {
        printk("RTMPSetSkuParam\n");
        printk("CountryPowerLimitRegion=%d\n",*(undefined1 *)(param_1 + 0x794c46));
        printk("CountryPowerLimitRegionABand=%d\n",*(undefined1 *)(param_1 + 0x794c47));
        create_sku_file(param_1);
        RTMPSetSkuParam(param_1);
        RTMPSetBackOffParam(param_1);
        if (0 < DebugLevel) {
          printk("EEPROM Init Done!\n");
        }
        iVar1 = WfMacInit(param_1);
        if (iVar1 == 0) {
          if (0 < DebugLevel) {
            printk("MAC Init Done!\n");
          }
          NICInitBBP(param_1);
          if (DebugLevel < 1) {
            return 0;
          }
          printk("PHY Init Done!\n");
          return 0;
        }
        WfEPROMSysExit(param_1);
      }
      WfMcuSysExit(param_1);
    }
    WfHifSysExit(param_1);
  }
  if (0 < DebugLevel) {
    printk("%s(): initial faild!! ret=%d\n","WfInit",iVar1);
  }
  return iVar1;
}

