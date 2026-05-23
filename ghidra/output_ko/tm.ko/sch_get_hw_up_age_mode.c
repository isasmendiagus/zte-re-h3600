// module: tm.ko
// function: sch_get_hw_up_age_mode @ 0x3ca70
// size: 168 bytes
//

undefined4 sch_get_hw_up_age_mode(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(3,local_14,0,&SchRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0] & 1;
    uVar2 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][sch_get_hw_up_age_mode]output: hwAgeMod = %d\n");
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    printk("ERROR:(%s:%d) reg read fail\n","tm/src/pon_tm_sch.c",0x148);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

