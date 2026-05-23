// module: tm.ko
// function: greg_set_oam_action @ 0x32fa8
// size: 144 bytes
//

undefined4
greg_set_oam_action(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  
  if (3 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][greg_set_oam_action]param error!\n");
    return 1;
  }
  cVar1 = tmOnuRegWrite(0x42,param_1,0,&gregRegTable,param_4);
  if (cVar1 == '\0') {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][greg_set_oam_action]write failed\n");
  return 0xffffffff;
}

