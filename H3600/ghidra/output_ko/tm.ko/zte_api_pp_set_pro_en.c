// module: tm.ko
// function: zte_api_pp_set_pro_en @ 0x63ea0
// size: 112 bytes
//

undefined4 zte_api_pp_set_pro_en(uint param_1,uint param_2,uint param_3,undefined4 param_4)

{
  undefined4 uVar1;
  bool bVar2;
  bool bVar3;
  
  bVar3 = param_3 != 0;
  bVar2 = param_3 == 1;
  if (param_3 < 2) {
    bVar3 = 0x51 < param_2;
    bVar2 = param_2 == 0x52;
  }
  if (param_1 < 2 && (!bVar3 || bVar2)) {
    if (param_1 != 0) {
      uVar1 = spa_set_dn_reg_pkt_en(param_2,param_3,param_3,param_4);
      return uVar1;
    }
    uVar1 = spa_set_up_reg_pkt_en();
    return uVar1;
  }
  if (g_tm_debug_level != 0) {
    printk("[TM][zte_zx_api_pp_set_pro_en]input invalid parameter!\n");
  }
  return 1;
}

