// module: mt7915.ko
// function: sta_frag_tx @ 0x5609c
// size: 1204 bytes
//

int sta_frag_tx(int param_1,undefined4 param_2,int param_3)

{
  byte bVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  uint uVar5;
  undefined1 uVar6;
  byte *pbVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  char cVar12;
  void *__dest;
  int iVar13;
  undefined6 *__src;
  short local_50;
  int local_44;
  undefined1 auStack_38 [20];
  
  iVar4 = fill_tx_blk();
  if (iVar4 == 0) {
    *(int *)(param_1 + 0x9db94) = *(int *)(param_1 + 0x9db94) + 1;
    RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0xc));
    return 1;
  }
  sta_build_802_11_header(param_1,param_3);
  if ((*(uint *)(param_3 + 100) & 0x10) != 0) {
    iVar4 = duplicate_pkt_with_TKIP_MIC(param_1,*(undefined4 *)(param_3 + 0xc));
    *(int *)(param_3 + 0xc) = iVar4;
    if (iVar4 == 0) {
      return 1;
    }
    RTMP_QueryPacketInfo(iVar4,auStack_38,param_3 + 0x24,param_3 + 0x28);
  }
  iVar9 = *(int *)(param_3 + 0x28);
  iVar4 = *(int *)(param_3 + 0x24);
  iVar11 = *(int *)(param_3 + 0x5c);
  *(int *)(param_3 + 0x30) = iVar4 + 0xe;
  *(int *)(param_3 + 0x28) = iVar9 + -0xe;
  iVar13 = (uint)*(byte *)(*(int *)(param_3 + 0xc) + 0x30) << 0x1b;
  if (iVar13 < 0) {
    *(int *)(param_3 + 0x30) = iVar4 + 0x12;
  }
  if (iVar13 < 0) {
    *(int *)(param_3 + 0x28) = iVar9 + -0x12;
  }
  iVar9 = iVar11 + (uint)*(byte *)(param_3 + 0x2c);
  *(byte *)(param_3 + 0x35) = *(byte *)(param_3 + 0x2c);
  __dest = (void *)(iVar9 + 3U & 0xfffffffc);
  *(char *)(param_3 + 0x34) = (char)__dest - (char)iVar9;
  if ((uint)*(byte *)(iVar4 + 0xd) + (uint)*(byte *)(iVar4 + 0xc) * 0x100 < 0x5dd) {
    *(undefined4 *)(param_3 + 0x54) = 0;
  }
  else {
    __src = &SNAP_802_1H;
    *(undefined6 **)(param_3 + 0x54) = &SNAP_802_1H;
    iVar9 = memcmp(&IPX,(void *)(iVar4 + 0xc),2);
    if ((iVar9 == 0) || (iVar4 = memcmp(&APPLE_TALK,(void *)(iVar4 + 0xc),2), iVar4 == 0)) {
      __src = &SNAP_BRIDGE_TUNNEL;
      *(undefined6 **)(param_3 + 0x54) = &SNAP_BRIDGE_TUNNEL;
    }
    memmove(__dest,__src,6);
    if (iVar13 < 0) {
      iVar4 = 0x10;
    }
    else {
      iVar4 = 0xc;
    }
    memmove((void *)((int)__dest + 6),(void *)(*(int *)(param_3 + 0x24) + iVar4),2);
    *(char *)(param_3 + 0x35) = *(char *)(param_3 + 0x35) + '\b';
  }
  if ((*(uint *)(param_3 + 100) & 0x10) == 0) {
    if ((*(uint *)(param_3 + 100) & 0xe) != 0) {
LAB_000561d0:
      local_44 = 8;
      goto LAB_000561d8;
    }
LAB_0005649c:
    pbVar7 = *(byte **)(param_3 + 0x50);
    if ((*(uint *)(param_3 + 100) & 0x1e0) == 0) {
      local_44 = 0;
    }
    else {
      local_44 = 0x10;
    }
    bVar1 = pbVar7[1];
    if ((bVar1 & 0xe0) != 0) goto LAB_000564c0;
LAB_000561e8:
    bVar1 = *pbVar7;
    *(byte *)(param_3 + 0x62) = (byte)(((uint)bVar1 << 0x1a) >> 0x1a);
    uVar10 = bVar1 & 0x3f;
LAB_000561f8:
    if (uVar10 < 0xc) {
      local_50 = RTMPCalcDuration(param_1,*(undefined1 *)(param_1 + uVar10 + 0x794c8f),0xe);
      goto LAB_00056224;
    }
  }
  else {
    RTMPCalculateMICValue
              (param_1,*(undefined4 *)(param_3 + 0xc),*(undefined4 *)(param_3 + 0x54),
               *(int *)(param_3 + 0x68),*(int *)(param_3 + 0x68) + 0x10,
               (uint)(*(int *)(param_3 + 0x18) << 0x12) >> 0x1f);
    memmove((void *)(*(int *)(param_3 + 0x30) + *(int *)(param_3 + 0x28)),
            (void *)(param_1 + 0xa39f44),8);
    *(int *)(param_3 + 0x28) = *(int *)(param_3 + 0x28) + 8;
    *(short *)(param_3 + 6) = *(short *)(param_3 + 6) + 8;
    if ((*(uint *)(param_3 + 100) & 0xe) != 0) goto LAB_000561d0;
    if ((*(uint *)(param_3 + 100) & 0x10) == 0) goto LAB_0005649c;
    local_44 = 0xc;
LAB_000561d8:
    pbVar7 = *(byte **)(param_3 + 0x50);
    bVar1 = pbVar7[1];
    if ((bVar1 & 0xe0) == 0) goto LAB_000561e8;
LAB_000564c0:
    if ((bVar1 & 0xe0) == 0x20) {
      uVar10 = (*pbVar7 & 0x3f) + 4;
      *(char *)(param_3 + 0x62) = (char)uVar10;
      goto LAB_000561f8;
    }
    *(undefined1 *)(param_3 + 0x62) = 0xc;
  }
  local_50 = RTMPCalcDuration(param_1,0xc,0xe);
