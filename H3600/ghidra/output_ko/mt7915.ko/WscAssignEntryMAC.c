// module: mt7915.ko
// function: WscAssignEntryMAC @ 0x1f28fc
// size: 88 bytes
//

void WscAssignEntryMAC(undefined4 param_1,int param_2)

{
  int iVar1;
  
  WscMaintainPeerList();
  _raw_spin_lock_bh(param_2 + 0x2c00);
  iVar1 = *(int *)(param_2 + 0x2c04);
  __memzero((void *)(param_2 + 0x1c55),6);
  if (iVar1 != 0) {
    memmove((void *)(param_2 + 0x1c55),(void *)(iVar1 + 8),6);
  }
  _raw_spin_unlock_bh(param_2 + 0x2c00);
  return;
}

