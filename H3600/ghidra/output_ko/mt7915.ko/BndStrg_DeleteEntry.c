// module: mt7915.ko
// function: BndStrg_DeleteEntry @ 0x9c86c
// size: 68 bytes
//

undefined4 BndStrg_DeleteEntry(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  _raw_spin_lock_bh(param_1 + 0x1014);
  uVar1 = BndStrg_DeleteEntry_UnLock(param_1,param_2,param_3);
  _raw_spin_unlock_bh(param_1 + 0x1014);
  return uVar1;
}

