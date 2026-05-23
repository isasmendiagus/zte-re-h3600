// module: mt7915.ko
// function: RT_CfgSetWirelessMode @ 0xb8554
// size: 368 bytes
//

undefined4 RT_CfgSetWirelessMode(int param_1,undefined4 param_2,int param_3)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar3 = os_str_tol(param_2,0,10);
  uVar1 = cfgmode_2_wmode(uVar3 & 0xff);
  iVar4 = wmode_valid_and_correct(param_1);
  if (iVar4 == 0) {
    uVar5 = 0;
    if (-1 < DebugLevel) {
      printk("%s(): Invalid wireless mode(%ld, wmode=0x%x), ChipCap(%s)\n","RT_CfgSetWirelessMode",
             uVar3,uVar1,(&PTR_s_Invalid_00294354)[*(uint *)(iVar2 + 0x2c) & 3]);
    }
  }
  else {
    iVar2 = wmode_band_equal(*(undefined2 *)(param_3 + 0x18),uVar1);
    if (iVar2 == 1) {
      if (0 < DebugLevel) {
        printk("wmode_band_equal(): Band Equal!\n");
      }
    }
    else if (0 < DebugLevel) {
      printk("wmode_band_equal(): Band Not Equal!\n");
    }
    *(undefined2 *)(param_3 + 0x18) = uVar1;
    *(char *)(param_1 + 0x794c48) = (char)uVar1;
    iVar2 = wmode_2_str(uVar1);
    if (iVar2 != 0) {
      if (2 < DebugLevel) {
        printk("%s(): Set WMODE=%s(0x%x)\n","RT_CfgSetWirelessMode",iVar2,uVar1);
      }
      os_free_mem(iVar2);
      return 1;
    }
    uVar5 = 1;
  }
  return uVar5;
}

