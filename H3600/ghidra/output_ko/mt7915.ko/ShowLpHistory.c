// module: mt7915.ko
// function: ShowLpHistory @ 0x1931bc
// size: 360 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void ShowLpHistory(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint local_24;
  
  local_24 = 0;
  if (param_2 == 0) {
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x89050200,&local_24);
    local_24 = local_24 & 0xfffffffe;
    hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x89050200);
    (*_memcpy)(0xa3d6f8);
  }
  local_24 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x89050200,&local_24);
  uVar2 = local_24 >> 0x10;
  if (0 < DebugLevel) {
    printk("       lp history (from old to new):\n");
  }
  uVar2 = (uVar2 & 0x1f) + 3;
  iVar3 = 0;
  do {
    uVar1 = uVar2 & 0x1f;
    uVar2 = uVar2 + 2;
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),(uVar1 + 0x22414081) * 4,&local_24);
    if (0 < DebugLevel) {
      printk("       %d: 0x%x\n",iVar3,local_24);
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x10);
  if (param_2 == 0) {
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x89050200,&local_24);
    local_24 = local_24 | 1;
    hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x89050200);
  }
  return;
}

