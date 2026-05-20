// module: mt7915.ko
// function: WfMacInit @ 0xb2d5c
// size: 352 bytes
//

undefined4 WfMacInit(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  iVar1 = chip_wait_hif_dma_idle(param_1,0xff,100,1000);
  if ((iVar1 == 1) || ((*(uint *)(param_1 + 0xa39f84) & 0x100) == 0)) {
    iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
    if (0 < DebugLevel) {
      printk("%s()-->\n","mac_init");
    }
    AsicInitMac(param_1);
    if (*(code **)(iVar1 + 0x30) != (code *)0x0) {
      (**(code **)(iVar1 + 0x30))(param_1);
    }
    AsicAutoFallbackInit(param_1);
    AsicSetMacMaxLen(param_1);
    if (0 < DebugLevel) {
      printk("<--%s()\n","mac_init");
    }
    asic_init_wtbl(param_1,1);
    AsicRxHeaderTransCtl(param_1,1,0,0,1,0);
    AsicRxHeaderTaranBLCtl(param_1,0,1,0x888e);
    AsicRxHeaderTaranBLCtl(param_1,1,1,0x88b4);
    AsicRxHeaderTaranBLCtl(param_1,2,1,0x890d);
    uVar3 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
    uVar2 = 0;
    if ((uVar3 & 0x400) != 0) {
      AsicAutoBATrigger(param_1,1,1000);
      return 0;
    }
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

