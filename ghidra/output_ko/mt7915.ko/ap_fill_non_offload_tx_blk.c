// module: mt7915.ko
// function: ap_fill_non_offload_tx_blk @ 0x1a534
// size: 1272 bytes
//

undefined4 ap_fill_non_offload_tx_blk(int param_1,int param_2,int param_3)

{
  undefined1 uVar1;
  uint uVar2;
  byte bVar3;
  ushort *puVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  bool bVar11;
  
  iVar9 = *(int *)(param_3 + 0xc);
  iVar10 = *(int *)(param_2 + 0x904);
  *(undefined4 *)(param_3 + 0x24) = *(undefined4 *)(iVar9 + 0xcc);
  *(undefined4 *)(param_3 + 0x28) = *(undefined4 *)(iVar9 + 100);
  *(undefined2 *)(param_3 + 0x1e) = *(undefined2 *)(iVar9 + 0x42);
  uVar1 = HcGetWmmIdx();
  *(undefined1 *)(param_3 + 0x20) = uVar1;
  uVar1 = *(undefined1 *)(iVar9 + 0x2a);
  *(undefined4 *)(param_3 + 0x30) = *(undefined4 *)(param_3 + 0x24);
  *(undefined1 *)(param_3 + 0x60) = 0;
  *(undefined1 *)(param_3 + 0x1c) = uVar1;
  *(undefined4 *)(param_3 + 0x78) = 0;
  uVar2 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((uVar2 & 0x40) == 0) {
LAB_0001a5b4:
    uVar2 = *(uint *)(param_3 + 0x18);
  }
  else {
    bVar3 = *(byte *)(param_3 + 5);
    bVar11 = 3 < bVar3;
    if (bVar3 != 4) {
      bVar11 = bVar3 != 1;
    }
    if (bVar11 && (bVar3 != 4 && bVar3 != 2)) goto LAB_0001a5b4;
    uVar2 = *(uint *)(param_3 + 0x18) | 0x800000;
    *(uint *)(param_3 + 0x18) = uVar2;
  }
  if (*(char *)(*(int *)(param_3 + 0xc) + 0x2e) == '\0') {
    uVar2 = uVar2 & 0xfffffeff;
  }
  else {
    uVar2 = uVar2 | 0x100;
  }
  *(uint *)(param_3 + 0x18) = uVar2;
  if (**(int **)(param_3 + 8) == 0x400) {
    *(undefined4 *)(param_3 + 0x14) = 0;
    uVar2 = *(uint *)(param_3 + 0x18) | 0x80000;
    *(uint *)(param_3 + 0x18) = uVar2;
    if (**(byte **)(iVar9 + 0xcc) == 0xff) {
      bVar3 = 0;
    }
    else {
      bVar3 = **(byte **)(iVar9 + 0xcc) & 1;
    }
    if (bVar3 == 0) {
      puVar4 = (ushort *)(param_1 + 0xa1ddc);
      *(ushort **)(param_3 + 0x50) = puVar4;
      if (0xe < *(byte *)(*(int *)(param_3 + 0x10) + 0x1a)) {
        *(byte *)(param_1 + 0xa1ddd) = *(byte *)(param_1 + 0xa1ddd) & 0x1f | 0x20;
        **(byte **)(param_3 + 0x50) = **(byte **)(param_3 + 0x50) & 0xc0;
        uVar2 = *(uint *)(param_3 + 0x18);
        puVar4 = *(ushort **)(param_3 + 0x50);
      }
    }
    else {
      puVar4 = (ushort *)(param_2 + 0xb0c);
      *(ushort **)(param_3 + 0x50) = puVar4;
    }
    *(uint *)(param_3 + 0x18) = uVar2 & 0xffffffcd;
    if (*(char *)(iVar9 + 0x2f) != '\0') {
      *(uint *)(param_3 + 0x18) = uVar2 & 0xffffffcd | 0x40;
    }
    goto LAB_0001a6b8;
  }
  uVar2 = (uint)*(ushort *)(param_3 + 0x1e);
  iVar6 = uVar2 * 0x14c0;
  iVar8 = param_1 + iVar6 + 0xa1d20;
  *(int *)(param_3 + 0x50) = param_1 + iVar6 + 0xa1ddc;
  *(int *)(param_3 + 0x14) = iVar8;
  if (iVar8 == 0) {
    if (3 < DebugLevel) {
      printk("%s():Err!! pMacEntry is NULL!!\n","ap_fill_non_offload_tx_blk");
    }
  }
  else {
    *(undefined4 *)(param_3 + 0x78) = *(undefined4 *)(param_1 + iVar6 + 0xa1e14);
  }
  if (*(char *)(param_1 + (uint)*(byte *)(param_3 + 1) + 0x79511c) == '\0') {
    uVar7 = *(uint *)(param_3 + 0x18) | 2;
  }
  else {
    uVar7 = *(uint *)(param_3 + 0x18) & 0xfffffffd;
  }
  *(uint *)(param_3 + 0x18) = uVar7;
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    if ((iVar8 == 0) || (iVar6 = uVar2 * 0x14c0 + param_1, *(int *)(iVar6 + 0xa1d20) != 0x20001)) {
      return 0;
    }
    if ((*(char *)(iVar6 + 0xa1e08) != '\0') &&
       ((*(byte *)(*(int *)(param_3 + 0xc) + 0x30) & 2) == 0)) {
      uVar7 = uVar7 | 0x8000000;
      *(uint *)(param_3 + 0x18) = uVar7;
    }
    if (((*(uint *)(param_1 + 0x795124) & 0x100) != 0) &&
       ((*(uint *)(uVar2 * 0x14c0 + param_1 + 0xa1dd4) & 1) != 0)) {
      uVar7 = uVar7 | 0x10;
      *(uint *)(param_3 + 0x18) = uVar7;
    }
  }
  if (*(char *)(param_3 + 5) == '\x02') {
    if (((*(byte *)(iVar9 + 0x30) & 0x4b) == 0) && ((*(byte *)(iVar9 + 0x4e) & 2) == 0)) {
      if (*(char *)(param_1 + 0x286285) == '\x01') {
LAB_0001a820:
        if ((*(ushort *)(uVar2 * 0x14c0 + param_1 + 0xa1dde) & 0xe03f) == 0) goto LAB_0001a840;
      }
      goto LAB_0001a7a0;
    }
    if ((iVar8 == 0) || (*(char *)(uVar2 * 0x14c0 + param_1 + 0xa2883) == '\0')) {
LAB_0001a840:
      *(uint *)(param_3 + 0x18) = uVar7 | 0x80000;
      *(int *)(param_3 + 0x50) = param_1 + 0xa1ddc;
      if (*(int *)(param_3 + 0x14) == 0) {
        if (3 < DebugLevel) {
          printk("%s():Err!! pTxBlk->pMacEntry is NULL!!\n","ap_fill_non_offload_tx_blk");
          goto LAB_0001a7a0;
        }
        if (iVar8 != 0) goto LAB_0001a7a8;
      }
      else {
        if ((((0x3f < *(byte *)(*(int *)(param_3 + 0x14) + 0xbf)) &&
             (uVar5 = *(uint *)(uVar2 * 0x14c0 + param_1 + 0xa1dd4), (uVar5 & 0x100000) != 0)) &&
            (*(char *)(param_1 + 0x79507d) == '\x01')) && ((uVar5 & 0x200) != 0)) {
          *(uint *)(param_3 + 0x18) = uVar7 & 0xffffffef | 0x80000;
        }
LAB_0001a7a0:
        if (iVar8 != 0) goto LAB_0001a7a8;
        if (3 < DebugLevel) {
          printk("%s():Err!! pMacEntry is NULL!!\n","ap_fill_non_offload_tx_blk");
        }
      }
    }
    else {
      if (*(char *)(param_1 + 0x286285) == '\x01') goto LAB_0001a820;
LAB_0001a7a8:
      iVar6 = uVar2 * 0x14c0 + param_1;
      if ((*(byte *)(iVar6 + 0xa1ddd) < 0x40) && ((*(uint *)(iVar6 + 0xa1dd4) & 4) != 0)) {
        *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 4;
      }
    }
    if (*(char *)(iVar9 + 0x2f) != '\0') {
      *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x40;
    }
    if (*(char *)(iVar9 + 0x33) != '\0') {
      *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x800;
    }
  }
  else if (*(char *)(param_3 + 5) == '\x05') {
    *(uint *)(param_3 + 0x18) = uVar7 | 0x20;
  }
  if (iVar8 == 0) {
    if (3 < DebugLevel) {
      printk("%s():Err!! pMacEntry is NULL!!\n","ap_fill_non_offload_tx_blk");
    }
  }
  else {
    iVar6 = uVar2 * 0x14c0 + param_1;
    *(int *)(iVar6 + 0xa2894) = *(int *)(iVar6 + 0xa2894) + 1;
  }
  puVar4 = *(ushort **)(param_3 + 0x50);
  if ((*(byte *)(iVar9 + 0x4e) & 4) != 0) {
    *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x2000000;
  }
LAB_0001a6b8:
  *(uint *)(param_1 + 0xa39f9c) = (uint)*puVar4;
  (**(code **)(iVar10 + 0x80))(param_1,param_2,param_3);
  return 1;
}

