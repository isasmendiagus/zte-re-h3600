// module: mt7915.ko
// function: tasklet_schedule_sw_int @ 0x1cbe94
// size: 48 bytes
//

undefined4 tasklet_schedule_sw_int(int param_1)

{
  int iVar1;
  
  iVar1 = _test_and_set_bit(0,param_1 + 0x90);
  if (iVar1 == 0) {
    __tasklet_hi_schedule(param_1 + 0x8c);
  }
  return 0;
}

