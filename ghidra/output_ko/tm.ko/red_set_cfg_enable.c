// module: tm.ko
// function: red_set_cfg_enable @ 0x41e88
// size: 248 bytes
//

undefined4 red_set_cfg_enable(uint param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][red_set_cfg_enable]input:red_en = %d, color_en = %d\n",param_1,param_2);
  }
  uVar1 = param_2;
  if (param_2 < 2) {
    uVar1 = param_1;
  }
  if (uVar1 < 2) {
    iVar2 = tmOnuRegWrite(0,param_1 + param_2 * 2,0,RedRegTable);
    if (iVar2 != 0) {
      if ((g_tm_debug_level != 0) &&
         (iVar2 = ___ratelimit(_rs_7061,"red_set_cfg_enable"), iVar2 != 0)) {
        printk("ERROR:(%s:%d) reg write fail\n","tm/src/pon_tm_red.c",0x5c);
      }
      return 0xffffffff;
    }
    return 0;
  }
  if ((g_tm_debug_level != 0) && (iVar2 = ___ratelimit(&_rs_7058,"red_set_cfg_enable"), iVar2 != 0))
  {
    printk("ERROR:(%s:%d) input invalid parameter!\n\n","tm/src/pon_tm_red.c",0x52);
  }
  return 1;
}

