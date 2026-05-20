// module: mt7915.ko
// function: show_vow_dump_sta @ 0x464c8
// size: 388 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 show_vow_dump_sta(int param_1,char *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  uint local_1c;
  
  local_1c = 0;
  if (param_2 == (char *)0x0) {
    local_1c = 0x20;
LAB_00046518:
    uVar4 = 0;
    uVar2 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  }
  else {
    iVar1 = sscanf(param_2,"0x%x",&local_1c);
    if ((iVar1 == 0) && (iVar1 = sscanf(param_2,"%u",&local_1c), iVar1 == 0)) {
      local_1c = 0x22;
    }
    else if (1 < local_1c - 0x22) goto LAB_00046518;
    uVar4 = *(uint *)(param_1 + 0xa797ac);
    uVar2 = *(uint *)(param_1 + 0xa797b0);
  }
  for (; uVar4 < uVar2; uVar4 = uVar4 + 1) {
    if (local_1c == 0) {
      uVar3 = uVar4 << 2 | 0x80000001;
    }
    else {
      uVar3 = (local_1c & 0xff) << 0x10 | 0x80000000 | uVar4;
    }
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x8388,uVar3);
    (*_memcpy)(0xa3d6f8);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8350,&local_2c);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8354,&local_28);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8358,&local_24);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x835c,&local_20);
    if (-1 < DebugLevel) {
      printk("STA%d: 0x%08X, 0x%08X, 0x%08X, 0x%08X.\n",uVar4,local_2c,local_28,local_24,local_20);
    }
  }
  return 1;
}

