// module: mt7915.ko
// function: pci_mac_recovery_func @ 0x1cbf04
// size: 224 bytes
//

void pci_mac_recovery_func(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 local_24 [2];
  
  iVar2 = param_1 + 0xc0;
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(*(int *)(param_1 + 0xd0) + 0xb0));
  uVar5 = *(uint *)("Get_RBIST_IQ_Data_Proc" + iVar1 + 0xc) & 0xffff;
  if (uVar5 == 0x7915 || (uVar5 == 0x7663 || uVar5 == 0x6867)) {
    uVar5 = 0xdfffffff;
    uVar3 = 0x20000000;
  }
  else {
    uVar5 = 0xbfffffff;
    uVar3 = 0x40000000;
  }
  OS_SPIN_LOCK_IRQSAVE(iVar2,local_24);
  uVar4 = *(undefined4 *)(iVar1 + 0xa7bf08);
  *(undefined4 *)(iVar1 + 0xa7bf08) = 0;
  OS_SPIN_UNLOCK_IRQRESTORE(iVar2,local_24);
  RTMP_MAC_RECOVERY(iVar1,uVar4);
  local_24[0] = _raw_spin_lock_irqsave(iVar2);
  *(uint *)(param_1 + 0xc) = uVar5 & *(uint *)(param_1 + 0xc);
  mt_int_enable(iVar1,param_1,uVar3);
  _raw_spin_unlock_irqrestore(iVar2,local_24[0]);
  return;
}

