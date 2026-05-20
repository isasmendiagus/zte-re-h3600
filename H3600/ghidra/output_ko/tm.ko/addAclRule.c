// module: tm.ko
// function: addAclRule @ 0x5e4ec
// size: 1628 bytes
//

undefined4 addAclRule(int param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  uint local_120;
  ushort local_11a;
  ushort local_118;
  ushort local_116;
  undefined4 local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  uint local_104;
  byte local_100 [16];
  ushort local_f0;
  byte local_ee;
  undefined1 auStack_ec [60];
  undefined1 auStack_b0 [16];
  uint local_a0;
  uint local_9c;
  uint local_98;
  uint local_94;
  uint local_90;
  uint local_8c;
  uint local_88;
  uint local_84;
  uint local_80;
  uint local_7c;
  undefined2 local_78;
  byte local_76;
  byte local_75;
  undefined1 auStack_6c [16];
  uint local_5c;
  uint local_58;
  uint local_54;
  uint local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  undefined2 local_34;
  byte local_32;
  byte local_31;
  
  local_120 = 0;
  if (param_3 == (undefined4 *)0x0 || param_1 == 0) {
    printk("ERROR:(%s:%d)","tm_acl_v2.c",0xb6c);
    printk("addAclRule params is NULL\n");
  }
  else {
    __memzero(local_100,0x14);
    __memzero(auStack_b0,0x44);
    __memzero(auStack_ec,0x3c);
    __memzero(&local_114,0x14);
    __memzero(&local_11a,6);
    iVar3 = *(int *)(param_1 + 0xc);
    g_ipv4FastEn = iVar3 == 3;
    g_ipv6FastEn = iVar3 == 4;
    g_multiEn = iVar3 == 100;
    iVar3 = aclGetExtIdxRuleRamAddrByPort(*(undefined4 *)(param_1 + 8),&local_120);
    if (iVar3 == 0) {
      local_104 = local_120;
      iVar3 = cla_get_extra_index_table(local_120,local_100);
      if (iVar3 == 0) {
        if ((local_ee & 0x10) == 0) {
          printk("ERROR:(%s:%d)","tm_acl_v2.c",0xb92);
          printk("uninitialized extract index table\n");
          return 0xfffffff4;
        }
        iVar3 = aclBuildExtRuleAndHashEntriesByParseCondition(param_1,auStack_b0,auStack_ec);
        if (iVar3 == 0) {
          iVar3 = *(int *)(param_1 + 0x1c);
          if (g_l2fast_opti == 0) {
            uVar5 = 0;
          }
          else {
            uVar5 = 8;
          }
          if (local_120 < 0xb) {
            iVar1 = local_120 * 0x10;
            bVar6 = false;
            do {
              while ((uVar4 = (int)(uint)local_f0 >> uVar5 & 1, uVar4 == 0 ||
                     (iVar3 != *(int *)(sa_rulesRecord + (iVar1 + uVar5) * 0x10)))) {
LAB_0005e62c:
                if (uVar4 == 0 && !bVar6) {
                  bVar6 = true;
                  local_116 = ~((ushort)~(ushort)((local_100[0] + uVar5) * 0x20000 >> 0x10) >> 1);
                }
LAB_0005e650:
                uVar5 = uVar5 + 1 & 0xff;
                if (uVar5 == 0x10) goto LAB_0005e9dc;
              }
              iVar2 = cla_get_extra_rule_table(uVar5 + local_100[0],auStack_6c);
              if (iVar2 != 0) {
                printk("ERROR:(%s:%d)","tm_acl_v2.c",0x660);
                printk("cla_get_extra_rule_table fail\n");
                return 0xfffffff4;
              }
              if (((((((((local_32 ^ local_76) & 8) != 0) || (((local_75 ^ local_31) & 4) != 0)) ||
                     ((local_5c << 4) >> 0x10 != (local_a0 << 4) >> 0x10)) ||
                    (((((local_58 & 0xfff) << 4 | local_5c >> 0x1c) !=
                       ((local_9c & 0xfff) << 4 | local_a0 >> 0x1c) ||
                      ((local_58 << 4) >> 0x10 != (local_9c << 4) >> 0x10)) ||
                     ((((local_54 & 0xfff) << 4 | local_58 >> 0x1c) !=
                       ((local_98 & 0xfff) << 4 | local_9c >> 0x1c) ||
                      (((local_54 << 4) >> 0x10 != (local_98 << 4) >> 0x10 ||
                       (((local_50 & 0xfff) << 4 | local_54 >> 0x1c) !=
                        ((local_94 & 0xfff) << 4 | local_98 >> 0x1c))))))))) ||
                   (((local_50 << 4) >> 0x10 != (local_94 << 4) >> 0x10 ||
                    (((((local_4c & 0xfff) << 4 | local_50 >> 0x1c) !=
                       ((local_90 & 0xfff) << 4 | local_94 >> 0x1c) ||
                      ((local_4c << 4) >> 0x10 != (local_90 << 4) >> 0x10)) ||
                     (((local_48 & 0xfff) << 4 | local_4c >> 0x1c) !=
                      ((local_8c & 0xfff) << 4 | local_90 >> 0x1c))))))) ||
                  ((((local_48 << 4) >> 0x10 != (local_8c << 4) >> 0x10 ||
                    (((local_44 & 0xfff) << 4 | local_48 >> 0x1c) !=
                     ((local_88 & 0xfff) << 4 | local_8c >> 0x1c))) ||
                   ((((local_44 << 4) >> 0x10 != (local_88 << 4) >> 0x10 ||
                     ((((local_40 & 0xfff) << 4 | local_44 >> 0x1c) !=
                       ((local_84 & 0xfff) << 4 | local_88 >> 0x1c) ||
                      ((local_40 << 4) >> 0x10 != (local_84 << 4) >> 0x10)))) ||
                    (((local_3c & 0xfff) << 4 | local_40 >> 0x1c) !=
                     ((local_80 & 0xfff) << 4 | local_84 >> 0x1c))))))) ||
                 (((((local_3c << 4) >> 0x10 != (local_80 << 4) >> 0x10 ||
                    (((local_38 & 0xfff) << 4 | local_3c >> 0x1c) !=
                     ((local_7c & 0xfff) << 4 | local_80 >> 0x1c))) ||
                   ((local_38 << 4) >> 0x10 != (local_7c << 4) >> 0x10)) ||
                  (((local_34 & 0xfff) << 4 | local_38 >> 0x1c) !=
                   ((local_78 & 0xfff) << 4 | local_7c >> 0x1c))))) goto LAB_0005e62c;
              if (((local_34._1_1_ ^ local_78._1_1_) & 0x10) != 0) goto LAB_0005e62c;
              if ((local_31 & 2) == 0) {
                local_11a = ~((ushort)~(ushort)((local_100[0] + uVar5) * 0x20000 >> 0x10) >> 1);
                goto LAB_0005e650;
              }
              iVar2 = local_100[0] + uVar5;
              uVar5 = uVar5 + 1 & 0xff;
              local_118 = ~((ushort)~(ushort)((uint)(iVar2 * 0x20000) >> 0x10) >> 1);
            } while (uVar5 != 0x10);
LAB_0005e9dc:
            iVar3 = aclBuildHashAndAclRule
                              (param_1,&local_11a,param_2,local_100,auStack_b0,auStack_ec,&local_114
                              );
            if (iVar3 == 0) {
              *param_3 = local_114;
              bVar6 = TM_CLA_DEBUG == 0;
              param_3[1] = local_110;
              param_3[2] = local_10c;
              param_3[4] = local_104;
              param_3[3] = local_108;
              if (bVar6) {
                return 0;
              }
              printk("m_ruleAddr=%x, m_hashAddr=%x, m_extRamMsk=%x,m_extIdxRamAddr=%d, m_direction=%d\n"
                     ,local_110,local_10c,local_108,local_120,*(undefined4 *)(param_1 + 0x10));
              return 0;
            }
          }
          else {
            printk("invalid p_ramAddr = %d\n");
          }
        }
      }
      return 0xfffffff4;
    }
    printk("ERROR:invalid sorce port %d\n",*(undefined4 *)(param_1 + 8));
  }
  return 0xfffffff4;
}

