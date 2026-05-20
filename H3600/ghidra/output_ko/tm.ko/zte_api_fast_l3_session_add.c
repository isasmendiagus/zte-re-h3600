// module: tm.ko
// function: zte_api_fast_l3_session_add @ 0x6558c
// size: 5904 bytes
//

int zte_api_fast_l3_session_add(byte *param_1,uint *param_2)

{
  byte bVar1;
  undefined4 *puVar2;
  int iVar3;
  byte bVar4;
  char *extraout_r1;
  char *pcVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  undefined1 *puVar8;
  undefined4 uVar9;
  uint uVar10;
  byte *pbVar11;
  byte *pbVar12;
  undefined4 uVar13;
  byte *pbVar14;
  int iVar15;
  byte *local_160;
  uint local_15c;
  uint local_158;
  uint local_154;
  uint local_150;
  uint local_14c;
  uint local_148;
  byte local_144 [4];
  undefined1 local_140;
  undefined1 local_13f;
  undefined1 local_13e [6];
  byte local_138 [4];
  undefined1 local_134;
  undefined1 local_133;
  undefined1 local_132 [6];
  undefined2 local_12c;
  byte local_128;
  byte local_126;
  byte local_125 [4];
  byte local_121 [33];
  uint local_100;
  uint local_fc;
  undefined4 local_f8;
  undefined2 local_f4;
  ushort local_f2;
  byte local_f0;
  undefined1 local_ef;
  undefined2 local_ee;
  undefined2 local_ec;
  ushort local_ea;
  byte local_e8;
  byte local_e7;
  undefined2 local_e6;
  undefined1 local_e4 [2];
  undefined2 local_e2;
  byte local_e0;
  undefined1 local_df;
  uint local_dc;
  uint local_d8;
  uint local_d4;
  undefined4 local_c8;
  undefined4 local_88;
  byte local_82;
  byte local_81;
  byte local_80 [4];
  byte local_7c [12];
  undefined2 local_70;
  undefined2 local_6e;
  byte local_6c [15];
  byte bStack_5d;
  byte local_5c [16];
  byte local_4c [16];
  undefined2 local_3c;
  undefined2 local_3a;
  undefined1 local_34;
  byte local_33;
  undefined2 local_32;
  undefined2 local_2e;
  byte local_2c;
  
  local_160 = (byte *)0x0;
  if (param_1 == (byte *)0x0) {
    if (g_tm_debug_level != 0) {
      printk("[%s] input ERROR: ptFastL3Session=NULL\n","zte_sw_api.c");
    }
    return -1;
  }
  __memzero(local_e4,0xbc);
  __memzero(&local_148,100);
  __memzero(&local_15c,0x14);
  local_d4 = (uint)*param_1;
  bVar4 = param_1[0x9d];
  local_2c = param_1[0x9f];
  if (bVar4 == 0xff) {
    local_df = 0;
    local_e0 = 0;
  }
  local_2e = 0;
  local_e4[0] = 0;
  if (bVar4 != 0xff) {
    local_df = 1;
    local_e0 = bVar4;
  }
  local_33 = param_1[0x9c];
  local_32 = *(undefined2 *)(param_1 + 0x9a);
  local_34 = (undefined1)*(undefined2 *)(param_1 + 0x98);
  if (1 < g_tm_debug_level) {
    printk("[%s] direction(0-up 1=dw)=%d\n","zte_sw_api.c",local_d4);
  }
  _raw_spin_lock_bh(&fast_api_busy_lock);
  if (param_1[0x68] == 0) {
    uVar10 = (uint)*(ushort *)(param_1 + 0x6a);
    local_148 = uVar10;
    if (uVar10 != 0) {
      local_12c = 0x8864;
      local_148 = 0x20000;
      zte_session_id = uVar10;
    }
  }
  else {
    local_148 = 0x10000;
    if (((*(int *)(param_1 + 8) == 0) && (*(int *)(param_1 + 0xc) == 0)) &&
       (*(int *)(param_1 + 0x10) == 0)) {
      local_12c = 0x800;
    }
    else {
      local_12c = 0x86dd;
    }
  }
  local_d8 = (uint)*(ushort *)(param_1 + 0x2e);
  local_e2 = 2000;
  if (local_d8 == 0) {
    if (param_1[0x28] == 6 || param_1[0x28] == 0x11) {
      local_d8 = 3;
    }
    else {
      local_d8 = 7;
    }
    tm_acl_setMtchInfo(param_1,local_e4);
    bVar4 = param_1[0x28];
    pcVar5 = extraout_r1;
    if (bVar4 != 6 && bVar4 != 0x11) {
      pcVar5 = (char *)0x3;
    }
    local_88 = 1;
    if ((bVar4 == 6 || bVar4 == 0x11) &&
       (pcVar5 = 
        "%d, gemport_valid = %d, gemport_id = %d, tcontid_llid = %d, queue_id = %d, flow_id = %d\n",
       is3TupleRule != 0)) {
      pcVar5 = (char *)0x3;
    }
    puVar8 = &local_13f;
    local_148 = (uint)pcVar5 | local_148;
    pbVar11 = param_1 + 0x3b;
    do {
      pbVar11 = pbVar11 + 1;
      puVar8[-5] = *pbVar11;
      puVar8 = puVar8 + 1;
      *puVar8 = 0xff;
    } while (pbVar11 != param_1 + 0x41);
    if (1 < g_tm_debug_level) {
      printk("set dmac:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x\n",local_144[0],local_144[1],local_144[2]
             ,local_144[3],local_140,local_13f);
    }
    pbVar11 = param_1 + 0x35;
    puVar8 = &local_133;
    do {
      pbVar11 = pbVar11 + 1;
      puVar8[-5] = *pbVar11;
      puVar8 = puVar8 + 1;
      *puVar8 = 0xff;
    } while (pbVar11 != param_1 + 0x3b);
    if (1 < g_tm_debug_level) {
      printk("set smac:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x\n",local_138[0],local_138[1],local_138[2]
             ,local_138[3],local_134,local_133);
    }
    uVar10 = (uint)*(ushort *)(param_1 + 0x32);
    bVar4 = (byte)(*(ushort *)(param_1 + 0x32) >> 8);
    if (*param_1 == 0) {
      if (uVar10 == 0xffff) {
        if (param_1[0x2c] == 0xff) {
          local_148 = local_148 | 4;
          local_f8 = 4;
        }
      }
      else {
        bVar1 = param_1[0x2c];
        if ((bVar1 - 0xe & 0xf7) == 0) {
          local_f8 = 1;
        }
        else {
          if ((bVar1 & 0xf7) != 0x12) {
            if (bVar1 == 0xfe) {
              local_148 = local_148 | 4;
              local_f8 = 0xc;
              if (1 < g_tm_debug_level) {
                printk("SW_ACL_ACT_TWOTAG_DEL_OUTERTAG_MOD_INNERTAG operMsk=0x%x vlanOper=%d\n");
                uVar10 = (uint)*(ushort *)(param_1 + 0x32);
              }
              local_f0 = (byte)((uVar10 << 0x13) >> 0x1f);
              local_ef = (undefined1)(uVar10 >> 0xd);
              local_f2 = (ushort)((uVar10 << 0x14) >> 0x14);
              local_ee = 0xffff;
              local_f4 = 0x8100;
            }
            else {
              printk("unsupported tag level\n");
            }
            goto LAB_000657a4;
          }
          local_f8 = 5;
        }
        local_148 = local_148 | 4;
        local_ea = (ushort)((uVar10 << 0x14) >> 0x14);
        local_e8 = (byte)((uVar10 << 0x13) >> 0x1f);
        local_e7 = bVar4 >> 5;
        local_e6 = 0xffff;
        local_ec = 0x8100;
      }
LAB_000657a4:
      iVar15 = *(int *)(param_1 + 0x44);
      bVar4 = param_1[0x28];
      if (iVar15 == *(int *)(param_1 + 4)) {
        if (bVar4 == 6 || bVar4 == 0x11) {
          if (is3TupleRule == 0) {
            uVar10 = 0x8000;
          }
          else {
            uVar10 = 0;
          }
        }
        else {
          uVar10 = 0;
        }
      }
      else {
        if (bVar4 == 6 || bVar4 == 0x11) {
          if (is3TupleRule == 0) {
            uVar10 = 0x8100;
          }
          else {
            uVar10 = 0x100;
          }
        }
        else {
          uVar10 = 0x100;
        }
        pbVar11 = param_1 + 0x43;
        pbVar12 = local_125 + 3;
        do {
          pbVar11 = pbVar11 + 1;
          pbVar12 = pbVar12 + 1;
          *pbVar12 = *pbVar11;
          zte_onu_sip = iVar15;
        } while (pbVar12 != local_121 + 3);
      }
      local_148 = uVar10 | local_148;
      local_fc = (uint)*(ushort *)(param_1 + 0x54);
      if (1 < g_tm_debug_level) {
        printk("set sip:%d.%d.%d.%d, set sport %d\n",local_121[0],local_121[1],local_121[2],
               local_121[3],local_fc);
      }
    }
    else {
      if (uVar10 == 0xffff) {
        if ((param_1[0x2c] & 0xf7) == 0x12) {
          local_f8 = 4;
          local_148 = local_148 | 4;
        }
      }
      else {
        if ((param_1[0x2c] & 0xf7) == 0x12) {
          local_f8 = 5;
        }
        else {
          if ((param_1[0x2c] - 0xe & 0xf7) != 0) {
            printk("unsupported tag level\n");
            goto LAB_00065ad0;
          }
          local_f8 = 1;
        }
        local_148 = local_148 | 4;
        local_ea = (ushort)((uVar10 << 0x14) >> 0x14);
        local_e8 = (byte)((uVar10 << 0x13) >> 0x1f);
        local_e7 = bVar4 >> 5;
        local_e6 = 0xffff;
        local_ec = 0x8100;
      }
LAB_00065ad0:
      if (param_1[0x28] == 6 || param_1[0x28] == 0x11) {
        uVar10 = 0x4080;
        if (is3TupleRule != 0) {
          uVar10 = 0x80;
        }
      }
      else {
        uVar10 = 0x80;
      }
      pbVar11 = param_1 + 0x43;
      pbVar12 = &local_126;
      local_148 = uVar10 | local_148;
      do {
        pbVar11 = pbVar11 + 1;
        pbVar12 = pbVar12 + 1;
        *pbVar12 = *pbVar11;
      } while (pbVar12 != local_125 + 3);
      local_100 = (uint)*(ushort *)(param_1 + 0x54);
      if (1 < g_tm_debug_level) {
        printk("set dip:%d.%d.%d.%d, set sport %d\n",local_125[0],local_125[1],local_125[2],
               local_125[3],local_100);
      }
    }
    if (param_1[0x34] != 0) {
      local_126 = param_1[0x35];
      local_148 = local_148 | 0x20;
joined_r0x00065b5c:
      if (1 < g_tm_debug_level) {
        iVar15 = 2;
        printk("set dscp: %d\n");
        goto LAB_00065b64;
      }
    }
LAB_00065b60:
    iVar15 = 2;
    goto LAB_00065b64;
  }
  if (local_d8 != 1) {
    if (local_d8 != 2) {
      if (local_d8 != 3) {
        if (g_tm_debug_level != 0) {
          printk("[%s] undefined l3 num %d found\n","zte_sw_api.c");
        }
        _raw_spin_unlock_bh(&fast_api_busy_lock);
        return -1;
      }
      tm_acl_setMtchInfo(param_1,local_e4);
      puVar8 = &local_13f;
      local_148 = local_148 | 3;
      local_88 = 1;
      pbVar11 = param_1 + 0x3b;
      do {
        pbVar11 = pbVar11 + 1;
        puVar8[-5] = *pbVar11;
        puVar8 = puVar8 + 1;
        *puVar8 = 0xff;
      } while (pbVar11 != param_1 + 0x41);
      if (1 < g_tm_debug_level) {
        printk("set dmac:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x\n",local_144[0],local_144[1],
               local_144[2],local_144[3],local_140,local_13f);
      }
      pbVar11 = param_1 + 0x35;
      puVar8 = &local_133;
      do {
        pbVar11 = pbVar11 + 1;
        puVar8[-5] = *pbVar11;
        puVar8 = puVar8 + 1;
        *puVar8 = 0xff;
      } while (param_1 + 0x3b != pbVar11);
      if (1 < g_tm_debug_level) {
        printk("set smac:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x\n",local_138[0],local_138[1],
               local_138[2],local_138[3],local_134,local_133);
      }
      pbVar11 = param_1 + 0x74;
      zte_dslite_hl = (uint)*pbVar11;
      pbVar12 = param_1 + 0x84;
      zte_dslite_fl = *(undefined4 *)(param_1 + 0x70);
      zte_dslite_tc = (uint)param_1[0x6c];
      iVar15 = 0;
      puVar2 = (undefined4 *)zte_onu_dipv6;
      puVar6 = (undefined4 *)zte_onu_sipv6;
      do {
        pbVar11 = pbVar11 + 4;
        iVar15 = iVar15 + 1;
        *puVar6 = *(undefined4 *)pbVar11;
        pbVar12 = pbVar12 + 4;
        *puVar2 = *(undefined4 *)pbVar12;
        puVar2 = puVar2 + 1;
        puVar6 = puVar6 + 1;
      } while (iVar15 != 4);
      uVar10 = (uint)*(ushort *)(param_1 + 0x32);
      bVar4 = (byte)(*(ushort *)(param_1 + 0x32) >> 8);
      if (*param_1 == 0) {
        if (uVar10 == 0xffff) {
          if (param_1[0x2c] == 0xff) {
            local_148 = local_148 | 4;
            local_f8 = 4;
          }
        }
        else {
          bVar1 = param_1[0x2c];
          if ((bVar1 - 0xe & 0xf7) == 0) {
            local_f8 = 1;
          }
          else {
            if ((bVar1 & 0xf7) != 0x12) {
              if (bVar1 == 0xfe) {
                local_148 = local_148 | 4;
                local_f8 = 0xc;
                if (1 < g_tm_debug_level) {
                  printk("SW_ACL_ACT_TWOTAG_DEL_OUTERTAG_MOD_INNERTAG operMsk=0x%x vlanOper=%d\n");
                  uVar10 = (uint)*(ushort *)(param_1 + 0x32);
                }
                local_f2 = (ushort)((uVar10 << 0x14) >> 0x14);
                local_f0 = (byte)((uVar10 << 0x13) >> 0x1f);
                local_ef = (undefined1)(uVar10 >> 0xd);
                local_ee = 0xffff;
                local_f4 = 0x8100;
              }
              else {
                printk("unsupported tag level\n");
              }
              goto LAB_000659dc;
            }
            local_f8 = 5;
          }
          local_148 = local_148 | 4;
          local_ea = (ushort)((uVar10 << 0x14) >> 0x14);
          local_e6 = 0xffff;
          local_e8 = (byte)((uVar10 << 0x13) >> 0x1f);
          local_e7 = bVar4 >> 5;
          local_ec = 0x8100;
        }
LAB_000659dc:
        local_148 = local_148 | 0x1000000;
        if (*(short *)(param_1 + 0x6a) == 0) {
          local_12c = 0x86dd;
        }
        if (1 < g_tm_debug_level) {
          printk("dslite add\n");
        }
      }
      else {
        bVar1 = param_1[0x2c];
        if (uVar10 == 0xffff) {
          if ((bVar1 & 0xf7) == 0x12) {
            local_148 = local_148 | 4;
            local_f8 = 4;
          }
        }
        else {
          if ((bVar1 & 0xf7) == 0x12) {
            local_ea = (ushort)((uVar10 << 0x14) >> 0x10);
            local_f8 = 5;
          }
          else {
            if ((bVar1 - 0xe & 0xf7) != 0) {
              printk("unsupported tag level\n");
              goto LAB_00065f84;
            }
            local_ea = (ushort)((uVar10 << 0x14) >> 0x10);
            local_f8 = 1;
          }
          local_ea = local_ea >> 4;
          local_148 = local_148 | 4;
          local_e7 = bVar4 >> 5;
          local_e8 = (byte)((uVar10 << 0x13) >> 0x1f);
          local_ec = 0x8100;
          local_e6 = 0xffff;
        }
LAB_00065f84:
        local_148 = local_148 | 0x2000000;
        local_12c = 0x800;
        if (1 < g_tm_debug_level) {
          printk("dslite delete\n");
        }
      }
      if (param_1[0x34] != 0) {
        local_126 = param_1[0x35];
        local_148 = local_148 | 0x40000;
        goto joined_r0x00065b5c;
      }
      goto LAB_00065b60;
    }
    if (((*(int *)(param_1 + 8) == 0) && (*(int *)(param_1 + 0xc) == 0)) &&
       (*(int *)(param_1 + 0x10) == 0)) {
      bVar4 = param_1[0x28];
      if (*param_1 == 0) {
        if (bVar4 == 6 || bVar4 == 0x11) {
          local_c8 = 0x701600;
          if (is3TupleRule != 0) {
            local_c8 = 0x401600;
          }
        }
        else {
          local_c8 = 0x401600;
        }
      }
      else if (bVar4 == 6 || bVar4 == 0x11) {
        local_c8 = 0x301600;
        if (is3TupleRule != 0) {
          local_c8 = 0x1600;
        }
      }
      else {
        local_c8 = 0x1600;
      }
      pbVar11 = param_1 + 0x13;
      pbVar12 = local_7c + 7;
      do {
        pbVar11 = pbVar11 + 1;
        pbVar12[-3] = *pbVar11;
        pbVar12 = pbVar12 + 1;
        *pbVar12 = 0xff;
      } while (pbVar11 != param_1 + 0x17);
      if (1 < g_tm_debug_level) {
        printk("acl filed dip:%d.%d.%d.%d\n",local_7c[4],local_7c[5],local_7c[6],local_7c[7]);
      }
      pbVar11 = param_1 + 3;
      pbVar12 = local_80 + 3;
      do {
        pbVar11 = pbVar11 + 1;
        pbVar12[-3] = *pbVar11;
        pbVar12 = pbVar12 + 1;
        *pbVar12 = 0xff;
      } while (pbVar11 != param_1 + 7);
      if (g_tm_debug_level < 2) {
        local_82 = param_1[0x28];
        local_6e = *(undefined2 *)(param_1 + 0x26);
        local_70 = *(undefined2 *)(param_1 + 0x24);
        goto LAB_000662b4;
      }
      printk("acl filed sip:%d.%d.%d.%d\n",local_80[0],local_80[1],local_80[2],local_80[3]);
      local_6e = *(undefined2 *)(param_1 + 0x26);
      local_82 = param_1[0x28];
      local_70 = *(undefined2 *)(param_1 + 0x24);
      if (g_tm_debug_level < 2) goto LAB_000662b4;
LAB_00066974:
      printk("acl filed protocol %d, dport %d, sport %d\n");
      local_dc = (uint)param_1[0x9e];
      if (1 < g_tm_debug_level) {
        printk("acl filed inport: %d\n");
      }
    }
    else {
      bVar4 = param_1[0x28];
      if (*param_1 == 0) {
        if (bVar4 == 6 || bVar4 == 0x11) {
          local_c8 = 0x746000;
          if (is3TupleRule != 0) {
            local_c8 = 0x446000;
          }
        }
        else {
          local_c8 = 0x446000;
        }
      }
      else if (bVar4 == 6 || bVar4 == 0x11) {
        local_c8 = 0x346000;
        if (is3TupleRule != 0) {
          local_c8 = 0x46000;
        }
      }
      else {
        local_c8 = 0x46000;
      }
      pbVar12 = param_1 + 0x13;
      pbVar14 = &bStack_5d;
      pbVar11 = local_5c + 0xf;
      do {
        pbVar12 = pbVar12 + 1;
        pbVar14 = pbVar14 + 1;
        *pbVar14 = *pbVar12;
        pbVar11 = pbVar11 + 1;
        *pbVar11 = 0xff;
      } while (pbVar14 != local_5c + 0xf);
      if (1 < g_tm_debug_level) {
        printk("acl filed dip:%8.8x.%8.8x.%8.8x.%8.8x\n",local_5c[0],local_5c[4],local_5c[8],
               local_5c[0xc]);
      }
      pbVar12 = param_1 + 3;
      pbVar14 = local_80 + 3;
      pbVar11 = (byte *)((int)&local_6e + 1);
      do {
        pbVar12 = pbVar12 + 1;
        pbVar14 = pbVar14 + 1;
        *pbVar14 = *pbVar12;
        pbVar11 = pbVar11 + 1;
        *pbVar11 = 0xff;
      } while (pbVar14 != (byte *)((int)&local_6e + 1));
      if (g_tm_debug_level < 2) {
        local_81 = param_1[0x28];
        local_3a = *(undefined2 *)(param_1 + 0x26);
        local_3c = *(undefined2 *)(param_1 + 0x24);
      }
      else {
        printk("acl filed sip:%8.8x.%8.8x.%8.8x.%8.8x\n",local_7c[0],local_7c[4],local_7c[8],
               (undefined1)local_70);
        local_3a = *(undefined2 *)(param_1 + 0x26);
        local_81 = param_1[0x28];
        local_3c = *(undefined2 *)(param_1 + 0x24);
        if (1 < g_tm_debug_level) goto LAB_00066974;
      }
LAB_000662b4:
      local_dc = (uint)param_1[0x9e];
    }
    uVar10 = (uint)*(ushort *)(param_1 + 0x32);
    if (*param_1 == 0) {
      if (uVar10 == 0x1000 || uVar10 == 0xffff) {
        if (uVar10 == 0xffff) {
          if (param_1[0x2c] == 0xff) goto LAB_0006669c;
        }
        else if (param_1[0x2c] == 0xfe) {
LAB_00066750:
          local_f8 = 0xc;
          local_148 = local_148 | 4;
          if (1 < g_tm_debug_level) {
            printk("SW_ACL_ACT_TWOTAG_DEL_OUTERTAG_MOD_INNERTAG operMsk=0x%x vlanOper=%d\n");
            uVar10 = (uint)*(ushort *)(param_1 + 0x32);
          }
          local_f0 = (byte)((uVar10 << 0x13) >> 0x1f);
          local_ef = (undefined1)(uVar10 >> 0xd);
          local_f2 = (ushort)((uVar10 << 0x14) >> 0x14);
          local_ee = 0xffff;
          local_f4 = 0x8100;
        }
      }
      else {
        bVar4 = param_1[0x2c];
        if ((bVar4 - 0xe & 0xf7) == 0) goto LAB_000664e8;
        if ((bVar4 & 0xf7) == 0x12) {
LAB_00066680:
          local_f8 = 5;
          goto LAB_000664f0;
        }
        if (bVar4 == 0xfe) goto LAB_00066750;
LAB_000665e0:
        printk("unsupported tag level\n");
      }
    }
    else if (uVar10 == 0xffff) {
      if ((param_1[0x2c] & 0xf7) == 0x12) {
LAB_0006669c:
        local_f8 = 4;
        local_148 = local_148 | 4;
      }
    }
    else {
      bVar4 = param_1[0x2c];
      if (uVar10 == 0x1000) {
        if ((bVar4 - 0xe & 0xf7) != 0) goto LAB_000662f8;
      }
      else {
        if ((bVar4 & 0xf7) == 0x12) goto LAB_00066680;
        if ((bVar4 - 0xe & 0xf7) != 0) goto LAB_000665e0;
      }
LAB_000664e8:
      local_f8 = 1;
LAB_000664f0:
      local_148 = local_148 | 4;
      local_ea = (ushort)((uVar10 << 0x14) >> 0x14);
      local_e8 = (byte)((uVar10 << 0x13) >> 0x1f);
      local_e7 = (byte)(*(ushort *)(param_1 + 0x32) >> 0xd);
      local_e6 = 0xffff;
      local_ec = 0x8100;
    }
LAB_000662f8:
    if (param_1[0x34] != 0) {
      local_126 = param_1[0x35];
      local_148 = local_148 | 0x20;
      if (1 < g_tm_debug_level) {
        printk("set dscp: %d\n");
      }
    }
    if (((*(int *)(param_1 + 8) == 0) && (*(int *)(param_1 + 0xc) == 0)) &&
       (*(int *)(param_1 + 0x10) == 0)) {
      local_88 = 1;
      if (param_1[0x28] == 6 || param_1[0x28] == 0x11) {
        local_d8 = 5;
      }
      else {
        local_d8 = 7;
      }
      iVar15 = 0;
    }
    else {
      iVar15 = 1;
      local_88 = 2;
      if (param_1[0x28] == 6 || param_1[0x28] == 0x11) {
        local_d8 = 6;
      }
      else {
        local_d8 = 8;
      }
    }
    goto LAB_00065b64;
  }
  if (param_1[0x28] == 6 || param_1[0x28] == 0x11) {
    local_d8 = 4;
    if (is3TupleRule != 0) goto LAB_00065d54;
    local_c8 = 0x346000;
  }
  else {
    local_d8 = 8;
LAB_00065d54:
    local_dc = (uint)param_1[0x9e];
    local_c8 = 0x446000;
    if (*param_1 != 0) {
      local_c8 = 0x46000;
    }
  }
  pbVar12 = param_1 + 0x13;
  pbVar14 = &bStack_5d;
  pbVar11 = local_5c + 0xf;
  do {
    pbVar12 = pbVar12 + 1;
    pbVar14 = pbVar14 + 1;
    *pbVar14 = *pbVar12;
    pbVar11 = pbVar11 + 1;
    *pbVar11 = 0xff;
  } while (pbVar14 != local_5c + 0xf);
  if (1 < g_tm_debug_level) {
    printk("acl filed dip:%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x\n"
           ,local_5c[0],local_5c[1],local_5c[2],local_5c[3],local_5c[4],local_5c[5],local_5c[6],
           local_5c[7],local_5c[8],local_5c[9],local_5c[10],local_5c[0xb],local_5c[0xc],
           local_5c[0xd],local_5c[0xe],local_5c[0xf]);
  }
  pbVar12 = param_1 + 3;
  pbVar14 = local_80 + 3;
  pbVar11 = (byte *)((int)&local_6e + 1);
  do {
    pbVar12 = pbVar12 + 1;
    pbVar14 = pbVar14 + 1;
    *pbVar14 = *pbVar12;
    pbVar11 = pbVar11 + 1;
    *pbVar11 = 0xff;
  } while (pbVar14 != (byte *)((int)&local_6e + 1));
  if (g_tm_debug_level < 2) {
    local_3a = *(undefined2 *)(param_1 + 0x26);
    local_81 = param_1[0x28];
    local_3c = *(undefined2 *)(param_1 + 0x24);
    bVar4 = local_81;
  }
  else {
    printk("acl filed sip:%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x.%02x\n"
           ,local_7c[0],local_7c[1],local_7c[2],local_7c[3],local_7c[4],local_7c[5],local_7c[6],
           local_7c[7],local_7c[8],local_7c[9],local_7c[10],local_7c[0xb],(undefined1)local_70,
           local_70._1_1_,(undefined1)local_6e,local_6e._1_1_);
    local_3a = *(undefined2 *)(param_1 + 0x26);
    local_81 = param_1[0x28];
    local_3c = *(undefined2 *)(param_1 + 0x24);
    bVar4 = local_81;
    if (1 < g_tm_debug_level) {
      printk("acl filed protocol %d, dport %d, sport %d\n");
      bVar4 = param_1[0x28];
    }
  }
  local_88 = 2;
  if (bVar4 == 6 || bVar4 == 0x11) {
    uVar10 = 0x400003;
    if (is3TupleRule != 0) {
      uVar10 = 3;
    }
  }
  else {
    uVar10 = 3;
  }
  puVar8 = &local_13f;
  local_148 = uVar10 | local_148;
  pbVar11 = param_1 + 0x3b;
  do {
    pbVar11 = pbVar11 + 1;
    puVar8[-5] = *pbVar11;
    puVar8 = puVar8 + 1;
    *puVar8 = 0xff;
  } while (pbVar11 != param_1 + 0x41);
  if (1 < g_tm_debug_level) {
    printk("set dmac:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x\n",local_144[0],local_144[1],local_144[2],
           local_144[3],local_140,local_13f);
  }
  pbVar11 = param_1 + 0x35;
  puVar8 = &local_133;
  do {
    pbVar11 = pbVar11 + 1;
    puVar8[-5] = *pbVar11;
    puVar8 = puVar8 + 1;
    *puVar8 = 0xff;
  } while (pbVar11 != param_1 + 0x3b);
  if (1 < g_tm_debug_level) {
    printk("set smac:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x\n",local_138[0],local_138[1],local_138[2],
           local_138[3],local_134,local_133);
  }
  uVar10 = (uint)*(ushort *)(param_1 + 0x32);
  if (*param_1 == 0) {
    if (uVar10 == 0xffff) {
      if (param_1[0x2c] == 0xff) {
LAB_000665a4:
        local_f8 = 4;
        local_148 = local_148 | 4;
      }
    }
    else {
      bVar4 = param_1[0x2c];
      if ((bVar4 - 0xe & 0xf7) == 0) {
LAB_00066174:
        local_f8 = 1;
LAB_0006617c:
        local_148 = local_148 | 4;
        local_ea = (ushort)((uVar10 << 0x14) >> 0x14);
        local_e8 = (byte)((uVar10 << 0x13) >> 0x1f);
        local_e7 = (byte)(*(ushort *)(param_1 + 0x32) >> 0xd);
        local_e6 = 0xffff;
        local_ec = 0x8100;
      }
      else {
        if ((bVar4 & 0xf7) == 0x12) goto LAB_00066484;
        if (bVar4 != 0xfe) goto LAB_00065ef8;
        local_f8 = 0xc;
        local_148 = local_148 | 4;
        if (1 < g_tm_debug_level) {
          printk("SW_ACL_ACT_TWOTAG_DEL_OUTERTAG_MOD_INNERTAG operMsk=0x%x vlanOper=%d\n");
          uVar10 = (uint)*(ushort *)(param_1 + 0x32);
        }
        local_f0 = (byte)((uVar10 << 0x13) >> 0x1f);
        local_ef = (undefined1)(uVar10 >> 0xd);
        local_f2 = (ushort)((uVar10 << 0x14) >> 0x14);
        local_ee = 0xffff;
        local_f4 = 0x8100;
      }
    }
  }
  else if (uVar10 == 0xffff) {
    if ((param_1[0x2c] & 0xf7) == 0x12) goto LAB_000665a4;
  }
  else {
    if ((param_1[0x2c] & 0xf7) == 0x12) {
LAB_00066484:
      local_f8 = 5;
      goto LAB_0006617c;
    }
    if ((param_1[0x2c] - 0xe & 0xf7) == 0) goto LAB_00066174;
LAB_00065ef8:
    printk("unsupported tag level\n");
  }
  if (param_1[0x34] != 0) {
    local_128 = param_1[0x35];
    local_148 = local_148 | 0x800000;
    if (1 < g_tm_debug_level) {
      iVar15 = 3;
      printk("set traffic class: %d\n");
      goto LAB_00065b64;
    }
  }
  iVar15 = 3;
LAB_00065b64:
  iVar3 = tm_add_acl_flow_rule(local_e4,&local_148,&local_15c);
  if (iVar3 == 0) {
    if (1 < g_tm_debug_level) {
      printk("[%s] add new flow: success\n","zte_sw_api.c");
    }
    pbVar11 = param_1 + 4;
    uVar10 = local_15c;
    if (*param_1 != 0) {
      uVar10 = local_15c | 0x80000000;
    }
    *param_2 = uVar10;
    param_2[1] = local_158;
    param_2[2] = local_154;
    param_2[3] = local_150;
    param_2[4] = local_14c;
    uVar10 = cla_list_hash_addr_gen(pbVar11,0x28);
    iVar3 = tm_findFastIdxByTuple(uVar10 & 0x1ff,pbVar11,&local_160);
    if (iVar3 == 0) {
      iVar3 = tm_del_acl_flow_rule(local_160 + 0x30,*local_160);
      if (iVar3 == 0) {
        if (1 < g_tm_debug_level) {
          printk("[%s] del exist flow: success\n","zte_sw_api.c");
        }
        *local_160 = *param_1;
        *(int *)(local_160 + 4) = iVar15;
        *(uint *)(local_160 + 0x30) = local_15c;
        *(uint *)(local_160 + 0x34) = local_158;
        *(uint *)(local_160 + 0x38) = local_154;
        *(uint *)(local_160 + 0x3c) = local_150;
        *(uint *)(local_160 + 0x40) = local_14c;
      }
      else if (g_tm_debug_level != 0) {
        printk("[%s] tm_del_acl_flow_rule failed %d\n","zte_sw_api.c",iVar3);
      }
    }
    else {
      pbVar12 = (byte *)kmem_cache_alloc(g_geInitFlag,0x20);
      if (pbVar12 != (byte *)0x0) {
        iVar3 = (uVar10 & 0x1ff) * 4;
        __memzero(pbVar12,0x4c);
        bVar4 = *param_1;
        *(int *)(pbVar12 + 4) = iVar15;
        *pbVar12 = bVar4;
        uVar7 = *(undefined4 *)(param_1 + 8);
        uVar9 = *(undefined4 *)(param_1 + 0xc);
        uVar13 = *(undefined4 *)(param_1 + 0x10);
        *(undefined4 *)(pbVar12 + 8) = *(undefined4 *)pbVar11;
        *(undefined4 *)(pbVar12 + 0xc) = uVar7;
        *(undefined4 *)(pbVar12 + 0x10) = uVar9;
        *(undefined4 *)(pbVar12 + 0x14) = uVar13;
        uVar7 = *(undefined4 *)(param_1 + 0x18);
        uVar9 = *(undefined4 *)(param_1 + 0x1c);
        uVar13 = *(undefined4 *)(param_1 + 0x20);
        *(undefined4 *)(pbVar12 + 0x18) = *(undefined4 *)(param_1 + 0x14);
        *(undefined4 *)(pbVar12 + 0x1c) = uVar7;
        *(undefined4 *)(pbVar12 + 0x20) = uVar9;
        *(undefined4 *)(pbVar12 + 0x24) = uVar13;
        uVar7 = *(undefined4 *)(param_1 + 0x28);
        *(undefined4 *)(pbVar12 + 0x28) = *(undefined4 *)(param_1 + 0x24);
        *(undefined4 *)(pbVar12 + 0x2c) = uVar7;
        *(uint *)(pbVar12 + 0x30) = local_15c;
        *(uint *)(pbVar12 + 0x34) = local_158;
        *(uint *)(pbVar12 + 0x38) = local_154;
        *(uint *)(pbVar12 + 0x3c) = local_150;
        *(uint *)(pbVar12 + 0x40) = local_14c;
        if (*(int *)(g_FastList + iVar3) == 0) {
          *(byte **)(g_FastList + iVar3) = pbVar12;
        }
        else {
          *(byte **)(*(int *)(g_FastList_Tail + iVar3) + 0x48) = pbVar12;
          *(undefined4 *)(pbVar12 + 0x44) = *(undefined4 *)(g_FastList_Tail + iVar3);
        }
        *(byte **)(g_FastList_Tail + iVar3) = pbVar12;
        if ((iVar15 == 2) || ((iVar15 != 3 && (iVar15 != 1)))) {
          (&g_fast_entry_v4)[*pbVar12] = (&g_fast_entry_v4)[*pbVar12] + 1;
        }
        else {
          *(int *)((int)&g_fast_entry_v6 + (uint)*pbVar12 * 4) =
               *(int *)((int)&g_fast_entry_v6 + (uint)*pbVar12 * 4) + 1;
        }
        _raw_spin_unlock_bh(&fast_api_busy_lock);
        return 0;
      }
      printk("[%s] FAIL! t_fastNode malloc fail!\n","zte_sw_api.c");
    }
  }
  _raw_spin_unlock_bh(&fast_api_busy_lock);
  return iVar3;
}

