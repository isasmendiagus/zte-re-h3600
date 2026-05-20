// module: tm.ko
// function: tm_acl_fast_add_v4v6 @ 0x5c2a8
// size: 2424 bytes
//

undefined4
tm_acl_fast_add_v4v6(uint param_1,int param_2,int param_3,undefined4 param_4,undefined4 *param_5)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  uint local_bc;
  uint local_b8;
  undefined1 auStack_b4 [35];
  undefined1 local_91;
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
  undefined1 auStack_64 [15];
  byte local_55;
  byte local_54;
  ushort local_51;
  ushort local_4f;
  ushort local_4d;
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
  
  local_bc = 0;
  local_b8 = 0;
  if (param_5 == (undefined4 *)0x0 || param_3 == 0) {
    return 0xfffffff4;
  }
  __memzero(&local_91,0x2d);
  __memzero(auStack_64,0x3c);
  __memzero(auStack_b4,0x20);
  cla_get_hash_poly_config(auStack_b4);
  if (param_2 == 0) {
    g_ipv6FastEn = *(int *)(param_3 + 0xc) == 4;
  }
  else {
    g_ipv4FastEn = *(int *)(param_3 + 0xc) == 3;
  }
  iVar2 = aclGetExtIdxRuleRamAddrByPort(*(undefined4 *)(param_3 + 8),&local_b8);
  g_ipv4FastEn = 0;
  g_ipv6FastEn = 0;
  if (iVar2 != 0) {
LAB_0005c824:
    printk("ERROR:invalid sorce port %d\n",*(undefined4 *)(param_3 + 8));
    return 0xfffffff4;
  }
  iVar2 = tm_acl_get_fastHashRule(param_2,param_3,param_4,auStack_64);
  if (iVar2 == 0) {
    return 0xfffffff4;
  }
  local_8d = (byte)(((uint)local_54 << 0x1a) >> 0x1f) | (byte)((local_51 & 0x7f) << 1);
  local_8b = (byte)(local_51 >> 0xf) | (byte)((local_4f & 0x7f) << 1);
  local_91 = 0;
  local_89 = (byte)(local_4f >> 0xf) | (byte)((local_4d & 0x7f) << 1);
  local_88 = (undefined1)(((uint)local_4d << 0x11) >> 0x18);
  local_87 = (byte)(local_4d >> 0xf) | (byte)((local_4b & 0x7f) << 1);
  local_86 = (undefined1)(((uint)local_4b << 0x11) >> 0x18);
  local_85 = (byte)(local_4b >> 0xf) | (byte)((local_49 & 0x7f) << 1);
  local_84 = (undefined1)(((uint)local_49 << 0x11) >> 0x18);
  local_8c = (undefined1)(((uint)local_51 << 0x11) >> 0x18);
  local_83 = (byte)(local_49 >> 0xf) | (byte)((local_47 & 0x7f) << 1);
  local_8a = (undefined1)(((uint)local_4f << 0x11) >> 0x18);
  local_81 = (byte)(local_47 >> 0xf) | (byte)((local_45 & 0x7f) << 1);
  local_82 = (undefined1)(((uint)local_47 << 0x11) >> 0x18);
  local_7f = (byte)(local_45 >> 0xf) | (byte)((local_43 & 0x7f) << 1);
  local_7d = (byte)(local_43 >> 0xf) | (byte)((local_41 & 0x7f) << 1);
  local_90 = 0;
  local_80 = (undefined1)(((uint)local_45 << 0x11) >> 0x18);
  local_7e = (undefined1)(((uint)local_43 << 0x11) >> 0x18);
  local_7c = (undefined1)(((uint)local_41 << 0x11) >> 0x18);
  local_79 = (byte)(local_3f >> 0xf) | (byte)((local_3d & 0x7f) << 1);
  local_77 = (byte)(local_3d >> 0xf) | (byte)((local_3b & 0x7f) << 1);
  local_7b = (byte)(local_41 >> 0xf) | (byte)((local_3f & 0x7f) << 1);
  local_75 = (byte)(local_3b >> 0xf) | (byte)((local_39 & 0x7f) << 1);
  local_73 = (byte)(local_39 >> 0xf) | (byte)((local_37 & 0x7f) << 1);
  local_7a = (undefined1)(((uint)local_3f << 0x11) >> 0x18);
  local_78 = (undefined1)(((uint)local_3d << 0x11) >> 0x18);
  local_71 = (byte)(local_37 >> 0xf) | (byte)((local_35 & 0x7f) << 1);
  local_76 = (undefined1)(((uint)local_3b << 0x11) >> 0x18);
  local_74 = (undefined1)(((uint)local_39 << 0x11) >> 0x18);
  local_72 = (undefined1)(((uint)local_37 << 0x11) >> 0x18);
  local_6f = (byte)(local_35 >> 0xf) | (byte)((local_33 & 0x7f) << 1);
  local_70 = (undefined1)(((uint)local_35 << 0x11) >> 0x18);
  local_6e = (undefined1)(((uint)local_33 << 0x11) >> 0x18);
  local_6b = (byte)(local_31 >> 0xf) | (byte)((local_2f & 0x7f) << 1);
  local_6d = (byte)(local_33 >> 0xf) | (byte)((local_31 & 0x7f) << 1);
  local_6c = (undefined1)(((uint)local_31 << 0x11) >> 0x18);
  local_67 = (byte)(local_2d >> 0xf) | (byte)((local_2b & 0x7f) << 1);
  local_68 = (undefined1)(((uint)local_2d << 0x11) >> 0x18);
  local_69 = (byte)(local_2f >> 0xf) | (byte)((local_2d & 0x7f) << 1);
  local_6a = (undefined1)(((uint)local_2f << 0x11) >> 0x18);
  local_66 = (undefined1)(((uint)local_2b << 0x11) >> 0x18);
  local_65 = local_65 & 0xfe | (byte)(local_2b >> 0xf);
  if (param_2 == 0) {
    if (param_1 == 0) {
      if (local_b8 == 10) {
        uVar3 = 6;
      }
      else {
        uVar3 = local_b8 * 0x10 + 6 & 0xff;
      }
      uVar5 = 0x11;
    }
    else {
      if (local_b8 == 10) {
        uVar3 = 2;
      }
      else {
        uVar3 = local_b8 * 0x10 + 2 & 0xff;
      }
      uVar5 = 0x13;
    }
  }
  else if (param_1 == 0) {
    uVar5 = 5;
    uVar3 = local_b8 * 0x10 + 4 & 0xff;
  }
  else {
    uVar5 = 7;
    uVar3 = (local_b8 & 0xf) << 4;
  }
  local_8e = (byte)(uVar3 >> 1);
  local_8f = 0;
  uVar3 = aclGetAvailableHashAddr_constprop_13(0,&local_91,auStack_b4,&local_bc);
  if (uVar3 != 0) goto LAB_0005c824;
  if ((int)local_bc < 0) {
    if (param_1 == 0) {
      if (param_2 == 0) {
        if (local_b8 == 10) {
          uVar3 = 6;
        }
        else {
          uVar3 = local_b8 * 0x10 + 6 & 0xff;
        }
      }
      else {
        uVar3 = local_b8 * 0x10 + 4 & 0xff;
      }
    }
    else if (param_2 == 0) {
      if (local_b8 == 10) {
        uVar3 = 2;
      }
      else {
        uVar3 = local_b8 * 0x10 + 2 & 0xff;
      }
    }
    else {
      uVar3 = (local_b8 & 0xf) << 4;
    }
    param_5[2] = local_bc & 0x7fff;
    local_55 = local_55 & 0xf | (byte)((uVar3 & 0xf) << 4);
    local_54 = local_54 & 0xf0 | (byte)(uVar3 >> 4);
    iVar2 = cla_set_hash_table(local_bc & 0x7fff,auStack_64);
    if (iVar2 != 0) {
      printk("ERROR:(%s:%d)","tm_acl_v2.c",0x26d9);
      printk("cla_set_hash_table fail\n");
      printk("ret %d\n",iVar2);
      return 0xfffffff4;
    }
  }
  else {
    if (param_1 == 0) {
      if (param_2 == 0) {
        if (local_b8 == 10) {
          uVar4 = 7;
        }
        else {
          uVar4 = local_b8 * 0x10 + 7 & 0xff;
        }
      }
      else {
        uVar4 = local_b8 * 0x10 + 5 & 0xff;
      }
    }
    else if (param_2 == 0) {
      if (local_b8 == 10) {
        uVar4 = 3;
      }
      else {
        uVar4 = local_b8 * 0x10 + 3 & 0xff;
      }
    }
    else {
      uVar4 = local_b8 * 0x10 + 1 & 0xff;
    }
    local_8f = local_8f & 0x7f | (byte)((uVar4 & 1) << 7);
    local_8e = local_8e & 0x80 | (byte)(uVar4 >> 1);
    local_bc = uVar3;
    uVar3 = aclGetAvailableHashAddr_constprop_13(1,&local_91,auStack_b4,&local_bc);
    if (uVar3 != 0) goto LAB_0005c824;
    if ((int)local_bc < 0) {
      if (param_1 == 0) {
        if (param_2 == 0) {
          if (local_b8 == 10) {
            uVar3 = 7;
          }
          else {
            uVar3 = local_b8 * 0x10 + 7 & 0xff;
          }
        }
        else {
          uVar3 = local_b8 * 0x10 + 5 & 0xff;
        }
      }
      else if (param_2 == 0) {
        if (local_b8 == 10) {
          uVar3 = 3;
        }
        else {
          uVar3 = local_b8 * 0x10 + 3 & 0xff;
        }
      }
      else {
        uVar3 = local_b8 * 0x10 + 1 & 0xff;
      }
      param_5[2] = local_bc & 0xffff | 0x10000;
      local_55 = local_55 & 0xf | (byte)((uVar3 & 0xf) << 4);
      local_54 = local_54 & 0xf0 | (byte)(uVar3 >> 4);
      cla_set_external_hash_table(local_bc & 0xffff,uVar5,auStack_64);
      s_aclHashUsedCnt[(local_bc & 0xffff) + 0x208] =
           s_aclHashUsedCnt[(local_bc & 0xffff) + 0x208] + '\x01';
      goto LAB_0005c778;
    }
    local_bc = uVar3;
    iVar2 = aclGetAvailableHashAddr_constprop_13(2,&local_91,auStack_b4,&local_bc);
    if (iVar2 != 0) goto LAB_0005c824;
    if (-1 < (int)local_bc) {
      return 0xfffffff4;
    }
    if (param_1 == 0) {
      if (param_2 == 0) {
        if (local_b8 == 10) {
          uVar3 = 6;
        }
        else {
          uVar3 = local_b8 * 0x10 + 6 & 0xff;
        }
      }
      else {
        uVar3 = local_b8 * 0x10 + 4 & 0xff;
      }
    }
    else if (param_2 == 0) {
      if (local_b8 == 10) {
        uVar3 = 2;
      }
      else {
        uVar3 = local_b8 * 0x10 + 2 & 0xff;
      }
    }
    else {
      uVar3 = (local_b8 & 0xf) << 4;
    }
    param_5[2] = local_bc & 0x7fff;
    local_55 = local_55 & 0xf | (byte)((uVar3 & 0xf) << 4);
    local_54 = local_54 & 0xf0 | (byte)(uVar3 >> 4);
    iVar2 = cla_set_hash_table(local_bc & 0x7fff,auStack_64);
    if (iVar2 != 0) {
      printk("ERROR:(%s:%d)","tm_acl_v2.c",0x26c7);
      printk("cla_set_hash_table fail\n");
      return 0xfffffff4;
    }
  }
  s_aclHashUsedCnt[param_5[2]] = s_aclHashUsedCnt[param_5[2]] + '\x01';
