// compatible: zte,zx279127-lsp0crpm
// function: FUN_c064b740 @ 0xc064b740
// found via struct field ptr -> 0xc064b740
// total struct-refs for compat: 1
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_c064b740(undefined4 param_1)

{
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  
  _DAT_c06be574 = FUN_c02c04a4(param_1,0);
  if (_DAT_c06be574 == 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)software_udf(0x12,0xc064b768);
    (*pcVar1)();
  }
  iVar3 = 0;
  _DAT_c06be578 =
       FUN_c02c57d4(0,s_fb_timer0_wclk_div_c05c4d4c,s_lb_lsp0_25m_wclk_c05c49a4,0,_DAT_c06be574 + 4,
                    0xb,4,0,0xc06be4f0);
  _DAT_c06be57c =
       FUN_c02c6968(0,s_fb_timer0_wclk_sel_c05c4d60,DAT_c064bd04,2,0,_DAT_c06be574 + 4,9,1,0,
                    0xc06be4f0);
  _DAT_c06be580 =
       FUN_c02c6574(0,s_fb_timer0_wclk_c05c4d74,s_fb_timer0_wclk_sel_c05c4d60,8,_DAT_c06be574 + 4,1,
                    0,0xc06be4f0);
  _DAT_c06be584 =
       FUN_c02c6574(0,s_fb_timer0_pclk_c05c4d84,s_lb_lsp0_apb_pclk_c05c4990,8,_DAT_c06be574 + 4,0,0,
                    0xc06be4f0);
  _DAT_c06be588 =
       FUN_c02c57d4(0,s_fb_timer1_wclk_div_c05c4d94,s_lb_lsp0_25m_wclk_c05c49a4,0,_DAT_c06be574 + 8,
                    0xb,4,0,0xc06be4f0);
  _DAT_c06be58c =
       FUN_c02c6968(0,s_fb_timer1_wclk_sel_c05c4da8,DAT_c064bd04,2,0,_DAT_c06be574 + 8,9,1,0,
                    0xc06be4f0);
  _DAT_c06be590 =
       FUN_c02c6574(0,s_fb_timer1_wclk_c05c4dbc,s_fb_timer1_wclk_sel_c05c4da8,8,_DAT_c06be574 + 8,1,
                    0,0xc06be4f0);
  _DAT_c06be594 =
       FUN_c02c6574(0,s_fb_timer1_pclk_c05c4dcc,s_lb_lsp0_apb_pclk_c05c4990,8,_DAT_c06be574 + 8,0,0,
                    0xc06be4f0);
  _DAT_c06be598 =
       FUN_c02c57d4(0,s_fb_timer2_wclk_div_c05c4ddc,s_lb_lsp0_25m_wclk_c05c49a4,0,
                    _DAT_c06be574 + 0xc,0xb,4,0,0xc06be4f0);
  _DAT_c06be59c =
       FUN_c02c6968(0,s_fb_timer2_wclk_sel_c05c4df0,DAT_c064bd04,2,0,_DAT_c06be574 + 0xc,9,1,0,
                    0xc06be4f0);
  _DAT_c06be5a0 =
       FUN_c02c6574(0,s_fb_timer2_wclk_c05c4e04,s_fb_timer2_wclk_sel_c05c4df0,8,_DAT_c06be574 + 0xc,
                    1,0,0xc06be4f0);
  _DAT_c06be5a4 =
       FUN_c02c6574(0,s_fb_timer2_pclk_c05c4e14,s_lb_lsp0_apb_pclk_c05c4990,8,_DAT_c06be574 + 0xc,0,
                    0,0xc06be4f0);
  _DAT_c06be5a8 =
       FUN_c02c6574(0,s_fb_gpio_pclk_c05c4e24,s_lb_lsp0_apb_pclk_c05c4990,8,_DAT_c06be574 + 0x1c,0,0
                    ,0xc06be4f0);
  _DAT_c06be5ac =
       FUN_c02c6968(0,s_fb_uart0_wclk_sel_c05c4e34,DAT_c064bd08,2,0,_DAT_c06be574 + 0x10,9,1,0,
                    0xc06be4f0);
  _DAT_c06be5b0 =
       FUN_c02c6574(0,s_fb_uart0_wclk_c05c4e48,s_fb_uart0_wclk_sel_c05c4e34,8,_DAT_c06be574 + 0x10,1
                    ,0,0xc06be4f0);
  _DAT_c06be5b4 =
       FUN_c02c6574(0,s_fb_uart0_pclk_c05c4e58,s_lb_lsp0_apb_pclk_c05c4990,8,_DAT_c06be574 + 0x10,0,
                    0,0xc06be4f0);
  _DAT_c06be5b8 =
       FUN_c02c6968(0,s_fb_uart1_wclk_sel_c05c4e68,DAT_c064bd08,2,0,_DAT_c06be574 + 0x14,9,1,0,
                    0xc06be4f0);
  _DAT_c06be5bc =
       FUN_c02c6574(0,s_fb_uart1_wclk_c05c4e7c,s_fb_uart1_wclk_sel_c05c4e68,8,_DAT_c06be574 + 0x14,1
                    ,0,0xc06be4f0);
  _DAT_c06be5c0 =
       FUN_c02c6574(0,s_fb_uart1_pclk_c05c4e8c,s_lb_lsp0_apb_pclk_c05c4990,8,_DAT_c06be574 + 0x14,0,
                    0,0xc06be4f0);
  _DAT_c06be5c4 =
       FUN_c02c57d4(0,s_fb_spi_wclk_div_c05c4e9c,s_lb_lsp0_100m_wclk_c05c4968,0,_DAT_c06be574 + 0x18
                    ,0xb,6,0,0xc06be4f0);
  _DAT_c06be5c8 =
       FUN_c02c6574(0,s_fb_spi_wclk_c05c4eac,s_fb_spi_wclk_div_c05c4e9c,8,_DAT_c06be574 + 0x18,1,0,
                    0xc06be4f0);
  _DAT_c06be5cc =
       FUN_c02c6574(0,s_fb_spi_pclk_c05c4eb8,s_lb_lsp0_apb_pclk_c05c4990,8,_DAT_c06be574 + 0x18,0,0,
                    0xc06be4f0);
  do {
    if (0xfffff000 < *(uint *)(&DAT_c06be578 + iVar3 * 4)) {
      FUN_c046918c(&DAT_c05c4ec4,iVar3);
      return;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x16);
  _DAT_c06be5d0 = &DAT_c06be578;
  _DAT_c06be5d4 = iVar3;
  FUN_c02c3208(param_1,FUN_c02c2dc8,&DAT_c06be5d0);
  uVar2 = _DAT_c06be5b0;
  iVar3 = FUN_c02c3688(_DAT_c06be5b0);
  if ((iVar3 == 0) && (iVar3 = FUN_c02c3090(uVar2), iVar3 != 0)) {
    FUN_c02c3d34(uVar2);
    return;
  }
  return;
}

