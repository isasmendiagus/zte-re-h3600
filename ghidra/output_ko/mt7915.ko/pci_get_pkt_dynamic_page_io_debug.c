// module: mt7915.ko
// function: pci_get_pkt_dynamic_page_io_debug @ 0x1cf578
// size: 984 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int pci_get_pkt_dynamic_page_io_debug(int *param_1,undefined1 *param_2,uint *param_3,int param_4)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined1 uVar7;
  int iVar8;
  undefined4 *puVar9;
  uint uVar10;
  bool bVar11;
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c [2];
  
  iVar2 = hc_get_hif_ctrl(param_1[0x29e5e8]);
  iVar2 = *(int *)(*(int *)(iVar2 + 4) + param_4 * 4);
  local_3c = 0;
  local_30 = 0;
  uVar10 = (uint)*(ushort *)(iVar2 + 0x14);
  local_2c[0] = 0;
  if (*param_3 == 0) {
    hif_io_read32(param_1[0x29e5e8],*(undefined4 *)(iVar2 + 8),iVar2 + 0xc);
    uVar6 = *(uint *)(iVar2 + 0xc);
    uVar5 = *(uint *)(iVar2 + 0x10);
    if (uVar6 == uVar5) {
      uVar7 = 0;
      goto LAB_001cf608;
    }
    if (uVar5 < uVar6) {
      iVar8 = -uVar5;
    }
    else {
      iVar8 = uVar10 - uVar5;
    }
    *param_3 = uVar6 + iVar8;
  }
  iVar8 = *(int *)(iVar2 + 0x18) + *(int *)(iVar2 + 0x10) * 0x24;
  puVar9 = *(undefined4 **)(iVar8 + 4);
  if ((*(byte *)((int)puVar9 + 7) & 0x80) == 0) {
    *param_3 = *(byte *)((int)puVar9 + 7) & 0xffffff80;
    if (3 < DebugLevel) {
      uVar7 = 1;
      printk("DDONE=0!\n");
      goto LAB_001cf608;
    }
  }
  else {
    local_2c[0] = (*(int *)(iVar8 + 0x18) + 0x3fU & 0xffffffe0) + 0xc0;
    iVar3 = FUN_001ca5b0(iVar2,puVar9,&local_30);
    if ((iVar3 != 0) &&
       (iVar4 = RTMP_AllocateRxPacketBuffer
                          (iVar2,*(undefined4 *)(*param_1 + 0xc),*(undefined4 *)(iVar8 + 0x18),
                           &local_38,&local_34), iVar4 != 0)) {
      linux_pci_unmap_single
                (*(undefined4 *)(*param_1 + 0xc),*(undefined4 *)(iVar8 + 0x20),
                 *(undefined4 *)(iVar8 + 0x18),0xff01);
      if ((iVar3 == 1) ||
         (iVar3 = FUN_001cf2b4(param_1,param_4,iVar8,puVar9,iVar3,local_30,local_2c), iVar3 != 0)) {
        if (*(int *)(iVar8 + 0xc) == 0) {
          local_3c = 0;
        }
        else {
          FUN_001cddc0(&local_3c,*(int *)(iVar8 + 0xc),local_2c[0],local_30);
          if ((local_3c != 0) &&
             (iVar3 = FUN_001cf00c(param_1,iVar8,puVar9,param_4,local_3c), iVar3 == 1)) {
            RTMPFreeNdisPacketIRQ(param_1,local_3c);
            local_3c = 0;
          }
        }
        *(undefined4 *)(iVar8 + 0x1c) = local_38;
        *(undefined4 *)(iVar8 + 0x20) = local_34;
        *(int *)(iVar8 + 0xc) = iVar4;
        *(uint *)(iVar8 + 0x18) = (uint)*(ushort *)(iVar2 + 0x2e);
        *puVar9 = local_34;
        *(undefined1 *)((int)puVar9 + 6) = *(undefined1 *)(iVar2 + 0x2e);
        *(byte *)((int)puVar9 + 7) =
             *(byte *)((int)puVar9 + 7) & 0xc0 | *(byte *)(iVar2 + 0x2f) & 0x3f;
        if ((param_1[0x28e7e1] & 4U) == 0) {
          if (3 < DebugLevel) {
            printk("%s(): system is not ready, rx pkt drop it.\n",
                   "pci_get_pkt_dynamic_page_io_debug");
          }
          if (local_3c == 0) goto LAB_001cf7b4;
          uVar7 = 1;
          RTMPFreeNdisPacketIRQ(param_1);
          local_3c = 0;
        }
        else {
LAB_001cf7b4:
          uVar7 = 0;
        }
        *param_3 = *param_3 - 1;
        *(undefined1 *)(puVar9 + 1) = 0;
        *(undefined1 *)((int)puVar9 + 5) = 0;
        uVar1 = *(ushort *)(iVar2 + 0x10);
        *(char *)(puVar9 + 2) = (char)uVar1;
        *(byte *)((int)puVar9 + 9) =
             *(byte *)((int)puVar9 + 9) & 0xf0 | (byte)(((uint)uVar1 << 0x14) >> 0x1c);
        iVar8 = *(int *)(iVar2 + 0x10);
        uVar6 = iVar8 + 1;
        if (uVar6 < uVar10) {
          *(uint *)(iVar2 + 0x10) = uVar6;
          *(short *)(iVar2 + 0x30) = *(short *)(iVar2 + 0x30) + 1;
          if (uVar6 == 0) goto LAB_001cf904;
          *(int *)(iVar2 + 0x34) = iVar8;
        }
        else {
          *(undefined4 *)(iVar2 + 0x10) = 0;
          *(short *)(iVar2 + 0x30) = *(short *)(iVar2 + 0x30) + 1;
LAB_001cf904:
          *(uint *)(iVar2 + 0x34) = uVar10 - 1;
          bVar11 = 0xfffffffe < DAT_005f4900;
          DAT_005f4900 = DAT_005f4900 + 1;
          DAT_005f4904 = DAT_005f4904 + (uint)bVar11;
        }
        uVar10 = DAT_005f4900 & 0xf;
        iVar8 = DAT_005f4900 << 0xc;
        *(char *)((int)puVar9 + 10) = (char)((DAT_005f4900 << 0x14) >> 0x18);
        *(byte *)((int)puVar9 + 9) = *(byte *)((int)puVar9 + 9) & 0xf | (byte)(uVar10 << 4);
        *(byte *)((int)puVar9 + 7) = *(byte *)((int)puVar9 + 7) & 0x7f;
        *(char *)((int)puVar9 + 0xb) = (char)((uint)iVar8 >> 0x18);
        DataSynchronizationBarrier(0xe);
        if (___aeabi_idivmod != (code *)0x0) {
          (*___aeabi_idivmod)();
        }
        if (*param_3 != 0) {
          HintPreloadData(*(undefined4 *)
                           (*(int *)(iVar2 + 0x18) + *(int *)(iVar2 + 0x10) * 0x24 + 0xc));
        }
        goto LAB_001cf608;
      }
      RTMPFreeNdisPacketIRQ(param_1,iVar4);
    }
  }
  uVar7 = 1;
LAB_001cf608:
  *param_2 = uVar7;
  return local_3c;
}

