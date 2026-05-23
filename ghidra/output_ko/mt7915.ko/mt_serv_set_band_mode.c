// module: mt7915.ko
// function: mt_serv_set_band_mode @ 0x251f5c
// size: 92 bytes
//

int mt_serv_set_band_mode(undefined4 *param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x7d1) == '\0') {
    iVar1 = net_ad_set_band_mode(*param_1,param_1 + 0x131);
    if (iVar1 != 0) {
      printk("%s: err=0x%08x\n","mt_serv_set_band_mode",iVar1);
    }
    return iVar1;
  }
                    /* WARNING: Could not recover jumptable at 0x00251f9c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = (**(code **)(param_1[0x7c4] + 200))(*param_1,param_1 + 0x131);
  return iVar1;
}

