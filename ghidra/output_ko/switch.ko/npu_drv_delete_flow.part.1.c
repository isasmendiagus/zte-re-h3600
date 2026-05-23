// module: switch.ko
// function: npu_drv_delete_flow.part.1 @ 0x20d2c
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
  byte *local_c4;
  byte *local_c0;
  undefined2 local_bc;
  undefined2 local_ba;
  byte local_b8;
  byte local_b7;
  byte *local_b4;
  byte *local_b0;
  undefined2 local_ac;
  undefined2 local_aa;
  byte local_a8;
  byte local_a7;
  byte *local_a4;
  byte *local_a0;
  undefined2 local_9c;
  undefined2 local_9a;
  byte local_98;
  byte local_97;
  byte *local_94;
  byte *local_90;
  undefined2 local_8c;
  undefined2 local_8a;
  byte local_88;
  byte local_87;
  byte *local_84;
  byte *local_80;
  undefined2 local_7c;
  undefined2 local_7a;
  int local_78;
  ushort local_74;
  undefined1 local_70;
  undefined1 local_6f;
  char *local_6c;
  int local_68;
  byte *local_64;
  byte *local_60;
  byte *local_5c;
  undefined2 local_58;
  undefined2 local_56;
  undefined2 local_54;
  undefined2 local_52;
  undefined2 local_50;
  undefined4 local_4c;
  byte local_48;
  byte local_47;
  uint local_44;
  byte *local_40;
  byte *local_3c;
  byte local_38;
  byte local_37;
  short local_32;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  __memzero(&local_84,0x6c);
  __memzero(&local_c4,0x10);
  __memzero(&local_b4,0x10);
  __memzero(&local_a4,0x10);
  __memzero(&local_94,0x10);
  if (param_1 == 0) {
    return -1;
  }
  pbVar7 = *(byte **)(param_1 + 0x14);
  __s2 = *(char **)(pbVar7 + *pbVar7);
  if (__s2 == (char *)0x0) {
    return -1;
  }
  local_6c = __s2;
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
  local_68 = *(int *)(pbVar5 + *pbVar5);
  if (local_68 == 0) {
    return -1;
  }
  if ((*(uint *)(param_1 + 0x28) & 0x1000000) == 0) {
    if ((*(uint *)(param_1 + 0x28) & 0x2000000) != 0) {
      local_6f = 1;
    }
  }
  else {
    local_70 = 1;
  }
  uVar4 = *(uint *)(param_1 + 0x28);
  if ((uVar4 & 0x1c) == 0) {
    if ((uVar4 & 0x700) != 0) {
      local_78 = 1;
      uVar4 = (uint)pbVar5[7];
      local_a0 = pbVar5 + uVar4 + 0x18;
      local_98 = pbVar5[uVar4 + 6];
      local_a4 = pbVar5 + uVar4 + 8;
      local_97 = pbVar5[uVar4 + 1] >> 4 | pbVar5[uVar4] << 4;
      if (local_98 == 6) {
        bVar1 = pbVar5[9];
LAB_0002130c:
        local_9c = *(undefined2 *)(pbVar5 + bVar1);
        local_9a = *(undefined2 *)(pbVar5 + bVar1 + 2);
      }
      else {
        if (local_98 == 0x11) {
          bVar1 = pbVar5[10];
          goto LAB_0002130c;
        }
        local_9c = 0;
        local_9a = 0;
      }
      local_74 = (ushort)local_98;
      uVar4 = (uint)pbVar7[7];
      local_90 = pbVar7 + uVar4 + 0x18;
      local_88 = pbVar7[uVar4 + 6];
      local_94 = pbVar7 + uVar4 + 8;
      local_87 = pbVar7[uVar4 + 1] >> 4 | pbVar7[uVar4] << 4;
      if (local_88 == 6) {
        bVar1 = pbVar7[9];
LAB_00021328:
        local_8c = *(undefined2 *)(pbVar7 + bVar1);
        local_8a = *(undefined2 *)(pbVar7 + bVar1 + 2);
      }
      else {
        if (local_88 == 0x11) {
          bVar1 = pbVar7[10];
          goto LAB_00021328;
        }
        local_8c = 0;
        local_8a = local_8c;
      }
      local_84 = local_a4;
      local_80 = local_a0;
      local_7c = local_9c;
      local_7a = local_9a;
      if (local_97 != local_87) {
        local_37 = local_37 | 0x10;
        local_38 = local_87;
      }
      goto LAB_00020eec;
    }
    if ((uVar4 & 0x60) == 0) {
      return -1;
    }
    local_78 = 2;
  }
  else {
    local_78 = 0;
  }
  uVar4 = (uint)pbVar5[5];
  local_c4 = *(byte **)(pbVar5 + uVar4);
  local_b8 = pbVar5[uVar4 + 9];
  local_c0 = *(byte **)(pbVar5 + uVar4 + 4);
  local_b7 = pbVar5[uVar4 + 8];
  if (local_b8 == 6) {
    bVar1 = pbVar5[9];
LAB_00021218:
    local_bc = *(undefined2 *)(pbVar5 + bVar1);
    local_ba = *(undefined2 *)(pbVar5 + bVar1 + 2);
  }
  else {
    if (local_b8 == 0x11) {
      bVar1 = pbVar5[10];
      goto LAB_00021218;
    }
    local_bc = 0;
    local_ba = 0;
  }
  local_74 = (ushort)local_b8;
  uVar4 = (uint)pbVar7[5];
  local_b4 = *(byte **)(pbVar7 + uVar4);
  local_a8 = pbVar7[uVar4 + 9];
  local_b0 = *(byte **)(pbVar7 + uVar4 + 4);
  local_a7 = pbVar7[uVar4 + 8];
  if (local_a8 == 6) {
    bVar1 = pbVar7[9];
LAB_00021234:
    local_ac = *(undefined2 *)(pbVar7 + bVar1);
    local_aa = *(undefined2 *)(pbVar7 + bVar1 + 2);
  }
  else {
    if (local_a8 == 0x11) {
      bVar1 = pbVar7[10];
      goto LAB_00021234;
    }
    local_ac = 0;
    local_aa = local_ac;
  }
  if (local_c0 == local_b0) {
    if (local_c4 != local_b4) {
      local_58 = local_ac;
      local_4c = 1;
      local_64 = local_b4;
      goto LAB_00020ec4;
    }
    local_4c = 0;
    if (bVar2) {
      local_58 = local_ac;
      local_64 = local_c4;
      goto LAB_00021290;
    }
    local_58 = local_aa;
    local_64 = local_c0;
  }
  else {
    if (local_c4 != local_b4) {
      return -1;
    }
    local_4c = 2;
    local_58 = local_aa;
    local_64 = local_b0;
LAB_00020ec4:
    if (bVar2) {
LAB_00021290:
      if (local_78 == 2) {
        uVar4 = (uint)pbVar7[7];
        local_40 = pbVar7 + uVar4 + 8;
        local_3c = pbVar7 + uVar4 + 0x18;
        local_48 = pbVar7[uVar4 + 1] >> 4 | pbVar7[uVar4] << 4;
        local_44 = (uint)CONCAT11(pbVar7[uVar4 + 2],pbVar7[uVar4 + 3]) |
                   (pbVar7[uVar4 + 1] & 0xf) << 0x10;
        local_47 = pbVar7[uVar4 + 7];
      }
    }
  }
  local_84 = local_c4;
  local_80 = local_c0;
  local_7c = local_bc;
  local_7a = local_ba;
  if (local_b7 != local_a7) {
    local_37 = local_37 | 0x10;
    local_38 = local_a7;
  }
