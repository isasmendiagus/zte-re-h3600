// module: mt7915.ko
// function: WPAStartFor2WayExec @ 0x121d54
// size: 80 bytes
//

void WPAStartFor2WayExec(undefined4 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_2 + 0xc);
  MlmeEnqueueWithWdev(iVar1,0x17,6,6,param_2 + 0xec,0,*(undefined4 *)(param_2 + 8));
  RtmpOsMlmeUp(iVar1 + 0x286298);
  return;
}

