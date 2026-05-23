// module: mt7915.ko
// function: vow_show_bss_dtoken @ 0x46cb0
// size: 356 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 vow_show_bss_dtoken(int param_1,char *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  uint local_1c;
  uint local_18;
  uint local_14;
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  iVar1 = sscanf(param_2,"%u",&local_1c);
  if ((iVar1 == 0) || (0xf < local_1c)) {
    uVar2 = 0;
  }
  else {
    if (*(char *)(param_1 + 0xa797a4) == '\0') {
      uVar3 = 0x835c;
      uVar4 = local_1c | 0x80460000;
      uVar2 = 0x8358;
      uVar5 = 0x8388;
    }
    else {
      uVar3 = 0x4035c;
      uVar2 = 0x40358;
      uVar5 = 0x40388;
      uVar4 = local_1c | 0x80480000;
      if (*(char *)(param_1 + 0xa797a4) != '\x03') {
        uVar3 = 0x835c;
        uVar2 = 0x8358;
        uVar5 = 0x8388;
      }
    }
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),uVar5,uVar4);
    (*_memcpy)(0xa3d6f8);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar2,&local_18);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar3,&local_14);
    uVar4 = local_18;
    if (local_18 >> 0x11 != 0) {
      uVar4 = local_18 - 0x3ffff;
    }
    uVar6 = local_14;
    if (local_14 >> 0x11 != 0) {
      uVar6 = local_14 - 0x3ffff;
    }
    if (DebugLevel < 0) {
      uVar2 = 1;
    }
    else {
      printk("Group%d airtime token: max %d(0x%08X), min %d(0x%08X)\n",local_1c,uVar4,local_18,uVar6
             ,local_14);
      uVar2 = 1;
    }
  }
  return uVar2;
}

