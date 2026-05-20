// module: mt7915.ko
// function: build_wmm_cap_ie @ 0x14742c
// size: 612 bytes
//

undefined4 build_wmm_cap_ie(int param_1,int *param_2)

{
  char cVar1;
  undefined2 uVar2;
  char cVar3;
  byte bVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 *puVar9;
  int iVar10;
  undefined2 *puVar11;
  byte *pbVar12;
  undefined4 local_36;
  undefined4 local_32;
  undefined4 local_2e;
  undefined4 local_2a;
  undefined4 local_26;
  undefined4 local_22;
  undefined4 local_1e;
  undefined2 local_1a;
  
  iVar10 = param_2[4];
  uVar8 = 0;
  if (*(char *)(iVar10 + 0x8d4) != '\0') {
    iVar6 = *(int *)(iVar10 + 0x14);
    if (((iVar6 == 4) || (iVar6 == 0x10)) || (iVar6 == 2)) {
      puVar9 = (undefined4 *)*param_2;
      local_32 = 0x500007dd;
      local_2e = 0x10002f2;
      local_2a = local_2a & 0xffffff00;
      iVar10 = GetStaCfgByWdev(param_1,iVar10);
      if (iVar10 == 0) {
        uVar8 = 0;
      }
      else {
        uVar8 = 0;
        if (*(char *)(iVar10 + 0x41e6) != '\0') {
          bVar4 = 0;
          if ((*(char *)(iVar10 + 0x8d8) != '\0') && (bVar4 = 0, *(char *)(iVar10 + 0x41eb) != '\0')
             ) {
            __memzero(&local_36,1);
            bVar4 = (byte)local_36 & 0x90 | (*(byte *)(param_1 + 0x794ca7) & 1) << 3 |
                    (*(byte *)(param_1 + 0x794ca8) & 1) << 2 |
                    (*(byte *)(param_1 + 0x794ca9) & 1) << 1 | *(byte *)(param_1 + 0x794caa) & 1 |
                    (*(byte *)(param_1 + 0x794cc4) & 3) << 5;
          }
          uVar8 = 9;
          *puVar9 = local_32;
          puVar9[1] = local_2e;
          *(byte *)(puVar9 + 2) = bVar4;
        }
      }
    }
    else {
      puVar9 = (undefined4 *)*param_2;
      local_2a = 0;
      local_26 = 0;
      local_22 = 0;
      local_1e = 0;
      local_1a = 0;
      local_32 = 0x500018dd;
      local_2e = 0x10102f2;
      iVar6 = wlan_config_get_ht_edca(iVar10);
      uVar8 = 0;
      if (iVar6 != 0) {
        iVar7 = 0;
        puVar11 = (undefined2 *)(iVar6 + 0x12);
        local_36 = *(undefined4 *)(iVar6 + 7);
        if (*(char *)(iVar10 + 0x8d8) == '\0') {
          bVar4 = 0;
        }
        else {
          bVar4 = 0x80;
        }
        local_2a = CONCAT31(local_2a._1_3_,bVar4 | *(byte *)(iVar6 + 6) & 0xf);
        puVar5 = &local_32;
        pbVar12 = (byte *)&local_36;
        do {
          bVar4 = *(byte *)(iVar6 + 0xb);
          cVar1 = *(char *)(iVar6 + 0xf);
          puVar11 = puVar11 + 1;
          uVar2 = *puVar11;
          cVar3 = (char)iVar7;
          iVar7 = iVar7 + 1;
          *(byte *)((int)puVar5 + 10) =
               (*pbVar12 & 0xf) + *(char *)(iVar6 + 0x1c) * '\x10' + cVar3 * ' ';
          *(char *)(puVar5 + 3) = (char)uVar2;
          *(byte *)((int)puVar5 + 0xb) = (bVar4 & 0xf) + cVar1 * '\x10';
          *(char *)((int)puVar5 + 0xd) = (char)((ushort)uVar2 >> 8);
          puVar5 = puVar5 + 1;
          iVar6 = iVar6 + 1;
          pbVar12 = pbVar12 + 1;
        } while (iVar7 != 4);
        *puVar9 = local_32;
        puVar9[1] = local_2e;
        puVar9[2] = local_2a;
        puVar9[3] = local_26;
        puVar9[4] = local_22;
        puVar9[5] = local_1e;
        *(undefined2 *)(puVar9 + 6) = local_1a;
        return 0x1a;
      }
    }
  }
  return uVar8;
}

