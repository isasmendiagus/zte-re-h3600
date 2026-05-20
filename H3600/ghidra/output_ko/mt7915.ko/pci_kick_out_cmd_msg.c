// module: mt7915.ko
// function: pci_kick_out_cmd_msg @ 0x1cb1dc
// size: 604 bytes
//

undefined4 pci_kick_out_cmd_msg(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  undefined4 local_44;
  int local_40;
  int local_3c;
  undefined1 auStack_38 [20];
  
  uVar7 = *(undefined4 *)(param_2 + 0x20);
  local_44 = 0;
  local_3c = 0;
  iVar2 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar6 = *(int *)(iVar2 + 0x88);
  iVar2 = OS_TEST_BIT(0,param_1 + 0xa784a0);
  if (iVar2 != 0) {
    iVar2 = FUN_001ca814(iVar6);
    if (iVar2 != 0) {
      iVar2 = iVar6 + 0x34;
      OS_SPIN_LOCK_IRQSAVE(iVar2,&local_44);
      RTMP_QueryPacketInfo(uVar7,auStack_38,&local_40,&local_3c);
      if (local_40 == 0) {
        OS_SPIN_UNLOCK_IRQRESTORE(iVar2,&local_44);
        return 1;
      }
      iVar3 = *(int *)(iVar6 + 0x28) * 0x24;
      iVar8 = *(int *)(iVar6 + 0xc) + iVar3;
      *(undefined4 *)(iVar8 + 0xc) = uVar7;
      puVar5 = *(undefined4 **)(iVar8 + 4);
      *(undefined4 *)(*(int *)(iVar6 + 0xc) + iVar3 + 0x10) = 0;
      iVar8 = *(int *)(iVar6 + 0xc);
      uVar7 = RtmpDrvPciMapSingle(param_1,local_40,local_3c,0,0xff00);
      *(undefined4 *)(iVar8 + iVar3 + 0x14) = uVar7;
      bVar1 = *(byte *)((int)puVar5 + 7);
      *(byte *)((int)puVar5 + 7) = bVar1 | 0x40;
      *(byte *)((int)puVar5 + 5) = *(byte *)((int)puVar5 + 5) & 0xbf;
      *(undefined1 *)(puVar5 + 1) = 0;
      *(char *)((int)puVar5 + 6) = (char)local_3c;
      *(byte *)((int)puVar5 + 7) = bVar1 & 0xc0 | 0x40 | (byte)((uint)(local_3c << 0x12) >> 0x1a);
      *(byte *)((int)puVar5 + 5) = *(byte *)((int)puVar5 + 5) & 0xc0;
      uVar7 = *(undefined4 *)(*(int *)(iVar6 + 0xc) + iVar3 + 0x14);
      *(byte *)((int)puVar5 + 5) = *(byte *)((int)puVar5 + 5) & 0x7f;
      *(byte *)((int)puVar5 + 7) = *(byte *)((int)puVar5 + 7) & 0x7f;
      *puVar5 = uVar7;
      uVar4 = *(int *)(iVar6 + 0x28) + 1;
      *(uint *)(iVar6 + 0x28) = uVar4;
      if (*(ushort *)(iVar6 + 0x5a) <= uVar4) {
        *(undefined4 *)(iVar6 + 0x28) = 0;
      }
      if ((*(byte *)(param_2 + 4) & 4) == 0) {
        AndesQueueTailCmdMsg(param_1 + 0xa784ec,param_2,5);
      }
      else {
        AndesQueueTailCmdMsg(param_1 + 0xa784d4,param_2,8);
        *(undefined4 *)(param_2 + 0x40) = jiffies;
      }
      iVar3 = OS_TEST_BIT(0,param_1 + 0xa784a0);
      if (iVar3 != 0) {
        hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),*(undefined4 *)(iVar6 + 0x24),
                       *(undefined4 *)(iVar6 + 0x28));
        OS_SPIN_UNLOCK_IRQRESTORE(iVar2,&local_44);
        return 0;
      }
      OS_SPIN_UNLOCK_IRQRESTORE(iVar2,&local_44);
      return 0xffffffff;
    }
    if (1 < DebugLevel) {
      printk("%s FreeNum == 0 (TxCpuIdx = %d, TxDmaIdx = %d, TxSwFreeIdx = %d)\n",
             "pci_kick_out_cmd_msg",*(undefined4 *)(iVar6 + 0x28),*(undefined4 *)(iVar6 + 8),
             *(undefined4 *)(iVar6 + 0x10));
    }
  }
  return 1;
}

