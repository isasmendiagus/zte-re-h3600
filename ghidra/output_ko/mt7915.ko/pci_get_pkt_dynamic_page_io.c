// module: mt7915.ko
// function: pci_get_pkt_dynamic_page_io @ 0x1cfcd0
// size: 792 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int pci_get_pkt_dynamic_page_io(int *param_1,undefined1 *param_2,uint *param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined1 uVar6;
  int iVar7;
  undefined4 *puVar8;
  uint uVar9;
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c [2];
  
  iVar1 = hc_get_hif_ctrl(param_1[0x29e5e8]);
  iVar1 = *(int *)(*(int *)(iVar1 + 4) + param_4 * 4);
  local_3c = 0;
  local_30 = 0;
  uVar9 = (uint)*(ushort *)(iVar1 + 0x14);
  local_2c[0] = 0;
  if (*param_3 == 0) {
    hif_io_read32(param_1[0x29e5e8],*(undefined4 *)(iVar1 + 8),iVar1 + 0xc);
    uVar5 = *(uint *)(iVar1 + 0xc);
    uVar4 = *(uint *)(iVar1 + 0x10);
    if (uVar5 == uVar4) {
      uVar6 = 0;
      goto LAB_001cfd60;
    }
    if (uVar4 < uVar5) {
      iVar7 = -uVar4;
    }
    else {
      iVar7 = uVar9 - uVar4;
    }
    *param_3 = uVar5 + iVar7;
  }
  iVar7 = *(int *)(iVar1 + 0x18) + *(int *)(iVar1 + 0x10) * 0x24;
  puVar8 = *(undefined4 **)(iVar7 + 4);
  if ((*(byte *)((int)puVar8 + 7) & 0x80) == 0) {
    *param_3 = *(byte *)((int)puVar8 + 7) & 0xffffff80;
    if (3 < DebugLevel) {
      uVar6 = 1;
      printk("DDONE=0!\n");
      goto LAB_001cfd60;
    }
  }
  else {
    local_2c[0] = (*(int *)(iVar7 + 0x18) + 0x3fU & 0xffffffe0) + 0xc0;
    iVar2 = FUN_001ca5b0(iVar1,puVar8,&local_30);
    if ((iVar2 != 0) &&
       (iVar3 = RTMP_AllocateRxPacketBuffer
                          (iVar1,*(undefined4 *)(*param_1 + 0xc),*(undefined4 *)(iVar7 + 0x18),
                           &local_38,&local_34), iVar3 != 0)) {
      linux_pci_unmap_single
                (*(undefined4 *)(*param_1 + 0xc),*(undefined4 *)(iVar7 + 0x20),
                 *(undefined4 *)(iVar7 + 0x18),0xff01);
      if ((iVar2 == 1) ||
         (iVar2 = FUN_001cf2b4(param_1,param_4,iVar7,puVar8,iVar2,local_30,local_2c), iVar2 != 0)) {
        if (*(int *)(iVar7 + 0xc) == 0) {
          local_3c = 0;
        }
        else {
          FUN_001cddc0(&local_3c,*(int *)(iVar7 + 0xc),local_2c[0],local_30);
        }
        *(undefined4 *)(iVar7 + 0x1c) = local_38;
        *(undefined4 *)(iVar7 + 0x20) = local_34;
        *(int *)(iVar7 + 0xc) = iVar3;
        *(uint *)(iVar7 + 0x18) = (uint)*(ushort *)(iVar1 + 0x2e);
        *puVar8 = local_34;
        *(undefined1 *)((int)puVar8 + 6) = *(undefined1 *)(iVar1 + 0x2e);
        *(byte *)((int)puVar8 + 7) =
             *(byte *)((int)puVar8 + 7) & 0xc0 | *(byte *)(iVar1 + 0x2f) & 0x3f;
        if ((param_1[0x28e7e1] & 4U) == 0) {
          if (3 < DebugLevel) {
            printk("%s(): system is not ready, rx pkt drop it.\n","pci_get_pkt_dynamic_page_io");
          }
          if (local_3c == 0) goto LAB_001cfee0;
          uVar6 = 1;
          RTMPFreeNdisPacketIRQ(param_1);
          local_3c = 0;
        }
        else {
LAB_001cfee0:
          uVar6 = 0;
        }
        *param_3 = *param_3 - 1;
        *(byte *)((int)puVar8 + 7) = *(byte *)((int)puVar8 + 7) & 0x7f;
        DataSynchronizationBarrier(0xe);
        if (___aeabi_idivmod != (code *)0x0) {
          (*___aeabi_idivmod)();
        }
        iVar7 = *(int *)(iVar1 + 0x10);
        uVar5 = iVar7 + 1;
        if (uVar5 < uVar9) {
          *(uint *)(iVar1 + 0x10) = uVar5;
          *(short *)(iVar1 + 0x30) = *(short *)(iVar1 + 0x30) + 1;
          if (uVar5 == 0) goto LAB_001cffb4;
        }
        else {
          *(undefined4 *)(iVar1 + 0x10) = 0;
          *(short *)(iVar1 + 0x30) = *(short *)(iVar1 + 0x30) + 1;
LAB_001cffb4:
          iVar7 = uVar9 - 1;
          uVar5 = 0;
        }
        *(int *)(iVar1 + 0x34) = iVar7;
        if (*param_3 != 0) {
          HintPreloadData(*(undefined4 *)(*(int *)(iVar1 + 0x18) + uVar5 * 0x24 + 0xc));
        }
        goto LAB_001cfd60;
      }
      RTMPFreeNdisPacketIRQ(param_1,iVar3);
    }
  }
  uVar6 = 1;
LAB_001cfd60:
  *param_2 = uVar6;
  return local_3c;
}

