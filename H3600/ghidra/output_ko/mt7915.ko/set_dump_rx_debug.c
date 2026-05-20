// module: mt7915.ko
// function: set_dump_rx_debug @ 0x1d556c
// size: 88 bytes
//

undefined4 set_dump_rx_debug(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 uVar2;
  
  uVar2 = os_str_tol(param_2,0,10);
  iVar1 = DebugLevel;
  *(undefined1 *)(param_1 + 0xa7d07f) = uVar2;
  if (0 < iVar1) {
    printk("set verification mode rx dump = %d\n",uVar2);
  }
  return 1;
}

