// compatible: zte,zx279127-lsp1crpm
// function: FUN_c064c294 @ 0xc064c294
// found via struct field ptr -> 0xc064c294
// total struct-refs for compat: 1
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_c064c294(undefined4 param_1)

{
  code *pcVar1;
  int iVar2;
  
  _DAT_c06addb4 = FUN_c02bf818(param_1,0);
  if (_DAT_c06addb4 == 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)software_udf(0x12,0xc064c2bc);
    (*pcVar1)();
  }
  iVar2 = 0;
  _DAT_c06addb8 =
       FUN_c02c4b48(0,s_fb_mdio_wclk_div_c05c5e9c,s_lb_lsp1_100m_wclk_c05c5cf8,0,_DAT_c06addb4 + 4,
                    0xb,7,0,0xc06adda8);
  _DAT_c06addbc =
       FUN_c02c58e8(0,s_fb_mdio_wclk_c05c5eb0,s_fb_mdio_wclk_div_c05c5e9c,8,_DAT_c06addb4 + 4,1,0,
                    0xc06adda8);
  _DAT_c06addc0 =
       FUN_c02c58e8(0,s_fb_mdio_pclk_c05c5ec0,s_lb_lsp1_apb_pclk_c05c5d20,8,_DAT_c06addb4 + 4,0,0,
                    0xc06adda8);
  _DAT_c06addc4 =
       FUN_c02c5cdc(0,s_fb_i2c0_wclk_sel_c05c5ed0,DAT_c064c948,2,0,_DAT_c06addb4 + 8,9,1,0,
                    0xc06adda8);
  _DAT_c06addc8 =
       FUN_c02c58e8(0,s_fb_i2c0_wclk_c05c5ee4,s_fb_i2c0_wclk_sel_c05c5ed0,8,_DAT_c06addb4 + 8,1,0,
                    0xc06adda8);
  _DAT_c06addcc =
       FUN_c02c58e8(0,s_fb_i2c0_pclk_c05c5ef4,s_lb_lsp1_apb_pclk_c05c5d20,8,_DAT_c06addb4 + 8,0,0,
                    0xc06adda8);
  _DAT_c06addd0 =
       FUN_c02c5cdc(0,s_fb_i2c1_wclk_sel_c05c5f04,DAT_c064c948,2,0,_DAT_c06addb4 + 0xc,9,1,0,
                    0xc06adda8);
  _DAT_c06addd4 =
       FUN_c02c58e8(0,s_fb_i2c1_wclk_c05c5f18,s_fb_i2c1_wclk_sel_c05c5f04,8,_DAT_c06addb4 + 0xc,1,0,
                    0xc06adda8);
  _DAT_c06addd8 =
       FUN_c02c58e8(0,s_fb_i2c1_pclk_c05c5f28,s_lb_lsp1_apb_pclk_c05c5d20,8,_DAT_c06addb4 + 0xc,0,0,
                    0xc06adda8);
  _DAT_c06adddc =
       FUN_c02c4b48(0,s_fb_usim_wclk_div_c05c5f38,s_lb_lsp1_25m_wclk_c05c5d34,0,_DAT_c06addb4 + 0x10
                    ,0xb,4,0,0xc06adda8);
  _DAT_c06adde0 =
       FUN_c02c58e8(0,s_fb_usim_wclk_c05c5f4c,s_fb_usim_wclk_div_c05c5f38,8,_DAT_c06addb4 + 0x10,1,0
                    ,0xc06adda8);
  _DAT_c06adde4 =
       FUN_c02c58e8(0,s_fb_usim_pclk_c05c5f5c,s_lb_lsp1_apb_pclk_c05c5d20,8,_DAT_c06addb4 + 0x10,0,0
                    ,0xc06adda8);
  _DAT_c06adde8 =
       FUN_c02c5cdc(0,s_fb_ssp_wclk_sel_c05c5f6c,DAT_c064c94c,2,0,_DAT_c06addb4 + 0x14,9,1,0,
                    0xc06adda8);
  _DAT_c06addec =
       FUN_c02c4b48(0,s_fb_ssp_wclk_div_c05c5f7c,s_fb_ssp_wclk_sel_c05c5f6c,0,_DAT_c06addb4 + 0x14,
                    0xb,4,0,0xc06adda8);
  _DAT_c06addf0 =
       FUN_c02c58e8(0,s_fb_ssp_wclk_c05c5f8c,s_fb_ssp_wclk_div_c05c5f7c,8,_DAT_c06addb4 + 0x14,1,0,
                    0xc06adda8);
  _DAT_c06addf4 =
       FUN_c02c58e8(0,s_fb_ssp_pclk_c05c5f98,s_lb_lsp1_apb_pclk_c05c5d20,8,_DAT_c06addb4 + 0x14,0,0,
                    0xc06adda8);
  _DAT_c06addf8 =
       FUN_c02c58e8(0,s_fb_efuse_wclk_c05c5fa4,s_lb_lsp1_25m_wclk_c05c5d34,8,_DAT_c06addb4 + 0x28,1,
                    0,0xc06adda8);
  _DAT_c06addfc =
       FUN_c02c58e8(0,s_fb_efuse_pclk_c05c5fb4,s_lb_lsp1_apb_pclk_c05c5d20,8,_DAT_c06addb4 + 0x28,0,
                    0,0xc06adda8);
  _DAT_c06ade00 =
       FUN_c02c58e8(0,s_fb_zsi_pcm_wclk_c05c5fc4,s_fb_tdm_wclk_c05c5fd4,8,_DAT_c06addb4 + 0x1c,1,0,
                    0xc06adda8);
  _DAT_c06ade04 =
       FUN_c02c58e8(0,s_fb_zsi_fastclk_c05c5fe0,s_lb_lsp1_49m152_wclk_c05c5d0c,8,
                    _DAT_c06addb4 + 0x1c,0,0,0xc06adda8);
  _DAT_c06ade08 =
       FUN_c02c4b48(0,s_fb_tdm_wclk_div_c05c5ff0,s_lb_lsp1_49m152_wclk_c05c5d0c,0,
                    _DAT_c06addb4 + 0x24,0xb,6,0,0xc06adda8);
  _DAT_c06ade0c =
       FUN_c02c58e8(0,s_fb_tdm_aclk_c05c6000,s_lb_lsp1_axi_aclk_c05c5ce4,8,_DAT_c06addb4 + 0x24,2,0,
                    0xc06adda8);
  _DAT_c06ade10 =
       FUN_c02c58e8(0,s_fb_tdm_wclk_c05c5fd4,s_fb_tdm_wclk_div_c05c5ff0,8,_DAT_c06addb4 + 0x24,1,0,
                    0xc06adda8);
  _DAT_c06ade14 =
       FUN_c02c58e8(0,s_fb_tdm_pclk_c05c600c,s_lb_lsp1_apb_pclk_c05c5d20,8,_DAT_c06addb4 + 0x24,0,0,
                    0xc06adda8);
  _DAT_c06ade18 =
       FUN_c02c4b48(0,s_fb_isi_pswclk_div_c05c6018,s_lb_lsp1_49m152_wclk_c05c5d0c,0,
                    _DAT_c06addb4 + 0x24,8,4,0,0xc06adda8);
  _DAT_c06ade1c =
       FUN_c02c58e8(0,s_fb_isi_pcm_wclk_c05c602c,s_fb_tdm_wclk_c05c5fd4,8,_DAT_c06addb4 + 0x1c,1,0,
                    0xc06adda8);
  _DAT_c06ade20 =
       FUN_c02c58e8(0,s_fb_isi_pswclk_c05c603c,s_lb_lsp1_49m152_wclk_c05c5d0c,8,_DAT_c06addb4 + 0x1c
                    ,0,0,0xc06adda8);
  do {
    if (0xfffff000 < *(uint *)(&DAT_c06addb8 + iVar2 * 4)) {
      FUN_c046ab98(&DAT_c05c604c,iVar2);
      return;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 != 0x1b);
  _DAT_c06ade24 = &DAT_c06addb8;
  _DAT_c06ade28 = iVar2;
  FUN_c02c257c(param_1,FUN_c02c213c,&DAT_c06ade24);
  return;
}

