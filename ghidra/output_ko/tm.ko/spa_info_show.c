// module: tm.ko
// function: spa_info_show @ 0x6f9ac
// size: 2172 bytes
//

undefined4 spa_info_show(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  char *__s1;
  uint *puVar7;
  undefined4 uVar8;
  uint local_54;
  uint local_50 [14];
  
  __s1 = (char *)*param_2;
  iVar1 = capable(0xc);
  if (iVar1 == 0) {
    return 0xffffffff;
  }
  iVar1 = strcmp(__s1,"helpSpa");
  if (iVar1 == 0) {
    printk("============================================================================\n");
    printk("Configuration Commands[HEX]\n");
    printk("============================================================================\n");
    printk(" echo [port]             > gvlaninframemode          - get vlan inframe mode\n");
    printk(" echo [port][vid][pri]   > sportpvid                 - set port pvid\n");
    printk(" echo [port]             > gportpvid                 - get port pvid\n");
    printk(" echo [action]           > sstpaction                - get stp action\n");
    printk(" echo [type][action]     > sproaction                - set protocol action\n");
    printk(" echo [port][vlTagMsk]   > sportvlanfilter           - set port tag type filter\n");
    printk(" echo [port]             > gportvlanfilter           - get port tag type filter\n");
    printk(" echo [port]             > gportpktfilter            - get port pkt type filter\n");
    printk(
          " echo [port][enable]     > sbpdupass802x             - set bpdu  passthrough  802.1x enable\n"
          );
    printk(
          " echo [port]             > gbpdupass802x             - get bpdu  passthrough  802.1x enable\n"
          );
    printk(" echo [port][enable]     > s802xtrap                 - set 802.1trap enable\n");
    printk(" echo [port]             > g802xtrap                 - get 802.1trap enable\n");
    printk(
          " echo [addr][acyion][reason][match_arrar][valid] > sonehashramentry                 - get 802.1trap enable\n"
          );
    printk(
          " echo [port][mode 0:DISNONE;1:DISALL;2:DISUNTAG;3:DISTAG] > svlaninframemode    - set vlan inframe mode\n"
          );
    printk(
          " echo [port][pkttype 0:noflt;1:fil not pro;2:flt all]     > sportpktfilter      - set port pkt type filter\n"
          );
    printk("============================================================================\n");
    printk("Display Commands: cat <file>\n");
    printk("============================================================================\n");
    printk(" cat statics                                           - dump printing options\n");
    printk(" cat pvid                                              - dump printing options\n");
    printk(" cat filter                                            - dump printing options\n");
    printk(" cat tpidSel                                           - dump printing options\n");
    printk(" cat desOut                                            - dump printing options\n");
    return 0;
  }
  iVar1 = strcmp(__s1,"statics");
  if (iVar1 == 0) {
    uVar8 = spaDebugStatics();
    return uVar8;
  }
  iVar1 = strcmp(__s1,"pvid");
  if (iVar1 != 0) {
    iVar1 = strcmp(__s1,"filter");
    if (iVar1 == 0) {
      uVar5 = fpga_read_reg(0x750aa);
      printk("addr 0x750aa: 0x%08x\n",uVar5);
      printk("0:not fil;1:fil not protocol pkt;2:fil all\n");
      uVar2 = 0;
      do {
        uVar6 = uVar2 + 1;
        printk("port %d filter 0x%x\n",uVar2,uVar5 >> ((uVar2 & 0x7f) << 1) & 3);
        uVar2 = uVar6;
      } while (uVar6 != 7);
      printk("cpu filter 0x%x\n",(uVar5 << 0xe) >> 0x1e);
      uVar8 = 0;
    }
    else {
      uVar2 = strcmp(__s1,"tpidSel");
      if (uVar2 == 0) {
        local_50[0] = uVar2;
        printk("----------------------------------\n");
        printk("| %-5s| %-5s| %-5s| %-10s|\n",&_LC88,&_LC89,&_LC90,"tpid_num");
        iVar1 = 0;
        do {
          iVar3 = tm_port_more_name_get(iVar1,local_50);
          uVar2 = 0;
          do {
            iVar4 = tm_in_port_tpid_select_get(iVar1,&local_54,uVar2);
            if (iVar3 != 0 || iVar4 != 0) {
              if (6 < g_tm_debug_level) {
                printk("spaDebugTpidSelShow failed!\n");
                return 0xffffffff;
              }
              return 0xffffffff;
            }
            uVar5 = uVar2 >> 2;
            uVar6 = uVar2 & 3;
            uVar2 = uVar2 + 1;
            printk("| %-5s| %-5d| %-5d| %-10d|\n",local_50[0],uVar5,uVar6,local_54);
            iVar3 = 0;
          } while (uVar2 != 0x10);
          iVar1 = iVar1 + 1;
        } while (iVar1 != 9);
        printk("----------------------------------\n");
        uVar8 = 0;
      }
      else {
        iVar1 = strcmp(__s1,"desOut");
        if (iVar1 == 0) {
          puVar7 = &local_54;
          iVar1 = 0x7517b;
          do {
            uVar2 = fpga_read_reg(iVar1);
            puVar7 = puVar7 + 1;
            *puVar7 = uVar2;
            iVar1 = iVar1 + 1;
          } while (puVar7 != local_50 + 0xd);
          uVar8 = 1;
          printk("---------------------------------------------\n");
          printk("spa to sadm  des info:\n");
          printk("---------------------------------------------\n");
          printk("Pkt_len          (0-13)     :%d\n",local_50[0] & 0x3fff);
          printk("hpmau1           (14-26)    :0x%x\n",(local_50[0] << 5) >> 0x13);
          printk("hpmau2           (27-39)    :0x%x\n",
                 local_50[0] >> 0x1b | (local_50[1] & 0xff) << 5);
          printk("hpmau3           (40-52)    :0x%x\n",(local_50[1] << 10) >> 0x13);
          printk("head_len         (53-60)    :0x%x\n",(local_50[1] << 3) >> 0x18);
          printk("inport           (61-64)    :0x%x\n",local_50[1] >> 0x1d | (local_50[2] & 1) << 3)
          ;
          printk("ssid             (65-67)    :0x%x\n",(local_50[2] << 0x1c) >> 0x1d);
          printk("gemport_id       (68-83)    :0x%x\n",(local_50[2] << 0x14) >> 0x18);
          printk("direction        (84)       :0x%x\n",(local_50[2] << 0xb) >> 0x1f);
          printk("action           (85-86)    :0x%x\n",(local_50[2] << 9) >> 0x1e);
          uVar2 = (local_50[2] << 2) >> 0x19;
          printk("Action reason    (87-93)    :0x%2x:%s\n",uVar2,(&trapPktType)[uVar2]);
          printk("omci_flag        (94)       :0x%x\n",(local_50[2] << 1) >> 0x1f);
          printk("802.1x_flag      (95)       :0x%x\n",local_50[2] >> 0x1f);
          printk("IPv6_multi       (96)       :0x%x\n",local_50[3] & 1);
          printk("SA_learn         (97)       :0x%x\n",(local_50[3] << 0x1e) >> 0x1f);
          printk("bpdu_flag        (98)       :0x%x\n",(local_50[3] << 0x1d) >> 0x1f);
          printk("pvid_flag        (99)       :0x%x\n",(local_50[3] << 0x1c) >> 0x1f);
          printk("Qnum             (100-102)  :0x%x\n",(local_50[3] << 0x19) >> 0x1d);
          printk("Pri              (103-105)  :0x%x\n",(local_50[3] << 0x16) >> 0x1d);
          printk("dscp             (106-111)  :0x%x\n",(local_50[3] << 0x10) >> 0x1a);
          printk("OAM              (112-114)  :0x%x\n",(local_50[3] << 0xd) >> 0x1d);
          printk("Cast_type        (115-116)  :0x%x\n",(local_50[3] << 0xb) >> 0x1e);
          printk("Tag_type         (117-119)  :0x%x\n",(local_50[3] << 8) >> 0x1d);
          printk("l3_en            (120)      :0x%x\n",(local_50[3] << 7) >> 0x1f);
          printk("port_map         (121-122)  :0x%x\n",(local_50[3] << 5) >> 0x1e);
          printk("spec_flow        (123-124)  :0x%x\n",(local_50[3] << 3) >> 0x1e);
          printk("pps(flow)_limit  (125)      :0x%x\n",(local_50[3] << 2) >> 0x1f);
          printk("move_flag        (126)      :0x%x\n",(local_50[3] << 1) >> 0x1f);
          printk("PPPoE_drop_flag  (127-129)  :0x%x\n",local_50[3] >> 0x1f | (local_50[4] & 3) << 1)
          ;
          printk("color            (130)      :0x%x\n",(local_50[4] << 0x1d) >> 0x1f);
          printk("trunk_index      (131-134)  :0x%x\n",(local_50[4] << 0x19) >> 0x1c);
          printk("ip_flag          (135)      :0x%x\n",(local_50[4] << 0x18) >> 0x1f);
          printk("ipv4_flag        (136)      :0x%x\n",(local_50[4] << 0x17) >> 0x1f);
          printk("ipv6_flag        (137)      :0x%x\n",(local_50[4] << 0x16) >> 0x1f);
          printk("tcp_flag         (138)      :0x%x\n",(local_50[4] << 0x15) >> 0x1f);
          printk("udp_flag         (139)      :0x%x\n",(local_50[4] << 0x14) >> 0x1f);
          printk("PPPoE            (140)      :0x%x\n",(local_50[4] << 0x13) >> 0x1f);
          printk("v4inv6           (141)      :0x%x\n",(local_50[4] << 0x12) >> 0x1f);
          printk("v6inv4           (142)      :0x%x\n",(local_50[4] << 0x11) >> 0x1f);
          printk("udp_lite_flag    (143)      :0x%x\n",(local_50[4] << 0x10) >> 0x1f);
          printk("l2_type          (144-145)  :0x%x\n",(local_50[4] << 0xe) >> 0x1e);
          printk("extend_flag      (146)      :0x%x\n",(local_50[4] << 0xd) >> 0x1f);
          printk("l2_offset        (147-154)  :0x%x\n",(local_50[4] << 5) >> 0x18);
          printk("l3_offset_v4     (155-162)  :0x%x\n",(local_50[5] & 7) << 5 | local_50[4] >> 0x1b)
          ;
          printk("l3_offset_v6     (163-170)  :0x%x\n",(local_50[5] << 0x15) >> 0x18);
          printk("l3_offset_v6_last(171-178)  :0x%x\n",(local_50[5] << 0xd) >> 0x18);
          printk("l4_offset        (179-186)  :0x%x\n",(local_50[5] << 5) >> 0x18);
          printk("l5_offset        (187-194)  :0x%x\n",(local_50[6] & 7) << 5 | local_50[5] >> 0x1b)
          ;
          printk("outer_pri        (195-197)  :0x%x\n",(local_50[6] << 0x1a) >> 0x1d);
          printk("inner_pri        (198-200)  :0x%x\n",(local_50[6] << 0x17) >> 0x1d);
          printk("outer_vid        (201-212)  :0x%x\n",(local_50[6] << 0xb) >> 0x14);
          printk("inner_vid        (213-224)  :0x%x\n",
                 local_50[6] >> 0x15 | (local_50[7] & 1) << 0xb);
          printk("SA               (225-272)  :%04x%08x\n",(local_50[8] << 0xf) >> 0x10,
                 local_50[8] << 0x1f | local_50[7] >> 1);
          printk("DA               (273-320)  :%04x%08x\n",
                 (local_50[9] << 2) >> 0x11 | (local_50[10] & 1) << 0xf,
                 (local_50[8] << 2) >> 0x11 | local_50[9] << 0xf);
        }
        else {
          iVar1 = strcmp(__s1,"gmatchram");
          if (iVar1 == 0) {
            spaDebugGetMatchRam();
            uVar8 = 0;
          }
          else {
            iVar1 = strcmp(__s1,"ghashram");
            if (iVar1 == 0) {
              spaDebugGetHashRam();
              uVar8 = 0;
            }
            else {
              iVar1 = strcmp(__s1,"setmatchruleandhashram");
              if (iVar1 == 0) {
                spaDebugSetMatchRuleAndHashRam();
                uVar8 = 0;
              }
              else {
                uVar8 = 0;
                printk("%s: illegal operation <%s>\n","spa_info_show",*param_2);
              }
            }
          }
        }
      }
    }
    return uVar8;
  }
  iVar1 = 0x750a3;
  do {
    uVar2 = fpga_read_reg(iVar1);
    iVar3 = iVar1 + 1;
    printk("addr 0x%x: 0x%08x --- port %d pvid %d\n",iVar1,uVar2,iVar1 + -0x750a3,uVar2 & 0xfff);
    iVar1 = iVar3;
  } while (iVar3 != 0x750aa);
  return 0;
}

