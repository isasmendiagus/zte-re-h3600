// module: tm.ko
// function: tm_devCleanup @ 0x10210
// size: 36 bytes
//

void tm_devCleanup(void)

{
  __unregister_chrdev(0xc6,0,0x100,"tm_sample_dev");
  tmUsrInterfaceRelease();
  return;
}

