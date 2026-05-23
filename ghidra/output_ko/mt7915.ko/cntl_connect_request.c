// module: mt7915.ko
// function: cntl_connect_request @ 0x10d34c
// size: 308 bytes
//

undefined4 cntl_connect_request(int param_1,undefined4 param_2,size_t param_3,void *param_4)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *local_24;
  
  iVar3 = *(int *)(param_1 + 8);
  if (iVar3 == 0) {
    printk(&_LC17,0x18e);
    dump_stack();
    iVar3 = *(int *)(param_1 + 8);
  }
  os_alloc_mem(iVar3,&local_24,param_3 + 8);
  if (local_24 == (undefined4 *)0x0) {
    uVar2 = 0;
    if (-1 < DebugLevel) {
      printk("%s: Alloc memory failed.\n","cntl_connect_request");
    }
  }
  else {
    *local_24 = param_2;
    iVar1 = DebugLevel;
    *(char *)(local_24 + 1) = (char)param_3;
    if (1 < iVar1) {
      printk("%s,type=%d,len=%d\n","cntl_connect_request",param_2,param_3);
    }
    if (param_3 != 0 && param_4 != (void *)0x0) {
      os_move_mem((void *)((int)local_24 + 5),param_4,param_3);
    }
    MlmeEnqueueWithWdev(iVar3,5,0,param_3 + 8,local_24,0,param_1);
    RtmpOsMlmeUp(iVar3 + 0x286298);
    os_free_mem(local_24);
    uVar2 = 1;
  }
  return uVar2;
}

