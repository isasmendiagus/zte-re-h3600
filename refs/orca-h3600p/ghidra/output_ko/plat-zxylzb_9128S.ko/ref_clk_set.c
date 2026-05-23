// module: plat-zxylzb_9128S.ko
// function: ref_clk_set @ 0x1c850
// size: 196 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void ref_clk_set(uint param_1)

{
  int iVar1;
  
  printk("enter ref_clk_set.. mode = %d .\n",param_1);
  *(uint *)(top_crm_base + 0x50) = *(uint *)(top_crm_base + 0x50) & 0x7fffffff;
  if ((param_1 & 0xfffffffd) == 1) {
    pll_cfg_integer(top_crm_base + 0x50,1,0x32,4,2);
  }
  else {
    pll_cfg_fractional(top_crm_base + 0x50,1,0x5d,0x4fdf3b,5,3);
  }
  iVar1 = 0x32;
  do {
    (*_request_threaded_irq)(0x66665b0);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  printk("ref_clk_set success!\n");
  return;
}

