// module: tm.ko
// function: cla_info_store @ 0x738fc
// size: 4220 bytes
//

undefined4 cla_info_store(undefined4 param_1,undefined4 *param_2,char *param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  char *__s1;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint local_148;
  int local_144;
  uint local_140;
  uint local_13c;
  uint local_138;
  undefined4 local_134;
  undefined4 local_130;
  undefined4 local_12c;
  undefined4 local_128;
  byte local_124;
  undefined1 uStack_123;
  byte bStack_122;
  byte bStack_121;
  undefined1 uStack_120;
  undefined1 uStack_11f;
  byte bStack_11e;
  byte bStack_11d;
  undefined1 local_11c;
  undefined1 uStack_11b;
  byte bStack_11a;
  byte bStack_119;
  undefined1 uStack_118;
  undefined1 uStack_117;
  byte bStack_116;
  byte bStack_115;
  undefined1 local_114;
  undefined1 uStack_113;
  byte bStack_112;
  byte bStack_111;
  undefined1 uStack_110;
  undefined1 uStack_10f;
  byte bStack_10e;
  byte bStack_10d;
  undefined1 local_10c;
  undefined1 uStack_10b;
  byte bStack_10a;
  byte bStack_109;
  byte bStack_108;
  undefined1 uStack_107;
  undefined1 uStack_106;
  byte bStack_105;
  undefined1 uStack_104;
  undefined1 uStack_103;
  undefined1 uStack_102;
  byte local_101;
  undefined1 uStack_100;
  undefined1 uStack_ff;
  undefined1 uStack_fe;
  byte bStack_fd;
  undefined1 uStack_fc;
  byte local_fb;
  byte bStack_fa;
  byte local_f9;
  undefined4 local_f8;
  undefined2 local_f4;
  undefined2 local_f2;
  byte local_f0 [4];
  uint local_ec;
  uint local_e8;
  uint local_e4;
  uint local_e0;
  uint local_dc;
  uint local_d8;
  byte local_d4 [4];
  uint local_d0;
  short local_cc [2];
  uint local_c8;
  short local_c4 [2];
  uint local_c0;
  short local_bc [2];
  uint local_b8;
  short local_b4 [2];
  uint local_b0;
  short local_ac [2];
  uint local_a8;
  short local_a4 [2];
  uint local_a0;
  short local_9c [2];
  uint local_98;
  short local_94 [2];
  uint local_90;
  short local_8c [2];
  uint local_88;
  short local_84 [2];
  undefined1 local_80 [92];
  
  local_148 = 0;
  local_144 = 0;
  local_140 = 0;
  local_13c = 0;
  local_138 = 0;
  __s1 = (char *)*param_2;
  memset(local_f0,0,200);
  iVar1 = capable(0xc);
  if (iVar1 == 0) {
    return 0xffffffff;
  }
  sscanf(param_3,"%x %x %x %x %x",&local_148,&local_144,&local_140,&local_13c,&local_138);
  disableIRQinterrupts();
  iVar1 = strcmp(__s1,"flowInfoList");
  if (iVar1 == 0) {
    tm_show_list(local_148);
  }
  else {
    iVar1 = strcmp(__s1,"gextraindextable");
    uVar6 = local_148;
    if (iVar1 == 0) {
      __memzero(&local_134,0x14);
      iVar1 = cla_get_extra_index_table(uVar6,&local_134);
      if (iVar1 == 0) {
        printk("cla extra_index_table get:\n");
        printk("valid           :%d\n",((uint)bStack_122 << 0x1b) >> 0x1f);
        printk("noMatch config  :0x%x\n",((uint)bStack_122 << 0x1c) >> 0x1e);
        printk("extra mode      :0x%x\n",bStack_122 & 1);
        printk("index valide    :0x%x\n",CONCAT11(uStack_123,local_124));
        printk("extract index15 :0x%x\n",local_128._3_1_);
        printk("extract index14 :0x%x\n",local_128._2_1_);
        printk("extract index13 :0x%x\n",local_128._1_1_);
        printk("extract index12 :0x%x\n",local_128 & 0xff);
        printk("extract index11 :0x%x\n",local_12c._3_1_);
        printk("extract index10 :0x%x\n",local_12c._2_1_);
        printk("extract index9  :0x%x\n",local_12c._1_1_);
        printk("extract index8  :0x%x\n",local_12c & 0xff);
        printk("extract index7  :0x%x\n",local_130._3_1_);
        printk("extract index6  :0x%x\n",local_130._2_1_);
        printk("extract index5  :0x%x\n",local_130._1_1_);
        printk("extract index4  :0x%x\n",local_130 & 0xff);
        printk("extract index3  :0x%x\n",local_134._3_1_);
        printk("extract index2  :0x%x\n",local_134._2_1_);
        printk("extract index1  :0x%x\n",local_134._1_1_);
        printk("extract index0  :0x%x\n",local_134 & 0xff);
      }
      else {
        printk("get cla extra_index_table fail, error code %d!\n");
      }
    }
    else {
      iVar1 = strcmp(__s1,"gextraruletable");
      uVar6 = local_148;
      if (iVar1 == 0) {
        __memzero(&local_134,0x44);
        iVar1 = cla_get_extra_rule_table(uVar6,&local_134);
        if (iVar1 == 0) {
          printk("CLA extra_rule_table get: \n");
          printk("offset19_type = 0x%x, offset18_type = 0x%x, offset17_type = 0x%x,offset16_type = 0x%x\n"
                 ,((uint)local_f2._1_1_ << 0x1c) >> 0x1d,((uint)local_f2 << 0x17) >> 0x1d,
                 ((uint)(byte)local_f2 << 0x1a) >> 0x1d,(byte)local_f2 & 7);
          printk("offset15_type = 0x%x, offset14_type = 0x%x, offset13_type = 0x%x,offset12_type = 0x%x\n"
                 ,local_f4._1_1_ >> 5,((uint)local_f4._1_1_ << 0x1b) >> 0x1d,
                 ((uint)local_f4 << 0x16) >> 0x1d,((uint)(byte)local_f4 << 0x19) >> 0x1d);
          printk("offset11_type = 0x%x, offset10_type = 0x%x, offset9_type = 0x%x,offset8_type = 0x%x\n"
                 ,((uint)(byte)local_f4 << 0x1c) >> 0x1d,
                 ((byte)local_f4 & 1) << 2 | (uint)(local_f8._3_1_ >> 6),
                 ((uint)local_f8._3_1_ << 0x1a) >> 0x1d,local_f8._3_1_ & 7);
          printk("offset7_type = 0x%x, offset6_type = 0x%x, offset5_type = 0x%x,offset4_type = 0x%x\n"
                 ,local_f8._2_1_ >> 5,((uint)local_f8._2_1_ << 0x1b) >> 0x1d,
                 (local_f8 << 0xe) >> 0x1d,((local_f8 >> 8) << 0x19) >> 0x1d);
          printk("offset3_type = 0x%x, offset2_type = 0x%x, offset1_type = 0x%x,offset0_type = 0x%x\n"
                 ,((local_f8 >> 8) << 0x1c) >> 0x1d,(local_f8 << 0x17) >> 0x1d,
                 (local_f8 << 0x1a) >> 0x1d,local_f8 & 7);
          uVar6 = (uint)local_f9;
          printk("reserve = 0x%x, extended_mask = 0x%x, dslite_v6rd_mask = 0x%x,Cvlan_mask = 0x%x\n"
                 ,local_f9 >> 5,(uVar6 << 0x1b) >> 0x1f,(uVar6 << 0x1c) >> 0x1f,
                 (uVar6 << 0x1d) >> 0x1f);
          printk("Memory_ctrl = 0x%x, hash_len = 0x%x, Rule_mode = 0x%x,No_Match_Ctrl = 0x%x\n",
                 ((uint)local_f9 << 0x1e) >> 0x1f,
                 ((uint)CONCAT11(local_f9,bStack_fa) << 0x17) >> 0x1b,
                 ((uint)bStack_fa << 0x1c) >> 0x1f,((uint)bStack_fa << 0x1d) >> 0x1e);
          printk("Pppoe_mask = 0x%x, L2_infor_mask = 0x%x, Tag_level_mask = 0x%x,Inport_mask = 0x%x\n"
                 ,bStack_fa & 1,local_fb >> 7,((uint)local_fb << 0x19) >> 0x1f,
                 ((uint)local_fb << 0x1a) >> 0x1f);
          printk("outport_mask = 0x%x, winmask19 = 0x%x, winmask18 = 0x%x,winmask17 = 0x%x\n",
                 ((uint)local_fb << 0x1b) >> 0x1f,
                 (CONCAT11(local_fb,uStack_fc) & 0xfff) << 4 | (uint)(bStack_fd >> 4),
                 (uint)(CONCAT13(bStack_fd,CONCAT12(uStack_fe,CONCAT11(uStack_ff,uStack_100))) << 4)
                 >> 0x10,(CONCAT11(uStack_ff,uStack_100) & 0xfff) << 4 | (uint)(local_101 >> 4));
          printk("winmask16 = 0x%x, winmask15 = 0x%x, winmask14 = 0x%x,winmask13 = 0x%x\n",
                 (uint)(CONCAT13(local_101,CONCAT12(uStack_102,CONCAT11(uStack_103,uStack_104))) <<
                       4) >> 0x10,
                 (CONCAT11(uStack_103,uStack_104) & 0xfff) << 4 | (uint)(bStack_105 >> 4),
                 (uint)(CONCAT13(bStack_105,CONCAT12(uStack_106,CONCAT11(uStack_107,bStack_108))) <<
                       4) >> 0x10,
                 (CONCAT11(uStack_107,bStack_108) & 0xfff) << 4 | (uint)(bStack_109 >> 4));
          printk("winmask12 = 0x%x, winmask11 = 0x%x, winmask10 = 0x%x,winmask9 = 0x%x\n",
                 (uint)(CONCAT13(bStack_109,CONCAT12(bStack_10a,CONCAT11(uStack_10b,local_10c))) <<
                       4) >> 0x10,
                 (CONCAT11(uStack_10b,local_10c) & 0xfff) << 4 | (uint)(bStack_10d >> 4),
                 (uint)(CONCAT13(bStack_10d,CONCAT12(bStack_10e,CONCAT11(uStack_10f,uStack_110))) <<
                       4) >> 0x10,
                 (CONCAT11(uStack_10f,uStack_110) & 0xfff) << 4 | (uint)(bStack_111 >> 4));
          printk("winmask8 = 0x%x, winmask7 = 0x%x, winmask6 = 0x%x, winmask5 = 0x%x\n",
                 (uint)(CONCAT13(bStack_111,CONCAT12(bStack_112,CONCAT11(uStack_113,local_114))) <<
                       4) >> 0x10,
                 (CONCAT11(uStack_113,local_114) & 0xfff) << 4 | (uint)(bStack_115 >> 4),
                 (uint)(CONCAT13(bStack_115,CONCAT12(bStack_116,CONCAT11(uStack_117,uStack_118))) <<
                       4) >> 0x10,
                 (CONCAT11(uStack_117,uStack_118) & 0xfff) << 4 | (uint)(bStack_119 >> 4));
          printk("winmask4 = 0x%x, winmask3 = 0x%x, winmask2 = 0x%x, winmask1 = 0x%x\n",
                 (uint)(CONCAT13(bStack_119,CONCAT12(bStack_11a,CONCAT11(uStack_11b,local_11c))) <<
                       4) >> 0x10,
                 (CONCAT11(uStack_11b,local_11c) & 0xfff) << 4 | (uint)(bStack_11d >> 4),
                 (uint)(CONCAT13(bStack_11d,CONCAT12(bStack_11e,CONCAT11(uStack_11f,uStack_120))) <<
                       4) >> 0x10,
                 (CONCAT11(uStack_11f,uStack_120) & 0xfff) << 4 | (uint)(bStack_121 >> 4));
          printk("winmask0 = 0x%x, winoffset19 = 0x%x, winoffset18 = 0x%x, winoffset17 = 0x%x\n",
                 (uint)(CONCAT13(bStack_121,CONCAT12(bStack_122,CONCAT11(uStack_123,local_124))) <<
                       4) >> 0x10,((uint)CONCAT11(uStack_123,local_124) << 0x14) >> 0x19,
                 (local_124 & 0x1f) << 2 | local_128._3_1_ >> 6,
                 ((local_128 >> 0x10) << 0x12) >> 0x19);
          printk("winoffset16 = 0x%x, winoffset15 = 0x%x, winoffset14 = 0x%x, winoffset13 = 0x%x\n",
                 local_128._2_1_ & 0x7f,local_128._1_1_ >> 1,(local_128 << 0x17) >> 0x19,
                 (local_128 & 3) << 5 | local_12c >> 0x1b);
          printk("winoffset12 = 0x%x, winoffset11 = 0x%x, winoffset10 = 0x%x, winoffset9 = 0x%x\n",
                 ((local_12c >> 0x10) << 0x15) >> 0x19,(local_12c << 0xc) >> 0x19,
                 (local_12c << 0x13) >> 0x19,(local_12c & 0x3f) << 1 | local_130 >> 0x1f);
          printk("winoffset8 = 0x%x, winoffset7 = 0x%x, winoffset6 = 0x%x, winoffset5 = 0x%x\n",
                 local_130._3_1_ & 0x7f,local_130._2_1_ >> 1,(local_130 << 0xf) >> 0x19,
                 (local_130 << 0x16) >> 0x19);
          printk("winoffset4 = 0x%x, winoffset3 = 0x%x, winoffset2 = 0x%x, winoffset1 = 0x%x, winoffset0 = 0x%x\n"
                 ,(local_130 & 7) << 4 | local_134 >> 0x1c,((local_134 >> 0x10) << 0x14) >> 0x19,
                 (local_134 << 0xb) >> 0x19,(local_134 << 0x12) >> 0x19,local_134 & 0x7f);
        }
        else {
          printk("get cla extra_rule_table fail, error code %d!\n");
        }
      }
      else {
        iVar2 = strcmp(__s1,"ghashtable");
        iVar1 = local_144;
        uVar6 = local_148;
        if (iVar2 == 0) {
          __memzero(&local_134,0x3c);
          if ((uVar6 & 0x10000) == 0) {
            iVar1 = cla_get_hash_table(uVar6,&local_134);
          }
          else {
            iVar1 = cla_get_external_hash_table(uVar6,iVar1,&local_134);
          }
          if (iVar1 == 0) {
            printk("CLA hash_table get: \n");
            printk("hashaddr = 0x%x, windata19 = 0x%x, windata18 = 0x%x, windata17 = 0x%x, windata16 = 0x%x\n"
                   ,uVar6,CONCAT11(bStack_fa,local_fb),CONCAT11(uStack_fc,bStack_fd),
                   CONCAT11(uStack_fe,uStack_ff),CONCAT11(uStack_100,local_101));
            printk("windata15 = 0x%x, windata14 = 0x%x, windata13 = 0x%x, windata12 = 0x%x, windata11 = 0x%x\n"
                   ,CONCAT11(uStack_102,uStack_103),CONCAT11(uStack_104,bStack_105),
                   CONCAT11(uStack_106,uStack_107),CONCAT11(bStack_108,bStack_109),
                   CONCAT11(bStack_10a,uStack_10b));
            printk("windata10 = 0x%x, windata9 = 0x%x, windata8 = 0x%x, windata7 = 0x%x, windata6 = 0x%x\n"
                   ,CONCAT11(local_10c,bStack_10d),CONCAT11(bStack_10e,uStack_10f),
                   CONCAT11(uStack_110,bStack_111),CONCAT11(bStack_112,uStack_113),
                   CONCAT11(local_114,bStack_115));
            printk("windata5 = 0x%x, windata4 = 0x%x, windata3 = 0x%x, windata2 = 0x%x, windata1 = 0x%x\n"
                   ,CONCAT11(bStack_116,uStack_117),CONCAT11(uStack_118,bStack_119),
                   CONCAT11(bStack_11a,uStack_11b),CONCAT11(local_11c,bStack_11d),
                   CONCAT11(bStack_11e,uStack_11f));
            uVar6 = (uint)bStack_122;
            printk("windata0 = 0x%x, Reserve = 0x%x, da_known = 0x%x, t-condId high = 0x%x, gemport_valid = 0x%x\n"
                   ,CONCAT11(uStack_120,bStack_121),bStack_122 >> 5,(uVar6 << 0x1b) >> 0x1f,
                   (uVar6 << 0x1c) >> 0x1f,(uVar6 << 0x1d) >> 0x1f);
            uVar6 = (uint)local_124;
            printk("flow_sta_info = 0x%x, valid = 0x%x, direction = 0x%x, rule_mode = 0x%x, extract_index = 0x%x\n"
                   ,(uint)(CONCAT13(bStack_121,CONCAT12(bStack_122,CONCAT11(uStack_123,local_124)))
                          << 0xe) >> 0x15,(uVar6 << 0x19) >> 0x1f,(uVar6 << 0x1a) >> 0x1f,
                   (uVar6 << 0x1b) >> 0x1f,(uVar6 & 0xf) << 4 | local_128 >> 0x1c);
            printk("pppoe_flag = 0x%x, l2_type = 0x%x, tag_level = 0x%x, inport= = 0x%x, outport = 0x%x\n"
                   ,((local_128 >> 0x18) << 0x1c) >> 0x1f,((local_128 >> 0x18) << 0x1d) >> 0x1e,
                   ((local_128 >> 0x10) << 0x17) >> 0x1d,(local_128 << 10) >> 0x14,
                   (local_128 << 0x16) >> 0x1b);
            printk("flow_pri = 0x%x, wan_id = 0x%x, qid_dscp_en = 0x%x qid_dscp_ram_index = 0x%x,qos_rp_flag = 0x%x, qos_id = 0x%x\n"
                   ,(local_128 & 0x1f) << 1 | (uint)(local_12c._3_1_ >> 7),
                   ((uint)local_12c._3_1_ << 0x19) >> 0x1b,((uint)local_12c._3_1_ << 0x1e) >> 0x1f,
                   ((local_12c >> 0x10) << 0x17) >> 0x1c,((local_12c >> 0x10) << 0x1b) >> 0x1f,
                   (local_12c << 0xc) >> 0x17);
            printk("adm_bucket_rp_en = 0x%x, bucket_info = 0x%x, mtu_rp_flag = 0x%x, mtu = 0x%x, cpu_qid_rg_flag = 0x%x\n"
                   ,((local_12c >> 8) << 0x1d) >> 0x1f,(local_12c << 0x16) >> 0x1a,
                   (local_12c << 0x1c) >> 0x1f,(local_12c & 7) << 0xb | local_130 >> 0x15,
                   ((local_130 >> 0x10) << 0x1b) >> 0x1f);
            uVar6 = (uint)local_130._1_1_;
            printk("cpu_qid = 0x%x,  cmd_flow_info_rp_flag = 0x%x, vlan_changed_flag = 0x%x, mod_en = 0x%x, pkt_len_changed = 0x%x, e8_en = %d\n"
                   ,((local_130 >> 0x10) << 0x1b) >> 0x1f,local_130 >> 0x10 & 1,local_130._1_1_ >> 7
                   ,(uVar6 << 0x19) >> 0x1f,(uVar6 << 0x1a) >> 0x1b,uVar6 & 1);
            printk("cmd_flow_id = 0x%x, tcnt_gpid_rp_en = 0x%x, gemport_uni_id = 0x%x, tcont_id = 0x%x\n"
                   ,(local_130 & 0xff) << 7 | (uint)(local_134._3_1_ >> 1),local_134._3_1_ & 1,
                   (local_134 << 8) >> 0x14,(local_134 << 0x14) >> 0x1b);
            uVar6 = local_134 & 0xff;
            printk("queue_info_rp_flag = 0x%x, queue_id = 0x%x, act_rp_flag = 0x%x, action = 0x%x\n"
                   ,(uVar6 << 0x19) >> 0x1f,(uVar6 << 0x1a) >> 0x1d,(uVar6 << 0x1d) >> 0x1f,
                   local_134 & 3);
          }
          else {
            printk("get cla hash_table fail, error code %d!\n");
          }
        }
        else {
          iVar2 = strcmp(__s1,"modhashtable");
          uVar5 = local_138;
          uVar7 = local_13c;
          uVar3 = local_140;
          iVar1 = local_144;
          uVar6 = local_148;
          if (iVar2 == 0) {
            __memzero(&local_134,0x3c);
            if ((uVar6 & 0x10000) == 0) {
              cla_get_hash_table(uVar6,&local_134);
              local_130._0_2_ =
                   CONCAT11(local_130._1_1_ & 0x81 | (byte)((uVar3 & 1) << 6) |
                            (byte)((uVar7 & 0x1f) << 1),(char)((uVar5 << 0x11) >> 0x18));
              local_134 = CONCAT13(local_134._3_1_ & 1 | (byte)((uVar5 & 0x7f) << 1),
                                   (undefined3)local_134);
              cla_set_hash_table(uVar6,&local_134);
            }
            else {
              cla_get_external_hash_table(uVar6,iVar1,&local_134);
              local_130._0_2_ =
                   CONCAT11(local_130._1_1_ & 0x81 | (byte)((uVar3 & 1) << 6) |
                            (byte)((uVar7 & 0x1f) << 1),(char)((uVar5 << 0x11) >> 0x18));
              local_134 = CONCAT13(local_134._3_1_ & 1 | (byte)((uVar5 & 0x7f) << 1),
                                   (undefined3)local_134);
              cla_set_external_hash_table(uVar6,iVar1,&local_134);
            }
          }
          else {
            iVar1 = strcmp(__s1,"setmaxl3entry");
            if (iVar1 == 0) {
              zte_api_sw_set_fast_max_entry(local_148,local_144,local_140,local_13c);
            }
            else {
              iVar1 = strcmp(__s1,"addfastrule");
              if (iVar1 == 0) {
                claDebugAddFastRule(param_3);
              }
              else {
                iVar1 = strcmp(__s1,"delfastrule");
                if (iVar1 == 0) {
                  claDebugDelFastRule(param_3);
                }
                else {
                  iVar1 = strcmp(__s1,"calculatehashaddr");
                  if (iVar1 == 0) {
                    sscanf(param_3,
                           "%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x"
                           ,local_f0,&local_ec,&local_e8,&local_e4,&local_e0,&local_dc,&local_d8,
                           local_d4,&local_d0,local_cc,&local_c8,local_c4,&local_c0,local_bc,
                           &local_b8,local_b4,&local_b0,local_ac,&local_a8,local_a4,&local_a0,
                           local_9c,&local_98,local_94,&local_90,local_8c,&local_88,local_84,
                           local_80);
                    iVar1 = (local_ec & 0xfff) << 5;
                    local_12c = (uint)(byte)((ushort)local_cc[0] >> 0xf);
                    local_130 = (uint)(local_d4[0] & 1);
                    iVar2 = (local_dc & 0xff) << 7;
                    local_12c = local_12c | (local_c8 & 0xffff) << 1;
                    local_134 = CONCAT22((ushort)(byte)((byte)((uint)iVar1 >> 0x10) |
                                                        (byte)((local_e8 & 7) << 1) |
                                                        (byte)((local_e4 & 3) << 4) |
                                                       (byte)((local_e0 & 1) << 6)) | (ushort)iVar2,
                                         (ushort)(local_f0[0] & 0x1f) | (ushort)iVar1);
                    local_130 = local_130 | (local_d0 & 0xffff) << 1;
                    local_128 = (uint)(byte)((ushort)local_c4[0] >> 0xf);
                    local_12c = CONCAT22((ushort)((local_12c << 0xf) >> 0x1f) | local_c4[0] << 1,
                                         (undefined2)local_12c);
                    local_134 = CONCAT13((byte)((uint)iVar2 >> 8) | (byte)((local_d8 & 1) << 7),
                                         (undefined3)local_134);
                    local_130 = CONCAT22((ushort)((local_130 << 0xf) >> 0x1f) | local_cc[0] << 1,
                                         (undefined2)local_130);
                    local_128 = local_128 | (local_c0 & 0xffff) << 1;
                    uVar6 = (local_b8 & 0xffff) << 1;
                    uVar5 = (byte)((ushort)local_bc[0] >> 0xf) | uVar6;
                    uVar3 = (local_b0 & 0xffff) << 1;
                    uVar10 = (byte)((ushort)local_b4[0] >> 0xf) | uVar3;
                    uVar7 = (local_a8 & 0xffff) << 1;
                    uVar9 = (byte)((ushort)local_ac[0] >> 0xf) | uVar7;
                    local_124 = (byte)uVar5;
                    uStack_123 = (undefined1)(uVar6 >> 8);
                    uVar6 = (local_a0 & 0xffff) << 1;
                    uVar8 = (byte)((ushort)local_a4[0] >> 0xf) | uVar6;
                    bStack_122 = (byte)((uVar5 << 0xf) >> 0x1f) | (byte)(local_b4[0] << 1);
                    bStack_11e = (byte)((uVar10 << 0xf) >> 0x1f) | (byte)(local_ac[0] << 1);
                    uStack_120 = (undefined1)uVar10;
                    uStack_11f = (undefined1)(uVar3 >> 8);
                    bStack_11d = (byte)((ushort)(local_ac[0] << 1) >> 8);
                    bStack_121 = (byte)((ushort)(local_b4[0] << 1) >> 8);
                    local_11c = (undefined1)uVar9;
                    uStack_11b = (undefined1)(uVar7 >> 8);
                    bStack_11a = (byte)((uVar9 << 0xf) >> 0x1f) | (byte)(local_a4[0] << 1);
                    uStack_118 = (undefined1)uVar8;
                    uStack_117 = (undefined1)(uVar6 >> 8);
                    local_128 = CONCAT22((ushort)((local_128 << 0xf) >> 0x1f) | local_bc[0] << 1,
                                         (undefined2)local_128);
                    bStack_116 = (byte)((uVar8 << 0xf) >> 0x1f) | (byte)(local_9c[0] << 1);
                    bStack_119 = (byte)((ushort)(local_a4[0] << 1) >> 8);
                    bStack_115 = (byte)((ushort)(local_9c[0] << 1) >> 8);
                    uVar6 = (local_90 & 0xffff) << 1;
                    uVar8 = (byte)((ushort)local_94[0] >> 0xf) | uVar6;
                    uVar3 = (local_98 & 0xffff) << 1;
                    uVar5 = (byte)((ushort)local_9c[0] >> 0xf) | uVar3;
                    uVar7 = (local_88 & 0xffff) << 1;
                    uVar9 = (byte)((ushort)local_8c[0] >> 0xf) | uVar7;
                    local_114 = (undefined1)uVar5;
                    uStack_113 = (undefined1)(uVar3 >> 8);
                    bStack_112 = (byte)((uVar5 << 0xf) >> 0x1f) | (byte)(local_94[0] << 1);
                    bStack_10e = (byte)((uVar8 << 0xf) >> 0x1f) | (byte)(local_8c[0] << 1);
                    uStack_110 = (undefined1)uVar8;
                    uStack_10f = (undefined1)(uVar6 >> 8);
                    bStack_10a = (byte)((uVar9 << 0xf) >> 0x1f) | (byte)(local_84[0] << 1);
                    bStack_10d = (byte)((ushort)(local_8c[0] << 1) >> 8);
                    bStack_108 = bStack_108 & 0xfe | (byte)((ushort)local_84[0] >> 0xf);
                    local_10c = (undefined1)uVar9;
                    uStack_10b = (undefined1)(uVar7 >> 8);
                    bStack_111 = (byte)((ushort)(local_94[0] << 1) >> 8);
                    bStack_109 = (byte)((ushort)(local_84[0] << 1) >> 8);
                    fpga_write_reg(0xe30b0,local_80[0]);
                    iVar1 = 0;
                    do {
                      iVar2 = iVar1 + 1;
                      fpga_write_reg(iVar1 + 0xe30b1,(&local_134)[iVar1]);
                      iVar1 = iVar2;
                    } while (iVar2 != 0xc);
                    uVar4 = fpga_read_reg(0xe30bf);
                    printk("calculate hash addr is :0x%x\n",uVar4);
                  }
                  else {
                    uVar3 = strcmp(__s1,"gagingstatus");
                    uVar6 = local_148;
                    if (uVar3 == 0) {
                      uVar7 = local_148;
                      if ((local_148 & 0x10000) != 0) {
                        uVar7 = (local_148 & 0xffff) + 0x400;
                      }
                      local_134 = uVar3;
                      cla_get_acl_aging_table(uVar7,&local_134);
                      printk("hashAddr:0x%x,agingTableAddr:0x%x,old status:%d\n",uVar6,uVar7,
                             local_134);
                      cla_set_acl_aging_table(uVar7,0);
                      cla_get_acl_aging_table(uVar7,&local_134);
                      printk("hashAddr:0x%x,agingTableAddr:0x%x,new status:%d\n",uVar6,uVar7,
                             local_134);
                    }
                    else {
                      iVar2 = strcmp(__s1,"setmaxfastentry");
                      uVar3 = local_140;
                      iVar1 = local_144;
                      uVar6 = local_148;
                      if (iVar2 == 0) {
                        printk("[tmtst] change fast rule max number: enable %d, up :%d, down :%d\n",
                               local_148,local_140,local_144);
                        if (uVar3 + iVar1 < 0x3e81) {
                          if (uVar6 == 0) {
                            uVar4 = 2;
                            UP_MAX_FAST_ENTRY = 0xff0;
                            DN_MAX_FAST_ENTRY = 0xff0;
                          }
                          else {
                            if (uVar6 != 1) goto LAB_00073adc;
                            uVar4 = 0;
                            DN_MAX_FAST_ENTRY = uVar3;
                            UP_MAX_FAST_ENTRY = iVar1;
                          }
                          g_flowTest = uVar6;
                          cla_set_outspace_cfg(uVar4,0);
                          cla_get_outspace_cfg(&ACL_OUT_HASH_NUM,&ACL_OUT_SPACE_SEL);
                        }
                        else {
                          printk("[tmtst]fast acl num max <=16000\n");
                        }
                      }
                      else {
                        printk("%s: illegal operation <%s>\n","cla_info_store",*param_2);
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
LAB_00073adc:
  printk("len:%d\n",param_4);
  return param_4;
}

