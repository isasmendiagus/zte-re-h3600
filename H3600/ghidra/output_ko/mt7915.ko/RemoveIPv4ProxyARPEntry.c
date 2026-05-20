// module: mt7915.ko
// function: RemoveIPv4ProxyARPEntry @ 0x22616c
// size: 284 bytes
//

void RemoveIPv4ProxyARPEntry(undefined4 param_1,int param_2,void *param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  
  if (0 < DebugLevel) {
    printk(&_LC4,"RemoveIPv4ProxyARPEntry");
  }
  if (param_4 == 0) {
    _raw_spin_lock_bh(param_2 + 0x4ca0);
    piVar4 = *(int **)(param_2 + 0x4ca8);
    piVar1 = (int *)*piVar4;
    if (piVar4 == (int *)0x0 || piVar4 == (int *)(param_2 + 0x4ca8)) goto LAB_00226230;
  }
  else {
    piVar4 = *(int **)(param_2 + 0x4ca8);
    piVar1 = (int *)*piVar4;
    if (piVar4 == (int *)0x0 || piVar4 == (int *)(param_2 + 0x4ca8)) {
      return;
    }
  }
  do {
    piVar3 = piVar1;
    iVar2 = memcmp(piVar4 + 2,param_3,6);
    if (iVar2 == 0) {
      if (*piVar4 != 0) {
        *(int *)(*piVar4 + 4) = piVar4[1];
      }
      if ((int *)piVar4[1] != (int *)0x0) {
        *(int *)piVar4[1] = *piVar4;
      }
      *piVar4 = 0;
      piVar4[1] = 0;
      os_free_mem(piVar4);
      break;
    }
    piVar1 = (int *)*piVar3;
    piVar4 = piVar3;
  } while (piVar3 != (int *)(param_2 + 0x4ca8) && piVar3 != (int *)0x0);
  if (param_4 != 0) {
    return;
  }
LAB_00226230:
  _raw_spin_unlock_bh(param_2 + 0x4ca0);
  return;
}

