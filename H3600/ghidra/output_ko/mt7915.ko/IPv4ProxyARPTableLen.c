// module: mt7915.ko
// function: IPv4ProxyARPTableLen @ 0x225ce0
// size: 124 bytes
//

int IPv4ProxyARPTableLen(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  int iVar2;
  
  if (0 < DebugLevel) {
    printk(&_LC4,"IPv4ProxyARPTableLen",param_3,DebugLevel,param_4);
  }
  _raw_spin_lock_bh(param_2 + 0x4ca0);
  iVar2 = 0;
  for (piVar1 = *(int **)(param_2 + 0x4ca8); piVar1 != (int *)(param_2 + 0x4ca8);
      piVar1 = (int *)*piVar1) {
    iVar2 = iVar2 + 10;
  }
  _raw_spin_unlock_bh(param_2 + 0x4ca0);
  return iVar2;
}

