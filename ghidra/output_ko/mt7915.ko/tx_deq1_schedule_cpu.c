// module: mt7915.ko
// function: tx_deq1_schedule_cpu @ 0x1505d0
// size: 48 bytes
//

void tx_deq1_schedule_cpu(int param_1)

{
  int iVar1;
  
  iVar1 = _test_and_set_bit(0,param_1 + 0x285bc8);
  if (iVar1 != 0) {
    return;
  }
  __tasklet_hi_schedule(param_1 + 0x285bc4);
  return;
}

