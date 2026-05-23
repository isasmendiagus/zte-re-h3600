// module: switch.ko
// function: npu_drv_delete_flow.part.1 @ 0x20de0
// size: 1564 bytes
//

int npu_drv_delete_flow_part_1(int param_1)

{
  byte bVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  undefined4 *puVar6;
  byte *pbVar7;
  char *__s2;
  byte *local_c8;
  byte *local_c4;
  undefined2 local_c0;
  undefined2 local_be;
  byte local_bc;
  byte local_bb;
  byte *local_b8;
  byte *local_b4;
  undefined2 local_b0;
  undefined2 local_ae;
  byte local_ac;
  byte local_ab;
  byte *local_a8;
  byte *local_a4;
  undefined2 local_a0;
  undefined2 local_9e;
  byte local_9c;
  byte local_9b;
  byte *local_98;
  byte *local_94;
  undefined2 local_90;
  undefined2 local_8e;
  byte local_8c;
  byte local_8b;
  byte *local_88;
  byte *local_84;
  undefined2 local_80;
  undefined2 local_7e;
  int local_7c;
  ushort local_78;
  undefined1 local_74;
  undefined1 local_73;
  char *local_70;
  int local_6c;
  byte *local_68;
  byte *local_64;
  byte *local_60;
  undefined2 local_5c;
  undefined2 local_5a;
  undefined2 local_58;
  undefined2 local_56;
  undefined2 local_54;
  undefined4 local_50;
  byte local_4c;
  byte local_4b;
  uint local_48;
  byte *local_44;
  byte *local_40;
  byte local_3c;
  byte local_3b;
  short local_36;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  __memzero(&local_88,0x70);
  __memzero(&local_c8,0x10);
  __memzero(&local_b8,0x10);
  __memzero(&local_a8,0x10);
  __memzero(&local_98,0x10);
  if (param_1 == 0) {
    return -1;
  }
  pbVar7 = *(byte **)(param_1 + 0x14);
  __s2 = *(char **)(pbVar7 + *pbVar7);
  if (__s2 == (char *)0x0) {
    return -1;
  }
  local_70 = __s2;
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
  pbVar5 = *(byte **)(param_1 + 0x10);
  local_6c = *(int *)(pbVar5 + *pbVar5);
  if (local_6c == 0) {
    return -1;
  }
  if ((*(uint *)(param_1 + 0x28) & 0x1000000) == 0) {
    if ((*(uint *)(param_1 + 0x28) & 0x2000000) != 0) {
      local_73 = 1;
    }
  }
  else {
    local_74 = 1;
  }
  uVar4 = *(uint *)(param_1 + 0x28);
  if ((uVar4 & 0x1c) == 0) {
    if ((uVar4 & 0x700) != 0) {
      local_7c = 1;
      uVar4 = (uint)pbVar5[7];
      local_a4 = pbVar5 + uVar4 + 0x18;
      local_9c = pbVar5[uVar4 + 6];
      local_a8 = pbVar5 + uVar4 + 8;
      local_9b = pbVar5[uVar4 + 1] >> 4 | pbVar5[uVar4] << 4;
      if (local_9c == 6) {
        bVar1 = pbVar5[9];
LAB_000213c0:
        local_a0 = *(undefined2 *)(pbVar5 + bVar1);
        local_9e = *(undefined2 *)(pbVar5 + bVar1 + 2);
      }
      else {
        if (local_9c == 0x11) {
          bVar1 = pbVar5[10];
          goto LAB_000213c0;
        }
        local_a0 = 0;
        local_9e = 0;
      }
      local_78 = (ushort)local_9c;
      uVar4 = (uint)pbVar7[7];
      local_94 = pbVar7 + uVar4 + 0x18;
      local_8c = pbVar7[uVar4 + 6];
      local_98 = pbVar7 + uVar4 + 8;
      local_8b = pbVar7[uVar4 + 1] >> 4 | pbVar7[uVar4] << 4;
      if (local_8c == 6) {
        bVar1 = pbVar7[9];
LAB_000213dc:
        local_90 = *(undefined2 *)(pbVar7 + bVar1);
        local_8e = *(undefined2 *)(pbVar7 + bVar1 + 2);
      }
      else {
        if (local_8c == 0x11) {
          bVar1 = pbVar7[10];
          goto LAB_000213dc;
        }
        local_90 = 0;
        local_8e = local_90;
      }
      local_88 = local_a8;
      local_84 = local_a4;
      local_80 = local_a0;
      local_7e = local_9e;
      if (local_9b != local_8b) {
        local_3b = local_3b | 0x10;
        local_3c = local_8b;
      }
      goto LAB_00020fa0;
    }
    if ((uVar4 & 0x60) == 0) {
      return -1;
    }
    local_7c = 2;
  }
  else {
    local_7c = 0;
  }
  uVar4 = (uint)pbVar5[5];
  local_c8 = *(byte **)(pbVar5 + uVar4);
  local_bc = pbVar5[uVar4 + 9];
  local_c4 = *(byte **)(pbVar5 + uVar4 + 4);
  local_bb = pbVar5[uVar4 + 8];
  if (local_bc == 6) {
    bVar1 = pbVar5[9];
LAB_000212cc:
    local_c0 = *(undefined2 *)(pbVar5 + bVar1);
    local_be = *(undefined2 *)(pbVar5 + bVar1 + 2);
  }
  else {
    if (local_bc == 0x11) {
      bVar1 = pbVar5[10];
      goto LAB_000212cc;
    }
    local_c0 = 0;
    local_be = 0;
  }
  local_78 = (ushort)local_bc;
  uVar4 = (uint)pbVar7[5];
  local_b8 = *(byte **)(pbVar7 + uVar4);
  local_ac = pbVar7[uVar4 + 9];
  local_b4 = *(byte **)(pbVar7 + uVar4 + 4);
  local_ab = pbVar7[uVar4 + 8];
  if (local_ac == 6) {
    bVar1 = pbVar7[9];
LAB_000212e8:
    local_b0 = *(undefined2 *)(pbVar7 + bVar1);
    local_ae = *(undefined2 *)(pbVar7 + bVar1 + 2);
  }
  else {
    if (local_ac == 0x11) {
      bVar1 = pbVar7[10];
      goto LAB_000212e8;
    }
    local_b0 = 0;
    local_ae = local_b0;
  }
  if (local_c4 == local_b4) {
    if (local_c8 != local_b8) {
      local_5c = local_b0;
      local_50 = 1;
      local_68 = local_b8;
      goto LAB_00020f78;
    }
    local_50 = 0;
    if (bVar2) {
      local_5c = local_b0;
      local_68 = local_c8;
      goto LAB_00021344;
    }
    local_5c = local_ae;
    local_68 = local_c4;
  }
  else {
    if (local_c8 != local_b8) {
      return -1;
    }
    local_50 = 2;
    local_5c = local_ae;
    local_68 = local_b4;
LAB_00020f78:
    if (bVar2) {
LAB_00021344:
      if (local_7c == 2) {
        uVar4 = (uint)pbVar7[7];
        local_44 = pbVar7 + uVar4 + 8;
        local_40 = pbVar7 + uVar4 + 0x18;
        local_4c = pbVar7[uVar4 + 1] >> 4 | pbVar7[uVar4] << 4;
        local_48 = (uint)CONCAT11(pbVar7[uVar4 + 2],pbVar7[uVar4 + 3]) |
                   (pbVar7[uVar4 + 1] & 0xf) << 0x10;
        local_4b = pbVar7[uVar4 + 7];
      }
    }
  }
  local_88 = local_c8;
  local_84 = local_c4;
  local_80 = local_c0;
  local_7e = local_be;
  if (local_bb != local_ab) {
    local_3b = local_3b | 0x10;
    local_3c = local_ab;
  }
LAB_00020fa0:
  local_60 = pbVar7 + pbVar7[1] + 6;
  local_64 = pbVar7 + pbVar7[1];
  local_3b = local_3b & 0xfc | pbVar5[3] & 1 ^ 1 | (pbVar7[3] & 1 ^ 1) << 1;
  if ((pbVar5[3] & 1) == 0) {
    local_58 = *(undefined2 *)(pbVar5 + pbVar5[3] + 2);
  }
  else {
    local_58 = 0;
  }
  if ((pbVar7[3] & 1) == 0) {
    local_5a = *(undefined2 *)(pbVar7 + pbVar7[3] + 2);
  }
  else {
    local_5a = 0;
  }
  if (((pbVar5[2] & 1) == 0) && (*(short *)(pbVar5 + pbVar5[2]) != -1)) {
    local_3b = local_3b | 4;
    if ((pbVar5[2] & 1) == 0) {
      local_56 = *(undefined2 *)(pbVar5 + pbVar5[2]);
    }
    else {
      local_56 = 0xffff;
    }
  }
  if (((pbVar7[2] & 1) == 0) && (*(short *)(pbVar7 + pbVar7[2]) != -1)) {
    local_3b = local_3b | 8;
    if ((pbVar7[2] & 1) == 0) {
      local_54 = *(undefined2 *)(pbVar7 + pbVar7[2]);
    }
    else {
      local_54 = 0xffff;
    }
  }
  local_36 = *(short *)(param_1 + 0x98);
  bVar2 = (bool)(bVar2 ^ 1);
  if (local_7c != 2) {
    bVar2 = false;
  }
  if (bVar2) {
    local_36 = local_36 + -0x28;
  }
  puVar6 = *(undefined4 **)(param_1 + 0x9c);
  local_34 = *puVar6;
  local_30 = puVar6[1];
  local_2c = puVar6[2];
  local_28 = puVar6[3];
  local_24 = puVar6[4];
  local_20 = puVar6[5];
  kfree(puVar6);
  *(undefined4 *)(param_1 + 0x9c) = 0;
  uVar4 = (*DAT_0002bbbc)(&local_88);
  return -((uVar4 ^ 1) & 0xff);
}

