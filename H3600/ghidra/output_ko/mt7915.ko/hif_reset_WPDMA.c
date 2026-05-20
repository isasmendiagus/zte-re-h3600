// module: mt7915.ko
// function: hif_reset_WPDMA @ 0x177bac
// size: 464 bytes
//

undefined4 hif_reset_WPDMA(int param_1)

{
  int iVar1;
  uint local_14;
  
  local_14 = 0;
  iVar1 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar1 = *(int *)(iVar1 + 0xa0);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025100,&local_14);
  local_14 = local_14 & 0xffffffcf;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025100);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025100,&local_14);
  local_14 = local_14 | 0x30;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025100);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c024100,&local_14);
  local_14 = local_14 & 0xffffffcf;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c024100);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c024100,&local_14);
  local_14 = local_14 | 0x30;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c024100);
  DataSynchronizationBarrier(0xf);
  if ((*(uint *)(*(int *)(iVar1 + 0xbc) + 0xd7090) & 0x7fffffff) != 0) {
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c029100,&local_14);
    local_14 = local_14 & 0xffffffcf;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c029100);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c029100,&local_14);
    local_14 = local_14 | 0x30;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c029100);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c028100,&local_14);
    local_14 = local_14 & 0xffffffcf;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c028100);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c028100,&local_14);
    local_14 = local_14 | 0x30;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c028100);
  }
  return 1;
}

