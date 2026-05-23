// compatible: zte,zx279127-lsp1crpm
// function: FUN_c064b084 @ 0xc064b084
// found via struct field ptr -> 0xc064b084
// total struct-refs for compat: 1
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_c064b084(undefined4 param_1)

{
  code *pcVar1;
  int iVar2;
  
  _DAT_c06be4fc = FUN_c02c04a4(param_1,0);
  if (_DAT_c06be4fc == 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)software_udf(0x12,0xc064b0ac);
    (*pcVar1)();
  }
  iVar2 = 0;
  _DAT_c06be500 =
       FUN_c02c57d4(0,s_fb_mdio_wclk_div_c05c4b70,s_lb_lsp1_100m_wclk_c05c49cc,0,_DAT_c06be4fc + 4,
                    0xb,7,0,0xc06be4f0);
  _DAT_c06be504 =
       FUN_c02c6574(0,s_fb_mdio_wclk_c05c4b84,s_fb_mdio_wclk_div_c05c4b70,8,_DAT_c06be4fc + 4,1,0,
                    0xc06be4f0);
  _DAT_c06be508 =
       FUN_c02c6574(0,s_fb_mdio_pclk_c05c4b94,s_lb_lsp1_apb_pclk_c05c49f4,8,_DAT_c06be4fc + 4,0,0,
                    0xc06be4f0);
  _DAT_c06be50c =
       FUN_c02c6968(0,s_fb_i2c0_wclk_sel_c05c4ba4,DAT_c064b738,2,0,_DAT_c06be4fc + 8,9,1,0,
                    0xc06be4f0);
  _DAT_c06be510 =
       FUN_c02c6574(0,s_fb_i2c0_wclk_c05c4bb8,s_fb_i2c0_wclk_sel_c05c4ba4,8,_DAT_c06be4fc + 8,1,0,
                    0xc06be4f0);
  _DAT_c06be514 =
       FUN_c02c6574(0,s_fb_i2c0_pclk_c05c4bc8,s_lb_lsp1_apb_pclk_c05c49f4,8,_DAT_c06be4fc + 8,0,0,
                    0xc06be4f0);
  _DAT_c06be518 =
       FUN_c02c6968(0,s_fb_i2c1_wclk_sel_c05c4bd8,DAT_c064b738,2,0,_DAT_c06be4fc + 0xc,9,1,0,
                    0xc06be4f0);
  _DAT_c06be51c =
       FUN_c02c6574(0,s_fb_i2c1_wclk_c05c4bec,s_fb_i2c1_wclk_sel_c05c4bd8,8,_DAT_c06be4fc + 0xc,1,0,
                    0xc06be4f0);
  _DAT_c06be520 =
       FUN_c02c6574(0,s_fb_i2c1_pclk_c05c4bfc,s_lb_lsp1_apb_pclk_c05c49f4,8,_DAT_c06be4fc + 0xc,0,0,
                    0xc06be4f0);
  _DAT_c06be524 =
       FUN_c02c57d4(0,s_fb_usim_wclk_div_c05c4c0c,s_lb_lsp1_25m_wclk_c05c4a08,0,_DAT_c06be4fc + 0x10
                    ,0xb,4,0,0xc06be4f0);
  _DAT_c06be528 =
       FUN_c02c6574(0,s_fb_usim_wclk_c05c4c20,s_fb_usim_wclk_div_c05c4c0c,8,_DAT_c06be4fc + 0x10,1,0
                    ,0xc06be4f0);
  _DAT_c06be52c =
       FUN_c02c6574(0,s_fb_usim_pclk_c05c4c30,s_lb_lsp1_apb_pclk_c05c49f4,8,_DAT_c06be4fc + 0x10,0,0
                    ,0xc06be4f0);
  _DAT_c06be530 =
       FUN_c02c6968(0,s_fb_ssp_wclk_sel_c05c4c40,DAT_c064b73c,2,0,_DAT_c06be4fc + 0x14,9,1,0,
                    0xc06be4f0);
  _DAT_c06be534 =
       FUN_c02c57d4(0,s_fb_ssp_wclk_div_c05c4c50,s_fb_ssp_wclk_sel_c05c4c40,0,_DAT_c06be4fc + 0x14,
                    0xb,4,0,0xc06be4f0);
  _DAT_c06be538 =
       FUN_c02c6574(0,s_fb_ssp_wclk_c05c4c60,s_fb_ssp_wclk_div_c05c4c50,8,_DAT_c06be4fc + 0x14,1,0,
                    0xc06be4f0);
  _DAT_c06be53c =
       FUN_c02c6574(0,s_fb_ssp_pclk_c05c4c6c,s_lb_lsp1_apb_pclk_c05c49f4,8,_DAT_c06be4fc + 0x14,0,0,
                    0xc06be4f0);
  _DAT_c06be540 =
       FUN_c02c6574(0,s_fb_efuse_wclk_c05c4c78,s_lb_lsp1_25m_wclk_c05c4a08,8,_DAT_c06be4fc + 0x28,1,
                    0,0xc06be4f0);
  _DAT_c06be544 =
       FUN_c02c6574(0,s_fb_efuse_pclk_c05c4c88,s_lb_lsp1_apb_pclk_c05c49f4,8,_DAT_c06be4fc + 0x28,0,
                    0,0xc06be4f0);
  _DAT_c06be548 =
       FUN_c02c6574(0,s_fb_zsi_pcm_wclk_c05c4c98,s_fb_tdm_wclk_c05c4ca8,8,_DAT_c06be4fc + 0x1c,1,0,
                    0xc06be4f0);
  _DAT_c06be54c =
       FUN_c02c6574(0,s_fb_zsi_fastclk_c05c4cb4,s_lb_lsp1_49m152_wclk_c05c49e0,8,
                    _DAT_c06be4fc + 0x1c,0,0,0xc06be4f0);
  _DAT_c06be550 =
       FUN_c02c57d4(0,s_fb_tdm_wclk_div_c05c4cc4,s_lb_lsp1_49m152_wclk_c05c49e0,0,
                    _DAT_c06be4fc + 0x24,0xb,6,0,0xc06be4f0);
  _DAT_c06be554 =
       FUN_c02c6574(0,s_fb_tdm_aclk_c05c4cd4,s_lb_lsp1_axi_aclk_c05c49b8,8,_DAT_c06be4fc + 0x24,2,0,
                    0xc06be4f0);
  _DAT_c06be558 =
       FUN_c02c6574(0,s_fb_tdm_wclk_c05c4ca8,s_fb_tdm_wclk_div_c05c4cc4,8,_DAT_c06be4fc + 0x24,1,0,
                    0xc06be4f0);
  _DAT_c06be55c =
       FUN_c02c6574(0,s_fb_tdm_pclk_c05c4ce0,s_lb_lsp1_apb_pclk_c05c49f4,8,_DAT_c06be4fc + 0x24,0,0,
                    0xc06be4f0);
  _DAT_c06be560 =
       FUN_c02c57d4(0,s_fb_isi_pswclk_div_c05c4cec,s_lb_lsp1_49m152_wclk_c05c49e0,0,
                    _DAT_c06be4fc + 0x24,8,4,0,0xc06be4f0);
  _DAT_c06be564 =
       FUN_c02c6574(0,s_fb_isi_pcm_wclk_c05c4d00,s_fb_tdm_wclk_c05c4ca8,8,_DAT_c06be4fc + 0x1c,1,0,
                    0xc06be4f0);
  _DAT_c06be568 =
       FUN_c02c6574(0,s_fb_isi_pswclk_c05c4d10,s_lb_lsp1_49m152_wclk_c05c49e0,8,_DAT_c06be4fc + 0x1c
                    ,0,0,0xc06be4f0);
  do {
    if (0xfffff000 < *(uint *)(&DAT_c06be500 + iVar2 * 4)) {
      FUN_c046918c(&DAT_c05c4d20,iVar2);
      return;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 != 0x1b);
  _DAT_c06be56c = &DAT_c06be500;
  _DAT_c06be570 = iVar2;
  FUN_c02c3208(param_1,FUN_c02c2dc8,&DAT_c06be56c);
  return;
}

