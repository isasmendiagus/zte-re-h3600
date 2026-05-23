// module: mt7915.ko
// function: RtmpOSNetDevAlloc @ 0x2441bc
// size: 92 bytes
//

bool RtmpOSNetDevAlloc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int extraout_r3;
  
  *param_1 = 0;
  iVar1 = DebugLevel;
  if (2 < DebugLevel) {
    printk("Allocate a net device with private data size=%d!\n");
    iVar1 = extraout_r3;
  }
  iVar1 = alloc_etherdev_mqs(param_2,1,1,iVar1,param_4);
  *param_1 = iVar1;
  return iVar1 == 0;
}

