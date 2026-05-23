// module: mt7915.ko
// function: pci_get_pkt_dynamic_page_ddone_debug @ 0x1cf954
// size: 888 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint pci_get_pkt_dynamic_page_ddone_debug(int *param_1,undefined1 *param_2,int *param_3,int param_4)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined1 uVar5;
  uint uVar6;
  int iVar7;
  undefined4 *puVar8;
  uint uVar9;
  bool bVar10;
  uint local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c [2];
  
  iVar2 = hc_get_hif_ctrl(param_1[0x29e5e8]);
  iVar7 = *(int *)(*(int *)(iVar2 + 4) + param_4 * 4);
  local_3c = 0;
  local_30 = 0;
  iVar2 = *(int *)(iVar7 + 0x18) + *(int *)(iVar7 + 0x10) * 0x24;
  puVar8 = *(undefined4 **)(iVar2 + 4);
  uVar9 = *(byte *)((int)puVar8 + 7) & 0xffffff80;
  uVar6 = uVar9;
  if ((*(byte *)((int)puVar8 + 7) & 0x80) == 0) {
LAB_001cf9bc:
    *param_2 = (char)uVar6;
    return uVar9;
  }
  local_2c[0] = (*(int *)(iVar2 + 0x18) + 0x3fU & 0xffffffe0) + 0xc0;
  iVar3 = FUN_001ca4e0(iVar7,puVar8,&local_30);
  if ((iVar3 == 0) ||
     (iVar4 = RTMP_AllocateRxPacketBuffer
                        (iVar7,*(undefined4 *)(*param_1 + 0xc),*(undefined4 *)(iVar2 + 0x18),
                         &local_38,&local_34), iVar4 == 0)) {
    *param_2 = 1;
    return local_3c;
  }
  linux_pci_unmap_single
            (*(undefined4 *)(*param_1 + 0xc),*(undefined4 *)(iVar2 + 0x20),
             *(undefined4 *)(iVar2 + 0x18),0xff01);
  if ((iVar3 != 1) &&
     (iVar3 = FUN_001cf2b4(param_1,param_4,iVar2,puVar8,iVar3,local_30,local_2c), iVar3 == 0)) {
    RTMPFreeNdisPacketIRQ(param_1,iVar4);
    uVar9 = local_3c;
    uVar6 = 1;
    goto LAB_001cf9bc;
  }
  if (*(int *)(iVar2 + 0xc) == 0) {
    local_3c = 0;
  }
  else {
    FUN_001cddc0(&local_3c,*(int *)(iVar2 + 0xc),local_2c[0],local_30);
    if ((local_3c != 0) && (iVar3 = FUN_001cf00c(param_1,iVar2,puVar8,param_4,local_3c), iVar3 == 1)
       ) {
      RTMPFreeNdisPacketIRQ(param_1,local_3c);
      local_3c = 0;
    }
  }
  *(undefined4 *)(iVar2 + 0x1c) = local_38;
  *(undefined4 *)(iVar2 + 0x20) = local_34;
  *(int *)(iVar2 + 0xc) = iVar4;
  *(uint *)(iVar2 + 0x18) = (uint)*(ushort *)(iVar7 + 0x2e);
  *puVar8 = local_34;
  *(undefined1 *)((int)puVar8 + 6) = *(undefined1 *)(iVar7 + 0x2e);
  *(byte *)((int)puVar8 + 7) = *(byte *)((int)puVar8 + 7) & 0xc0 | *(byte *)(iVar7 + 0x2f) & 0x3f;
  if ((param_1[0x28e7e1] & 4U) == 0) {
    if (3 < DebugLevel) {
      printk("%s(): system is not ready, rx pkt drop it.\n","pci_get_pkt_dynamic_page_ddone_debug");
    }
    if (local_3c == 0) goto LAB_001cfb60;
    uVar5 = 1;
    RTMPFreeNdisPacketIRQ(param_1);
    local_3c = 0;
  }
  else {
LAB_001cfb60:
    uVar5 = 0;
  }
  *(undefined1 *)(puVar8 + 1) = 0;
  *(undefined1 *)((int)puVar8 + 5) = 0;
  uVar1 = *(ushort *)(iVar7 + 0x10);
  *(char *)(puVar8 + 2) = (char)uVar1;
  *(byte *)((int)puVar8 + 9) =
       *(byte *)((int)puVar8 + 9) & 0xf0 | (byte)(((uint)uVar1 << 0x14) >> 0x1c);
  iVar2 = *(int *)(iVar7 + 0x10);
  uVar9 = iVar2 + 1;
  *(uint *)(iVar7 + 0x10) = uVar9;
  if (uVar9 < *(ushort *)(iVar7 + 0x14)) {
    *(short *)(iVar7 + 0x30) = *(short *)(iVar7 + 0x30) + 1;
    if (uVar9 != 0) {
      *(int *)(iVar7 + 0x34) = iVar2;
      goto LAB_001cfbe0;
    }
  }
  else {
    *(undefined4 *)(iVar7 + 0x10) = 0;
    *(short *)(iVar7 + 0x30) = *(short *)(iVar7 + 0x30) + 1;
  }
  *(uint *)(iVar7 + 0x34) = *(ushort *)(iVar7 + 0x14) - 1;
  bVar10 = 0xfffffffe < DAT_005f4908;
  DAT_005f4908 = DAT_005f4908 + 1;
  DAT_005f490c = DAT_005f490c + (uint)bVar10;
LAB_001cfbe0:
  uVar9 = DAT_005f4908 & 0xf;
  iVar2 = DAT_005f4908 << 0xc;
  *(char *)((int)puVar8 + 10) = (char)((DAT_005f4908 << 0x14) >> 0x18);
  *(byte *)((int)puVar8 + 9) = *(byte *)((int)puVar8 + 9) & 0xf | (byte)(uVar9 << 4);
  *(byte *)((int)puVar8 + 7) = *(byte *)((int)puVar8 + 7) & 0x7f;
  *(char *)((int)puVar8 + 0xb) = (char)((uint)iVar2 >> 0x18);
  DataSynchronizationBarrier(0xe);
  if (___aeabi_idivmod != (code *)0x0) {
    (*___aeabi_idivmod)();
  }
  if (*param_3 != 0) {
    HintPreloadData(*(undefined4 *)(*(int *)(iVar7 + 0x18) + *(int *)(iVar7 + 0x10) * 0x24 + 0xc));
  }
  *param_2 = uVar5;
  return local_3c;
}

