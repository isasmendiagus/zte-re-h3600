// module: tm.ko
// function: red_get_share_mode @ 0x424a0
// size: 180 bytes
//

undefined4 red_get_share_mode(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(3,local_14,0,RedRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0] & 1;
    uVar2 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][red_get_share_mode]output: mode = %d\n");
    }
  }
  else {
    if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_7123,"red_get_share_mode"), iVar1 != 0)
       ) {
      printk("ERROR:(%s:%d) reg read fail\n","tm/src/pon_tm_red.c",0x170);
    }
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

