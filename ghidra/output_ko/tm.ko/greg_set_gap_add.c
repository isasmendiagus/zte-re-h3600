// module: tm.ko
// function: greg_set_gap_add @ 0x33120
// size: 144 bytes
//

undefined4 greg_set_gap_add(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  
  if (0xf < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][greg_set_gap_add]param error!\n");
    return 1;
  }
  cVar1 = tmOnuRegWrite(0x44,param_1,0,&gregRegTable,param_4);
  if (cVar1 == '\0') {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][greg_set_gap_add]write failed\n");
  return 0xffffffff;
}

