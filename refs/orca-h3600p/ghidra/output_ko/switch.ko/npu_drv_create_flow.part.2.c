// module: switch.ko
// function: npu_drv_create_flow.part.2 @ 0x2156c
// size: 2164 bytes
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
  undefined4 local_d8;
  undefined1 local_d4;
  byte *local_d0;
  byte *local_cc;
  undefined2 local_c8;
  undefined2 local_c6;
  byte local_c4;
  byte local_c3;
  byte *local_c0;
  byte *local_bc;
  undefined2 local_b8;
  undefined2 local_b6;
  byte local_b4;
  byte local_b3;
  byte *local_b0;
  byte *local_ac;
  undefined2 local_a8;
  undefined2 local_a6;
  byte local_a4;
  byte local_a3;
  byte *local_a0;
  byte *local_9c;
  undefined2 local_98;
  undefined2 local_96;
  byte local_94;
  byte local_93;
  byte *local_90;
  byte *local_8c;
  undefined2 local_88;
  undefined2 local_86;
  int local_84;
  ushort local_80;
  undefined1 local_7c;
  undefined1 local_7b;
  char *local_78;
  int local_74;
  byte *local_70;
  byte *local_6c;
  byte *local_68;
  undefined2 local_64;
  undefined2 local_62;
  undefined2 local_60;
  undefined2 local_5e;
  undefined2 local_5c;
  undefined4 local_58;
  byte local_54;
  byte local_53;
  uint local_50;
  byte *local_4c;
  byte *local_48;
  byte local_44;
  byte local_43;
  char local_3f;
  short local_3e;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  __memzero(&local_d8,8);
  __memzero(&local_90,0x70);
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
    local_d4 = 1;
  }
  else {
    local_d4 = 0;
  }
  uVar7 = *(uint *)(param_1 + 0x28);
  if ((uVar7 & 0x1c) == 0) {
    if ((uVar7 & 0x700) == 0) {
      if ((uVar7 & 0x60) == 0) {
        return 0xffffffff;
      }
      local_d8 = 2;
    }
    else {
      local_d8 = 1;
    }
  }
  else {
    local_d8 = 0;
  }
  if ((DAT_0002bbc4 != (code *)0x0) && (iVar3 = (*DAT_0002bbc4)(&local_d8), iVar3 == 0)) {
    return 0xffffffff;
  }
  __memzero(&local_d0,0x10);
  __memzero(&local_c0,0x10);
  __memzero(&local_b0,0x10);
  __memzero(&local_a0,0x10);
  pbVar11 = *(byte **)(param_1 + 0x14);
  pcVar10 = *(char **)(pbVar11 + *pbVar11);
  if (pcVar10 == (char *)0x0) {
    return 0xffffffff;
  }
  local_78 = pcVar10;
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
  pcVar10 = local_78;
  pbVar8 = *(byte **)(param_1 + 0x10);
  local_74 = *(int *)(pbVar8 + *pbVar8);
  if (local_74 == 0) {
    return 0xffffffff;
  }
  if ((*(uint *)(param_1 + 0x28) & 0x1000000) == 0) {
    if ((*(uint *)(param_1 + 0x28) & 0x2000000) != 0) {
      local_7b = 1;
    }
  }
  else {
    local_7c = 1;
  }
  uVar7 = *(uint *)(param_1 + 0x28);
  if ((uVar7 & 0x1c) == 0) {
    if ((uVar7 & 0x700) != 0) {
      local_84 = 1;
      uVar7 = (uint)pbVar8[7];
      local_ac = pbVar8 + uVar7 + 0x18;
      local_a4 = pbVar8[uVar7 + 6];
      local_b0 = pbVar8 + uVar7 + 8;
      local_a3 = pbVar8[uVar7 + 1] >> 4 | pbVar8[uVar7] << 4;
      if (local_a4 == 6) {
        bVar1 = pbVar8[9];
LAB_00021da4:
        local_a8 = *(undefined2 *)(pbVar8 + bVar1);
        local_a6 = *(undefined2 *)(pbVar8 + bVar1 + 2);
      }
      else {
        if (local_a4 == 0x11) {
          bVar1 = pbVar8[10];
          goto LAB_00021da4;
        }
        local_a8 = 0;
        local_a6 = 0;
      }
      local_80 = (ushort)local_a4;
      uVar7 = (uint)pbVar11[7];
      local_9c = pbVar11 + uVar7 + 0x18;
      local_94 = pbVar11[uVar7 + 6];
      local_a0 = pbVar11 + uVar7 + 8;
      local_93 = pbVar11[uVar7 + 1] >> 4 | pbVar11[uVar7] << 4;
      if (local_94 == 6) {
        bVar1 = pbVar11[9];
LAB_00021dc0:
        local_98 = *(undefined2 *)(pbVar11 + bVar1);
        local_96 = *(undefined2 *)(pbVar11 + bVar1 + 2);
      }
      else {
        if (local_94 == 0x11) {
          bVar1 = pbVar11[10];
          goto LAB_00021dc0;
        }
        local_98 = 0;
        local_96 = local_98;
      }
      local_90 = local_b0;
      local_8c = local_ac;
      local_88 = local_a8;
      local_86 = local_a6;
      if (local_a3 != local_93) {
        local_43 = local_43 | 0x10;
        local_44 = local_93;
      }
      goto LAB_00021970;
    }
    if ((uVar7 & 0x60) == 0) {
      return 0xffffffff;
    }
    local_84 = 2;
  }
  else {
    local_84 = 0;
  }
  uVar7 = (uint)pbVar8[5];
  local_d0 = *(byte **)(pbVar8 + uVar7);
  local_c4 = pbVar8[uVar7 + 9];
  local_cc = *(byte **)(pbVar8 + uVar7 + 4);
  local_c3 = pbVar8[uVar7 + 8];
  if (local_c4 == 6) {
    bVar1 = pbVar8[9];
LAB_00021c70:
    local_c8 = *(undefined2 *)(pbVar8 + bVar1);
    local_c6 = *(undefined2 *)(pbVar8 + bVar1 + 2);
  }
  else {
    if (local_c4 == 0x11) {
      bVar1 = pbVar8[10];
      goto LAB_00021c70;
    }
    local_c8 = 0;
    local_c6 = 0;
  }
  local_80 = (ushort)local_c4;
  uVar7 = (uint)pbVar11[5];
  local_c0 = *(byte **)(pbVar11 + uVar7);
  local_b4 = pbVar11[uVar7 + 9];
  local_bc = *(byte **)(pbVar11 + uVar7 + 4);
  local_b3 = pbVar11[uVar7 + 8];
  if (local_b4 == 6) {
    bVar1 = pbVar11[9];
LAB_00021ccc:
    local_b8 = *(undefined2 *)(pbVar11 + bVar1);
    local_b6 = *(undefined2 *)(pbVar11 + bVar1 + 2);
  }
  else {
    if (local_b4 == 0x11) {
      bVar1 = pbVar11[10];
      goto LAB_00021ccc;
    }
    local_b8 = 0;
    local_b6 = local_b8;
  }
  if (local_cc == local_bc) {
    if (local_d0 != local_c0) {
      local_64 = local_b8;
      local_58 = 1;
      local_70 = local_c0;
      goto LAB_00021948;
    }
    local_58 = 0;
    if (bVar2) {
      local_64 = local_b8;
      local_70 = local_d0;
      goto LAB_00021d28;
    }
    local_64 = local_b6;
    local_70 = local_cc;
  }
  else {
    if (local_d0 != local_c0) {
      return 0xffffffff;
    }
    local_58 = 2;
    local_64 = local_b6;
    local_70 = local_bc;
LAB_00021948:
    if (bVar2) {
LAB_00021d28:
      if (local_84 == 2) {
        uVar7 = (uint)pbVar11[7];
        local_4c = pbVar11 + uVar7 + 8;
        local_48 = pbVar11 + uVar7 + 0x18;
        local_54 = pbVar11[uVar7 + 1] >> 4 | pbVar11[uVar7] << 4;
        local_50 = (uint)CONCAT11(pbVar11[uVar7 + 2],pbVar11[uVar7 + 3]) |
                   (pbVar11[uVar7 + 1] & 0xf) << 0x10;
        local_53 = pbVar11[uVar7 + 7];
      }
    }
  }
  local_90 = local_d0;
  local_8c = local_cc;
  local_88 = local_c8;
  local_86 = local_c6;
  if (local_c3 != local_b3) {
    local_43 = local_43 | 0x10;
    local_44 = local_b3;
  }
