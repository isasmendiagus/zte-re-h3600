// module: mt7915.ko
// function: chip_set_cca_en @ 0x18e0a8
// size: 268 bytes
//

undefined4 chip_set_cca_en(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined *puVar2;
  int iVar3;
  uint local_14 [2];
  
  iVar3 = *(int *)(param_1 + 0x4328);
  cVar1 = os_str_tol(param_2,0,10);
  if (0 < DebugLevel) {
    puVar2 = &_LC227;
    if (cVar1 == '\0') {
      puVar2 = &_LC228;
    }
    printk("Enable CCA on Band0 SEC40: %s\n",puVar2);
  }
  phy_io_read32(*(undefined4 *)(iVar3 + 0xa797a0),0x10618,local_14);
  local_14[0] = local_14[0] | 0x40004;
  if (0 < DebugLevel) {
    printk("-- Force Mode: %d, Force CCA SEC40: %d [0x%08x]\n",1,1,local_14[0]);
  }
  phy_io_write32(*(undefined4 *)(iVar3 + 0xa797a0),0x10618,local_14[0]);
  mac_io_read32(*(undefined4 *)(iVar3 + 0xa797a0),0x820f4000,local_14);
  local_14[0] = local_14[0] & 0xffffffef | 0x200000;
  mac_io_write32(*(undefined4 *)(iVar3 + 0xa797a0),0x820f4000);
  return 1;
}