LAB_00020eec:
  local_5c = pbVar7 + pbVar7[1] + 6;
  local_60 = pbVar7 + pbVar7[1];
  local_37 = local_37 & 0xfc | pbVar5[3] & 1 ^ 1 | (pbVar7[3] & 1 ^ 1) << 1;
  if ((pbVar5[3] & 1) == 0) {
    local_54 = *(undefined2 *)(pbVar5 + pbVar5[3] + 2);
  }
  else {
    local_54 = 0;
  }
  if ((pbVar7[3] & 1) == 0) {
    local_56 = *(undefined2 *)(pbVar7 + pbVar7[3] + 2);
  }
  else {
    local_56 = 0;
  }
  if (((pbVar5[2] & 1) == 0) && (*(short *)(pbVar5 + pbVar5[2]) != -1)) {
    local_37 = local_37 | 4;
    if ((pbVar5[2] & 1) == 0) {
      local_52 = *(undefined2 *)(pbVar5 + pbVar5[2]);
    }
    else {
      local_52 = 0xffff;
    }
  }
  if (((pbVar7[2] & 1) == 0) && (*(short *)(pbVar7 + pbVar7[2]) != -1)) {
    local_37 = local_37 | 8;
    if ((pbVar7[2] & 1) == 0) {
      local_50 = *(undefined2 *)(pbVar7 + pbVar7[2]);
    }
    else {
      local_50 = 0xffff;
    }
  }
  local_32 = *(short *)(param_1 + 0x98);
  bVar2 = (bool)(bVar2 ^ 1);
  if (local_78 != 2) {
    bVar2 = false;
  }
  if (bVar2) {
    local_32 = local_32 + -0x28;
  }
  puVar6 = *(undefined4 **)(param_1 + 0x9c);
  local_30 = *puVar6;
  local_2c = puVar6[1];
  local_28 = puVar6[2];
  local_24 = puVar6[3];
  local_20 = puVar6[4];
  local_1c = puVar6[5];
  kfree(puVar6);
  *(undefined4 *)(param_1 + 0x9c) = 0;
  uVar4 = (*DAT_0002b90c)(&local_84);
  return -((uVar4 ^ 1) & 0xff);
}