LAB_00056224:
  uVar10 = *(uint *)(param_3 + 0x28);
  cVar12 = '\0';
  *(undefined1 *)(param_3 + 4) = 0xff;
  do {
    iVar4 = wlan_operate_get_frag_thld(param_2);
    uVar8 = (-4 - (uint)*(byte *)(param_3 + 0x35)) + iVar4;
    if (uVar8 < uVar10) {
      *(uint *)(param_3 + 0x28) = uVar8;
      uVar5 = wlan_operate_get_frag_thld(param_2);
      *(byte *)(iVar11 + 1) = *(byte *)(iVar11 + 1) | 4;
      sVar2 = *(short *)(param_1 + 0x794c4a);
      if (uVar10 - uVar8 < uVar5) {
        uVar5 = uVar10 - uVar8;
      }
      sVar3 = RTMPCalcDuration(param_1,*(undefined1 *)(param_3 + 0x62),local_44 + uVar5);
      if (cVar12 == '\0') {
        uVar6 = 1;
      }
      else {
        uVar6 = 2;
      }
      *(short *)(iVar11 + 2) = local_50 * 2 + sVar2 * 3 + sVar3;
      *(undefined1 *)(param_3 + 0x2f) = uVar6;
    }
    else {
      *(uint *)(param_3 + 0x28) = uVar10;
      *(byte *)(iVar11 + 1) = *(byte *)(iVar11 + 1) & 0xfb;
      if (cVar12 == '\0') {
        uVar6 = 0;
      }
      else {
        uVar6 = 3;
      }
      *(short *)(iVar11 + 2) = local_50 + *(short *)(param_1 + 0x794c4a);
      *(char *)(param_3 + 4) = cVar12;
      *(undefined1 *)(param_3 + 0x2f) = uVar6;
    }
    uVar10 = uVar10 - *(int *)(param_3 + 0x28);
    if (cVar12 == '\0') {
      *(undefined1 *)(param_3 + 0x60) = 0;
      iVar4 = asic_hw_tx(param_1,param_3);
      if (iVar4 != 0) {
        return iVar4;
      }
      *(int *)(param_1 + 0xa78a18) = *(int *)(param_3 + 0x28) + *(int *)(param_1 + 0xa78a18);
      if (*(int *)(param_3 + 0x54) != 0) {
        *(char *)(param_3 + 0x35) = *(char *)(param_3 + 0x35) + -8;
      }
    }
    else {
      *(undefined1 *)(param_3 + 0x60) = 2;
      iVar4 = asic_hw_tx(param_1,param_3);
      if (iVar4 != 0) {
        return iVar4;
      }
      *(int *)(param_1 + 0xa78a18) = *(int *)(param_3 + 0x28) + *(int *)(param_1 + 0xa78a18);
    }
    cVar12 = cVar12 + '\x01';
    *(int *)(param_3 + 0x30) = *(int *)(param_3 + 0x30) + *(int *)(param_3 + 0x28);
    *(byte *)(iVar11 + 0x16) = *(byte *)(iVar11 + 0x16) & 0xf0 | *(byte *)(iVar11 + 0x16) + 1 & 0xf;
  } while (uVar10 != 0);
  return 0;
}

