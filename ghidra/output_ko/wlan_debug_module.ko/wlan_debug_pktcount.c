// module: wlan_debug_module.ko
// function: wlan_debug_pktcount @ 0x13ca8
// size: 5816 bytes
//

undefined4 wlan_debug_pktcount(int param_1,uint param_2,char *param_3)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  char *pcVar4;
  size_t sVar5;
  size_t sVar6;
  ushort uVar7;
  ushort uVar8;
  uint uVar9;
  byte *pbVar10;
  int iVar11;
  uint uVar12;
  size_t sVar13;
  byte *pbVar14;
  ushort uVar15;
  uint uVar16;
  bool bVar17;
  bool bVar18;
  byte *local_7c;
  int local_78;
  uint local_74;
  undefined4 local_58;
  uint local_54;
  undefined4 local_50;
  undefined4 local_4c;
  char *apcStack_48 [4];
  char *local_38;
  undefined *puStack_34;
  undefined *puStack_30;
  char *pcStack_2c;
  
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  if ((g_pktcnt_dbgflag == 0) && (g_dscp_set_flag == 0)) {
    return 0;
  }
  if (0x13 < param_2 || param_1 == 0) {
    return 0xffffffff;
  }
  bVar17 = param_3 != (char *)0x0;
  iVar3 = create_wlan_proc_file(g_pktlist_proc + param_2 * 0xc4);
  if (iVar3 == 1 && bVar17) {
    __memzero(g_pktlist_proc + param_2 * 0xc4 + 0xa4,0x20);
    strncpy(g_pktlist_proc + param_2 * 0xc4 + 0xa4,param_3,0x1f);
  }
  pbVar10 = *(byte **)(param_1 + 0xcc);
  uVar12 = *(uint *)(param_1 + 100);
  if (*(char **)(param_1 + 0x18) == (char *)0x0) {
    local_58 = 0x4e414c57;
    local_54 = local_54 & 0xffffff00;
  }
  else {
    strncpy((char *)&local_58,*(char **)(param_1 + 0x18),0xf);
  }
  *(int *)(&g_pktlist + param_2 * 0x3e98) = *(int *)(&g_pktlist + param_2 * 0x3e98) + 1;
  if (uVar12 < 0x26) {
    return 0;
  }
  uVar8 = *(ushort *)(pbVar10 + 0xc) >> 8;
  uVar7 = *(ushort *)(pbVar10 + 0xc) << 8;
  uVar15 = uVar7 | uVar8;
  if ((uVar15 == 0x800 && g_dscp_set_flag != 0) && ((param_2 & 0xfffffffd) == 0)) {
    if (pbVar10[0x17] == 0x11) {
      if ((g_dscp_set_flag & 2) != 0) {
        if ((*(int *)(param_1 + 0xd4) != 1) ||
           ((uVar9 = g_dscp_of_udp, (*(byte *)(param_1 + 0x72) & 1) != 0 &&
            ((*(uint *)(*(int *)(param_1 + 0xc4) + 0x20) & 0xffff) != 1)))) goto LAB_000142d8;
LAB_00014944:
        ipv4_change_dscp_constprop_3(pbVar10 + 0xe,(uVar9 & 7) << 5);
        bVar18 = 0xfffffffe < (uint)g_normal_pkt_cnt;
        g_normal_pkt_cnt._0_4_ = (uint)g_normal_pkt_cnt + 1;
        g_normal_pkt_cnt._4_4_ = g_normal_pkt_cnt._4_4_ + (uint)bVar18;
      }
    }
    else if ((pbVar10[0x17] == 6) && ((g_dscp_set_flag & 1) != 0)) {
      if ((*(int *)(param_1 + 0xd4) == 1) &&
         ((uVar9 = g_dscp_of_tcp, (*(byte *)(param_1 + 0x72) & 1) == 0 ||
          ((*(uint *)(*(int *)(param_1 + 0xc4) + 0x20) & 0xffff) == 1)))) goto LAB_00014944;
LAB_000142d8:
      bVar18 = 0xfffffffe < (uint)g_shared_pkt_cnt;
      g_shared_pkt_cnt._0_4_ = (uint)g_shared_pkt_cnt + 1;
      g_shared_pkt_cnt._4_4_ = g_shared_pkt_cnt._4_4_ + (uint)bVar18;
    }
  }
  if (g_pktcnt_dbgflag == 0) {
    return 0;
  }
  pbVar14 = pbVar10 + 6;
  if (uVar15 == 0x8100) {
    uVar15 = *(ushort *)(pbVar10 + 0x10) << 8 | *(ushort *)(pbVar10 + 0x10) >> 8;
    if (uVar15 == 0x8100) {
      local_7c = pbVar10 + 8;
      uVar15 = *(ushort *)(pbVar10 + 0x14) << 8 | *(ushort *)(pbVar10 + 0x14) >> 8;
      local_78 = 2;
      local_74 = (*(ushort *)(pbVar10 + 0x12) & 0xf) << 8 | (uint)(*(ushort *)(pbVar10 + 0x12) >> 8)
      ;
    }
    else {
      local_74 = (*(ushort *)(pbVar10 + 0xe) & 0xf) << 8 | (uint)(*(ushort *)(pbVar10 + 0xe) >> 8);
      local_7c = pbVar10 + 4;
      local_78 = 1;
    }
LAB_00013ebc:
    if (uVar15 == 0x800) {
LAB_0001408c:
      bVar1 = local_7c[0x17];
      if (bVar1 == 0x11) {
        if ((g_pktcnt_dbgflag & 2) != 0) {
          countIP(local_7c,param_2,param_3,pbVar14,pbVar10,1,uVar12,local_74);
        }
        if ((g_pktcnt_dbgflag & 8) != 0) {
          uVar9 = (local_7c[0xe] & 0xf) * 4;
          if ((local_7c[0xe] & 0xf) == 5) {
            iVar3 = 0x24;
            uVar9 = 0x22;
            uVar7 = *(ushort *)(local_7c + 0x22);
          }
          else {
            if (0x14 < uVar9) {
              uVar9 = uVar9 + 0xe;
            }
            iVar3 = uVar9 + 2;
            uVar7 = *(ushort *)(local_7c + uVar9);
          }
          uVar8 = uVar7 << 8 | uVar7 >> 8;
          uVar7 = *(ushort *)(local_7c + iVar3) << 8 | *(ushort *)(local_7c + iVar3) >> 8;
          if ((uVar7 == 0x43 && uVar8 == 0x44) || (uVar7 == 0x44 && uVar8 == 0x43)) {
            uVar16 = (uint)local_7c[uVar9 + 0xfa];
            apcStack_48[0] = "unknown";
            apcStack_48[1] = "discover";
            apcStack_48[2] = "offer";
            apcStack_48[3] = "request";
            local_38 = "decline";
            puStack_34 = &DAT_00016f90;
            puStack_30 = &DAT_00016f94;
            pcStack_2c = "release";
            if (uVar16 - 1 < 7 && bVar17) {
              if (local_74 == 0xffffffff) {
                printk("[%s]%8ld [%u][%s] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X, %d.%d.%d.%d->%d.%d.%d.%d, dhcp %s, clientip=%d.%d.%d.%d, yourip=%d.%d.%d.%d, clientmac=%02X:%02X:%02X:%02X:%02X:%02X\n"
                       ,&local_58,jiffies,param_2,param_3,pbVar10[6],pbVar10[7],pbVar10[8],
                       pbVar10[9],pbVar10[10],pbVar10[0xb],*pbVar10,pbVar10[1],pbVar10[2],pbVar10[3]
                       ,pbVar10[4],pbVar10[5],local_7c[0x1a],local_7c[0x1b],local_7c[0x1c],
                       local_7c[0x1d],local_7c[0x1e],local_7c[0x1f],local_7c[0x20],local_7c[0x21],
                       apcStack_48[uVar16],local_7c[uVar9 + 0x14],local_7c[uVar9 + 0x15],
                       local_7c[uVar9 + 0x16],local_7c[uVar9 + 0x17],local_7c[uVar9 + 0x18],
                       local_7c[uVar9 + 0x19],local_7c[uVar9 + 0x1a],local_7c[uVar9 + 0x1b],
                       local_7c[uVar9 + 0x24],local_7c[uVar9 + 0x25],local_7c[uVar9 + 0x26],
                       local_7c[uVar9 + 0x27],local_7c[uVar9 + 0x28],local_7c[uVar9 + 0x29]);
              }
              else {
                printk("[%s]%8ld [%u][%s] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X, %d.%d.%d.%d->%d.%d.%d.%d, dhcp %s, clientip=%d.%d.%d.%d, yourip=%d.%d.%d.%d, clientmac=%02X:%02X:%02X:%02X:%02X:%02X, VID=%d\n"
                       ,&local_58,jiffies,param_2,param_3,pbVar10[6],pbVar10[7],pbVar10[8],
                       pbVar10[9],pbVar10[10],pbVar10[0xb],*pbVar10,pbVar10[1],pbVar10[2],pbVar10[3]
                       ,pbVar10[4],pbVar10[5],local_7c[0x1a],local_7c[0x1b],local_7c[0x1c],
                       local_7c[0x1d],local_7c[0x1e],local_7c[0x1f],local_7c[0x20],local_7c[0x21],
                       apcStack_48[uVar16],local_7c[uVar9 + 0x14],local_7c[uVar9 + 0x15],
                       local_7c[uVar9 + 0x16],local_7c[uVar9 + 0x17],local_7c[uVar9 + 0x18],
                       local_7c[uVar9 + 0x19],local_7c[uVar9 + 0x1a],local_7c[uVar9 + 0x1b],
                       local_7c[uVar9 + 0x24],local_7c[uVar9 + 0x25],local_7c[uVar9 + 0x26],
                       local_7c[uVar9 + 0x27],local_7c[uVar9 + 0x28],local_7c[uVar9 + 0x29],local_74
                      );
              }
            }
          }
        }
        if ((g_pktcnt_dbgflag & 0x20) != 0) {
          uVar9 = (local_7c[0xe] & 0xf) * 4;
          if ((local_7c[0xe] & 0xf) == 5) {
            uVar9 = 0x22;
            sVar2 = *(short *)(local_7c + 0x22);
            iVar3 = 0x24;
          }
          else {
            if (0x14 < uVar9) {
              uVar9 = uVar9 + 0xe;
            }
            sVar2 = *(short *)(local_7c + uVar9);
            iVar3 = uVar9 + 2;
          }
          if (sVar2 == 0x3500 || *(short *)(local_7c + iVar3) == 0x3500) {
            if (bVar17) {
              if (local_74 == 0xffffffff) {
                printk("[%s]%8ld [%u][%s] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X, %d.%d.%d.%d->%d.%d.%d.%d\n"
                       ,&local_58,jiffies,param_2,param_3,pbVar10[6],pbVar10[7],pbVar10[8],
                       pbVar10[9],pbVar10[10],pbVar10[0xb],*pbVar10,pbVar10[1],pbVar10[2],pbVar10[3]
                       ,pbVar10[4],pbVar10[5],local_7c[0x1a],local_7c[0x1b],local_7c[0x1c],
                       local_7c[0x1d],local_7c[0x1e],local_7c[0x1f],local_7c[0x20],local_7c[0x21]);
              }
              else {
                printk("[%s]%8ld [%u][%s] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X, %d.%d.%d.%d->%d.%d.%d.%d, VID=%d\n"
                       ,&local_58,jiffies,param_2,param_3,pbVar10[6],pbVar10[7],pbVar10[8],
                       pbVar10[9],pbVar10[10],pbVar10[0xb],*pbVar10,pbVar10[1],pbVar10[2],pbVar10[3]
                       ,pbVar10[4],pbVar10[5],local_7c[0x1a],local_7c[0x1b],local_7c[0x1c],
                       local_7c[0x1d],local_7c[0x1e],local_7c[0x1f],local_7c[0x20],local_7c[0x21],
                       local_74);
              }
            }
            iVar3 = 0;
            bVar1 = local_7c[uVar9 + 0x14];
            while (bVar1 != 0) {
              iVar3 = iVar3 + bVar1 + 1;
              bVar1 = (local_7c + uVar9 + 0x14)[iVar3];
            }
            printk("Queries = <");
            for (iVar11 = 1; iVar11 <= iVar3 + -1; iVar11 = iVar11 + 1) {
              if (local_7c[iVar11 + uVar9 + 0x14] < 0x1f) {
                printk(&_LC79);
              }
              else {
                printk(&_LC80);
              }
            }
            printk(&_LC81);
          }
        }
      }
      else {
        if (bVar1 == 6) {
          uVar9 = g_pktcnt_dbgflag & 1;
        }
        else {
          uVar9 = 0;
        }
        if (uVar9 == 0) {
          uVar9 = (g_pktcnt_dbgflag << 0x1d) >> 0x1f;
          if (bVar1 != 1) {
            uVar9 = 0;
          }
          if (uVar9 == 0) {
            uVar9 = (g_pktcnt_dbgflag << 0x16) >> 0x1f;
            if (bVar1 != 2) {
              uVar9 = 0;
            }
            if (uVar9 != 0) {
              uVar16 = local_7c[0xe] & 0xf;
              apcStack_48[0] = "IGMP report(IGMPV2)";
              apcStack_48[1] = "IGMP report(IGMPV1)";
              apcStack_48[2] = "IGMP leave";
              apcStack_48[3] = "IGMP query";
              uVar9 = uVar16 * 4;
              if (uVar16 == 5) {
                uVar9 = 0x22;
              }
              local_38 = "unknown";
              if ((uVar16 != 5) && (0x14 < uVar16 * 4)) {
                uVar9 = uVar9 + 0xe;
              }
              bVar1 = local_7c[uVar9];
              if ((byte)(bVar1 - 0x11) < 7) {
                iVar3 = *(int *)(CSWTCH_239 + (uint)(byte)(bVar1 - 0x11) * 4);
              }
              else {
                iVar3 = 4;
              }
              if (bVar17) {
                if (local_74 == 0xffffffff) {
                  printk("[%s]%8ld [%u][%s] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X, %d.%d.%d.%d->%d.%d.%d.%d, %s,IGMPType=%x\n"
                         ,&local_58,jiffies,param_2,param_3,pbVar10[6],pbVar10[7],pbVar10[8],
                         pbVar10[9],pbVar10[10],pbVar10[0xb],*pbVar10,pbVar10[1],pbVar10[2],
                         pbVar10[3],pbVar10[4],pbVar10[5],local_7c[0x1a],local_7c[0x1b],
                         local_7c[0x1c],local_7c[0x1d],local_7c[0x1e],local_7c[0x1f],local_7c[0x20],
                         local_7c[0x21],apcStack_48[iVar3],bVar1);
                }
                else {
                  printk("[%s]%8ld [%u][%s] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X, %d.%d.%d.%d->%d.%d.%d.%d, %s,IGMPType=%x,VID=%d\n"
                         ,&local_58,jiffies,param_2,param_3,pbVar10[6],pbVar10[7],pbVar10[8],
                         pbVar10[9],pbVar10[10],pbVar10[0xb],*pbVar10,pbVar10[1],pbVar10[2],
                         pbVar10[3],pbVar10[4],pbVar10[5],local_7c[0x1a],local_7c[0x1b],
                         local_7c[0x1c],local_7c[0x1d],local_7c[0x1e],local_7c[0x1f],local_7c[0x20],
                         local_7c[0x21],apcStack_48[iVar3],bVar1,local_74);
                }
              }
            }
          }
          else {
            printPING(local_7c,param_2,param_3,pbVar14,pbVar10,&local_58,local_74);
          }
        }
        else {
          countIP(local_7c,param_2,param_3,pbVar14,pbVar10,0,uVar12,local_74);
        }
      }
      goto LAB_000140e0;
    }
    uVar9 = (g_pktcnt_dbgflag << 0x1b) >> 0x1f;
    if (uVar15 != 0x806) {
      uVar9 = 0;
    }
    if (uVar9 != 0) {
      uVar9 = (*(ushort *)(local_7c + 0x14) & 0xff) << 8 | (uint)(*(ushort *)(local_7c + 0x14) >> 8)
      ;
      if (uVar9 - 1 < 2 && bVar17) {
        if (local_74 == 0xffffffff) {
          pcVar4 = "reply";
          if (uVar9 == 1) {
            pcVar4 = "request";
          }
          printk("[%s]%8ld [%u][%s] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X, arp %s, sender %02X:%02X:%02X:%02X:%02X:%02X(%d.%d.%d.%d), target %02X:%02X:%02X:%02X:%02X:%02X(%d.%d.%d.%d)\n"
                 ,&local_58,jiffies,param_2,param_3,pbVar10[6],pbVar10[7],pbVar10[8],pbVar10[9],
                 pbVar10[10],pbVar10[0xb],*pbVar10,pbVar10[1],pbVar10[2],pbVar10[3],pbVar10[4],
                 pbVar10[5],pcVar4,local_7c[0x16],local_7c[0x17],local_7c[0x18],local_7c[0x19],
                 local_7c[0x1a],local_7c[0x1b],local_7c[0x1c],local_7c[0x1d],local_7c[0x1e],
                 local_7c[0x1f],local_7c[0x20],local_7c[0x21],local_7c[0x22],local_7c[0x23],
                 local_7c[0x24],local_7c[0x25],local_7c[0x26],local_7c[0x27],local_7c[0x28],
                 local_7c[0x29]);
        }
        else {
          pcVar4 = "reply";
          if (uVar9 == 1) {
            pcVar4 = "request";
          }
          printk("[%s]%8ld [%u][%s] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X, arp %s, sender %02X:%02X:%02X:%02X:%02X:%02X(%d.%d.%d.%d), target %02X:%02X:%02X:%02X:%02X:%02X(%d.%d.%d.%d), VID=%d\n"
                 ,&local_58,jiffies,param_2,param_3,pbVar10[6],pbVar10[7],pbVar10[8],pbVar10[9],
                 pbVar10[10],pbVar10[0xb],*pbVar10,pbVar10[1],pbVar10[2],pbVar10[3],pbVar10[4],
                 pbVar10[5],pcVar4,local_7c[0x16],local_7c[0x17],local_7c[0x18],local_7c[0x19],
                 local_7c[0x1a],local_7c[0x1b],local_7c[0x1c],local_7c[0x1d],local_7c[0x1e],
                 local_7c[0x1f],local_7c[0x20],local_7c[0x21],local_7c[0x22],local_7c[0x23],
                 local_7c[0x24],local_7c[0x25],local_7c[0x26],local_7c[0x27],local_7c[0x28],
                 local_7c[0x29],local_74);
        }
      }
      goto LAB_000140e0;
    }
    if (uVar15 == 0x86dd) {
      bVar1 = local_7c[0x14];
      if (bVar1 == 0x11) {
        if ((g_pktcnt_dbgflag & 2) != 0) {
          countIPv6(local_7c,param_2,param_3,pbVar14,pbVar10,1,uVar12,local_74);
        }
        if ((g_pktcnt_dbgflag & 8) != 0) {
          printDHCPv6(local_7c,param_2,param_3,pbVar14,pbVar10,&local_58,local_74);
        }
      }
      else {
        if (bVar1 == 6) {
          uVar9 = g_pktcnt_dbgflag & 1;
        }
        else {
          uVar9 = 0;
        }
        if (uVar9 == 0) {
          uVar9 = (g_pktcnt_dbgflag << 0x1d) >> 0x1f;
          if (bVar1 != 0x3a) {
            uVar9 = 0;
          }
          if (uVar9 != 0) {
            printPINGv6(local_7c,param_2,param_3,pbVar14,pbVar10,&local_58,local_74);
          }
        }
        else {
          countIPv6(local_7c,param_2,param_3,pbVar14,pbVar10,0,uVar12,local_74);
        }
      }
      goto LAB_000140e0;
    }
    iVar3 = local_78;
    if (uVar15 == 0x893a) {
      if ((g_pktcnt_dbgflag & 0x80) != 0) {
        uVar8 = *(ushort *)(local_7c + 0x10) << 8 | *(ushort *)(local_7c + 0x10) >> 8;
        uVar7 = *(ushort *)(local_7c + 0x12) << 8 | *(ushort *)(local_7c + 0x12) >> 8;
        if (bVar17) {
          if (local_74 == 0xffffffff) {
            printk("[%s]%8ld [%u][%s] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X, pktLen=%d, 1905 type:0x%x, id=%d\n"
                   ,&local_58,jiffies,param_2,param_3,pbVar10[6],pbVar10[7],pbVar10[8],pbVar10[9],
                   pbVar10[10],pbVar10[0xb],*pbVar10,pbVar10[1],pbVar10[2],pbVar10[3],pbVar10[4],
                   pbVar10[5],uVar12,uVar8,uVar7);
          }
          else {
            printk("[%s]%8ld [%u][%s] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X,  pktLen=%d, 1905 type:0x%x, id=%d, VID=%d\n"
                   ,&local_58,jiffies,param_2,param_3,pbVar10[6],pbVar10[7],pbVar10[8],pbVar10[9],
                   pbVar10[10],pbVar10[0xb],*pbVar10,pbVar10[1],pbVar10[2],pbVar10[3],pbVar10[4],
                   pbVar10[5],uVar12,uVar8,uVar7,local_74);
          }
        }
        print_hex_dump(&_LC89,&_LC90,0,0x10,1,local_7c,uVar12,0);
      }
      goto LAB_000140e0;
    }
  }
  else {
    if (uVar15 == 0x9200 || (uVar7 & 0xfdff | uVar8) == 0x9100) {
      local_7c = pbVar10 + 8;
      local_78 = 0;
      local_74 = 0xffffffff;
      goto LAB_00013ebc;
    }
    if (uVar15 != 0x8864) {
      local_78 = 0;
      local_74 = 0xffffffff;
      local_7c = pbVar10;
      goto LAB_00013ebc;
    }
    local_7c = pbVar10 + 8;
    local_78 = 0;
    local_74 = 0xffffffff;
    iVar3 = 0;
    if (*(short *)(pbVar10 + 0x14) == 0x2100) goto LAB_0001408c;
  }
  local_78 = iVar3;
  if ((((((*local_7c == 0xff) && (local_7c[1] == 0xff)) && (local_7c[2] == 0xff)) &&
       ((local_7c[3] == 0xff && (local_7c[4] == 0xff)))) &&
      (((local_7c[5] == 0xff && ((local_7c[0xe] == 0 && (local_7c[0xf] == 1)))) &&
       (local_7c[0x10] == 0xaf)))) &&
     ((((local_7c[0x11] == 0x81 && (local_7c[0x12] == 1)) && (local_7c[0x13] == 2)) &&
      (((g_pktcnt_dbgflag & 0x100) != 0 && (bVar17)))))) {
    if (local_74 == 0xffffffff) {
      printk("[%s]%8ld [%u][%s] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X, pktLen=%d, pkt type:LLC\n"
             ,&local_58,jiffies,param_2,param_3,pbVar10[6],pbVar10[7],pbVar10[8],pbVar10[9],
             pbVar10[10],pbVar10[0xb],*pbVar10,pbVar10[1],pbVar10[2],pbVar10[3],pbVar10[4],
             pbVar10[5],uVar12);
    }
    else {
      printk("[%s]%8ld [%u][%s] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X, pktLen=%d, pkt type:LLC, VID=%d\n"
             ,&local_58,jiffies,param_2,param_3,pbVar10[6],pbVar10[7],pbVar10[8],pbVar10[9],
             pbVar10[10],pbVar10[0xb],*pbVar10,pbVar10[1],pbVar10[2],pbVar10[3],pbVar10[4],
             pbVar10[5],uVar12,local_74);
    }
  }
