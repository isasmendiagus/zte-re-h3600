// module: mt7915.ko
// function: mt_ate_wtbl_cfg_v2 @ 0x2855f8
// size: 756 bytes
//

void mt_ate_wtbl_cfg_v2(int param_1,int param_2)

{
  int iVar1;
  char cVar2;
  char cVar3;
  byte bVar4;
  byte bVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  char cVar8;
  undefined1 uVar9;
  undefined1 uVar10;
  int iVar11;
  int iVar12;
  undefined1 uVar13;
  int iVar14;
  bool bVar15;
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
  undefined1 local_51;
  
  iVar11 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar12 = net_ad_wrap_service(param_1);
  param_2 = param_2 * 0xd18;
  cVar2 = *(char *)(iVar12 + param_2 + 0x1104);
  cVar3 = *(char *)(iVar12 + param_2 + 0x1106);
  iVar12 = net_ad_wrap_service(param_1);
  bVar4 = *(byte *)(iVar12 + param_2 + 0x1135);
  iVar12 = net_ad_wrap_service(param_1);
  bVar5 = *(byte *)(iVar12 + param_2 + 0x1138);
  iVar12 = net_ad_wrap_service(param_1);
  uVar6 = *(undefined1 *)(iVar12 + param_2 + 0x1139);
  iVar12 = net_ad_wrap_service(param_1);
  uVar7 = *(undefined1 *)(iVar12 + param_2 + 0x1136);
  iVar12 = net_ad_wrap_service(param_1);
  cVar8 = *(char *)(iVar12 + param_2 + 0x113c);
  iVar12 = net_ad_wrap_service(param_1);
  uVar13 = *(undefined1 *)(iVar12 + param_2 + 0x113a);
  iVar12 = net_ad_wrap_service(param_1);
  uVar9 = *(undefined1 *)(iVar12 + param_2 + 0x113b);
  iVar12 = net_ad_wrap_service(param_1);
  iVar14 = *(int *)(iVar12 + param_2 + 0x1128);
  iVar12 = net_ad_wrap_service(param_1);
  uVar10 = *(undefined1 *)(iVar12 + param_2 + 0x113d);
  os_zero_mem(&local_74,0x4c);
  local_74 = 1;
  local_73 = 0x1d;
  if (1 < bVar4) {
    if (bVar4 < 4) {
      local_70 = 1;
      local_6f = uVar9;
      if (iVar11 == 0) {
        local_6e = 3;
      }
      else {
        local_6e = *(undefined1 *)(iVar11 + 0x5f);
      }
      goto LAB_00285764;
    }
    if (bVar4 == 4) {
      local_70 = 1;
      local_6c = 1;
      local_6b = uVar9;
      if (iVar11 == 0) {
        local_6e = 7;
      }
      else {
        local_6e = *(undefined1 *)(iVar11 + 0x61);
      }
      goto LAB_00285764;
    }
  }
  local_70 = 0;
  local_6c = 0;
LAB_00285764:
  if (cVar3 != '\0') {
    if (iVar14 < 0) {
      local_67 = (byte)iVar14;
      local_68 = local_67 & 0x1f;
    }
    else {
      iVar11 = 0;
      do {
        iVar1 = iVar11 * 8;
        iVar12 = iVar11 * 8;
        iVar11 = iVar11 + 1;
        if (*(int *)(ant_to_spe_idx_map + iVar1) == iVar14) {
          local_67 = ant_to_spe_idx_map[iVar12 + 4];
          local_68 = local_67 & 0x1f;
          goto LAB_002857b0;
        }
      } while (iVar11 != 0x10);
      local_68 = 0;
      local_67 = 0;
    }
LAB_002857b0:
    local_63 = 1;
    local_52 = 1;
    local_62 = 7;
    local_66 = local_67;
    local_65 = local_67;
    local_64 = local_67;
  }
  local_60 = uVar7;
  if (cVar8 != '\0') {
    switch(uVar7) {
    case 0:
      local_58 = 1;
      break;
    case 1:
      local_57 = 1;
      break;
    case 2:
      local_56 = 1;
      break;
    case 3:
      local_55 = 1;
      break;
    default:
      if (0 < DebugLevel) {
        printk("%s: Can\'t find such bw, use default\n","mt_ate_wtbl_cfg_v2");
      }
    }
  }
  local_5e = raStbcSettingCheck(uVar13,bVar4,bVar5,uVar6,0,0);
  bVar15 = cVar2 != '\0';
  uVar13 = uVar9;
  if (bVar15) {
    uVar13 = 1;
  }
  local_54 = (ushort)bVar5;
  if (bVar15) {
    local_51 = uVar13;
  }
  local_5f = bVar4;
  local_5d = cVar8;
  local_5c = uVar7;
  local_5b = uVar10;
  local_5a = uVar9;
  local_59 = uVar6;
  MtCmdATETest(param_1,&local_74);
  return;
}

