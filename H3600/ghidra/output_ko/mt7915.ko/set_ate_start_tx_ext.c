// module: mt7915.ko
// function: set_ate_start_tx_ext @ 0x26c244
// size: 1112 bytes
//

int set_ate_start_tx_ext(int param_1,undefined4 param_2)

{
  char cVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  int iVar15;
  uint uVar16;
  int iVar17;
  undefined4 uVar18;
  int iVar19;
  uint uVar20;
  uint *puVar21;
  uint uVar22;
  uint uVar23;
  bool bVar24;
  undefined1 local_ac;
  undefined1 local_a4;
  undefined1 local_a0;
  undefined1 local_9c;
  undefined1 local_98;
  undefined2 local_94;
  undefined1 local_8c;
  undefined1 local_84;
  undefined4 local_74;
  undefined4 local_70;
  uint local_6c;
  int local_68;
  uint local_64;
  uint local_60 [15];
  
  iVar19 = *(int *)(param_1 + 0xa39fd4);
  local_60[0] = 0;
  local_60[1] = 0;
  local_60[2] = 0;
  local_60[3] = 0;
  local_60[4] = 0;
  local_60[5] = 0;
  local_60[6] = 0;
  local_60[7] = 0;
  local_60[8] = 0;
  local_60[9] = 0;
  local_60[10] = 0;
  local_60[0xb] = 0;
  local_60[0xc] = 0;
  local_60[0xd] = 0;
  if (0 < DebugLevel) {
    printk("%s: Arg = %s\n","set_ate_start_tx_ext",param_2);
  }
  iVar15 = rstrtok(param_2,&_LC2);
  if (iVar15 == 0) {
    return 0;
  }
  puVar21 = &local_64;
  iVar17 = 0;
  do {
    uVar16 = simple_strtol(iVar15,0,10);
    iVar17 = iVar17 + 1;
    puVar21 = puVar21 + 1;
    *puVar21 = uVar16;
    iVar15 = rstrtok(0,&_LC2);
    uVar14 = local_60[0xd];
    uVar13 = local_60[0xc];
    uVar12 = local_60[0xb];
    uVar11 = local_60[10];
    uVar10 = local_60[9];
    uVar9 = local_60[8];
    uVar8 = local_60[7];
    uVar7 = local_60[6];
    uVar6 = local_60[5];
    uVar5 = local_60[4];
    uVar4 = local_60[3];
    uVar3 = local_60[2];
    uVar16 = local_60[0];
    if (iVar15 == 0) {
      if (iVar17 != 0xe) {
        return 0;
      }
      break;
    }
  } while (iVar17 != 0xe);
  uVar23 = local_60[1];
  if (local_60[1] == 0) {
    uVar23 = -0x70000001;
  }
  iVar15 = net_ad_wrap_service(param_1);
  iVar17 = uVar16 * 0xd18;
  *(uint *)(iVar15 + iVar17 + 0x1118) = uVar23;
  iVar15 = net_ad_wrap_service(param_1);
  *(char *)(iVar15 + iVar17 + 0x1135) = (char)uVar3;
  iVar15 = net_ad_wrap_service(param_1);
  local_ac = (undefined1)uVar4;
  *(undefined1 *)(iVar15 + iVar17 + 0x1138) = local_ac;
  iVar15 = net_ad_wrap_service(param_1);
  local_a4 = (undefined1)uVar6;
  *(undefined1 *)(iVar15 + iVar17 + 0x113a) = local_a4;
  iVar15 = net_ad_wrap_service(param_1);
  local_a0 = (undefined1)uVar7;
  *(undefined1 *)(iVar15 + iVar17 + 0x113b) = local_a0;
  iVar15 = net_ad_wrap_service(param_1);
  local_9c = (undefined1)uVar8;
  *(undefined1 *)(iVar15 + iVar17 + 0x11cc) = local_9c;
  iVar15 = net_ad_wrap_service(param_1);
  local_98 = (undefined1)uVar9;
  local_94 = (undefined2)uVar10;
  *(undefined1 *)(iVar15 + iVar17 + 0x11cd) = local_98;
  *(undefined2 *)(param_1 + 0xa3b008) = local_94;
  iVar15 = net_ad_wrap_service(param_1);
  *(uint *)(iVar15 + iVar17 + 0x10f4) = uVar11;
  iVar15 = net_ad_wrap_service(param_1);
  local_8c = (undefined1)uVar12;
  *(undefined1 *)(iVar15 + iVar17 + 0x113c) = local_8c;
  iVar15 = net_ad_wrap_service(param_1);
  *(uint *)(iVar15 + iVar17 + 0x1128) = uVar13;
  iVar15 = net_ad_wrap_service(param_1);
  local_84 = (undefined1)uVar14;
  *(undefined1 *)(iVar15 + iVar17 + 0x1139) = local_84;
  iVar15 = net_ad_wrap_service(param_1);
  uVar20 = (uint)*(byte *)(iVar15 + iVar17 + 0x1130);
  iVar15 = net_ad_wrap_service(param_1);
  uVar22 = (uint)*(byte *)(iVar15 + iVar17 + 0x1131);
  iVar15 = net_ad_wrap_service(param_1);
  cVar1 = *(char *)(iVar15 + iVar17 + 0x1137);
  iVar15 = net_ad_wrap_service(param_1);
  cVar2 = *(char *)(iVar15 + iVar17 + 0x1136);
  iVar15 = net_ad_wrap_service(param_1);
  bVar24 = uVar3 == 4;
  if (uVar3 < 5) {
    bVar24 = uVar4 == 0x20;
  }
  uVar18 = *(undefined4 *)(iVar15 + iVar17 + 0x10f4);
  if ((bVar24) && (cVar1 != '\x01' && cVar2 != '\x01')) {
    if (DebugLevel < 1) {
      return -1;
    }
    iVar19 = -1;
    printk("%s: Bandwidth must to be 40 at MCS 32\n","set_ate_start_tx_ext");
  }
  else {
    os_zero_mem(&local_74,0x14);
    local_68 = uVar16;
    local_70 = uVar5;
    local_6c = uVar20;
    local_64 = uVar22;
    (**(code **)(iVar19 + 0x2c))(param_1,local_74,uVar5,uVar20,uVar16,uVar22);
    (**(code **)(iVar19 + 0x68))(param_1,uVar18);
    (**(code **)(iVar19 + 8))(param_1);
    iVar19 = (**(code **)(iVar19 + 0x10))(param_1);
    if (iVar19 == 0) {
      iVar19 = 1;
    }
  }
  if ((0 < DebugLevel) &&
     (printk("%s: band_idx:%u, pkt_cnt:%u, phy:%u, mcs:%u, stbc:%u, ldpc:%u\n",
             "set_ate_start_tx_ext",uVar16,uVar23,uVar3,uVar4,uVar6,uVar7), 0 < DebugLevel)) {
    printk("%s: ibf:%u, ebf:%u, wlan_id:%u, aifs:%u, gi:%u, tx_path:%x, nss:%x\n",
           "set_ate_start_tx_ext",uVar8,uVar9,uVar10,uVar11,uVar12,uVar13,uVar14);
  }
  return iVar19;
}

