// module: mt7915.ko
// function: ba_reordering_resource_init @ 0xa56a0
// size: 296 bytes
//

undefined4 ba_reordering_resource_init(int param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *local_2c [2];
  
  puVar1 = (undefined4 *)(param_1 + 0x2f5c8);
  do {
    *puVar1 = 0;
    _raw_spin_lock_bh(puVar1);
    puVar1[1] = 0;
    puVar1[3] = 0;
    if (2 < DebugLevel) {
      printk("Allocate %d memory for BA reordering\n",param_2 * 0x1c);
    }
    os_alloc_mem(param_1,local_2c,param_2 * 0x1c);
    puVar1[-1] = local_2c[0];
    if (local_2c[0] == (undefined4 *)0x0) {
      if (-1 < DebugLevel) {
        printk("Can\'t Allocate Memory for BA Reordering\n");
      }
      _raw_spin_unlock_bh(puVar1);
      return 0;
    }
    if (0 < param_2) {
      iVar3 = 0;
      do {
        puVar2 = local_2c[0];
        __memzero(local_2c[0],0x1c);
        iVar3 = iVar3 + 1;
        puVar1[3] = puVar1[3] + 1;
        local_2c[0] = local_2c[0] + 7;
        *puVar2 = puVar1[1];
        puVar1[1] = puVar2;
      } while (iVar3 != param_2);
    }
    puVar2 = puVar1 + 5;
    _raw_spin_unlock_bh(puVar1);
    puVar1 = puVar2;
  } while (puVar2 != (undefined4 *)(param_1 + 0x2f5f0));
  return 1;
}

