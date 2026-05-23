// module: mt7915.ko
// function: ApCliAssocTimeoutExt @ 0x80be4
// size: 184 bytes
//

void ApCliAssocTimeoutExt(undefined4 param_1,int param_2)

{
  int iVar1;
  
  if (param_2 + 0xe0 == 0) {
    printk(&_LC31,0xdf);
    dump_stack();
  }
  if (2 < DebugLevel) {
    printk("Repeater Cli ASSOC - enqueue APCLI_MT2_ASSOC_TIMEOUT\n");
  }
  iVar1 = *(int *)(param_2 + 0x8c);
  if (-1 < DebugLevel) {
    printk("(%s) ifIndex = %d, CliIdx = %d !!!\n","ApCliAssocTimeoutExt",
           *(undefined1 *)(param_2 + 0xee),*(undefined1 *)(param_2 + 4));
  }
  MlmeEnqueueWithWdev(iVar1,1,9,0,0,0,param_2 + 0xe0);
  RtmpOsMlmeUp(iVar1 + 0x286298);
  return;
}

