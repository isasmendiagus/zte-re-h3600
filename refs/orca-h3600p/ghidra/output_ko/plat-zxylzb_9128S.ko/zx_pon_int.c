// module: plat-zxylzb_9128S.ko
// function: zx_pon_int @ 0x1b708
// size: 124 bytes
//

undefined4 zx_pon_int(undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  
  uVar1 = *(uint *)(pon_base + 0x40040) & ~*(uint *)(pon_base + 0x40044);
  if (((uVar1 & 0x40) != 0) && (lp_isr != (code *)0x0)) {
    (*lp_isr)(ZX_INT_PON,*param_2,lp_isr,&lp_isr,param_4);
    param_2[4] = param_2[4] + 1;
  }
  if ((uVar1 & 0x10) != 0) {
    rog_onu_flag = 1;
  }
  return 1;
}

