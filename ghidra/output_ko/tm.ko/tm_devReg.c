// module: tm.ko
// function: tm_devReg @ 0x101b0
// size: 96 bytes
//

int tm_devReg(void)

{
  int iVar1;
  
  iVar1 = __register_chrdev(0xc6,0,0x100,"tm_sample_dev",&tm_devFops);
  if (iVar1 < 0) {
    printk("ERROR:%s failed with %d\n","Sorry, registering the character device ",iVar1);
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

