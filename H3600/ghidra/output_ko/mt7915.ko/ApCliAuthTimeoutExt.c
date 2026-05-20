// module: mt7915.ko
// function: ApCliAuthTimeoutExt @ 0x80af0
// size: 184 bytes
//

void ApCliAuthTimeoutExt(undefined4 param_1,int param_2)

{
  int iVar1;
  
  if (param_2 + 0xe0 == 0) {
    printk(&_LC31,0xbc);
    dump_stack();
  }
  if (2 < DebugLevel) {
    printk("Repeater Cli AUTH - AuthTimeout\n");
  }
  iVar1 = *(int *)(param_2 + 0x8c);
  if (-1 < DebugLevel) {
    printk("(%s) ifIndex = %d, CliIdx = %d !!!\n","ApCliAuthTimeoutExt",
           *(undefined1 *)(param_2 + 0xee),*(undefined1 *)(param_2 + 4));
  }
  MlmeEnqueueWithWdev(iVar1,2,3,0,0,0,param_2 + 0xe0);
  RtmpOsMlmeUp(iVar1 + 0x286298);
  return;
}

