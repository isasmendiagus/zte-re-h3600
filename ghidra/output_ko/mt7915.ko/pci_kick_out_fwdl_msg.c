// module: mt7915.ko
// function: pci_kick_out_fwdl_msg @ 0x1caf54
// size: 644 bytes
//

undefined4 pci_kick_out_fwdl_msg(int param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  int *piVar9;
  undefined4 local_44;
  int local_40;
  int local_3c;
  undefined1 auStack_38 [20];
  
  uVar8 = *(undefined4 *)(param_2 + 0x20);
  local_44 = 0;
  local_3c = 0;
  iVar3 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar4 = OS_TEST_BIT(0,param_1 + 0xa784a0);
  if (iVar4 == 0) {
    uVar8 = 0xffffffff;
  }
  else {
    piVar6 = *(int **)(iVar3 + 0x8c);
    uVar5 = FUN_001ca814(piVar6);
    if (uVar5 < 10) {
      (**(code **)(iVar3 + *piVar6 * 4 + 0xc))(param_1,(char)piVar6[0x16]);
      iVar3 = FUN_001ca814(piVar6);
      if (iVar3 == 0) {
        if (1 < DebugLevel) {
          printk("%s FreeNum == 0 (TxCpuIdx = %d, TxDmaIdx = %d, TxSwFreeIdx = %d)\n",
                 "pci_kick_out_fwdl_msg",piVar6[10],piVar6[2],piVar6[4]);
          return 1;
        }
        return 1;
      }
    }
    piVar9 = piVar6 + 0xd;
    OS_SPIN_LOCK_IRQSAVE(piVar9,&local_44);
    RTMP_QueryPacketInfo(uVar8,auStack_38,&local_40,&local_3c);
    if (local_40 == 0) {
      OS_SPIN_UNLOCK_IRQRESTORE(piVar9,&local_44);
      uVar8 = 1;
    }
    else {
      iVar3 = piVar6[10] * 0x24;
      puVar7 = *(undefined4 **)(piVar6[3] + iVar3 + 4);
      *(undefined4 *)(piVar6[3] + iVar3 + 0xc) = uVar8;
      *(undefined4 *)(piVar6[3] + iVar3 + 0x10) = 0;
      iVar4 = piVar6[3];
      uVar8 = RtmpDrvPciMapSingle(param_1,local_40,local_3c,0,0xff00);
      *(undefined4 *)(iVar4 + iVar3 + 0x14) = uVar8;
      bVar1 = *(byte *)((int)puVar7 + 7);
      *(byte *)((int)puVar7 + 7) = bVar1 | 0x40;
      *(byte *)((int)puVar7 + 5) = *(byte *)((int)puVar7 + 5) & 0xbf;
      *(undefined1 *)(puVar7 + 1) = 0;
      *(char *)((int)puVar7 + 6) = (char)local_3c;
      bVar2 = (byte)((uint)(local_3c << 0x12) >> 0x1a);
      *(byte *)((int)puVar7 + 7) = bVar1 & 0xc0 | 0x40 | bVar2;
      *(byte *)((int)puVar7 + 5) = *(byte *)((int)puVar7 + 5) & 0xc0;
      uVar8 = *(undefined4 *)(piVar6[3] + iVar3 + 0x14);
      *(byte *)((int)puVar7 + 5) = *(byte *)((int)puVar7 + 5) & 0x7f;
      *(byte *)((int)puVar7 + 7) = bVar2 | 0x40;
      *puVar7 = uVar8;
      iVar3 = piVar6[10];
      piVar6[10] = iVar3 + 1U;
      if ((uint)*(ushort *)((int)piVar6 + 0x5a) <= iVar3 + 1U) {
        piVar6[10] = 0;
      }
      if ((*(byte *)(param_2 + 4) & 4) == 0) {
        iVar3 = param_1 + 0xa784ec;
        uVar8 = 5;
      }
      else {
        iVar3 = param_1 + 0xa784d4;
        uVar8 = 8;
      }
      AndesQueueTailCmdMsg(iVar3,param_2,uVar8);
      iVar3 = OS_TEST_BIT(0,param_1 + 0xa784a0);
      if (iVar3 == 0) {
        OS_SPIN_UNLOCK_IRQRESTORE(piVar9,&local_44);
        uVar8 = 0xffffffff;
      }
      else {
        hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),piVar6[9],piVar6[10]);
        OS_SPIN_UNLOCK_IRQRESTORE(piVar9,&local_44);
        uVar8 = 0;
      }
    }
  }
  return uVar8;
}

