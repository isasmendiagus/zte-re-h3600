// module: mt7915.ko
// function: RTMPReportMicError @ 0x57310
// size: 268 bytes
//

void RTMPReportMicError(undefined4 param_1,int param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  undefined1 local_11;
  
  local_11 = *(char *)(param_3 + 0x48) == '\x01';
  if (param_2 == 0) {
    printk(&_LC0,0x50);
    dump_stack();
    return;
  }
  GetAssociatedAPByWdev();
  uVar1 = jiffies;
  if (*(int *)(param_2 + 0x2127b4) == 0) {
    *(uint *)(param_2 + 0x2127b0) = jiffies;
    *(undefined4 *)(param_2 + 0x2127b4) = 1;
    __memzero(param_2 + 0x2127ba,8);
  }
  else if ((*(int *)(param_2 + 0x2127b4) == 1) &&
          (iVar2 = *(int *)(param_2 + 0x2127b0), *(uint *)(param_2 + 0x2127b0) = jiffies,
          uVar1 <= iVar2 + 6000U)) {
    *(undefined4 *)(param_2 + 0x2127b4) = 2;
  }
  MlmeEnqueueWithWdev(param_1,5,0x528,1,&local_11,0,param_2);
  if (*(int *)(param_2 + 0x2127b4) != 2) {
    return;
  }
  RTMPSetTimer(param_2 + 0x2123a0,100);
  return;
}

