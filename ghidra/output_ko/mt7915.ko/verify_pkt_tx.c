// module: mt7915.ko
// function: verify_pkt_tx @ 0x1d6960
// size: 936 bytes
//

undefined4 verify_pkt_tx(int param_1,int param_2,int param_3)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  byte bVar7;
  int iVar8;
  byte *pbVar9;
  undefined4 uVar10;
  uint uVar11;
  bool bVar12;
  bool bVar13;
  bool bVar14;
  undefined2 local_5e;
  undefined2 local_5c;
  undefined1 local_5a;
  undefined1 local_58;
  undefined1 local_57;
  byte local_56;
  undefined1 local_55;
  undefined1 local_54;
  undefined1 local_53;
  undefined1 local_52;
  undefined1 local_51;
  undefined1 local_50;
  undefined1 local_4f;
  undefined2 local_4e;
  byte local_4c;
  undefined1 local_4b;
  int local_48;
  undefined1 local_44;
  undefined1 local_40;
  undefined1 local_3c;
  byte local_3b;
  byte local_3a;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined1 local_2a;
  
  iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  bVar7 = *(byte *)(iVar3 + 2);
  if (param_2 == 0) {
    return 1;
  }
  piVar4 = *(int **)(param_3 + 0x40);
  iVar3 = *(int *)(param_2 + 0x904);
  if (piVar4 != (int *)0x0) {
    iVar8 = *piVar4;
    *piVar4 = 0;
    *(int *)(param_3 + 0x40) = iVar8;
    if (iVar8 == 0) {
      *(undefined4 *)(param_3 + 0x44) = 0;
    }
    *(int *)(param_3 + 0x48) = *(int *)(param_3 + 0x48) + -1;
  }
  *(int **)(param_3 + 0xc) = piVar4;
  *(undefined2 *)(param_3 + 0x1e) = *(undefined2 *)((int)piVar4 + 0x42);
  RTMP_QueryPacketInfo(piVar4,&local_5c,param_3 + 0x24,param_3 + 0x28);
  uVar2 = HcGetWmmIdx(param_1,param_2);
  *(undefined4 *)(param_3 + 0x30) = *(undefined4 *)(param_3 + 0x24);
  *(undefined1 *)(param_3 + 0x20) = uVar2;
  __memzero(&local_5c,0x34);
  if (*(int *)(param_1 + 0xa7cc60) != 3) {
    uVar6 = *(uint *)(param_1 + 0xa7cc58);
    pbVar9 = (byte *)(*(int *)(param_3 + 0x24) + (uint)bVar7);
    if ((uVar6 & 8) != 0) {
      pbVar9[0x16] = pbVar9[0x16] & 0xf | *(char *)(param_1 + 0xa7d088) << 4;
      pbVar9[0x17] = (byte)(((uint)*(ushort *)(param_1 + 0xa7d088) << 0x14) >> 0x18);
      uVar6 = *(uint *)(param_1 + 0xa7cc58);
    }
    if ((uVar6 & 4) != 0) {
      pbVar9[1] = pbVar9[1] & 0xef | (*(byte *)(param_1 + 0xa7d08d) & 1) << 4;
    }
    if ((*(int *)(param_1 + 0xa7cc64) != 10) && ((*(uint *)(param_1 + 0xa7cc58) & 0x10) != 0)) {
      *(undefined2 *)(pbVar9 + 2) = *(undefined2 *)(param_1 + 0xa7d08a);
    }
    local_3b = (byte)(((uint)*pbVar9 << 0x1c) >> 0x1e);
    local_3a = *pbVar9 >> 4;
  }
  uVar10 = *(undefined4 *)(param_3 + 0x24);
  bVar1 = *(byte *)(param_2 + 0xb0a);
  local_5c = *(undefined2 *)(*(int *)(param_3 + 0xc) + 0x42);
  local_56 = *(byte *)(param_1 + 0xa7cc6c) & 1;
  local_5a = 0;
  local_55 = 0;
  local_54 = 0;
  local_51 = 0;
  local_4f = 0;
  local_32 = HcGetWmmIdx(param_1,param_2);
  local_40 = HcGetMgmtQueueIdx(param_1,param_2,(int)*(char *)(*(int *)(param_3 + 0xc) + 0x4f));
  uVar6 = *(uint *)(param_1 + 0xa7cc58);
  local_57 = (uVar6 & 0x80) == 0;
  local_33 = *(undefined1 *)(param_2 + 0x29);
  local_48 = *(int *)(param_3 + 0x28) - (uint)bVar7;
  if ((uVar6 & 0x100) != 0) {
    local_31 = 1;
  }
  if ((uVar6 & 4) != 0) {
    local_34 = 1;
  }
  if ((uVar6 & 0x10) != 0) {
    local_53 = 1;
  }
  uVar5 = uVar6 & 0x2000;
  if (uVar5 != 0) {
    local_52 = 1;
  }
  if ((uVar6 & 8) != 0) {
    local_4e = *(undefined2 *)(param_1 + 0xa7d088);
    local_58 = 1;
  }
  if ((uVar6 & 0x400) != 0) {
    local_2e = 1;
  }
  if ((uVar6 & 0x800) != 0) {
    local_2f = 1;
  }
  if ((uVar6 & 0x1000) != 0) {
    local_2a = *(undefined1 *)(param_1 + 0xa7d08e);
  }
  iVar8 = *(int *)(param_1 + 0xa7cc60);
  if (iVar8 == 0) {
    if (uVar5 != 0) {
      local_44 = 0x1c;
      goto LAB_001d6b98;
    }
  }
  else {
    if (iVar8 == 1) {
      uVar11 = *(uint *)(param_1 + 0xa7cc64);
      bVar12 = 7 < uVar11;
      bVar13 = uVar11 != 8;
      if (bVar13) {
        bVar12 = uVar11 != 10;
      }
      bVar14 = uVar11 == 0xb;
      if (!bVar12 || (!bVar13 || bVar14)) {
        uVar11 = 0x10;
      }
      if (!bVar12 || (!bVar13 || bVar14)) {
        local_44 = (undefined1)uVar11;
      }
      goto LAB_001d6b98;
    }
    if (iVar8 != 2) goto LAB_001d6b98;
    if ((uVar6 & 2) != 0) {
      if (uVar5 == 0) {
        local_44 = 0x1a;
      }
      else {
        local_44 = 0x1e;
      }
      goto LAB_001d6b98;
    }
  }
  local_44 = 0x18;
