// module: mt7915.ko
// function: pci_get_pkt_dynamic_slab_io @ 0x1cd850
// size: 760 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint pci_get_pkt_dynamic_slab_io(int *param_1,undefined1 *param_2,uint *param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined1 uVar9;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c [2];
  
  iVar1 = hc_get_hif_ctrl(param_1[0x29e5e8]);
  iVar1 = *(int *)(*(int *)(iVar1 + 4) + param_4 * 4);
  local_2c[0] = 0;
  uVar4 = (uint)*(ushort *)(iVar1 + 0x14);
  if (*param_3 == 0) {
    hif_io_read32(param_1[0x29e5e8],*(undefined4 *)(iVar1 + 8),iVar1 + 0xc);
    uVar5 = *(uint *)(iVar1 + 0xc);
    uVar6 = *(uint *)(iVar1 + 0x10);
    if (uVar5 == uVar6) {
      uVar5 = 0;
      uVar9 = 0;
      goto LAB_001cd8e0;
    }
    if (uVar5 < uVar6) {
      iVar7 = uVar4 - uVar6;
    }
    else {
      iVar7 = -uVar6;
    }
    *param_3 = uVar5 + iVar7;
  }
  iVar7 = *(int *)(iVar1 + 0x18) + *(int *)(iVar1 + 0x10) * 0x24;
  puVar8 = *(undefined4 **)(iVar7 + 4);
  uVar5 = *(byte *)((int)puVar8 + 7) & 0xffffff80;
  if ((*(byte *)((int)puVar8 + 7) & 0x80) == 0) {
    *param_3 = uVar5;
    if (3 < DebugLevel) {
      uVar9 = 1;
      printk("DDONE=0!\n");
      goto LAB_001cd8e0;
    }
  }
  else {
    iVar2 = FUN_001ca5b0(iVar1,puVar8,local_2c);
    if ((iVar2 != 0) &&
       (iVar3 = RTMP_AllocateRxPacketBuffer
                          (iVar1,*(undefined4 *)(*param_1 + 0xc),*(undefined4 *)(iVar7 + 0x18),
                           &local_34,&local_30), iVar3 != 0)) {
      linux_pci_unmap_single
                (*(undefined4 *)(*param_1 + 0xc),*(undefined4 *)(iVar7 + 0x20),
                 *(undefined4 *)(iVar7 + 0x18),0xff01);
      if ((iVar2 != 1) &&
         (iVar2 = FUN_001cd5b8(param_1,param_4,iVar7,puVar8,iVar2,local_2c[0]), iVar2 == 0)) {
        RTMPFreeNdisPacketIRQ(param_1,iVar3);
        uVar9 = 1;
        uVar5 = 0;
        goto LAB_001cd8e0;
      }
      uVar5 = *(uint *)(iVar7 + 0xc);
      *(undefined4 *)(iVar7 + 0x1c) = local_34;
      *(undefined4 *)(iVar7 + 0x20) = local_30;
      *(int *)(iVar7 + 0xc) = iVar3;
      *(uint *)(iVar7 + 0x18) = (uint)*(ushort *)(iVar1 + 0x2e);
      *puVar8 = local_30;
      *(undefined1 *)((int)puVar8 + 6) = *(undefined1 *)(iVar1 + 0x2e);
      *(byte *)((int)puVar8 + 7) =
           *(byte *)((int)puVar8 + 7) & 0xc0 | *(byte *)(iVar1 + 0x2f) & 0x3f;
      if ((param_1[0x28e7e1] & 4U) == 0) {
        if (3 < DebugLevel) {
          printk("%s(): system is not ready, rx pkt drop it.\n","pci_get_pkt_dynamic_slab_io");
        }
        if (uVar5 == 0) {
          uVar9 = 0;
        }
        else {
          RTMPFreeNdisPacketIRQ(param_1,uVar5);
          uVar9 = 1;
          uVar5 = 0;
        }
      }
      else {
        uVar9 = 0;
      }
      *param_3 = *param_3 - 1;
      *(byte *)((int)puVar8 + 7) = *(byte *)((int)puVar8 + 7) & 0x7f;
      DataSynchronizationBarrier(0xe);
      if (___aeabi_idivmod != (code *)0x0) {
        (*___aeabi_idivmod)();
      }
      iVar7 = *(int *)(iVar1 + 0x10);
      uVar6 = iVar7 + 1;
      if (uVar6 < uVar4) {
        *(uint *)(iVar1 + 0x10) = uVar6;
        *(short *)(iVar1 + 0x30) = *(short *)(iVar1 + 0x30) + 1;
        if (uVar6 == 0) goto LAB_001cdaf0;
      }
      else {
        *(undefined4 *)(iVar1 + 0x10) = 0;
        *(short *)(iVar1 + 0x30) = *(short *)(iVar1 + 0x30) + 1;
LAB_001cdaf0:
        iVar7 = uVar4 - 1;
        uVar6 = 0;
      }
      *(int *)(iVar1 + 0x34) = iVar7;
      if (*param_3 != 0) {
        HintPreloadData(*(undefined4 *)(*(int *)(iVar1 + 0x18) + uVar6 * 0x24 + 0xc));
        *param_2 = uVar9;
        return uVar5;
      }
      goto LAB_001cd8e0;
    }
  }
  uVar9 = 1;
  uVar5 = 0;
LAB_001cd8e0:
  *param_2 = uVar9;
  return uVar5;
}

