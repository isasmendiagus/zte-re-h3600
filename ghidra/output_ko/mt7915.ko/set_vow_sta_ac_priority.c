// module: mt7915.ko
// function: set_vow_sta_ac_priority @ 0x44990
// size: 260 bytes
//

undefined4 set_vow_sta_ac_priority(int param_1,char *param_2)

{
  char cVar1;
  uint uVar2;
  uint local_10;
  uint local_c;
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  uVar2 = sscanf(param_2,"%u-%u",&local_c,&local_10);
  if (((1 < uVar2) &&
      (uVar2 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0)), local_c < uVar2)) &&
     (local_10 < 4)) {
    *(char *)(param_1 + (local_c + 0x14f33d) * 8 + 6) = (char)local_10;
    cVar1 = vow_set_sta(param_1,local_c & 0xffff,2);
    if (cVar1 == '\0') {
      if (-1 < DebugLevel) {
        printk("%s: sta %d W AC change rule %d.\n","set_vow_sta_ac_priority",local_c,
               *(undefined1 *)(param_1 + (local_c + 0x14f33d) * 8 + 6));
        return 1;
      }
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("%s: sta %d W ENUM_VOW_DRR_PRIORITY_CFG_ITEM failed.\n","set_vow_sta_ac_priority",
             local_c);
    }
  }
  return 0;
}

