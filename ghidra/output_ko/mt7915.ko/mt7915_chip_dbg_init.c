// module: mt7915.ko
// function: mt7915_chip_dbg_init @ 0x194d58
// size: 504 bytes
//

void mt7915_chip_dbg_init(undefined4 *param_1)

{
  param_1[1] = chip_dump_mib_info;
  param_1[2] = chip_show_tmac_info;
  param_1[3] = chip_show_agg_info;
  param_1[5] = chip_show_dmasch_info;
  param_1[6] = chip_show_pse_info;
  param_1[0xb] = chip_show_protect_info;
  param_1[0xc] = chip_show_cca_info;
  param_1[0xd] = chip_set_cca_en;
  param_1[0xf] = chip_check_txv;
  param_1[0x10] = chip_show_bcn_info;
  param_1[8] = chip_show_ple_info;
  param_1[10] = chip_show_drr_info;
  param_1[0x11] = chip_dump_wtbl_info;
  param_1[0x12] = chip_dump_wtbl_mac;
  param_1[0x13] = chip_dump_wtbl_base_info;
  param_1[0x14] = chip_show_amsdu_info;
  param_1[0x15] = chip_set_hw_amsdu;
  param_1[0x16] = chip_set_header_translation;
  param_1[0x17] = chip_show_dma_info;
  param_1[0x19] = chip_show_sta_acq_info;
  param_1[0x1a] = chip_show_txcmdq_info;
  param_1[0x1b] = chip_get_ple_acq_stat;
  param_1[0x1c] = chip_get_ple_txcmd_stat;
  param_1[0x1d] = chip_get_dis_sta_map;
  param_1[0x1e] = chip_get_sta_pause;
  param_1[0x1f] = chip_get_obss_nonwifi_airtime;
  param_1[0x20] = chip_get_sta_airtime;
  param_1[0x23] = chip_get_sta_tx_cnt;
  param_1[0x21] = chip_get_sta_addr;
  param_1[0x22] = chip_get_sta_rate;
  *param_1 = 0;
  param_1[7] = 0;
  param_1[0xe] = 0;
  param_1[0x24] = chip_get_lpon_frcr;
  param_1[0x25] = chip_set_sta_psm;
  param_1[0x26] = chip_ctrl_manual_hetb_tx;
  param_1[0x27] = chip_ctrl_manual_hetb_rx;
  param_1[0x28] = chip_ctrl_asic_spe;
  param_1[0x29] = chip_get_tx_mibinfo;
  param_1[0x18] = chip_show_asic_rx_stat;
  param_1[9] = chip_show_ple_info_by_idx;
  param_1[0x2a] = chip_show_fw_debg_info;
  param_1[0x2b] = chip_set_fw_cp_util_en;
  return;
}

