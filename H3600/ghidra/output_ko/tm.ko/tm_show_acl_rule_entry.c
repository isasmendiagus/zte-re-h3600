// module: tm.ko
// function: tm_show_acl_rule_entry @ 0x5f554
// size: 2348 bytes
//

undefined4 tm_show_acl_rule_entry(int param_1,undefined4 param_2)

{
  char *pcVar1;
  uint uVar2;
  undefined1 *puVar3;
  char **ppcVar4;
  undefined1 *puVar5;
  int iVar6;
  uint uVar7;
  char **ppcVar8;
  uint uVar9;
  uint uVar10;
  char **ppcVar11;
  undefined4 local_174;
  undefined1 auStack_170 [2];
  byte local_16e;
  undefined2 local_16c;
  undefined2 local_16a;
  char *apcStack_168 [2];
  undefined1 local_15e;
  byte local_15d;
  undefined2 local_15c;
  byte local_15a;
  undefined1 local_156;
  undefined1 local_155;
  undefined1 local_154;
  byte local_153;
  byte local_152;
  byte local_151;
  undefined1 local_150;
  byte local_14f;
  byte local_14e;
  byte local_14d;
  char *apcStack_14c [3];
  uint local_140;
  byte local_13c;
  byte local_13b;
  undefined2 local_13a;
  byte local_138;
  char *apcStack_134 [7];
  byte local_118;
  byte local_111;
  uint local_110;
  byte local_10c;
  undefined2 local_109;
  undefined2 local_107;
  undefined2 local_105;
  undefined2 local_103;
  undefined2 local_101;
  undefined2 local_ff;
  undefined2 local_fd;
  undefined2 local_fb;
  undefined2 local_f9;
  undefined2 local_f7;
  undefined1 local_f5 [2];
  undefined2 local_f3;
  undefined2 local_f1;
  undefined2 local_ef;
  undefined2 local_ed;
  undefined2 local_eb;
  undefined2 local_e9;
  undefined2 local_e7;
  undefined2 local_e5;
  undefined2 local_e3;
  uint local_e0;
  undefined4 local_dc;
  uint local_d8;
  undefined2 local_d4;
  undefined2 local_d2;
  uint local_d0;
  uint local_cc;
  uint local_c8;
  uint local_c4;
  uint local_c0;
  uint local_bc;
  uint local_b8;
  uint local_b4;
  uint local_b0;
  uint local_ac;
  undefined2 local_a8;
  undefined2 local_a6;
  undefined4 local_a4;
  undefined2 local_a0;
  undefined2 local_9e;
  undefined4 auStack_9c [29];
  undefined1 auStack_28 [4];
  
  apcStack_168[0] = "Upstream";
  apcStack_168[1] = "DownStream";
  apcStack_134[0] = "Untagged";
  apcStack_134[1] = "Priority Tagged";
  apcStack_134[2] = "Single Tagged";
  apcStack_134[3] = "Double Tagged";
  apcStack_134[4] = "Three Tagged";
  apcStack_134[5] = "Four Tagged";
  apcStack_14c[0] = "Forward";
  apcStack_14c[1] = &DAT_000a51fc;
  apcStack_14c[2] = &DAT_000a5204;
  __memzero(apcStack_134 + 6,0x3c);
  __memzero(&local_e0,0x44);
  cla_get_extra_rule_table(*(undefined1 *)(param_1 + 0xc),&local_e0);
  uVar7 = *(uint *)(param_1 + 8);
  if ((uVar7 & 0x10000) == 0) {
    cla_get_hash_table(uVar7 & 0x7fff,apcStack_134 + 6);
    uVar7 = *(uint *)(param_1 + 8);
  }
  else {
    puVar5 = (undefined1 *)((uVar7 & 0xffff) * 0x40 + -0xefe0001);
    ppcVar11 = apcStack_134 + 6;
    do {
      ppcVar8 = ppcVar11 + 2;
      puVar3 = puVar5;
      ppcVar4 = ppcVar8;
      do {
        puVar3 = puVar3 + 1;
        ppcVar4 = (char **)((int)ppcVar4 + -1);
        *(undefined1 *)ppcVar4 = *puVar3;
      } while (ppcVar11 != ppcVar4);
      puVar5 = puVar5 + 8;
      ppcVar11 = ppcVar8;
    } while (ppcVar8 != (char **)(local_f5 + 1));
  }
  printk("Index:%d,Dir:%s,Flow_Pri:0x%x,HashAddr:%d(0x%x)\n",param_2,
         apcStack_168[-((int)((uint)local_10c << 0x1a) >> 0x1f)],
         (local_110 & 0x1f) << 1 | (uint)(local_111 >> 7),uVar7,uVar7);
  printk("MatchInfo:\n");
  uVar9 = (uint)local_a8._1_1_;
  uVar7 = ((local_110 >> 0x10) << 0x17) >> 0x1d;
  printk("\t externed_Mask:0x%x,Dslite_v6rd_Mask:0x%x,hash_len %d, rule_mode %d(0x%x)\n\t L2_info:%d(Mask:0x%x), PPPoe:%d(Mask:0x%x), %s(%d,Mask:0x%x), Inport:%d(Mask:0x%x), Outport:%d(Mask:0x%x)\n"
         ,((uint)local_a6._1_1_ << 0x1b) >> 0x1f,((uint)local_a6._1_1_ << 0x1c) >> 0x1f,
         ((uint)local_a6 << 0x17) >> 0x1b,((uint)local_10c << 0x1b) >> 0x1f,
         ((uint)(byte)local_a6 << 0x1c) >> 0x1f,((local_110 >> 0x18) << 0x1d) >> 0x1e,
         local_a8._1_1_ >> 7,((local_110 >> 0x18) << 0x1c) >> 0x1f,(byte)local_a6 & 1,
         apcStack_134[uVar7],uVar7,(uVar9 << 0x19) >> 0x1f,(local_110 << 10) >> 0x14,
         (uVar9 << 0x1a) >> 0x1f,(local_110 << 0x16) >> 0x1b,(uVar9 << 0x1b) >> 0x1f);
  printk("\tDATA :%04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x\n"
         ,local_109,local_107,local_105,local_103,local_101,local_ff,local_fd,local_fb,local_f9,
         local_f7,local_f5,local_f3,local_f1,local_ef,local_ed,local_eb,local_e9,local_e7,local_e5,
         local_e3);
  printk("\tMASK :%04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x\n"
         ,(local_d0 << 4) >> 0x10,(local_cc & 0xfff) << 4 | local_d0 >> 0x1c,(local_cc << 4) >> 0x10
         ,(local_c8 & 0xfff) << 4 | local_cc >> 0x1c,(local_c8 << 4) >> 0x10,
         (local_c4 & 0xfff) << 4 | local_c8 >> 0x1c,(local_c4 << 4) >> 0x10,
         (local_c0 & 0xfff) << 4 | local_c4 >> 0x1c,(local_c0 << 4) >> 0x10,
         (local_bc & 0xfff) << 4 | local_c0 >> 0x1c,(local_bc << 4) >> 0x10,
         (local_b8 & 0xfff) << 4 | local_bc >> 0x1c,(local_b8 << 4) >> 0x10,
         (local_b4 & 0xfff) << 4 | local_b8 >> 0x1c,(local_b4 << 4) >> 0x10,
         (local_b0 & 0xfff) << 4 | local_b4 >> 0x1c,(local_b0 << 4) >> 0x10,
         (local_ac & 0xfff) << 4 | local_b0 >> 0x1c,(local_ac << 4) >> 0x10,
         (local_a8 & 0xfff) << 4 | local_ac >> 0x1c);
  printk("\tSHIFT:%04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x\n"
         ,local_e0 & 0x7f,(local_e0 << 0x12) >> 0x19,(local_e0 << 0xb) >> 0x19,
         ((local_e0 >> 0x10) << 0x14) >> 0x19,(local_dc & 7) << 4 | local_e0 >> 0x1c,
         (local_dc << 0x16) >> 0x19,(local_dc << 0xf) >> 0x19,local_dc >> 0x11 & 0x7f,
         local_dc._3_1_ & 0x7f,(local_d8 & 0x3f) << 1 | (uint)(local_dc._3_1_ >> 7),
         (local_d8 << 0x13) >> 0x19,(local_d8 << 0xc) >> 0x19,((local_d8 >> 0x10) << 0x15) >> 0x19,
         ((byte)local_d4 & 3) << 5 | local_d8 >> 0x1b,((uint)local_d4 << 0x17) >> 0x19,
         local_d4._1_1_ >> 1,(byte)local_d2 & 0x7f,((uint)local_d2 << 0x12) >> 0x19,
         (local_d0 & 0x1f) << 2 | (uint)(local_d2._1_1_ >> 6),(local_d0 << 0x14) >> 0x19);
  uVar10 = (uint)(byte)local_a0;
  uVar9 = local_a4 >> 8 & 0xff;
  uVar7 = (local_a4 << 0xe) >> 0x1d;
  printk("\tTYPE :%04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x %04x\n"
         ,local_a4 & 7,(local_a4 << 0x1a) >> 0x1d,(local_a4 << 0x17) >> 0x1d,(uVar9 << 0x1c) >> 0x1d
         ,(uVar9 << 0x19) >> 0x1d,uVar7,((uint)local_a4._2_1_ << 0x1b) >> 0x1d,local_a4._2_1_ >> 5,
         local_a4._3_1_ & 7,((uint)local_a4._3_1_ << 0x1a) >> 0x1d,
         (uVar10 & 1) << 2 | (uint)(local_a4._3_1_ >> 6),(uVar10 << 0x1c) >> 0x1d,
         (uVar10 << 0x19) >> 0x1d,((uint)local_a0 << 0x16) >> 0x1d,
         ((uint)local_a0._1_1_ << 0x1b) >> 0x1d,local_a0._1_1_ >> 5,(byte)local_9e & 7,
         ((uint)(byte)local_9e << 0x1a) >> 0x1d,((uint)local_9e << 0x17) >> 0x1d,
         ((uint)local_9e._1_1_ << 0x1c) >> 0x1d);
  uVar9 = (uint)((int)apcStack_134[6] << 8) >> 0x14;
  uVar10 = uVar9;
  printk("ForwardInfo:\n\t%s, tcont:%d, queue:%d, gemport_uni:0x%x(%d)\n",
         apcStack_14c[(uint)apcStack_134[6] & 3],(uint)((int)apcStack_134[6] << 0x14) >> 0x1b,
         (uint)((int)apcStack_134[6] << 0x1a) >> 0x1d,uVar9,uVar9);
  uVar2 = (uint)local_118 << 7 | (uint)apcStack_134[6] >> 0x19;
  if (uVar2 < 0x400) {
    pp_pm_get_flow_info();
  }
  else {
    pp_pm_get_external_flow_info(((uint)local_10c << 0x1a) >> 0x1f,uVar2,&local_140);
  }
  pp_pm_get_next_hop_ram_info(((uint)local_13a << 0x15) >> 0x17,&local_156);
  pp_pm_get_sub_ram_info((local_138 & 0x1f) << 5 | (uint)(local_13a._1_1_ >> 3),&local_15e);
  printk("ActionInfo:");
  if ((local_140 & 1) != 0) {
    uVar9 = (uint)local_153;
    uVar10 = (uint)local_152;
    uVar7 = (uint)local_151;
    printk("\n\tDMAC:%x:%x:%x:%x:%x:%x",local_156,local_155,local_154,uVar9,uVar10,uVar7);
  }
  if (((byte)local_140 & 2) != 0) {
    printk("\n\tSMAC_EN:1");
  }
  if ((local_13c & 0x20) != 0) {
    uVar9 = (uint)local_14f;
    uVar10 = (uint)local_14e;
    uVar7 = (uint)local_14d;
    printk("\n\tNAT_DPORT:%d, SUBNET_ID:%d, NEXT_IP:%d.%d.%d.%d",(local_140 << 0xe) >> 0x10,
           ((uint)local_13b << 0x1b) >> 0x1c,local_150,uVar9,uVar10,uVar7);
  }
  if ((local_15d & 1) != 0) {
    printk("\n\tDSCP_TC:%d",local_15e);
  }
  if ((local_15d & 2) != 0) {
    printk("\n\tDEI_EN:1");
  }
  if ((local_15d & 4) != 0) {
    printk("\n\tDSLITE:1");
  }
  if ((local_15d & 8) != 0) {
    printk("\n\tPPPOE:1\t");
  }
  local_174 = 0;
  pp_pm_get_pppoe_session_id_ram_info(((uint)local_13b << 0x1b) >> 0x1c,&local_174);
  printk("subnet_id:%x,pppoe_session_id:0x%x\n",((uint)local_13b << 0x1b) >> 0x1c,local_174);
  if ((local_15d & 0x10) != 0) {
    printk("\n\t6RD:1");
  }
  iVar6 = 0;
  printk(&_LC198);
  memcpy(auStack_9c,&PTR_s_NULL_0007adbc,0x74);
  pp_pm_get_vlan_modify_ram_info((local_15a & 0xf) << 6 | (uint)(local_15c._1_1_ >> 2),&local_16c);
  do {
    pp_pm_get_cmd_ram_info(iVar6 + ((local_15c & 0x3ff) << 3 | (uint)(local_15d >> 5)),auStack_170);
    uVar2 = local_16e & 0x1f;
    if (uVar2 == 1) break;
    switch(uVar2) {
    case 2:
      goto switchD_0005fcc0_caseD_2;
    default:
      printk("\t%s:(0x%04x)\n",auStack_9c[uVar2],uVar2,auStack_28 + uVar2 * 4,uVar9,uVar10,uVar7);
      break;
    case 6:
      pcVar1 = "\tADD VLAN:";
      goto LAB_0005fcf0;
    case 7:
      pcVar1 = "\tREP VLAN";
LAB_0005fcf0:
      printk(pcVar1);
      uVar10 = ((uint)local_16a._1_1_ << 0x1b) >> 0x1f;
      uVar7 = (uint)(local_16a._1_1_ >> 5);
      uVar9 = local_16a & 0xfff;
      printk("cvid %d, ccfi %d, cpri %d, svid %d, scfi %d, spri %d\n",local_16c & 0xfff,
             ((uint)local_16c._1_1_ << 0x1b) >> 0x1f,local_16c._1_1_ >> 5,uVar9,uVar10,uVar7);
switchD_0005fcc0_caseD_2:
      break;
    case 9:
      printk("\tDEL VLAN\n");
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 != 8);
  printk(&_LC200);
  return 0;
}

