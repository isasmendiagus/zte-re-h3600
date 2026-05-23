// module: mt7915.ko
// function: pci_get_pkt_pre_slab_ddone @ 0x1cd310
// size: 680 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int pci_get_pkt_pre_slab_ddone(int *param_1,byte *param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  undefined2 extraout_r1;
  undefined2 extraout_r1_00;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  byte bVar7;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c [2];
  
  iVar1 = hc_get_hif_ctrl(param_1[0x29e5e8]);
  iVar1 = *(int *)(*(int *)(iVar1 + 4) + param_4 * 4);
  local_2c[0] = 0;
  iVar4 = *(int *)(iVar1 + 0x18) + *(int *)(iVar1 + 0x10) * 0x24;
  puVar6 = *(undefined4 **)(iVar4 + 4);
  bVar7 = *(byte *)((int)puVar6 + 7) & 0x80;
  if ((*(byte *)((int)puVar6 + 7) & 0x80) == 0) {
    if (*(short *)(iVar1 + 0x30) == 0) {
      hif_io_read32(param_1[0x29e5e8],*(undefined4 *)(iVar1 + 8),iVar1 + 0xc);
      bVar7 = *(int *)(iVar1 + 0xc) != *(int *)(iVar1 + 0x10);
      if ((bool)bVar7) {
        DAT_005f48fc = DAT_005f48fc + 1;
      }
    }
    if (DAT_005f48fc < 10) {
      iVar5 = 0;
      goto LAB_001cd514;
    }
  }
  else {
    bVar7 = 0;
    DAT_005f48fc = 0;
  }
  iVar5 = FUN_001ca4e0(iVar1,puVar6,local_2c);
  if (iVar5 != 0) {
    iVar2 = RTMP_AllocateRxPacketBuffer
                      (iVar1,*(undefined4 *)(*param_1 + 0xc),*(undefined4 *)(iVar4 + 0x18),&local_34
                       ,&local_30);
    *(undefined2 *)(iVar1 + 0x2c) = 1;
    if (iVar2 != 0) {
      linux_pci_unmap_single
                (*(undefined4 *)(*param_1 + 0xc),*(undefined4 *)(iVar4 + 0x20),
                 *(undefined4 *)(iVar4 + 0x18),0xff01);
      if ((iVar5 != 1) &&
         (iVar5 = FUN_001ccd68(param_1,param_4,iVar4,puVar6,iVar5,local_2c[0]), iVar5 == 0)) {
        bVar7 = 1;
        __aeabi_idivmod(*(ushort *)(iVar1 + 0x22) + 1,*(undefined2 *)(iVar1 + 0x24));
        *(undefined2 *)(iVar1 + 0x22) = extraout_r1_00;
        iVar5 = 0;
        goto LAB_001cd514;
      }
      iVar5 = *(int *)(iVar4 + 0xc);
      *(undefined4 *)(iVar4 + 0x1c) = local_34;
      *(undefined4 *)(iVar4 + 0x20) = local_30;
      *(int *)(iVar4 + 0xc) = iVar2;
      *(uint *)(iVar4 + 0x18) = (uint)*(ushort *)(iVar1 + 0x2e);
      *puVar6 = local_30;
      *(undefined1 *)((int)puVar6 + 6) = *(undefined1 *)(iVar1 + 0x2e);
      *(byte *)((int)puVar6 + 7) =
           *(byte *)((int)puVar6 + 7) & 0xc0 | *(byte *)(iVar1 + 0x2f) & 0x3f;
      if ((9 < DAT_005f48fc) && (DAT_005f48fc = 0, iVar5 != 0)) {
        bVar7 = 1;
        iVar5 = 0;
        __aeabi_idivmod(*(ushort *)(iVar1 + 0x22) + 1,*(undefined2 *)(iVar1 + 0x24));
        *(undefined2 *)(iVar1 + 0x22) = extraout_r1;
      }
      *(byte *)((int)puVar6 + 7) = *(byte *)((int)puVar6 + 7) & 0x7f;
      DataSynchronizationBarrier(0xe);
      if (___aeabi_idivmod != (code *)0x0) {
        (*___aeabi_idivmod)();
      }
      iVar4 = *(int *)(iVar1 + 0x10);
      uVar3 = iVar4 + 1;
      *(uint *)(iVar1 + 0x10) = uVar3;
      if (uVar3 < *(ushort *)(iVar1 + 0x14)) {
        *(short *)(iVar1 + 0x30) = *(short *)(iVar1 + 0x30) + 1;
        if (uVar3 == 0) goto LAB_001cd53c;
      }
      else {
        *(undefined4 *)(iVar1 + 0x10) = 0;
        *(short *)(iVar1 + 0x30) = *(short *)(iVar1 + 0x30) + 1;
LAB_001cd53c:
        iVar4 = *(ushort *)(iVar1 + 0x14) - 1;
      }
      *(int *)(iVar1 + 0x34) = iVar4;
      goto LAB_001cd514;
    }
  }
  bVar7 = 1;
  iVar5 = 0;
LAB_001cd514:
  *param_2 = bVar7;
  return iVar5;
}

