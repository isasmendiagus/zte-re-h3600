// module: mt7915.ko
// function: set_vow_sta_pause @ 0x43cc8
// size: 192 bytes
//

undefined4 set_vow_sta_pause(int param_1,char *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  uint local_10;
  undefined4 local_c;
  
  if (param_2 != (char *)0x0) {
    uVar1 = sscanf(param_2,"%u-%u",&local_10,&local_c);
    if ((uVar1 < 2) ||
       (uVar1 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0)), uVar1 <= local_10)) {
      uVar2 = 0;
    }
    else {
      *(char *)(param_1 + (local_10 + 0x14f33d) * 8 + 7) = (char)local_c;
      vow_set_sta(param_1,local_10 & 0xffff,0x30);
      if (DebugLevel < 0) {
        uVar2 = 1;
      }
      else {
        printk("%s: sta %d set %u.\n","set_vow_sta_pause",local_10,local_c);
        uVar2 = 1;
      }
    }
    return uVar2;
  }
  return 0;
}

