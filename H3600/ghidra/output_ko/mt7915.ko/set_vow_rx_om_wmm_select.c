// module: mt7915.ko
// function: set_vow_rx_om_wmm_select @ 0x4596c
// size: 220 bytes
//

undefined4 set_vow_rx_om_wmm_select(int param_1,char *param_2)

{
  uint uVar1;
  int iVar2;
  uint local_18;
  undefined4 local_14 [2];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  uVar1 = sscanf(param_2,"%u-%u",&local_18,local_14);
  if ((1 < uVar1) && (local_18 < 4)) {
    *(char *)(param_1 + local_18 + 0xa797e0) = (char)local_14[0];
    iVar2 = vow_set_wmm_selection(param_1,local_18 & 0xff);
    if (DebugLevel < 0) {
      if (iVar2 == 0) {
        return 1;
      }
    }
    else {
      printk("%s: OM MAC index %d set %u.\n","set_vow_rx_om_wmm_select",local_18,local_14[0]);
      if (iVar2 == 0) {
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("%s: set command failed.\n","set_vow_rx_om_wmm_select");
      }
    }
  }
  return 0;
}

