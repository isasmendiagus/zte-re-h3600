// module: mt7915.ko
// function: mt_AsicBfeeStaRecUpdate @ 0x864cc
// size: 576 bytes
//

undefined4 mt_AsicBfeeStaRecUpdate(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char local_22;
  char local_21;
  
  iVar4 = param_1 + param_4 * 0x14c0 + 0xa1d20;
  if (*(char *)(param_1 + 0x79504d) == '\0') {
    bVar1 = (byte)"SetPartProfileParameters"[param_1 + 0x18] >> 4;
  }
  else {
    iVar2 = HcGetBandByWdev(*(undefined4 *)(param_1 + param_4 * 0x14c0 + 0xa1d28));
    if (iVar2 == 0) {
      bVar1 = "SetPartProfileParameters"[param_1 + 0x1a];
    }
    else {
      bVar1 = "rtmp_read_vow_parms_from_file"[param_1];
    }
  }
  if (2 < DebugLevel) {
    printk("%s() dbdc: %u, u1TxPath: %u\n","mt_AsicBfeeStaRecUpdate",
           *(undefined1 *)(param_1 + 0x79504d),bVar1);
  }
  if (iVar4 == 0) {
    if (-1 < DebugLevel) {
      printk("%s() Fail. pEntry null\n","mt_AsicBfeeStaRecUpdate");
      return 0;
    }
    return 0;
  }
  iVar3 = param_1 + param_4 * 0x14c0;
  os_zero_mem(iVar3 + 0xa2984,2);
  iVar2 = wlan_config_get_etxbf(*(undefined4 *)(iVar3 + 0xa1d28));
  if ((iVar2 == 1) || (iVar2 = wlan_config_get_etxbf(*(undefined4 *)(iVar3 + 0xa1d28)), iVar2 == 3))
  {
    if (2 < DebugLevel) {
      printk("%s txbf_get_oui: %u\n","mt_AsicBfeeStaRecUpdate",g_u4TxBfOui);
    }
    if (((g_u4TxBfOui & 4) != 0) && (iVar4 = FUN_00084dc0(iVar4,&local_21,&local_22), iVar4 != 0)) {
      if ((local_21 != '\0') && (bVar1 == 2 && local_22 == '\x01')) {
        *(undefined1 *)(param_4 * 0x14c0 + param_1 + 0xa2984) = 1;
      }
      if (DebugLevel < 3) {
        return 1;
      }
      printk("%s u2WlanIdx: %u fgStaBfer:%u, u1StaNr=%u\n","mt_AsicBfeeStaRecUpdate",param_4,
             local_21,local_22);
    }
  }
  if ((2 < DebugLevel) &&
     (printk("====================== BFee StaRec Info =====================\n"), 2 < DebugLevel)) {
    param_1 = param_4 * 0x14c0 + param_1;
    printk("fgFbIdentityMatrix: %u\n",*(undefined1 *)(param_1 + 0xa2984));
    if (2 < DebugLevel) {
      printk("fgIgnFbk: %u\n",*(undefined1 *)(param_1 + 0xa2985));
    }
  }
  return 1;
}

