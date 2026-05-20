// module: tm.ko
// function: adm_get_bucket_fill_time @ 0x2a9bc
// size: 168 bytes
//

int adm_get_bucket_fill_time(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(4,local_14,0,AdmRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    if (6 < g_tm_debug_level) {
      printk("[TM][adm_get_bucket_fill_time]output: time_val = %d\n");
    }
  }
  else if ((g_tm_debug_level != 0) &&
          (iVar2 = ___ratelimit(_rs_7111,"adm_get_bucket_fill_time"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg read fail\n","pp_adm.c",0x19f);
  }
  return iVar1;
}

