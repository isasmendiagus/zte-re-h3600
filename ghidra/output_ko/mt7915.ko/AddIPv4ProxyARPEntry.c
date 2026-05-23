// module: mt7915.ko
// function: AddIPv4ProxyARPEntry @ 0x225efc
// size: 620 bytes
//

undefined4
AddIPv4ProxyARPEntry(undefined4 param_1,int param_2,void *param_3,char *param_4,int param_5)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  char *pcVar6;
  int *local_2c [2];
  
  if (0 < DebugLevel) {
    printk(&_LC4,"AddIPv4ProxyARPEntry");
  }
  if ((*param_4 == '\0') && (param_4[1] == '\0')) {
    if (-1 < DebugLevel) {
      printk("Drop invalid IP Addr:%d.%d.%d.%d\n",0,0,param_4[2],param_4[3]);
      return 0;
    }
    return 0;
  }
  if (param_5 == 0) {
    _raw_spin_lock_bh(param_2 + 0x4ca0);
    local_2c[0] = *(int **)(param_2 + 0x4ca8);
    if (local_2c[0] != (int *)(param_2 + 0x4ca8)) goto LAB_00225f7c;
  }
  else {
    local_2c[0] = *(int **)(param_2 + 0x4ca8);
    if (local_2c[0] == (int *)(param_2 + 0x4ca8)) goto LAB_00226058;
LAB_00225f7c:
    do {
      piVar4 = local_2c[0];
      iVar2 = memcmp(local_2c[0] + 2,param_3,6);
      if (iVar2 == 0) {
        if (param_5 == 0) {
          _raw_spin_unlock_bh(param_2 + 0x4ca0);
        }
        bVar1 = true;
        piVar4 = local_2c[0];
        goto joined_r0x00225fa8;
      }
      local_2c[0] = (int *)*piVar4;
    } while (local_2c[0] != (int *)(param_2 + 0x4ca8));
    if (param_5 != 0) goto LAB_00226058;
  }
  _raw_spin_unlock_bh(param_2 + 0x4ca0);
LAB_00226058:
  bVar1 = false;
  os_alloc_mem(0,local_2c,0x14);
  piVar4 = local_2c[0];
joined_r0x00225fa8:
  local_2c[0] = piVar4;
  if (piVar4 == (int *)0x0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s Not available memory\n","AddIPv4ProxyARPEntry");
    uVar3 = 0;
  }
  else {
    pcVar6 = param_4 + -1;
    memmove(piVar4 + 2,param_3,6);
    memmove((void *)((int)piVar4 + 0xe),param_4,4);
    iVar2 = 0;
    do {
      iVar5 = iVar2 + 1;
      pcVar6 = pcVar6 + 1;
      printk("pTargetIPv4Addr[%i] = %d\n",iVar2,*pcVar6);
      iVar2 = iVar5;
    } while (iVar5 != 4);
    if (bVar1) {
      uVar3 = 1;
    }
    else if (param_5 == 0) {
      _raw_spin_lock_bh(param_2 + 0x4ca0);
      piVar4 = *(int **)(param_2 + 0x4cac);
      *local_2c[0] = *piVar4;
      local_2c[0][1] = (int)piVar4;
      *(int **)(*piVar4 + 4) = local_2c[0];
      *piVar4 = (int)local_2c[0];
      _raw_spin_unlock_bh(param_2 + 0x4ca0);
      uVar3 = 1;
    }
    else {
      piVar4 = *(int **)(param_2 + 0x4cac);
      uVar3 = 1;
      *local_2c[0] = *piVar4;
      local_2c[0][1] = (int)piVar4;
      *(int **)(*piVar4 + 4) = local_2c[0];
      *piVar4 = (int)local_2c[0];
    }
  }
  return uVar3;
}

