// module: mt7915.ko
// function: RemoveIPv6ProxyARPEntry @ 0x2265bc
// size: 220 bytes
//

void RemoveIPv6ProxyARPEntry(undefined4 param_1,int param_2,void *param_3)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  bool bVar4;
  bool bVar5;
  
  if (0 < DebugLevel) {
    printk(&_LC4,"RemoveIPv6ProxyARPEntry");
  }
  _raw_spin_lock_bh(param_2 + 0x4ca4);
  piVar2 = *(int **)(param_2 + 0x4cb0);
  piVar3 = (int *)*piVar2;
  if (piVar2 != (int *)0x0 && piVar2 != (int *)(param_2 + 0x4cb0)) {
    do {
      iVar1 = memcmp(piVar2 + 2,param_3,6);
      if (iVar1 == 0) {
        if (*piVar2 != 0) {
          *(int *)(*piVar2 + 4) = piVar2[1];
        }
        if ((int *)piVar2[1] != (int *)0x0) {
          *(int *)piVar2[1] = *piVar2;
        }
        *piVar2 = 0;
        piVar2[1] = 0;
        os_free_mem(piVar2);
      }
      bVar4 = piVar3 != (int *)(param_2 + 0x4cb0);
      bVar5 = piVar3 != (int *)0x0;
      piVar2 = piVar3;
      piVar3 = (int *)*piVar3;
    } while (bVar4 && bVar5);
  }
  _raw_spin_unlock_bh(param_2 + 0x4ca4);
  return;
}

