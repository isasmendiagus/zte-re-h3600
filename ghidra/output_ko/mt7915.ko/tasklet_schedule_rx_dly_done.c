// module: mt7915.ko
// function: tasklet_schedule_rx_dly_done @ 0x1cbdd4
// size: 48 bytes
//

undefined4 tasklet_schedule_rx_dly_done(int param_1)

{
  int iVar1;
  
  iVar1 = _test_and_set_bit(0,param_1 + 0x40);
  if (iVar1 == 0) {
    __tasklet_hi_schedule(param_1 + 0x3c);
  }
  return 0;
}

