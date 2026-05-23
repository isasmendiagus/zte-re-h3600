// module: tm.ko
// function: brgDebugStatics @ 0x7286c
// size: 52 bytes
//

undefined4 brgDebugStatics(void)

{
  int iVar1;
  undefined1 auStack_b0 [172];
  
  iVar1 = sbrg_get_statistics(auStack_b0);
  if (iVar1 != 0) {
    printk("g_sbrg_statistics fail, error code %d!\n");
  }
  return 1;
}

