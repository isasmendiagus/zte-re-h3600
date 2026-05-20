// module: switch.ko
// function: npu_drv_refresh_flow @ 0x20398
// size: 1596 bytes
//

undefined4 npu_drv_refresh_flow(undefined4 param_1,int param_2)

{
  byte bVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  undefined4 *puVar6;
  byte *pbVar7;
  char *__s2;
  undefined4 local_d0;
  byte *local_cc;
  byte *local_c8;
  undefined2 local_c4;
  undefined2 local_c2;
  byte local_c0;
  byte local_bf;
  byte *local_bc;
  byte *local_b8;
  undefined2 local_b4;
  undefined2 local_b2;
  byte local_b0;
  byte local_af;
  byte *local_ac;
  byte *local_a8;
  undefined2 local_a4;
  undefined2 local_a2;
  byte local_a0;
  byte local_9f;
  byte *local_9c;
  byte *local_98;
  undefined2 local_94;
  undefined2 local_92;
  byte local_90;
  byte local_8f;
  byte *local_8c;
  byte *local_88;
  undefined2 local_84;
  undefined2 local_82;
  int local_80;
  ushort local_7c;
  undefined1 local_78;
  undefined1 local_77;
  char *local_74;
  int local_70;
  byte *local_6c;
  byte *local_68;
  byte *local_64;
  undefined2 local_60;
  undefined2 local_5e;
  undefined2 local_5c;
  undefined2 local_5a;
  undefined2 local_58;
  undefined4 local_54;
  byte local_50;
  byte local_4f;
  uint local_4c;
  byte *local_48;
  byte *local_44;
  byte local_40;
  byte local_3f;
  short local_3a;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_d0 = 0;
  if (DAT_0002b910 == (code *)0x0) {
    return 0;
  }
  if (*(int *)(*(int *)(param_2 + 0x34) + 0x14) - 4U < 2) {
    return 1;
  }
  __memzero(&local_8c,0x6c);
  __memzero(&local_cc,0x10);
  __memzero(&local_bc,0x10);
  __memzero(&local_ac,0x10);
  __memzero(&local_9c,0x10);
  if (param_2 == 0) {
    return 0;
  }
  pbVar7 = *(byte **)(param_2 + 0x14);
  __s2 = *(char **)(pbVar7 + *pbVar7);
  if (__s2 == (char *)0x0) {
    return 0;
  }
  local_74 = __s2;
  iVar3 = strcmp("pon0",__s2);
  if (((((iVar3 == 0) || (iVar3 = strcmp("pon",__s2), iVar3 == 0)) ||
       (iVar3 = strcmp("gpon0",__s2), iVar3 == 0)) ||
      ((iVar3 = strcmp("epon0",__s2), iVar3 == 0 || (iVar3 = strcmp("mii1",__s2), iVar3 == 0)))) ||
     (iVar3 = strcmp("eth0",__s2), iVar3 == 0)) {
    bVar2 = true;
  }
  else {
    iVar3 = strcmp("ptm0",__s2);
    bVar2 = iVar3 == 0;
  }
  pbVar5 = *(byte **)(param_2 + 0x10);
  local_70 = *(int *)(pbVar5 + *pbVar5);
  if (local_70 == 0) {
    return 0;
  }
  if ((*(uint *)(param_2 + 0x28) & 0x1000000) == 0) {
    if ((*(uint *)(param_2 + 0x28) & 0x2000000) != 0) {
      local_77 = 1;
    }
  }
  else {
    local_78 = 1;
  }
  uVar4 = *(uint *)(param_2 + 0x28);
  if ((uVar4 & 0x1c) == 0) {
    if ((uVar4 & 0x700) != 0) {
      local_80 = 1;
      uVar4 = (uint)pbVar5[7];
      local_a8 = pbVar5 + uVar4 + 0x18;
      local_a0 = pbVar5[uVar4 + 6];
      local_ac = pbVar5 + uVar4 + 8;
      local_9f = pbVar5[uVar4 + 1] >> 4 | pbVar5[uVar4] << 4;
      if (local_a0 == 6) {
        bVar1 = pbVar5[9];
LAB_000208c0:
        local_a4 = *(undefined2 *)(pbVar5 + bVar1);
        local_a2 = *(undefined2 *)(pbVar5 + bVar1 + 2);
      }
      else {
        if (local_a0 == 0x11) {
          bVar1 = pbVar5[10];
          goto LAB_000208c0;
        }
        local_a4 = 0;
        local_a2 = 0;
      }
      local_7c = (ushort)local_a0;
      uVar4 = (uint)pbVar7[7];
      local_98 = pbVar7 + uVar4 + 0x18;
      local_90 = pbVar7[uVar4 + 6];
      local_9c = pbVar7 + uVar4 + 8;
      local_8f = pbVar7[uVar4 + 1] >> 4 | pbVar7[uVar4] << 4;
      if (local_90 == 6) {
        bVar1 = pbVar7[9];
LAB_000209a0:
        local_94 = *(undefined2 *)(pbVar7 + bVar1);
        local_92 = *(undefined2 *)(pbVar7 + bVar1 + 2);
      }
      else {
        if (local_90 == 0x11) {
          bVar1 = pbVar7[10];
          goto LAB_000209a0;
        }
        local_94 = 0;
        local_92 = local_94;
      }
      local_8c = local_ac;
      local_88 = local_a8;
      local_84 = local_a4;
      local_82 = local_a2;
      if (local_9f != local_8f) {
        local_3f = local_3f | 0x10;
        local_40 = local_8f;
      }
      goto LAB_0002074c;
    }
    if ((uVar4 & 0x60) == 0) {
      return 0;
    }
    local_80 = 2;
  }
  else {
    local_80 = 0;
  }
  uVar4 = (uint)pbVar5[5];
  local_cc = *(byte **)(pbVar5 + uVar4);
  local_c0 = pbVar5[uVar4 + 9];
  local_c8 = *(byte **)(pbVar5 + uVar4 + 4);
  local_bf = pbVar5[uVar4 + 8];
  if (local_c0 == 6) {
    bVar1 = pbVar5[9];
LAB_000208dc:
    local_c4 = *(undefined2 *)(pbVar5 + bVar1);
    local_c2 = *(undefined2 *)(pbVar5 + bVar1 + 2);
  }
  else {
    if (local_c0 == 0x11) {
      bVar1 = pbVar5[10];
      goto LAB_000208dc;
    }
    local_c4 = 0;
    local_c2 = 0;
  }
  local_7c = (ushort)local_c0;
  uVar4 = (uint)pbVar7[5];
  local_bc = *(byte **)(pbVar7 + uVar4);
  local_b0 = pbVar7[uVar4 + 9];
  local_b8 = *(byte **)(pbVar7 + uVar4 + 4);
  local_af = pbVar7[uVar4 + 8];
  if (local_b0 == 6) {
    bVar1 = pbVar7[9];
LAB_000206f8:
    local_b4 = *(undefined2 *)(pbVar7 + bVar1);
    local_b2 = *(undefined2 *)(pbVar7 + bVar1 + 2);
  }
  else {
    if (local_b0 == 0x11) {
      bVar1 = pbVar7[10];
      goto LAB_000206f8;
    }
    local_b4 = 0;
    local_b2 = local_b4;
  }
  if (local_c8 == local_b8) {
    if (local_cc != local_bc) {
      local_60 = local_b4;
      local_54 = 1;
      local_6c = local_bc;
      goto LAB_00020724;
    }
    local_54 = 0;
    if (bVar2) {
      local_60 = local_b4;
      local_6c = local_cc;
      goto LAB_00020930;
    }
    local_60 = local_b2;
    local_6c = local_c8;
  }
  else {
    if (local_cc != local_bc) {
      return 0;
    }
    local_54 = 2;
    local_60 = local_b2;
    local_6c = local_b8;
LAB_00020724:
    if (bVar2) {
LAB_00020930:
      if (local_80 == 2) {
        uVar4 = (uint)pbVar7[7];
        local_48 = pbVar7 + uVar4 + 8;
        local_44 = pbVar7 + uVar4 + 0x18;
        local_50 = pbVar7[uVar4 + 1] >> 4 | pbVar7[uVar4] << 4;
        local_4c = (uint)CONCAT11(pbVar7[uVar4 + 2],pbVar7[uVar4 + 3]) |
                   (pbVar7[uVar4 + 1] & 0xf) << 0x10;
        local_4f = pbVar7[uVar4 + 7];
      }
    }
  }
  local_8c = local_cc;
  local_88 = local_c8;
  local_84 = local_c4;
  local_82 = local_c2;
  if (local_bf != local_af) {
    local_3f = local_3f | 0x10;
    local_40 = local_af;
  }
LAB_0002074c:
  local_64 = pbVar7 + pbVar7[1] + 6;
  local_68 = pbVar7 + pbVar7[1];
  local_3f = local_3f & 0xfc | pbVar5[3] & 1 ^ 1 | (pbVar7[3] & 1 ^ 1) << 1;
  if ((pbVar5[3] & 1) == 0) {
    local_5c = *(undefined2 *)(pbVar5 + pbVar5[3] + 2);
  }
  else {
    local_5c = 0;
  }
  if ((pbVar7[3] & 1) == 0) {
    local_5e = *(undefined2 *)(pbVar7 + pbVar7[3] + 2);
  }
  else {
    local_5e = 0;
  }
  if (((pbVar5[2] & 1) == 0) && (*(short *)(pbVar5 + pbVar5[2]) != -1)) {
    local_3f = local_3f | 4;
    if ((pbVar5[2] & 1) == 0) {
      local_5a = *(undefined2 *)(pbVar5 + pbVar5[2]);
    }
    else {
      local_5a = 0xffff;
    }
  }
  if (((pbVar7[2] & 1) == 0) && (*(short *)(pbVar7 + pbVar7[2]) != -1)) {
    local_3f = local_3f | 8;
    if ((pbVar7[2] & 1) == 0) {
      local_58 = *(undefined2 *)(pbVar7 + pbVar7[2]);
    }
    else {
      local_58 = 0xffff;
    }
  }
  local_3a = *(short *)(param_2 + 0x98);
  bVar2 = (bool)(bVar2 ^ 1);
  if (local_80 != 2) {
    bVar2 = false;
  }
  if (bVar2) {
    local_3a = local_3a + -0x28;
  }
  puVar6 = *(undefined4 **)(param_2 + 0x9c);
  local_38 = *puVar6;
  local_34 = puVar6[1];
  local_30 = puVar6[2];
  local_2c = puVar6[3];
  local_28 = puVar6[4];
  local_24 = puVar6[5];
  iVar3 = (*DAT_0002b910)(&local_8c,&local_d0);
  if (iVar3 == 0) {
    return 0;
  }
  return local_d0;
}

