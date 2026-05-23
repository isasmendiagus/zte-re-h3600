// module: tm.ko
// function: greg_get_oam_action @ 0x33038
// size: 88 bytes
//

undefined4
greg_get_oam_action(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  
  cVar1 = tmOnuRegRead(0x42,param_1,0,&gregRegTable,param_4);
  if (cVar1 == '\0') {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][greg_get_oam_action]read failed\n");
  return 0xffffffff;
}

