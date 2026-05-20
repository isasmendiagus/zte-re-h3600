// module: mt7915.ko
// function: sta_ampdu_tx @ 0x55c78
// size: 1060 bytes
//

undefined4 sta_ampdu_tx(int param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  void *pvVar5;
  byte bVar6;
  uint uVar7;
  uint uVar8;
  void *__dest;
  int iVar9;
  byte *pbVar10;
  undefined6 *__src;
  ushort *unaff_r10;
  undefined2 local_2a [3];
  
  local_2a[0] = 0;
  iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  bVar6 = *(byte *)(iVar3 + 2);
  iVar3 = fill_tx_blk(param_1,param_2,param_3);
  if (iVar3 != 0) {
    iVar3 = *(int *)(param_3 + 8);
    if ((*(uint *)(param_3 + 0x18) & 0x800000) == 0) {
      if (*(char *)(iVar3 + 0xc1) == '\0') {
        sta_build_802_11_header(param_1,param_3);
        iVar9 = *(int *)(param_3 + 0x58) + (uint)bVar6;
      }
      else {
        iVar9 = iVar3 + 200 + (uint)bVar6;
        *(int *)(param_3 + 0x58) = iVar3 + 200;
        sta_build_cache_802_11_header(param_1,param_3,iVar9);
      }
      cVar1 = *(char *)(iVar3 + 0xc1);
      iVar4 = *(int *)(param_3 + 0xc);
      uVar7 = (uint)*(byte *)(param_3 + 0x35);
      if (cVar1 == '\0') {
        unaff_r10 = (ushort *)(iVar3 + 0x14c);
      }
      bVar6 = *(byte *)(iVar4 + 0x30);
      pbVar10 = (byte *)(iVar9 + uVar7);
      if ((cVar1 == '\0') ||
         (unaff_r10 = (ushort *)(iVar3 + 0x14c),
         (uint)*unaff_r10 !=
         ((int)*(char *)(iVar4 + 0x34) & 0xffffU | ((int)*(char *)(iVar4 + 0x35) & 0xffffU) << 8)))
      {
        if ((*(char *)(param_1 + 0x79507d) == '\x01') &&
           ((*(uint *)(*(int *)(param_3 + 0x14) + 0xb4) & 0x200) != 0)) {
          if (cVar1 == '\0') {
            __memzero(pbVar10,4);
            pbVar10[3] = pbVar10[3] | 0x80;
          }
          pbVar10 = pbVar10 + 4;
          *(byte *)(iVar9 + 1) = *(byte *)(iVar9 + 1) | 0x80;
          bVar6 = *(char *)(param_3 + 0x35) + 4;
          *(char *)(param_3 + 0x2c) = *(char *)(param_3 + 0x2c) + '\x04';
          uVar7 = (uint)bVar6;
          *(byte *)(param_3 + 0x35) = bVar6;
        }
        if (uVar7 < 0x18) {
          printk(&_LC22,0x3fb);
          dump_stack();
        }
        iVar9 = *(int *)(param_3 + 0x28);
        __dest = (void *)((uint)(pbVar10 + 3) & 0xfffffffc);
        cVar1 = (char)__dest - (char)pbVar10;
        *(int *)(param_3 + 0x30) = *(int *)(param_3 + 0x24) + 0xe;
        *(int *)(param_3 + 0x28) = iVar9 + -0xe;
        bVar6 = *(byte *)(*(int *)(param_3 + 0xc) + 0x30);
        *(char *)(param_3 + 0x34) = cVar1;
        if ((bVar6 & 0x10) != 0) {
          *(int *)(param_3 + 0x30) = *(int *)(param_3 + 0x24) + 0x12;
          *(int *)(param_3 + 0x28) = iVar9 + -0x12;
        }
        *(char *)(iVar3 + 0x148) = cVar1;
        iVar9 = *(int *)(param_3 + 0x30);
        if ((uint)*(byte *)(iVar9 + -1) + (uint)*(byte *)(iVar9 + -2) * 0x100 < 0x5dd) {
          *(undefined4 *)(param_3 + 0x54) = 0;
        }
        else {
          __src = &SNAP_802_1H;
          *(undefined6 **)(param_3 + 0x54) = &SNAP_802_1H;
          iVar4 = memcmp(&IPX,(void *)(iVar9 + -2),2);
          if ((iVar4 == 0) || (iVar9 = memcmp(&APPLE_TALK,(void *)(iVar9 + -2),2), iVar9 == 0)) {
            __src = &SNAP_BRIDGE_TUNNEL;
            *(undefined6 **)(param_3 + 0x54) = &SNAP_BRIDGE_TUNNEL;
          }
          memmove(__dest,__src,6);
          pvVar5 = (void *)((int)__dest + 6);
          __dest = (void *)((int)__dest + 8);
          memmove(pvVar5,(void *)(*(int *)(param_3 + 0x30) + -2),2);
          *(char *)(param_3 + 0x35) = *(char *)(param_3 + 0x35) + '\b';
        }
        *unaff_r10 = (short)*(char *)(*(int *)(param_3 + 0xc) + 0x34) |
                     (short)*(char *)(*(int *)(param_3 + 0xc) + 0x35) << 8;
        *(undefined1 *)(iVar3 + 0x149) = *(undefined1 *)(param_3 + 0x35);
        *(undefined1 *)(iVar3 + 0x14a) = *(undefined1 *)(param_3 + 0x2c);
      }
      else {
        *pbVar10 = *(byte *)(param_3 + 0x1c) & 0xf;
        iVar4 = *(int *)(param_3 + 0x28);
        __dest = (void *)(iVar9 + (uint)*(byte *)(iVar3 + 0x149));
        *(byte *)(param_3 + 0x35) = *(byte *)(iVar3 + 0x149);
        *(undefined1 *)(param_3 + 0x2c) = *(undefined1 *)(iVar3 + 0x14a);
        uVar2 = *(undefined1 *)(iVar3 + 0x148);
        *(int *)(param_3 + 0x30) = *(int *)(param_3 + 0x24) + 0xe;
        *(int *)(param_3 + 0x28) = iVar4 + -0xe;
        *(undefined1 *)(param_3 + 0x34) = uVar2;
        if ((bVar6 & 0x10) != 0) {
          *(int *)(param_3 + 0x30) = *(int *)(param_3 + 0x24) + 0x12;
          *(int *)(param_3 + 0x28) = iVar4 + -0x12;
        }
      }
    }
    else {
      __dest = (void *)0x0;
      *(undefined1 *)(param_3 + 0x35) = 0;
      *(undefined1 *)(param_3 + 0x34) = 2;
      *(undefined4 *)(param_3 + 0x30) = *(undefined4 *)(param_3 + 0x24);
    }
    if (*(char *)(iVar3 + 0xc1) == '\0') {
      asic_write_tmac_info(param_1,*(undefined4 *)(param_3 + 0x58),param_3);
      if (((*(byte *)(*(int *)(param_3 + 0xc) + 0x30) & 0x4b) != 0) ||
         ((*(byte *)(*(int *)(param_3 + 0xc) + 0x4e) & 2) != 0)) {
        *(undefined1 *)(iVar3 + 0xc1) = 0;
      }
      __memzero((void *)(iVar3 + 0x150),0x40);
      pvVar5 = (void *)(*(int *)(param_3 + 0x58) + 4);
      memmove((void *)(iVar3 + 0x150),pvVar5,(int)__dest - (int)pvVar5);
      __memzero((void *)(iVar3 + 200),0x80);
      memmove((void *)(iVar3 + 200),*(void **)(param_3 + 0x58),
              (int)__dest - (int)*(void **)(param_3 + 0x58));
    }
    else {
      asic_write_tmac_info(param_1,*(undefined4 *)(param_3 + 0x58),param_3);
    }
    *(int *)(param_1 + 0xa39ef0) = *(int *)(param_1 + 0xa39ef0) + 1;
    uVar7 = *(uint *)(param_3 + 0x28);
    uVar8 = *(uint *)(param_1 + 0xa39ef8);
    *(uint *)(param_1 + 0xa39ef8) = uVar8 + uVar7;
    *(uint *)(param_1 + 0xa39efc) = *(int *)(param_1 + 0xa39efc) + (uint)CARRY4(uVar8,uVar7);
    *(int *)(param_1 + 0xa78a18) = *(int *)(param_3 + 0x28) + *(int *)(param_1 + 0xa78a18);
    asic_write_tx_resource(param_1,param_3,1,local_2a);
    return 0;
  }
  *(int *)(param_1 + 0x9db94) = *(int *)(param_1 + 0x9db94) + 1;
  RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0xc));
  return 1;
}

