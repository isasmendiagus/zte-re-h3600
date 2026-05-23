// module: mt7915.ko
// function: pci_mac_fw_own_func @ 0x1cb5c0
// size: 72 bytes
//

void pci_mac_fw_own_func(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(*(int *)(param_1 + 0xd0) + 0xb0));
  uVar2 = _raw_spin_lock_irqsave(param_1 + 0xc0);
  mt_int_enable(uVar1,param_1,0x80000000);
  _raw_spin_unlock_irqrestore(param_1 + 0xc0,uVar2);
  return;
}

