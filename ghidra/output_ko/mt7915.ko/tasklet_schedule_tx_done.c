// module: mt7915.ko
// function: tasklet_schedule_tx_done @ 0x1cbd48
// size: 44 bytes
//

undefined4 tasklet_schedule_tx_done(int param_1)

{
  int iVar1;
  
  iVar1 = _test_and_set_bit(0,param_1 + 4);
  if (iVar1 == 0) {
    __tasklet_hi_schedule(param_1);
  }
  return 0;
}

