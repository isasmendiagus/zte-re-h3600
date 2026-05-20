// module: mt7915.ko
// function: pci_get_pkt_pre_slab_io @ 0x1cd08c
// size: 644 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint pci_get_pkt_pre_slab_io(int *param_1,undefined1 *param_2,uint *param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined2 extraout_r1;
  uint uVar4;
  uint uVar5;
  undefined1 uVar6;
  int iVar7;
  uint uVar8;
  undefined4 *puVar9;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c [2];
  
  iVar1 = hc_get_hif_ctrl(param_1[0x29e5e8]);
  iVar1 = *(int *)(*(int *)(iVar1 + 4) + param_4 * 4);
  local_2c[0] = 0;
  uVar8 = (uint)*(ushort *)(iVar1 + 0x14);
  if (*param_3 == 0) {
    hif_io_read32(param_1[0x29e5e8],*(undefined4 *)(iVar1 + 8),iVar1 + 0xc);
    uVar5 = *(uint *)(iVar1 + 0xc);
    uVar4 = *(uint *)(iVar1 + 0x10);
    if (uVar5 == uVar4) {
      uVar6 = 0;
      uVar5 = 0;
      goto LAB_001cd118;
    }
    if (uVar5 < uVar4) {
      iVar7 = uVar8 - uVar4;
    }
    else {
      iVar7 = -uVar4;
    }
    *param_3 = uVar5 + iVar7;
  }
  iVar7 = *(int *)(iVar1 + 0x18) + *(int *)(iVar1 + 0x10) * 0x24;
  puVar9 = *(undefined4 **)(iVar7 + 4);
  uVar5 = *(byte *)((int)puVar9 + 7) & 0xffffff80;
  if ((*(byte *)((int)puVar9 + 7) & 0x80) == 0) {
    *param_3 = uVar5;
    if (3 < DebugLevel) {
      uVar6 = 1;
      printk("DDONE=0!\n");
      goto LAB_001cd118;
    }
  }
  else {
    iVar2 = FUN_001ca5b0(iVar1,puVar9,local_2c);
    if (iVar2 != 0) {
      iVar3 = RTMP_AllocateRxPacketBuffer
                        (iVar1,*(undefined4 *)(*param_1 + 0xc),*(undefined4 *)(iVar7 + 0x18),
                         &local_34,&local_30);
      *(undefined2 *)(iVar1 + 0x2c) = 1;
      if (iVar3 != 0) {
        linux_pci_unmap_single
                  (*(undefined4 *)(*param_1 + 0xc),*(undefined4 *)(iVar7 + 0x20),
                   *(undefined4 *)(iVar7 + 0x18),0xff01);
        if ((iVar2 != 1) &&
           (iVar2 = FUN_001ccd68(param_1,param_4,iVar7,puVar9,iVar2,local_2c[0]), iVar2 == 0)) {
          uVar6 = 1;
          __aeabi_idivmod(*(ushort *)(iVar1 + 0x22) + 1,*(undefined2 *)(iVar1 + 0x24));
          *(undefined2 *)(iVar1 + 0x22) = extraout_r1;
          uVar5 = 0;
          goto LAB_001cd118;
        }
        uVar5 = *(uint *)(iVar7 + 0xc);
        *(undefined4 *)(iVar7 + 0x1c) = local_34;
        *(undefined4 *)(iVar7 + 0x20) = local_30;
        *(int *)(iVar7 + 0xc) = iVar3;
        *(uint *)(iVar7 + 0x18) = (uint)*(ushort *)(iVar1 + 0x2e);
        *puVar9 = local_30;
        *(undefined1 *)((int)puVar9 + 6) = *(undefined1 *)(iVar1 + 0x2e);
        *(byte *)((int)puVar9 + 7) =
             *(byte *)((int)puVar9 + 7) & 0xc0 | *(byte *)(iVar1 + 0x2f) & 0x3f;
        *param_3 = *param_3 - 1;
        *(byte *)((int)puVar9 + 7) = *(byte *)((int)puVar9 + 7) & 0x7f;
        DataSynchronizationBarrier(0xe);
        if (___aeabi_idivmod != (code *)0x0) {
          (*___aeabi_idivmod)();
        }
        iVar7 = *(int *)(iVar1 + 0x10);
        uVar4 = iVar7 + 1;
        if (uVar4 < uVar8) {
          *(uint *)(iVar1 + 0x10) = uVar4;
          *(short *)(iVar1 + 0x30) = *(short *)(iVar1 + 0x30) + 1;
          if (uVar4 != 0) goto LAB_001cd2b8;
        }
        else {
          *(undefined4 *)(iVar1 + 0x10) = 0;
          *(short *)(iVar1 + 0x30) = *(short *)(iVar1 + 0x30) + 1;
        }
        iVar7 = uVar8 - 1;
LAB_001cd2b8:
        *(int *)(iVar1 + 0x34) = iVar7;
        *param_2 = 0;
        return uVar5;
      }
    }
  }
  uVar6 = 1;
  uVar5 = 0;
LAB_001cd118:
  *param_2 = uVar6;
  return uVar5;
}

