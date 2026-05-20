// compatible: zte,zx279127-topcrm
// function: FUN_c064b464 @ 0xc064b464
// found via struct field ptr -> 0xc064b464
// total struct-refs for compat: 1
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_c064b464(undefined4 param_1)

{
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  
  _DAT_c06adc90 = FUN_c02bf818(param_1,0);
  if (_DAT_c06adc90 == 0) {
                    /* WARNING: Does not return */
    pcVar1 = (code *)software_udf(0x12,0xc064b48c);
    (*pcVar1)();
  }
  _DAT_c06adc94 = FUN_c02c5718(0,s_main_clk_c05c5a50,0,0x10,25000000);
  _DAT_c06adc98 = FUN_c02c5718(0,s_pll_a9_c05c5a5c,s_main_clk_c05c5a50,0,1600000000);
  _DAT_c06add64 = FUN_c02c5718(0,s_clk_800m_c05c5a64,s_main_clk_c05c5a50,0,800000000);
  _DAT_c06add68 = FUN_c02c5718(0,s_clk_825m_c05c5a70,s_main_clk_c05c5a50,0,825000000);
  _DAT_c06add6c = FUN_c02c5718(0,s_clk_850m_c05c5a7c,s_main_clk_c05c5a50,0,850000000);
  _DAT_c06add70 = FUN_c02c5718(0,s_clk_875m_c05c5a88,s_main_clk_c05c5a50,0,875000000);
  _DAT_c06add74 = FUN_c02c5718(0,s_clk_900m_c05c5a94,s_main_clk_c05c5a50,0,900000000);
  _DAT_c06add78 = FUN_c02c5718(0,s_clk_925m_c05c5aa0,s_main_clk_c05c5a50,0,925000000);
  _DAT_c06add7c = FUN_c02c5718(0,s_clk_950m_c05c5aac,s_main_clk_c05c5a50,0,950000000);
  _DAT_c06add80 = FUN_c02c5718(0,s_clk_975m_c05c5ab8,s_main_clk_c05c5a50,0,975000000);
  _DAT_c06add84 = FUN_c02c5718(0,s_clk_1000m_c05c5ac4,s_main_clk_c05c5a50,0,1000000000);
  _DAT_c06add88 = FUN_c02c5718(0,s_clk_1025m_c05c5ad0,s_main_clk_c05c5a50,0,0x3d184240);
  _DAT_c06add8c = FUN_c02c5718(0,s_clk_1050m_c05c5adc,s_main_clk_c05c5a50,0,1050000000);
  _DAT_c06add90 = FUN_c02c5718(0,s_clk_1075m_c05c5ae8,s_main_clk_c05c5a50,0,0x401332c0);
  _DAT_c06add94 = FUN_c02c5718(0,s_clk_1100m_c05c5af4,s_main_clk_c05c5a50,0,1100000000);
  _DAT_c06adc9c = FUN_c02c5718(0,s_pll_lsp_c05c5b00,s_main_clk_c05c5a50,0,1000000000);
  _DAT_c06adca0 = FUN_c02c5718(0,s_pll_audio_c05c5b08,s_main_clk_c05c5a50,0,983000000);
  _DAT_c06adca4 = FUN_c02c5718(0,s_pll_ddr_c05c5b14,s_main_clk_c05c5a50,0,0x4f64b500);
  _DAT_c06adca8 = FUN_c02c5718(0,s_pll_pon_c05c5b1c,s_main_clk_c05c5a50,0,125000000);
  _DAT_c06adccc = FUN_c02c5718(0,s_clk_300m_c05c5b24,s_pll_a9_c05c5a5c,0,300000000);
  _DAT_c06adcd0 = FUN_c02c5718(0,s_clk_200m_c05c5b30,s_pll_a9_c05c5a5c,0,200000000);
  _DAT_c06add60 = FUN_c02c5718(0,s_clk_20m_c05c5b3c,s_clk_200m_c05c5b30,0,20000000);
  _DAT_c06adcac = FUN_c02c5570(0,s_pll_a9_postdiv_c05c5b44,s_pll_a9_c05c5a5c,0,1,3);
  _DAT_c06adcb0 = FUN_c02c5570(0,s_pll_lsp_postdiv_c05c5b54,s_pll_lsp_c05c5b00,0,1,10);
  _DAT_c06adcb4 = FUN_c02c5570(0,s_pll_ddr_postdiv_c05c5b64,s_pll_ddr_c05c5b14,0,1,5);
  _DAT_c06adcb8 = FUN_c02c5718(0,s_pll_audio_postdiv_c05c5b74,s_pll_audio_c05c5b08,0,0x2ee0000);
  _DAT_c06adcbc = FUN_c02c5570(0,s_clk_166m5_c05c5b88,s_pll_ddr_c05c5b14,0,1,8);
  _DAT_c06adcc0 = FUN_c02c5570(0,s_clk_125m_local_c05c5b94,s_pll_lsp_c05c5b00,0,1,8);
  _DAT_c06adcc4 = FUN_c02c5570(0,s_clk_100m_c05c5ba4,s_pll_lsp_postdiv_c05c5b54,0,1,1);
  _DAT_c06adcd4 = FUN_c02c5570(0,s_clk_266m4_c05c5bb0,s_pll_ddr_postdiv_c05c5b64,0,1,1);
  _DAT_c06adcd8 = FUN_c02c5570(0,s_clk_250m_c05c5bbc,s_pll_lsp_c05c5b00,0,1,4);
  _DAT_c06adcdc = FUN_c02c5570(0,s_clk_50m_c05c5bc8,s_pll_lsp_postdiv_c05c5b54,0,1,2);
  _DAT_c06adce0 = FUN_c02c5570(0,s_matrix_aclk_c05c5bd0,s_matrix_aclk_sel_c05c5bdc,0,1,1);
  _DAT_c06adce4 = FUN_c02c5570(0,s_clk_32k768_c05c5bec,s_pll_audio_postdiv_c05c5b74,0,1,0x5dc);
  _DAT_c06adce8 = FUN_c02c5570(0,s_clk_49m152_c05c5bf8,s_pll_audio_postdiv_c05c5b74,0,1,1);
  _DAT_c06adcec = FUN_c02c5570(0,s_lb_a9mg_clk_c05c5c04,s_a9_wclk_sel_c05c5c10,0,1,1);
  _DAT_c06adcf0 = FUN_c02c5570(0,s_a9_periphclk_c05c5c1c,s_lb_a9mg_clk_c05c5c04,0,1,2);
  _DAT_c06add04 = FUN_c02c5570(0,s_matrix_hclk_c05c5c2c,s_matrix_aclk_c05c5bd0,0,1,2);
  _DAT_c06add00 = FUN_c02c5570(0,s_matrix_pclk_c05c5c38,s_matrix_aclk_c05c5bd0,0,1,2);
  _DAT_c06adcf4 =
       FUN_c02c5cdc(0,s_matrix_aclk_sel_c05c5bdc,&PTR_s_main_clk_c06913c0,4,0,_DAT_c06adc90 + 0xc,
                    0xf,2,0,0xc06adda8);
  uVar4 = *(uint *)(_DAT_c06adc90 + 0x18);
  DataSynchronizationBarrier(0xf);
  uVar2 = FUN_c0180f14(((uVar4 << 0xe) >> 0x14) * 0x19,(uVar4 << 0x1a) >> 0x1d);
  iVar3 = FUN_c0180f14(uVar2,uVar4 & 7);
  _DAT_c06adcc8 = FUN_c02c5718(0,s_clk_plla9_cpu_c05c5c44,s_main_clk_c05c5a50,0,iVar3 * 1000000);
  _DAT_c06adcf8 =
       FUN_c02c5cdc(0,s_a9_wclk_sel_c05c5c10,DAT_c064c28c,4,0,_DAT_c06adc90 + 0xc,0xd,2,0,0xc06adda8
                   );
  _DAT_c06adcfc =
       FUN_c02c5cdc(0,s_nand_wclk_sel_c05c5c54,DAT_c064c290,2,0,_DAT_c06adc90 + 0xc,4,1,0,0xc06adda8
                   );
  _DAT_c06add08 =
       FUN_c02c58e8(0,s_lb_nandflash_100m_wclk_c05c5c64,s_nand_wclk_sel_c05c5c54,8,
                    _DAT_c06adc90 + 0x14,0xf,0,0xc06adda8);
  _DAT_c06add0c =
       FUN_c02c58e8(0,s_lb_nandflash_ahb_hclk_c05c5c7c,s_matrix_hclk_c05c5c2c,8,_DAT_c06adc90 + 0x14
                    ,0xe,0,0xc06adda8);
  _DAT_c06add10 =
       FUN_c02c58e8(0,s_lb_lsp0_100m_wclk_c05c5c94,s_clk_100m_c05c5ba4,8,_DAT_c06adc90 + 0x14,0xd,0,
                    0xc06adda8);
  _DAT_c06add14 =
       FUN_c02c58e8(0,s_lb_lsp0_32k_wclk_c05c5ca8,s_clk_32k768_c05c5bec,8,_DAT_c06adc90 + 0x14,0xc,0
                    ,0xc06adda8);
  _DAT_c06add18 =
       FUN_c02c58e8(0,s_lb_lsp0_apb_pclk_c05c5cbc,s_matrix_pclk_c05c5c38,8,_DAT_c06adc90 + 0x14,0xb,
                    0,0xc06adda8);
  _DAT_c06add1c =
       FUN_c02c58e8(0,s_lb_lsp0_25m_wclk_c05c5cd0,s_main_clk_c05c5a50,8,_DAT_c06adc90 + 0x14,9,0,
                    0xc06adda8);
  _DAT_c06add20 =
       FUN_c02c58e8(0,s_lb_lsp1_axi_aclk_c05c5ce4,s_matrix_aclk_c05c5bd0,8,_DAT_c06adc90 + 0x14,8,0,
                    0xc06adda8);
  _DAT_c06add24 =
       FUN_c02c58e8(0,s_lb_lsp1_100m_wclk_c05c5cf8,s_clk_100m_c05c5ba4,8,_DAT_c06adc90 + 0x14,7,0,
                    0xc06adda8);
  _DAT_c06add28 =
       FUN_c02c58e8(0,s_lb_lsp1_49m152_wclk_c05c5d0c,s_clk_49m152_c05c5bf8,8,_DAT_c06adc90 + 0x14,6,
                    0,0xc06adda8);
  _DAT_c06add2c =
       FUN_c02c58e8(0,s_lb_lsp1_apb_pclk_c05c5d20,s_matrix_pclk_c05c5c38,8,_DAT_c06adc90 + 0x14,5,0,
                    0xc06adda8);
  _DAT_c06add30 =
       FUN_c02c58e8(0,s_lb_lsp1_25m_wclk_c05c5d34,s_main_clk_c05c5a50,8,_DAT_c06adc90 + 0x14,4,0,
                    0xc06adda8);
  _DAT_c06add34 =
       FUN_c02c58e8(0,s_axi_iram_saclk_c05c5d48,s_matrix_aclk_c05c5bd0,8,_DAT_c06adc90 + 0x14,2,0,
                    0xc06adda8);
  _DAT_c06add38 =
       FUN_c02c58e8(0,s_axi_irom_saclk_c05c5d58,s_matrix_aclk_c05c5bd0,8,_DAT_c06adc90 + 0x14,1,0,
                    0xc06adda8);
  _DAT_c06add3c =
       FUN_c02c58e8(0,s_sys_ctrl_pclk_c05c5d68,s_matrix_pclk_c05c5c38,8,_DAT_c06adc90 + 0x14,0,0,
                    0xc06adda8);
  _DAT_c06add40 =
       FUN_c02c5570(0,s_lb_nandflash_wclk_c05c5d78,s_lb_nandflash_100m_wclk_c05c5c64,0,1,4);
  _DAT_c06add44 =
       FUN_c02c58e8(0,s_lb_usb30_aclk_c05c5d8c,s_matrix_aclk_c05c5bd0,8,_DAT_c06adc90 + 0x48,0x15,0,
                    0xc06adda8);
  _DAT_c06add48 =
       FUN_c02c58e8(0,s_usb_suspend_clk_c05c5d9c,s_clk_32k768_c05c5bec,8,_DAT_c06adc90 + 0x48,0x14,0
                    ,0xc06adda8);
  _DAT_c06add4c =
       FUN_c02c58e8(0,s_lb_usb30_ref_clk_c05c5dac,s_clk_20m_c05c5b3c,8,_DAT_c06adc90 + 0x48,0x13,0,
                    0xc06adda8);
  _DAT_c06add50 =
       FUN_c02c58e8(0,s_lb_usb30_u2phy_utmi_refclk_c05c5dc0,s_clk_20m_c05c5b3c,8,
                    _DAT_c06adc90 + 0x48,0x12,0,0xc06adda8);
  _DAT_c06add54 =
       FUN_c02c58e8(0,s_lb_usb30_u3phy_pllrefclkin_c05c5ddc,s_main_clk_c05c5a50,8,
                    _DAT_c06adc90 + 0x48,0x11,0,0xc06adda8);
  _DAT_c06add58 =
       FUN_c02c58e8(0,s_lb_usb20_ahb_hclk_c05c5df8,s_matrix_hclk_c05c5c2c,8,_DAT_c06adc90 + 0x48,0xb
                    ,0,0xc06adda8);
  _DAT_c06add5c =
       FUN_c02c58e8(0,s_lb_usb20_utmi_refclk_c05c5e0c,s_clk_20m_c05c5b3c,8,_DAT_c06adc90 + 0x48,0xc,
                    0,0xc06adda8);
  _DAT_c06add98 =
       FUN_c02c4b48(0,s_fb_sdmmc_wclk_div_c05c5e24,s_matrix_aclk_c05c5bd0,0,_DAT_c06adc90 + 0x10,0xc
                    ,6,0,0xc06adda8);
  _DAT_c06add9c =
       FUN_c02c58e8(0,s_fb_sdmmc_work_clk_c05c5e38,s_fb_sdmmc_wclk_div_c05c5e24,8,
                    _DAT_c06adc90 + 0x48,0x1b,0,0xc06adda8);
  _DAT_c06adda0 =
       FUN_c02c58e8(0,s_fb_sdmmc_ahb_clk_c05c5e4c,s_matrix_hclk_c05c5c2c,8,_DAT_c06adc90 + 0x48,0x1a
                    ,0,0xc06adda8);
  _DAT_c06adda4 =
       FUN_c02c58e8(0,s_fb_sdmmc_cdet_clk_c05c5e60,s_lb_lsp0_32k_wclk_c05c5ca8,8,
                    _DAT_c06adc90 + 0x48,0x19,0,0xc06adda8);
  iVar3 = 0;
  do {
    if (0xfffff000 < *(uint *)(&DAT_c06adc94 + iVar3 * 4)) {
      FUN_c046ab98(&DAT_c05c5e74,iVar3);
      return;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x45);
  _DAT_c06addac = &DAT_c06adc94;
  _DAT_c06addb0 = iVar3;
  FUN_c02c257c(param_1,FUN_c02c213c,&DAT_c06addac);
  return;
}

