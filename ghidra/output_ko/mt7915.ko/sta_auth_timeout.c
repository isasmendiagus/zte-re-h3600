// module: mt7915.ko
// function: sta_auth_timeout @ 0x76d74
// size: 120 bytes
//

void sta_auth_timeout(undefined4 param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = *param_2;
  if (2 < DebugLevel) {
    printk("%s():AuthTimeout\n","sta_auth_timeout");
  }
  MlmeEnqueueWithWdev(iVar1,2,3,0,0,0,param_2[1]);
  RtmpOsMlmeUp(iVar1 + 0x286298);
  return;
}

