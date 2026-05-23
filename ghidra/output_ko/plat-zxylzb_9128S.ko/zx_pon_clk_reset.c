// module: plat-zxylzb_9128S.ko
// function: zx_pon_clk_reset @ 0x1c624
// size: 32 bytes
//

void zx_pon_clk_reset(void)

{
  *(uint *)(top_crm_base + 0xc) = *(uint *)(top_crm_base + 0xc) | 0x1e0;
  return;
}

