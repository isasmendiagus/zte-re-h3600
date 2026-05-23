// module: tm.ko
// function: cla_info_show @ 0x74978
// size: 5400 bytes
//

int cla_info_show(undefined4 param_1,undefined4 *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  undefined2 uVar13;
  int iVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  uint uVar22;
  uint uVar23;
  char *pcVar24;
  uint uVar25;
  char *pcVar26;
  uint uVar27;
  uint uVar28;
  uint *puVar29;
  int iVar30;
  char *pcVar31;
  uint *puVar32;
  uint uVar33;
  undefined1 *puVar34;
  int *piVar35;
  char *pcVar36;
  uint uVar37;
  uint uVar38;
  uint uVar39;
  uint uVar40;
  uint uVar41;
  uint uVar42;
  uint uVar43;
  uint uVar44;
  uint uVar45;
  uint uVar46;
  uint local_8c;
  uint local_88;
  uint local_84 [2];
  undefined4 local_7c;
  undefined4 local_78;
  uint local_74;
  undefined4 local_70;
  uint local_6c;
  uint local_68;
  uint local_64;
  uint local_60 [2];
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  uint local_48;
  undefined4 local_44;
  undefined4 local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  int local_2c;
  
  pcVar26 = (char *)*param_2;
  iVar14 = capable(0xc);
  if (iVar14 == 0) {
    iVar14 = -1;
  }
  else {
    iVar14 = strcmp(pcVar26,"helpCla");
    if (iVar14 == 0) {
      printk("============================================================================\n");
      printk("Configuration Commands[HEX]\n");
      printk("============================================================================\n");
      printk(
            " echo [direction]                     > flowInfoList      - List flow info by direction:up[0],dwn[1]\n"
            );
      printk(
            " echo [dir][gemid][proto][smac][gwmac][isapp][se_id][l2_len][tcontid]  > addfastrule  - add rule table by manual\n"
            );
      printk(" dir:0 up:1 down;proto:17 v4;isapp:0 not ppp:1 ppp;l2_len:14\n");
      printk(
            " echo [dir][sport][dport][proto][sip][dip] > delfastrule  - del rule table:dir[up:0 down:1]\n"
            );
      printk(
            " echo [hash_addr]                     > ghashtable        - read rule table by hash address\n"
            );
      printk(
            " echo [index_id]                      > gextraindextable  - read index table by index id\n"
            );
      printk(
            " echo [rule_id]                       > gextraruletable   - read rule table by rule id\n"
            );
      printk(
            " echo parameters                      > calculatehashaddr - calculate hash addr,see the function for parameters \n"
            );
      printk(" echo [up][dn]                        > setmaxl3entry    - set max l3 entry\n");
      printk(
            " echo [hashAddr]                      > gagingstatus   - get entry aging status,hashAddr is the address of entry\n"
            );
      printk(" echo [enable][upnum][dnnum]          > setmaxfastentry    - set max fast entry\n");
      printk("============================================================================\n");
      printk("Display Commands: cat <file>\n");
      printk("============================================================================\n");
      printk(
            " cat desOut                                        - get descriptor handled by cla module\n"
            );
      printk(
            " cat desIn                                         - get descriptor enter into cla module\n"
            );
      printk(" cat statics                                       - dump printing cla statistics\n");
      printk(" cat reason                                        - dump printing options\n");
      printk(" cat showcommrule                                  - show common rule info\n");
      printk(" cat showfastrule                                  - show fast rule entry \n");
      printk(" cat gclacfg                                       - get cla cfg\n");
      printk(" cat gparsehashkey                                 - get parsed hash key\n");
      printk(" cat showfastinfoall                               - get all fast entry info\n");
      printk(" cat showaclinfoall                                - get all acl info\n");
      printk(" cat gfastentrynum                               - get fast entry num\n");
      return 0;
    }
    iVar14 = strcmp(pcVar26,"desOut");
    if (iVar14 == 0) {
      puVar29 = &local_88;
      local_84[0] = 0;
      local_84[1] = 0;
      local_7c = 0;
      local_78 = 0;
      local_74 = 0;
      local_70 = 0;
      local_6c = 0;
      local_68 = 0;
      local_64 = 0;
      iVar14 = 0xe30e5;
      do {
        uVar15 = fpga_read_reg(iVar14);
        puVar29 = puVar29 + 1;
        *puVar29 = uVar15;
        iVar14 = iVar14 + 1;
      } while (puVar29 != &local_64);
      __memzero(local_60,0x24);
      local_60[0] = local_84[0];
      local_60[1] = local_84[1];
      local_58 = local_7c;
      local_54 = local_78;
      local_50 = local_74;
      local_4c = local_70;
      local_48 = local_6c;
      local_44 = local_68;
      local_40 = local_64;
      printk("pkt_len                :%d\n",local_84[0] & 0x3fff);
      printk("1th_pmau               :%d\n",(local_60[0] << 5) >> 0x13);
      printk("2th_pmau               :%d\n",(local_60[1] & 0xff) << 5 | local_60[0] >> 0x1b);
      printk("3th_pmau               :%d\n",(local_60[1] << 0xb) >> 0x13);
      printk("head_len               :%d\n",((local_60[1] >> 0x10) << 0x13) >> 0x18);
      printk("inport                 :%d\n",(local_58 & 1) << 3 | local_60[1] >> 0x1d);
      printk("ssid_in                :%d\n",(local_58 << 0x1c) >> 0x1d);
      printk("gemport_id             :%d\n",(ushort)local_58 >> 4);
      printk("cpu_sa_learn           :%d\n",local_58._2_1_ & 1);
      printk("multi_release          :%d\n",((local_58 >> 0x10) << 0x1e) >> 0x1f);
      printk("rsv0                   :%d\n",((local_58 >> 0x10) << 0x1d) >> 0x1f);
      printk("direction              :%d\n",((local_58 >> 0x10) << 0x1b) >> 0x1f);
      printk("action                 :%d\n",((local_58 >> 0x10) << 0x19) >> 0x1e);
      uVar15 = ((local_58 >> 0x10) << 0x12) >> 0x19;
      printk("action_rsn             :%d(%s)\n",uVar15,(&trapPktType)[uVar15]);
      printk("oam                    :%d\n",(local_54 & 1) << 2 | local_58 >> 0x1e);
      printk("cast_type              :%d\n",(local_54 << 0x1d) >> 0x1e);
      printk("tag_type               :%d\n",(local_54 << 0x1a) >> 0x1d);
      printk("l3_en                  :%d\n",(local_54 << 0x19) >> 0x1f);
      printk("port_map               :%d\n",(local_54 << 0x17) >> 0x1e);
      printk("spec_flow              :%d\n",((local_54 >> 8) << 0x1d) >> 0x1e);
      printk("pps_flag               :%d\n",((local_54 >> 8) << 0x1c) >> 0x1f);
      printk("move_flag              :%d\n",((local_54 >> 8) << 0x1b) >> 0x1f);
      uVar15 = local_54 >> 0xd & 7;
      printk("drop_reason            :%d(%s)\n",uVar15,*(undefined4 *)(drop_reason + uVar15 * 4));
      printk("color                  :%d\n",local_54._2_1_ & 1);
      printk("ssid_out               :%d\n",((local_54 >> 0x10) << 0x1c) >> 0x1d);
      printk("rsv1                   :%d\n",((local_54 >> 0x10) << 0x1b) >> 0x1f);
      printk("ip_flag                :%d\n",((local_54 >> 0x10) << 0x1a) >> 0x1f);
      printk("ipv4_flag              :%d\n",((local_54 >> 0x10) << 0x19) >> 0x1f);
      printk("ipv6_flag              :%d\n",local_54._2_1_ >> 7);
      printk("tcp_flag               :%d\n",local_54._3_1_ & 1);
      printk("udp_flag               :%d\n",((local_54 >> 0x18) << 0x1e) >> 0x1f);
      printk("pppoe_flag             :%d\n",((local_54 >> 0x18) << 0x1d) >> 0x1f);
      printk("v4inv6_flag            :%d\n",((local_54 >> 0x18) << 0x1c) >> 0x1f);
      printk("v6inv4_flag            :%d\n",((local_54 >> 0x18) << 0x1b) >> 0x1f);
      printk("udp_lite_flag          :%d\n",((local_54 >> 0x18) << 0x1a) >> 0x1f);
      printk("l2_type                :%d\n",local_54._3_1_ >> 6);
      printk("l2_offset              :%d\n",local_50 & 0xff);
      printk("l3_offset_v4           :%d\n",local_50._1_1_);
      printk("l3_offset_v6           :%d\n",local_50._2_1_);
      printk("l3_offset_v6_last      :%d\n",local_50._3_1_);
      printk("l4_offset              :%d\n",local_4c & 0xff);
      printk("l5_offset              :%d\n",local_4c._1_1_);
      printk("outer_pri              :%d\n",local_4c._2_1_ & 7);
      printk("outer_vid              :%d\n",((local_4c >> 0x10) << 0x11) >> 0x14);
      printk("ram_id                 :%d\n",(local_48 & 0x3f) << 1 | local_4c >> 0x1f);
      printk("Cpu_qid/E8_qid         :%d\n",(local_48 << 0x17) >> 0x1d);
      printk("Qos_id                 :%d\n",(local_48 << 0xe) >> 0x17);
      printk("Qnum                   :%d\n",((local_48 >> 0x10) << 0x1b) >> 0x1d);
      printk("Vlan_change            :%d\n",((local_48 >> 0x10) << 0x1a) >> 0x1f);
      printk("Da_known               :%d\n",((local_48 >> 0x10) << 0x19) >> 0x1f);
      printk("Outport                :%d\n",((local_48 >> 0x10) << 0x15) >> 0x1c);
      printk("Bucket_info            :%d\n",(local_44 & 1) << 5 | local_48 >> 0x1b);
      printk("Mod_en                 :%d\n",(local_44 << 0x1e) >> 0x1f);
      printk("Cmd_flow_id            :%d\n",(local_44 << 0xf) >> 0x11);
      printk("Pkt_len_changed        :%d\n",((local_44 >> 0x10) << 0x11) >> 0x12);
      printk("E8_en                  :%d\n",local_44._3_1_ >> 7);
      printk("Wan_id                 :%d\n",(byte)local_40 >> 3);
      printk("Tcont_llid             :%d\n",
             local_40 >> 8 & 0x1f | (((local_58 >> 0x10) << 0x1c) >> 0x1f) << 5);
      printk("ssid_flag              :%d\n",((local_40 >> 8) << 0x1a) >> 0x1f);
      printk("rsv3                   :%d\n",((local_40 >> 8) << 0x19) >> 0x1f);
      printk("Copy_flag              :%d\n",local_40._1_1_ >> 7);
      printk("Sta_en                 :%d\n",local_40._2_1_ & 1);
      printk("flow_stat_info         :%d\n",
             local_40 & 7 | (((local_40 >> 0x10) << 0x17) >> 0x18) << 3);
      return 1;
    }
    iVar14 = strcmp(pcVar26,"desIn");
    if (iVar14 == 0) {
      puVar29 = &local_64;
      local_60[0] = 0;
      local_60[1] = 0;
      local_58 = 0;
      local_54 = 0;
      local_50 = 0;
      local_4c = 0;
      local_48 = 0;
      iVar14 = 0xe30f8;
      do {
        uVar15 = fpga_read_reg(iVar14);
        puVar29 = puVar29 + 1;
        *puVar29 = uVar15;
        iVar14 = iVar14 + 1;
      } while (puVar29 != &local_48);
      __memzero(local_84,0x19);
      iVar14 = 1;
      local_84[0] = local_60[0];
      local_84[1] = local_60[1];
      local_7c = local_58;
      local_78 = local_54;
      local_74 = local_50;
      local_70 = local_4c;
      local_6c = CONCAT31(local_6c._1_3_,(char)local_48);
      printk("pkt_len            :%d\n",local_60[0] & 0x3fff);
      printk("1th_pmau           :%d\n",(local_84[0] << 5) >> 0x13);
      printk("2th_pmau           :%d\n",(local_84[1] & 0xff) << 5 | local_84[0] >> 0x1b);
      printk("3th_pmau           :%d\n",(local_84[1] << 0xb) >> 0x13);
      printk("head_len           :%d\n",((local_84[1] >> 0x10) << 0x13) >> 0x18);
      printk("inport             :%d\n",(local_7c & 1) << 3 | local_84[1] >> 0x1d);
      printk("ssid_in            :%d\n",(local_7c << 0x1c) >> 0x1d);
      printk("gemport_id         :%d\n",(ushort)local_7c >> 4);
      printk("cpu_sa_learn       :%d\n",local_7c._2_1_ & 1);
      printk("multi_release      :%d\n",((local_7c >> 0x10) << 0x1e) >> 0x1f);
      printk("rsv                :%d\n",((local_7c >> 0x10) << 0x1d) >> 0x1f);
      printk("tcont_bit_5        :%d\n",((local_7c >> 0x10) << 0x1c) >> 0x1f);
      printk("direction          :%d\n",((local_7c >> 0x10) << 0x1b) >> 0x1f);
      printk("action             :%d\n",((local_7c >> 0x10) << 0x19) >> 0x1e);
      uVar15 = ((local_7c >> 0x10) << 0x12) >> 0x19;
      printk("action_rsn         :%d(%s)\n",uVar15,(&trapPktType)[uVar15]);
      printk("oam                :%d\n",(local_78 & 1) << 2 | local_7c >> 0x1e);
      printk("cast_type          :%d\n",(local_78 << 0x1d) >> 0x1e);
      printk("tag_type           :%d\n",(local_78 << 0x1a) >> 0x1d);
      printk("l3_en              :%d\n",(local_78 << 0x19) >> 0x1f);
      printk("port_map           :%d\n",(local_78 << 0x17) >> 0x1e);
      printk("spec_flow          :%d\n",((local_78 >> 8) << 0x1d) >> 0x1e);
      printk("pps_flag           :%d\n",((local_78 >> 8) << 0x1c) >> 0x1f);
      printk("move_flag          :%d\n",((local_78 >> 8) << 0x1b) >> 0x1f);
      uVar15 = local_78 >> 0xd & 7;
      printk("drop_reason        :%d(%s)\n",uVar15,*(undefined4 *)(drop_reason + uVar15 * 4));
      printk("color              :%d\n",local_78._2_1_ & 1);
      printk("ssid_out           :%d\n",((local_78 >> 0x10) << 0x1c) >> 0x1d);
      printk("rsv                :%d\n",((local_78 >> 0x10) << 0x1b) >> 0x1f);
      printk("ip_flag            :%d\n",((local_78 >> 0x10) << 0x1a) >> 0x1f);
      printk("ipv4_flag          :%d\n",((local_78 >> 0x10) << 0x19) >> 0x1f);
      printk("ipv6_flag          :%d\n",local_78._2_1_ >> 7);
      printk("tcp_flag           :%d\n",local_78._3_1_ & 1);
      printk("udp_flag           :%d\n",((local_78 >> 0x18) << 0x1e) >> 0x1f);
      printk("pppoe_flag         :%d\n",((local_78 >> 0x18) << 0x1d) >> 0x1f);
      printk("v4inv6_flag        :%d\n",((local_78 >> 0x18) << 0x1c) >> 0x1f);
      printk("v6inv4_flag        :%d\n",((local_78 >> 0x18) << 0x1b) >> 0x1f);
      printk("udp_lite_flag      :%d\n",((local_78 >> 0x18) << 0x1a) >> 0x1f);
      printk("l2_type            :%d\n",local_78._3_1_ >> 6);
      printk("extend_flag        :%d\n",local_74 & 1);
      printk("l2_offset          :%d\n",(local_74 << 0x17) >> 0x18);
      printk("l3_offset_v4       :%d\n",(local_74 << 0xf) >> 0x18);
      printk("l3_offset_v6       :%d\n",((local_74 >> 0x10) << 0x17) >> 0x18);
      printk("l3_offset_v6_last  :%d\n",(local_70 & 1) << 7 | local_74 >> 0x19);
      printk("l4_offset          :%d\n",(local_70 << 0x17) >> 0x18);
      printk("l5_offset          :%d\n",(local_70 << 0xf) >> 0x18);
      printk("out_pri            :%d\n",((local_70 >> 0x10) << 0x1c) >> 0x1d);
      printk("outer_vid          :%d\n",local_70._2_2_ >> 4);
      printk("ram_id             :%d\n",local_6c & 0x7f);
    }
    else {
      iVar14 = strcmp(pcVar26,"statics");
      if (iVar14 == 0) {
        iVar14 = 1;
        uVar15 = fpga_read_reg(0xe30ee);
        printk("acl failed counter    :%d\n",uVar15 & 0xffff);
        printk("acl required counter  :%d\n",uVar15 >> 0x10);
        uVar15 = fpga_read_reg(0xe30f0);
        printk("cla tx fwd no e8 cnt  :%d\n",uVar15 & 0xffff);
        printk("cla tx fwd e8 cnt     :%d\n",uVar15 >> 0x10);
        uVar13 = fpga_read_reg(0xe30f1);
        printk("cla tx trp cnt        :%d\n",uVar13);
        uVar15 = fpga_read_reg(0xe30f2);
        printk("cla tx drp no e8 cnt  :%d\n",uVar15 & 0xffff);
        printk("cla tx drp e8 cnt     :%d\n",uVar15 >> 0x10);
        uVar13 = fpga_read_reg(0xe30f3);
        printk("cla rx fwd cnt        :%d\n",uVar13);
        uVar13 = fpga_read_reg(0xe30f4);
        printk("cla rx trp cnt        :%d\n",uVar13);
        uVar13 = fpga_read_reg(0xe30f5);
        printk("cla rx drp cnt        :%d\n",uVar13);
      }
      else {
        iVar14 = strcmp(pcVar26,"reason");
        if (iVar14 == 0) {
          printk("Action:0-forward;1-trap;2-drop\n");
          printk("======================================\n");
          printk("Forward Reason--type of packet:\n");
          printk("======================================\n");
          if (forwardPktType._0_4_ != 0) {
            puVar34 = forwardPktType;
            iVar14 = 0;
            do {
              printk("0x%02x:%s\n",iVar14);
              puVar34 = (undefined1 *)((int)puVar34 + 4);
              iVar14 = iVar14 + 1;
            } while (*(int *)puVar34 != 0);
          }
          printk("\n======================================\n");
          printk("Trap Reason--type of packet:\n");
          printk("======================================\n");
          iVar14 = 0;
          if (trapPktType != 0) {
            piVar35 = &trapPktType;
            iVar30 = 0;
            do {
              printk("0x%02x:%s\n",iVar30);
              piVar35 = piVar35 + 1;
              iVar30 = iVar30 + 1;
            } while (*piVar35 != 0);
          }
        }
        else {
          iVar14 = strcmp(pcVar26,"showcommrule");
          if (iVar14 == 0) {
            tm_show_common_rule_list();
            iVar14 = 0;
          }
          else {
            iVar14 = strcmp(pcVar26,"showfastrule");
            if (iVar14 == 0) {
              tm_show_fast_rule_list();
              iVar14 = 1;
            }
            else {
              iVar14 = strcmp(pcVar26,"gclacfg");
              if (iVar14 == 0) {
                __memzero(local_60,0x38);
                iVar14 = cla_get_config(local_60);
                if (iVar14 == 0) {
                  printk("AGE RD CLEAR:%d\n",local_60[0]);
                  pcVar24 = "1:Search Mac Table";
                  pcVar36 = "1:Register";
                  pcVar31 = "0:Acl";
                  pcVar26 = "trap";
                  if (local_44 == 0) {
                    pcVar24 = "0:Pass Through";
                  }
                  printk("MAC Request Ctrl:%s\n",pcVar24);
                  pcVar24 = pcVar36;
                  if (local_48 == 0) {
                    pcVar24 = pcVar31;
                  }
                  printk("Dn Broadcast Ctrl:%s\n",pcVar24);
                  pcVar24 = pcVar36;
                  if (local_4c == 0) {
                    pcVar24 = pcVar31;
                  }
                  printk("Dn Multicast Ctrl:%s\n",pcVar24);
                  pcVar24 = pcVar36;
                  if (local_50 == 0) {
                    pcVar24 = pcVar31;
                  }
                  printk("Dn Unicast Ctrl:%s\n",pcVar24);
                  if (local_54 == 0) {
                    pcVar36 = pcVar31;
                  }
                  printk("Up Unicast Ctrl:%s\n",pcVar36);
                  pcVar36 = "1:Enable";
                  if (local_58 == 0) {
                    pcVar36 = "0:Not Enabel";
                  }
                  printk("Modify Enable:%s\n",pcVar36);
                  pcVar36 = "1:Trap Enable";
                  if (local_60[1] == 0) {
                    pcVar36 = "0:Not Trap";
                  }
                  printk("Trap Cfg:%s\n",pcVar36);
                  printk("v6rd_del_en:%d\n",local_40);
                  printk("dslite_del_en:%d\n",local_3c);
                  pcVar36 = "all rule aging";
                  if (local_38 == 0) {
                    pcVar36 = "only highest pri rule aging";
                  }
                  printk("age_mode:%s\n",pcVar36);
                  pcVar36 = "outport from brg";
                  if (local_34 == 0) {
                    pcVar36 = "outport from cla";
                  }
                  printk("outport select:%s\n",pcVar36);
                  pcVar36 = pcVar26;
                  if (local_30 == 0) {
                    pcVar36 = "not trap";
                  }
                  printk("cfg_local_ip_mode_dn:%s\n",pcVar36);
                  if (local_2c == 0) {
                    pcVar26 = "not trap";
                  }
                  printk("cfg_local_ip_mode_up:%s\n",pcVar26);
                }
                else {
                  printk("[pp_cla_debug]cla get config fail, error code %d!\n",iVar14);
                }
              }
              else {
                iVar14 = strcmp(pcVar26,"showfastinfoall");
                if (iVar14 == 0) {
                  tm_show_fast_rule_list_detail();
                  iVar14 = 0;
                }
                else {
                  iVar14 = strcmp(pcVar26,"showaclinfoall");
                  if (iVar14 == 0) {
                    tm_show_common_rule_list_detail();
                    iVar14 = 0;
                  }
                  else {
                    local_8c = strcmp(pcVar26,"gfastentrynum");
                    if (local_8c == 0) {
                      local_88 = local_8c;
                      local_84[0] = local_8c;
                      local_60[0] = local_8c;
                      zte_api_sw_fast_entry_policy(local_84,local_60,&local_8c,&local_88);
                      printk("v4_up:%d, v4_dn:%d, v6_up:%d, v6_dn:%d\n",local_84[0],local_60[0],
                             local_8c,local_88);
                      printk("fast entry total %d\n",local_60[0] + local_84[0] + local_8c + local_88
                            );
                      iVar14 = 0;
                    }
                    else {
                      iVar14 = strcmp(pcVar26,"gparsehashkey");
                      if (iVar14 == 0) {
                        local_60[0] = 0;
                        local_60[1] = 0;
                        local_58 = 0;
                        local_54 = 0;
                        local_50 = 0;
                        local_4c = 0;
                        local_48 = 0;
                        local_44 = 0;
                        local_40 = 0;
                        local_3c = 0;
                        local_38 = 0;
                        local_34 = 0;
                        iVar14 = 0xe3098;
                        puVar29 = local_60;
                        do {
                          uVar15 = fpga_read_reg(iVar14);
                          puVar32 = puVar29 + 1;
                          *puVar29 = uVar15;
                          uVar15 = local_48;
                          iVar14 = iVar14 + 1;
                          puVar29 = puVar32;
                        } while (puVar32 != &local_30);
                        uVar1 = local_60[0] >> 0x10;
                        uVar16 = local_60[0] << 0xf;
                        uVar25 = local_60[0] >> 0x10 & 0xff;
                        uVar2 = local_60[0] >> 0x1f;
                        uVar39 = local_60[1] << 0xf;
                        uVar17 = local_58 & 1;
                        uVar37 = local_60[1] & 1;
                        uVar20 = local_54 & 1;
                        uVar3 = local_60[1] >> 0x11;
                        uVar40 = local_58 << 0xf;
                        uVar18 = local_50 & 1;
                        uVar4 = local_58 >> 0x11;
                        uVar21 = local_4c & 1;
                        uVar5 = local_54 >> 0x11;
                        uVar44 = local_54 << 0xf;
                        uVar27 = local_48 & 1;
                        uVar6 = local_50 >> 0x11;
                        uVar38 = local_50 << 0xf;
                        uVar7 = local_4c >> 0x11;
                        uVar45 = local_44 & 1;
                        uVar8 = local_48 >> 0x11;
                        uVar41 = local_40 & 1;
                        uVar19 = local_3c & 1;
                        uVar22 = local_38 & 1;
                        uVar9 = local_44 >> 0x11;
                        uVar10 = local_40 >> 0x11;
                        uVar33 = local_4c << 0xf;
                        uVar28 = local_34 & 1;
                        uVar11 = local_3c >> 0x11;
                        uVar42 = local_40 << 0xf;
                        uVar46 = local_44 << 0xf;
                        uVar12 = local_38 >> 0x11;
                        uVar23 = local_38 << 0xf;
                        uVar43 = local_3c << 0xf;
                        printk("outport:          0x%x\n",local_60[0] & 0x1f);
                        printk("inport:           0x%x\n",uVar16 >> 0x14);
                        printk("tag_level:        0x%x\n",(uVar25 << 0x1c) >> 0x1d);
                        printk("l2_type:          0x%x\n",(uVar25 << 0x1a) >> 0x1e);
                        printk("pppoe_flag:       0x%x\n",(uVar25 << 0x19) >> 0x1f);
                        printk("ex_rule_id:       0x%x\n",(uVar1 << 0x11) >> 0x18);
                        printk("ex_rule_mode:     0x%x\n",uVar2);
                        printk("direct:           0x%x\n",uVar37);
                        printk("extra_data0:      0x%x\n",uVar39 >> 0x10);
                        printk("extra_data1:      0x%x\n",uVar17 << 0xf | uVar3);
                        printk("extra_data2:      0x%x\n",uVar40 >> 0x10);
                        printk("extra_data3:      0x%x\n",uVar20 << 0xf | uVar4);
                        printk("extra_data4:      0x%x\n",uVar44 >> 0x10);
                        printk("extra_data5:      0x%x\n",uVar18 << 0xf | uVar5);
                        printk("extra_data6:      0x%x\n",uVar38 >> 0x10);
                        printk("extra_data7:      0x%x\n",uVar21 << 0xf | uVar6);
                        printk("extra_data8:      0x%x\n",uVar33 >> 0x10);
                        printk("extra_data9:      0x%x\n",uVar27 << 0xf | uVar7);
                        printk("extra_data10:     0x%x\n",(uVar15 << 0xf) >> 0x10);
                        printk("extra_data11:     0x%x\n",uVar45 << 0xf | uVar8);
                        printk("extra_data12:     0x%x\n",uVar46 >> 0x10);
                        printk("extra_data13:     0x%x\n",uVar41 << 0xf | uVar9);
                        printk("extra_data14:     0x%x\n",uVar42 >> 0x10);
                        printk("extra_data15:     0x%x\n",uVar19 << 0xf | uVar10);
                        printk("extra_data16:     0x%x\n",uVar43 >> 0x10);
                        printk("extra_data17:     0x%x\n",uVar22 << 0xf | uVar11);
                        printk("extra_data18:     0x%x\n",uVar23 >> 0x10);
                        printk("extra_data19:     0x%x\n",uVar28 << 0xf | uVar12);
                        iVar14 = 0;
                      }
                      else {
                        printk("%s: illegal operation <%s>\n","cla_info_show",*param_2);
                        iVar14 = 0;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return iVar14;
}

