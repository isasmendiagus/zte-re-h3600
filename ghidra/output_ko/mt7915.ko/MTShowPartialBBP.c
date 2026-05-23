// module: mt7915.ko
// function: MTShowPartialBBP @ 0x1c83b4
// size: 124 bytes
//

undefined4 MTShowPartialBBP(int param_1,uint param_2,uint param_3)

{
  undefined4 local_1c [2];
  
  for (; param_2 <= param_3; param_2 = param_2 + 4) {
    phy_io_read32(*(undefined4 *)(param_1 + 0xa797a0),param_2,local_1c);
    if (0 < DebugLevel) {
      printk("%s():0x%04x 0x%08x\n","MTShowPartialBBP",param_2,local_1c[0]);
    }
  }
  return 1;
}

