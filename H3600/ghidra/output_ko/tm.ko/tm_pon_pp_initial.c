// module: tm.ko
// function: tm_pon_pp_initial @ 0x4f480
// size: 140 bytes
//

undefined4 tm_pon_pp_initial(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  
  uVar1 = tm_pon_pp_reg_initial();
  uVar2 = tm_pon_pp_sadm_initial();
  uVar3 = tm_pon_pp_brg_initial();
  uVar4 = tm_pon_pp_cla_initial();
  uVar5 = tm_pon_pp_adm_initial();
  uVar6 = tm_pon_pp_dpa_initial();
  uVar7 = tm_pon_pp_pm_initial();
  uVar7 = uVar2 | uVar1 | uVar3 | uVar4 | uVar5 | uVar6 | uVar7;
  if (uVar7 != 0) {
    if ((g_tm_debug_level != 0) && (iVar8 = ___ratelimit(_rs_26537,"tm_pon_pp_initial"), iVar8 != 0)
       ) {
      printk("tm_pon_pp_initialFail, error rcode=%d!\n",uVar7);
    }
    return 0xffffffff;
  }
  return 0;
}

