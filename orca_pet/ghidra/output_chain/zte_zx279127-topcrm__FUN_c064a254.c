// compatible: zte,zx279127-topcrm
// function: FUN_c064a254 @ 0xc064a254
// found via struct field ptr -> 0xc064a254
// total struct-refs for compat: 1
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_c064a254(undefined4 param_1)

{
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  
  _DAT_c06be3d8 = FUN_c02c04a4(param_1,0);
  if (_DAT_c06be3d8 == 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)software_udf(0x12,0xc064a27c);
    (*pcVar1)();
  }
  _DAT_c06be3dc = FUN_c02c63a4(0,s_main_clk_c05c4724,0,0x10,25000000);
  _DAT_c06be3e0 = FUN_c02c63a4(0,s_pll_a9_c05c4730,s_main_clk_c05c4724,0,1600000000);
  _DAT_c06be4ac = FUN_c02c63a4(0,s_clk_800m_c05c4738,s_main_clk_c05c4724,0,800000000);
  _DAT_c06be4b0 = FUN_c02c63a4(0,s_clk_825m_c05c4744,s_main_clk_c05c4724,0,825000000);
  _DAT_c06be4b4 = FUN_c02c63a4(0,s_clk_850m_c05c4750,s_main_clk_c05c4724,0,850000000);
  _DAT_c06be4b8 = FUN_c02c63a4(0,s_clk_875m_c05c475c,s_main_clk_c05c4724,0,875000000);
  _DAT_c06be4bc = FUN_c02c63a4(0,s_clk_900m_c05c4768,s_main_clk_c05c4724,0,900000000);
  _DAT_c06be4c0 = FUN_c02c63a4(0,s_clk_925m_c05c4774,s_main_clk_c05c4724,0,925000000);
  _DAT_c06be4c4 = FUN_c02c63a4(0,s_clk_950m_c05c4780,s_main_clk_c05c4724,0,950000000);
  _DAT_c06be4c8 = FUN_c02c63a4(0,s_clk_975m_c05c478c,s_main_clk_c05c4724,0,975000000);
  _DAT_c06be4cc = FUN_c02c63a4(0,s_clk_1000m_c05c4798,s_main_clk_c05c4724,0,1000000000);
  _DAT_c06be4d0 = FUN_c02c63a4(0,s_clk_1025m_c05c47a4,s_main_clk_c05c4724,0,0x3d184240);
  _DAT_c06be4d4 = FUN_c02c63a4(0,s_clk_1050m_c05c47b0,s_main_clk_c05c4724,0,1050000000);
  _DAT_c06be4d8 = FUN_c02c63a4(0,s_clk_1075m_c05c47bc,s_main_clk_c05c4724,0,0x401332c0);
  _DAT_c06be4dc = FUN_c02c63a4(0,s_clk_1100m_c05c47c8,s_main_clk_c05c4724,0,1100000000);
  _DAT_c06be3e4 = FUN_c02c63a4(0,s_pll_lsp_c05c47d4,s_main_clk_c05c4724,0,1000000000);
  _DAT_c06be3e8 = FUN_c02c63a4(0,s_pll_audio_c05c47dc,s_main_clk_c05c4724,0,983000000);
  _DAT_c06be3ec = FUN_c02c63a4(0,s_pll_ddr_c05c47e8,s_main_clk_c05c4724,0,0x4f64b500);
  _DAT_c06be3f0 = FUN_c02c63a4(0,s_pll_pon_c05c47f0,s_main_clk_c05c4724,0,125000000);
  _DAT_c06be414 = FUN_c02c63a4(0,s_clk_300m_c05c47f8,s_pll_a9_c05c4730,0,300000000);
  _DAT_c06be418 = FUN_c02c63a4(0,s_clk_200m_c05c4804,s_pll_a9_c05c4730,0,200000000);
  _DAT_c06be4a8 = FUN_c02c63a4(0,s_clk_20m_c05c4810,s_clk_200m_c05c4804,0,20000000);
  _DAT_c06be3f4 = FUN_c02c61fc(0,s_pll_a9_postdiv_c05c4818,s_pll_a9_c05c4730,0,1,3);
  _DAT_c06be3f8 = FUN_c02c61fc(0,s_pll_lsp_postdiv_c05c4828,s_pll_lsp_c05c47d4,0,1,10);
  _DAT_c06be3fc = FUN_c02c61fc(0,s_pll_ddr_postdiv_c05c4838,s_pll_ddr_c05c47e8,0,1,5);
  _DAT_c06be400 = FUN_c02c63a4(0,s_pll_audio_postdiv_c05c4848,s_pll_audio_c05c47dc,0,0x2ee0000);
  _DAT_c06be404 = FUN_c02c61fc(0,s_clk_166m5_c05c485c,s_pll_ddr_c05c47e8,0,1,8);
  _DAT_c06be408 = FUN_c02c61fc(0,s_clk_125m_local_c05c4868,s_pll_lsp_c05c47d4,0,1,8);
  _DAT_c06be40c = FUN_c02c61fc(0,s_clk_100m_c05c4878,s_pll_lsp_postdiv_c05c4828,0,1,1);
  _DAT_c06be41c = FUN_c02c61fc(0,s_clk_266m4_c05c4884,s_pll_ddr_postdiv_c05c4838,0,1,1);
  _DAT_c06be420 = FUN_c02c61fc(0,s_clk_250m_c05c4890,s_pll_lsp_c05c47d4,0,1,4);
  _DAT_c06be424 = FUN_c02c61fc(0,s_clk_50m_c05c489c,s_pll_lsp_postdiv_c05c4828,0,1,2);
  _DAT_c06be428 = FUN_c02c61fc(0,s_matrix_aclk_c05c48a4,s_matrix_aclk_sel_c05c48b0,0,1,1);
  _DAT_c06be42c = FUN_c02c61fc(0,s_clk_32k768_c05c48c0,s_pll_audio_postdiv_c05c4848,0,1,0x5dc);
  _DAT_c06be430 = FUN_c02c61fc(0,s_clk_49m152_c05c48cc,s_pll_audio_postdiv_c05c4848,0,1,1);
  _DAT_c06be434 = FUN_c02c61fc(0,s_lb_a9mg_clk_c05c48d8,s_a9_wclk_sel_c05c48e4,0,1,1);
  _DAT_c06be438 = FUN_c02c61fc(0,s_a9_periphclk_c05c48f0,s_lb_a9mg_clk_c05c48d8,0,1,2);
  _DAT_c06be44c = FUN_c02c61fc(0,s_matrix_hclk_c05c4900,s_matrix_aclk_c05c48a4,0,1,2);
  _DAT_c06be448 = FUN_c02c61fc(0,s_matrix_pclk_c05c490c,s_matrix_aclk_c05c48a4,0,1,2);
  _DAT_c06be43c =
       FUN_c02c6968(0,s_matrix_aclk_sel_c05c48b0,&PTR_s_main_clk_c06a15e0,4,0,_DAT_c06be3d8 + 0xc,
                    0xf,2,0,0xc06be4f0);
  uVar4 = *(uint *)(_DAT_c06be3d8 + 0x18);
  DataSynchronizationBarrier(0xf);
  uVar2 = FUN_c01811d4(((uVar4 << 0xe) >> 0x14) * 0x19,(uVar4 << 0x1a) >> 0x1d);
  iVar3 = FUN_c01811d4(uVar2,uVar4 & 7);
  _DAT_c06be410 = FUN_c02c63a4(0,s_clk_plla9_cpu_c05c4918,s_main_clk_c05c4724,0,iVar3 * 1000000);
  _DAT_c06be440 =
       FUN_c02c6968(0,s_a9_wclk_sel_c05c48e4,DAT_c064b07c,4,0,_DAT_c06be3d8 + 0xc,0xd,2,0,0xc06be4f0
                   );
  _DAT_c06be444 =
       FUN_c02c6968(0,s_nand_wclk_sel_c05c4928,DAT_c064b080,2,0,_DAT_c06be3d8 + 0xc,4,1,0,0xc06be4f0
                   );
  _DAT_c06be450 =
       FUN_c02c6574(0,s_lb_nandflash_100m_wclk_c05c4938,s_nand_wclk_sel_c05c4928,8,
                    _DAT_c06be3d8 + 0x14,0xf,0,0xc06be4f0);
  _DAT_c06be454 =
       FUN_c02c6574(0,s_lb_nandflash_ahb_hclk_c05c4950,s_matrix_hclk_c05c4900,8,_DAT_c06be3d8 + 0x14
                    ,0xe,0,0xc06be4f0);
  _DAT_c06be458 =
       FUN_c02c6574(0,s_lb_lsp0_100m_wclk_c05c4968,s_clk_100m_c05c4878,8,_DAT_c06be3d8 + 0x14,0xd,0,
                    0xc06be4f0);
  _DAT_c06be45c =
       FUN_c02c6574(0,s_lb_lsp0_32k_wclk_c05c497c,s_clk_32k768_c05c48c0,8,_DAT_c06be3d8 + 0x14,0xc,0
                    ,0xc06be4f0);
  _DAT_c06be460 =
       FUN_c02c6574(0,s_lb_lsp0_apb_pclk_c05c4990,s_matrix_pclk_c05c490c,8,_DAT_c06be3d8 + 0x14,0xb,
                    0,0xc06be4f0);
  _DAT_c06be464 =
       FUN_c02c6574(0,s_lb_lsp0_25m_wclk_c05c49a4,s_main_clk_c05c4724,8,_DAT_c06be3d8 + 0x14,9,0,
                    0xc06be4f0);
  _DAT_c06be468 =
       FUN_c02c6574(0,s_lb_lsp1_axi_aclk_c05c49b8,s_matrix_aclk_c05c48a4,8,_DAT_c06be3d8 + 0x14,8,0,
                    0xc06be4f0);
  _DAT_c06be46c =
       FUN_c02c6574(0,s_lb_lsp1_100m_wclk_c05c49cc,s_clk_100m_c05c4878,8,_DAT_c06be3d8 + 0x14,7,0,
                    0xc06be4f0);
  _DAT_c06be470 =
       FUN_c02c6574(0,s_lb_lsp1_49m152_wclk_c05c49e0,s_clk_49m152_c05c48cc,8,_DAT_c06be3d8 + 0x14,6,
                    0,0xc06be4f0);
  _DAT_c06be474 =
       FUN_c02c6574(0,s_lb_lsp1_apb_pclk_c05c49f4,s_matrix_pclk_c05c490c,8,_DAT_c06be3d8 + 0x14,5,0,
                    0xc06be4f0);
  _DAT_c06be478 =
       FUN_c02c6574(0,s_lb_lsp1_25m_wclk_c05c4a08,s_main_clk_c05c4724,8,_DAT_c06be3d8 + 0x14,4,0,
                    0xc06be4f0);
  _DAT_c06be47c =
       FUN_c02c6574(0,s_axi_iram_saclk_c05c4a1c,s_matrix_aclk_c05c48a4,8,_DAT_c06be3d8 + 0x14,2,0,
                    0xc06be4f0);
  _DAT_c06be480 =
       FUN_c02c6574(0,s_axi_irom_saclk_c05c4a2c,s_matrix_aclk_c05c48a4,8,_DAT_c06be3d8 + 0x14,1,0,
                    0xc06be4f0);
  _DAT_c06be484 =
       FUN_c02c6574(0,s_sys_ctrl_pclk_c05c4a3c,s_matrix_pclk_c05c490c,8,_DAT_c06be3d8 + 0x14,0,0,
                    0xc06be4f0);
  _DAT_c06be488 =
       FUN_c02c61fc(0,s_lb_nandflash_wclk_c05c4a4c,s_lb_nandflash_100m_wclk_c05c4938,0,1,4);
  _DAT_c06be48c =
       FUN_c02c6574(0,s_lb_usb30_aclk_c05c4a60,s_matrix_aclk_c05c48a4,8,_DAT_c06be3d8 + 0x48,0x15,0,
                    0xc06be4f0);
  _DAT_c06be490 =
       FUN_c02c6574(0,s_usb_suspend_clk_c05c4a70,s_clk_32k768_c05c48c0,8,_DAT_c06be3d8 + 0x48,0x14,0
                    ,0xc06be4f0);
  _DAT_c06be494 =
       FUN_c02c6574(0,s_lb_usb30_ref_clk_c05c4a80,s_clk_20m_c05c4810,8,_DAT_c06be3d8 + 0x48,0x13,0,
                    0xc06be4f0);
  _DAT_c06be498 =
       FUN_c02c6574(0,s_lb_usb30_u2phy_utmi_refclk_c05c4a94,s_clk_20m_c05c4810,8,
                    _DAT_c06be3d8 + 0x48,0x12,0,0xc06be4f0);
  _DAT_c06be49c =
       FUN_c02c6574(0,s_lb_usb30_u3phy_pllrefclkin_c05c4ab0,s_main_clk_c05c4724,8,
                    _DAT_c06be3d8 + 0x48,0x11,0,0xc06be4f0);
  _DAT_c06be4a0 =
       FUN_c02c6574(0,s_lb_usb20_ahb_hclk_c05c4acc,s_matrix_hclk_c05c4900,8,_DAT_c06be3d8 + 0x48,0xb
                    ,0,0xc06be4f0);
  _DAT_c06be4a4 =
       FUN_c02c6574(0,s_lb_usb20_utmi_refclk_c05c4ae0,s_clk_20m_c05c4810,8,_DAT_c06be3d8 + 0x48,0xc,
                    0,0xc06be4f0);
  _DAT_c06be4e0 =
       FUN_c02c57d4(0,s_fb_sdmmc_wclk_div_c05c4af8,s_matrix_aclk_c05c48a4,0,_DAT_c06be3d8 + 0x10,0xc
                    ,6,0,0xc06be4f0);
  _DAT_c06be4e4 =
       FUN_c02c6574(0,s_fb_sdmmc_work_clk_c05c4b0c,s_fb_sdmmc_wclk_div_c05c4af8,8,
                    _DAT_c06be3d8 + 0x48,0x1b,0,0xc06be4f0);
  _DAT_c06be4e8 =
       FUN_c02c6574(0,s_fb_sdmmc_ahb_clk_c05c4b20,s_matrix_hclk_c05c4900,8,_DAT_c06be3d8 + 0x48,0x1a
                    ,0,0xc06be4f0);
  _DAT_c06be4ec =
       FUN_c02c6574(0,s_fb_sdmmc_cdet_clk_c05c4b34,s_lb_lsp0_32k_wclk_c05c497c,8,
                    _DAT_c06be3d8 + 0x48,0x19,0,0xc06be4f0);
  iVar3 = 0;
  do {
    if (0xfffff000 < *(uint *)(&DAT_c06be3dc + iVar3 * 4)) {
      FUN_c046918c(&DAT_c05c4b48,iVar3);
      return;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x45);
  _DAT_c06be4f4 = &DAT_c06be3dc;
  _DAT_c06be4f8 = iVar3;
  FUN_c02c3208(param_1,FUN_c02c2dc8,&DAT_c06be4f4);
  return;
}

