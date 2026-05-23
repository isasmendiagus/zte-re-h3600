// module: mt7915.ko
// function: UAPSD_Release @ 0x1ddb54
// size: 32 bytes
//

void UAPSD_Release(void)

{
  if (DebugLevel < 3) {
    return;
  }
  printk("uapsd> release a spinlock!\n");
  return;
}

