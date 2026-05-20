// module: mt7915.ko
// function: mt_pci_write_multi_tx_resource @ 0x1c9a10
// size: 532 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint mt_pci_write_multi_tx_resource(int param_1,byte *param_2,int param_3,short *param_4)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  void *__dest;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 *puVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  
  iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar4 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_2[5] != 4) {
    printk(&_LC13,0x218);
    dump_stack();
  }
  bVar1 = param_2[3];
  iVar10 = *(int *)(*(int *)(iVar4 + 8) + (uint)*param_2 * 4);
  uVar12 = (uint)*(ushort *)(iVar10 + 0x28);
  uVar2 = *(ushort *)(iVar10 + 0x5a);
  iVar4 = uVar12 * 0x24;
  iVar7 = *(int *)(iVar10 + 0xc) + iVar4;
  __dest = *(void **)(iVar7 + 0x1c);
  uVar8 = *(undefined4 *)(iVar7 + 0x20);
  if (param_3 == 0) {
    uVar11 = ((uint)*(byte *)(iVar3 + 2) - (uint)param_2[0x39]) + (uint)param_2[0x35] +
             (uint)param_2[0x34];
    memmove(__dest,(void *)(*(int *)(param_2 + 0x58) + (uint)param_2[0x39]),uVar11);
  }
  else {
    uVar11 = (uint)param_2[0x35];
    memmove(__dest,*(void **)(param_2 + 0x58),uVar11);
  }
  *(undefined4 *)(*(int *)(iVar10 + 0xc) + iVar4 + 0xc) = *(undefined4 *)(param_2 + 0xc);
  *(undefined4 *)(*(int *)(iVar10 + 0xc) + iVar4 + 0x10) = 0;
  iVar3 = *(int *)(iVar10 + 0xc);
  uVar5 = RtmpDrvPciMapSingle(param_1,param_2,0,1,0xff00);
  *(undefined4 *)(iVar3 + iVar4 + 0x14) = uVar5;
  puVar9 = *(undefined4 **)(*(int *)(iVar10 + 0xc) + iVar4 + 4);
  *(char *)((int)puVar9 + 6) = (char)(uVar11 & 0xffff);
  *puVar9 = uVar8;
  *(byte *)((int)puVar9 + 7) =
       *(byte *)((int)puVar9 + 7) & 0xc0 | (byte)(((uVar11 & 0xffff) << 0x12) >> 0x1a);
  puVar9[2] = *(undefined4 *)(*(int *)(iVar10 + 0xc) + iVar4 + 0x14);
  uVar11 = *(uint *)(param_2 + 0x28);
  uVar6 = uVar11 & 0x3fff;
  *(char *)(puVar9 + 1) = (char)uVar6;
  *(byte *)((int)puVar9 + 5) =
       (byte)((uVar11 << 0x12) >> 0x1a) | (uVar6 != 0 && param_3 == bVar1 - 1) << 6;
  *(byte *)((int)puVar9 + 7) = *(byte *)((int)puVar9 + 7) & 0x3f | (uVar6 == 0) << 6;
  DataSynchronizationBarrier(0xe);
  if (___aeabi_idivmod != (code *)0x0) {
    (*___aeabi_idivmod)();
  }
  uVar11 = uVar12 + 1 & 0xffff;
  if (uVar2 <= uVar11) {
    uVar11 = 0;
  }
  *(uint *)(iVar10 + 0x28) = uVar11;
  *param_4 = *param_4 + -1;
  return uVar12;
}

