// module: mt7915.ko
// function: set_tssi_enable @ 0xba7e8
// size: 200 bytes
//

undefined4 set_tssi_enable(int param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  cVar1 = os_str_tol(param_2,0,10);
  if (cVar1 == '\x01') {
    *(undefined1 *)(iVar2 + 0x128) = 1;
    if (0 < DebugLevel) {
      printk("turn on TSSI mechanism\n");
      return 1;
    }
  }
  else {
    if (cVar1 != '\0') {
      if (DebugLevel < 1) {
        return 0;
      }
      printk("illegal param(%u)\n",cVar1);
      return 0;
    }
    *(undefined1 *)(iVar2 + 0x128) = 0;
    if (0 < DebugLevel) {
      printk("turn off TSS mechanism\n");
    }
  }
  return 1;
}

