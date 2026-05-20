// module: mt7915.ko
// function: hif_init_WPDMA @ 0x17a2cc
// size: 976 bytes
//

undefined4 hif_init_WPDMA(int param_1)

{
  int iVar1;
  uint uVar2;
  uint local_14;
  
  iVar1 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar1 = *(int *)(iVar1 + 0xa0);
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025208,&local_14);
  local_14 = local_14 | 0x18000000;
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025208);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c024680,4);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c024684,&DAT_00400004);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c024688,0x800000);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025600,0x800004);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025604,0xc00004);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025608,0x1000004);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02560c,0x1400004);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025610,0x1800004);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025614,0x1c00004);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025618,0x2000004);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02561c,0x2400004);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025640,0x2800004);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025644,0x2c00004);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025648,0x3000004);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02564c,0x3400004);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025650,0x3800004);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025654,0x3c00000);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025680,0x3c00004);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025684,0x4000004);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c025688,0x4400004);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02568c,0x4800000);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02420c,0xffffffff);
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02520c,0xffffffff);
  uVar2 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((uVar2 & 0x80000) != 0) {
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c0242f0,1);
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c0252f0,0);
  }
  DataSynchronizationBarrier(0xf);
  if ((*(uint *)(*(int *)(iVar1 + 0xbc) + 0xd7090) & 0x7fffffff) != 0) {
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c029208,&local_14);
    local_14 = local_14 | 0x18000000;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c029208);
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c028684,0x4800004);
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c028688,0x4c00000);
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02960c,0x4c00004);
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c029610,0x5000000);
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c029688,0x5000004);
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02968c,0x5400000);
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02820c,0xffffffff);
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c02920c,0xffffffff);
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c027030,&local_14);
    local_14 = local_14 | 1;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c027030);
  }
  return 1;
}