LAB_0005c778:
  *param_5 = param_4;
  uVar3 = (local_54 & 0xf) << 4 | (uint)(local_55 >> 4);
  iVar2 = local_b8 * 0x10;
  param_5[4] = local_b8;
  param_5[3] = uVar3 | 0x10000000;
  iVar1 = (iVar2 + (uint)(local_55 >> 4)) * 0x10;
  *(undefined4 *)(sa_rulesRecord + iVar1 + 8) = param_5[2];
  *(uint *)(sa_rulesRecord + iVar1 + 4) = uVar3 | 0x10000000;
  *(int *)(sa_rulesRecord + iVar1 + 0xc) = *(int *)(sa_rulesRecord + iVar1 + 0xc) + 1;
  if (param_1 == 0) {
    if (param_2 != 0) {
      if (uVar3 != iVar2 + 5U) {
        return 0;
      }
      if (*(int *)(g_v4OutUsed_3t + local_b8 * 4) != 0) {
        return 0;
      }
      EN_V4FAST_EXTIDXTBL(0,local_b8 & 0xff,1);
      *(undefined4 *)(g_v4OutUsed_3t + local_b8 * 4) = 1;
      return 0;
    }
    if (local_b8 == 10) {
      uVar4 = 7;
    }
    else {
      uVar4 = iVar2 + 7;
    }
  }
  else {
    if (param_2 != 0) {
      if (uVar3 != iVar2 + 1U) {
        return 0;
      }
      if (*(int *)(g_v4OutUsed + local_b8 * 4) == 0) {
        EN_V4FAST_EXTIDXTBL(param_1 & 0xff,local_b8 & 0xff,1);
        *(undefined4 *)(g_v4OutUsed + local_b8 * 4) = 1;
        return 0;
      }
      return 0;
    }
    if (local_b8 == 10) {
      uVar4 = 3;
    }
    else {
      uVar4 = iVar2 + 3;
    }
  }
  if (uVar3 != uVar4) {
    return 0;
  }
  if (param_1 != 0 && param_2 == 0) {
    if (*(int *)(g_v6OutUsed + local_b8 * 4) != 0) {
      return 0;
    }
    EN_V6FAST_EXTIDXTBL(param_1 & 0xff,local_b8 & 0xff,1);
    *(undefined4 *)(g_v6OutUsed + local_b8 * 4) = 1;
    return 0;
  }
  if (param_1 != 0) {
    return 0;
  }
  if (*(int *)(g_v6OutUsed_3t + local_b8 * 4) != 0) {
    return 0;
  }
  EN_V6FAST_EXTIDXTBL(0,local_b8 & 0xff,1);
  *(undefined4 *)(g_v6OutUsed_3t + local_b8 * 4) = 1;
  return 0;
}

