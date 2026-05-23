// module: tm.ko
// function: aclBuildHashAndAclRule @ 0x5cc20
// size: 5960 bytes
//

undefined4
aclBuildHashAndAclRule
          (byte *param_1,ushort *param_2,uint param_3,int param_4,int param_5,undefined4 *param_6,
          uint *param_7)

{
  byte bVar1;
  ushort uVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  undefined3 uVar7;
  undefined4 uVar8;
  undefined1 uVar9;
  undefined1 uVar10;
  undefined4 *puVar11;
  uint uVar12;
  int iVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  uint uVar16;
  undefined4 uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  int iVar21;
  uint uVar22;
  undefined4 *puVar23;
  uint uVar24;
  undefined4 *puVar25;
  undefined4 *puVar26;
  uint uVar27;
  uint local_bc;
  uint local_b8;
  undefined1 auStack_b4 [35];
  byte local_91;
  undefined1 local_90;
  byte local_8f;
  byte local_8e;
  byte local_8d;
  undefined1 local_8c;
  byte local_8b;
  undefined1 local_8a;
  byte local_89;
  undefined1 local_88;
  byte local_87;
  undefined1 local_86;
  byte local_85;
  undefined1 local_84;
  byte local_83;
  undefined1 local_82;
  byte local_81;
  undefined1 local_80;
  byte local_7f;
  undefined1 local_7e;
  byte local_7d;
  undefined1 local_7c;
  byte local_7b;
  undefined1 local_7a;
  byte local_79;
  undefined1 local_78;
  byte local_77;
  undefined1 local_76;
  byte local_75;
  undefined1 local_74;
  byte local_73;
  undefined1 local_72;
  byte local_71;
  undefined1 local_70;
  byte local_6f;
  undefined1 local_6e;
  byte local_6d;
  undefined1 local_6c;
  byte local_6b;
  undefined1 local_6a;
  byte local_69;
  undefined1 local_68;
  byte local_67;
  undefined1 local_66;
  byte local_65;
  undefined4 local_64;
  undefined1 local_60;
  byte local_5f;
  ushort local_5e;
  undefined4 local_5c;
  undefined4 local_58;
  byte local_54 [3];
  undefined1 uStack_51;
  byte bStack_50;
  ushort local_4f;
  undefined1 local_4d [2];
  ushort local_4b;
  ushort local_49;
  ushort local_47;
  ushort local_45;
  ushort local_43;
  ushort local_41;
  ushort local_3f;
  ushort local_3d;
  ushort local_3b;
  ushort local_39;
  ushort local_37;
  ushort local_35;
  ushort local_33;
  ushort local_31;
  ushort local_2f;
  ushort local_2d;
  ushort local_2b;
  
  local_b8 = 0;
  if (param_7 == (uint *)0x0 || param_6 == (undefined4 *)0x0) {
    printk("ERROR:(%s:%d)","tm_acl_v2.c",0x7a7);
    printk("param pp_hashEnties is NULL \n");
    return 0xfffffff4;
  }
  if ((int)g_pktLenChged < 1) {
    uVar22 = 0;
    if (g_pktLenChged != 0) {
      uVar22 = -g_pktLenChged & 0xff | 0x40;
    }
  }
  else {
    uVar22 = g_pktLenChged & 0xff;
  }
  param_7[1] = 0;
  *param_7 = param_3;
  g_pktLenChged = 0;
  __memzero(&local_64,0x3c);
  __memzero(&local_91,0x2d);
  __memzero(auStack_b4,0x20);
  puVar11 = &local_64;
  puVar26 = param_6;
  do {
    puVar25 = puVar26;
    puVar23 = puVar11;
    puVar26 = puVar25 + 4;
    uVar14 = puVar25[1];
    uVar15 = puVar25[2];
    uVar17 = puVar25[3];
    *puVar23 = *puVar25;
    puVar23[1] = uVar14;
    puVar23[2] = uVar15;
    puVar23[3] = uVar17;
    puVar11 = puVar23 + 4;
  } while (puVar26 != param_6 + 0xc);
  uVar14 = puVar25[5];
  uVar15 = puVar25[6];
  puVar23[4] = *puVar26;
  puVar23[5] = uVar14;
  puVar23[6] = uVar15;
  if ((local_54[0] & 0x40) == 0) {
    printk("ERROR:(%s:%d)","tm_acl_v2.c",0x7c6);
    printk("temp hash table is empty \n");
    return 0xfffffff4;
  }
  if (g_dsliteSet == '\0') {
    if (g_dsliteDel == '\0') {
      if (g_v6rdSet == '\0') {
        uVar18 = (uint)*(ushort *)(param_1 + 2);
        if (g_v6rdDel != '\0') {
          uVar18 = uVar18 + 0x14;
        }
      }
      else {
        uVar18 = *(ushort *)(param_1 + 2) - 0x14;
      }
    }
    else {
      uVar18 = *(ushort *)(param_1 + 2) + 0x28;
    }
  }
  else {
    uVar18 = *(ushort *)(param_1 + 2) - 0x28;
  }
  uVar16 = *(uint *)(param_1 + 0x10);
  if (uVar16 == 1) {
    switch(param_1[0xb5]) {
    case 0:
      local_bc = 1;
      break;
    case 1:
      local_bc = 2;
      break;
    case 2:
      local_bc = 3;
      break;
    case 3:
      local_bc = 4;
      break;
    case 4:
      local_bc = 5;
      break;
    default:
      local_bc = 0;
      printk("ERROR:(%s:%d)","tm_acl_v2.c",0x82b);
      printk("Invalid parse target uni port!\n");
      uVar16 = *(uint *)(param_1 + 0x10);
      break;
    case 6:
      local_bc = 6;
      break;
    case 7:
      local_bc = 7;
      break;
    case 0x10:
      local_bc = 0x10;
      break;
    case 0x11:
      local_bc = 0x11;
      break;
    case 0x12:
      local_bc = 0x12;
      break;
    case 0x13:
      local_bc = 0x13;
      break;
    case 0x14:
      local_bc = 0x14;
      break;
    case 0x15:
      local_bc = 0x15;
      break;
    case 0x16:
      local_bc = 0x16;
      break;
    case 0x17:
      local_bc = 0x17;
      break;
    case 0x18:
      local_bc = 0x18;
      break;
    case 0x19:
      local_bc = 0x19;
      break;
    case 0x1a:
      local_bc = 0x1a;
      break;
    case 0x1b:
      local_bc = 0x1b;
      break;
    case 0x1c:
      local_bc = 0x1c;
      break;
    case 0x1d:
      local_bc = 0x1d;
      break;
    case 0x1e:
      local_bc = 0x1e;
      break;
    case 0x1f:
      local_bc = 0x1f;
    }
  }
  else {
    local_bc = 0;
  }
  uVar15 = local_5c;
  uVar14 = local_64;
  uVar19 = uVar16 & 1;
  uVar24 = *(uint *)(param_1 + 0x1c);
  if ((uVar24 & 4) == 0) {
    uVar20 = 0;
  }
  else {
    uVar20 = param_1[1] & 7;
  }
  if (macMode == 0) {
    uVar27 = 0;
    if (((uVar24 & 0x400000) != 0) && (uVar27 = local_bc, g_multiEn != '\0')) {
      uVar27 = 0;
    }
    local_58._0_2_ = (ushort)local_58 & 0xfc1f | (ushort)(uVar27 << 5);
  }
  else {
    local_58._0_2_ = (ushort)local_58 & 0xfc1f;
  }
  local_58 = CONCAT22(local_58._2_2_ & 0xfe3f | (ushort)(uVar20 << 6),(ushort)local_58);
  uVar8 = local_58;
  uVar27 = (uint)param_1[0xb4];
  bVar3 = local_5f & 0x41 | (g_multiEn == '\0') << 7;
  bVar4 = (byte)(((uVar22 << 0x19) >> 0x1b) << 1);
  uVar2 = (ushort)CONCAT31(local_64._1_3_,(byte)local_64 & 199 | (byte)((param_1[0xb1] & 7) << 3)) &
          0xf07f | 0x40 | (param_1[0xb0] & 0x1f) << 7;
  local_64 = CONCAT22(local_64._2_2_,uVar2);
  uVar17 = local_64;
  bVar1 = (param_1[0xb8] & 0x1f) << 2 | (byte)((*param_1 & 1) << 7);
  local_58 = CONCAT31(SUB43(uVar8,1),
                      (byte)local_58 & 0xe0 | (byte)(((uint)*param_1 << 0x1a) >> 0x1b));
  local_64._3_1_ = SUB41(uVar14,3);
  uVar22 = param_1[0xb1] & 7;
  if ((param_1[0xb4] & 8) != 0) {
    uVar22 = uVar27;
  }
  local_5c = CONCAT13(bVar1,(undefined3)local_5c);
  uVar8 = local_5c;
  uVar12 = g_qosEn & 1;
  local_64._0_3_ = (undefined3)uVar17;
  uVar7 = (undefined3)local_64;
  local_64 = CONCAT13(local_64._3_1_,(undefined3)local_64) | 0x1000000;
  local_5c._0_1_ = (byte)uVar15;
  local_5c._1_3_ = SUB43(uVar8,1);
  uVar14 = CONCAT31(local_5c._1_3_,(byte)local_5c & 0xf8 | (byte)((uVar18 << 0x12) >> 0x1d));
  local_5e = (ushort)(byte)((byte)local_5e & 0xf1 | (byte)((uVar22 & 7) << 1) | 0x10);
  local_5c._2_2_ = SUB42(uVar8,2);
  local_5e = local_5e & 0x1f | (ushort)((uVar18 & 0x7ff) << 5);
  local_5c = CONCAT22(local_5c._2_2_,
                      (ushort)uVar14 & 0xfc0f | 8 | ((param_1[5] & 1) << 5 | param_1[4] & 0x1f) << 4
                     ) | 0x400;
  uVar22 = local_5c;
  if (g_qosEn == 0) {
    local_64._0_1_ = (byte)uVar2;
    bVar1 = (byte)local_64;
    local_64 = CONCAT13(local_64._3_1_ & 1 | (byte)((param_3 & 0x7f) << 1),uVar7);
    local_60 = (undefined1)((param_3 << 0x11) >> 0x18);
    local_64 = CONCAT31(local_64._1_3_,bVar1 & 0xfc | 4 | (byte)*(undefined4 *)(param_1 + 0x18) & 3)
    ;
    local_5e = local_5e | 1;
  }
  else {
    local_5c._2_1_ = SUB41(uVar15,2);
    local_5c._0_2_ = (undefined2)uVar22;
    local_5c = CONCAT13(bVar1,CONCAT12(local_5c._2_1_,(undefined2)local_5c)) & 0xfff007ff | 0x100000
               | (param_3 >> 0x10 & 0x1ff) << 0xb;
  }
  uVar22 = local_64;
  if (g_macBind == '\x01') {
    local_64 = CONCAT31(local_64._1_3_,
                        (byte)local_64 & 0xbc | 4 | (byte)*(undefined4 *)(param_1 + 0x18) & 3);
    uVar14 = local_64;
    local_64._3_1_ = SUB41(uVar22,3);
    bVar3 = local_5f & 0x41;
    local_5e = local_5e & 0xffee;
    local_64._0_3_ = (undefined3)uVar14;
    local_64 = CONCAT13(local_64._3_1_,(undefined3)local_64) & 0xfeffffff;
    uVar9 = local_5c._1_1_;
    uVar10 = local_5c._2_1_;
    local_5c = local_5c & 0xfffffff7;
    local_5c = CONCAT22(local_5c._2_2_,CONCAT11(uVar9,(byte)local_5c)) & 0xfffffbff;
    local_5c = CONCAT13(local_5c._3_1_,CONCAT12(uVar10,(undefined2)local_5c)) & 0xffefffff;
  }
  local_5f = bVar3 | bVar4 | 0x40;
  bVar5 = (byte)(uVar20 << 1);
  local_5c = local_5c & 0xfe1fffff;
  bVar6 = (byte)((local_58 << 0x16) >> 0x1b);
  local_91 = local_91 & 0xe0 | bVar6;
  bVar1 = local_8f & 0x81 | bVar5;
  local_8d = local_8d & 0xfe | (byte)uVar19;
  uVar22 = local_8e & 0xffffff7f | uVar12 << 7;
  uVar12 = CONCAT13(uStack_51,
                    CONCAT12(local_54[2] & 0xf7 | (param_1[0xb0] >> 5 & 1) << 3,
                             (ushort)(byte)(local_54[0] & 0xcf | (byte)(uVar19 << 5) |
                                           (byte)(uVar12 << 4)))) & 0xfffc007f;
  local_8e = (byte)uVar22;
  local_54[0] = (byte)uVar12;
  local_54[1] = 0;
  local_54[2] = (byte)(uVar12 >> 0x10);
  uStack_51 = (undefined1)(uVar12 >> 0x18);
  if (uVar16 == 1) {
    local_54[2] = local_54[2] & 0xfb;
    if ((uVar24 & 0x800000) == 0) {
      local_8f = local_8f & 0x80 | bVar5;
      local_90 = 0;
      local_58 = local_58 & 0xffc003ff;
      local_91 = bVar6;
    }
    else {
      uVar22 = (uint)*(ushort *)(param_1 + 6);
      local_8f = local_8f & 0x80 | bVar5 | (byte)((uVar22 << 0x14) >> 0x1f);
      local_58 = local_58 & 0xffc003ff | (uVar22 & 0xfff) << 10;
      local_91 = bVar6 | (byte)((uVar22 & 7) << 5);
      local_90 = (undefined1)((uVar22 << 0x15) >> 0x18);
    }
    uVar22 = (uint)*(ushort *)(param_1 + 0xb2);
    if (uVar22 == 10) {
      local_64 = local_64 & 0xff000fff;
      local_5f = bVar3 & 0x7f | bVar4 | 0x40;
    }
    else {
      switch(uVar22) {
      case 0:
        uVar22 = 1;
      case 0x10:
      case 0x11:
      case 0x12:
      case 0x13:
      case 0x14:
      case 0x15:
      case 0x16:
      case 0x17:
      case 0x18:
      case 0x19:
      case 0x1a:
      case 0x1b:
      case 0x1c:
      case 0x1d:
      case 0x1e:
      case 0x1f:
        local_bc = uVar22;
        break;
      case 1:
        local_bc = 2;
        break;
      case 2:
        local_bc = 3;
        break;
      case 3:
        local_bc = 4;
        break;
      case 4:
        local_bc = 5;
        break;
      default:
        printk("ERROR:(%s:%d)","tm_acl_v2.c",0x8b9,uVar22,uVar20,1,uVar18,param_4,uVar27);
        printk("Invalid target uni port!\n");
        break;
      case 6:
        local_bc = 6;
        break;
      case 7:
        local_bc = 7;
      }
      if (g_multiEn == '\0') {
        local_54[2] = local_54[2] | 0x10;
        local_64 = local_64 & 0xff000fff | (local_bc & 0xfff) << 0xc;
      }
      else {
        local_64 = local_64 & 0xff000fff;
        local_54[2] = local_54[2] & 0xef;
      }
    }
  }
  else {
    if (uVar16 != 0) {
      local_8f = bVar1;
      printk("ERROR:(%s:%d)","tm_acl_v2.c",0x944,uVar22,uVar20,uVar19,uVar18,param_4,uVar27);
      printk("Undefined Direct Found \n");
      return 0xfffffff4;
    }
    if (lan_up == 0) {
      local_64 = local_64 & 0xff000fff | (*(ushort *)(param_1 + 0xb2) & 0xfff) << 0xc;
      local_54[2] = local_54[2] | 4;
    }
    else {
      local_54[2] = local_54[2] & 0xfb;
      local_64 = local_64 & 0xff000fff | (lan_up_port + 1U & 0xfff) << 0xc;
    }
    if ((uVar24 & 0x400000) == 0) {
      local_8f = local_8f & 0x80 | bVar5;
      local_90 = 0;
      local_58 = local_58 & 0xffc003ff;
      local_91 = bVar6;
    }
    else {
      uVar22 = *(uint *)(param_1 + 8);
      switch(uVar22) {
      case 0:
        uVar22 = 1;
        local_8f = bVar1;
        break;
      case 1:
        uVar22 = 2;
        local_8f = bVar1;
        break;
      case 2:
        uVar22 = 3;
        local_8f = bVar1;
        break;
      case 3:
        uVar22 = 4;
        local_8f = bVar1;
        break;
      case 4:
        uVar22 = 5;
        local_8f = bVar1;
        break;
      default:
        local_8f = bVar1;
        printk("ERROR:(%s:%d)","tm_acl_v2.c",0x935,uVar22,uVar20,0,uVar18,param_4,uVar27);
        printk("Invalid source uni port!\n");
        uVar22 = 0;
        break;
      case 0x10:
      case 0x11:
      case 0x12:
      case 0x13:
      case 0x14:
      case 0x15:
      case 0x16:
      case 0x17:
      case 0x18:
      case 0x19:
      case 0x1a:
      case 0x1b:
      case 0x1c:
      case 0x1d:
      case 0x1e:
      case 0x1f:
        uVar22 = uVar22 & 0xfff;
        local_8f = bVar1;
      }
      local_90 = (undefined1)((uVar22 << 0x15) >> 0x18);
      local_8f = local_8f & 0xfe | (byte)(uVar22 >> 0xb);
      local_58 = local_58 & 0xffc003ff | uVar22 << 10;
      local_91 = local_91 & 0x1f | (byte)((uVar22 & 7) << 5);
    }
  }
  local_8d = local_8d & 1 | (byte)((CONCAT11(bStack_50,uStack_51) & 0x7f) << 1);
  local_8b = bStack_50 >> 7 | (byte)((local_4f & 0x7f) << 1);
  local_8c = (undefined1)(((uint)CONCAT11(bStack_50,uStack_51) << 0x11) >> 0x18);
  local_89 = (byte)(local_4f >> 0xf) | (byte)(((ushort)local_4d & 0x7f) << 1);
  local_87 = local_4d[1] >> 7 | (byte)((local_4b & 0x7f) << 1);
  local_8a = (undefined1)(((uint)local_4f << 0x11) >> 0x18);
  local_85 = (byte)(local_4b >> 0xf) | (byte)((local_49 & 0x7f) << 1);
  local_88 = (undefined1)(((uint)(ushort)local_4d << 0x11) >> 0x18);
  local_83 = (byte)(local_49 >> 0xf) | (byte)((local_47 & 0x7f) << 1);
  local_86 = (undefined1)(((uint)local_4b << 0x11) >> 0x18);
  local_81 = (byte)(local_47 >> 0xf) | (byte)((local_45 & 0x7f) << 1);
  local_84 = (undefined1)(((uint)local_49 << 0x11) >> 0x18);
  local_82 = (undefined1)(((uint)local_47 << 0x11) >> 0x18);
  local_7f = (byte)(local_45 >> 0xf) | (byte)((local_43 & 0x7f) << 1);
  local_80 = (undefined1)(((uint)local_45 << 0x11) >> 0x18);
  local_7d = (byte)(local_43 >> 0xf) | (byte)((local_41 & 0x7f) << 1);
  local_7e = (undefined1)(((uint)local_43 << 0x11) >> 0x18);
  local_7c = (undefined1)(((uint)local_41 << 0x11) >> 0x18);
  local_7b = (byte)(local_41 >> 0xf) | (byte)((local_3f & 0x7f) << 1);
  local_79 = (byte)(local_3f >> 0xf) | (byte)((local_3d & 0x7f) << 1);
  local_7a = (undefined1)(((uint)local_3f << 0x11) >> 0x18);
  local_78 = (undefined1)(((uint)local_3d << 0x11) >> 0x18);
  local_77 = (byte)(local_3d >> 0xf) | (byte)((local_3b & 0x7f) << 1);
  local_75 = (byte)(local_3b >> 0xf) | (byte)((local_39 & 0x7f) << 1);
  local_73 = (byte)(local_39 >> 0xf) | (byte)((local_37 & 0x7f) << 1);
  local_71 = (byte)(local_37 >> 0xf) | (byte)((local_35 & 0x7f) << 1);
  local_70 = (undefined1)(((uint)local_35 << 0x11) >> 0x18);
  local_76 = (undefined1)(((uint)local_3b << 0x11) >> 0x18);
  local_6f = (byte)(local_35 >> 0xf) | (byte)((local_33 & 0x7f) << 1);
  local_72 = (undefined1)(((uint)local_37 << 0x11) >> 0x18);
  local_6e = (undefined1)(((uint)local_33 << 0x11) >> 0x18);
  local_6d = (byte)(local_33 >> 0xf) | (byte)((local_31 & 0x7f) << 1);
  local_74 = (undefined1)(((uint)local_39 << 0x11) >> 0x18);
  local_6c = (undefined1)(((uint)local_31 << 0x11) >> 0x18);
  local_65 = local_65 & 0xfe | (byte)(local_2b >> 0xf);
  local_6b = (byte)(local_31 >> 0xf) | (byte)((local_2f & 0x7f) << 1);
  local_69 = (byte)(local_2f >> 0xf) | (byte)((local_2d & 0x7f) << 1);
  local_6a = (undefined1)(((uint)local_2f << 0x11) >> 0x18);
  local_67 = (byte)(local_2d >> 0xf) | (byte)((local_2b & 0x7f) << 1);
  local_68 = (undefined1)(((uint)local_2d << 0x11) >> 0x18);
  local_66 = (undefined1)(((uint)local_2b << 0x11) >> 0x18);
  iVar13 = cla_get_hash_poly_config(auStack_b4);
  if (iVar13 != 0) {
    printk("ERROR:(%s:%d)","tm_acl_v2.c",0x962);
    printk("get hash poly cfg fail\n");
    return 0xfffffff4;
  }
  uVar22 = (uint)*param_2;
  if ((*param_2 & 0x8000) != 0) {
    uVar18 = uVar22 & 0xff;
    if ((short)param_2[1] < 0) {
      local_8f = local_8f & 0x7f | (byte)((uVar22 & 1) << 7);
      local_8e = local_8e & 0x80 | (byte)(uVar18 >> 1);
      local_54[0] = local_54[0] & 0xf0 | (byte)(uVar18 >> 4);
      local_58._3_1_ = local_58._3_1_ & 0xf | (byte)((uVar22 & 0xf) << 4);
      iVar13 = aclGetAvailableHashAddr_constprop_13(0,&local_91,auStack_b4,&local_b8);
      if (iVar13 != 0) {
        uVar14 = 0x96f;
        goto LAB_0005dac0;
      }
      if ((int)local_b8 < 0) {
        param_7[2] = local_b8 & 0x7fff;
        iVar13 = cla_set_hash_table(local_b8 & 0x7fff,&local_64);
        if (iVar13 != 0) {
          uVar14 = 0x9be;
          goto LAB_0005e180;
        }
        goto LAB_0005d934;
      }
      bVar1 = (byte)param_2[1];
      local_8f = local_8f & 0x7f | (byte)((bVar1 & 1) << 7);
      local_8e = local_8e & 0x80 | bVar1 >> 1;
      local_58._3_1_ = local_58._3_1_ & 0xf | (byte)((bVar1 & 0xf) << 4);
      local_54[0] = local_54[0] & 0xf0 | bVar1 >> 4;
      iVar13 = aclGetAvailableHashAddr_constprop_13(1,&local_91,auStack_b4,&local_b8);
      if (iVar13 != 0) {
        uVar14 = 0x97d;
        goto LAB_0005dac0;
      }
      if ((int)local_b8 < 0) {
        param_7[2] = local_b8 & 0xffff | 0x10000;
        cla_set_external_hash_table
                  (local_b8,(*(byte *)(param_5 + 0x3b) & 1) << 4 | *(byte *)(param_5 + 0x3a) >> 4,
                   &local_64);
        uVar22 = 0xc6fec;
        local_b8 = local_b8 & 0xffff;
        goto LAB_0005d940;
      }
      iVar13 = aclGetAvailableHashAddr_constprop_13(2,&local_91,auStack_b4,&local_b8);
      if (iVar13 != 0) {
        uVar14 = 0x989;
        goto LAB_0005dac0;
      }
      if (-1 < (int)local_b8) {
        return 0xfffffff4;
      }
      uVar2 = *param_2;
      param_7[2] = local_b8 & 0x7fff;
      local_54[0] = local_54[0] & 0xf0 | (byte)uVar2 >> 4;
      local_58._3_1_ = local_58._3_1_ & 0xf | (byte)uVar2 << 4;
      iVar13 = cla_set_hash_table(local_b8 & 0x7fff,&local_64);
      if (iVar13 != 0) {
        uVar14 = 0x998;
        goto LAB_0005e180;
      }
      iVar13 = param_7[2] + 0xc6de4;
    }
    else {
      local_8f = local_8f & 0x7f | (byte)((uVar22 & 1) << 7);
      local_8e = local_8e & 0x80 | (byte)(uVar18 >> 1);
      local_54[0] = local_54[0] & 0xf0 | (byte)(uVar18 >> 4);
      local_58._3_1_ = local_58._3_1_ & 0xf | (byte)((uVar22 & 0xf) << 4);
      iVar13 = aclGetAvailableHashAddr_constprop_13(0,&local_91,auStack_b4,&local_b8);
      if (iVar13 != 0) {
        uVar14 = 0x9d3;
        goto LAB_0005dac0;
      }
      if ((int)local_b8 < 0) {
        param_7[2] = local_b8 & 0x7fff;
        iVar13 = cla_set_hash_table(local_b8 & 0x7fff,&local_64);
        if (iVar13 != 0) {
          uVar14 = 0xa3c;
          goto LAB_0005e180;
        }
      }
      else {
        uVar22 = (uint)param_2[2];
        if ((param_2[2] & 0x8000) == 0) {
          return 0xfffffff4;
        }
        local_8f = local_8f & 0x7f | (byte)((uVar22 & 1) << 7);
        local_8e = local_8e & 0x80 | (byte)((uVar22 & 0xff) >> 1);
        local_54[0] = local_54[0] & 0xf0 | (byte)((uVar22 & 0xff) >> 4);
        local_58._3_1_ = local_58._3_1_ & 0xf | (byte)((uVar22 & 0xf) << 4);
        iVar13 = aclGetAvailableHashAddr_constprop_13(1,&local_91,auStack_b4,&local_b8);
        if (iVar13 != 0) {
          uVar14 = 0x9e3;
          goto LAB_0005dac0;
        }
        if ((int)local_b8 < 0) {
          param_7[2] = local_b8 & 0xffff | 0x10000;
          cla_set_external_hash_table
                    (local_b8,(*(byte *)(param_5 + 0x3b) & 1) << 4 | *(byte *)(param_5 + 0x3a) >> 4,
                     &local_64);
          *(byte *)(param_5 + 0x3b) = *(byte *)(param_5 + 0x3b) | 2;
          iVar13 = cla_set_extra_rule_table(local_54[0] << 4 | local_58._3_1_ >> 4);
          if (iVar13 != 0) {
            uVar14 = 0xa1a;
            goto LAB_0005e308;
          }
          *(ushort *)(param_4 + 0x10) =
               *(ushort *)(param_4 + 0x10) | (ushort)(1 << (uint)(local_58._3_1_ >> 4));
          iVar13 = cla_set_extra_index_table(param_7[4],param_4);
          if (iVar13 != 0) {
            uVar14 = 0xa23;
            goto LAB_0005d5d8;
          }
          uVar22 = (uint)(local_58._3_1_ >> 4);
          uVar16 = (local_54[0] & 0xf) << 4 | uVar22;
          s_aclHashUsedCnt[(local_b8 & 0xffff) + 0x208] =
               s_aclHashUsedCnt[(local_b8 & 0xffff) + 0x208] + '\x01';
          uVar19 = param_7[4];
          uVar14 = *(undefined4 *)(param_1 + 0x1c);
          uVar18 = param_7[2];
          goto LAB_0005d4a4;
        }
        iVar13 = aclGetAvailableHashAddr_constprop_13(2,&local_91,auStack_b4,&local_b8);
        if (iVar13 != 0) {
          uVar14 = 0x9ef;
          goto LAB_0005dac0;
        }
        if (-1 < (int)local_b8) {
          return 0xfffffff4;
        }
        uVar2 = *param_2;
        param_7[2] = local_b8 & 0x7fff;
        local_54[0] = local_54[0] & 0xf0 | (byte)uVar2 >> 4;
        local_58._3_1_ = local_58._3_1_ & 0xf | (byte)uVar2 << 4;
        iVar13 = cla_set_hash_table(local_b8 & 0x7fff,&local_64);
        if (iVar13 != 0) {
          uVar14 = 0x9fd;
          goto LAB_0005e180;
        }
      }
LAB_0005d934:
      uVar22 = param_7[2];
      local_b8 = 0xc6de4;
LAB_0005d940:
      iVar13 = local_b8 + uVar22;
    }
    *(char *)(iVar13 + -0xe8c) = *(char *)(iVar13 + -0xe8c) + '\x01';
    uVar22 = param_7[2];
    iVar13 = param_7[4] * 0x10 + (uint)(local_58._3_1_ >> 4);
LAB_0005d964:
    iVar13 = iVar13 * 0x10;
    iVar21 = *(int *)(sa_rulesRecord + iVar13 + 0xc);
    *(uint *)(sa_rulesRecord + iVar13 + 8) = uVar22;
    param_7[3] = *(uint *)(sa_rulesRecord + iVar13 + 4);
    *(int *)(sa_rulesRecord + iVar13 + 0xc) = iVar21 + 1;
    return 0;
  }
  uVar22 = (uint)param_2[1];
  if ((param_2[1] & 0x8000) == 0) {
    uVar22 = (uint)param_2[2];
    if ((param_2[2] & 0x8000) == 0) {
      return 0xfffffff4;
    }
    local_8f = local_8f & 0x7f | (byte)((uVar22 & 1) << 7);
    local_8e = local_8e & 0x80 | (byte)((uVar22 & 0xff) >> 1);
    local_54[0] = local_54[0] & 0xf0 | (byte)((uVar22 & 0xff) >> 4);
    local_58._3_1_ = local_58._3_1_ & 0xf | (byte)((uVar22 & 0xf) << 4);
    if ((g_acl_internal != 0) &&
       (iVar13 = aclGetAvailableHashAddr_constprop_13(0,&local_91,auStack_b4,&local_b8), iVar13 != 0
       )) {
      uVar14 = 0xad7;
LAB_0005dac0:
      printk("ERROR:(%s:%d)","tm_acl_v2.c",uVar14);
      printk("aclGetAvailableHashAddr fail\n");
      return 0xfffffff4;
    }
    if ((int)local_b8 < 0) {
      param_7[2] = local_b8 & 0x7fff;
      iVar13 = cla_set_hash_table(local_b8 & 0x7fff,&local_64);
      if (iVar13 != 0) {
        uVar14 = 0xb23;
        goto LAB_0005e180;
      }
      s_aclHashUsedCnt[param_7[2]] = s_aclHashUsedCnt[param_7[2]] + '\x01';
      *(byte *)(param_5 + 0x3b) = *(byte *)(param_5 + 0x3b) & 0xfd;
      iVar13 = cla_set_extra_rule_table(local_54[0] << 4 | local_58._3_1_ >> 4);
      if (iVar13 != 0) {
        uVar14 = 0xb2f;
LAB_0005e308:
        printk("ERROR:(%s:%d)","tm_acl_v2.c",uVar14);
        printk("cla_set_extra_rule_table fail\n");
        return 0xfffffff4;
      }
      *(ushort *)(param_4 + 0x10) =
           *(ushort *)(param_4 + 0x10) | (ushort)(1 << (uint)(local_58._3_1_ >> 4));
      iVar13 = cla_set_extra_index_table(param_7[4],param_4);
      if (iVar13 != 0) {
        uVar14 = 0xb38;
LAB_0005d5d8:
        printk("ERROR:(%s:%d)","tm_acl_v2.c",uVar14);
        printk("cla_set_extra_index_table fail\n");
        return 0xfffffff4;
      }
    }
    else {
      iVar13 = aclGetAvailableHashAddr_constprop_13(1,&local_91,auStack_b4,&local_b8);
      if (iVar13 != 0) {
        uVar14 = 0xae3;
        goto LAB_0005dac0;
      }
      if (-1 < (int)local_b8) {
        return 0xfffffff4;
      }
      param_7[2] = local_b8 & 0xffff | 0x10000;
      cla_set_external_hash_table
                (local_b8,(*(byte *)(param_5 + 0x3b) & 1) << 4 | *(byte *)(param_5 + 0x3a) >> 4,
                 &local_64);
      s_aclHashUsedCnt[(local_b8 & 0xffff) + 0x208] =
           s_aclHashUsedCnt[(local_b8 & 0xffff) + 0x208] + '\x01';
      *(byte *)(param_5 + 0x3b) = *(byte *)(param_5 + 0x3b) | 2;
      iVar13 = cla_set_extra_rule_table(local_54[0] << 4 | local_58._3_1_ >> 4);
      if (iVar13 != 0) {
        uVar14 = 0xb00;
        goto LAB_0005e308;
      }
      *(ushort *)(param_4 + 0x10) =
           *(ushort *)(param_4 + 0x10) | (ushort)(1 << (uint)(local_58._3_1_ >> 4));
      iVar13 = cla_set_extra_index_table(param_7[4],param_4);
      if (iVar13 != 0) {
        uVar14 = 0xb09;
        goto LAB_0005d5d8;
      }
    }
  }
  else {
    local_8f = local_8f & 0x7f | (byte)((uVar22 & 1) << 7);
    local_8e = local_8e & 0x80 | (byte)((uVar22 & 0xff) >> 1);
    local_54[0] = local_54[0] & 0xf0 | (byte)((uVar22 & 0xff) >> 4);
    local_58._3_1_ = local_58._3_1_ & 0xf | (byte)((uVar22 & 0xf) << 4);
    iVar13 = aclGetAvailableHashAddr_constprop_13(1,&local_91,auStack_b4,&local_b8);
    if (iVar13 != 0) {
      uVar14 = 0xa54;
      goto LAB_0005dac0;
    }
    if ((int)local_b8 < 0) {
      param_7[2] = local_b8 & 0xffff | 0x10000;
      cla_set_external_hash_table
                (local_b8,(*(byte *)(param_5 + 0x3b) & 1) << 4 | *(byte *)(param_5 + 0x3a) >> 4,
                 &local_64);
      uVar22 = 0xc6fec;
      local_b8 = local_b8 & 0xffff;
      goto LAB_0005d940;
    }
    uVar22 = (uint)param_2[2];
    if ((param_2[2] & 0x8000) == 0) {
      return 0xfffffff4;
    }
    local_8f = local_8f & 0x7f | (byte)((uVar22 & 1) << 7);
    local_8e = local_8e & 0x80 | (byte)((uVar22 & 0xff) >> 1);
    local_58._3_1_ = local_58._3_1_ & 0xf | (byte)((uVar22 & 0xf) << 4);
    local_54[0] = local_54[0] & 0xf0 | (byte)((uVar22 & 0xff) >> 4);
    iVar13 = aclGetAvailableHashAddr_constprop_13(0,&local_91,auStack_b4,&local_b8);
    if (iVar13 != 0) {
      uVar14 = 0xa62;
      goto LAB_0005dac0;
    }
    if (-1 < (int)local_b8) {
      iVar13 = aclGetAvailableHashAddr_constprop_13(2,&local_91,auStack_b4,&local_b8);
      if (iVar13 != 0) {
        uVar14 = 0xa6c;
        goto LAB_0005dac0;
      }
      if (-1 < (int)local_b8) {
        return 0xfffffff4;
      }
      uVar2 = param_2[1];
      param_7[2] = local_b8 & 0x7fff;
      local_54[0] = local_54[0] & 0xf0 | (byte)uVar2 >> 4;
      local_58._3_1_ = local_58._3_1_ & 0xf | (byte)uVar2 << 4;
      iVar13 = cla_set_hash_table(local_b8 & 0x7fff,&local_64);
      if (iVar13 != 0) {
        uVar14 = 0xa7d;
        goto LAB_0005e180;
      }
      uVar22 = param_7[2];
      iVar13 = param_7[4] * 0x10 + (uint)(local_58._3_1_ >> 4);
      goto LAB_0005d964;
    }
    param_7[2] = local_b8 & 0x7fff;
    iVar13 = cla_set_hash_table(local_b8 & 0x7fff,&local_64);
    if (iVar13 != 0) {
      uVar14 = 0xa8d;
LAB_0005e180:
      printk("ERROR:(%s:%d)","tm_acl_v2.c",uVar14);
      printk("cla_set_hash_table fail\n");
      return 0xfffffff4;
    }
    s_aclHashUsedCnt[param_7[2]] = s_aclHashUsedCnt[param_7[2]] + '\x01';
    *(byte *)(param_5 + 0x3b) = *(byte *)(param_5 + 0x3b) & 0xfd;
    iVar13 = cla_set_extra_rule_table(local_54[0] << 4 | local_58._3_1_ >> 4);
    if (iVar13 != 0) {
      uVar14 = 0xa98;
      goto LAB_0005e308;
    }
    *(ushort *)(param_4 + 0x10) =
         *(ushort *)(param_4 + 0x10) | (ushort)(1 << (uint)(local_58._3_1_ >> 4));
    iVar13 = cla_set_extra_index_table(param_7[4],param_4);
    if (iVar13 != 0) {
      uVar14 = 0xaa0;
      goto LAB_0005d5d8;
    }
  }
  uVar19 = param_7[4];
  uVar14 = *(undefined4 *)(param_1 + 0x1c);
  uVar18 = param_7[2];
  uVar22 = (uint)(local_58._3_1_ >> 4);
  uVar16 = (local_54[0] & 0xf) << 4 | uVar22;
LAB_0005d4a4:
  param_7[3] = uVar16 | 0x10000000;
  iVar13 = (uVar22 + uVar19 * 0x10) * 0x10;
  *(uint *)(sa_rulesRecord + iVar13 + 4) = uVar16 | 0x10000000;
  *(undefined4 *)(sa_rulesRecord + iVar13) = uVar14;
  *(uint *)(sa_rulesRecord + iVar13 + 8) = uVar18;
  *(int *)(sa_rulesRecord + iVar13 + 0xc) = *(int *)(sa_rulesRecord + iVar13 + 0xc) + 1;
  return 0;
}

