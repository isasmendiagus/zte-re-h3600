// compatible: zte,zx279127-lsp0crpm
// function: FUN_c064c950 @ 0xc064c950
// found via struct field ptr -> 0xc064c950
// total struct-refs for compat: 1
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_c064c950(undefined4 param_1)

{
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  
  _DAT_c06ade2c = FUN_c02bf818(param_1,0);
  if (_DAT_c06ade2c == 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)software_udf(0x12,0xc064c978);
    (*pcVar1)();
  }
  iVar3 = 0;
  _DAT_c06ade30 =
       FUN_c02c4b48(0,s_fb_timer0_wclk_div_c05c6078,s_lb_lsp0_25m_wclk_c05c5cd0,0,_DAT_c06ade2c + 4,
                    0xb,4,0,0xc06adda8);
  _DAT_c06ade34 =
       FUN_c02c5cdc(0,s_fb_timer0_wclk_sel_c05c608c,DAT_c064cf14,2,0,_DAT_c06ade2c + 4,9,1,0,
                    0xc06adda8);
  _DAT_c06ade38 =
       FUN_c02c58e8(0,s_fb_timer0_wclk_c05c60a0,s_fb_timer0_wclk_sel_c05c608c,8,_DAT_c06ade2c + 4,1,
                    0,0xc06adda8);
  _DAT_c06ade3c =
       FUN_c02c58e8(0,s_fb_timer0_pclk_c05c60b0,s_lb_lsp0_apb_pclk_c05c5cbc,8,_DAT_c06ade2c + 4,0,0,
                    0xc06adda8);
  _DAT_c06ade40 =
       FUN_c02c4b48(0,s_fb_timer1_wclk_div_c05c60c0,s_lb_lsp0_25m_wclk_c05c5cd0,0,_DAT_c06ade2c + 8,
                    0xb,4,0,0xc06adda8);
  _DAT_c06ade44 =
       FUN_c02c5cdc(0,s_fb_timer1_wclk_sel_c05c60d4,DAT_c064cf14,2,0,_DAT_c06ade2c + 8,9,1,0,
                    0xc06adda8);
  _DAT_c06ade48 =
       FUN_c02c58e8(0,s_fb_timer1_wclk_c05c60e8,s_fb_timer1_wclk_sel_c05c60d4,8,_DAT_c06ade2c + 8,1,
                    0,0xc06adda8);
  _DAT_c06ade4c =
       FUN_c02c58e8(0,s_fb_timer1_pclk_c05c60f8,s_lb_lsp0_apb_pclk_c05c5cbc,8,_DAT_c06ade2c + 8,0,0,
                    0xc06adda8);
  _DAT_c06ade50 =
       FUN_c02c4b48(0,s_fb_timer2_wclk_div_c05c6108,s_lb_lsp0_25m_wclk_c05c5cd0,0,
                    _DAT_c06ade2c + 0xc,0xb,4,0,0xc06adda8);
  _DAT_c06ade54 =
       FUN_c02c5cdc(0,s_fb_timer2_wclk_sel_c05c611c,DAT_c064cf14,2,0,_DAT_c06ade2c + 0xc,9,1,0,
                    0xc06adda8);
  _DAT_c06ade58 =
       FUN_c02c58e8(0,s_fb_timer2_wclk_c05c6130,s_fb_timer2_wclk_sel_c05c611c,8,_DAT_c06ade2c + 0xc,
                    1,0,0xc06adda8);
  _DAT_c06ade5c =
       FUN_c02c58e8(0,s_fb_timer2_pclk_c05c6140,s_lb_lsp0_apb_pclk_c05c5cbc,8,_DAT_c06ade2c + 0xc,0,
                    0,0xc06adda8);
  _DAT_c06ade60 =
       FUN_c02c58e8(0,s_fb_gpio_pclk_c05c6150,s_lb_lsp0_apb_pclk_c05c5cbc,8,_DAT_c06ade2c + 0x1c,0,0
                    ,0xc06adda8);
  _DAT_c06ade64 =
       FUN_c02c5cdc(0,s_fb_uart0_wclk_sel_c05c6160,DAT_c064cf18,2,0,_DAT_c06ade2c + 0x10,9,1,0,
                    0xc06adda8);
  _DAT_c06ade68 =
       FUN_c02c58e8(0,s_fb_uart0_wclk_c05c6174,s_fb_uart0_wclk_sel_c05c6160,8,_DAT_c06ade2c + 0x10,1
                    ,0,0xc06adda8);
  _DAT_c06ade6c =
       FUN_c02c58e8(0,s_fb_uart0_pclk_c05c6184,s_lb_lsp0_apb_pclk_c05c5cbc,8,_DAT_c06ade2c + 0x10,0,
                    0,0xc06adda8);
  _DAT_c06ade70 =
       FUN_c02c5cdc(0,s_fb_uart1_wclk_sel_c05c6194,DAT_c064cf18,2,0,_DAT_c06ade2c + 0x14,9,1,0,
                    0xc06adda8);
  _DAT_c06ade74 =
       FUN_c02c58e8(0,s_fb_uart1_wclk_c05c61a8,s_fb_uart1_wclk_sel_c05c6194,8,_DAT_c06ade2c + 0x14,1
                    ,0,0xc06adda8);
  _DAT_c06ade78 =
       FUN_c02c58e8(0,s_fb_uart1_pclk_c05c61b8,s_lb_lsp0_apb_pclk_c05c5cbc,8,_DAT_c06ade2c + 0x14,0,
                    0,0xc06adda8);
  _DAT_c06ade7c =
       FUN_c02c4b48(0,s_fb_spi_wclk_div_c05c61c8,s_lb_lsp0_100m_wclk_c05c5c94,0,_DAT_c06ade2c + 0x18
                    ,0xb,6,0,0xc06adda8);
  _DAT_c06ade80 =
       FUN_c02c58e8(0,s_fb_spi_wclk_c05c61d8,s_fb_spi_wclk_div_c05c61c8,8,_DAT_c06ade2c + 0x18,1,0,
                    0xc06adda8);
  _DAT_c06ade84 =
       FUN_c02c58e8(0,s_fb_spi_pclk_c05c61e4,s_lb_lsp0_apb_pclk_c05c5cbc,8,_DAT_c06ade2c + 0x18,0,0,
                    0xc06adda8);
  do {
    if (0xfffff000 < *(uint *)(&DAT_c06ade30 + iVar3 * 4)) {
      FUN_c046ab98(&DAT_c05c61f0,iVar3);
      return;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x16);
  _DAT_c06ade88 = &DAT_c06ade30;
  _DAT_c06ade8c = iVar3;
  FUN_c02c257c(param_1,FUN_c02c213c,&DAT_c06ade88);
  uVar2 = _DAT_c06ade68;
  iVar3 = FUN_c02c29fc(_DAT_c06ade68);
  if ((iVar3 == 0) && (iVar3 = FUN_c02c2404(uVar2), iVar3 != 0)) {
    FUN_c02c30a8(uVar2);
    return;
  }
  return;
}