LAB_001d6b98:
  local_3c = 1;
  bVar12 = (*(ushort *)(param_2 + 0x18) & 0x4e) != 0;
  local_4b = 3;
  bVar7 = 0;
  local_2b = 0;
  local_2c = 0;
  if (!bVar12) {
    bVar7 = local_5e._1_1_;
    local_5e._1_1_ = 1;
  }
  local_50 = *(undefined1 *)(param_1 + 0xa7d08c);
  if (bVar12) {
    bVar7 = local_5e._1_1_ & 0x1f | bVar7 << 5;
  }
  else {
    bVar7 = bVar7 & 0x1f | local_5e._1_1_ << 5;
  }
  local_4c = (byte)(((uint)bVar1 << 0x1a) >> 0x1a);
  if (uVar5 != 0) {
    bVar7 = bVar7 & 0x1f | 0x40;
  }
  local_5e = ((bVar7 & 0xfe) & 0xf9) << 8;
  if ((uVar6 & 0x40) == 0) {
    uVar10 = asic_mlme_hw_tx(param_1,uVar10,&local_5c,&local_5e,param_3);
    return uVar10;
  }
  *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x800000;
  (**(code **)(iVar3 + 0x44))(param_1,param_2,param_3);
  uVar10 = asic_hw_tx(param_1,param_3);
  return uVar10;
}