LAB_00021970:
  local_68 = pbVar11 + pbVar11[1] + 6;
  local_6c = pbVar11 + pbVar11[1];
  local_43 = local_43 & 0xfc | pbVar8[3] & 1 ^ 1 | (pbVar11[3] & 1 ^ 1) << 1;
  if ((pbVar8[3] & 1) == 0) {
    local_60 = *(undefined2 *)(pbVar8 + pbVar8[3] + 2);
  }
  else {
    local_60 = 0;
  }
  if ((pbVar11[3] & 1) == 0) {
    local_62 = *(undefined2 *)(pbVar11 + pbVar11[3] + 2);
  }
  else {
    local_62 = 0;
  }
  if (((pbVar8[2] & 1) == 0) && (*(short *)(pbVar8 + pbVar8[2]) != -1)) {
    local_43 = local_43 | 4;
    if ((pbVar8[2] & 1) == 0) {
      local_5e = *(undefined2 *)(pbVar8 + pbVar8[2]);
    }
    else {
      local_5e = 0xffff;
    }
  }
  if (((pbVar11[2] & 1) == 0) && (*(short *)(pbVar11 + pbVar11[2]) != -1)) {
    local_43 = local_43 | 8;
    if ((pbVar11[2] & 1) == 0) {
      local_5c = *(undefined2 *)(pbVar11 + pbVar11[2]);
    }
    else {
      local_5c = 0xffff;
    }
  }
  local_3e = *(short *)(param_1 + 0x98);
  bVar2 = (bool)(bVar2 ^ 1);
  if (local_84 != 2) {
    bVar2 = false;
  }
  if (bVar2) {
    local_3e = local_3e + -0x28;
  }
  bVar1 = *pbVar11;
  iVar3 = strcmp("eth0",local_78);
  if (iVar3 == 0) {
    iVar3 = dev_get_by_name(&init_net,&_LC2);
  }
  else {
    iVar3 = dev_get_by_name(&init_net,pcVar10);
  }
  if (iVar3 == 0) {
    local_3f = '\0';
  }
  else {
    iVar4 = __alloc_skb(0x40,0x20,0,0xffffffff);
    if (iVar4 == 0) {
      disableIRQinterrupts();
      iVar4 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
      *(int *)(iVar4 + *(int *)(iVar3 + 0x280)) = *(int *)(iVar4 + *(int *)(iVar3 + 0x280)) + -1;
      local_3f = '\0';
    }
    else {
      *(undefined4 *)(iVar4 + 0x84) = *(undefined4 *)(pbVar11 + bVar1 + 4);
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
      local_3f = cVar9;
    }
  }
  iVar3 = (*npu_hff_func_tbl)(&local_90);
  if ((iVar3 != 0) &&
     (puVar6 = (undefined4 *)kmem_cache_alloc(_CspGetPortInfo,0x80d0), puVar6 != (undefined4 *)0x0))
  {
    *(undefined4 **)(param_1 + 0x9c) = puVar6;
    *puVar6 = local_3c;
    *(undefined4 *)(*(int *)(param_1 + 0x9c) + 4) = local_38;
    *(undefined4 *)(*(int *)(param_1 + 0x9c) + 8) = local_34;
    *(undefined4 *)(*(int *)(param_1 + 0x9c) + 0xc) = local_30;
    *(undefined4 *)(*(int *)(param_1 + 0x9c) + 0x10) = local_2c;
    *(undefined4 *)(*(int *)(param_1 + 0x9c) + 0x14) = local_28;
    *(undefined4 *)(*(int *)(param_1 + 0x9c) + 0x18) = local_24;
    return 0;
  }
  return 0xffffffff;
}

