// module: tm.ko
// function: tm_pon_tm_initial @ 0x54258
// size: 116 bytes
//

undefined4 tm_pon_tm_initial(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  uVar1 = tm_pon_tm_reg_initial();
  uVar2 = tm_pon_tm_red_initial();
  uVar3 = tm_pon_tm_qmg_initial();
  uVar4 = tm_pon_tm_sch_initial();
  uVar4 = uVar2 | uVar1 | uVar3 | uVar4;
  if (uVar4 != 0) {
    if ((g_tm_debug_level != 0) && (iVar5 = ___ratelimit(_rs_26444,"tm_pon_tm_initial"), iVar5 != 0)
       ) {
      printk("tm_pon_tm_initial Fail, error rcode=%d!\n",uVar4);
    }
    return 0xffffffff;
  }
  return 0;
}

