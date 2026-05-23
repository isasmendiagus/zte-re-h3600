// module: mt7915.ko
// function: chip_irq_init @ 0x177d7c
// size: 640 bytes
//

void chip_irq_init(int param_1)

{
  int iVar1;
  uint local_14 [2];
  
  iVar1 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar1 = *(int *)(iVar1 + 0xa0);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x18060018,local_14);
  local_14[0] = local_14[0] | 1;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x18060018);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x18060028,local_14);
  local_14[0] = local_14[0] | 1;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x18060028);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025204,local_14);
  local_14[0] = local_14[0] | 0x10000000;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025204);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c0251fc,local_14);
  local_14[0] = local_14[0] | 0x100;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c0251fc);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025204,local_14);
  local_14[0] = local_14[0] | 0x20000000;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025204);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c0251f4,local_14);
  local_14[0] = local_14[0] | 3;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c0251f4);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c024298,local_14);
  local_14[0] = local_14[0] | 3;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c024298);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025298,local_14);
  local_14[0] = local_14[0] | 7;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025298);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02529c,local_14);
  local_14[0] = local_14[0] | 0xc0000;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02529c);
  DataSynchronizationBarrier(0xf);
  if ((*(uint *)(*(int *)(iVar1 + 0xbc) + 0xd7090) & 0x7fffffff) != 0) {
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c028298,local_14);
    local_14[0] = local_14[0] | 2;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c028298);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c029298,local_14);
    local_14[0] = local_14[0] | 4;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c029298);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02929c,local_14);
    local_14[0] = local_14[0] | 8;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02929c);
  }
  return;
}

