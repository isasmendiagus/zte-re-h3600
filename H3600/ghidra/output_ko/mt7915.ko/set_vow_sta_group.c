// module: mt7915.ko
// function: set_vow_sta_group @ 0x43d8c
// size: 240 bytes
//

undefined4 set_vow_sta_group(int param_1,char *param_2)

{
  uint uVar1;
  int iVar2;
  uint local_18;
  undefined4 local_14 [2];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  uVar1 = sscanf(param_2,"%u-%u",&local_18,local_14);
  if ((1 < uVar1) &&
     (uVar1 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0)), local_18 < uVar1)) {
    *(char *)(param_1 + (local_18 + 0x14f33d) * 8 + 4) = (char)local_14[0];
    iVar2 = vow_set_sta(param_1,local_18 & 0xffff,1);
    if (DebugLevel < 0) {
      if (iVar2 == 0) {
        return 1;
      }
    }
    else {
      printk("%s: sta %d group %u.\n","set_vow_sta_group",local_18,local_14[0]);
      if (iVar2 == 0) {
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("%s: set command failed.\n","set_vow_sta_group");
      }
    }
  }
  return 0;
}

