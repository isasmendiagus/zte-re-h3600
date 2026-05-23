// module: mt7915.ko
// function: pci_get_pkt_dynamic_page_ddone @ 0x1cffec
// size: 812 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int pci_get_pkt_dynamic_page_ddone(int *param_1,byte *param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  byte bVar7;
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c [2];
  
  iVar1 = hc_get_hif_ctrl(param_1[0x29e5e8]);
  iVar1 = *(int *)(*(int *)(iVar1 + 4) + param_4 * 4);
  local_3c = 0;
  local_30 = 0;
  local_2c[0] = 0;
  iVar5 = *(int *)(iVar1 + 0x18) + *(int *)(iVar1 + 0x10) * 0x24;
  puVar6 = *(undefined4 **)(iVar5 + 4);
  bVar7 = *(byte *)((int)puVar6 + 7) & 0x80;
  if ((*(byte *)((int)puVar6 + 7) & 0x80) == 0) {
    if (*(short *)(iVar1 + 0x30) == 0) {
      hif_io_read32(param_1[0x29e5e8],*(undefined4 *)(iVar1 + 8),iVar1 + 0xc);
      bVar7 = *(int *)(iVar1 + 0xc) != *(int *)(iVar1 + 0x10);
      if ((bool)bVar7) {
        DAT_005f4910 = DAT_005f4910 + 1;
      }
    }
    if (DAT_005f4910 < 10) goto LAB_001d00b0;
  }
  else {
    bVar7 = 0;
    DAT_005f4910 = 0;
  }
  local_2c[0] = (*(int *)(iVar5 + 0x18) + 0x3fU & 0xffffffe0) + 0xc0;
  iVar2 = FUN_001ca4e0(iVar1,puVar6,&local_30);
  if ((iVar2 != 0) &&
     (iVar3 = RTMP_AllocateRxPacketBuffer
                        (iVar1,*(undefined4 *)(*param_1 + 0xc),*(undefined4 *)(iVar5 + 0x18),
                         &local_38,&local_34), iVar3 != 0)) {
    linux_pci_unmap_single
              (*(undefined4 *)(*param_1 + 0xc),*(undefined4 *)(iVar5 + 0x20),
               *(undefined4 *)(iVar5 + 0x18),0xff01);
    if ((iVar2 == 1) ||
       (iVar2 = FUN_001cf2b4(param_1,param_4,iVar5,puVar6,iVar2,local_30,local_2c), iVar2 != 0)) {
      if (*(int *)(iVar5 + 0xc) == 0) {
        local_3c = 0;
      }
      else {
        FUN_001cddc0(&local_3c,*(int *)(iVar5 + 0xc),local_2c[0],local_30);
      }
      *(undefined4 *)(iVar5 + 0x1c) = local_38;
      *(undefined4 *)(iVar5 + 0x20) = local_34;
      *(int *)(iVar5 + 0xc) = iVar3;
      *(uint *)(iVar5 + 0x18) = (uint)*(ushort *)(iVar1 + 0x2e);
      *puVar6 = local_34;
      *(undefined1 *)((int)puVar6 + 6) = *(undefined1 *)(iVar1 + 0x2e);
      *(byte *)((int)puVar6 + 7) =
           *(byte *)((int)puVar6 + 7) & 0xc0 | *(byte *)(iVar1 + 0x2f) & 0x3f;
      if (((param_1[0x28e7e1] & 4U) == 0) || (9 < DAT_005f4910)) {
        if (3 < DebugLevel) {
          printk("%s(): system is not ready, rx pkt drop it.\n","pci_get_pkt_dynamic_page_ddone");
        }
        DAT_005f4910 = 0;
        if (local_3c != 0) {
          bVar7 = 1;
          RTMPFreeNdisPacketIRQ(param_1);
          local_3c = 0;
        }
      }
      *(byte *)((int)puVar6 + 7) = *(byte *)((int)puVar6 + 7) & 0x7f;
      DataSynchronizationBarrier(0xe);
      if (___aeabi_idivmod != (code *)0x0) {
        (*___aeabi_idivmod)();
      }
      iVar5 = *(int *)(iVar1 + 0x10);
      uVar4 = iVar5 + 1;
      *(uint *)(iVar1 + 0x10) = uVar4;
      if (uVar4 < *(ushort *)(iVar1 + 0x14)) {
        *(short *)(iVar1 + 0x30) = *(short *)(iVar1 + 0x30) + 1;
        iVar2 = uVar4 * 0x24;
        if (uVar4 != 0) goto LAB_001d0250;
      }
      else {
        iVar2 = 0;
        *(undefined4 *)(iVar1 + 0x10) = 0;
        *(short *)(iVar1 + 0x30) = *(short *)(iVar1 + 0x30) + 1;
      }
      iVar5 = *(ushort *)(iVar1 + 0x14) - 1;
LAB_001d0250:
      *(int *)(iVar1 + 0x34) = iVar5;
      HintPreloadData(*(undefined4 *)(*(int *)(iVar1 + 0x18) + iVar2 + 0xc));
      *param_2 = bVar7;
      return local_3c;
    }
    RTMPFreeNdisPacketIRQ(param_1,iVar3);
  }
  bVar7 = 1;
LAB_001d00b0:
  *param_2 = bVar7;
  return local_3c;
}

