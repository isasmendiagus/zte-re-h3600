// module: mt7915.ko
// function: GetIPv4ProxyARPTable @ 0x225db4
// size: 156 bytes
//

undefined4
GetIPv4ProxyARPTable(undefined4 param_1,int param_2,undefined4 *param_3,undefined4 param_4)

{
  int *piVar1;
  void *__dest;
  
  __dest = (void *)*param_3;
  if (0 < DebugLevel) {
    printk(&_LC4,"GetIPv4ProxyARPTable",param_3,DebugLevel,param_4);
  }
  _raw_spin_lock_bh(param_2 + 0x4ca0);
  for (piVar1 = *(int **)(param_2 + 0x4ca8); piVar1 != (int *)(param_2 + 0x4ca8);
      piVar1 = (int *)*piVar1) {
    memmove(__dest,piVar1 + 2,6);
    memmove((void *)((int)__dest + 6),(void *)((int)piVar1 + 0xe),4);
    __dest = (void *)((int)__dest + 10);
  }
  _raw_spin_unlock_bh(param_2 + 0x4ca0);
  return 1;
}

