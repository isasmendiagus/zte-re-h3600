// module: mt7915.ko
// function: dfs_zero_wait_ch_init_timeout @ 0x22edc4
// size: 232 bytes
//

void dfs_zero_wait_ch_init_timeout(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  undefined1 auStack_19 [5];
  
  if (2 < DebugLevel) {
    printk("%s() ch_stat %d\n","dfs_zero_wait_ch_init_timeout",*(undefined4 *)(param_2 + 0x79540c));
  }
  RTMPCancelTimer(param_2 + 0xa791c4,auStack_19);
  if (*(int *)(param_2 + 0x79540c) == 0) {
    DfsDedicatedOutBandSetChannel
              (param_2,*(undefined1 *)(param_2 + 0x7953fb),*(undefined1 *)(param_2 + 0x7953fc),2);
    return;
  }
  if (*(int *)(param_2 + 0x79540c) == 5) {
    uVar1 = dfs_get_band_by_ch(param_2,*(undefined1 *)(param_2 + 0x7953fb));
    if (2 < DebugLevel) {
      printk("%s() New inband channel %d bandidx %d\n","dfs_zero_wait_ch_init_timeout",
             *(undefined1 *)(param_2 + 0x7953fb),uVar1);
    }
    *(undefined4 *)(param_2 + 0x79540c) = 2;
    DfsDedicatedInBandSetChannel
              (param_2,*(undefined1 *)(param_2 + 0x7953fb),*(undefined1 *)(param_2 + 0x7953fc),0,
               uVar1);
  }
  return;
}

