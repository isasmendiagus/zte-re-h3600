// module: mt7915.ko
// function: set_vow_sta_psm @ 0x45ec8
// size: 332 bytes
//

int set_vow_sta_psm(int param_1,char *param_2)

{
  int iVar1;
  uint uVar2;
  uint local_24;
  int local_20;
  uint local_1c [2];
  
  iVar1 = hc_get_chip_dbg(*(undefined4 *)(param_1 + 0xa797a0));
  if (((param_2 == (char *)0x0) || (uVar2 = sscanf(param_2,"%u-%u",&local_24,&local_20), uVar2 < 2))
     || (uVar2 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0)), uVar2 <= local_24))
  {
    iVar1 = 0;
  }
  else {
    if (*(char *)(param_1 + 0xa797a4) == '\x03') {
      iVar1 = (**(code **)(iVar1 + 0x94))(param_1,local_24,local_20);
      if (iVar1 != 1) {
        if (DebugLevel < 0) {
          return iVar1;
        }
        printk("%s: set psm failed\n","set_vow_sta_psm");
      }
    }
    else {
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x29000,0x80000000);
      uVar2 = local_24 << 8 | 0x3000c;
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar2,local_1c);
      iVar1 = 1;
      if (local_20 == 0) {
        local_1c[0] = local_1c[0] & 0xbfffffff;
      }
      else {
        local_1c[0] = local_1c[0] | 0x40000000;
      }
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),uVar2);
    }
    if (-1 < DebugLevel) {
      printk("%s: sta%d psm--> %u.\n","set_vow_sta_psm",local_24,local_20);
    }
  }
  return iVar1;
}

