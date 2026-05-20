// module: tm.ko
// function: pp_pm_get_indirect_cmd @ 0x2ca50
// size: 200 bytes
//

undefined4 pp_pm_get_indirect_cmd(uint *param_1,uint *param_2,uint *param_3)

{
  char cVar1;
  undefined4 uVar2;
  uint local_1c [2];
  
  local_1c[0] = 0;
  cVar1 = tmOnuRegRead(0,local_1c,0,&ppPmRegTable);
  if (cVar1 == '\0') {
    *param_1 = (local_1c[0] << 4) >> 0x1f;
    *param_2 = (local_1c[0] << 5) >> 0x1b;
    *param_3 = local_1c[0] & 0xfffff;
    uVar2 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][pp_pm_get_indirect_cmd]output: ind_rw_en = %d, ram_id = %d, ram_addr = %d\n",
             *param_1,*param_2);
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    printk("[TM][pp_pm_get_indirect_cmd]reg read failed\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

