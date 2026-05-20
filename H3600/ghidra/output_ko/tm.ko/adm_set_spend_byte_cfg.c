// module: tm.ko
// function: adm_set_spend_byte_cfg @ 0x2af00
// size: 224 bytes
//

int adm_set_spend_byte_cfg(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][adm_set_spend_byte_cfg]input: SpdByteCfg = %d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  if (0x3f < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7164,"adm_set_spend_byte_cfg"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp_adm.c",0x299);
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(8,param_1,0,AdmRegTable);
  if (((iVar1 != 0) && (g_tm_debug_level != 0)) &&
     (iVar2 = ___ratelimit(_rs_7167,"adm_set_spend_byte_cfg"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","pp_adm.c",0x2a1);
    return iVar1;
  }
  return iVar1;
}

