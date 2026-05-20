// module: mt7915.ko
// function: tasklet_schedule_rx_event_done @ 0x1cbda4
// size: 48 bytes
//

undefined4 tasklet_schedule_rx_event_done(int param_1)

{
  int iVar1;
  
  iVar1 = _test_and_set_bit(0,param_1 + 0x2c);
  if (iVar1 == 0) {
    __tasklet_hi_schedule(param_1 + 0x28);
  }
  return 0;
}

