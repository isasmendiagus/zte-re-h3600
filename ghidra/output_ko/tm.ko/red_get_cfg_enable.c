// module: tm.ko
// function: red_get_cfg_enable @ 0x41f88
// size: 200 bytes
//

undefined4 red_get_cfg_enable(uint *param_1,uint *param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint local_14;
  
  local_14 = 0;
  iVar1 = tmOnuRegRead(0,&local_14,0,RedRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14 & 1;
    *param_2 = (local_14 << 0x1e) >> 0x1f;
    uVar2 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][red_get_cfg_enable]output: red_en = %d color_en = %d\n",*param_1);
    }
  }
  else {
    if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_7069,"red_get_cfg_enable"), iVar1 != 0)
       ) {
      printk("ERROR:(%s:%d) reg read fail\n","tm/src/pon_tm_red.c",0x7f);
    }
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

