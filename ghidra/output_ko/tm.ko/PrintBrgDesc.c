// module: tm.ko
// function: PrintBrgDesc @ 0x7113c
// size: 3420 bytes
//

undefined4 PrintBrgDesc(int param_1)

{
  undefined1 uVar1;
  uint *puVar2;
  uint *puVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint *puVar9;
  byte *pbVar10;
  uint *puVar11;
  uint local_b8;
  uint local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  uint local_a4;
  undefined4 local_a0;
  uint local_9c;
  undefined4 local_98;
  undefined4 local_94;
  byte local_90;
  undefined4 local_8f;
  byte local_8b;
  byte bStack_8a;
  byte bStack_89;
  byte bStack_88;
  byte local_87;
  byte bStack_86;
  byte bStack_85;
  byte bStack_84;
  byte local_83;
  byte bStack_82;
  byte bStack_81;
  byte bStack_80;
  byte local_7f;
  byte bStack_7e;
  byte bStack_7d;
  byte bStack_7c;
  byte local_7b;
  byte bStack_7a;
  byte bStack_79;
  byte bStack_78;
  byte local_77;
  byte bStack_76;
  byte local_75 [4];
  byte local_71;
  byte local_70;
  byte local_6f;
  byte local_6e;
  byte local_6d;
  byte local_5b;
  byte local_5a;
  byte local_59;
  byte local_58;
  byte local_57;
  byte local_56;
  byte local_55;
  uint local_54 [10];
  byte bStack_2c;
  uint auStack_24 [2];
  byte abStack_1c [8];
  
  __memzero(&local_b8,0x29);
  pbVar10 = &local_58;
  __memzero(&local_8f,0x3b);
  iVar8 = 0xe2380;
  do {
    uVar4 = fpga_read_reg(iVar8);
    pbVar10 = pbVar10 + 4;
    *(undefined4 *)pbVar10 = uVar4;
    iVar8 = iVar8 + 1;
  } while (pbVar10 != abStack_1c);
  sbrg_set_desc_monitor_sel(param_1);
  if (param_1 == 0) {
    local_b8 = local_54[0];
    local_b4 = local_54[1];
    local_b0 = local_54[2];
    local_ac = local_54[3];
    local_a8 = local_54[4];
    local_a4 = local_54[5];
    local_a0 = local_54[6];
    local_9c = local_54[7];
    local_98 = local_54[8];
    local_94 = local_54[9];
    local_90 = bStack_2c;
    printk("pkt_len(13:00)                         0x%x\n",local_54[0] & 0x3fff);
    printk("1th_pmau(26:14)                        0x%x\n",(local_b8 << 5) >> 0x13);
    printk("2th_pmau(39:27)                        0x%x\n",(local_b4 & 0xff) << 5 | local_b8 >> 0x1b
          );
    printk("3th_pmau(52:40)                        0x%x\n",(local_b4 << 0xb) >> 0x13);
    printk("head_len(60:53)                        0x%x\n",((local_b4 >> 0x10) << 0x13) >> 0x18);
    printk("inport(64:61)                          0x%x\n",(local_b0 & 1) << 3 | local_b4 >> 0x1d);
    printk("ssid(67:65)                            0x%x\n",(local_b0 << 0x1c) >> 0x1d);
    printk("gemport_id(79:68)                      0x%x\n",(ushort)local_b0 >> 4);
    printk("rsv(80:80)                             0x%x\n",local_b0._2_1_ & 1);
    printk("multi release(81:81)                   0x%x\n",((local_b0 >> 0x10) << 0x1e) >> 0x1f);
    printk("tcont mirrow bit5(82:82)               0x%x\n",((local_b0 >> 0x10) << 0x1d) >> 0x1f);
    printk("tcont bit 5                            0x%x\n",((local_b0 >> 0x10) << 0x1c) >> 0x1f);
    printk("direction(84:84)                       0x%x\n",((local_b0 >> 0x10) << 0x1b) >> 0x1f);
    printk("action(86:85)                          0x%x\n",((local_b0 >> 0x10) << 0x19) >> 0x1e);
    uVar5 = ((local_b0 >> 0x10) << 0x12) >> 0x19;
    printk("action_rsn(93:87)                      0x%x(%s)\n",uVar5,(&trapPktType)[uVar5]);
    printk("pae2sadm_flag(94:94)                   0x%x\n",((local_b0 >> 0x18) << 0x19) >> 0x1f);
    printk("multi_ipv6(95:95)                      0x%x\n",local_b0._3_1_ >> 7);
    printk("sa_learn(96:96)                        0x%x\n",local_ac & 1);
    printk("bpdu_flag(97:97)                       0x%x\n",(local_ac << 0x1e) >> 0x1f);
    printk("pvid_flag(98:98)                       0x%x\n",(local_ac << 0x1d) >> 0x1f);
    printk("pkt_qnum(101:99)                       0x%x\n",(local_ac << 0x1a) >> 0x1d);
    printk("pkt_pri/cos(104:102)                   0x%x\n",(local_ac << 0x17) >> 0x1d);
    printk("ip_dscp(110:105)                       0x%x\n",((local_ac >> 8) << 0x19) >> 0x1a);
    printk("oam(113:111)                           0x%x\n",(local_ac << 0xe) >> 0x1d);
    printk("cast_type(115:114)                     0x%x\n",((local_ac >> 0x10) << 0x1c) >> 0x1e);
    printk("tag_type(118:116)                      0x%x\n",((local_ac >> 0x10) << 0x19) >> 0x1d);
    printk("l3_en(119:119)                         0x%x\n",local_ac._2_1_ >> 7);
    printk("port_map(121:120)                      0x%x\n",local_ac._3_1_ & 3);
    printk("spec_flow(123:122)                     0x%x\n",((local_ac >> 0x18) << 0x1c) >> 0x1e);
    printk("pps_flag(124:124)                      0x%x\n",((local_ac >> 0x18) << 0x1b) >> 0x1f);
    printk("move_flag(125:125)                     0x%x\n",((local_ac >> 0x18) << 0x1a) >> 0x1f);
    printk("pppoe_drop_flag/drop_reason(128:126)   0x%x\n",(local_a8 & 1) << 2 | local_ac >> 0x1e);
    printk("color(129:129)                         0x%x\n",(local_a8 << 0x1e) >> 0x1f);
    printk("trunk_index(133:130)                   0x%x\n",(local_a8 << 0x1a) >> 0x1c);
    printk("ip_flag(134:134)                       0x%x\n",(local_a8 << 0x19) >> 0x1f);
    printk("ipv4_flag(135:135)                     0x%x\n",(byte)local_a8 >> 7);
    printk("ipv6_flag(136:136)                     0x%x\n",local_a8._1_1_ & 1);
    printk("tcp_flag(137:137)                      0x%x\n",((local_a8 >> 8) << 0x1e) >> 0x1f);
    printk("udp_flag(138:138)                      0x%x\n",((local_a8 >> 8) << 0x1d) >> 0x1f);
    printk("pppoe_format(139:139)                  0x%x\n",((local_a8 >> 8) << 0x1c) >> 0x1f);
    printk("v4inv6_flag(140:140)                   0x%x\n",((local_a8 >> 8) << 0x1b) >> 0x1f);
    printk("v6inv4_flag(141:141)                   0x%x\n",((local_a8 >> 8) << 0x1a) >> 0x1f);
    printk("udp_lite_flag(142:142)                 0x%x\n",((local_a8 >> 8) << 0x19) >> 0x1f);
    printk("l2_type(144:143)                       0x%x\n",(local_a8 << 0xf) >> 0x1e);
    printk("extend_flag(145:145)                   0x%x\n",((local_a8 >> 0x10) << 0x1e) >> 0x1f);
    printk("l2_offset(153:146)                     0x%x\n",((local_a8 >> 0x10) << 0x16) >> 0x18);
    printk("l3_offset_v4(161:154)                  0x%x\n",(local_a4 & 3) << 6 | local_a8 >> 0x1a);
    printk("l3_offset_v6(169:162)                  0x%x\n",(local_a4 << 0x16) >> 0x18);
    printk("l3_offset_v6_last(177:170)             0x%x\n",(local_a4 << 0xe) >> 0x18);
    printk("l4_offset(185:178)                     0x%x\n",((local_a4 >> 0x10) << 0x16) >> 0x18);
    printk("l5_offset(193:186)                     0x%x\n",(local_a0 & 3) << 6 | local_a4 >> 0x1a);
    printk("outer_pri(196:194)                     0x%x\n",(local_a0 << 0x1b) >> 0x1d);
    printk("inner_pri(199:197)                     0x%x\n",(byte)local_a0 >> 5);
    printk("outer_vid(211:200)                     0x%x\n",(local_a0 << 0xc) >> 0x14);
    printk("inner_vid(213:212)                     0x%x\n",local_a0._2_2_ >> 4);
    uVar5 = local_9c & 0xff;
    printk("smac(271:224)                          %02x:%02x:%02x:%02x:%02x:%02x\n",uVar5,uVar5,
           uVar5,uVar5,local_98 & 0xff,local_98 & 0xff);
    printk("from_cpu(528:528)                      0x%x\n",local_98._2_1_ & 1);
    printk("outport_cpu(532:529)                   0x%x\n",((local_98 >> 0x10) << 0x1b) >> 0x1c);
    printk("cpu_queue_id(535:533)                  0x%x\n",local_98._2_1_ >> 5);
    printk("da_known_cpu(536:536)                  0x%x\n",local_98._3_1_ & 1);
    printk("vlan_change_cpu(537:537)               0x%x\n",((local_98 >> 0x18) << 0x1e) >> 0x1f);
    printk("vlan_org(549:538)                      0x%x\n",(local_94 & 0x3f) << 6 | local_98 >> 0x1a
          );
    printk("pri_org(552:550)                       0x%x\n",(local_94 << 0x17) >> 0x1d);
    printk("ingress_mirror(553:553)                0x%x\n",((local_94 >> 8) << 0x1e) >> 0x1f);
    printk("ram_id(560:554)                        0x%x\n",(local_94 << 0xf) >> 0x19);
    printk("fwd_rsn(567:561)                       0x%x\n",local_94._2_1_ >> 1);
    printk("len_change(581:568)                    0x%x\n",local_94 >> 0x18 | (local_90 & 0x3f) << 8
          );
  }
  else {
    puVar2 = local_54;
    puVar3 = &local_8f;
    do {
      puVar11 = puVar3;
      puVar9 = puVar2;
      uVar5 = puVar9[1];
      uVar6 = puVar9[2];
      uVar7 = puVar9[3];
      *puVar11 = *puVar9;
      puVar11[1] = uVar5;
      puVar11[2] = uVar6;
      puVar11[3] = uVar7;
      puVar2 = puVar9 + 4;
      puVar3 = puVar11 + 4;
    } while (puVar9 + 4 != auStack_24);
    uVar5 = puVar9[5];
    puVar11[4] = puVar9[4];
    puVar11[5] = uVar5;
    uVar1 = *(undefined1 *)((int)puVar9 + 0x1a);
    *(short *)(puVar11 + 6) = (short)puVar9[6];
    *(undefined1 *)((int)puVar11 + 0x1a) = uVar1;
    printk("pkt_len(13:00)                         0x%x\n",
           (uint)(byte)local_8f | (local_8f._1_1_ & 0x3f) << 8);
    printk("1th_pmau(26:14)                        0x%x\n",
           (uint)local_8f._2_1_ << 2 | (uint)(local_8f._1_1_ >> 6) | (local_8f._3_1_ & 7) << 10);
    printk("2th_pmau(39:27)                        0x%x\n",
           (uint)local_8b << 5 | (uint)(local_8f._3_1_ >> 3));
    printk("3th_pmau(52:40)                        0x%x\n",(uint)bStack_8a | (bStack_89 & 0x1f) << 8
          );
    printk("head_len(60:53)                        0x%x\n",bStack_88 << 3 | bStack_89 >> 5);
    printk("inport(64:61)                          0x%x\n",(local_87 & 1) << 3 | bStack_88 >> 5);
    printk("ssid(67:65)                            0x%x\n",((uint)local_87 << 0x1c) >> 0x1d);
    printk("gemport_id(79:68)                      0x%x\n",
           (uint)bStack_86 << 4 | (uint)(local_87 >> 4));
    printk("rsv(80:80)                             0x%x\n",bStack_85 & 1);
    printk("multi_release(81:81)                   0x%x\n",((uint)bStack_85 << 0x1e) >> 0x1f);
    printk("tcont_mirrow_bit5(82:82)               0x%x\n",((uint)bStack_85 << 0x1d) >> 0x1f);
    printk("tcont_bit_5(83:83)                     0x%x\n",((uint)bStack_85 << 0x1c) >> 0x1f);
    printk("direction(84:84)                       0x%x\n",((uint)bStack_85 << 0x1b) >> 0x1f);
    printk("action(86:85)                          0x%x\n",((uint)bStack_85 << 0x19) >> 0x1e);
    uVar5 = (bStack_84 & 0x3f) << 1 | (uint)(bStack_85 >> 7);
    printk("action_rsn(93:87)                      0x%x(%s)\n",uVar5,(&trapPktType)[uVar5]);
    printk("pkt_qnum(96:94)                        0x%x\n",(local_83 & 1) << 2 | bStack_84 >> 6);
    printk("pkt_pri/cos(99:97)                     0x%x\n",((uint)local_83 << 0x1c) >> 0x1d);
    printk("ip_dscp(105:100)                       0x%x\n",(bStack_82 & 3) << 4 | local_83 >> 4);
    printk("oam(108:106)                           0x%x\n",((uint)bStack_82 << 0x1b) >> 0x1d);
    printk("cast_type(110:109)                     0x%x\n",((uint)bStack_82 << 0x19) >> 0x1e);
    printk("tag_type(113:111)                      0x%x\n",(bStack_81 & 3) << 1 | bStack_82 >> 7);
    printk("l3_en(114:114)                         0x%x\n",((uint)bStack_81 << 0x1d) >> 0x1f);
    printk("port_map(116:115)                      0x%x\n",((uint)bStack_81 << 0x1b) >> 0x1e);
    printk("spec_flow(118:117)                     0x%x\n",((uint)bStack_81 << 0x19) >> 0x1e);
    printk("pps_flag(119:119)                      0x%x\n",bStack_81 >> 7);
    printk("move_flag(120:120)                     0x%x\n",bStack_80 & 1);
    printk("pppoe_drop_flag/drop_reason(123:121)   0x%x\n",((uint)bStack_80 << 0x1c) >> 0x1d);
    printk("color(124:124)                         0x%x\n",((uint)bStack_80 << 0x1b) >> 0x1f);
    printk("trunk_index(128:125)                   0x%x\n",(local_7f & 1) << 3 | bStack_80 >> 5);
    printk("ip_flag(129:129)                       0x%x\n",((uint)local_7f << 0x1e) >> 0x1f);
    printk("ipv4_flag(130:130)                     0x%x\n",((uint)local_7f << 0x1d) >> 0x1f);
    printk("ipv6_flag(131:131)                     0x%x\n",((uint)local_7f << 0x1c) >> 0x1f);
    printk("tcp_flag(132:132)                      0x%x\n",((uint)local_7f << 0x1b) >> 0x1f);
    printk("udp_flag(133:133)                      0x%x\n",((uint)local_7f << 0x1a) >> 0x1f);
    printk("pppoe_format(134:134)                  0x%x\n",((uint)local_7f << 0x19) >> 0x1f);
    printk("v4inv6_flag(135:135)                   0x%x\n",local_7f >> 7);
    printk("v6inv4_flag(136:136)                   0x%x\n",bStack_7e & 1);
    printk("udp_lite_flag(137:137)                 0x%x\n",((uint)bStack_7e << 0x1e) >> 0x1f);
    printk("l2_type(139:138)                       0x%x\n",((uint)bStack_7e << 0x1c) >> 0x1e);
    printk("extend_flag(140:140)                   0x%x\n",((uint)bStack_7e << 0x1b) >> 0x1f);
    printk("l2_offset(148:141)                     0x%x\n",bStack_7d << 3 | bStack_7e >> 5);
    printk("l3_offset_v4(156:149)                  0x%x\n",bStack_7c << 3 | bStack_7d >> 5);
    printk("l3_offset_v6(164:157)                  0x%x\n",local_7b << 3 | bStack_7c >> 5);
    printk("l3_offset_v6_last(172:165)             0x%x\n",bStack_7a << 3 | local_7b >> 5);
    printk("l4_offset(180:173)                     0x%x\n",bStack_79 << 3 | bStack_7a >> 5);
    printk("l5_offset(188:181)                     0x%x\n",bStack_78 << 3 | bStack_79 >> 5);
    printk("outer_pri(191:189)                     0x%x\n",bStack_78 >> 5);
    printk("inner_pri(194:192)                     0x%x\n",local_77 & 7);
    printk("outer_vid(206:195)                     0x%x\n",
           (bStack_76 & 0x7f) << 5 | (uint)(local_77 >> 3));
    printk("vlan_org(218:207)                      0x%x\n",
           (uint)local_75[0] << 1 | (uint)(bStack_76 >> 7) | (local_75[1] & 7) << 9);
    printk("pri_org(221:219)                       0x%x\n",((uint)local_75[1] << 0x1a) >> 0x1d);
    printk("ingress_mirror(222:222)                0x%x\n",((uint)local_75[1] << 0x19) >> 0x1f);
    printk("ram_id(229:223)                        0x%x\n",
           (local_75[2] & 0x3f) << 1 | local_75[1] >> 7);
    printk("outport(239:230)                       0x%x\n",
           (uint)local_75[3] << 2 | (uint)(local_75[2] >> 6));
    printk("ssid_flag(240:240)                     0x%x\n",local_71 & 1);
    printk("vtrans2vcheck_vlanlist(420:241)        0x%x\n",
           (uint)local_70 << 7 | (uint)(local_71 >> 1) | (uint)local_6f << 0xf |
           (uint)local_6e << 0x17 | (uint)local_6d << 0x1f);
    printk("gem_mir(421:421)                       0x%x\n",((uint)local_5b << 0x1a) >> 0x1f);
    printk("qnum_pon(424:422)                      0x%x\n",(local_5a & 1) << 2 | local_5b >> 6);
    printk("qnum_uni0(427:425)                     0x%x\n",((uint)local_5a << 0x1c) >> 0x1d);
    printk("qnum_uni1(430:428)                     0x%x\n",((uint)local_5a << 0x19) >> 0x1d);
    printk("qnum_uni2(433:431)                     0x%x\n",(local_59 & 3) << 1 | local_5a >> 7);
    printk("qnum_uni3(436:434)                     0x%x\n",((uint)local_59 << 0x1b) >> 0x1d);
    printk("qnum_uni4(439:437)                     0x%x\n",local_59 >> 5);
    printk("qnum_wifi0(442:440)                    0x%x\n",local_58 & 7);
    printk("qnum_wifi1(445:443)                    0x%x\n",((uint)local_58 << 0x1a) >> 0x1d);
    printk("from_cpu(446:446)                      0x%x\n",((uint)local_58 << 0x19) >> 0x1f);
    printk("cpu_que_id(449:447)                    0x%x\n",(local_57 & 3) << 1 | local_58 >> 7);
    printk("fwd_rsn(456:450)                       0x%x\n",(local_56 & 1) << 6 | local_57 >> 2);
    printk("len_change(470:457)                    0x%x\n",
           (local_55 & 0x7f) << 7 | (uint)(local_56 >> 1));
  }
  return 0;
}

