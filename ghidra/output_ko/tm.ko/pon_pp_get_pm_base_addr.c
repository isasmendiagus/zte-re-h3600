// module: tm.ko
// function: pon_pp_get_pm_base_addr @ 0x2983c
// size: 208 bytes
//

undefined4 pon_pp_get_pm_base_addr(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(0xe,local_14,0,PonPpRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    if ((g_tm_debug_level == 0) ||
       (iVar1 = ___ratelimit(_rs_7308,"pon_pp_get_pm_base_addr"), iVar1 == 0)) {
      return 0;
    }
    printk("[TM][pon_pp_get_pm_base_addr]output: base_addr = %d\n",*param_1);
    uVar2 = 0;
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7305,"pon_pp_get_pm_base_addr"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg read fail\n","pp/src/pp_reg.c",0x4b4);
    }
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

