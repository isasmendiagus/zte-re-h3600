// module: mt7915.ko
// function: show_vow_dump_bss_bitmap @ 0x4664c
// size: 492 bytes
//

undefined4 show_vow_dump_bss_bitmap(int param_1,char *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  uint local_1c [2];
  
  local_1c[0] = 0;
  if ((param_2 == (char *)0x0) ||
     ((iVar1 = sscanf(param_2,"0x%x",local_1c), iVar1 == 0 &&
      (iVar1 = sscanf(param_2,"%u",local_1c), iVar1 == 0)))) {
    uVar4 = 0x10;
    uVar3 = 0;
    local_1c[0] = 0x42;
  }
  else if (local_1c[0] - 0x22 < 2) {
    uVar3 = *(uint *)(param_1 + 0xa797b4);
    uVar4 = *(uint *)(param_1 + 0xa797b8);
    if (uVar4 <= uVar3) {
      return 1;
    }
  }
  else {
    uVar4 = 0x10;
    uVar3 = 0;
  }
  do {
    uVar2 = 0x80440000;
    if (*(char *)(param_1 + 0xa797a4) != '\0') {
      uVar2 = (local_1c[0] & 0xff) << 0x10 | 0x80000000;
    }
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x8388,uVar2 | uVar3);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8350,&local_2c);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8354,&local_28);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8358,&local_24);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x835c,&local_20);
    if (-1 < DebugLevel) {
      printk("Group%d BitMap: 0x%08X, 0x%08X, 0x%08X, 0x%08X.\n",uVar3,local_2c,local_28,local_24,
             local_20);
    }
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8690,&local_2c);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8694,&local_28);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8698,&local_24);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x869c,&local_20);
    if (-1 < DebugLevel) {
      printk("Group%d BitMap: 0x%08X, 0x%08X, 0x%08X, 0x%08X.\n",uVar3,local_2c,local_28,local_24,
             local_20);
    }
    uVar3 = uVar3 + 1;
  } while (uVar3 < uVar4);
  return 1;
}

