// module: mt7915.ko
// function: RT_AES_KeyExpansion @ 0x121e64
// size: 548 bytes
//

void RT_AES_KeyExpansion(int param_1,uint param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int extraout_r1;
  byte bVar5;
  uint uVar6;
  int iVar7;
  byte bVar8;
  undefined1 *puVar9;
  byte bVar10;
  undefined1 *puVar11;
  uint uVar12;
  undefined1 *puVar13;
  byte *pbVar14;
  undefined1 *puVar15;
  byte *local_48;
  byte *local_44;
  byte *local_40;
  byte *local_3c;
  byte *local_38;
  uint local_34;
  
  param_2 = param_2 >> 2;
  if (param_2 == 0) {
    local_34 = 0x1c;
  }
  else {
    puVar13 = (undefined1 *)(param_3 + 0xf);
    puVar11 = (undefined1 *)(param_3 + 0x4b);
    puVar9 = (undefined1 *)(param_3 + 0x87);
    puVar15 = (undefined1 *)(param_3 + 0xc3);
    uVar4 = 0;
    iVar7 = param_1;
    do {
      iVar2 = uVar4 * 4;
      uVar4 = uVar4 + 1;
      puVar13 = puVar13 + 1;
      *puVar13 = *(undefined1 *)(param_1 + iVar2);
      puVar11 = puVar11 + 1;
      *puVar11 = *(undefined1 *)(iVar7 + 1);
      puVar9 = puVar9 + 1;
      *puVar9 = *(undefined1 *)(iVar7 + 2);
      puVar15 = puVar15 + 1;
      *puVar15 = *(undefined1 *)(iVar7 + 3);
      iVar7 = iVar7 + 4;
    } while (uVar4 != param_2);
    local_34 = (param_2 + 7) * 4;
    if (local_34 <= param_2) {
      return;
    }
  }
  pbVar14 = (byte *)(param_3 + param_2 + 0xe);
  local_48 = (byte *)(param_3 + param_2 + 0x4a);
  local_3c = (byte *)(param_3 + param_2 + 0x86);
  local_40 = (byte *)(param_3 + param_2 + 0xc2);
  local_38 = (byte *)(param_3 + param_2 + 0xf);
  local_44 = (byte *)(param_3 + 0xf);
  uVar4 = param_2;
  iVar7 = param_3 + param_2;
  do {
    __aeabi_uidivmod(uVar4,param_2);
    pbVar14 = pbVar14 + 1;
    bVar1 = *pbVar14;
    local_48 = local_48 + 1;
    bVar5 = *local_48;
    local_3c = local_3c + 1;
    bVar10 = *local_3c;
    local_40 = local_40 + 1;
    bVar8 = *local_40;
    if (extraout_r1 == 0) {
      iVar2 = __aeabi_uidiv(uVar4,param_2);
      uVar12 = (uint)bVar10;
      uVar3 = *(undefined4 *)(&_LANCHOR0 + iVar2 * 4);
      bVar10 = (&DAT_00297eb4)[bVar8] ^ (byte)((uint)uVar3 >> 8);
      uVar6 = (uint)bVar5;
      bVar8 = (&DAT_00297eb4)[bVar1] ^ (byte)uVar3;
      bVar5 = (&DAT_00297eb4)[uVar12] ^ (byte)((uint)uVar3 >> 0x10);
      bVar1 = (&DAT_00297eb4)[uVar6] ^ (byte)((uint)uVar3 >> 0x18);
    }
    else if (6 < param_2 && extraout_r1 == 4) {
      bVar1 = (&DAT_00297eb4)[bVar1];
      bVar5 = (&DAT_00297eb4)[bVar5];
      bVar10 = (&DAT_00297eb4)[bVar10];
      bVar8 = (&DAT_00297eb4)[bVar8];
    }
    uVar4 = uVar4 + 1;
    local_44 = local_44 + 1;
    local_38 = local_38 + 1;
    *local_38 = bVar1 ^ *local_44;
    *(byte *)(iVar7 + 0x4c) = bVar5 ^ *(byte *)(param_3 + 0x4c);
    *(byte *)(iVar7 + 0x88) = bVar10 ^ *(byte *)(param_3 + 0x88);
    *(byte *)(iVar7 + 0xc4) = bVar8 ^ *(byte *)(param_3 + 0xc4);
    param_3 = param_3 + 1;
    iVar7 = iVar7 + 1;
  } while (uVar4 < local_34);
  return;
}

