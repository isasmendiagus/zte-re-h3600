// module: tm.ko
// function: spaDebugStatics @ 0x6f3d4
// size: 52 bytes
//

undefined4 spaDebugStatics(void)

{
  int iVar1;
  undefined1 auStack_88 [132];
  
  iVar1 = spa_get_statistics(auStack_88);
  if (iVar1 != 0) {
    printk("g_spa_statistics fail, error code %d!\n");
  }
  return 0;
}

