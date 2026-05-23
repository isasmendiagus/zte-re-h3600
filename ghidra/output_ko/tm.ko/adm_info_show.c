// module: tm.ko
// function: adm_info_show @ 0x70228
// size: 2544 bytes
//

undefined4 adm_info_show(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  char *pcVar7;
  int iVar8;
  undefined4 uVar9;
  undefined1 uStack_59;
  uint local_58;
  uint local_54;
  uint local_50;
  uint local_4c;
  uint local_48 [9];
  
  pcVar7 = (char *)*param_2;
  iVar1 = capable(0xc);
  if (iVar1 == 0) {
    uVar9 = 0xffffffff;
  }
  else {
    iVar1 = strcmp(pcVar7,"helpAdm");
    if (iVar1 == 0) {
      printk("============================================================================\n");
      printk("Configuration Commands[HEX]\n");
      printk("============================================================================\n");
      printk(
            " echo [flowid][flowcnt][statMod][RdClr]  > flowStat            - List flow rate limit pkt statistics\n"
            );
      printk(
            " echo [port]                             > protPpsCfg          - List protocol pkt pps cfg by port\n"
            );
      printk(" port:0-uni0, 1-uni1, 2-uni2, 3-uni3, 4-uni4, 5-pon, 6-wifi1, 7-wifi2\n");
      printk(
            " echo [dir][type][cpuq][rate]            > protToqCfg          - List protocol pkt pps cfg by port\n"
            );
      printk(
            " echo [enable]                           > spqrtlmten          - set flow rate limit enable\n"
            );
      printk(
            " echo [dir][pps_unit][ena][pps_num]      > sprotocolpktppsrate - set protocol pkt pps rate\n"
            );
      printk(
            " echo [dir][pps_unit]                    > gpktlimitpps        - get protocol pkt pps rate\n"
            );
      printk(
            " echo [index]                            > gadmindramprint     - get adm indirect access ram print\n"
            );
      printk(" echo [index]                            > sadmppsmap          - set cpuid 2 pps");
      printk("============================================================================\n");
      printk("Display Commands: cat <file>\n");
      printk("============================================================================\n");
      printk(" cat helpAdm            - display adm command help\n");
      printk(" cat desOut             - dump printing adm output packet des\n");
      printk(" cat protPpsStat        - show protocol pps stats\n");
      printk(" cat flowLimitCfg       - show floe limit cfg\n");
      printk(" cat showadmcfg         - dump printing flow limit bucket cfg \n");
      printk(" cat showppsrate        - show pps en and pps rate \n");
      return 0;
    }
    iVar1 = strcmp(pcVar7,"desOut");
    if (iVar1 == 0) {
      puVar6 = &local_4c;
      local_48[0] = 0;
      local_48[1] = 0;
      local_48[2] = 0;
      local_48[3] = 0;
      local_48[4] = 0;
      local_48[5] = 0;
      local_48[6] = 0;
      local_48[7] = 0;
      do {
        uVar2 = fpga_read_reg(0xe5090);
        puVar6 = puVar6 + 1;
        *puVar6 = uVar2;
      } while (puVar6 != local_48 + 7);
      printk("---------------------------------------------\n");
      printk("adm to pp_ctrl des info:\n");
      printk("---------------------------------------------\n");
      uVar2 = local_48[0];
      printk("Pkt_len          (0-13)     :%d\n",local_48[0] & 0x3fff);
      printk("hpmau1           (14-26)    :0x%x\n",(uVar2 << 5) >> 0x13);
      uVar3 = local_48[1];
      printk("hpmau2           (27-39)    :0x%x\n",uVar2 >> 0x1b | (local_48[1] & 0xff) << 5);
      printk("hpmau3           (40-52)    :0x%x\n",(uVar3 << 10) >> 0x13);
      printk("head_len         (53-60)    :0x%x\n",(uVar3 << 3) >> 0x18);
      uVar2 = local_48[2];
      printk("inport           (61-64)    :0x%x\n",uVar3 >> 0x1d | (local_48[2] & 1) << 3);
      printk("ssid             (65-67)    :0x%x\n",(uVar2 << 0x1c) >> 0x1d);
      printk("gemport_id       (68-83)    :0x%x\n",(uVar2 << 0x14) >> 0x18);
      printk("direction        (84)       :0x%x\n",(uVar2 << 0xb) >> 0x1f);
      printk("action           (85-86)    :0x%x\n",(uVar2 << 9) >> 0x1e);
      uVar3 = (uVar2 << 1) >> 0x19;
      printk("Action reason    (87-93)    :0x%2x:%s\n",uVar3,(&trapPktType)[uVar3]);
      uVar3 = local_48[3];
      printk("OAM              (94-96)    :0x%x\n",uVar2 >> 0x1e | (local_48[3] & 1) << 2);
      printk("Cast_type        (97-98)    :0x%x\n",(uVar3 << 0x1d) >> 0x1e);
      printk("Tag_type         (99-101)   :0x%x\n",(uVar3 << 0x1a) >> 0x1d);
      printk("l3_en            (102)      :0x%x\n",(uVar3 << 0x19) >> 0x1f);
      printk("port_map         (103-104)  :0x%x\n",(uVar3 << 0x17) >> 0x1e);
      printk("spec_flow        (105-106)  :0x%x\n",(uVar3 << 0x15) >> 0x1e);
      printk("pps(flow)_limit  (107)      :0x%x\n",(uVar3 << 0x14) >> 0x1f);
      printk("move_flag        (108)      :0x%x\n",(uVar3 << 0x13) >> 0x1f);
      printk("drop_reason      (109-111)  :0x%x\n",(uVar3 << 0x10) >> 0x1d);
      printk("color            (112)      :0x%x\n",(uVar3 << 0xf) >> 0x1f);
      printk("trunk_index      (113-116)  :0x%x\n",(uVar3 << 0xb) >> 0x1c);
      printk("ip_flag          (117)      :0x%x\n",(uVar3 << 10) >> 0x1f);
      printk("ipv4_flag        (118)      :0x%x\n",(uVar3 << 9) >> 0x1f);
      printk("ipv6_flag        (119)      :0x%x\n",(uVar3 << 8) >> 0x1f);
      printk("tcp_flag         (120)      :0x%x\n",(uVar3 << 7) >> 0x1f);
      printk("udp_flag         (121)      :0x%x\n",(uVar3 << 6) >> 0x1f);
      printk("PPPoE            (122)      :0x%x\n",(uVar3 << 5) >> 0x1f);
      printk("v4inv6           (123)      :0x%x\n",(uVar3 << 4) >> 0x1f);
      printk("v6inv4           (124)      :0x%x\n",(uVar3 << 3) >> 0x1f);
      printk("udp_lite_flag    (125)      :0x%x\n",(uVar3 << 2) >> 0x1f);
      printk("l2_type          (126-127)  :0x%x\n",uVar3 >> 0x1e);
      uVar2 = local_48[4];
      printk("l2_offset        (128-135)  :0x%x\n",local_48[4] & 0xff);
      printk("l3_offset_v4     (136-143)  :0x%x\n",(uVar2 << 0x10) >> 0x18);
      printk("l3_offset_v6     (144-151)  :0x%x\n",(uVar2 << 8) >> 0x18);
      printk("l3_offset_v6_last(152-159)  :0x%x\n",uVar2 >> 0x18);
      uVar2 = local_48[5];
      printk("l4_offset        (160-167)  :0x%x\n",local_48[5] & 0xff);
      printk("l5_offset        (168-175)  :0x%x\n",(uVar2 << 0x10) >> 0x18);
      printk("outer_pri        (176-178)  :0x%x\n",(uVar2 << 0xd) >> 0x1d);
      printk("outer_vid        (179-190)  :0x%x\n",(uVar2 << 1) >> 0x14);
      uVar3 = local_48[6];
      printk("ram_id           (191-197)  :0x%x\n",uVar2 >> 0x1f | (local_48[6] & 0x3f) << 1);
      printk("cpu Qnum         (198-200)  :0x%x\n",(uVar3 << 0x17) >> 0x1d);
      printk("Qos_id           (201-209)  :0x%x\n",(uVar3 << 0xe) >> 0x17);
      printk("Qnum             (210-212)  :0x%x\n",(uVar3 << 0xb) >> 0x1d);
      printk("valn_change      (213)      :0x%x\n",(uVar3 << 10) >> 0x1f);
      printk("Da_known         (214)      :0x%x\n",(uVar3 << 9) >> 0x1f);
      printk("outport          (215-218)  :0x%x\n",(uVar3 << 5) >> 0x1c);
      printk("mod_en           (219)      :0x%x\n",(uVar3 << 4) >> 0x1f);
      uVar2 = local_48[7];
      printk("flow_id          (220-234)  :0x%x\n",uVar3 >> 0x1c | (local_48[7] & 0x7ff) << 4);
      printk("pkt_len_changed  (235-248)  :0x%x\n",(uVar2 << 0xb) >> 0x16);
      printk("e8_en            (249)      :0x%x\n",(uVar2 << 6) >> 0x1f);
      return 0;
    }
    iVar1 = strcmp(pcVar7,"protPpsStat");
    if (iVar1 == 0) {
      printk("|--------------------------------------------|\n");
      printk("| adm protocol packet pps ratelimit info |\n");
      printk("|--------------------------------------------|\n");
      printk("| %-3s| %-7s| %-13s| %-13s  |\n",&_LC81,"bktNum","PassPktCnt","DropPktCnt");
      printk("|--------------------------------------------|\n");
      iVar1 = 0;
      do {
        adm_get_up_pass_protocal_packtcnt(iVar1,&local_50);
        adm_get_up_drop_protocal_packtcnt(iVar1,local_48);
        iVar8 = iVar1 + 1;
        printk("| %-3s| %-7d| %-13d| %-13d  |\n",&_LC86,iVar1,local_50,local_48[0]);
        iVar1 = iVar8;
      } while (iVar8 != 8);
      iVar1 = 0;
      do {
        adm_get_dn_pass_protocal_packtcnt(iVar1,&local_50);
        adm_get_dn_drop_protocal_packtcnt(iVar1,local_48);
        iVar8 = iVar1 + 1;
        printk("| %-3s| %-7d| %-13d| %-13d  |\n",&_LC87,iVar1,local_50,local_48[0]);
        iVar1 = iVar8;
      } while (iVar8 != 8);
      printk("|--------------------------------------------|\n");
      return 0;
    }
    iVar1 = strcmp(pcVar7,"flowLimitCfg");
    if (iVar1 == 0) {
      printk(
            "|-------------------------- adm flow limit bucket cfg info ----------------------------|\n"
            );
      printk("| %-6s| %-7s| %-8s| %-8s| %-8s| %-8s| %-8s| %-8s| %-8s|\n","bktId","bktEna","bktCoup",
             &_LC94,&_LC95,&_LC96,&_LC97,"avgRate","maxRate");
      printk(
            "|--------------------------------------------------------------------------------------|\n"
            );
      iVar1 = 0;
      do {
        adm_get_bucket_c(iVar1,local_48);
        adm_get_bucket_e(iVar1,&local_50);
        tm_flow_rate_limit_get(iVar1,&uStack_59,&local_58,&local_54);
        iVar8 = iVar1 + 1;
        printk(" %-6d| %-7d| %-8d| %-8d| %-8d| %-8d| %-8d| %-8d| %-8d|\n",iVar1,local_48[3],
               local_48[2],local_48[1],local_4c,local_48[0],local_50,local_58,local_58 + local_54);
        iVar1 = iVar8;
      } while (iVar8 != 0x20);
      uVar9 = 1;
      printk(
            "|--------------------------------------------------------------------------------------|\n"
            );
    }
    else {
      local_58 = strcmp(pcVar7,"showadmcfg");
      if (local_58 == 0) {
        local_54 = local_58;
        local_50 = local_58;
        local_48[0] = local_58;
        uVar2 = adm_get_turnon_enable(&local_58);
        uVar3 = adm_get_credit_cmp_mode(&local_54);
        uVar4 = adm_get_bucket_fill_time(&local_50);
        uVar5 = adm_get_spend_byte_cfg(local_48);
        pcVar7 = "Enable";
        uVar5 = uVar3 | uVar2 | uVar4 | uVar5;
        if (local_58 == 0) {
          pcVar7 = "Close";
        }
        printk("ADM Rate Limit Enable:%s\n",pcVar7);
        pcVar7 = "Loose";
        if (local_54 == 0) {
          pcVar7 = "Strict";
        }
        printk("ADM Mode:%s\n",pcVar7);
        printk("ADM Bucket Fill Time:0x%x\n",local_50);
        printk("ADM Spent Byte:0x%x\n",local_48[0]);
        uVar9 = 0;
        if (uVar5 != 0) {
          uVar9 = 0xffffffff;
          printk("[pp_adm_debug]admDebugShowCfg failed!,error code %d\n",uVar5);
        }
      }
      else {
        local_58 = strcmp(pcVar7,"showppsrate");
        if (local_58 == 0) {
          local_54 = local_58;
          local_50 = local_58;
          local_48[0] = local_58;
          printk("dir\tQuenum\tQueRate\tQuePassCnt\tQuePassProtoCnt\ttQueDrpProtoCnt\n");
          iVar1 = 0;
          do {
            iVar8 = iVar1 + -8;
            if (iVar1 < 8) {
              adm_get_policing_enable(0,iVar1,&local_58);
              adm_get_pass_pktcnt_persec(0,iVar1,&local_54);
              adm_get_up_pass_protocal_packtcnt(iVar1,&local_50);
              adm_get_up_drop_protocal_packtcnt(iVar1,local_48);
            }
            else {
              adm_get_policing_enable(1,iVar8,&local_58);
              adm_get_pass_pktcnt_persec(1,iVar8,&local_54);
              adm_get_dn_pass_protocal_packtcnt(iVar8,&local_50);
              adm_get_dn_drop_protocal_packtcnt(iVar8,local_48);
            }
            iVar8 = iVar1 + 1;
            printk("%d\t%d\t%d\t%d\t%d\t%d\n",7 < iVar1,iVar1,local_58,local_54,local_50,local_48[0]
                  );
            uVar9 = 0;
            iVar1 = iVar8;
          } while (iVar8 != 0x10);
        }
        else {
          uVar9 = 0;
          printk("%s: illegal operation <%s>\n","adm_info_show",*param_2);
        }
      }
    }
  }
  return uVar9;
}

