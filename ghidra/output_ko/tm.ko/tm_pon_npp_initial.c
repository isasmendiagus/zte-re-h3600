// module: tm.ko
// function: tm_pon_npp_initial @ 0x4f040
// size: 152 bytes
//

undefined4 tm_pon_npp_initial(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  
  uVar1 = tm_pon_npp_greg_initial();
  uVar2 = tm_pon_npp_sdet_initial();
  uVar3 = tm_pon_npp_sipc_initial();
  uVar4 = tm_pon_npp_uopc_initial();
  uVar5 = tm_pon_npp_sopc_initial();
  uVar6 = tm_pon_npp_spa_initial();
  uVar7 = tm_pon_npp_pm_initial();
  uVar8 = tm_pon_npp_smac_initial();
  uVar8 = uVar2 | uVar1 | uVar3 | uVar4 | uVar5 | uVar6 | uVar7 | uVar8;
  if (uVar8 != 0) {
    if ((g_tm_debug_level != 0) &&
       (iVar9 = ___ratelimit(&_rs_26630,"tm_pon_npp_initial"), iVar9 != 0)) {
      printk("tm_pon_npp_initial Fail, error code=%d!\n",uVar8);
    }
    return 0xffffffff;
  }
  return 0;
}

