// module: mt7915.ko
// function: mt_pci_write_tx_resource @ 0x1c986c
// size: 420 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint mt_pci_write_tx_resource(int param_1,byte *param_2,int param_3,short *param_4)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  void *__dest;
  undefined4 *puVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  undefined4 uVar10;
  
  iVar2 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar6 = *(int *)(*(int *)(iVar2 + 8) + (uint)*param_2 * 4);
  uVar7 = (uint)*(ushort *)(iVar6 + 0x28);
  iVar2 = uVar7 * 0x24;
  iVar9 = *(int *)(iVar6 + 0xc) + iVar2;
  *(undefined4 *)(iVar9 + 0xc) = *(undefined4 *)(param_2 + 0xc);
  __dest = *(void **)(iVar9 + 0x1c);
  uVar10 = *(undefined4 *)(iVar9 + 0x20);
  *(undefined4 *)(*(int *)(iVar6 + 0xc) + iVar2 + 0x10) = 0;
  iVar9 = *(int *)(iVar6 + 0xc);
  uVar3 = RtmpDrvPciMapSingle(param_1,param_2,0,1,0xff00);
  *(undefined4 *)(iVar9 + iVar2 + 0x14) = uVar3;
  puVar5 = *(undefined4 **)(*(int *)(iVar6 + 0xc) + iVar2 + 4);
  *puVar5 = uVar10;
  iVar9 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar8 = ((uint)param_2[0x34] +
          (uint)param_2[0x35] + (uint)*(byte *)(iVar9 + 2) + (uint)param_2[0x38]) -
          (uint)param_2[0x39] & 0xffff;
  memmove(__dest,(void *)(*(int *)(param_2 + 0x58) + (uint)param_2[0x39]),uVar8);
  *(char *)((int)puVar5 + 6) = (char)uVar8;
  bVar1 = (byte)((uVar8 << 0x12) >> 0x18);
  *(byte *)((int)puVar5 + 7) = *(byte *)((int)puVar5 + 7) & 0xc0 | bVar1 >> 2;
  puVar5[2] = *(undefined4 *)(*(int *)(iVar6 + 0xc) + iVar2 + 0x14);
  uVar8 = *(uint *)(param_2 + 0x28);
  uVar4 = uVar8 & 0x3fff;
  *(char *)(puVar5 + 1) = (char)uVar4;
  *(byte *)((int)puVar5 + 7) = bVar1 >> 2 | (uVar4 == 0) << 6;
  *(byte *)((int)puVar5 + 5) = (byte)((uVar8 << 0x12) >> 0x1a) | (param_3 != 0 && uVar4 != 0) << 6;
  DataSynchronizationBarrier(0xe);
  if (___aeabi_idivmod != (code *)0x0) {
    (*___aeabi_idivmod)();
  }
  *(uint *)(iVar6 + 0x28) = uVar7;
  *param_4 = *param_4 + -1;
  return uVar7;
}

