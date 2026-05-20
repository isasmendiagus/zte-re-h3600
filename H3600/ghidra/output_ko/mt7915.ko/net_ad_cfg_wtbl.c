// module: mt7915.ko
// function: net_ad_cfg_wtbl @ 0x25ce24
// size: 608 bytes
//

undefined4 net_ad_cfg_wtbl(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  char cVar3;
  byte bVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  char cVar7;
  char cVar8;
  byte bVar9;
  undefined1 uVar10;
  undefined1 uVar11;
  int iVar12;
  int iVar13;
  undefined4 uVar14;
  byte bVar15;
  uint uVar16;
  int iVar17;
  bool bVar18;
  undefined1 uVar19;
  undefined1 local_74;
  undefined1 local_73;
  undefined1 local_70;
  undefined1 local_6f;
  undefined1 local_6e;
  undefined1 local_6c;
  undefined1 local_6b;
  byte local_68;
  byte local_67;
  byte local_66;
  byte local_65;
  byte local_64;
  undefined1 local_63;
  undefined1 local_62;
  undefined1 local_60;
  byte local_5f;
  undefined1 local_5e;
  char local_5d;
  undefined1 local_5c;
  undefined1 local_5b;
  undefined1 local_5a;
  undefined1 local_59;
  undefined1 local_58;
  undefined1 local_57;
  undefined1 local_56;
  undefined1 local_55;
  ushort local_54;
  undefined1 local_52;
  byte local_51;
  
  iVar12 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar12 == 0) {
    return 0x606;
  }
  iVar13 = hc_get_chip_cap(*(undefined4 *)(iVar12 + 0xa797a0));
  cVar3 = *(char *)(param_3 + 0x1c);
  bVar4 = *(byte *)(param_3 + 2);
  uVar5 = *(undefined1 *)(param_3 + 9);
  uVar6 = *(undefined1 *)(param_3 + 3);
  cVar7 = *(char *)(param_2 + 0xc5c);
  cVar8 = *(char *)(param_3 + 0x1e);
  bVar9 = *(byte *)(param_3 + 8);
  iVar17 = *(int *)(param_2 + 0xc48);
  uVar10 = *(undefined1 *)(param_2 + 0xc5a);
  uVar16 = (uint)*(byte *)(param_2 + 0xc5b);
  uVar11 = *(undefined1 *)(param_2 + 0xc5d);
  sys_ad_zero_mem(&local_74,0x4c);
  local_74 = 1;
  local_73 = 0x1d;
  if (1 < bVar4) {
    uVar19 = (undefined1)uVar16;
    if (bVar4 < 4) {
      local_70 = 1;
      local_6f = uVar19;
      if (iVar13 == 0) {
        local_6e = 3;
      }
      else {
        local_6e = *(undefined1 *)(param_1 + 0x44);
      }
      goto LAB_0025cefc;
    }
    if (bVar4 == 4) {
      local_70 = 1;
      local_6c = 1;
      local_6b = uVar19;
      if (iVar13 == 0) {
        local_6e = 7;
      }
      else {
        local_6e = *(undefined1 *)(param_1 + 0x49);
      }
      goto LAB_0025cefc;
    }
  }
  local_70 = 0;
  local_6c = 0;
LAB_0025cefc:
  if (cVar8 != '\0') {
    if (iVar17 < 0) {
      local_67 = (byte)iVar17;
      local_68 = local_67 & 0x1f;
    }
    else {
      iVar13 = 0;
      do {
        iVar2 = iVar13 * 8;
        iVar1 = iVar13 * 8;
        iVar13 = iVar13 + 1;
        if (*(int *)(test_ant_to_spe_idx_map + iVar2) == iVar17) {
          local_67 = test_ant_to_spe_idx_map[iVar1 + 4];
          local_68 = local_67 & 0x1f;
          goto LAB_0025cf50;
        }
      } while (iVar13 != 0x10);
      local_68 = 0;
      local_67 = 0;
    }
LAB_0025cf50:
    local_63 = 1;
    local_52 = 1;
    local_62 = 7;
    local_66 = local_67;
    local_65 = local_67;
    local_64 = local_67;
  }
  local_60 = uVar6;
  if (cVar7 != '\0') {
    switch(uVar6) {
    case 0:
      local_58 = 1;
      break;
    case 1:
      local_57 = 1;
      break;
    case 2:
      local_56 = 1;
      break;
    default:
      printk("%s: can\'t find such bw, use default\n","net_ad_cfg_wtbl");
      break;
    case 5:
      local_55 = 1;
    }
  }
  local_5e = raStbcSettingCheck(uVar10,bVar4,bVar9,uVar5,0,0,uVar16);
  bVar18 = cVar3 != '\0';
  local_5a = (undefined1)uVar16;
  bVar15 = bVar9;
  if (bVar18) {
    bVar15 = 1;
  }
  local_54 = (ushort)bVar9;
  if (bVar18) {
    local_51 = bVar15;
  }
  local_5f = bVar4;
  local_5d = cVar7;
  local_5c = uVar6;
  local_5b = uVar11;
  local_59 = uVar5;
  uVar14 = MtCmdATETest(iVar12,&local_74);
  return uVar14;
}

