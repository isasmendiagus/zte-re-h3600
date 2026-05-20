// module: mt7915.ko
// function: AES_CCM_MAC @ 0x122a8c
// size: 820 bytes
//

void AES_CCM_MAC(int param_1,uint param_2,undefined4 param_3,undefined4 param_4,int param_5,
                uint param_6,int param_7,uint param_8,int param_9,int param_10)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte *pbVar5;
  int iVar6;
  byte *pbVar7;
  byte *pbVar8;
  uint uVar9;
  byte *pbVar10;
  uint uVar11;
  uint uVar12;
  undefined4 local_4c;
  byte local_48 [16];
  byte local_38 [20];
  
  local_4c = 0;
  __memzero(local_48,0x10);
  iVar6 = 0xe - param_6;
  if (param_8 != 0) {
    local_48[0] = local_48[0] | 0x40;
  }
  bVar1 = (byte)iVar6;
  if (param_6 != 0) {
    iVar6 = param_6 - 1;
  }
  local_48[0] = local_48[0] | bVar1 | (byte)((param_9 - 2U >> 1) << 3);
  if (param_6 != 0) {
    pbVar8 = (byte *)(param_5 + -1);
    pbVar7 = local_48;
    do {
      pbVar8 = pbVar8 + 1;
      pbVar7 = pbVar7 + 1;
      *pbVar7 = *pbVar8;
    } while (pbVar8 != (byte *)(param_5 + iVar6));
    if (param_6 < 0xc) goto LAB_00122d6c;
    if (param_6 == 0xc) goto LAB_00122d74;
  }
  else {
LAB_00122d6c:
    local_48[0xc] = (byte)(param_2 >> 0x18);
LAB_00122d74:
    local_48[0xd] = (byte)(param_2 >> 0x10);
  }
  local_48[0xf] = (byte)param_2;
  local_48[0xe] = (byte)(param_2 >> 8);
  __memzero(local_38,0x10);
  local_4c = 0x10;
  RT_AES_Encrypt(local_48,0x10,param_3,param_4,local_38,&local_4c);
  __memzero(local_48,0x10);
  bVar1 = (byte)(param_8 >> 8);
  if (param_8 - 1 < 0xfeff) {
    local_48[1] = (undefined1)param_8;
    uVar9 = 2;
    local_48[0] = bVar1;
  }
  else {
    local_48[3] = (char)(param_8 >> 0x10);
    local_48[5] = (undefined1)param_8;
    local_48[2] = (char)(param_8 >> 0x18);
    local_48[4] = bVar1;
    if (param_8 == 0) goto LAB_00122c6c;
    uVar9 = 6;
  }
  pbVar7 = local_48 + 0xf;
  uVar12 = 0;
  do {
    uVar11 = param_8 - uVar12;
    if (0xf < uVar11) {
      uVar11 = 0x10;
    }
    uVar2 = uVar11 + uVar9;
    pbVar8 = pbVar7;
    pbVar3 = (byte *)((int)&local_4c + 3);
    if (uVar2 < 0x11) {
      if (uVar11 != 0) goto LAB_00122be0;
    }
    else {
      uVar11 = 0x10 - uVar9;
      uVar2 = uVar11 + uVar9;
LAB_00122be0:
      pbVar5 = (byte *)(param_7 + uVar12);
      do {
        if (uVar9 < 0x10) {
          local_48[uVar9] = *pbVar5;
        }
        uVar9 = uVar9 + 1;
        pbVar5 = pbVar5 + 1;
      } while (uVar9 != uVar2);
    }
    do {
      pbVar3 = pbVar3 + 1;
      *pbVar3 = *pbVar3 ^ pbVar8[1];
      pbVar8 = pbVar8 + 1;
    } while (pbVar3 != pbVar7);
    __memzero(local_38,0x10);
    uVar12 = uVar12 + uVar11;
    local_4c = 0x10;
    RT_AES_Encrypt(local_48,0x10,param_3,param_4,local_38,&local_4c);
    __memzero(local_48,0x10);
    uVar9 = 0;
  } while (uVar12 < param_8);
LAB_00122c6c:
  if (param_2 != 0) {
    pbVar8 = (byte *)((int)&local_4c + 3);
    pbVar7 = local_48 + 0xf;
    uVar9 = 0;
    do {
      __memzero(local_48,0x10);
      uVar12 = param_2 - uVar9;
      if (0xf < uVar12) {
        uVar12 = 0x10;
      }
      pbVar3 = pbVar7;
      pbVar5 = pbVar8;
      if (uVar12 != 0) {
        pbVar10 = (byte *)(param_1 + (uVar9 - 1));
        pbVar4 = pbVar8;
        do {
          pbVar10 = pbVar10 + 1;
          pbVar4 = pbVar4 + 1;
          *pbVar4 = *pbVar10;
        } while (pbVar10 != (byte *)(param_1 + uVar12 + (uVar9 - 1)));
      }
      do {
        pbVar5 = pbVar5 + 1;
        *pbVar5 = *pbVar5 ^ pbVar3[1];
        pbVar3 = pbVar3 + 1;
      } while (pbVar5 != pbVar7);
      __memzero(local_38,0x10);
      uVar9 = uVar9 + uVar12;
      local_4c = 0x10;
      RT_AES_Encrypt(local_48,0x10,param_3,param_4,local_38,&local_4c);
    } while (uVar9 < param_2);
  }
  if (param_9 != 0) {
    pbVar7 = local_48 + 0xf;
    pbVar8 = (byte *)(param_10 + -1);
    do {
      pbVar7 = pbVar7 + 1;
      pbVar8 = pbVar8 + 1;
      *pbVar8 = *pbVar7;
    } while (pbVar8 != (byte *)(param_10 + param_9 + -1));
  }
  return;
}

