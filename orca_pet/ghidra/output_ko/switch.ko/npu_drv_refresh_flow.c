// module: switch.ko
// function: npu_drv_refresh_flow @ 0x2042c
// size: 1604 bytes
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
  undefined4 local_d4;
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
  short local_3e;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_d4 = 0;
  if (DAT_0002bbc0 == (code *)0x0) {
    return 0;
  }
  if (*(int *)(*(int *)(param_2 + 0x34) + 0x14) - 4U < 2) {
    return 1;
  }
  __memzero(&local_90,0x70);
  __memzero(&local_d0,0x10);
  __memzero(&local_c0,0x10);
  __memzero(&local_b0,0x10);
  __memzero(&local_a0,0x10);
  if (param_2 == 0) {
    return 0;
  }
  pbVar7 = *(byte **)(param_2 + 0x14);
  __s2 = *(char **)(pbVar7 + *pbVar7);
  if (__s2 == (char *)0x0) {
    return 0;
  }
  local_78 = __s2;
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
  local_74 = *(int *)(pbVar5 + *pbVar5);
  if (local_74 == 0) {
    return 0;
  }
  if ((*(uint *)(param_2 + 0x28) & 0x1000000) == 0) {
    if ((*(uint *)(param_2 + 0x28) & 0x2000000) != 0) {
      local_7b = 1;
    }
  }
  else {
    local_7c = 1;
  }
  uVar4 = *(uint *)(param_2 + 0x28);
  if ((uVar4 & 0x1c) == 0) {
    if ((uVar4 & 0x700) != 0) {
      local_84 = 1;
      uVar4 = (uint)pbVar5[7];
      local_ac = pbVar5 + uVar4 + 0x18;
      local_a4 = pbVar5[uVar4 + 6];
      local_b0 = pbVar5 + uVar4 + 8;
      local_a3 = pbVar5[uVar4 + 1] >> 4 | pbVar5[uVar4] << 4;
      if (local_a4 == 6) {
        bVar1 = pbVar5[9];
LAB_0002095c:
        local_a8 = *(undefined2 *)(pbVar5 + bVar1);
        local_a6 = *(undefined2 *)(pbVar5 + bVar1 + 2);
      }
      else {
        if (local_a4 == 0x11) {
          bVar1 = pbVar5[10];
          goto LAB_0002095c;
        }
        local_a8 = 0;
        local_a6 = 0;
      }
      local_80 = (ushort)local_a4;
      uVar4 = (uint)pbVar7[7];
      local_9c = pbVar7 + uVar4 + 0x18;
      local_94 = pbVar7[uVar4 + 6];
      local_a0 = pbVar7 + uVar4 + 8;
      local_93 = pbVar7[uVar4 + 1] >> 4 | pbVar7[uVar4] << 4;
      if (local_94 == 6) {
        bVar1 = pbVar7[9];
LAB_00020a3c:
        local_98 = *(undefined2 *)(pbVar7 + bVar1);
        local_96 = *(undefined2 *)(pbVar7 + bVar1 + 2);
      }
      else {
        if (local_94 == 0x11) {
          bVar1 = pbVar7[10];
          goto LAB_00020a3c;
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
      goto LAB_000207e0;
    }
    if ((uVar4 & 0x60) == 0) {
      return 0;
    }
    local_84 = 2;
  }
  else {
    local_84 = 0;
  }
  uVar4 = (uint)pbVar5[5];
  local_d0 = *(byte **)(pbVar5 + uVar4);
  local_c4 = pbVar5[uVar4 + 9];
  local_cc = *(byte **)(pbVar5 + uVar4 + 4);
  local_c3 = pbVar5[uVar4 + 8];
  if (local_c4 == 6) {
    bVar1 = pbVar5[9];
LAB_00020978:
    local_c8 = *(undefined2 *)(pbVar5 + bVar1);
    local_c6 = *(undefined2 *)(pbVar5 + bVar1 + 2);
  }
  else {
    if (local_c4 == 0x11) {
      bVar1 = pbVar5[10];
      goto LAB_00020978;
    }
    local_c8 = 0;
    local_c6 = 0;
  }
  local_80 = (ushort)local_c4;
  uVar4 = (uint)pbVar7[5];
  local_c0 = *(byte **)(pbVar7 + uVar4);
  local_b4 = pbVar7[uVar4 + 9];
  local_bc = *(byte **)(pbVar7 + uVar4 + 4);
  local_b3 = pbVar7[uVar4 + 8];
  if (local_b4 == 6) {
    bVar1 = pbVar7[9];
LAB_0002078c:
    local_b8 = *(undefined2 *)(pbVar7 + bVar1);
    local_b6 = *(undefined2 *)(pbVar7 + bVar1 + 2);
  }
  else {
    if (local_b4 == 0x11) {
      bVar1 = pbVar7[10];
      goto LAB_0002078c;
    }
    local_b8 = 0;
    local_b6 = local_b8;
  }
  if (local_cc == local_bc) {
    if (local_d0 != local_c0) {
      local_64 = local_b8;
      local_58 = 1;
      local_70 = local_c0;
      goto LAB_000207b8;
    }
    local_58 = 0;
    if (bVar2) {
      local_64 = local_b8;
      local_70 = local_d0;
      goto LAB_000209cc;
    }
    local_64 = local_b6;
    local_70 = local_cc;
  }
  else {
    if (local_d0 != local_c0) {
      return 0;
    }
    local_58 = 2;
    local_64 = local_b6;
    local_70 = local_bc;
LAB_000207b8:
    if (bVar2) {
LAB_000209cc:
      if (local_84 == 2) {
        uVar4 = (uint)pbVar7[7];
        local_4c = pbVar7 + uVar4 + 8;
        local_48 = pbVar7 + uVar4 + 0x18;
        local_54 = pbVar7[uVar4 + 1] >> 4 | pbVar7[uVar4] << 4;
        local_50 = (uint)CONCAT11(pbVar7[uVar4 + 2],pbVar7[uVar4 + 3]) |
                   (pbVar7[uVar4 + 1] & 0xf) << 0x10;
        local_53 = pbVar7[uVar4 + 7];
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
LAB_000207e0:
  local_68 = pbVar7 + pbVar7[1] + 6;
  local_6c = pbVar7 + pbVar7[1];
  local_43 = local_43 & 0xfc | pbVar5[3] & 1 ^ 1 | (pbVar7[3] & 1 ^ 1) << 1;
  if ((pbVar5[3] & 1) == 0) {
    local_60 = *(undefined2 *)(pbVar5 + pbVar5[3] + 2);
  }
  else {
    local_60 = 0;
  }
  if ((pbVar7[3] & 1) == 0) {
    local_62 = *(undefined2 *)(pbVar7 + pbVar7[3] + 2);
  }
  else {
    local_62 = 0;
  }
  if (((pbVar5[2] & 1) == 0) && (*(short *)(pbVar5 + pbVar5[2]) != -1)) {
    local_43 = local_43 | 4;
    if ((pbVar5[2] & 1) == 0) {
      local_5e = *(undefined2 *)(pbVar5 + pbVar5[2]);
    }
    else {
      local_5e = 0xffff;
    }
  }
  if (((pbVar7[2] & 1) == 0) && (*(short *)(pbVar7 + pbVar7[2]) != -1)) {
    local_43 = local_43 | 8;
    if ((pbVar7[2] & 1) == 0) {
      local_5c = *(undefined2 *)(pbVar7 + pbVar7[2]);
    }
    else {
      local_5c = 0xffff;
    }
  }
  local_3e = *(short *)(param_2 + 0x98);
  bVar2 = (bool)(bVar2 ^ 1);
  if (local_84 != 2) {
    bVar2 = false;
  }
  if (bVar2) {
    local_3e = local_3e + -0x28;
  }
  puVar6 = *(undefined4 **)(param_2 + 0x9c);
  local_3c = *puVar6;
  local_38 = puVar6[1];
  local_34 = puVar6[2];
  local_30 = puVar6[3];
  local_2c = puVar6[4];
  local_28 = puVar6[5];
  local_24 = puVar6[6];
  iVar3 = (*DAT_0002bbc0)(&local_90,&local_d4);
  if (iVar3 == 0) {
    return 0;
  }
  return local_d4;
}

