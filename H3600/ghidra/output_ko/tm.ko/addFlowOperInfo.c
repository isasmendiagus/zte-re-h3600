// module: tm.ko
// function: addFlowOperInfo @ 0x5b30c
// size: 2224 bytes
//

undefined4 addFlowOperInfo(uint *param_1,undefined4 param_2,undefined4 *param_3)

{
  int *piVar1;
  ushort uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined1 *puVar8;
  uint uVar9;
  undefined1 auStack_b6 [2];
  undefined4 local_b4;
  byte local_af [5];
  undefined1 auStack_aa [6];
  undefined1 auStack_a4 [2];
  char local_a2;
  undefined1 local_a1;
  undefined2 local_a0;
  char local_9e;
  undefined1 local_9d;
  undefined2 local_9c;
  undefined1 auStack_9a [2];
  undefined4 local_98;
  uint local_94;
  undefined2 local_90;
  undefined2 local_88;
  short local_86;
  short local_84;
  undefined1 local_82;
  undefined1 local_81;
  undefined1 local_80;
  undefined1 local_7f;
  undefined1 local_7e;
  undefined1 local_7d;
  undefined1 local_7c;
  undefined1 local_7b;
  undefined1 local_7a;
  char local_79;
  undefined1 local_78;
  undefined2 local_76;
  undefined1 local_74;
  undefined1 local_73;
  undefined1 auStack_6c [5];
  undefined1 local_67;
  undefined1 local_66;
  undefined1 local_65;
  undefined1 local_63;
  undefined1 local_60;
  undefined1 local_5f;
  uint local_5c;
  undefined2 local_58;
  undefined1 local_54;
  ushort local_52;
  byte local_50;
  byte local_4f;
  undefined2 local_4e;
  undefined1 auStack_48 [12];
  int local_3c;
  uint local_38;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 local_30;
  undefined2 local_2e;
  byte local_2c;
  byte local_2b;
  undefined1 local_2a;
  undefined1 local_29;
  undefined1 local_28;
  undefined1 local_27;
  undefined1 local_26;
  
  local_b4 = 0;
  if (param_1 == (uint *)0x0) {
    printk("pp_flowOperInfo is NULL\n");
    return 0xfffffff4;
  }
  __memzero(auStack_48,0x28);
  __memzero(auStack_6c,0x24);
  __memzero(auStack_9a,0x12);
  __memzero(auStack_b6,2);
  __memzero(auStack_a4,10);
  __memzero(&local_88,0x1c);
  __memzero(local_af,5);
  uVar9 = *param_1;
  local_32 = 0;
  local_31 = 0;
  local_52 = 0;
  local_54 = 0;
  local_30 = 0;
  local_50 = 0;
  local_4f = 0;
  local_5c = 0;
  local_5f = 0;
  local_af[1] = 0;
  local_af[0] = 0;
  local_af[3] = 0;
  local_af[2] = '\0';
  local_2e = 0xffff;
  local_4e = 0xffff;
  local_58 = 0xffff;
  local_28 = 1;
  local_27 = 1;
  if (uVar9 == 0) {
    if ((gs_upDefFlowInit != 0) && (gs_downDefFlowInit != 0)) {
      *param_3 = 0;
      return 0;
    }
    if (g_flowTest != 1) goto LAB_0005b410;
LAB_0005b9d8:
    puVar8 = index;
    iVar5 = 0;
    do {
      piVar1 = (int *)(puVar8 + 8);
      puVar8 = puVar8 + 0x10;
      if ((*piVar1 == 1) && (*(uint *)(index + iVar5 * 0x10) == uVar9)) {
        *param_3 = *(undefined4 *)(index + iVar5 * 0x10 + 4);
        g_pktLenChged = *(undefined4 *)(index + iVar5 * 0x10 + 0xc);
        return 0;
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 != 10);
  }
  else if (g_flowTest == 1) goto LAB_0005b9d8;
  local_32 = (uVar9 & 1) != 0;
  if ((bool)local_32) {
    local_94 = param_1[1];
    local_90 = (undefined2)param_1[2];
  }
  if ((uVar9 & 2) != 0) {
    iVar5 = 0;
    local_31 = 1;
    while( true ) {
      pp_pm_get_onu_mac_ram_info(iVar5,auStack_aa);
      iVar6 = memcmp(param_1 + 4,auStack_aa,6);
      local_3c = iVar5;
      if (iVar6 == 0) break;
      iVar5 = iVar5 + 1;
      if (iVar5 == 0x10) {
        printk("invalid source mac addr %s\n",param_1 + 4);
        return 0xfffffff4;
      }
    }
  }
LAB_0005b410:
  if ((uVar9 & 8) != 0) {
    local_88 = (undefined2)param_1[7];
  }
  if ((uVar9 & 0x10) != 0) {
    local_74 = (undefined1)param_1[8];
  }
  if ((uVar9 & 0x40) != 0) {
    local_73 = *(undefined1 *)((int)param_1 + 0x21);
  }
  if ((uVar9 & 4) != 0) {
    local_9d = (undefined1)param_1[0x16];
    local_9c = *(undefined2 *)((int)param_1 + 0x56);
    local_5c = param_1[0x14];
    uVar2 = *(ushort *)((int)param_1 + 0x5a);
    local_79 = *(char *)((int)param_1 + 0x59);
    local_84 = (short)param_1[0x15];
    local_a1 = (undefined1)param_1[0x18];
    local_af[2] = *(char *)((int)param_1 + 0x61);
    local_a0 = *(undefined2 *)((int)param_1 + 0x5e);
    local_86 = (short)param_1[0x17];
    local_60 = 1;
    local_9e = local_79;
    if (((uVar2 & 0xe000) != 0) && (local_7c = 1, local_79 == '\b')) {
      local_82 = 1;
      local_9e = '\0';
    }
    if ((uVar2 & 0x1000) != 0) {
      local_7b = 1;
    }
    if ((uVar2 & 0xfff) != 0) {
      local_7d = 1;
    }
    uVar2 = *(ushort *)((int)param_1 + 0x62);
    local_a2 = local_af[2];
    if ((uVar2 & 0xe000) != 0) {
      local_80 = 1;
      local_af[3] = 1;
      if (local_af[2] == '\b') {
        local_82 = 1;
        local_a2 = '\0';
      }
    }
    if ((uVar2 & 0x1000) != 0) {
      local_7f = 1;
    }
    if ((uVar2 & 0xfff) != 0) {
      local_81 = 1;
    }
    if (local_84 != 0) {
      local_7a = 1;
    }
    local_78 = local_9d;
    local_76 = local_9c;
    if (local_86 != 0) {
      local_7e = 1;
    }
  }
  if ((uVar9 & 0x20) != 0) {
    local_af[0] = *(byte *)((int)param_1 + 0x22);
    local_54 = 1;
    local_af[1] = 1;
    local_52 = (ushort)local_af[0];
  }
  if (((uVar9 & 0x100) != 0) && (local_2a = 1, *(int *)(g_onu_sip + local_3c * 4) != zte_onu_sip)) {
    iVar5 = pon_pp_set_6rd_sip(local_3c,&zte_onu_sip);
    if (iVar5 != 0) {
      printk("pon_pp_set_6rd_sip fail\n");
      return 0xfffffff4;
    }
    *(int *)(g_onu_sip + local_3c * 4) = zte_onu_sip;
  }
  if ((uVar9 & 0x80) != 0) {
    local_98 = *(undefined4 *)((int)param_1 + 0x23);
    local_29 = 1;
  }
  if ((uVar9 & 0x8000) != 0) {
    local_38 = local_38 | param_1[0x13] << 0x10;
    local_2b = local_2b | 2;
  }
  if ((uVar9 & 0x4000) != 0) {
    local_2b = local_2b | 1;
    local_38 = local_38 | param_1[0x12];
  }
  if ((uVar9 & 0x80000) != 0) {
    local_2c = local_2c | 1;
  }
  if ((uVar9 & 0x400000) != 0) {
    local_2c = local_2c | 1;
  }
  local_26 = 0;
  local_63 = 0;
  if ((uVar9 & 0x800000) != 0) {
    local_af[0] = (byte)param_1[8];
    local_af[1] = 1;
    local_50 = local_50 | 2;
    local_4f = local_af[0];
  }
  if ((uVar9 & 0x20000) != 0) {
    local_88 = (undefined2)param_1[7];
    local_65 = 1;
    if (*(int *)(g_session_id + local_3c * 4) != zte_session_id) {
      iVar5 = pp_pm_set_pppoe_session_id_ram_info();
      if (iVar5 != 0) {
        printk("pp_pm_set_pppoe_session_id_ram_info fail\n");
        return 0xfffffff4;
      }
      *(int *)(g_session_id + local_3c * 4) = zte_session_id;
    }
  }
  if ((uVar9 & 0x10000) != 0) {
    local_88 = (undefined2)param_1[7];
    local_65 = 1;
  }
  if ((uVar9 & 0x1000000) != 0) {
    local_88 = (undefined2)param_1[7];
    iVar5 = local_3c * 4;
    local_67 = 1;
    if ((*(int *)(g_dslite_tc + iVar5) != zte_dslite_tc) ||
       (*(int *)(g_dslite_hl + iVar5) != zte_dslite_hl)) {
      iVar5 = pon_pp_set_dslite_traffclass_hoplimit(local_3c,zte_dslite_tc,zte_dslite_hl);
      iVar6 = zte_dslite_hl;
      if (iVar5 != 0) {
        printk("pon_pp_set_dslite_traffclass_hoplimit fail\n");
        return 0xfffffff4;
      }
      iVar5 = local_3c * 4;
      *(int *)(g_dslite_tc + iVar5) = zte_dslite_tc;
      *(int *)(g_dslite_hl + iVar5) = iVar6;
    }
    if (*(int *)(g_dslite_fl + iVar5) != zte_dslite_fl) {
      iVar5 = pon_pp_set_dslite_flow_lable();
      if (iVar5 != 0) {
        printk("pon_pp_set_dslite_flow_lable fail\n");
        return 0xfffffff4;
      }
      *(int *)(g_dslite_fl + local_3c * 4) = zte_dslite_fl;
    }
    iVar5 = local_3c * 0x10;
    if ((((*(int *)(g_onu_sipv6 + iVar5) != zte_onu_sipv6._0_4_) ||
         (*(int *)(g_onu_sipv6 + iVar5 + 4) != zte_onu_sipv6._4_4_)) ||
        (*(int *)(g_onu_sipv6 + iVar5 + 8) != zte_onu_sipv6._8_4_)) ||
       (*(int *)(g_onu_sipv6 + iVar5 + 0xc) != zte_onu_sipv6._12_4_)) {
      iVar5 = pp_pm_set_b4_ipv6_ram_info(local_3c,zte_onu_sipv6);
      uVar4 = zte_onu_sipv6._12_4_;
      uVar3 = zte_onu_sipv6._8_4_;
      uVar7 = zte_onu_sipv6._4_4_;
      if (iVar5 != 0) {
        printk("pp_pm_set_b4_ipv6_ram_info fail\n");
        return 0xfffffff4;
      }
      iVar5 = local_3c * 0x10;
      *(undefined4 *)(g_onu_sipv6 + iVar5) = zte_onu_sipv6._0_4_;
      *(undefined4 *)(g_onu_sipv6 + iVar5 + 4) = uVar7;
      *(undefined4 *)(g_onu_sipv6 + iVar5 + 8) = uVar3;
      *(undefined4 *)(g_onu_sipv6 + iVar5 + 0xc) = uVar4;
    }
    if (((*(int *)(g_onu_dipv6 + iVar5) != zte_onu_dipv6._0_4_) ||
        (*(int *)(g_onu_dipv6 + iVar5 + 4) != zte_onu_dipv6._4_4_)) ||
       ((*(int *)(g_onu_dipv6 + iVar5 + 8) != zte_onu_dipv6._8_4_ ||
        (*(int *)(g_onu_dipv6 + iVar5 + 0xc) != zte_onu_dipv6._12_4_)))) {
      iVar5 = pp_pm_set_aftr_ipv6_ram_info(local_3c,zte_onu_dipv6);
      uVar4 = zte_onu_dipv6._12_4_;
      uVar3 = zte_onu_dipv6._8_4_;
      uVar7 = zte_onu_dipv6._4_4_;
      if (iVar5 != 0) {
        printk("pp_pm_get_b4_ipv6_ram_info fail\n");
        return 0xfffffff4;
      }
      iVar5 = local_3c * 0x10;
      *(undefined4 *)(g_onu_dipv6 + iVar5) = zte_onu_dipv6._0_4_;
      *(undefined4 *)(g_onu_dipv6 + iVar5 + 4) = uVar7;
      *(undefined4 *)(g_onu_dipv6 + iVar5 + 8) = uVar3;
      *(undefined4 *)(g_onu_dipv6 + iVar5 + 0xc) = uVar4;
    }
    switch(local_3c) {
    case 0:
      g_dslite_sel = 0;
      break;
    case 1:
      g_dslite_sel = 0x1249;
      break;
    case 2:
      g_dslite_sel = 0x2492;
      break;
    case 3:
      g_dslite_sel = 0x36db;
      break;
    case 4:
      g_dslite_sel = 0x4924;
      break;
    case 5:
      g_dslite_sel = 0x5b6d;
      break;
    case 6:
      g_dslite_sel = 0x6db6;
      break;
    default:
      g_dslite_sel = 0x7fff;
    }
  }
  if ((uVar9 & 0x2000000) != 0) {
    local_88 = (undefined2)param_1[7];
    local_67 = 1;
  }
  if ((uVar9 & 0xc000000) != 0) {
    local_88 = (undefined2)param_1[7];
    local_66 = 1;
  }
  iVar5 = operInfoAdd(auStack_48,auStack_6c,auStack_a4,auStack_9a,auStack_b6,&local_88,local_af,
                      param_2,uVar9,&local_b4);
  if (iVar5 == 0) {
    *param_3 = local_b4;
    uVar3 = g_pktLenChged;
    uVar7 = 0;
    if (g_flowTest == 1) {
      puVar8 = index;
      iVar5 = 0;
      while (piVar1 = (int *)(puVar8 + 8), puVar8 = puVar8 + 0x10, *piVar1 != 0) {
        iVar5 = iVar5 + 1;
        if (iVar5 == 10) {
          printk("index exceed max num\n");
          return 0;
        }
      }
      iVar5 = iVar5 * 0x10;
      *(uint *)(index + iVar5) = uVar9;
      *(undefined4 *)(index + iVar5 + 4) = local_b4;
      *(undefined4 *)(index + iVar5 + 8) = 1;
      *(undefined4 *)(index + iVar5 + 0xc) = uVar3;
      uVar7 = 0;
    }
  }
  else {
    iVar5 = __printk_ratelimit("addFlowOperInfo");
    if (iVar5 == 0) {
      uVar7 = 0xfffffff4;
    }
    else {
      printk("operInfoAdd fail\n");
      uVar7 = 0xfffffff4;
    }
  }
  return uVar7;
}

