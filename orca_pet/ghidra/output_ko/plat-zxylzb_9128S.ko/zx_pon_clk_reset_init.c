// module: plat-zxylzb_9128S.ko
// function: zx_pon_clk_reset_init @ 0x1ca6c
// size: 520 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 zx_pon_clk_reset_init(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  ref_clk_set();
  *(uint *)(top_crm_base + 8) = *(uint *)(top_crm_base + 8) & 0xffffffdf;
  *(uint *)(top_crm_base + 8) = *(uint *)(top_crm_base + 8) & 0xffffffef;
  iVar3 = 10;
  do {
    (*_request_threaded_irq)(0x66665b0);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  *(uint *)(top_crm_base + 8) = *(uint *)(top_crm_base + 8) | 0x20;
  iVar3 = 10;
  do {
    (*_request_threaded_irq)(0x66665b0);
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  reg_def_set();
  serdes_mode_set(param_1,0,0);
  *(uint *)(top_crm_base + 8) = *(uint *)(top_crm_base + 8) | 0x10;
  do {
  } while ((*(uint *)(pon_serdes_base + 0x68) & 0x10) == 0);
  iVar3 = 0x14;
  printk("rxpll_ready\n");
  while ((*_request_threaded_irq)(0x66665b0), (*(uint *)(pon_serdes_base + 0x70) & 0x1000000) == 0)
  {
    iVar3 = iVar3 + -1;
    if (iVar3 == 0) {
      printk("err:pll is not ready for banding\n");
      return 0xffffffff;
    }
  }
  iVar1 = *(int *)(pon_serdes_base + 0x70);
  iVar3 = temp_ctrl_read();
  uVar2 = (uint)(iVar1 << 8) >> 0x1a;
  printk("serdes band cpu_temper:%d coarse:0x%x\n",iVar3,uVar2);
  if (iVar3 < -6) {
    uVar2 = uVar2 + 1;
LAB_0001cbc4:
    if (0x3f < uVar2) {
      uVar2 = 0x3f0000;
      goto LAB_0001cbd4;
    }
  }
  else if (0xf < iVar3 + 6U) {
    if (iVar3 - 10U < 0x31) {
      uVar2 = uVar2 - 1;
    }
    else if (iVar3 - 0x3bU < 0x21) {
      uVar2 = uVar2 - 2;
    }
    else {
      uVar2 = uVar2 - 3;
    }
    goto LAB_0001cbc4;
  }
  uVar2 = uVar2 << 0x10;
LAB_0001cbd4:
  *(uint *)(pon_serdes_base + 0x44) = *(uint *)(pon_serdes_base + 0x44) & 0xffc0ffff | uVar2;
  *(uint *)(pon_serdes_base + 0x40) = *(uint *)(pon_serdes_base + 0x40) | 0x4000000;
  printk("band calc fin\n");
  *(uint *)(sys_ctrl_base + 0x10) = *(uint *)(sys_ctrl_base + 0x10) & 0xfffff7ff;
  *(uint *)(top_crm_base + 0xc) = *(uint *)(top_crm_base + 0xc) | 0x1e0;
  return 0;
}

