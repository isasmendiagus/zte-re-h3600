// module: tm.ko
// function: adm_set_indirect_rw_cmd @ 0x2aa70
// size: 192 bytes
//

undefined4 adm_set_indirect_rw_cmd(int param_1,uint param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  if (g_tm_debug_level < 7) {
    bVar3 = 2 < param_2;
    bVar2 = param_2 == 3;
    if (param_2 < 4) {
      bVar3 = param_1 != 0;
      bVar2 = param_1 == 1;
    }
    if (!bVar3 || bVar2) {
LAB_0002aaa8:
      iVar1 = tmOnuRegWrite(5,param_3 + param_2 * 0x400000 + param_1 * 0x8000000,0,AdmRegTable);
      if (iVar1 == 0) {
        return 0;
      }
      if (g_tm_debug_level < 7) {
        return 0xffffffff;
      }
      printk("[TM][adm_set_indirect_rw_cmd]reg write failed\n");
      return 0xffffffff;
    }
  }
  else {
    printk("[TM][adm_set_indirect_rw_cmd]input: indrw_en = %d, ram_id = %d, ram_addr = %d\n",param_1
           ,param_2,param_3,param_4);
    bVar3 = 2 < param_2;
    bVar2 = param_2 == 3;
    if (param_2 < 4) {
      bVar3 = param_1 != 0;
      bVar2 = param_1 == 1;
    }
    if (!bVar3 || bVar2) goto LAB_0002aaa8;
    if (6 < g_tm_debug_level) {
      printk("[TM][adm_set_indirect_rw_cmd]input invalid parameter!\n");
    }
  }
  return 1;
}

