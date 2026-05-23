// module: mt7915.ko
// function: sta_ieee_802_11_data_tx @ 0x55b54
// size: 292 bytes
//

void sta_ieee_802_11_data_tx(undefined4 param_1,undefined4 param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined6 *__src;
  int iVar6;
  void *__dest;
  bool bVar7;
  
  sta_build_802_11_header(param_1,param_3);
  uVar3 = *(uint *)(param_3 + 0xc);
  iVar4 = *(int *)(param_3 + 0x28);
  iVar2 = *(int *)(param_3 + 0x24);
  *(int *)(param_3 + 0x30) = iVar2 + 0xe;
  *(int *)(param_3 + 0x28) = iVar4 + -0xe;
  bVar1 = *(byte *)(param_3 + 0x2c);
  iVar6 = (uint)*(byte *)(uVar3 + 0x30) << 0x1b;
  if (iVar6 < 0) {
    uVar3 = iVar2 + 0x12;
    *(uint *)(param_3 + 0x30) = uVar3;
    *(int *)(param_3 + 0x28) = iVar4 + -0x12;
  }
  uVar5 = bVar1 & 3;
  bVar7 = (bVar1 & 3) != 0;
  if (bVar7) {
    uVar3 = 4 - uVar5;
  }
  *(byte *)(param_3 + 0x35) = bVar1;
  if (bVar7) {
    uVar5 = uVar3 & 0xff;
  }
  *(char *)(param_3 + 0x34) = (char)uVar5;
  __dest = (void *)(*(int *)(param_3 + 0x5c) + uVar5 + bVar1);
  if (0x5dc < (uint)*(byte *)(iVar2 + 0xd) + (uint)*(byte *)(iVar2 + 0xc) * 0x100) {
    __src = &SNAP_802_1H;
    *(undefined6 **)(param_3 + 0x54) = &SNAP_802_1H;
    iVar4 = memcmp(&IPX,(void *)(iVar2 + 0xc),2);
    if ((iVar4 == 0) || (iVar2 = memcmp(&APPLE_TALK,(void *)(iVar2 + 0xc),2), iVar2 == 0)) {
      __src = &SNAP_BRIDGE_TUNNEL;
      *(undefined6 **)(param_3 + 0x54) = &SNAP_BRIDGE_TUNNEL;
    }
    memmove(__dest,__src,6);
    if (iVar6 < 0) {
      iVar2 = 0x10;
    }
    else {
      iVar2 = 0xc;
    }
    memmove((void *)((int)__dest + 6),(void *)(*(int *)(param_3 + 0x24) + iVar2),2);
    *(char *)(param_3 + 0x35) = *(char *)(param_3 + 0x35) + '\b';
    return;
  }
  *(undefined4 *)(param_3 + 0x54) = 0;
  return;
}

