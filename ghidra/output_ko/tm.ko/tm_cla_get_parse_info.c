// module: tm.ko
// function: tm_cla_get_parse_info @ 0x67a74
// size: 6600 bytes
//

undefined4 tm_cla_get_parse_info(byte *param_1,byte *param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  byte bVar10;
  byte bVar11;
  byte bVar12;
  char *pcVar13;
  byte *pbVar14;
  uint uVar15;
  byte *pbVar16;
  uint uVar17;
  byte *pbVar18;
  int iVar19;
  byte *pbVar20;
  int iVar21;
  byte *pbVar22;
  
  if (param_1 == (byte *)0x0) {
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[%s] input ERROR: flow_config=NULL\n","zte_sw_api.c");
    return 0xffffffff;
  }
  if (param_2 == (byte *)0x0) {
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[%s] input ERROR: cla_parse_info=NULL\n","zte_sw_api.c");
    return 0xffffffff;
  }
  if (0x10 < param_1[8]) {
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[%s] input ERROR: filed entrynum too large!filed entrynum=%d\n","zte_sw_api.c");
    return 0xffffffff;
  }
  bVar1 = *param_1;
  *(uint *)(param_2 + 0xc) = (uint)bVar1;
  uVar17 = g_tm_debug_level;
  if (bVar1 == 0x66) {
    g_macBind = 1;
    param_2[0x14] = 2;
    param_2[0x15] = 0;
    param_2[0x16] = 0;
    param_2[0x17] = 0;
  }
  else {
    g_macBind = 0;
  }
  if (1 < uVar17) {
    printk("TM_ACL_ruletype(0-L2 1-PRO 2-QoS 3-L3v4 4-L3v6) set value=%d\n",
           *(undefined4 *)(param_2 + 0xc));
  }
  *param_2 = param_1[1];
  if (g_tm_debug_level < 2) {
    if (*(int *)(param_1 + 4) != 0) {
      if (*(int *)(param_1 + 4) != 1) {
LAB_00067bc8:
        uVar17 = g_tm_debug_level;
        param_2[0x10] = 2;
        param_2[0x11] = 0;
        param_2[0x12] = 0;
        param_2[0x13] = 0;
        if (uVar17 < 2) {
          return 0xffffffff;
        }
        printk("TM_ACL_direction invalid direction!\n");
        return 0xffffffff;
      }
      param_2[0x10] = 1;
      param_2[0x11] = 0;
      param_2[0x12] = 0;
      param_2[0x13] = 0;
      param_2[8] = 5;
      param_2[9] = 0;
      param_2[10] = 0;
      param_2[0xb] = 0;
      goto LAB_00069224;
    }
    param_2[0x10] = 0;
    param_2[0x11] = 0;
    param_2[0x12] = 0;
    param_2[0x13] = 0;
LAB_00067b2c:
    if (param_1[8] != 0) goto LAB_00067b3c;
  }
  else {
    printk("TM_ACL_rulepri=%d\n");
    uVar17 = g_tm_debug_level;
    if (*(int *)(param_1 + 4) == 0) {
      param_2[0x10] = 0;
      param_2[0x11] = 0;
      param_2[0x12] = 0;
      param_2[0x13] = 0;
      if (uVar17 < 2) goto LAB_00067b2c;
      printk("TM_ACL_direction(0:up 1:down) =%d\n");
    }
    else {
      if (*(int *)(param_1 + 4) != 1) goto LAB_00067bc8;
      param_2[0x10] = 1;
      param_2[0x11] = 0;
      param_2[0x12] = 0;
      param_2[0x13] = 0;
      param_2[8] = 5;
      param_2[9] = 0;
      param_2[10] = 0;
      param_2[0xb] = 0;
      if (1 < uVar17) {
        printk("TM_ACL_srcport(1--8)=%d\n");
        if (g_tm_debug_level < 2) goto LAB_00067b2c;
        printk("TM_ACL_direction(0:up 1:dw)=%d\n",*(undefined4 *)(param_2 + 0x10));
      }
    }
LAB_00069224:
    if (param_1[8] != 0) {
LAB_00067b3c:
      pbVar20 = param_1 + 0x1f;
      iVar19 = 0;
      pbVar18 = param_1;
LAB_00067b50:
      uVar17 = g_tm_debug_level;
      switch(*(undefined4 *)(pbVar18 + 0xc)) {
      case 0:
        if (*(int *)(param_1 + 4) == 0) {
          uVar17 = (uint)pbVar18[0x1d] << 0x10 | (uint)pbVar18[0x1e] << 8 | (uint)pbVar18[0x1f] |
                   (uint)pbVar18[0x1c] << 0x18;
          if (uVar17 == 0x100000) {
            param_2[8] = 0x14;
            param_2[9] = 0;
            param_2[10] = 0;
            param_2[0xb] = 0;
            *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
          }
          else if ((int)uVar17 < 0x100001) {
            if (uVar17 == 8) {
              param_2[8] = 3;
              param_2[9] = 0;
              param_2[10] = 0;
              param_2[0xb] = 0;
              *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
            }
            else if ((int)uVar17 < 9) {
              if (uVar17 == 1) {
                param_2[8] = 0;
                param_2[9] = 0;
                param_2[10] = 0;
                param_2[0xb] = 0;
                *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
              }
              else if ((int)uVar17 < 2) {
                if (uVar17 != 0x80000000) {
LAB_00068cbc:
                  if (g_tm_debug_level == 0) {
                    return 0xffffffff;
                  }
                  printk("[%s] invalid UNIPORT!!!\n","zte_sw_api.c");
                  return 0xffffffff;
                }
                param_2[8] = 0x1f;
                param_2[9] = 0;
                param_2[10] = 0;
                param_2[0xb] = 0;
                *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
              }
              else if (uVar17 == 2) {
                param_2[8] = 1;
                param_2[9] = 0;
                param_2[10] = 0;
                param_2[0xb] = 0;
                *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
              }
              else {
                if (uVar17 != 4) goto LAB_00068cbc;
                param_2[8] = 2;
                param_2[9] = 0;
                param_2[10] = 0;
                param_2[0xb] = 0;
                *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
              }
            }
            else if (uVar17 == 0x20000) {
              param_2[8] = 0x11;
              param_2[9] = 0;
              param_2[10] = 0;
              param_2[0xb] = 0;
              *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
            }
            else if ((int)uVar17 < 0x20001) {
              if (uVar17 == 0x10) {
                param_2[8] = 4;
                param_2[9] = 0;
                param_2[10] = 0;
                param_2[0xb] = 0;
                *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
              }
              else {
                if (uVar17 != 0x10000) goto LAB_00068cbc;
                param_2[8] = 0x10;
                param_2[9] = 0;
                param_2[10] = 0;
                param_2[0xb] = 0;
                *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
              }
            }
            else if (uVar17 == 0x40000) {
              param_2[8] = 0x12;
              param_2[9] = 0;
              param_2[10] = 0;
              param_2[0xb] = 0;
              *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
            }
            else {
              if (uVar17 != 0x80000) goto LAB_00068cbc;
              param_2[8] = 0x13;
              param_2[9] = 0;
              param_2[10] = 0;
              param_2[0xb] = 0;
              *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
            }
          }
          else if (uVar17 == 0x2000000) {
            param_2[8] = 0x19;
            param_2[9] = 0;
            param_2[10] = 0;
            param_2[0xb] = 0;
            *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
          }
          else if ((int)uVar17 < 0x2000001) {
            if (uVar17 == 0x400000) {
              param_2[8] = 0x16;
              param_2[9] = 0;
              param_2[10] = 0;
              param_2[0xb] = 0;
              *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
            }
            else if ((int)uVar17 < 0x400001) {
              if (uVar17 != 0x200000) goto LAB_00068cbc;
              param_2[8] = 0x15;
              param_2[9] = 0;
              param_2[10] = 0;
              param_2[0xb] = 0;
              *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
            }
            else if (uVar17 == 0x800000) {
              param_2[8] = 0x17;
              param_2[9] = 0;
              param_2[10] = 0;
              param_2[0xb] = 0;
              *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
            }
            else {
              if (uVar17 != 0x1000000) goto LAB_00068cbc;
              param_2[8] = 0x18;
              param_2[9] = 0;
              param_2[10] = 0;
              param_2[0xb] = 0;
              *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
            }
          }
          else if (uVar17 == 0x10000000) {
            param_2[8] = 0x1c;
            param_2[9] = 0;
            param_2[10] = 0;
            param_2[0xb] = 0;
            *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
          }
          else if ((int)uVar17 < 0x10000001) {
            if (uVar17 == 0x4000000) {
              param_2[8] = 0x1a;
              param_2[9] = 0;
              param_2[10] = 0;
              param_2[0xb] = 0;
              *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
            }
            else {
              if (uVar17 != 0x8000000) goto LAB_00068cbc;
              param_2[8] = 0x1b;
              param_2[9] = 0;
              param_2[10] = 0;
              param_2[0xb] = 0;
              *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
            }
          }
          else if (uVar17 == 0x20000000) {
            param_2[8] = 0x1d;
            param_2[9] = 0;
            param_2[10] = 0;
            param_2[0xb] = 0;
            *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
          }
          else {
            if (uVar17 != 0x40000000) goto LAB_00068cbc;
            param_2[8] = 0x1e;
            param_2[9] = 0;
            param_2[10] = 0;
            param_2[0xb] = 0;
            *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
          }
          if (1 < g_tm_debug_level) {
            printk("TM_ACL_FIELD_UNIPORT=%d\n",*(undefined4 *)(param_2 + 8));
          }
        }
        else if (*(int *)(param_1 + 4) == 1) {
          uVar17 = (uint)pbVar18[0x1d] << 0x10 | (uint)pbVar18[0x1e] << 8 | (uint)pbVar18[0x1f] |
                   (uint)pbVar18[0x1c] << 0x18;
          if (uVar17 == 0x100000) {
            param_2[0xb5] = 0x14;
            *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
          }
          else if ((int)uVar17 < 0x100001) {
            if (uVar17 == 8) {
              param_2[0xb5] = 3;
              *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
            }
            else if ((int)uVar17 < 9) {
              if (uVar17 == 1) {
                param_2[0xb5] = 0;
                *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
              }
              else if ((int)uVar17 < 2) {
                if (uVar17 != 0x80000000) {
LAB_00068ef8:
                  if (g_tm_debug_level == 0) {
                    return 0xffffffff;
                  }
                  printk("[%s]tm_cla_get_parse_info invalid UNIPORT!!!\n","zte_sw_api.c");
                  return 0xffffffff;
                }
                param_2[0xb5] = 0x1f;
                *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
              }
              else if (uVar17 == 2) {
                param_2[0xb5] = 1;
                *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
              }
              else {
                if (uVar17 != 4) goto LAB_00068ef8;
                param_2[0xb5] = 2;
                *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
              }
            }
            else if (uVar17 == 0x20000) {
              param_2[0xb5] = 0x11;
              *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
            }
            else if ((int)uVar17 < 0x20001) {
              if (uVar17 == 0x10) {
                param_2[0xb5] = 4;
                *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
              }
              else {
                if (uVar17 != 0x10000) goto LAB_00068ef8;
                param_2[0xb5] = 0x10;
                *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
              }
            }
            else if (uVar17 == 0x40000) {
              param_2[0xb5] = 0x12;
              *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
            }
            else {
              if (uVar17 != 0x80000) goto LAB_00068ef8;
              param_2[0xb5] = 0x13;
              *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
            }
          }
          else if (uVar17 == 0x2000000) {
            param_2[0xb5] = 0x19;
            *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
          }
          else if ((int)uVar17 < 0x2000001) {
            if (uVar17 == 0x400000) {
              param_2[0xb5] = 0x16;
              *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
            }
            else if ((int)uVar17 < 0x400001) {
              if (uVar17 != 0x200000) goto LAB_00068ef8;
              param_2[0xb5] = 0x15;
              *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
            }
            else if (uVar17 == 0x800000) {
              param_2[0xb5] = 0x17;
              *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
            }
            else {
              if (uVar17 != 0x1000000) goto LAB_00068ef8;
              param_2[0xb5] = 0x18;
              *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
            }
          }
          else if (uVar17 == 0x10000000) {
            param_2[0xb5] = 0x1c;
            *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
          }
          else if ((int)uVar17 < 0x10000001) {
            if (uVar17 == 0x4000000) {
              param_2[0xb5] = 0x1a;
              *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
            }
            else {
              if (uVar17 != 0x8000000) goto LAB_00068ef8;
              param_2[0xb5] = 0x1b;
              *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
            }
          }
          else if (uVar17 == 0x20000000) {
            param_2[0xb5] = 0x1d;
            *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
          }
          else {
            if (uVar17 != 0x40000000) goto LAB_00068ef8;
            param_2[0xb5] = 0x1e;
            *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400000;
          }
          if (1 < g_tm_debug_level) {
            printk("TM_ACL_FIELD_UNIPORT=%d\n",param_2[0xb5]);
          }
        }
        break;
      case 1:
        if (*(int *)(param_1 + 4) == 1) {
          param_2[8] = 5;
          param_2[9] = 0;
          param_2[10] = 0;
          param_2[0xb] = 0;
          *(ushort *)(param_2 + 6) = CONCAT11(pbVar18[0x1e],pbVar18[0x1f]);
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x800000;
          if ((1 < uVar17) && (printk("TM_ACL_srcport=%d\n"), 1 < g_tm_debug_level)) {
            printk("TM_ACL_FIELD_PONPORT gemportID=%d\n",*(undefined2 *)(param_2 + 6));
          }
        }
        break;
      case 2:
        pbVar22 = param_2 + 0x27;
        pbVar14 = param_2 + 0x2d;
        iVar21 = 0;
        *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 1;
        pbVar16 = pbVar18;
        do {
          iVar21 = iVar21 + 1;
          pbVar22 = pbVar22 + 1;
          *pbVar22 = pbVar16[0x1a];
          pbVar14 = pbVar14 + 1;
          *pbVar14 = pbVar16[0x2a];
          pbVar16 = pbVar16 + 1;
        } while (iVar21 != 6);
        if (1 < g_tm_debug_level) {
          bVar2 = param_2[0x2d];
          bVar3 = param_2[0x2b];
          uVar17 = 0x7270;
          bVar4 = param_2[0x2c];
          bVar5 = param_2[0x28];
          bVar6 = param_2[0x29];
          bVar7 = param_2[0x2a];
          bVar8 = param_2[0x2e];
          bVar9 = param_2[0x2f];
          bVar10 = param_2[0x30];
          bVar11 = param_2[0x31];
          bVar12 = param_2[0x32];
          bVar1 = param_2[0x33];
LAB_00068108:
          printk(uVar17 | 0xa0000,bVar5,bVar6,bVar7,bVar3,bVar4,bVar2,bVar8,bVar9,bVar10,bVar11,
                 bVar12,bVar1);
        }
        break;
      case 3:
        pbVar22 = param_2 + 0x33;
        pbVar14 = param_2 + 0x39;
        iVar21 = 0;
        *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 2;
        pbVar16 = pbVar18;
        do {
          iVar21 = iVar21 + 1;
          pbVar22 = pbVar22 + 1;
          *pbVar22 = pbVar16[0x1a];
          pbVar14 = pbVar14 + 1;
          *pbVar14 = pbVar16[0x2a];
          pbVar16 = pbVar16 + 1;
        } while (iVar21 != 6);
        if (1 < g_tm_debug_level) {
          bVar2 = param_2[0x39];
          bVar3 = param_2[0x37];
          uVar17 = 0x72b8;
          bVar4 = param_2[0x38];
          bVar5 = param_2[0x34];
          bVar6 = param_2[0x35];
          bVar7 = param_2[0x36];
          bVar8 = param_2[0x3a];
          bVar9 = param_2[0x3b];
          bVar10 = param_2[0x3c];
          bVar11 = param_2[0x3d];
          bVar12 = param_2[0x3e];
          bVar1 = param_2[0x3f];
          goto LAB_00068108;
        }
        break;
      case 4:
        *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 4;
        param_2[1] = pbVar18[0x1f];
        if (1 < g_tm_debug_level) {
          printk("SW_ACL_FIELD_TAG_LEVEL(0-untag 1-prio tag 2-single 3-double 4-three 5-four)=%d\n")
          ;
        }
        break;
      case 5:
        *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 8;
        *(ushort *)(param_2 + 0x40) = CONCAT11(pbVar18[0x1e],pbVar18[0x1f]);
        if (1 < uVar17) {
          printk("SW_ACL_FIELD_OUTERTPID=0x%x\n");
        }
        break;
      case 6:
        if (pbVar18[0x2c] == 0xff) {
          param_2[0x45] = pbVar18[0x1c];
          *(ushort *)(param_2 + 0x46) = *(ushort *)(param_2 + 0x46) | 0xe000;
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x10;
          if (1 < uVar17) {
            printk("SW_ACL_FIELD_OUTERTAG PRI=%d mask=0x%x\n");
          }
        }
        uVar17 = g_tm_debug_level;
        if (pbVar18[0x2d] == 0xff) {
          param_2[0x44] = pbVar18[0x1d];
          *(ushort *)(param_2 + 0x46) = *(ushort *)(param_2 + 0x46) | 0x1000;
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x10;
          if (1 < uVar17) {
            printk("SW_ACL_FIELD_OUTERTAG CFI=%d mask=0x%x\n");
          }
        }
        uVar17 = g_tm_debug_level;
        if ((pbVar18[0x2e] == 0xff) && (pbVar18[0x2f] == 0xff)) {
          bVar1 = pbVar18[0x1e];
          bVar12 = pbVar18[0x1f];
          *(ushort *)(param_2 + 0x46) = ~(~(*(ushort *)(param_2 + 0x46) >> 0xc) << 0xc);
          *(ushort *)(param_2 + 0x42) = CONCAT11(bVar1,bVar12);
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x10;
          if (1 < uVar17) {
            printk("SW_ACL_FIELD_OUTERTAG VID=%d mask=0x%x\n");
          }
        }
        break;
      case 7:
        *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x20;
        *(ushort *)(param_2 + 0x48) = CONCAT11(pbVar18[0x1e],pbVar18[0x1f]);
        if (1 < uVar17) {
          printk("SW_ACL_FIELD_INNERTPID=0x%x\n");
        }
        break;
      case 8:
        if (pbVar18[0x2c] == 0xff) {
          param_2[0x4d] = pbVar18[0x1c];
          *(ushort *)(param_2 + 0x4e) = *(ushort *)(param_2 + 0x4e) | 0xe000;
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x40;
          if (1 < uVar17) {
            printk("SW_ACL_FIELD_INNERTAG PRI=%d mask=0x%x\n");
          }
        }
        uVar17 = g_tm_debug_level;
        if (pbVar18[0x2d] == 0xff) {
          param_2[0x4c] = pbVar18[0x1d];
          *(ushort *)(param_2 + 0x4e) = *(ushort *)(param_2 + 0x4e) | 0x1000;
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x40;
          if (1 < uVar17) {
            printk("SW_ACL_FIELD_INNERTAG CFI=%d mask=0x%x\n");
          }
        }
        uVar17 = g_tm_debug_level;
        if ((pbVar18[0x2e] == 0xff) && (pbVar18[0x2f] == 0xff)) {
          bVar1 = pbVar18[0x1e];
          bVar12 = pbVar18[0x1f];
          *(ushort *)(param_2 + 0x4e) = ~(~(*(ushort *)(param_2 + 0x4e) >> 0xc) << 0xc);
          *(ushort *)(param_2 + 0x4a) = CONCAT11(bVar1,bVar12);
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x40;
          if (1 < uVar17) {
            printk("SW_ACL_FIELD_INNERTAG VID=%d mask=0x%x\n");
          }
        }
        break;
      case 9:
        *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x80;
        *(ushort *)(param_2 + 0x52) = CONCAT11(pbVar18[0x1e],pbVar18[0x1f]);
        if (1 < uVar17) {
          printk("SW_ACL_FIELD_ETHERTYPE=0x%x\n");
        }
        break;
      case 10:
        if (pbVar18[0x1f] == 4) {
          param_2[99] = 4;
          param_2[0x5c] = 1;
          param_2[0x5d] = 0;
          param_2[0x5e] = 0;
          param_2[0x5f] = 0;
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x100;
          if ((1 < uVar17) && (printk("SW_ACL_FIELD_IP_VERSION ipType=%d\n"), 1 < g_tm_debug_level))
          {
            printk("SW_ACL_FIELD_IPV4_VERSION version=%d\n",param_2[99]);
          }
        }
        else {
          param_2[0x5c] = 2;
          param_2[0x5d] = 0;
          param_2[0x5e] = 0;
          param_2[0x5f] = 0;
          param_2[0x60] = 6;
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x20000;
          if (1 < uVar17) {
            printk("SW_ACL_FIELD_IP_VERSION ipType=%d\n");
          }
        }
        break;
      case 0xb:
        param_2[0x5c] = 1;
        param_2[0x5d] = 0;
        param_2[0x5e] = 0;
        param_2[0x5f] = 0;
        if (uVar17 < 2) {
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x800;
          param_2[0x60] = pbVar18[0x1f];
        }
        else {
          printk("SW_ACL_FIELD_IP_VERSION ipType=%d\n");
          uVar17 = g_tm_debug_level;
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x800;
          param_2[0x60] = pbVar18[0x1f];
          if (1 < uVar17) {
            printk("SW_ACL_FIELD_IPV4_TOS=%d\n");
          }
        }
        break;
      case 0xc:
        param_2[0x5c] = 1;
        param_2[0x5d] = 0;
        param_2[0x5e] = 0;
        param_2[0x5f] = 0;
        if (uVar17 < 2) {
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x1000;
          param_2[0x62] = pbVar18[0x1f];
        }
        else {
          printk("SW_ACL_FIELD_IP_VERSION ipType=%d\n");
          uVar17 = g_tm_debug_level;
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x1000;
          param_2[0x62] = pbVar18[0x1f];
          if (1 < uVar17) {
            printk("SW_ACL_FIELD_IPV4_PROTOCOL=%d\n");
          }
        }
        break;
      case 0xd:
        param_2[0x5c] = 1;
        param_2[0x5d] = 0;
        param_2[0x5e] = 0;
        param_2[0x5f] = 0;
        if (1 < uVar17) {
          printk("SW_ACL_FIELD_IP_VERSION ipType=%d\n");
          uVar17 = g_tm_debug_level;
        }
        pbVar22 = param_2 + 0x6b;
        pbVar14 = param_2 + 0x6f;
        iVar21 = 0;
        *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x400;
        pbVar16 = pbVar18;
        do {
          iVar21 = iVar21 + 1;
          pbVar22 = pbVar22 + 1;
          *pbVar22 = pbVar16[0x1c];
          pbVar14 = pbVar14 + 1;
          *pbVar14 = pbVar16[0x2c];
          pbVar16 = pbVar16 + 1;
        } while (iVar21 != 4);
        if (1 < uVar17) {
          bVar6 = param_2[0x71];
          bVar7 = param_2[0x6f];
          pcVar13 = "SW_ACL_FIELD_IPV4_DIP=%d.%d.%d.%d mask=%x.%x.%x.%x\n";
          bVar8 = param_2[0x6c];
          bVar9 = param_2[0x6d];
          bVar10 = param_2[0x6e];
          bVar11 = param_2[0x70];
          bVar12 = param_2[0x72];
          bVar1 = param_2[0x73];
LAB_0006804c:
          printk(pcVar13,bVar8,bVar9,bVar10,bVar7,bVar11,bVar6,bVar12,bVar1);
        }
        break;
      case 0xe:
        param_2[0x5c] = 1;
        param_2[0x5d] = 0;
        param_2[0x5e] = 0;
        param_2[0x5f] = 0;
        if (1 < uVar17) {
          printk("SW_ACL_FIELD_IP_VERSION ipType=%d\n");
          uVar17 = g_tm_debug_level;
        }
        pbVar22 = param_2 + 99;
        pbVar14 = param_2 + 0x67;
        iVar21 = 0;
        *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x200;
        pbVar16 = pbVar18;
        do {
          iVar21 = iVar21 + 1;
          pbVar22 = pbVar22 + 1;
          *pbVar22 = pbVar16[0x1c];
          pbVar14 = pbVar14 + 1;
          *pbVar14 = pbVar16[0x2c];
          pbVar16 = pbVar16 + 1;
        } while (iVar21 != 4);
        if (1 < uVar17) {
          bVar6 = param_2[0x69];
          bVar7 = param_2[0x67];
          pcVar13 = "SW_ACL_FIELD_IPV4_SIP=%d.%d.%d.%d mask=%x.%x.%x.%x\n";
          bVar8 = param_2[100];
          bVar9 = param_2[0x65];
          bVar10 = param_2[0x66];
          bVar11 = param_2[0x68];
          bVar12 = param_2[0x6a];
          bVar1 = param_2[0x6b];
          goto LAB_0006804c;
        }
        break;
      case 0xf:
        param_2[0x5c] = 2;
        param_2[0x5d] = 0;
        param_2[0x5e] = 0;
        param_2[0x5f] = 0;
        if (uVar17 < 2) {
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x40000;
          param_2[99] = pbVar18[0x1f];
        }
        else {
          printk("SW_ACL_FIELD_IP_VERSION ipType=%d\n");
          uVar17 = g_tm_debug_level;
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x40000;
          param_2[99] = pbVar18[0x1f];
          if (1 < uVar17) {
            printk("SW_ACL_FIELD_IPV6_NEXTHEADER=%d\n");
          }
        }
        break;
      case 0x10:
        param_2[0x5c] = 2;
        param_2[0x5d] = 0;
        param_2[0x5e] = 0;
        param_2[0x5f] = 0;
        if (uVar17 < 2) {
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x10000;
          param_2[0x61] = pbVar18[0x1f];
        }
        else {
          printk("SW_ACL_FIELD_IP_VERSION ipType=%d\n");
          uVar17 = g_tm_debug_level;
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x10000;
          param_2[0x61] = pbVar18[0x1f];
          if (1 < uVar17) {
            printk("SW_ACL_FIELD_IPV6_TRAFFIC_CLASS=%d\n");
          }
        }
        break;
      case 0x11:
        param_2[0x5c] = 2;
        param_2[0x5d] = 0;
        param_2[0x5e] = 0;
        param_2[0x5f] = 0;
        if (1 < uVar17) {
          printk("SW_ACL_FIELD_IP_VERSION ipType=%d\n");
          uVar17 = g_tm_debug_level;
        }
        *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x8000;
        *(uint *)(param_2 + 100) =
             (uint)CONCAT12(pbVar18[0x1d],CONCAT11(pbVar18[0x1e],pbVar18[0x1f]));
        if (1 < uVar17) {
          printk("SW_ACL_FIELD_IPV6_FLOWLABEL=%d\n");
        }
        break;
      case 0x12:
        param_2[0x5c] = 2;
        param_2[0x5d] = 0;
        param_2[0x5e] = 0;
        param_2[0x5f] = 0;
        if (uVar17 < 2) {
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x4000;
        }
        else {
          printk("SW_ACL_FIELD_IP_VERSION ipType=%d\n");
          uVar17 = g_tm_debug_level;
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x4000;
          if (1 < uVar17) {
            printk("SW_ACL_FIELD_IPV6_DIPV6=\nvalue:");
            uVar17 = g_tm_debug_level;
          }
        }
        pbVar22 = pbVar18 + 0xf;
        pbVar16 = param_2 + 0x87;
        iVar21 = 0;
        do {
          pbVar22 = pbVar22 + 1;
          pbVar16 = pbVar16 + 1;
          *pbVar16 = *pbVar22;
          if (uVar17 < 2) {
            if (iVar21 == 0xf) {
LAB_00069098:
              uVar17 = g_tm_debug_level;
              if (1 < g_tm_debug_level) {
                printk(&_LC193);
                uVar17 = g_tm_debug_level;
              }
              break;
            }
          }
          else {
            printk(&_LC250);
            if (iVar21 == 0xf) goto LAB_00069098;
            uVar17 = g_tm_debug_level;
            if (1 < g_tm_debug_level) {
              printk(&_LC251);
              uVar17 = g_tm_debug_level;
            }
          }
          iVar21 = iVar21 + 1;
        } while (iVar21 != 0x10);
        if (1 < uVar17) {
          printk("mask :");
          uVar17 = g_tm_debug_level;
        }
        pbVar22 = param_2 + 0x97;
        iVar21 = 0;
        pbVar16 = pbVar20;
        do {
          pbVar16 = pbVar16 + 1;
          pbVar22 = pbVar22 + 1;
          *pbVar22 = *pbVar16;
          if (uVar17 < 2) {
            if (iVar21 == 0xf) goto LAB_00068eac;
          }
          else {
            printk(&_LC250);
            if (iVar21 == 0xf) goto LAB_00068eac;
            if (1 < g_tm_debug_level) {
              printk(&_LC251);
            }
          }
          iVar21 = iVar21 + 1;
          uVar17 = g_tm_debug_level;
        } while (iVar21 != 0x10);
        break;
      case 0x13:
        param_2[0x5c] = 2;
        param_2[0x5d] = 0;
        param_2[0x5e] = 0;
        param_2[0x5f] = 0;
        if (uVar17 < 2) {
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x2000;
        }
        else {
          printk("SW_ACL_FIELD_IP_VERSION ipType=%d\n");
          uVar17 = g_tm_debug_level;
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x2000;
          if (1 < uVar17) {
            printk("SW_ACL_FIELD_IPV6_SIPV6=\nvalue:");
            uVar17 = g_tm_debug_level;
          }
        }
        pbVar22 = pbVar18 + 0xf;
        pbVar16 = param_2 + 0x67;
        iVar21 = 0;
        do {
          pbVar22 = pbVar22 + 1;
          pbVar16 = pbVar16 + 1;
          *pbVar16 = *pbVar22;
          if (uVar17 < 2) {
            if (iVar21 == 0xf) {
LAB_000690d0:
              uVar17 = g_tm_debug_level;
              if (1 < g_tm_debug_level) {
                printk(&_LC193);
                uVar17 = g_tm_debug_level;
              }
              break;
            }
          }
          else {
            printk(&_LC250);
            if (iVar21 == 0xf) goto LAB_000690d0;
            uVar17 = g_tm_debug_level;
            if (1 < g_tm_debug_level) {
              printk(&_LC251);
              uVar17 = g_tm_debug_level;
            }
          }
          iVar21 = iVar21 + 1;
        } while (iVar21 != 0x10);
        if (1 < uVar17) {
          printk("mask :");
          uVar17 = g_tm_debug_level;
        }
        pbVar22 = param_2 + 0x77;
        iVar21 = 0;
        pbVar16 = pbVar20;
        do {
          pbVar16 = pbVar16 + 1;
          pbVar22 = pbVar22 + 1;
          *pbVar22 = *pbVar16;
          if (uVar17 < 2) {
            if (iVar21 == 0xf) goto LAB_00068eac;
          }
          else {
            printk(&_LC250);
            if (iVar21 == 0xf) goto LAB_00068eac;
            if (1 < g_tm_debug_level) {
              printk(&_LC251);
            }
          }
          iVar21 = iVar21 + 1;
          uVar17 = g_tm_debug_level;
        } while (iVar21 != 0x10);
        break;
      case 0x14:
        *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x200000;
        uVar17 = g_tm_debug_level;
        if (*(int *)(param_2 + 0x5c) == 2) {
          *(ushort *)(param_2 + 0xaa) = CONCAT11(pbVar18[0x1e],pbVar18[0x1f]);
          if (1 < uVar17) {
            printk("SW_ACL_FIELD_L4_DPORT v6 set value=%d\n");
          }
        }
        else {
          param_2[0x5c] = 1;
          param_2[0x5d] = 0;
          param_2[0x5e] = 0;
          param_2[0x5f] = 0;
          *(ushort *)(param_2 + 0x76) = CONCAT11(pbVar18[0x1e],pbVar18[0x1f]);
          if (1 < uVar17) {
            printk("SW_ACL_FIELD_L4_DPORT v4 set value=%d\n");
          }
        }
        break;
      case 0x15:
        *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x100000;
        uVar17 = g_tm_debug_level;
        if (*(int *)(param_2 + 0x5c) == 2) {
          *(ushort *)(param_2 + 0xa8) = CONCAT11(pbVar18[0x1e],pbVar18[0x1f]);
          if (1 < uVar17) {
            printk("SW_ACL_FIELD_L4_SPORT v6 set value=%d\n");
          }
        }
        else {
          param_2[0x5c] = 1;
          param_2[0x5d] = 0;
          param_2[0x5e] = 0;
          param_2[0x5f] = 0;
          *(ushort *)(param_2 + 0x74) = CONCAT11(pbVar18[0x1e],pbVar18[0x1f]);
          if (1 < uVar17) {
            printk("SW_ACL_FIELD_L4_SPORT v4 set value=%d\n");
          }
        }
        break;
      case 0x16:
        param_2[0x5c] = 2;
        param_2[0x5d] = 0;
        param_2[0x5e] = 0;
        param_2[0x5f] = 0;
        if (uVar17 < 2) {
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x80000;
          param_2[0xac] = pbVar18[0x1f];
        }
        else {
          printk("SW_ACL_FIELD_IP_VERSION ipType=%d\n");
          uVar17 = g_tm_debug_level;
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x80000;
          param_2[0xac] = pbVar18[0x1f];
          if (1 < uVar17) {
            printk("SW_ACL_FIELD_IPV6_SECONDHEADER=%d\n");
          }
        }
        break;
      case 0x17:
        if ((pbVar18[0x2e] == 0xff) && (pbVar18[0x2f] == 0xff)) {
          param_2[0x5a] = 0;
          param_2[0x5b] = 0;
          param_2[0x59] = 0;
          param_2[0x58] = 0;
          bVar1 = pbVar18[0x1e];
          bVar12 = pbVar18[0x1f];
          param_2[0x5a] = 0xff;
          param_2[0x5b] = 0xf;
          *(ushort *)(param_2 + 0x56) = CONCAT11(bVar1,bVar12);
          *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x1000000;
          if (6 < uVar17) {
            printk("SW_ACL_FIELD_OUTERTAG VID=%d mask=0x%x\n",*(undefined2 *)(param_2 + 0x42),
                   *(undefined2 *)(param_2 + 0x46));
          }
        }
        break;
      default:
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        printk("[%s] invalid field!!!\n","zte_sw_api.c");
        return 0xffffffff;
      }
      goto LAB_00067c58;
    }
LAB_00067c70:
    if (1 < g_tm_debug_level) {
      printk("[%s] output: parsemask=0x%x\n","zte_sw_api.c",*(undefined4 *)(param_2 + 0x1c));
    }
  }
  uVar17 = g_tm_debug_level;
  switch(*(undefined4 *)(param_1 + 0x24c)) {
  case 0:
    param_2[0x18] = 2;
    param_2[0x19] = 0;
    param_2[0x1a] = 0;
    param_2[0x1b] = 0;
    break;
  case 1:
  case 2:
    param_2[0x18] = 0;
    param_2[0x19] = 0;
    param_2[0x1a] = 0;
    param_2[0x1b] = 0;
    break;
  case 3:
    param_2[0x18] = 1;
    param_2[0x19] = 0;
    param_2[0x1a] = 0;
    param_2[0x1b] = 0;
    break;
  default:
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[%s] invalid fwdmode!!!\n","zte_sw_api.c");
    return 0xffffffff;
  }
  if (uVar17 < 2) {
    param_2[0xb1] = param_1[0x256];
  }
  else {
    printk("SW_ACL_FWD mode(0-fwd 1-trap 2-drop)=%d\n",*(undefined4 *)(param_2 + 0x18));
    uVar17 = g_tm_debug_level;
    param_2[0xb1] = param_1[0x256];
    if (1 < uVar17) {
      printk("SW_ACL_FWD trgqueue=%d\n");
    }
  }
  iVar19 = *(int *)(param_1 + 4);
  if (iVar19 == 1) {
    uVar17 = *(uint *)(param_1 + 0x250);
    if (uVar17 == 0) {
      return 0;
    }
    if (uVar17 == 0x100000) {
      param_2[0xb2] = 0x14;
      param_2[0xb3] = 0;
    }
    else if (uVar17 < 0x100001) {
      if (uVar17 == 0x40) {
        param_2[0xb2] = 6;
        param_2[0xb3] = 0;
      }
      else if (uVar17 < 0x41) {
        if (uVar17 == 4) {
          param_2[0xb2] = 2;
          param_2[0xb3] = 0;
        }
        else if (uVar17 < 5) {
          if (uVar17 == 1) {
            param_2[0xb2] = 0;
            param_2[0xb3] = 0;
          }
          else {
            if (uVar17 != 2) {
LAB_00068b24:
              if (g_tm_debug_level != 0) {
                printk("[%s]sw_cla_get_parse_info invalid Fwd_gemport: desportmsk=0x%x!\n",
                       "zte_sw_api.c");
              }
              return 0xffffffff;
            }
            param_2[0xb2] = 1;
            param_2[0xb3] = 0;
          }
        }
        else if (uVar17 == 8) {
          param_2[0xb2] = 3;
          param_2[0xb3] = 0;
        }
        else {
          if (uVar17 != 0x10) goto LAB_00068b24;
          param_2[0xb2] = 4;
          param_2[0xb3] = 0;
        }
      }
      else if (uVar17 == 0x20000) {
        param_2[0xb2] = 0x11;
        param_2[0xb3] = 0;
      }
      else if (uVar17 < 0x20001) {
        if (uVar17 == 0x80) {
          param_2[0xb2] = 7;
          param_2[0xb3] = 0;
        }
        else {
          if (uVar17 != 0x10000) goto LAB_00068b24;
          param_2[0xb2] = 0x10;
          param_2[0xb3] = 0;
        }
      }
      else if (uVar17 == 0x40000) {
        param_2[0xb2] = 0x12;
        param_2[0xb3] = 0;
      }
      else {
        if (uVar17 != 0x80000) goto LAB_00068b24;
        param_2[0xb2] = 0x13;
        param_2[0xb3] = 0;
      }
    }
    else if (uVar17 == 0x4000000) {
      param_2[0xb2] = 0x1a;
      param_2[0xb3] = 0;
    }
    else if (uVar17 < 0x4000001) {
      if (uVar17 == 0x800000) {
        param_2[0xb2] = 0x17;
        param_2[0xb3] = 0;
      }
      else if (uVar17 < 0x800001) {
        if (uVar17 == 0x200000) {
          param_2[0xb2] = 0x15;
          param_2[0xb3] = 0;
        }
        else {
          if (uVar17 != 0x400000) goto LAB_00068b24;
          param_2[0xb2] = 0x16;
          param_2[0xb3] = 0;
        }
      }
      else if (uVar17 == 0x1000000) {
        param_2[0xb2] = 0x18;
        param_2[0xb3] = 0;
      }
      else {
        if (uVar17 != 0x2000000) goto LAB_00068b24;
        param_2[0xb2] = 0x19;
        param_2[0xb3] = 0;
      }
    }
    else if (uVar17 == 0x20000000) {
      param_2[0xb2] = 0x1d;
      param_2[0xb3] = 0;
    }
    else if (uVar17 < 0x20000001) {
      if (uVar17 == 0x8000000) {
        param_2[0xb2] = 0x1b;
        param_2[0xb3] = 0;
      }
      else {
        if (uVar17 != 0x10000000) goto LAB_00068b24;
        param_2[0xb2] = 0x1c;
        param_2[0xb3] = 0;
      }
    }
    else if (uVar17 == 0x40000000) {
      param_2[0xb2] = 0x1e;
      param_2[0xb3] = 0;
    }
    else {
      if (uVar17 != 0x80000000) goto LAB_00068b24;
      param_2[0xb2] = 0x1f;
      param_2[0xb3] = 0;
    }
    if (1 < g_tm_debug_level) {
      printk("SW_ACL_FWD trggemport=%d\n",*(undefined2 *)(param_2 + 0xb2));
    }
    iVar19 = *(int *)(param_1 + 4);
  }
  uVar17 = g_tm_debug_level;
  if (iVar19 == 0) {
    *(undefined2 *)(param_2 + 0xb2) = *(undefined2 *)(param_1 + 0x254);
    if (uVar17 < 2) {
      param_2[0xb0] = (byte)*(undefined4 *)(param_1 + 0x250);
    }
    else {
      printk("SW_ACL_FWD trggemport=%d\n");
      uVar17 = g_tm_debug_level;
      uVar15 = *(uint *)(param_1 + 0x250);
      param_2[0xb0] = (byte)uVar15;
      if (1 < uVar17) {
        printk("SW_ACL_FWD trgport=%d\n",uVar15 & 0xff);
        return 0;
      }
    }
  }
  return 0;
LAB_00068eac:
  if (1 < g_tm_debug_level) {
    printk(&_LC193);
  }
LAB_00067c58:
  iVar19 = iVar19 + 1;
  pbVar18 = pbVar18 + 0x24;
  pbVar20 = pbVar20 + 0x24;
  if ((int)(uint)param_1[8] <= iVar19) goto LAB_00067c70;
  goto LAB_00067b50;
}

