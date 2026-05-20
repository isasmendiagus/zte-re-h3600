// module: mt7915.ko
// function: RtmpOSIRQRequest @ 0x244c28
// size: 92 bytes
//

int RtmpOSIRQRequest(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = request_threaded_irq(param_1,param_3,0,0x80,param_2,param_4);
  if ((iVar1 != 0) && (0 < DebugLevel)) {
    printk("request_irq ERROR(%d)\n",iVar1);
  }
  return iVar1;
}

