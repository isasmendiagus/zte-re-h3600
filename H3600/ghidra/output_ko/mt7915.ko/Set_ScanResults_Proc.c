// module: mt7915.ko
// function: Set_ScanResults_Proc @ 0xbab08
// size: 136 bytes
//

undefined4 Set_ScanResults_Proc(int param_1)

{
  int iVar1;
  
  iVar1 = Channel2Index(param_1,*(undefined1 *)(param_1 + 0x286074),
                        *(undefined1 *)(param_1 + 0x28608c));
  if (0 < DebugLevel) {
    printk("Channel : %d NF value : %ddb \tBusyTime : %dusec\n",*(undefined4 *)(param_1 + 0x286074),
           *(undefined4 *)(param_1 + 0x286088),*(undefined4 *)(param_1 + (iVar1 + 0xa1824) * 4 + 4))
    ;
  }
  *(undefined1 *)(param_1 + 0x28608c) = 0;
  *(undefined4 *)(param_1 + 0x286074) = 0;
  *(undefined4 *)(param_1 + 0x286088) = 0;
  *(undefined4 *)(param_1 + (iVar1 + 0xa1824) * 4 + 4) = 0;
  return 1;
}

