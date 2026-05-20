// module: mt7915.ko
// function: sta_fill_non_offload_tx_blk @ 0x53fb8
// size: 1536 bytes
//

undefined4 sta_fill_non_offload_tx_blk(int param_1,int param_2,int param_3)

{
  byte bVar1;
  undefined1 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  char cVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  undefined4 *puVar12;
  uint uVar13;
  bool bVar14;
  
  iVar10 = *(int *)(param_3 + 0xc);
  iVar11 = *(int *)(param_2 + 0x904);
  *(undefined4 *)(param_3 + 0x24) = *(undefined4 *)(iVar10 + 0xcc);
  *(undefined4 *)(param_3 + 0x28) = *(undefined4 *)(iVar10 + 100);
  *(undefined2 *)(param_3 + 0x1e) = *(undefined2 *)(iVar10 + 0x42);
  uVar2 = HcGetWmmIdx();
  *(undefined1 *)(param_3 + 0x20) = uVar2;
  uVar2 = *(undefined1 *)(iVar10 + 0x2a);
  *(undefined1 *)(param_3 + 0x60) = 0;
  *(undefined4 *)(param_3 + 0x30) = *(undefined4 *)(param_3 + 0x24);
  *(undefined1 *)(param_3 + 0x1c) = uVar2;
  uVar3 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((uVar3 & 0x40) == 0) {
LAB_00054038:
    uVar3 = *(uint *)(param_3 + 0x18);
  }
  else {
    bVar1 = *(byte *)(param_3 + 5);
    bVar14 = 3 < bVar1;
    if (bVar1 != 4) {
      bVar14 = bVar1 != 1;
    }
    if (bVar14 && (bVar1 != 4 && bVar1 != 2)) goto LAB_00054038;
    uVar3 = *(uint *)(param_3 + 0x18) | 0x800000;
    *(uint *)(param_3 + 0x18) = uVar3;
  }
  if (*(char *)(*(int *)(param_3 + 0xc) + 0x2e) == '\0') {
    uVar3 = uVar3 & 0xfffffeff;
  }
  else {
    uVar3 = uVar3 | 0x100;
  }
  *(uint *)(param_3 + 0x18) = uVar3;
  if (**(int **)(param_3 + 8) == 0x400) {
    *(undefined4 *)(param_3 + 0x14) = 0;
    *(uint *)(param_3 + 0x18) = uVar3 | 0x80000;
    *(int *)(param_3 + 0x50) = param_1 + 0xa1ddc;
    *(byte *)(param_1 + 0xa1ddd) = *(byte *)(param_1 + 0xa1ddd) & 0x1f | 0x20;
    **(byte **)(param_3 + 0x50) = **(byte **)(param_3 + 0x50) & 0xc0;
    uVar3 = *(uint *)(param_3 + 0x18) & 0xffffffcd;
    *(uint *)(param_3 + 0x18) = uVar3;
    if (*(char *)(iVar10 + 0x2f) != '\0') {
      *(uint *)(param_3 + 0x18) = uVar3 | 0x40;
    }
    if (((*(uint *)(param_1 + 0x795124) & 2) != 0) && ((*(byte *)(param_1 + 0xa77bcf) & 1) != 0)) {
      cVar6 = *(char *)(param_3 + 5);
      bVar14 = cVar6 != '\0';
      if (cVar6 != '\x01') {
        bVar14 = cVar6 != '\x06';
      }
      if (bVar14 && (cVar6 != '\x01' && cVar6 != '\a')) {
        iVar4 = memcmp((void *)(param_1 + 0x794b5b),(void *)(*(int *)(iVar10 + 0xcc) + 6),6);
        iVar5 = DebugLevel;
        if ((iVar4 != 0) &&
           (*(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x2000, 3 < iVar5)) {
          printk("@@ %s: Dongle Packet)\n","sta_fill_non_offload_tx_blk");
        }
        iVar5 = MATEngineTxHandle(param_1,iVar10,0,**(undefined4 **)(param_3 + 0x14));
        if (iVar5 != 0) {
          RTMPFreeNdisPacket(param_1,iVar10);
          *(undefined4 *)(param_3 + 0x24) = *(undefined4 *)(iVar5 + 0xcc);
          uVar8 = *(undefined4 *)(iVar5 + 100);
          *(int *)(param_3 + 0xc) = iVar5;
          *(undefined4 *)(param_3 + 0x28) = uVar8;
        }
      }
    }
    goto LAB_0005410c;
  }
  uVar13 = (uint)*(ushort *)(param_3 + 0x1e);
  puVar12 = (undefined4 *)(param_1 + uVar13 * 0x14c0 + 0xa1d20);
  *(uint *)(param_3 + 0x50) = param_1 + uVar13 * 0x14c0 + 0xa1ddc;
  *(undefined4 **)(param_3 + 0x14) = puVar12;
  if (*(char *)(param_1 + (uint)*(byte *)(param_3 + 1) + 0x79511c) == '\0') {
    uVar3 = uVar3 | 2;
  }
  else {
    uVar3 = uVar3 & 0xfffffffd;
  }
  *(uint *)(param_3 + 0x18) = uVar3;
  if (*(char *)(param_1 + 0x286285) == '\0') {
    cVar6 = *(char *)(param_3 + 5);
    if ((*(byte *)(param_1 + 0xa77bcf) & 1) != 0) {
      bVar14 = cVar6 != '\0';
      if (cVar6 != '\x01') {
        bVar14 = cVar6 != '\x06';
      }
      if (bVar14 && (cVar6 != '\x01' && cVar6 != '\a')) {
        iVar4 = memcmp((void *)(param_1 + 0x794b5b),(void *)(*(int *)(iVar10 + 0xcc) + 6),6);
        iVar5 = DebugLevel;
        puVar7 = puVar12;
        if ((iVar4 != 0) &&
           (*(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x2000, 3 < iVar5)) {
          printk("%s(): Dongle Packet)\n","sta_fill_non_offload_tx_blk");
          puVar7 = *(undefined4 **)(param_3 + 0x14);
        }
        iVar5 = MATEngineTxHandle(param_1,iVar10,0,*puVar7);
        if (iVar5 != 0) {
          RTMPFreeNdisPacket(param_1,iVar10);
          *(undefined4 *)(param_3 + 0x24) = *(undefined4 *)(iVar5 + 0xcc);
          uVar8 = *(undefined4 *)(iVar5 + 100);
          *(int *)(param_3 + 0xc) = iVar5;
          *(undefined4 *)(param_3 + 0x28) = uVar8;
          iVar10 = iVar5;
        }
        if ((*(uint *)(param_3 + 0x18) & 0x800000) == 0) {
          cVar6 = *(char *)(param_3 + 5);
        }
        else {
          memmove((void *)(*(int *)(*(int *)(param_3 + 0xc) + 0xcc) + 6),(void *)(param_2 + 0x1b),6)
          ;
          cVar6 = *(char *)(param_3 + 5);
        }
      }
    }
    if ((*(uint *)(param_1 + 0x795124) & 0x100) == 0) goto LAB_000540d4;
    if ((*(uint *)(uVar13 * 0x14c0 + param_1 + 0xa1dd4) & 1) != 0) {
      *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x10;
    }
    if (cVar6 != '\x02') goto LAB_000540dc;
LAB_00054288:
    if (((*(byte *)(iVar10 + 0x30) & 0x4b) == 0) && ((*(byte *)(iVar10 + 0x4e) & 2) == 0)) {
      if (*(char *)(param_1 + 0x286285) == '\x01') {
LAB_000544a4:
        if ((*(ushort *)(uVar13 * 0x14c0 + param_1 + 0xa1dde) & 0xe03f) == 0) goto LAB_000544c4;
      }
      goto LAB_000542ac;
    }
    if ((puVar12 == (undefined4 *)0x0) || (*(char *)(uVar13 * 0x14c0 + param_1 + 0xa2883) == '\0'))
    {
LAB_000544c4:
      uVar3 = *(uint *)(param_3 + 0x18);
      *(int *)(param_3 + 0x50) = param_1 + 0xa1ddc;
      *(uint *)(param_3 + 0x18) = uVar3 | 0x80000;
      if (*(int *)(param_3 + 0x14) == 0) {
        if (3 < DebugLevel) {
          printk("%s():Err!! pTxBlk->pMacEntry is NULL!!\n","sta_fill_non_offload_tx_blk");
          goto LAB_000542ac;
        }
        if (puVar12 != (undefined4 *)0x0) goto LAB_000542b4;
      }
      else {
        if ((((0x3f < *(byte *)(*(int *)(param_3 + 0x14) + 0xbf)) &&
             (uVar9 = *(uint *)(uVar13 * 0x14c0 + param_1 + 0xa1dd4), (uVar9 & 0x100000) != 0)) &&
            (*(char *)(param_1 + 0x79507d) == '\x01')) && ((uVar9 & 0x200) != 0)) {
          *(uint *)(param_3 + 0x18) = uVar3 & 0xffffffef | 0x80000;
        }
LAB_000542ac:
        if (puVar12 != (undefined4 *)0x0) goto LAB_000542b4;
        if (3 < DebugLevel) {
          printk("%s():Err!! pMacEntry is NULL!!\n","sta_fill_non_offload_tx_blk");
        }
      }
    }
    else {
      if (*(char *)(param_1 + 0x286285) == '\x01') goto LAB_000544a4;
LAB_000542b4:
      iVar5 = uVar13 * 0x14c0 + param_1;
      if ((*(byte *)(iVar5 + 0xa1ddd) < 0x40) && ((*(uint *)(iVar5 + 0xa1dd4) & 4) != 0)) {
        *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 4;
      }
    }
    if (*(char *)(iVar10 + 0x2f) != '\0') {
      *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x40;
    }
    if (*(char *)(iVar10 + 0x33) != '\0') {
      *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x800;
    }
  }
  else {
    cVar6 = *(char *)(param_3 + 5);
LAB_000540d4:
    if (cVar6 == '\x02') goto LAB_00054288;
LAB_000540dc:
    if (cVar6 == '\x05') {
      *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x20;
    }
  }
  if (puVar12 == (undefined4 *)0x0) {
    if (3 < DebugLevel) {
      printk("%s():Err!! pMacEntry is NULL!!\n","sta_fill_non_offload_tx_blk");
    }
  }
  else {
    iVar10 = uVar13 * 0x14c0 + param_1;
    *(int *)(iVar10 + 0xa2894) = *(int *)(iVar10 + 0xa2894) + 1;
  }
LAB_0005410c:
  *(uint *)(param_1 + 0xa39f9c) = (uint)**(ushort **)(param_3 + 0x50);
  (**(code **)(iVar11 + 0x80))(param_1,param_2,param_3);
  return 1;
}

