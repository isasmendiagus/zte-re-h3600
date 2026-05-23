// module: tm.ko
// function: greg_set_tm_oam_en @ 0x33090
// size: 144 bytes
//

undefined4 greg_set_tm_oam_en(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  
  if (1 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][greg_set_tm_oam_en]param error!\n");
    return 1;
  }
  cVar1 = tmOnuRegWrite(0x43,param_1,0,&gregRegTable,param_4);
  if (cVar1 == '\0') {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][greg_set_tm_oam_en]write failed\n");
  return 0xffffffff;
}

