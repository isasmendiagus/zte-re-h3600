// module: mt7915.ko
// function: mtd_pci_write_tx_resource @ 0x1c9df8
// size: 500 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint mtd_pci_write_tx_resource(int param_1,byte *param_2,int param_3,short *param_4)

{
  ushort uVar1;
  ushort uVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  uint uVar9;
  undefined4 *puVar10;
  uint uVar11;
  void *__dest;
  int iVar12;
  
  iVar4 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar5 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar12 = *(int *)(*(int *)(iVar5 + 8) + (uint)*param_2 * 4);
  uVar11 = (uint)*(ushort *)(iVar12 + 0x28);
  uVar1 = *(ushort *)(iVar12 + 0x5a);
  iVar5 = *(int *)(iVar12 + 0xc) + uVar11 * 0x24;
  *(undefined4 *)(iVar5 + 0x10) = 0;
  __dest = *(void **)(iVar5 + 0x1c);
  *(undefined4 *)(iVar5 + 0x14) = *(undefined4 *)(param_2 + 0x3c);
  if (param_2[5] == 5) {
    iVar6 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
    uVar8 = ((uint)param_2[0x34] +
            (uint)param_2[0x35] + (uint)*(byte *)(iVar6 + 2) + (uint)param_2[0x38]) -
            (uint)param_2[0x39] & 0xffff;
    memmove(__dest,(void *)(*(int *)(param_2 + 0x58) + (uint)param_2[0x39]),uVar8);
    *(uint *)(iVar5 + 0x18) = uVar8;
  }
  else {
    iVar6 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
    uVar8 = ((uint)param_2[0x34] +
            (uint)param_2[0x35] + (uint)*(byte *)(iVar6 + 2) + (uint)param_2[0x38]) -
            (uint)param_2[0x39] & 0xffff;
    *(uint *)(iVar5 + 0x18) = uVar8;
  }
  puVar10 = *(undefined4 **)(iVar5 + 4);
  uVar7 = RtmpDrvPciMapSingle(param_1,__dest,uVar8,0,0xff00);
  *(undefined4 *)(iVar5 + 0x20) = uVar7;
  *puVar10 = uVar7;
  uVar2 = *(ushort *)(iVar5 + 0x18);
  *(char *)((int)puVar10 + 6) = (char)uVar2;
  bVar3 = (byte)(((uint)uVar2 << 0x12) >> 0x18);
  *(byte *)((int)puVar10 + 7) = *(byte *)((int)puVar10 + 7) & 0xc0 | bVar3 >> 2;
  puVar10[2] = *(undefined4 *)(iVar5 + 0x14);
  uVar8 = (uint)*(ushort *)(iVar4 + 0x156);
  if (*(uint *)(param_2 + 0x28) <= (uint)*(ushort *)(iVar4 + 0x156)) {
    uVar8 = *(uint *)(param_2 + 0x28);
  }
  uVar9 = uVar8 & 0x3fff;
  *(char *)(puVar10 + 1) = (char)uVar9;
  *(byte *)((int)puVar10 + 7) = bVar3 >> 2 | (uVar9 == 0) << 6;
  *(byte *)((int)puVar10 + 5) = (byte)((uVar8 << 0x12) >> 0x1a) | (param_3 != 0 && uVar9 != 0) << 6;
  DataSynchronizationBarrier(0xe);
  if (___aeabi_idivmod != (code *)0x0) {
    (*___aeabi_idivmod)();
  }
  uVar8 = uVar11 + 1 & 0xffff;
  if (uVar1 <= uVar8) {
    uVar8 = 0;
  }
  *(uint *)(iVar12 + 0x28) = uVar8;
  *param_4 = *param_4 + -1;
  return uVar11;
}

