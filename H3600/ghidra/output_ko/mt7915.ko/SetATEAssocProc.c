// module: mt7915.ko
// function: SetATEAssocProc @ 0x2662d0
// size: 1680 bytes
//

undefined4 SetATEAssocProc(int param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  char *pcVar7;
  undefined1 auStack_89 [3];
  undefined1 local_86;
  undefined1 local_85;
  undefined1 local_84;
  uint local_80;
  uint local_7c;
  uint local_78;
  uint local_74;
  uint local_70;
  uint local_6c;
  uint local_68;
  uint local_64;
  char acStack_60 [68];
  
  __memzero(param_1 + 0xa78654,0x30);
  if (param_2 != (char *)0x0) {
    cVar1 = *param_2;
    while (cVar1 != '\0') {
      pcVar2 = (char *)rtstrchr(param_2,0x2d);
      pcVar7 = pcVar2;
      if (pcVar2 != (char *)0x0) {
        pcVar7 = pcVar2 + 1;
        *pcVar2 = '\0';
      }
      if (2 < DebugLevel) {
        printk("%s: param_str=%s\n","SetATEAssocProc",param_2);
      }
      if ((((*param_2 != '\0') &&
           (puVar3 = (undefined1 *)rtstrchr(param_2,0x3a), puVar3 != (undefined1 *)0x0)) &&
          (*puVar3 = 0, puVar3 != (undefined1 *)0xffffffff && *param_2 != '\0')) &&
         ((puVar3[1] != '\0' && (iVar4 = ATEManualParsingParam(param_1,param_2), iVar4 == 0)))) {
        if ((((((2 < DebugLevel) &&
               ((printk("Parameter Usage:\n"), 2 < DebugLevel &&
                (printk(
                       "\tiwpriv ra0 set assoc=[mac:hh:hh:hh:hh:hh:hh]-[wtbl:dd]-[ownmac:dd]-[type:xx]-[mode:mmm]-[bw:dd]-[nss:ss]-[maxrate:kkk_dd]\n"
                       ), 2 < DebugLevel)))) &&
              (printk("\t\tmac: peer\'s mac address in hex format\n"), 2 < DebugLevel)) &&
             ((((((printk("\t\t\tExample=> mac:00:0c:43:12:34:56\n"), 2 < DebugLevel &&
                  (printk("\t\twtbl: the WTBL entry index peer will occupied, in range 1~127\n"),
                  2 < DebugLevel)) && (printk("\t\t\tExample=> wtbl:1\n"), 2 < DebugLevel)) &&
                ((printk(
                        "\t\townmac: the OwnMAC index we\'ll used to send frame to this peer, in range 0~4 or 16~31\n"
                        ), 2 < DebugLevel && (printk("\t\t\tExample=> ownmac:0\n"), 2 < DebugLevel))
                )) && ((printk(
                              "\t\ttype: peer\'s operation type, is a ap or sta, allow input: \"ap\" or \"sta\"\n"
                              ), 2 < DebugLevel &&
                       ((printk("\t\t\tExample=> type:ap\n"), 2 < DebugLevel &&
                        (printk(
                               "\t\tmode: peer\'s phy operation mode, allow input: a/b/g/gn/an/ac\n"
                               ), 2 < DebugLevel)))))) &&
              (printk("\t\t\tExample=> mode:aanac\tto indicate peer can support A/AN/AC mode\n"),
              2 < DebugLevel)))) &&
            ((((printk("\t\tbw: Peer\'s bandwidth capability, in range to 20/40/80/160\n"),
               2 < DebugLevel &&
               (printk("\t\t\tExample=> bw:40\tindicate peer can support BW_40\n"), 2 < DebugLevel))
              && (printk(
                        "\t\tnss: Peer\'s capability for Spatial stream which can tx/rx, in range of 1~4 with restriction of Software/Hardware cap.\n"
                        ), 2 < DebugLevel)) &&
             (((printk("\t\t\tExample=> nss:2\tindicate peer can support 2ss for both tx/rx\n"),
               2 < DebugLevel &&
               (printk(
                      "\t\tmaxrate: Peer\'s data rate capability for tx/rx, separate as two parts and separate by \'_\' character\n"
                      ), 2 < DebugLevel)) &&
              ((printk(
                      "\t\t\t\t kkk: phy modulation mode, allow input:\'cck\', \'ofdm\', \'htmix\', \'htgf\', \'vht\'\n"
                      ), 2 < DebugLevel &&
               ((printk("\t\t\t\t dd:phy mcs rate, for CCK:0~3, OFDM:0~7, HT:0~32, VHT:0~9\n"),
                2 < DebugLevel &&
                (printk(
                       "\t\t\tExample=> maxrate:cck_1\tindicate we only can transmit CCK and MCS 1(2Mbps) or lower MCS to peer\n"
                       ), 2 < DebugLevel)))))))))) &&
           (printk(
                  "\t\t\tExample=> maxrate:ofdm_3\tindicate we only can transmit OFDM and MCS 3(24Mbps) to peer\n"
                  ), 2 < DebugLevel)) {
          printk(
                "\t\t\tExample=> maxrate:htmix_3\tindicate we only can transmit OFDM and MCS 3(24Mbps) to peer\n"
                );
        }
        return 0;
      }
      if (pcVar7 == (char *)0x0) break;
      param_2 = pcVar7;
      cVar1 = *pcVar7;
    }
  }
  if ((((((2 < DebugLevel) &&
         (printk("%s:User manual configured peer STA info:\n","SetATEAssocProc"), 2 < DebugLevel))
        && (printk("\tMAC=>0x%02x:%02x:%02x:%02x:%02x:%02x\n",*(undefined1 *)(param_1 + 0xa78654),
                   *(undefined1 *)(param_1 + 0xa78655),*(undefined1 *)(param_1 + 0xa78656),
                   *(undefined1 *)(param_1 + 0xa78657),*(undefined1 *)(param_1 + 0xa78658),
                   *(undefined1 *)(param_1 + 0xa78659)), 2 < DebugLevel)) &&
       (((printk("\tBAND=>%d\n",*(undefined1 *)(param_1 + 0xa7865a)), 2 < DebugLevel &&
         (printk("\tOwnMacIdx=>%d\n",*(undefined1 *)(param_1 + 0xa7865c)), 2 < DebugLevel)) &&
        ((printk("\tWTBL_Idx=>%d\n",*(undefined1 *)(param_1 + 0xa7865d)), 2 < DebugLevel &&
         ((printk("\tOperationType=>%d\n",*(undefined1 *)(param_1 + 0xa7865b)), 2 < DebugLevel &&
          (printk("\tPhyMode=>%d\n",*(undefined1 *)(param_1 + 0xa7865e)), 2 < DebugLevel)))))))) &&
      ((printk("\tBandWidth=>%d\n",*(undefined1 *)(param_1 + 0xa7865f)), 2 < DebugLevel &&
       ((((printk("\tNSS=>%d\n",*(undefined1 *)(param_1 + 0xa78660)), 2 < DebugLevel &&
          (printk("\tPfmuId=>%d\n",*(undefined2 *)(param_1 + 0xa78662)), 2 < DebugLevel)) &&
         (printk("\tAid=>%d\n",*(undefined2 *)(param_1 + 0xa78666)), 2 < DebugLevel)) &&
        ((printk("\tSpe_idx=>%d\n",*(undefined1 *)(param_1 + 0xa78664)), 2 < DebugLevel &&
         (printk("\tMaxRate_Mode=>%d\n",*(undefined1 *)(param_1 + 0xa7866a)), 2 < DebugLevel))))))))
     && (printk("\tMaxRate_MCS=>%d\n",*(undefined4 *)(param_1 + 0xa7866c)), 2 < DebugLevel)) {
    printk("Now apply it to hardware!\n");
  }
  SetATEApplyStaToMacTblEntry(param_1);
  __memzero(acStack_60,0x40);
  sprintf(acStack_60,"%d-%d-%d-%d-%d-%d-%d-%d-%d-%d",(uint)*(byte *)(param_1 + 0xa7865d),
          (uint)*(byte *)(param_1 + 0xa7866a),(uint)*(byte *)(param_1 + 0xa7865f),
          *(undefined4 *)(param_1 + 0xa7866c),(uint)*(byte *)(param_1 + 0xa78660),0,0,0,0,0);
  if (2 < DebugLevel) {
    printk("\tSet fixed RateInfo string as %s\n",acStack_60);
  }
  uVar5 = asic_get_nsts_by_mcs
                    (param_1,*(undefined1 *)(param_1 + 0xa7866a),*(undefined1 *)(param_1 + 0xa7866c)
                     ,0,*(undefined1 *)(param_1 + 0xa78660));
  local_80 = asic_tx_rate_to_tmi_rate
                       (param_1,*(undefined1 *)(param_1 + 0xa7866a),
                        *(undefined1 *)(param_1 + 0xa7866c),uVar5,0,0);
  local_80 = local_80 & 0xfff;
  local_7c = local_80;
  local_78 = local_80;
  local_74 = local_80;
  local_70 = local_80;
  local_6c = local_80;
  local_68 = local_80;
  local_64 = local_80;
  os_zero_mem(auStack_89,9);
  local_85 = *(undefined1 *)(param_1 + 0xa7865f);
  local_86 = 0;
  local_84 = 0;
  AsicTxCapAndRateTableUpdate(param_1,*(undefined1 *)(param_1 + 0xa7865d),auStack_89,&local_80,0);
  SetATEApplyStaToAsic(param_1);
  wdev_search_by_omac_idx(param_1,*(undefined1 *)(param_1 + 0xa7865c));
  uVar5 = HcGetBandByWdev();
  uVar6 = wdev_search_by_omac_idx(param_1,*(undefined1 *)(param_1 + 0xa7865c));
  mt_ate_store_tx_info
            (param_1,uVar5,uVar6,param_1 + 0xa78654,
             (uint)*(byte *)(param_1 + 0xa7865d) * 0x14c0 + param_1 + 0xa1d20,0);
  return 1;
}