LAB_000140e0:
  if (((g_pktcnt_dbgflag & 0x40) != 0) && (g_pktcnt_dbgnum != 0)) {
    sVar13 = uVar12 * 3 + (uVar12 >> 4) + 0x2d;
    pcVar4 = (char *)__kmalloc(sVar13,0x20);
    if (pcVar4 == (char *)0x0) {
      printk("kmalloc fail\n");
      return 0xffffffff;
    }
    if (sVar13 != 0) {
      __memzero(pcVar4,sVar13);
    }
    g_count = g_count + 1;
    snprintf(pcVar4,7,"[%04u]");
    sVar5 = strnlen(pcVar4,sVar13);
    snprintf(pcVar4 + sVar5,0xe,"[pktlen=%04d]",uVar12);
    sVar5 = strnlen(pcVar4,sVar13);
    sVar6 = strnlen((char *)&local_58,0x10);
    snprintf(pcVar4 + sVar5,sVar6 + 5,"[%s]:\n",&local_58);
    uVar9 = g_pktprint_len;
    if (uVar12 <= g_pktprint_len) {
      uVar9 = uVar12;
    }
    if (local_78 != 0) {
      local_7c = local_7c + ~((local_78 - 1U & 0xff) << 2 ^ 3);
    }
    if (uVar9 != 0) {
      sVar5 = strnlen(pcVar4,sVar13);
      uVar12 = 1;
      snprintf(pcVar4 + sVar5,4,"%02x ",(uint)*local_7c);
      pbVar10 = local_7c + 1;
      while (uVar12 = uVar12 + 1, pbVar10 != local_7c + uVar9) {
        sVar5 = strnlen(pcVar4,sVar13);
        pbVar14 = pbVar10 + 1;
        snprintf(pcVar4 + sVar5,4,"%02x ",(uint)*pbVar10);
        pbVar10 = pbVar14;
        if ((uVar12 & 0xf) == 0) {
          sVar5 = strlen(pcVar4);
          (pcVar4 + sVar5)[0] = '\n';
          (pcVar4 + sVar5)[1] = '\0';
          uVar12 = 0;
        }
      }
      if ((uVar9 & 0xf) != 0) {
        sVar13 = strlen(pcVar4);
        (pcVar4 + sVar13)[0] = '\n';
        (pcVar4 + sVar13)[1] = '\0';
      }
    }
    printk(&_LC99,pcVar4);
    kfree(pcVar4);
    if ((g_pktcnt_dbgnum == 0) || (g_pktcnt_dbgnum = g_pktcnt_dbgnum + -1, g_pktcnt_dbgnum == 0)) {
      g_count = 0;
      return 0;
    }
  }
  return 0;
}

