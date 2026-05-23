// module: mt7915.ko
// function: pci_write_frag_tx_resource @ 0x1ca264
// size: 464 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint pci_write_frag_tx_resource(int param_1,byte *param_2,uint param_3,short *param_4)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined4 *puVar9;
  int iVar10;
  uint uVar11;
  
  iVar3 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar10 = *(int *)(*(int *)(iVar3 + 8) + (uint)*param_2 * 4);
  uVar11 = (uint)*(ushort *)(iVar10 + 0x28);
  uVar1 = *(ushort *)(iVar10 + 0x5a);
  iVar3 = *(int *)(iVar10 + 0xc) + uVar11 * 0x24;
  uVar5 = (uint)uVar1;
  if (param_2[4] == param_3) {
    uVar5 = 0;
  }
  uVar6 = *(undefined4 *)(iVar3 + 0x1c);
  puVar9 = *(undefined4 **)(iVar3 + 4);
  if (param_2[4] == param_3) {
    uVar7 = *(undefined4 *)(param_2 + 0xc);
    *(uint *)(iVar3 + 0x10) = uVar5;
    *(undefined4 *)(iVar3 + 0xc) = uVar7;
  }
  uVar5 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((uVar5 & 0x800) == 0) {
    uVar7 = RtmpDrvPciMapSingle(param_1,param_2,0,1,0xff00);
    *(undefined4 *)(iVar3 + 0x14) = uVar7;
  }
  else {
    *(undefined4 *)(iVar3 + 0x14) = *(undefined4 *)(param_2 + 0x3c);
  }
  iVar4 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar5 = ((uint)param_2[0x34] +
          (uint)param_2[0x35] + (uint)*(byte *)(iVar4 + 2) + (uint)param_2[0x38]) -
          (uint)param_2[0x39] & 0xffff;
  *(uint *)(iVar3 + 0x18) = uVar5;
  uVar6 = RtmpDrvPciMapSingle(param_1,uVar6,uVar5,0,0xff00);
  *(undefined4 *)(iVar3 + 0x20) = uVar6;
  *puVar9 = uVar6;
  uVar2 = *(ushort *)(iVar3 + 0x18);
  *(char *)((int)puVar9 + 6) = (char)uVar2;
  *(byte *)((int)puVar9 + 7) =
       *(byte *)((int)puVar9 + 7) & 0xc0 | (byte)(((uint)uVar2 << 0x12) >> 0x1a);
  puVar9[2] = *(undefined4 *)(iVar3 + 0x14);
  uVar5 = *(uint *)(param_2 + 0x28);
  uVar8 = uVar5 & 0x3fff;
  *(char *)(puVar9 + 1) = (char)uVar8;
  *(byte *)((int)puVar9 + 5) = (byte)((uVar5 << 0x12) >> 0x1a) | (uVar8 != 0) << 6;
  *(byte *)((int)puVar9 + 7) = *(byte *)((int)puVar9 + 7) & 0x3f | (uVar8 == 0) << 6;
  DataSynchronizationBarrier(0xe);
  if (___aeabi_idivmod != (code *)0x0) {
    (*___aeabi_idivmod)();
  }
  uVar5 = uVar11 + 1 & 0xffff;
  *(int *)(param_2 + 0x7c) = *(int *)(param_2 + 0x7c) + *(int *)(param_2 + 0x28);
  if (uVar1 <= uVar5) {
    uVar5 = 0;
  }
  *(uint *)(iVar10 + 0x28) = uVar5;
  *param_4 = *param_4 + -1;
  return uVar11;
}

