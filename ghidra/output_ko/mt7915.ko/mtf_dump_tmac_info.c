// module: mt7915.ko
// function: mtf_dump_tmac_info @ 0x19b530
// size: 2916 bytes
//

void mtf_dump_tmac_info(int param_1,uint *param_2)

{
  undefined1 *puVar1;
  uint uVar2;
  uint uVar3;
  
  puVar1 = (undefined1 *)hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  hex_dump("txd raw data: ",param_2,*puVar1);
  if (0 < DebugLevel) {
    printk("TMAC_TXD Fields:\n");
    if (0 < DebugLevel) {
      printk("\tTMAC_TXD_0:\n");
      if (0 < DebugLevel) {
        printk("\t\tTxByteCnt = %d\n",*param_2 & 0xffff);
        if (DebugLevel < 1) goto LAB_0019b6cc;
        uVar2 = (*param_2 << 7) >> 0x1e;
        printk("\t\tpkt_ft = %d(%s)\n",uVar2,*(undefined4 *)(pkt_ft_str + uVar2 * 4));
        if (0 < DebugLevel) {
          printk("\t\tQueID =0x%x\n",*param_2 >> 0x19);
          goto LAB_0019b68c;
        }
      }
      goto LAB_0019b574;
    }
LAB_0019b68c:
    if (0 < DebugLevel) {
      printk("\tTMAC_TXD_1:\n");
      if (0 < DebugLevel) {
        printk("\t\tWlan Index = %d\n",param_2[1] & 0x3ff);
LAB_0019b6cc:
        if ((0 < DebugLevel) &&
           (printk("\t\tVTA = %d\n",(param_2[1] << 0x15) >> 0x1f), 0 < DebugLevel)) {
          uVar2 = (param_2[1] << 0xe) >> 0x1e;
          printk("\t\tHdrFmt = %d(%s)\n",uVar2,*(undefined4 *)(hdr_fmt_str + uVar2 * 4));
          goto LAB_0019b724;
        }
      }
      goto LAB_0019b574;
    }
LAB_0019b724:
    uVar3 = param_2[1];
    uVar2 = (uVar3 << 0xe) >> 0x1e;
    if (uVar2 != 2) {
      if (uVar2 != 3) {
        if (uVar2 == 0) goto LAB_0019b744;
        goto LAB_0019b798;
      }
      goto LAB_0019b5d8;
    }
LAB_0019b77c:
    if (DebugLevel < 1) goto LAB_0019b594;
    printk("\t\t\tHeader Len = %d(WORD)\n",(uVar3 << 0x10) >> 0x1b);
LAB_0019b798:
    if ((((((((((DebugLevel < 1) ||
               (printk("\t\tHdrPad = %d\n",(param_2[1] << 0xc) >> 0x1e), DebugLevel < 1)) ||
              (printk("\t\tTID = %d\n",(param_2[1] << 9) >> 0x1d), DebugLevel < 1)) ||
             ((printk("\t\tamsdu = %d\n",(param_2[1] << 8) >> 0x1f), DebugLevel < 1 ||
              (printk("\t\town_mac = %d\n",(param_2[1] << 2) >> 0x1a), DebugLevel < 1)))) ||
            (printk("\t\tTGID = %d\n",(param_2[1] << 1) >> 0x1f), DebugLevel < 1)) ||
           (((printk("\t\tTxDFormatType = %d\n",param_2[1] >> 0x1f), DebugLevel < 1 ||
             (printk("\tTMAC_TXD_2:\n"), DebugLevel < 1)) ||
            ((printk("\t\tsub_type = %d\n",param_2[2] & 0xf), DebugLevel < 1 ||
             (((printk("\t\tfrm_type = %d\n",(param_2[2] << 0x1a) >> 0x1e), DebugLevel < 1 ||
               (printk("\t\tNDP = %d\n",(param_2[2] << 0x19) >> 0x1f), DebugLevel < 1)) ||
              (printk("\t\tNDPA = %d\n",(param_2[2] << 0x18) >> 0x1f), DebugLevel < 1)))))))) ||
          ((printk("\t\tSounding = %d\n",(param_2[2] << 0x17) >> 0x1f), DebugLevel < 1 ||
           (printk("\t\tRTS = %d\n",(param_2[2] << 0x16) >> 0x1f), DebugLevel < 1)))) ||
         ((printk("\t\tbc_mc_pkt = %d\n",(param_2[2] << 0x15) >> 0x1f), DebugLevel < 1 ||
          ((((printk("\t\tBIP = %d\n",(param_2[2] << 0x14) >> 0x1f), DebugLevel < 1 ||
             (printk("\t\tDuration = %d\n",(param_2[2] << 0x13) >> 0x1f), DebugLevel < 1)) ||
            ((printk("\t\tHE(HTC Exist) = %d\n",(param_2[2] << 0x12) >> 0x1f), DebugLevel < 1 ||
             (((printk("\t\tFRAG = %d\n",(param_2[2] << 0x10) >> 0x1e), DebugLevel < 1 ||
               (printk("\t\tReamingLife/MaxTx time = %d (unit: 64TU)\n",(param_2[2] << 9) >> 0x19),
               DebugLevel < 1)) ||
              (printk("\t\tpwr_offset = %d\n",(param_2[2] << 2) >> 0x1a), DebugLevel < 1)))))) ||
           ((printk("\t\tfix rate mode = %d\n",(param_2[2] << 1) >> 0x1f), DebugLevel < 1 ||
            (printk("\t\tfix rate = %d\n",param_2[2] >> 0x1f), DebugLevel < 1)))))))) ||
        ((printk("\tTMAC_TXD_3:\n"), DebugLevel < 1 ||
         (((((printk("\t\tNoAck = %d\n",param_2[3] & 1), DebugLevel < 1 ||
             (printk("\t\tPF = %d\n",(param_2[3] << 0x1e) >> 0x1f), DebugLevel < 1)) ||
            ((printk("\t\tEMRD = %d\n",(param_2[3] << 0x1d) >> 0x1f), DebugLevel < 1 ||
             ((((printk("\t\tEEOSP = %d\n",(param_2[3] << 0x1c) >> 0x1f), DebugLevel < 1 ||
                (printk("\t\tda_select = %d\n",(param_2[3] << 0x1b) >> 0x1f), DebugLevel < 1)) ||
               (printk("\t\ttm = %d\n",(param_2[3] << 0x1a) >> 0x1f), DebugLevel < 1)) ||
              ((printk("\t\ttx_cnt = %d\n",(param_2[3] << 0x15) >> 0x1b), DebugLevel < 1 ||
               (printk("\t\tremain_tx_cnt = %d\n",(param_2[3] << 0x10) >> 0x1b), DebugLevel < 1)))))
             ))) || ((printk("\t\tsn = %d\n",(param_2[3] << 4) >> 0x14), DebugLevel < 1 ||
                     ((printk("\t\tba dis = %d\n",(param_2[3] << 3) >> 0x1f), DebugLevel < 1 ||
                      (printk("\t\tpwr_mgmt = 0x%x\n",(param_2[3] << 2) >> 0x1f), DebugLevel < 1))))
                    )) ||
          ((printk("\t\tpn_vld = %d\n",(param_2[3] << 1) >> 0x1f), DebugLevel < 1 ||
           (((printk("\t\tsn_vld = %d\n",param_2[3] >> 0x1f), DebugLevel < 1 ||
             (printk("\tTMAC_TXD_4:\n"), DebugLevel < 1)) ||
            (printk("\t\tpn_low = 0x%x\n",param_2[4]), DebugLevel < 1)))))))))) ||
       ((((printk("\tTMAC_TXD_5:\n"), DebugLevel < 1 ||
          (printk("\t\tpid = %d\n",param_2[5] & 0xff), DebugLevel < 1)) ||
         (printk("\t\ttx_status_fmt = %d\n",(param_2[5] << 0x17) >> 0x1f), DebugLevel < 1)) ||
        (((printk("\t\ttx_status_2_mcu = %d\n",(param_2[5] << 0x16) >> 0x1f), DebugLevel < 1 ||
          (printk("\t\ttx_status_2_host = %d\n",(param_2[5] << 0x15) >> 0x1f), DebugLevel < 1)) ||
         ((printk("\t\tADD_BA = %d\n",(param_2[5] << 0x11) >> 0x1f), DebugLevel < 1 ||
          ((printk("\t\tMD = %d\n",(param_2[5] << 0x10) >> 0x1f), DebugLevel < 1 ||
           (printk("\t\tpn_high = 0x%x\n",param_2[5] >> 0x10), DebugLevel < 1))))))))))
    goto LAB_0019b594;
    printk("\tTMAC_TXD_6:\n");
    if (-1 < (int)param_2[2]) goto LAB_0019b5a0;
    if (DebugLevel < 1) goto LAB_0019b5a8;
    printk("\t\tbw = %d\n",param_2[6] & 7);
    if (0 < DebugLevel) {
      printk("\t\tdyn_bw = %d\n",(param_2[6] << 0x1c) >> 0x1f);
      if (DebugLevel < 1) goto LAB_0019b5bc;
      printk("\t\tant_id = %d\n",(param_2[6] << 0x18) >> 0x1c);
      if (0 < DebugLevel) {
        printk("\t\tspe_idx_sel = %d\n",(param_2[6] << 0x15) >> 0x1f);
        if (DebugLevel < 1) goto LAB_0019b5a8;
        printk("\t\tldpc = %d\n",(param_2[6] << 0x14) >> 0x1f);
        goto LAB_0019be24;
      }
LAB_0019be6c:
      if (0 < DebugLevel) {
        printk("\t\ttx_rate = 0x%x\n",(param_2[6] << 2) >> 0x12);
        goto LAB_0019b5a0;
      }
      goto LAB_0019bef4;
    }
LAB_0019be24:
    if (DebugLevel < 1) goto LAB_0019beb0;
    printk("\t\tHELTF Type = %d\n",(param_2[6] << 0x12) >> 0x1e);
    if (0 < DebugLevel) {
      printk("\t\tGI = %d\n",(param_2[6] << 0x10) >> 0x1e);
      goto LAB_0019be6c;
    }
    goto LAB_0019b5bc;
  }
LAB_0019b574:
  uVar3 = param_2[1];
  uVar2 = (uVar3 << 0xe) >> 0x1e;
  if (uVar2 == 2) goto LAB_0019b77c;
  if (uVar2 == 3) {
LAB_0019b5d8:
    if (DebugLevel < 1) goto LAB_0019b594;
    printk("\t\t\tEOSP = %d, AMS = %d\n",(uVar3 << 0x13) >> 0x1f,(uVar3 << 0x12) >> 0x1f);
    goto LAB_0019b798;
  }
  if (uVar2 == 0) {
LAB_0019b744:
    if (0 < DebugLevel) {
      printk("\t\t\tMRD = %d, EOSP = %d,\t\t\t\tRMVL = %d, VLAN = %d, ETYP = %d\n",
             (uVar3 << 0x14) >> 0x1f,(uVar3 << 0x13) >> 0x1f,(uVar3 << 0x12) >> 0x1f,
             (uVar3 << 0x11) >> 0x1f,(uVar3 << 0x10) >> 0x1f);
      goto LAB_0019b798;
    }
  }
LAB_0019b594:
  if ((int)param_2[2] < 0) {
LAB_0019b5a8:
    if ((param_2[1] & 0x400) != 0) {
LAB_0019b5b4:
      if (0 < DebugLevel) {
        printk("\t\tat = %d\n",param_2[7] & 0x3ff);
LAB_0019bf1c:
        if (0 < DebugLevel) {
          printk("\t\thw amsdu cap = %d\n",(param_2[7] << 0x15) >> 0x1f);
          if ((int)param_2[2] < 0) {
            if (DebugLevel < 1) {
              return;
            }
            printk("\t\tspe_idx = 0x%x\n",(param_2[7] << 0x10) >> 0x1b);
          }
          goto LAB_0019b5c8;
        }
      }
    }
  }
  else {
LAB_0019b5a0:
    if (DebugLevel < 1) goto LAB_0019b5a8;
    printk("\t\ttxebf = %d\n",(param_2[6] << 1) >> 0x1f);
LAB_0019beb0:
    if ((0 < DebugLevel) && (printk("\t\ttxibf = %d\n",param_2[6] >> 0x1f), 0 < DebugLevel)) {
      printk("\tTMAC_TXD_7:\n");
LAB_0019bef4:
      if ((param_2[1] & 0x400) != 0) goto LAB_0019b5b4;
      if (DebugLevel < 1) goto LAB_0019b5bc;
      printk("\t\tsw_tx_time = %d\n",param_2[7] & 0x3ff);
      goto LAB_0019bf1c;
    }
  }
LAB_0019b5bc:
  if ((int)param_2[2] < 0) {
    return;
  }
LAB_0019b5c8:
  if ((((0 < DebugLevel) &&
       (printk("\t\tpse_fid = 0x%x\n",(param_2[7] << 4) >> 0x14), 0 < DebugLevel)) &&
      (printk("\t\tpp_sub_type=%d\n",(param_2[7] << 0xc) >> 0x1c), 0 < DebugLevel)) &&
     (((printk("\t\tpp_type=%d\n",(param_2[7] << 10) >> 0x1e), 0 < DebugLevel &&
       (printk("\t\tctxd cnt=0x%x\n",(param_2[7] << 6) >> 0x1d), 0 < DebugLevel)) &&
      ((printk("\t\tctxd = %d\n",(param_2[7] << 5) >> 0x1f), 0 < DebugLevel &&
       ((printk("\t\ti = %d\n",(param_2[7] << 3) >> 0x1f), 0 < DebugLevel &&
        (printk("\t\tUT = %d\n",(param_2[7] << 2) >> 0x1f), 0 < DebugLevel)))))))) {
    printk("\t\t txd len= %d\n",param_2[7] >> 0x1e);
    return;
  }
  return;
}

