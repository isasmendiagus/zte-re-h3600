// module: mt7915.ko
// function: ap_frag_tx @ 0x1d2fc
// size: 1004 bytes
//

int ap_frag_tx(int param_1,int param_2,int param_3)

{
  byte bVar1;
  short sVar2;
  undefined1 uVar3;
  short sVar4;
  int iVar5;
  uint uVar6;
  byte *pbVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  char cVar11;
  bool bVar12;
  bool bVar13;
  short local_3c;
  uint local_2c;
  
  iVar10 = *(int *)(param_2 + 0x904);
  iVar5 = fill_tx_blk();
  if (iVar5 == 0) {
    iVar5 = *(int *)(param_3 + 0x78);
    if (iVar5 == 0) {
      iVar5 = *(int *)(param_3 + 0x74);
      if (iVar5 != 0) {
        *(int *)(iVar5 + 0x213194) = *(int *)(iVar5 + 0x213194) + 1;
      }
    }
    else {
      *(int *)(iVar5 + 0x43fc) = *(int *)(iVar5 + 0x43fc) + 1;
    }
    *(int *)(param_1 + 0x9db94) = *(int *)(param_1 + 0x9db94) + 1;
    RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0xc));
    if (DebugLevel < 3) {
      return 0;
    }
    printk("<--%s(%d): ##########Fail#########\n","ap_frag_tx",0xa63);
    return 0;
  }
  if ((*(uint *)(param_3 + 100) & 0x10) != 0) {
    iVar5 = duplicate_pkt_with_TKIP_MIC(param_1,*(undefined4 *)(param_3 + 0xc));
    *(int *)(param_3 + 0xc) = iVar5;
    if (iVar5 == 0) {
      return 1;
    }
    *(undefined4 *)(param_3 + 0x24) = *(undefined4 *)(iVar5 + 0xcc);
    *(undefined4 *)(param_3 + 0x28) = *(undefined4 *)(iVar5 + 100);
  }
  (**(code **)(iVar10 + 0x40))(param_1,param_2,param_3);
  if ((*(uint *)(param_3 + 100) & 0x10) != 0) {
    RTMPCalculateMICValue
              (param_1,*(undefined4 *)(param_3 + 0xc),*(undefined4 *)(param_3 + 0x54),
               *(int *)(param_3 + 0x68),*(int *)(param_3 + 0x68) + 0x10,
               *(undefined1 *)(param_2 + 0xe));
    memmove((void *)(*(int *)(param_3 + 0x30) + *(int *)(param_3 + 0x28)),
            (void *)(param_1 + 0xa39f44),8);
    *(int *)(param_3 + 0x28) = *(int *)(param_3 + 0x28) + 8;
    *(short *)(param_3 + 6) = *(short *)(param_3 + 6) + 8;
  }
  FUN_0001bb8c(param_1,param_2,param_3);
  uVar9 = *(uint *)(param_3 + 100);
  bVar13 = 8 < uVar9;
  bVar12 = uVar9 == 9;
  if (!bVar12) {
    bVar13 = uVar9 != 1;
  }
  uVar8 = uVar9;
  if (!bVar13 || (bVar12 || uVar9 == 2)) {
    local_2c = 8;
    uVar8 = local_2c;
  }
  if (bVar13 && (!bVar12 && uVar9 != 2)) {
    if (uVar8 == 3) {
      local_2c = 0xc;
    }
    else if (uVar8 == 4) {
      local_2c = 0x10;
    }
    else {
      local_2c = 0;
    }
  }
  pbVar7 = *(byte **)(param_3 + 0x50);
  if ((pbVar7[1] & 0xe0) == 0) {
    bVar1 = *pbVar7;
    *(byte *)(param_3 + 0x62) = (byte)(((uint)bVar1 << 0x1a) >> 0x1a);
    uVar9 = bVar1 & 0x3f;
LAB_0001d408:
    if (uVar9 < 0xc) {
      local_3c = RTMPCalcDuration(param_1,*(undefined1 *)(param_1 + uVar9 + 0x794c8f),0xe);
      goto LAB_0001d434;
    }
  }
  else {
    if ((pbVar7[1] & 0xe0) == 0x20) {
      uVar9 = (*pbVar7 & 0x3f) + 4;
      *(char *)(param_3 + 0x62) = (char)uVar9;
      goto LAB_0001d408;
    }
    *(undefined1 *)(param_3 + 0x62) = 0xc;
  }
  local_3c = RTMPCalcDuration(param_1,0xc,0xe);
LAB_0001d434:
  uVar9 = *(uint *)(param_3 + 0x28);
  iVar5 = *(int *)(param_3 + 0x5c);
  cVar11 = '\0';
  *(undefined1 *)(param_3 + 4) = 0xff;
  do {
    iVar10 = wlan_operate_get_frag_thld(param_2);
    uVar8 = (-4 - (uint)*(byte *)(param_3 + 0x35)) + iVar10;
    if (uVar8 < uVar9) {
      *(uint *)(param_3 + 0x28) = uVar8;
      uVar6 = wlan_operate_get_frag_thld(param_2);
      *(byte *)(iVar5 + 1) = *(byte *)(iVar5 + 1) | 4;
      sVar2 = *(short *)(param_1 + 0x794c4a);
      if (uVar9 - uVar8 < uVar6) {
        uVar6 = uVar9 - uVar8;
      }
      sVar4 = RTMPCalcDuration(param_1,*(undefined1 *)(param_3 + 0x62),local_2c + uVar6);
      if (cVar11 == '\0') {
        uVar3 = 1;
      }
      else {
        uVar3 = 2;
      }
      *(short *)(iVar5 + 2) = local_3c * 2 + sVar2 * 3 + sVar4;
      *(undefined1 *)(param_3 + 0x2f) = uVar3;
    }
    else {
      *(uint *)(param_3 + 0x28) = uVar9;
      if (cVar11 == '\0') {
        iVar10 = 0;
      }
      uVar3 = (undefined1)iVar10;
      *(byte *)(iVar5 + 1) = *(byte *)(iVar5 + 1) & 0xfb;
      if (cVar11 != '\0') {
        uVar3 = 3;
      }
      *(short *)(iVar5 + 2) = local_3c + *(short *)(param_1 + 0x794c4a);
      *(char *)(param_3 + 4) = cVar11;
      *(undefined1 *)(param_3 + 0x2f) = uVar3;
    }
    bVar13 = cVar11 == '\0';
    cVar11 = cVar11 + '\x01';
    uVar9 = uVar9 - *(int *)(param_3 + 0x28);
    if (bVar13) {
      *(undefined1 *)(param_3 + 0x60) = 0;
      iVar10 = asic_hw_tx(param_1,param_3);
      if (iVar10 != 0) {
        return iVar10;
      }
      if (*(int *)(param_3 + 0x54) != 0) {
        *(char *)(param_3 + 0x35) = *(char *)(param_3 + 0x35) + -8;
      }
    }
    else {
      *(undefined1 *)(param_3 + 0x60) = 2;
      iVar10 = asic_hw_tx(param_1,param_3);
      if (iVar10 != 0) {
        return iVar10;
      }
    }
    *(int *)(param_3 + 0x30) = *(int *)(param_3 + 0x30) + *(int *)(param_3 + 0x28);
    *(byte *)(iVar5 + 0x16) = *(byte *)(iVar5 + 0x16) & 0xf0 | *(byte *)(iVar5 + 0x16) + 1 & 0xf;
  } while (uVar9 != 0);
  return 0;
}

