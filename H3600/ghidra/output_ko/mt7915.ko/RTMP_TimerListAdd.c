// module: mt7915.ko
// function: RTMP_TimerListAdd @ 0x13c0c0
// size: 236 bytes
//

void RTMP_TimerListAdd(int param_1,int param_2)

{
  int iVar1;
  undefined4 *local_14;
  
  local_14 = *(undefined4 **)(param_1 + 0xa78490);
  if (local_14 == (undefined4 *)0x0) {
    local_14 = (undefined4 *)0x0;
  }
  else {
    do {
      if (local_14[1] == param_2) {
        return;
      }
      local_14 = (undefined4 *)*local_14;
    } while (local_14 != (undefined4 *)0x0);
  }
  os_alloc_mem(0,&local_14,8);
  if (local_14 == (undefined4 *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: alloc timer obj fail!\n","RTMP_TimerListAdd");
    }
  }
  else {
    local_14[1] = param_2;
    *local_14 = 0;
    if (*(undefined4 **)(param_1 + 0xa78494) == (undefined4 *)0x0) {
      *(undefined4 **)(param_1 + 0xa78490) = local_14;
    }
    else {
      **(undefined4 **)(param_1 + 0xa78494) = local_14;
    }
    *(undefined4 **)(param_1 + 0xa78494) = local_14;
    iVar1 = DebugLevel;
    *(char *)(param_1 + 0xa78498) = *(char *)(param_1 + 0xa78498) + '\x01';
    if (3 < iVar1) {
      printk("%s: add timer obj %lx!\n","RTMP_TimerListAdd",param_2);
    }
  }
  return;
}

