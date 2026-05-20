// module: mt7915.ko
// function: apcli_fill_offload_tx_blk @ 0x67994
// size: 664 bytes
//

undefined4 apcli_fill_offload_tx_blk(int param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  char cVar1;
  undefined1 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  undefined *__src;
  bool bVar9;
  bool bVar10;
  bool bVar11;
  
  iVar8 = *(int *)(param_3 + 0xc);
  *(undefined2 *)(param_3 + 0x1e) = *(undefined2 *)(iVar8 + 0x42);
  *(undefined4 *)(param_3 + 0x24) = *(undefined4 *)(iVar8 + 0xcc);
  *(undefined4 *)(param_3 + 0x28) = *(undefined4 *)(iVar8 + 100);
  if ((*(byte *)(iVar8 + 0x3a) & 8) != 0) {
    *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x100000;
  }
  if (*(char *)(iVar8 + 0x2e) != '\0') {
    *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x100;
  }
  uVar3 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((uVar3 & 0x40) != 0) {
    uVar3 = (uint)*(byte *)(param_3 + 5);
    bVar11 = 3 < uVar3;
    bVar9 = uVar3 != 4;
    if (bVar9) {
      bVar11 = uVar3 != 1;
    }
    bVar10 = uVar3 == 2;
    if (!bVar11 || (!bVar9 || bVar10)) {
      uVar3 = *(uint *)(param_3 + 0x18);
    }
    if (!bVar11 || (!bVar9 || bVar10)) {
      uVar3 = uVar3 | 0x800000;
    }
    if (!bVar11 || (!bVar9 || bVar10)) {
      *(uint *)(param_3 + 0x18) = uVar3;
    }
  }
  uVar3 = (uint)*(ushort *)(param_3 + 0x1e);
  iVar4 = param_1 + uVar3 * 0x14c0;
  if (*(char *)(iVar4 + 0xa1e08) != '\0') {
    iVar8 = param_1 + uVar3 * 0x14c0 + 0xa1d20;
    *(int *)(param_3 + 0x14) = iVar8;
    uVar6 = GetStaCfgByWdev(param_1,*(undefined4 *)(iVar4 + 0xa1d28),iVar4,iVar8,param_4);
    *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x8000000;
    *(undefined4 *)(param_3 + 0x74) = uVar6;
    goto LAB_00067b88;
  }
  if (*(int *)(iVar4 + 0xa1d20) != 2 && *(int *)(iVar4 + 0xa1d20) != 0x40001) goto LAB_00067b88;
  cVar1 = *(char *)(param_3 + 5);
  bVar11 = cVar1 != '\0';
  if (cVar1 != '\x01') {
    bVar11 = cVar1 != '\x06';
  }
  if (!bVar11 || (cVar1 == '\x01' || cVar1 == '\a')) goto LAB_00067b88;
  iVar5 = *(int *)(iVar4 + 0xa281c);
  if (((iVar5 == 0) || (*(char *)(iVar5 + 5) != '\x02')) || ((&DAT_0036790d)[param_1] == '\0')) {
    iVar4 = uVar3 * 0x14c0 + param_1;
    iVar5 = MATEngineTxHandle(param_1,iVar8,*(undefined1 *)(iVar4 + 0xa1e04));
    __src = &DAT_0036db73 + param_1 + (uint)*(byte *)(iVar4 + 0xa1e04) * 0x2137b0;
LAB_00067ad4:
    if (iVar5 != 0) {
      RTMPFreeNdisPacket(param_1,iVar8);
      *(undefined4 *)(param_3 + 0x24) = *(undefined4 *)(iVar5 + 0xcc);
      uVar6 = *(undefined4 *)(iVar5 + 100);
      *(int *)(param_3 + 0xc) = iVar5;
      *(undefined4 *)(param_3 + 0x28) = uVar6;
      iVar8 = iVar5;
    }
    uVar7 = (uint)(*(int *)(param_3 + 0x18) << 8) >> 0x1f;
    if (__src == (undefined *)0x0) {
      uVar7 = 0;
    }
    if (uVar7 != 0) {
      memmove((void *)(*(int *)(iVar8 + 0xcc) + 6),__src,6);
    }
  }
  else {
    *(undefined *)(param_1 + 0x794b40) = (&DAT_0036790d)[param_1];
    if ((&DAT_00367910)[param_1] != '\x01') {
      iVar5 = MATEngineTxHandle(param_1,iVar8,*(undefined1 *)(iVar5 + 2));
      __src = (undefined *)(*(int *)(iVar4 + 0xa281c) + 0x83);
      goto LAB_00067ad4;
    }
  }
  iVar8 = uVar3 * 0x14c0 + param_1;
  uVar6 = GetStaCfgByWdev(param_1,*(undefined4 *)(iVar8 + 0xa1d28),0x14c0,0xa1d28,param_4);
  *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x200;
  *(undefined4 *)(param_3 + 0x74) = uVar6;
  iVar8 = *(int *)(iVar8 + 0xa281c);
  if ((iVar8 != 0) && (*(char *)(iVar8 + 5) == '\x02')) {
    *(undefined4 *)(iVar8 + 0x4148) = 0;
  }
LAB_00067b88:
  uVar2 = HcGetWmmIdx(param_1,param_2);
  *(undefined4 *)(param_3 + 0x30) = *(undefined4 *)(param_3 + 0x24);
  *(undefined1 *)(param_3 + 0x20) = uVar2;
  return 1;
}

