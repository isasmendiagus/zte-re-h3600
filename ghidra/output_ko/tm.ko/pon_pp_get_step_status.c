// module: tm.ko
// function: pon_pp_get_step_status @ 0x28570
// size: 212 bytes
//

undefined4 pon_pp_get_step_status(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(4,local_14,0,PonPpRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0] & 0x7ffffff;
    if ((g_tm_debug_level == 0) ||
       (iVar1 = ___ratelimit(_rs_7114,"pon_pp_get_step_status"), iVar1 == 0)) {
      return 0;
    }
    printk("[TM][pon_pp_get_step_status]output: step_status = %d\n",*param_1);
    uVar2 = 0;
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7111,"pon_pp_get_step_status"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg read fail\n","pp/src/pp_reg.c",0x17f);
    }
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

