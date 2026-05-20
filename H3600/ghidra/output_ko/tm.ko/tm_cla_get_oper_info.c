// module: tm.ko
// function: tm_cla_get_oper_info @ 0x694ac
// size: 6036 bytes
//

undefined4 tm_cla_get_oper_info(int param_1,uint *param_2,int param_3)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  ushort uVar7;
  uint3 uVar8;
  uint3 uVar9;
  uint uVar10;
  int iVar11;
  char *pcVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  uint uVar16;
  undefined1 *puVar17;
  undefined1 *puVar18;
  
  if (param_1 == 0) {
    if (g_tm_debug_level != 0) {
      printk("[%s] input ERROR: flow_config=NULL\n","zte_sw_api.c");
      return 0xffffffff;
    }
  }
  else if (param_2 == (uint *)0x0) {
    if (g_tm_debug_level != 0) {
      printk("[%s] input ERROR: flow_oper_info=NULL\n","zte_sw_api.c");
      return 0xffffffff;
    }
  }
  else if (param_3 == 0) {
    if (g_tm_debug_level != 0) {
      printk("[%s] input ERROR: cla_parse_info=NULL\n","zte_sw_api.c");
      return 0xffffffff;
    }
  }
  else {
    if (*(byte *)(param_1 + 600) < 0x11) {
      if (*(byte *)(param_1 + 600) != 0) {
        iVar14 = 0;
        iVar13 = param_1;
        do {
          switch(*(undefined4 *)(iVar13 + 0x25c)) {
          case 0:
            puVar18 = (undefined1 *)(iVar13 + 0x269);
            uVar15 = *param_2 | 1;
            puVar17 = (undefined1 *)((int)param_2 + 3);
            *param_2 = uVar15;
            do {
              puVar18 = puVar18 + 1;
              puVar17 = puVar17 + 1;
              *puVar17 = *puVar18;
            } while (puVar18 != (undefined1 *)(iVar13 + 0x26f));
            if (1 < g_tm_debug_level) {
              uVar1 = (undefined1)param_2[1];
              uVar2 = *(undefined1 *)((int)param_2 + 5);
              pcVar12 = "SW_ACL_ACT_SET_DMAC=%02x:%02x:%02x:%02x:%02x:%02x operMsk=0x%x\n";
              uVar3 = *(undefined1 *)((int)param_2 + 6);
              uVar4 = *(undefined1 *)((int)param_2 + 7);
              uVar5 = (undefined1)param_2[2];
              uVar6 = *(undefined1 *)((int)param_2 + 9);
LAB_00069c84:
              printk(pcVar12,uVar1,uVar2,uVar3,uVar4,uVar5,uVar6,uVar15);
            }
            break;
          case 1:
            puVar18 = (undefined1 *)(iVar13 + 0x269);
            uVar15 = *param_2 | 2;
            puVar17 = (undefined1 *)((int)param_2 + 0xf);
            *param_2 = uVar15;
            do {
              puVar18 = puVar18 + 1;
              puVar17 = puVar17 + 1;
              *puVar17 = *puVar18;
            } while (puVar18 != (undefined1 *)(iVar13 + 0x26f));
            if (1 < g_tm_debug_level) {
              uVar1 = (undefined1)param_2[4];
              uVar2 = *(undefined1 *)((int)param_2 + 0x11);
              pcVar12 = "SW_ACL_ACT_SET_SMAC=%02x:%02x:%02x:%02x:%02x:%02x operMsk=0x%x\n";
              uVar3 = *(undefined1 *)((int)param_2 + 0x12);
              uVar4 = *(undefined1 *)((int)param_2 + 0x13);
              uVar5 = (undefined1)param_2[5];
              uVar6 = *(undefined1 *)((int)param_2 + 0x15);
              goto LAB_00069c84;
            }
            break;
          case 2:
            param_2[0x14] = 1;
            *param_2 = *param_2 | 4;
            if (1 < g_tm_debug_level) {
              printk("SW_ACL_ACT_UNTAG_ADD_ONETAG operMsk=0x%x vlanOper=%d\n");
            }
            uVar15 = g_tm_debug_level;
            if ((*(char *)(iVar13 + 0x27a) == -1) && (*(char *)(iVar13 + 0x27b) == -1)) {
              *(ushort *)(param_2 + 0x17) =
                   CONCAT11(*(undefined1 *)(iVar13 + 0x26a),*(undefined1 *)(iVar13 + 0x26b));
            }
            else {
              *(undefined2 *)(param_2 + 0x17) = 0x8100;
            }
            if (1 < uVar15) {
              printk("SW_ACL_ACT_UNTAG_ADD_ONETAG TPID=0x%x\n",(short)param_2[0x17]);
            }
            uVar15 = g_tm_debug_level;
            if (*(char *)(iVar13 + 0x27c) == -1) {
              *(undefined1 *)((int)param_2 + 0x61) = *(undefined1 *)(iVar13 + 0x26c);
              *(ushort *)((int)param_2 + 0x62) = *(ushort *)((int)param_2 + 0x62) | 0xe000;
              if (1 < uVar15) {
                printk("SW_ACL_ACT_UNTAG_ADD_ONETAG PRI=%d vidMsk=0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if (*(char *)(iVar13 + 0x27d) == -1) {
              *(undefined1 *)(param_2 + 0x18) = *(undefined1 *)(iVar13 + 0x26d);
              *(ushort *)((int)param_2 + 0x62) = *(ushort *)((int)param_2 + 0x62) | 0x1000;
              if (1 < uVar15) {
                printk("SW_ACL_ACT_UNTAG_ADD_ONETAG CFI=%d vidMsk=0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if ((*(char *)(iVar13 + 0x27e) == -1) && (*(char *)(iVar13 + 0x27f) == -1)) {
              uVar1 = *(undefined1 *)(iVar13 + 0x26e);
              uVar6 = *(undefined1 *)(iVar13 + 0x26f);
              *(ushort *)((int)param_2 + 0x62) =
                   ~(~(*(ushort *)((int)param_2 + 0x62) >> 0xc) << 0xc);
              *(ushort *)((int)param_2 + 0x5e) = CONCAT11(uVar1,uVar6);
              if (1 < uVar15) {
                printk("SW_ACL_ACT_UNTAG_ADD_ONETAG VID=%d vidMsk=0x%x\n");
              }
            }
            break;
          case 3:
            param_2[0x14] = 2;
            *param_2 = *param_2 | 4;
            if (1 < g_tm_debug_level) {
              printk("SW_ACL_ACT_UNTAG_ADD_TWOTAG operMsk=0x%x vlanOper=%d\n");
            }
            uVar15 = g_tm_debug_level;
            if ((*(char *)(iVar13 + 0x274) == -1) && (*(char *)(iVar13 + 0x275) == -1)) {
              *(ushort *)(param_2 + 0x17) =
                   CONCAT11(*(undefined1 *)(iVar13 + 0x264),*(undefined1 *)(iVar13 + 0x265));
            }
            else {
              *(undefined2 *)(param_2 + 0x17) = 0x8100;
            }
            if (uVar15 < 2) {
              if (*(char *)(iVar13 + 0x276) != -1) goto LAB_00069ae0;
              *(undefined1 *)((int)param_2 + 0x61) = *(undefined1 *)(iVar13 + 0x266);
              *(ushort *)((int)param_2 + 0x62) =
                   ~((ushort)~(ushort)(((uint)*(ushort *)((int)param_2 + 0x62) << 0x13) >> 0x10) >>
                    3);
LAB_0006ab78:
              if (*(char *)(iVar13 + 0x277) == -1) {
                *(undefined1 *)(param_2 + 0x18) = *(undefined1 *)(iVar13 + 0x267);
                *(ushort *)((int)param_2 + 0x62) = *(ushort *)((int)param_2 + 0x62) | 0x1000;
              }
            }
            else {
              printk("SW_ACL_ACT_UNTAG_ADD_TWOTAG SVLAN TPID=0x%x\n",(short)param_2[0x17]);
              uVar15 = g_tm_debug_level;
              if (*(char *)(iVar13 + 0x276) == -1) {
                *(undefined1 *)((int)param_2 + 0x61) = *(undefined1 *)(iVar13 + 0x266);
                *(ushort *)((int)param_2 + 0x62) = *(ushort *)((int)param_2 + 0x62) | 0xe000;
                if (uVar15 < 2) goto LAB_0006ab78;
                printk("SW_ACL_ACT_UNTAG_ADD_TWOTAG SVLAN PRI=%d vidMsk=0x%x\n");
                uVar15 = g_tm_debug_level;
              }
LAB_00069ae0:
              if (*(char *)(iVar13 + 0x277) == -1) {
                *(undefined1 *)(param_2 + 0x18) = *(undefined1 *)(iVar13 + 0x267);
                *(ushort *)((int)param_2 + 0x62) = *(ushort *)((int)param_2 + 0x62) | 0x1000;
                if (1 < uVar15) {
                  printk("SW_ACL_ACT_UNTAG_ADD_TWOTAG SVLAN CFI=%d vidMsk=0x%x\n");
                  uVar15 = g_tm_debug_level;
                }
              }
            }
            if ((*(char *)(iVar13 + 0x278) == -1) && (*(char *)(iVar13 + 0x279) == -1)) {
              uVar1 = *(undefined1 *)(iVar13 + 0x268);
              uVar6 = *(undefined1 *)(iVar13 + 0x269);
              *(ushort *)((int)param_2 + 0x62) =
                   ~(~(*(ushort *)((int)param_2 + 0x62) >> 0xc) << 0xc);
              *(ushort *)((int)param_2 + 0x5e) = CONCAT11(uVar1,uVar6);
              if (1 < uVar15) {
                printk("SW_ACL_ACT_UNTAG_ADD_TWOTAG SVLAN VID=%d vidMsk=0x%x\n");
                uVar15 = g_tm_debug_level;
              }
            }
            if ((*(char *)(iVar13 + 0x27a) == -1) && (*(char *)(iVar13 + 0x27b) == -1)) {
              *(ushort *)(param_2 + 0x15) =
                   CONCAT11(*(undefined1 *)(iVar13 + 0x26a),*(undefined1 *)(iVar13 + 0x26b));
            }
            else {
              *(undefined2 *)(param_2 + 0x15) = 0x8100;
            }
            if (1 < uVar15) {
              printk("SW_ACL_ACT_UNTAG_ADD_TWOTAG CVLAN TPID=0x%x\n",(short)param_2[0x15]);
            }
            uVar15 = g_tm_debug_level;
            if (*(char *)(iVar13 + 0x27c) == -1) {
              *(undefined1 *)((int)param_2 + 0x59) = *(undefined1 *)(iVar13 + 0x26c);
              *(ushort *)((int)param_2 + 0x5a) = *(ushort *)((int)param_2 + 0x5a) | 0xe000;
              if (1 < uVar15) {
                printk("SW_ACL_ACT_UNTAG_ADD_TWOTAG CVLAN PRI=%d vidMsk=0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if (*(char *)(iVar13 + 0x27d) == -1) {
              *(undefined1 *)(param_2 + 0x16) = *(undefined1 *)(iVar13 + 0x26d);
              *(ushort *)((int)param_2 + 0x5a) = *(ushort *)((int)param_2 + 0x5a) | 0x1000;
              if (1 < uVar15) {
                printk("SW_ACL_ACT_UNTAG_ADD_TWOTAG CVLAN CFI=%d vidMsk=0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if ((*(char *)(iVar13 + 0x27e) == -1) && (*(char *)(iVar13 + 0x27f) == -1)) {
              uVar1 = *(undefined1 *)(iVar13 + 0x26e);
              uVar6 = *(undefined1 *)(iVar13 + 0x26f);
              *(ushort *)((int)param_2 + 0x5a) =
                   ~(~(*(ushort *)((int)param_2 + 0x5a) >> 0xc) << 0xc);
              *(ushort *)((int)param_2 + 0x56) = CONCAT11(uVar1,uVar6);
              if (1 < uVar15) {
                printk("SW_ACL_ACT_UNTAG_ADD_TWOTAG CVLAN VID=%d vidMsk=0x%x\n");
              }
            }
            break;
          case 4:
            param_2[0x14] = 3;
            *param_2 = *param_2 | 4;
            if (1 < g_tm_debug_level) {
              printk("SW_ACL_ACT_ONETAG_ADD_ONETAG operMsk=0x%x vlanOper=%d\n");
            }
            uVar15 = g_tm_debug_level;
            if ((*(char *)(iVar13 + 0x27a) == -1) && (*(char *)(iVar13 + 0x27b) == -1)) {
              *(ushort *)(param_2 + 0x17) =
                   CONCAT11(*(undefined1 *)(iVar13 + 0x26a),*(undefined1 *)(iVar13 + 0x26b));
            }
            else {
              *(undefined2 *)(param_2 + 0x17) = 0x8100;
            }
            if (1 < uVar15) {
              printk("SW_ACL_ACT_ONETAG_ADD_ONETAG SVLAN TPID=0x%x\n",(short)param_2[0x17]);
            }
            uVar15 = g_tm_debug_level;
            if (*(char *)(iVar13 + 0x27c) == -1) {
              *(undefined1 *)((int)param_2 + 0x61) = *(undefined1 *)(iVar13 + 0x26c);
              *(ushort *)((int)param_2 + 0x62) = *(ushort *)((int)param_2 + 0x62) | 0xe000;
              if (1 < uVar15) {
                printk("SW_ACL_ACT_ONETAG_ADD_ONETAG SVLAN PRI=%d vidMsk=0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if (*(char *)(iVar13 + 0x27d) == -1) {
              *(undefined1 *)(param_2 + 0x18) = *(undefined1 *)(iVar13 + 0x26d);
              *(ushort *)((int)param_2 + 0x62) = *(ushort *)((int)param_2 + 0x62) | 0x1000;
              if (1 < uVar15) {
                printk("SW_ACL_ACT_ONETAG_ADD_ONETAG SVLAN CFI=%d vidMsk=0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if ((*(char *)(iVar13 + 0x27e) == -1) && (*(char *)(iVar13 + 0x27f) == -1)) {
              uVar1 = *(undefined1 *)(iVar13 + 0x26e);
              uVar6 = *(undefined1 *)(iVar13 + 0x26f);
              *(ushort *)((int)param_2 + 0x62) =
                   ~(~(*(ushort *)((int)param_2 + 0x62) >> 0xc) << 0xc);
              *(ushort *)((int)param_2 + 0x5e) = CONCAT11(uVar1,uVar6);
              if (1 < uVar15) {
                printk("SW_ACL_ACT_ONETAG_ADD_ONETAG SVLAN VID=%d vidMsk=0x%x\n");
              }
            }
            break;
          case 5:
            param_2[0x14] = 4;
            *param_2 = *param_2 | 4;
            if (1 < g_tm_debug_level) {
              printk("SW_ACL_ACT_ONETAG_DEL_ONETAG operMsk=0x%x vlanOper=%d\n");
            }
            break;
          case 6:
            param_2[0x14] = 5;
            *param_2 = *param_2 | 4;
            if (1 < g_tm_debug_level) {
              printk("SW_ACL_ACT_ONETAG_MOD_ONETAG operMsk=0x%x vlanOper=%d\n");
            }
            uVar15 = g_tm_debug_level;
            if (((*(char *)(iVar13 + 0x27a) == -1) && (*(char *)(iVar13 + 0x27b) == -1)) &&
               (*(ushort *)(param_2 + 0x17) =
                     CONCAT11(*(undefined1 *)(iVar13 + 0x26a),*(undefined1 *)(iVar13 + 0x26b)),
               1 < uVar15)) {
              printk("SW_ACL_ACT_ONETAG_MOD_ONETAG TPID=0x%x\n");
            }
            uVar15 = g_tm_debug_level;
            if (*(char *)(iVar13 + 0x27c) == -1) {
              *(undefined1 *)((int)param_2 + 0x61) = *(undefined1 *)(iVar13 + 0x26c);
              *(ushort *)((int)param_2 + 0x62) = *(ushort *)((int)param_2 + 0x62) | 0xe000;
              if (1 < uVar15) {
                printk("SW_ACL_ACT_ONETAG_MOD_ONETAG PRI=%d vidMsk=0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if (*(char *)(iVar13 + 0x27d) == -1) {
              *(undefined1 *)(param_2 + 0x18) = *(undefined1 *)(iVar13 + 0x26d);
              *(ushort *)((int)param_2 + 0x62) = *(ushort *)((int)param_2 + 0x62) | 0x1000;
              if (1 < uVar15) {
                printk("SW_ACL_ACT_ONETAG_MOD_ONETAG CFI=%d vidMsk =0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if ((*(char *)(iVar13 + 0x27e) == -1) && (*(char *)(iVar13 + 0x27f) == -1)) {
              uVar1 = *(undefined1 *)(iVar13 + 0x26e);
              uVar6 = *(undefined1 *)(iVar13 + 0x26f);
              *(ushort *)((int)param_2 + 0x62) =
                   ~(~(*(ushort *)((int)param_2 + 0x62) >> 0xc) << 0xc);
              *(ushort *)((int)param_2 + 0x5e) = CONCAT11(uVar1,uVar6);
              if (1 < uVar15) {
                printk("SW_ACL_ACT_ONETAG_MOD_ONETAG VLANID=%d vidMsk =0x%x\n");
              }
            }
            break;
          case 7:
            param_2[0x14] = 6;
            *param_2 = *param_2 | 4;
            if (1 < g_tm_debug_level) {
              printk("SW_ACL_ACT_ONETAG_ADD_ONETAG_MOD_ONETAG operMsk=0x%x vlanOper=%d\n");
            }
            uVar15 = g_tm_debug_level;
            if ((*(char *)(iVar13 + 0x274) == -1) && (*(char *)(iVar13 + 0x275) == -1)) {
              *(ushort *)(param_2 + 0x15) =
                   CONCAT11(*(undefined1 *)(iVar13 + 0x264),*(undefined1 *)(iVar13 + 0x265));
            }
            else {
              *(undefined2 *)(param_2 + 0x15) = 0x8100;
            }
            if (1 < uVar15) {
              printk("SW_ACL_ACT_ONETAG_ADD_ONETAG_MOD_ONETAG CVLAN TPID=0x%x\n",
                     (short)param_2[0x15]);
            }
            uVar15 = g_tm_debug_level;
            if (*(char *)(iVar13 + 0x276) == -1) {
              *(undefined1 *)((int)param_2 + 0x59) = *(undefined1 *)(iVar13 + 0x266);
              *(ushort *)((int)param_2 + 0x5a) = *(ushort *)((int)param_2 + 0x5a) | 0xe000;
              if (1 < uVar15) {
                printk("SW_ACL_ACT_ONETAG_ADD_ONETAG_MOD_ONETAG CVLAN PRI=%d vidMsk=0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if (*(char *)(iVar13 + 0x277) == -1) {
              *(undefined1 *)(param_2 + 0x16) = *(undefined1 *)(iVar13 + 0x267);
              *(ushort *)((int)param_2 + 0x5a) = *(ushort *)((int)param_2 + 0x5a) | 0x1000;
              if (1 < uVar15) {
                printk("SW_ACL_ACT_ONETAG_ADD_ONETAG_MOD_ONETAG CVLAN CFI=%d vidMsk=0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if ((*(char *)(iVar13 + 0x278) == -1) && (*(char *)(iVar13 + 0x279) == -1)) {
              uVar1 = *(undefined1 *)(iVar13 + 0x268);
              uVar6 = *(undefined1 *)(iVar13 + 0x269);
              *(ushort *)((int)param_2 + 0x5a) =
                   ~(~(*(ushort *)((int)param_2 + 0x5a) >> 0xc) << 0xc);
              *(ushort *)((int)param_2 + 0x56) = CONCAT11(uVar1,uVar6);
              if (1 < uVar15) {
                printk("SW_ACL_ACT_ONETAG_ADD_ONETAG_MOD_ONETAG CVLAN VID=%d vidMsk=0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if (((*(char *)(iVar13 + 0x27a) == -1) && (*(char *)(iVar13 + 0x27b) == -1)) &&
               (*(ushort *)(param_2 + 0x17) =
                     CONCAT11(*(undefined1 *)(iVar13 + 0x26a),*(undefined1 *)(iVar13 + 0x26b)),
               1 < uVar15)) {
              printk("SW_ACL_ACT_ONETAG_ADD_ONETAG_MOD_ONETAG SVLAN TPID=0x%x\n");
            }
            uVar15 = g_tm_debug_level;
            if (*(char *)(iVar13 + 0x27c) == -1) {
              *(undefined1 *)((int)param_2 + 0x61) = *(undefined1 *)(iVar13 + 0x26c);
              *(ushort *)((int)param_2 + 0x62) = *(ushort *)((int)param_2 + 0x62) | 0xe000;
              if (1 < uVar15) {
                printk("SW_ACL_ACT_ONETAG_ADD_ONETAG_MOD_ONETAG SVLAN PRI=%d vidMsk=0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if (*(char *)(iVar13 + 0x27d) == -1) {
              *(undefined1 *)(param_2 + 0x18) = *(undefined1 *)(iVar13 + 0x26d);
              *(ushort *)((int)param_2 + 0x62) = *(ushort *)((int)param_2 + 0x62) | 0x1000;
              if (1 < uVar15) {
                printk("SW_ACL_ACT_ONETAG_ADD_ONETAG_MOD_ONETAG SVLAN CFI=%d vidMsk=0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if ((*(char *)(iVar13 + 0x27e) == -1) && (*(char *)(iVar13 + 0x27f) == -1)) {
              uVar1 = *(undefined1 *)(iVar13 + 0x26e);
              uVar6 = *(undefined1 *)(iVar13 + 0x26f);
              *(ushort *)((int)param_2 + 0x62) =
                   ~(~(*(ushort *)((int)param_2 + 0x62) >> 0xc) << 0xc);
              *(ushort *)((int)param_2 + 0x5e) = CONCAT11(uVar1,uVar6);
              if (1 < uVar15) {
                printk("SW_ACL_ACT_ONETAG_ADD_ONETAG_MOD_ONETAG SLAN VLANID=%d vidMsk=0x%x\n");
              }
            }
            break;
          case 8:
          case 0x1c:
            break;
          case 9:
            param_2[0x14] = 8;
            *param_2 = *param_2 | 4;
            if (1 < g_tm_debug_level) {
              printk("SW_ACL_ACT_TWOTAG_DEL_ONETAG operMsk=0x%x vlanOper=%d\n");
            }
            break;
          case 10:
            param_2[0x14] = 9;
            *param_2 = *param_2 | 4;
            if (1 < g_tm_debug_level) {
              printk("W_ACL_ACT_TWOTAG_MOD_INNERTAG operMsk=0x%x vlanOper=%d\n");
            }
            uVar15 = g_tm_debug_level;
            if (((*(char *)(iVar13 + 0x27a) == -1) && (*(char *)(iVar13 + 0x27b) == -1)) &&
               (*(ushort *)(param_2 + 0x15) =
                     CONCAT11(*(undefined1 *)(iVar13 + 0x26a),*(undefined1 *)(iVar13 + 0x26b)),
               1 < uVar15)) {
              printk("SW_ACL_ACT_TWOTAG_MOD_INNERTAG TPID=0x%x\n");
            }
            uVar15 = g_tm_debug_level;
            if (*(char *)(iVar13 + 0x27c) == -1) {
              *(undefined1 *)((int)param_2 + 0x59) = *(undefined1 *)(iVar13 + 0x26c);
              *(ushort *)((int)param_2 + 0x5a) = *(ushort *)((int)param_2 + 0x5a) | 0xe000;
              if (1 < uVar15) {
                printk("SW_ACL_ACT_TWOTAG_MOD_INNERTAG PRI=%d vidMsk=0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if (*(char *)(iVar13 + 0x27d) == -1) {
              *(undefined1 *)(param_2 + 0x16) = *(undefined1 *)(iVar13 + 0x26d);
              *(ushort *)((int)param_2 + 0x5a) = *(ushort *)((int)param_2 + 0x5a) | 0x1000;
              if (1 < uVar15) {
                printk("SW_ACL_ACT_TWOTAG_MOD_INNERTAG CFI=%d vidMsk=0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if ((*(char *)(iVar13 + 0x27e) == -1) && (*(char *)(iVar13 + 0x27f) == -1)) {
              uVar1 = *(undefined1 *)(iVar13 + 0x26e);
              uVar6 = *(undefined1 *)(iVar13 + 0x26f);
              *(ushort *)((int)param_2 + 0x5a) =
                   ~(~(*(ushort *)((int)param_2 + 0x5a) >> 0xc) << 0xc);
              *(ushort *)((int)param_2 + 0x56) = CONCAT11(uVar1,uVar6);
              if (1 < uVar15) {
                printk("SW_ACL_ACT_TWOTAG_MOD_INNERTAG VLANID=%d vidMsk=0x%x\n");
              }
            }
            break;
          case 0xb:
            param_2[0x14] = 10;
            *param_2 = *param_2 | 4;
            if (1 < g_tm_debug_level) {
              printk("SW_ACL_ACT_TWOTAG_MOD_OUTERTAG operMsk=0x%x vlanOper=%d\n");
            }
            uVar15 = g_tm_debug_level;
            if (((*(char *)(iVar13 + 0x27a) == -1) && (*(char *)(iVar13 + 0x27b) == -1)) &&
               (*(ushort *)(param_2 + 0x17) =
                     CONCAT11(*(undefined1 *)(iVar13 + 0x26a),*(undefined1 *)(iVar13 + 0x26b)),
               1 < uVar15)) {
              printk("SW_ACL_ACT_TWOTAG_MOD_OUTERTAG TPID=0x%x\n");
            }
            uVar15 = g_tm_debug_level;
            if (*(char *)(iVar13 + 0x27c) == -1) {
              *(undefined1 *)((int)param_2 + 0x61) = *(undefined1 *)(iVar13 + 0x26c);
              *(ushort *)((int)param_2 + 0x62) = *(ushort *)((int)param_2 + 0x62) | 0xe000;
              if (1 < uVar15) {
                printk("SW_ACL_ACT_TWOTAG_MOD_OUTERTAG PRI=%d vidMsk=0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if (*(char *)(iVar13 + 0x27d) == -1) {
              *(undefined1 *)(param_2 + 0x18) = *(undefined1 *)(iVar13 + 0x26d);
              *(ushort *)((int)param_2 + 0x62) = *(ushort *)((int)param_2 + 0x62) | 0x1000;
              if (1 < uVar15) {
                printk("SW_ACL_ACT_TWOTAG_MOD_OUTERTAG CFI=%d vidMsk=0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if ((*(char *)(iVar13 + 0x27e) == -1) && (*(char *)(iVar13 + 0x27f) == -1)) {
              uVar1 = *(undefined1 *)(iVar13 + 0x26e);
              uVar6 = *(undefined1 *)(iVar13 + 0x26f);
              *(ushort *)((int)param_2 + 0x62) =
                   ~(~(*(ushort *)((int)param_2 + 0x62) >> 0xc) << 0xc);
              *(ushort *)((int)param_2 + 0x5e) = CONCAT11(uVar1,uVar6);
              if (1 < uVar15) {
                printk("SW_ACL_ACT_TWOTAG_MOD_OUTERTAG VLANID=%d vidMsk=0x%x\n");
              }
            }
            break;
          case 0xc:
            param_2[0x14] = 0xb;
            *param_2 = *param_2 | 4;
            if (1 < g_tm_debug_level) {
              printk("SW_ACL_ACT_TWOTAG_DEL_TWOTAG operMsk=0x%x vlanOper=%d\n");
            }
            break;
          case 0xd:
            param_2[0x14] = 0xc;
            *param_2 = *param_2 | 4;
            if (1 < g_tm_debug_level) {
              printk("SW_ACL_ACT_TWOTAG_DEL_OUTERTAG_MOD_INNERTAG operMsk=0x%x vlanOper=%d\n");
            }
            uVar15 = g_tm_debug_level;
            if (((*(char *)(iVar13 + 0x27a) == -1) && (*(char *)(iVar13 + 0x27b) == -1)) &&
               (*(ushort *)(param_2 + 0x15) =
                     CONCAT11(*(undefined1 *)(iVar13 + 0x26a),*(undefined1 *)(iVar13 + 0x26b)),
               1 < uVar15)) {
              printk("SW_ACL_ACT_TWOTAG_DEL_OUTERTAG_MOD_INNERTAG TPID=0x%x\n");
            }
            uVar15 = g_tm_debug_level;
            if (*(char *)(iVar13 + 0x27c) == -1) {
              *(undefined1 *)((int)param_2 + 0x59) = *(undefined1 *)(iVar13 + 0x26c);
              *(ushort *)((int)param_2 + 0x5a) = *(ushort *)((int)param_2 + 0x5a) | 0xe000;
              if (1 < uVar15) {
                printk("SW_ACL_ACT_TWOTAG_DEL_OUTERTAG_MOD_INNERTAG PRI=%d vidMsk=0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if (*(char *)(iVar13 + 0x27d) == -1) {
              *(undefined1 *)(param_2 + 0x16) = *(undefined1 *)(iVar13 + 0x26d);
              *(ushort *)((int)param_2 + 0x5a) = *(ushort *)((int)param_2 + 0x5a) | 0x1000;
              if (1 < uVar15) {
                printk("SW_ACL_ACT_TWOTAG_DEL_OUTERTAG_MOD_INNERTAG CFI=%d vidMsk=0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if ((*(char *)(iVar13 + 0x27e) == -1) && (*(char *)(iVar13 + 0x27f) == -1)) {
              uVar1 = *(undefined1 *)(iVar13 + 0x26e);
              uVar6 = *(undefined1 *)(iVar13 + 0x26f);
              *(ushort *)((int)param_2 + 0x5a) =
                   ~(~(*(ushort *)((int)param_2 + 0x5a) >> 0xc) << 0xc);
              *(ushort *)((int)param_2 + 0x56) = CONCAT11(uVar1,uVar6);
              if (1 < uVar15) {
                printk("SW_ACL_ACT_TWOTAG_DEL_OUTERTAG_MOD_INNERTAG VLANID=%d vidMsk=0x%x\n");
              }
            }
            break;
          case 0xe:
            param_2[0x14] = 0xd;
            *param_2 = *param_2 | 4;
            if (1 < g_tm_debug_level) {
              printk("SW_ACL_ACT_TWOTAG_MOD_TWOTAG operMsk=0x%x vlanOper=%d\n");
            }
            uVar15 = g_tm_debug_level;
            if (((*(char *)(iVar13 + 0x274) == -1) && (*(char *)(iVar13 + 0x275) == -1)) &&
               (*(ushort *)(param_2 + 0x17) =
                     CONCAT11(*(undefined1 *)(iVar13 + 0x264),*(undefined1 *)(iVar13 + 0x265)),
               1 < uVar15)) {
              printk("SW_ACL_ACT_TWOTAG_MOD_TWOTAG SVLAN TPID=0x%x\n");
            }
            uVar15 = g_tm_debug_level;
            if (*(char *)(iVar13 + 0x276) == -1) {
              *(undefined1 *)((int)param_2 + 0x61) = *(undefined1 *)(iVar13 + 0x266);
              *(ushort *)((int)param_2 + 0x62) = *(ushort *)((int)param_2 + 0x62) | 0xe000;
              if (1 < uVar15) {
                printk("SW_ACL_ACT_TWOTAG_MOD_TWOTAG SVLAN PRI=%d vidMsk=0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if (*(char *)(iVar13 + 0x277) == -1) {
              *(undefined1 *)(param_2 + 0x18) = *(undefined1 *)(iVar13 + 0x267);
              *(ushort *)((int)param_2 + 0x62) = *(ushort *)((int)param_2 + 0x62) | 0x1000;
              if (1 < uVar15) {
                printk("SW_ACL_ACT_TWOTAG_MOD_TWOTAG SVLAN CFI=%d vidMsk=0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if ((*(char *)(iVar13 + 0x278) == -1) && (*(char *)(iVar13 + 0x279) == -1)) {
              uVar1 = *(undefined1 *)(iVar13 + 0x268);
              uVar6 = *(undefined1 *)(iVar13 + 0x269);
              *(ushort *)((int)param_2 + 0x62) =
                   ~(~(*(ushort *)((int)param_2 + 0x62) >> 0xc) << 0xc);
              *(ushort *)((int)param_2 + 0x5e) = CONCAT11(uVar1,uVar6);
              if (1 < uVar15) {
                printk("SW_ACL_ACT_TWOTAG_MOD_TWOTAG SVLAN VLANID=%d vidMsk=0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if (((*(char *)(iVar13 + 0x27a) == -1) && (*(char *)(iVar13 + 0x27b) == -1)) &&
               (*(ushort *)(param_2 + 0x15) =
                     CONCAT11(*(undefined1 *)(iVar13 + 0x26a),*(undefined1 *)(iVar13 + 0x26b)),
               1 < uVar15)) {
              printk("SW_ACL_ACT_TWOTAG_MOD_TWOTAG CVLAN TPID=0x%x\n");
            }
            uVar15 = g_tm_debug_level;
            if (*(char *)(iVar13 + 0x27c) == -1) {
              *(undefined1 *)((int)param_2 + 0x59) = *(undefined1 *)(iVar13 + 0x26c);
              *(ushort *)((int)param_2 + 0x5a) = *(ushort *)((int)param_2 + 0x5a) | 0xe000;
              if (1 < uVar15) {
                printk("SW_ACL_ACT_TWOTAG_MOD_TWOTAG CVLAN PRI=%d vidMsk=0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if (*(char *)(iVar13 + 0x27d) == -1) {
              *(undefined1 *)(param_2 + 0x16) = *(undefined1 *)(iVar13 + 0x26d);
              *(ushort *)((int)param_2 + 0x5a) = *(ushort *)((int)param_2 + 0x5a) | 0x1000;
              if (1 < uVar15) {
                printk("SW_ACL_ACT_TWOTAG_MOD_TWOTAG CVLAN CFI=%d vidMsk=0x%x\n");
              }
            }
            uVar15 = g_tm_debug_level;
            if ((*(char *)(iVar13 + 0x27e) == -1) && (*(char *)(iVar13 + 0x27f) == -1)) {
              uVar1 = *(undefined1 *)(iVar13 + 0x26e);
              uVar6 = *(undefined1 *)(iVar13 + 0x26f);
              *(ushort *)((int)param_2 + 0x5a) =
                   ~(~(*(ushort *)((int)param_2 + 0x5a) >> 0xc) << 0xc);
              *(ushort *)((int)param_2 + 0x56) = CONCAT11(uVar1,uVar6);
              if (1 < uVar15) {
                printk("SW_ACL_ACT_TWOTAG_MOD_TWOTAG CVLAN VLANID=%d vidMsk=0x%x\n");
              }
            }
            break;
          case 0xf:
            *param_2 = *param_2 | 8;
            uVar15 = g_tm_debug_level;
            *(ushort *)(param_2 + 7) =
                 CONCAT11(*(undefined1 *)(iVar13 + 0x26e),*(undefined1 *)(iVar13 + 0x26f));
            if (1 < uVar15) {
              printk("SW_ACL_ACT_SET_ETHERTYPE value=0x%x operMsk=0x%x\n");
            }
            break;
          case 0x10:
            *param_2 = *param_2 | 0x10;
            uVar15 = g_tm_debug_level;
            *(undefined1 *)(param_2 + 8) = *(undefined1 *)(iVar13 + 0x26f);
            if (1 < uVar15) {
              printk("SW_ACL_ACT_SET_IPV4_VERSION value=%d operMsk=0x%x\n");
            }
            break;
          case 0x11:
            *param_2 = *param_2 | 0x20;
            uVar15 = g_tm_debug_level;
            *(undefined1 *)((int)param_2 + 0x22) = *(undefined1 *)(iVar13 + 0x26f);
            if (1 < uVar15) {
              printk("SW_ACL_ACT_SET_IPV4_TOS value=%d operMsk=0x%x\n");
            }
            break;
          case 0x12:
            *param_2 = *param_2 | 0x40;
            uVar15 = g_tm_debug_level;
            *(undefined1 *)((int)param_2 + 0x21) = *(undefined1 *)(iVar13 + 0x26f);
            if (1 < uVar15) {
              printk("SW_ACL_ACT_SET_IPV4_PROTOCOL value=%d operMsk=0x%x\n");
            }
            break;
          case 0x13:
            *param_2 = *param_2 | 0x80;
            uVar15 = g_tm_debug_level;
            *(undefined1 *)((int)param_2 + 0x23) = *(undefined1 *)(iVar13 + 0x26c);
            *(undefined1 *)(param_2 + 9) = *(undefined1 *)(iVar13 + 0x26d);
            *(undefined1 *)((int)param_2 + 0x25) = *(undefined1 *)(iVar13 + 0x26e);
            *(undefined1 *)((int)param_2 + 0x26) = *(undefined1 *)(iVar13 + 0x26f);
            if (1 < uVar15) {
              printk("SW_ACL_ACT_SET_IPV4_DIP value=%d.%d.%d.%d operMsk=0x%x\n");
            }
            break;
          case 0x14:
            *param_2 = *param_2 | 0x100;
            uVar15 = g_tm_debug_level;
            *(undefined1 *)((int)param_2 + 0x27) = *(undefined1 *)(iVar13 + 0x26c);
            *(undefined1 *)(param_2 + 10) = *(undefined1 *)(iVar13 + 0x26d);
            *(undefined1 *)((int)param_2 + 0x29) = *(undefined1 *)(iVar13 + 0x26e);
            *(undefined1 *)((int)param_2 + 0x2a) = *(undefined1 *)(iVar13 + 0x26f);
            if (1 < uVar15) {
              printk("SW_ACL_ACT_SET_IPV4_SIP value=%d.%d.%d.%d operMsk=0x%x\n");
            }
            break;
          case 0x15:
            *param_2 = *param_2 | 0x200;
            uVar15 = g_tm_debug_level;
            *(undefined1 *)((int)param_2 + 0x21) = *(undefined1 *)(iVar13 + 0x26f);
            if (1 < uVar15) {
              printk("SW_ACL_ACT_SET_IPV6_NEXTHEADER value=%d operMsk=0x%x\n");
            }
            break;
          case 0x16:
            *param_2 = *param_2 | 0x400;
            uVar15 = g_tm_debug_level;
            *(undefined1 *)(param_2 + 8) = *(undefined1 *)(iVar13 + 0x26f);
            if (1 < uVar15) {
              printk("SW_ACL_ACT_SET_IPV6_TRAFFIC_CLASS value=%d operMsk=0x%x\n");
            }
            break;
          case 0x17:
            *param_2 = *param_2 | 0x800;
            uVar15 = g_tm_debug_level;
            param_2[9] = (uint)CONCAT12(*(undefined1 *)(iVar13 + 0x26d),
                                        CONCAT11(*(undefined1 *)(iVar13 + 0x26e),
                                                 *(undefined1 *)(iVar13 + 0x26f)));
            if (1 < uVar15) {
              printk("SW_ACL_ACT_SET_IPV6_FLOWLABEL value=%d operMsk=0x%x\n");
            }
            break;
          case 0x18:
            *param_2 = *param_2 | 0x1000;
            if (1 < g_tm_debug_level) {
              printk("SW_ACL_ACT_SET_IPV6_DIPV6value=");
            }
            puVar18 = (undefined1 *)((int)param_2 + 0x27);
            puVar17 = (undefined1 *)(iVar13 + 0x25f);
            iVar11 = 0;
            uVar15 = g_tm_debug_level;
            do {
              puVar17 = puVar17 + 1;
              puVar18 = puVar18 + 1;
              *puVar18 = *puVar17;
              if (1 < uVar15) {
                printk(&_LC336);
                uVar15 = g_tm_debug_level;
                if (iVar11 == 0xf) break;
                if (1 < g_tm_debug_level) {
                  printk(&_LC251);
                  uVar15 = g_tm_debug_level;
                }
              }
              iVar11 = iVar11 + 1;
            } while (iVar11 != 0x10);
            goto joined_r0x000697b8;
          case 0x19:
            *param_2 = *param_2 | 0x2000;
            if (1 < g_tm_debug_level) {
              printk("SW_ACL_ACT_SET_IPV6_SIPV6=");
            }
            puVar18 = (undefined1 *)((int)param_2 + 0x37);
            puVar17 = (undefined1 *)(iVar13 + 0x25f);
            iVar11 = 0;
            uVar15 = g_tm_debug_level;
            do {
              puVar17 = puVar17 + 1;
              puVar18 = puVar18 + 1;
              *puVar18 = *puVar17;
              if (1 < uVar15) {
                printk(&_LC336);
                uVar15 = g_tm_debug_level;
                if (iVar11 == 0xf) break;
                if (1 < g_tm_debug_level) {
                  printk(&_LC251);
                  uVar15 = g_tm_debug_level;
                }
              }
              iVar11 = iVar11 + 1;
            } while (iVar11 != 0x10);
joined_r0x000697b8:
            if (1 < uVar15) {
              printk(" operMsk=0x%x\n",*param_2);
            }
            break;
          case 0x1a:
            *param_2 = *param_2 | 0x4000;
            uVar15 = g_tm_debug_level;
            param_2[0x12] =
                 (uint)CONCAT11(*(undefined1 *)(iVar13 + 0x26e),*(undefined1 *)(iVar13 + 0x26f));
            if (1 < uVar15) {
              printk("SW_ACL_ACT_SET_L4_DPORT=%d operMsk=0x%x\n");
            }
            break;
          case 0x1b:
            *param_2 = *param_2 | 0x8000;
            uVar15 = g_tm_debug_level;
            param_2[0x13] =
                 (uint)CONCAT11(*(undefined1 *)(iVar13 + 0x26e),*(undefined1 *)(iVar13 + 0x26f));
            if (1 < uVar15) {
              printk("SW_ACL_ACT_SET_L4_SPORT=%d operMsk=0x%x\n");
            }
            break;
          case 0x1d:
            uVar1 = *(undefined1 *)(iVar13 + 0x269);
            uVar7 = CONCAT11(*(undefined1 *)(iVar13 + 0x268),uVar1);
            uVar8 = CONCAT12(*(undefined1 *)(iVar13 + 0x26a),
                             CONCAT11(*(undefined1 *)(iVar13 + 0x26b),
                                      *(undefined1 *)(iVar13 + 0x26c)));
            uVar16 = (uint)uVar8;
            uVar9 = CONCAT12(*(undefined1 *)(iVar13 + 0x26d),
                             CONCAT11(*(undefined1 *)(iVar13 + 0x26e),
                                      *(undefined1 *)(iVar13 + 0x26f)));
            uVar15 = (uint)uVar9;
            if (0x1f < uVar7) {
              if (g_tm_debug_level == 0) {
                return 0xffffffff;
              }
              printk("[%s] SW_ACL_ACT_RATELIMIT invalid BKTID!!!bktid=%d\n","zte_sw_api.c",uVar7);
              return 0xffffffff;
            }
            if (uVar9 == 0 && uVar8 == 0) {
              iVar11 = tm_flow_rate_limit_set(uVar7,0,0,0);
              if (iVar11 != 0) {
                if (g_tm_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[%s] FAIL! bktid=%d cir=%d pir=%d\n","zte_sw_api.c",uVar7,0,0);
                return 0xffffffff;
              }
            }
            else {
              iVar11 = tm_flow_rate_limit_set(uVar7,1,uVar16,uVar15 - uVar16);
              if (iVar11 != 0) {
                if (g_tm_debug_level == 0) {
                  return 0xffffffff;
                }
                printk("[%s] FAIL! bktid=%d cir=%d pir=%d\n","zte_sw_api.c",uVar7,uVar16,uVar15);
                return 0xffffffff;
              }
              if (g_tm_debug_level < 2) {
                *(undefined1 *)(param_3 + 4) = uVar1;
                *(undefined1 *)(param_3 + 5) = 1;
                break;
              }
              printk("SW_ACL_ACT_RATELIMIT bktid=%d cir=%d pir=%d\n",*(undefined1 *)(param_3 + 4),
                     uVar16,uVar15);
            }
            uVar10 = g_tm_debug_level;
            *(undefined1 *)(param_3 + 4) = uVar1;
            *(undefined1 *)(param_3 + 5) = 1;
            if (6 < uVar10) {
              printk("SW_ACL_ACT_RATELIMIT bktid=%d cir=%d pir=%d\n",uVar7,uVar16,uVar15);
            }
            break;
          default:
            if (g_tm_debug_level == 0) {
              return 0xffffffff;
            }
            printk("[%s] invalid action!!!\n","zte_sw_api.c");
            return 0xffffffff;
          }
          iVar14 = iVar14 + 1;
          iVar13 = iVar13 + 0x24;
        } while (iVar14 < (int)(uint)*(byte *)(param_1 + 600));
      }
      if (1 < g_tm_debug_level) {
        printk("[%s] output: operMsk=0x%x vlanOper=%d\n","zte_sw_api.c",*param_2,param_2[0x14]);
      }
      return 0;
    }
    if (g_tm_debug_level != 0) {
      printk("[%s] input ERROR: action entrynum too large!action entrynum=%d\n","zte_sw_api.c");
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}

