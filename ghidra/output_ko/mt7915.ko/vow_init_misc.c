// module: mt7915.ko
// function: vow_init_misc @ 0x427f4
// size: 412 bytes
//

void vow_init_misc(int param_1)

{
  int iVar1;
  int iVar2;
  uint local_14;
  
  if (*(char *)(param_1 + 0xa797a4) == '\0') {
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f20fc,&local_14);
    local_14 = local_14 | 0x8000000;
    hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f20fc);
    if ((*(uint *)(param_1 + 0xa7a2e8) & 0xff00ff) != 0) {
      if (*(char *)(param_1 + 0xa797a4) == '\0') {
        hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f4000,&local_14);
        local_14 = local_14 | 0x800000;
        hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f4000);
        hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f52e0,&local_14);
        local_14 = local_14 | 0x200000;
        hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f52e0);
        hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x82060370,&local_14);
        local_14 = local_14 | 0x4000000;
        hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x82060370);
      }
      goto LAB_00042918;
    }
  }
  else if ((*(uint *)(param_1 + 0xa7a2e8) & 0xff00ff) != 0) {
LAB_00042918:
    if (*(char *)(param_1 + 0xa7a32c) == '\0') {
      *(undefined1 *)(param_1 + 0xa7a2f4) = 6;
      *(undefined1 *)(param_1 + 0xa7a2f5) = 0xc;
      *(undefined1 *)(param_1 + 0xa7a2f6) = 0x10;
      *(undefined1 *)(param_1 + 0xa7a2f7) = 0x14;
    }
    else {
      *(undefined1 *)(param_1 + 0xa7a2f4) = *(undefined1 *)(param_1 + 0xa7a32d);
      *(undefined1 *)(param_1 + 0xa7a2f5) = *(undefined1 *)(param_1 + 0xa7a32e);
      *(undefined1 *)(param_1 + 0xa7a2f6) = *(undefined1 *)(param_1 + 0xa7a32f);
      *(undefined1 *)(param_1 + 0xa7a2f7) = *(undefined1 *)(param_1 + 0xa7a330);
    }
    iVar1 = 0x20;
    do {
      iVar2 = iVar1 + 1;
      vow_set_sta(param_1,0,iVar1);
      iVar1 = iVar2;
    } while (iVar2 != 0x24);
    return;
  }
  return;
}

