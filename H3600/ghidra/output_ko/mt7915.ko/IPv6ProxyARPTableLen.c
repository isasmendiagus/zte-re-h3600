// module: mt7915.ko
// function: IPv6ProxyARPTableLen @ 0x225d60
// size: 84 bytes
//

int IPv6ProxyARPTableLen(undefined4 param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  _raw_spin_lock_bh(param_2 + 0x4ca4);
  iVar2 = 0;
  for (piVar1 = *(int **)(param_2 + 0x4cb0); piVar1 != (int *)(param_2 + 0x4cb0);
      piVar1 = (int *)*piVar1) {
    iVar2 = iVar2 + 0x17;
  }
  _raw_spin_unlock_bh(param_2 + 0x4ca4);
  return iVar2;
}

