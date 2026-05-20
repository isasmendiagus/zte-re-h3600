// module: tm.ko
// function: adm_get_spend_byte_cfg @ 0x2aff0
// size: 168 bytes
//

int adm_get_spend_byte_cfg(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(8,local_14,0,AdmRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    if (6 < g_tm_debug_level) {
      printk("[TM][adm_get_spend_byte_cfg]output: spd_byte_cfg = %d\n");
    }
  }
  else if ((g_tm_debug_level != 0) &&
          (iVar2 = ___ratelimit(_rs_7174,"adm_get_spend_byte_cfg"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg read fail\n","pp_adm.c",0x2c3);
  }
  return iVar1;
}

