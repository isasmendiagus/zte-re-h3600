// module: mt7915.ko
// function: show_vow_dump_bss @ 0x46838
// size: 440 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 show_vow_dump_bss(int param_1,char *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  uint local_1c;
  
  local_1c = 0;
  if (param_2 == (char *)0x0) {
    if (*(char *)(param_1 + 0xa797a4) != '\0') {
      uVar3 = 0x10;
      local_1c = 0x40;
      uVar2 = 0;
      goto LAB_000468b0;
    }
LAB_00046998:
    local_1c = 0x44;
  }
  else {
    iVar1 = sscanf(param_2,"0x%x",&local_1c);
    if ((iVar1 != 0) || (iVar1 = sscanf(param_2,"%u",&local_1c), iVar1 != 0)) {
      bVar4 = 0x21 < local_1c;
      if (local_1c != 0x22) {
        bVar4 = local_1c != 0x44;
      }
      if (bVar4 && (local_1c != 0x22 && local_1c != 0x45)) {
        uVar2 = 0;
        uVar3 = 0x10;
      }
      else {
        uVar3 = 0x20;
        uVar2 = 0x10;
      }
      goto LAB_000468b0;
    }
    if (*(char *)(param_1 + 0xa797a4) == '\0') goto LAB_00046998;
    local_1c = 0x22;
  }
  uVar3 = 0x20;
  uVar2 = 0x10;
LAB_000468b0:
  do {
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x8388,
                   uVar2 | (local_1c & 0xff) << 0x10 | 0x80000000);
    (*_memcpy)(0xa3d6f8);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8350,&local_2c);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8354,&local_28);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x8358,&local_24);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x835c,&local_20);
    if (-1 < DebugLevel) {
      printk("Group%d Config: 0x%08X, 0x%08X, 0x%08X, 0x%08X.\n",uVar2,local_2c,local_28,local_24,
             local_20);
    }
    uVar2 = uVar2 + 1;
  } while (uVar2 < uVar3);
  return 1;
}

