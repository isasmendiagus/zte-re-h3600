// module: mt7915.ko
// function: set_vow_rx_bss_wmmset @ 0x45884
// size: 228 bytes
//

undefined4 set_vow_rx_bss_wmmset(int param_1,char *param_2)

{
  uint uVar1;
  int iVar2;
  uint local_18;
  uint local_14 [2];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  uVar1 = sscanf(param_2,"%u-%u",&local_18,local_14);
  if (((1 < uVar1) && (local_14[0] < 4)) && (local_18 < 0x10)) {
    *(char *)(param_1 + local_18 + 0xa79816) = (char)local_14[0];
    iVar2 = vow_set_mbss2wmm_map(param_1,local_18 & 0xff);
    if (DebugLevel < 0) {
      if (iVar2 == 0) {
        return 1;
      }
    }
    else {
      printk("%s: bss_idx %d set %u.\n","set_vow_rx_bss_wmmset",local_18,local_14[0]);
      if (iVar2 == 0) {
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("%s: set command failed.\n","set_vow_rx_bss_wmmset");
      }
    }
  }
  return 0;
}

