// module: switch.ko
// function: npu_drv_create_flow.part.2 @ 0x214a8
// size: 2152 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 npu_drv_create_flow_part_2(int param_1)

{
  byte bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  byte *pbVar8;
  char cVar9;
  char *pcVar10;
  byte *pbVar11;
  undefined4 local_d4;
  undefined1 local_d0;
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
  char local_3b;
  short local_3a;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  __memzero(&local_d4,8);
  __memzero(&local_8c,0x6c);
  if (param_1 == 0) {
    return 0xffffffff;
  }
  pcVar10 = *(char **)(*(byte **)(param_1 + 0x14) + **(byte **)(param_1 + 0x14));
  if (pcVar10 == (char *)0x0) {
    return 0xffffffff;
  }
  iVar3 = strcmp("pon0",pcVar10);
  if (((((iVar3 == 0) || (iVar3 = strcmp("pon",pcVar10), iVar3 == 0)) ||
       (iVar3 = strcmp("gpon0",pcVar10), iVar3 == 0)) ||
      ((iVar3 = strcmp("epon0",pcVar10), iVar3 == 0 || (iVar3 = strcmp("mii1",pcVar10), iVar3 == 0))
      )) || ((iVar3 = strcmp("eth0",pcVar10), iVar3 == 0 ||
             (iVar3 = strcmp("ptm0",pcVar10), iVar3 == 0)))) {
    local_d0 = 1;
  }
  else {
    local_d0 = 0;
  }
  uVar7 = *(uint *)(param_1 + 0x28);
  if ((uVar7 & 0x1c) == 0) {
    if ((uVar7 & 0x700) == 0) {
      if ((uVar7 & 0x60) == 0) {
        return 0xffffffff;
      }
      local_d4 = 2;
    }
    else {
      local_d4 = 1;
    }
  }
  else {
    local_d4 = 0;
  }
  if ((DAT_0002b914 != (code *)0x0) && (iVar3 = (*DAT_0002b914)(&local_d4), iVar3 == 0)) {
    return 0xffffffff;
  }
  __memzero(&local_cc,0x10);
  __memzero(&local_bc,0x10);
  __memzero(&local_ac,0x10);
  __memzero(&local_9c,0x10);
  pbVar11 = *(byte **)(param_1 + 0x14);
  pcVar10 = *(char **)(pbVar11 + *pbVar11);
  if (pcVar10 == (char *)0x0) {
    return 0xffffffff;
  }
  local_74 = pcVar10;
  iVar3 = strcmp("pon0",pcVar10);
  if ((((iVar3 == 0) || (iVar3 = strcmp("pon",pcVar10), iVar3 == 0)) ||
      (iVar3 = strcmp("gpon0",pcVar10), iVar3 == 0)) ||
     (((iVar3 = strcmp("epon0",pcVar10), iVar3 == 0 || (iVar3 = strcmp("mii1",pcVar10), iVar3 == 0))
      || (iVar3 = strcmp("eth0",pcVar10), iVar3 == 0)))) {
    bVar2 = true;
  }
  else {
    iVar3 = strcmp("ptm0",pcVar10);
    bVar2 = iVar3 == 0;
  }
  pcVar10 = local_74;
  pbVar8 = *(byte **)(param_1 + 0x10);
  local_70 = *(int *)(pbVar8 + *pbVar8);
  if (local_70 == 0) {
    return 0xffffffff;
  }
  if ((*(uint *)(param_1 + 0x28) & 0x1000000) == 0) {
    if ((*(uint *)(param_1 + 0x28) & 0x2000000) != 0) {
      local_77 = 1;
    }
  }
  else {
    local_78 = 1;
  }
  uVar7 = *(uint *)(param_1 + 0x28);
  if ((uVar7 & 0x1c) == 0) {
    if ((uVar7 & 0x700) != 0) {
      local_80 = 1;
      uVar7 = (uint)pbVar8[7];
      local_a8 = pbVar8 + uVar7 + 0x18;
      local_a0 = pbVar8[uVar7 + 6];
      local_ac = pbVar8 + uVar7 + 8;
      local_9f = pbVar8[uVar7 + 1] >> 4 | pbVar8[uVar7] << 4;
      if (local_a0 == 6) {
        bVar1 = pbVar8[9];
LAB_00021cd4:
        local_a4 = *(undefined2 *)(pbVar8 + bVar1);
        local_a2 = *(undefined2 *)(pbVar8 + bVar1 + 2);
      }
      else {
        if (local_a0 == 0x11) {
          bVar1 = pbVar8[10];
          goto LAB_00021cd4;
        }
        local_a4 = 0;
        local_a2 = 0;
      }
      local_7c = (ushort)local_a0;
      uVar7 = (uint)pbVar11[7];
      local_98 = pbVar11 + uVar7 + 0x18;
      local_90 = pbVar11[uVar7 + 6];
      local_9c = pbVar11 + uVar7 + 8;
      local_8f = pbVar11[uVar7 + 1] >> 4 | pbVar11[uVar7] << 4;
      if (local_90 == 6) {
        bVar1 = pbVar11[9];
LAB_00021cf0:
        local_94 = *(undefined2 *)(pbVar11 + bVar1);
        local_92 = *(undefined2 *)(pbVar11 + bVar1 + 2);
      }
      else {
        if (local_90 == 0x11) {
          bVar1 = pbVar11[10];
          goto LAB_00021cf0;
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
      goto LAB_000218ac;
    }
    if ((uVar7 & 0x60) == 0) {
      return 0xffffffff;
    }
    local_80 = 2;
  }
  else {
    local_80 = 0;
  }
  uVar7 = (uint)pbVar8[5];
  local_cc = *(byte **)(pbVar8 + uVar7);
  local_c0 = pbVar8[uVar7 + 9];
  local_c8 = *(byte **)(pbVar8 + uVar7 + 4);
  local_bf = pbVar8[uVar7 + 8];
  if (local_c0 == 6) {
    bVar1 = pbVar8[9];
LAB_00021ba0:
    local_c4 = *(undefined2 *)(pbVar8 + bVar1);
    local_c2 = *(undefined2 *)(pbVar8 + bVar1 + 2);
  }
  else {
    if (local_c0 == 0x11) {
      bVar1 = pbVar8[10];
      goto LAB_00021ba0;
    }
    local_c4 = 0;
    local_c2 = 0;
  }
  local_7c = (ushort)local_c0;
  uVar7 = (uint)pbVar11[5];
  local_bc = *(byte **)(pbVar11 + uVar7);
  local_b0 = pbVar11[uVar7 + 9];
  local_b8 = *(byte **)(pbVar11 + uVar7 + 4);
  local_af = pbVar11[uVar7 + 8];
  if (local_b0 == 6) {
    bVar1 = pbVar11[9];
LAB_00021bfc:
    local_b4 = *(undefined2 *)(pbVar11 + bVar1);
    local_b2 = *(undefined2 *)(pbVar11 + bVar1 + 2);
  }
  else {
    if (local_b0 == 0x11) {
      bVar1 = pbVar11[10];
      goto LAB_00021bfc;
    }
    local_b4 = 0;
    local_b2 = local_b4;
  }
  if (local_c8 == local_b8) {
    if (local_cc != local_bc) {
      local_60 = local_b4;
      local_54 = 1;
      local_6c = local_bc;
      goto LAB_00021884;
    }
    local_54 = 0;
    if (bVar2) {
      local_60 = local_b4;
      local_6c = local_cc;
      goto LAB_00021c58;
    }
    local_60 = local_b2;
    local_6c = local_c8;
  }
  else {
    if (local_cc != local_bc) {
      return 0xffffffff;
    }
    local_54 = 2;
    local_60 = local_b2;
    local_6c = local_b8;
LAB_00021884:
    if (bVar2) {
LAB_00021c58:
      if (local_80 == 2) {
        uVar7 = (uint)pbVar11[7];
        local_48 = pbVar11 + uVar7 + 8;
        local_44 = pbVar11 + uVar7 + 0x18;
        local_50 = pbVar11[uVar7 + 1] >> 4 | pbVar11[uVar7] << 4;
        local_4c = (uint)CONCAT11(pbVar11[uVar7 + 2],pbVar11[uVar7 + 3]) |
                   (pbVar11[uVar7 + 1] & 0xf) << 0x10;
        local_4f = pbVar11[uVar7 + 7];
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
LAB_000218ac:
  local_64 = pbVar11 + pbVar11[1] + 6;
  local_68 = pbVar11 + pbVar11[1];
  local_3f = local_3f & 0xfc | pbVar8[3] & 1 ^ 1 | (pbVar11[3] & 1 ^ 1) << 1;
  if ((pbVar8[3] & 1) == 0) {
    local_5c = *(undefined2 *)(pbVar8 + pbVar8[3] + 2);
  }
  else {
    local_5c = 0;
  }
  if ((pbVar11[3] & 1) == 0) {
    local_5e = *(undefined2 *)(pbVar11 + pbVar11[3] + 2);
  }
  else {
    local_5e = 0;
  }
  if (((pbVar8[2] & 1) == 0) && (*(short *)(pbVar8 + pbVar8[2]) != -1)) {
    local_3f = local_3f | 4;
    if ((pbVar8[2] & 1) == 0) {
      local_5a = *(undefined2 *)(pbVar8 + pbVar8[2]);
    }
    else {
      local_5a = 0xffff;
    }
  }
  if (((pbVar11[2] & 1) == 0) && (*(short *)(pbVar11 + pbVar11[2]) != -1)) {
    local_3f = local_3f | 8;
    if ((pbVar11[2] & 1) == 0) {
      local_58 = *(undefined2 *)(pbVar11 + pbVar11[2]);
    }
    else {
      local_58 = 0xffff;
    }
  }
  local_3a = *(short *)(param_1 + 0x98);
  bVar2 = (bool)(bVar2 ^ 1);
  if (local_80 != 2) {
    bVar2 = false;
  }
  if (bVar2) {
    local_3a = local_3a + -0x28;
  }
  bVar1 = *pbVar11;
  iVar3 = strcmp("eth0",local_74);
  if (iVar3 == 0) {
    iVar3 = dev_get_by_name(&init_net,&_LC2);
  }
  else {
    iVar3 = dev_get_by_name(&init_net,pcVar10);
  }
  if (iVar3 == 0) {
    local_3b = '\0';
  }
  else {
    iVar4 = __alloc_skb(0x40,0x20,0,0xffffffff);
    if (iVar4 == 0) {
      disableIRQinterrupts();
      iVar4 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
      *(int *)(iVar4 + *(int *)(iVar3 + 0x280)) = *(int *)(iVar4 + *(int *)(iVar3 + 0x280)) + -1;
      local_3b = '\0';
    }
    else {
      *(undefined4 *)(iVar4 + 0x80) = *(undefined4 *)(pbVar11 + bVar1 + 4);
      iVar5 = CSPKernel_skb_SelectQueue(iVar4,iVar3);
      if (iVar5 - 1U < 8) {
        cVar9 = '\b' - (char)iVar5;
      }
      else if (iVar5 == 0x8f) {
        cVar9 = '\a';
      }
      else {
        cVar9 = '\0';
      }
      disableIRQinterrupts();
      iVar5 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
      *(int *)(iVar5 + *(int *)(iVar3 + 0x280)) = *(int *)(iVar5 + *(int *)(iVar3 + 0x280)) + -1;
      kfree_skb(iVar4);
      local_3b = cVar9;
    }
  }
  iVar3 = (*npu_hff_func_tbl)(&local_8c);
  if ((iVar3 != 0) &&
     (puVar6 = (undefined4 *)kmem_cache_alloc(_CspGetPortInfo,0x80d0), puVar6 != (undefined4 *)0x0))
  {
    *(undefined4 **)(param_1 + 0x9c) = puVar6;
    *puVar6 = local_38;
    *(undefined4 *)(*(int *)(param_1 + 0x9c) + 4) = local_34;
    *(undefined4 *)(*(int *)(param_1 + 0x9c) + 8) = local_30;
    *(undefined4 *)(*(int *)(param_1 + 0x9c) + 0xc) = local_2c;
    *(undefined4 *)(*(int *)(param_1 + 0x9c) + 0x10) = local_28;
    *(undefined4 *)(*(int *)(param_1 + 0x9c) + 0x14) = local_24;
    return 0;
  }
  return 0xffffffff;
}

