// module: mt7915.ko
// function: ZTE_GetRealTimeTxRxRate @ 0x157fec
// size: 1172 bytes
//

void ZTE_GetRealTimeTxRxRate(int param_1,int param_2,uint *param_3,uint *param_4)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint unaff_r9;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  bool bVar16;
  uint local_a8;
  uint local_a4;
  uint local_a0;
  uint local_7c;
  uint local_78;
  undefined1 uStack_74;
  byte local_73;
  byte local_72;
  byte local_71;
  byte local_70;
  byte local_6f;
  byte local_6e;
  byte local_6d;
  undefined1 auStack_6c [49];
  byte local_3b;
  byte local_39;
  byte local_38;
  byte local_37;
  char local_36;
  byte local_35;
  byte local_34;
  
  local_7c = 0;
  local_78 = 0;
  if ((param_2 == 0 || param_1 == 0) || (param_4 == (uint *)0x0 || param_3 == (uint *)0x0)) {
    return;
  }
  uVar1 = HcGetBandByWdev(*(undefined4 *)(param_2 + 8));
  if (*(char *)(param_2 + 0xb7e) != '\x01') goto LAB_00158054;
  MtCmdGetTxStatistic(param_1,4,0,*(undefined2 *)(param_2 + 0xe0),auStack_6c);
  local_a8 = (uint)local_38;
  uVar10 = (local_3b & 7) << 0xd | (local_37 & 3) << 7 | (uint)(local_36 != '\0') << 6 |
           (uint)(local_a8 != 0) << 9 | (local_39 & 1) << 10;
  if ((local_3b & 7) < 4) {
    if (((uVar10 << 0x10) >> 0x18 & 0xe0) == 0x20) {
      uVar3 = getLegacyOFDMMCSIndex(local_35);
      local_a8 = (uint)local_38;
      uVar10 = uVar10 | uVar3 & 0x3f;
      local_a0 = (uint)local_34;
    }
    else {
      local_a0 = (uint)local_34;
      uVar10 = uVar10 | local_35 & 0x3f;
    }
  }
  else {
    local_a0 = (uint)local_34;
    uVar10 = uVar10 | (uint)local_35 + (local_a0 - 1 & 3) * 0x10 & 0x3f;
  }
  uVar13 = (uVar10 << 0x17) >> 0x1e;
  MtCmdPhyGetRxRate(param_1,3,uVar1,*(undefined2 *)(param_2 + 0xe0),&uStack_74);
  uVar3 = uVar10 >> 0xd;
  uVar11 = (uVar10 << 0x15) >> 0x1f;
  uVar9 = (uint)local_72;
  local_a4 = (uint)local_70;
  uVar4 = uVar9 & 7;
  uVar14 = (uint)local_6d;
  uVar5 = (uint)local_6e;
  bVar16 = local_a4 != 0;
  uVar6 = uVar14 & 3;
  uVar7 = uVar5 & 1;
  if (uVar4 < 4) {
    unaff_r9 = 0;
    if (uVar4 == 1) {
      uVar2 = getLegacyOFDMMCSIndex(local_73);
      local_a4 = (uint)local_70;
      uVar2 = uVar2 & 0x3f;
      uVar9 = (uint)local_72;
      uVar15 = (uint)local_73;
      uVar14 = (uint)local_6d;
      uVar5 = (uint)local_6e;
      uVar8 = (uint)local_71;
    }
    else {
      uVar15 = (uint)local_73;
      uVar8 = (uint)local_71;
      uVar2 = uVar15 & 0x3f;
    }
  }
  else {
    uVar8 = (uint)local_71;
    uVar15 = (uint)local_73;
    uVar2 = uVar15 + uVar8 * 0x10 & 0x3f;
  }
  if (uVar3 < 4) {
    uVar12 = uVar10 & 0x3f;
  }
  else {
    uVar12 = uVar10 & 0xf;
  }
  uVar8 = uVar8 + 1 & 0xff;
  *(uint *)(param_2 + 0x160) = uVar8;
  *(uint *)(param_2 + 0x154) = uVar11;
  if (3 < uVar9) {
    uVar11 = uVar15 & 0xf;
  }
  *(uint *)(param_2 + 0x13c) = uVar3;
  *(uint *)(param_2 + 0x14c) = uVar13;
  *(uint *)(param_2 + 0x158) = uVar9;
  *(uint *)(param_2 + 0x168) = uVar14;
  *(uint *)(param_2 + 0x144) = local_a0;
  *(uint *)(param_2 + 0x170) = uVar5;
  *(uint *)(param_2 + 0x148) = uVar12;
  *(uint *)(param_2 + 0x150) = local_a8;
  if (3 < uVar9) {
    *(uint *)(param_2 + 0x164) = uVar11;
  }
  *(uint *)(param_2 + 0x16c) = local_a4;
  if (uVar9 < 4) {
    uVar11 = uVar15 & 0x3f;
    if (uVar9 < 2) {
      if (uVar9 == 1) {
        if (uVar11 == 0xb) {
          uVar2 = 0;
        }
        else if (uVar11 == 0xf) {
          uVar2 = 1;
        }
        else {
          if (uVar11 == 10) goto LAB_00158478;
          if (uVar11 == 0xe) {
            uVar2 = 3;
          }
          else if (uVar11 == 9) {
            uVar2 = 4;
          }
          else if (uVar11 == 0xd) {
            uVar2 = 5;
          }
          else if (uVar11 == 8) {
            uVar2 = 6;
          }
          else if (uVar11 == 0xc) {
            uVar2 = 7;
          }
          else {
            uVar2 = 0;
          }
        }
      }
      else {
        uVar2 = uVar11;
        if ((((uVar11 != 0) && (uVar11 != 1)) && (uVar11 != 2)) && (uVar11 != 3)) {
          if (uVar11 == 5) {
            uVar2 = 1;
          }
          else if (uVar11 == 6) {
LAB_00158478:
            uVar2 = 2;
          }
          else if (uVar11 == 7) {
            uVar2 = 3;
          }
          else {
            uVar2 = 0;
          }
        }
      }
      *(uint *)(param_2 + 0x164) = uVar2;
    }
    else {
      *(uint *)(param_2 + 0x164) = uVar11;
    }
  }
  if (uVar3 < 5) {
    getRate(uVar10,&local_7c);
    getRate(unaff_r9 & 0xffff1800 | uVar2 | (local_6f & 1) << 6 | uVar6 << 7 | (uint)bVar16 << 9 |
            uVar7 << 10 | uVar4 << 0xd,&local_78);
  }
  else {
    get_rate_he(uVar12 & 0xf,uVar13,local_a0,0,&local_7c);
    if (local_a8 == 1) {
      local_7c = local_7c * 0x3c7 >> 10;
    }
    else if (local_a8 == 2) {
      local_7c = local_7c * 0x366 >> 10;
    }
    get_rate_he(uVar11 & 0xf,uVar14,uVar8,0,&local_78);
    if (local_a4 == 1) {
      local_78 = local_78 * 0x3c7 >> 10;
    }
    else if (local_a4 == 2) {
      local_78 = local_78 * 0x366 >> 10;
    }
  }
LAB_00158054:
  *param_3 = local_7c;
  *param_4 = local_78;
  *(uint *)(param_2 + 0x140) = local_7c;
  *(uint *)(param_2 + 0x15c) = local_78;
  return;
}

