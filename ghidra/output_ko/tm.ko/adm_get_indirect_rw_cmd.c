// module: tm.ko
// function: adm_get_indirect_rw_cmd @ 0x2ab34
// size: 208 bytes
//

undefined4 adm_get_indirect_rw_cmd(uint *param_1,uint *param_2,uint *param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint local_1c [2];
  
  local_1c[0] = 0;
  iVar1 = tmOnuRegRead(5,local_1c,0,AdmRegTable);
  if (iVar1 == 0) {
    *param_1 = (local_1c[0] << 4) >> 0x1f;
    *param_2 = (local_1c[0] << 5) >> 0x1b;
    *param_3 = local_1c[0] & 0x3fffff;
    uVar2 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][adm_get_indirect_rw_cmd]output: ind_rw_en = %d, RAMID = %d, ram_addr = %d\n",
             *param_1,*param_2);
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7128,"adm_get_indirect_rw_cmd"), iVar1 != 0)) {
      printk("[TM][adm_get_indirect_rw_cmd]reg read failed\n");
    }
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

