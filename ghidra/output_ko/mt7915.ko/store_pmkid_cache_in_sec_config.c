// module: mt7915.ko
// function: store_pmkid_cache_in_sec_config @ 0x117138
// size: 300 bytes
//

void store_pmkid_cache_in_sec_config(int param_1,int *param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_2 == (int *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s(): pEntry is null\n","store_pmkid_cache_in_sec_config",param_3,param_4);
      return;
    }
    return;
  }
  if (4 < DebugLevel) {
    printk("EntryType = %d\n",*param_2);
  }
  if (param_3 == -1) {
    param_2[0x1c2] = 0;
    param_2[0x1c3] = 0;
    return;
  }
  if (*param_2 != 0x20001) {
    return;
  }
  iVar1 = param_1 + param_3 * 0x60;
  param_2[0x1c2] = iVar1 + 0x368803;
  param_2[0x1c3] = iVar1 + 0x368813;
  iVar1 = GetStaCfgByWdev(param_1,param_2[2]);
  if (iVar1 == 0) {
    if (-1 < DebugLevel) {
      printk("%s(): pStaCfg is null\n","store_pmkid_cache_in_sec_config");
      return;
    }
    return;
  }
  iVar1 = iVar1 + param_3 * 0x57;
  param_2[0x1c2] = iVar1 + 0x21264f;
  param_2[0x1c3] = iVar1 + 0x21265f;
  return;
}

