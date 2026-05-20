// module: tm.ko
// function: tm_initModule @ 0x78198
// size: 52 bytes
//

undefined4 tm_initModule(void)

{
  tm_devReg();
  tmUsrInterfaceCreate();
  printk("tm_initModule begin...\n");
  aclTestInit();
  tm_initial();
  printk("tm_initModule end...\n");
  return 0;
}

