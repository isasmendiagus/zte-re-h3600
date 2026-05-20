// module: tm.ko
// function: tm_cleanupModule @ 0x781cc
// size: 4 bytes
//

void tm_cleanupModule(void)

{
  __unregister_chrdev(0xc6,0,0x100,"tm_sample_dev");
  tmUsrInterfaceRelease();
  return;
}

