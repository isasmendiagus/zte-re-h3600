// module: mt7915.ko
// function: cntl_auth_assoc_conf @ 0x10d754
// size: 160 bytes
//

bool cntl_auth_assoc_conf(int param_1,int param_2,undefined2 param_3)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  undefined2 local_1a [3];
  
  iVar1 = *(int *)(param_1 + 8);
  iVar2 = *(int *)(param_1 + 0xca8);
  local_1a[0] = param_3;
  if (iVar1 == 0) {
    printk(&_LC17,0x222);
    dump_stack();
    iVar1 = *(int *)(param_1 + 8);
  }
  bVar3 = iVar2 == 6;
  if (bVar3 || param_2 != 7) {
    MlmeEnqueueWithWdev(iVar1,5,param_2,2,local_1a,0,param_1);
    RtmpOsMlmeUp(iVar1 + 0x286298);
  }
  return bVar3 || param_2 != 7;
}

