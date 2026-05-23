// module: mt7915.ko
// function: MTShowAllBBP @ 0x1c8430
// size: 116 bytes
//

undefined4 MTShowAllBBP(int param_1)

{
  int iVar1;
  undefined4 local_1c [2];
  
  iVar1 = 0x10000;
  do {
    phy_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar1,local_1c);
    if (0 < DebugLevel) {
      printk("%s():0x%04x 0x%08x\n","MTShowAllBBP",iVar1,local_1c[0]);
    }
    iVar1 = iVar1 + 4;
  } while (iVar1 != 0x20004);
  return 1;
}

