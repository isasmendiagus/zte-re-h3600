// module: mt7915.ko
// function: tasklet_schedule_mac_fw_own @ 0x1cbe34
// size: 48 bytes
//

undefined4 tasklet_schedule_mac_fw_own(int param_1)

{
  int iVar1;
  
  iVar1 = _test_and_set_bit(0,param_1 + 0x68);
  if (iVar1 == 0) {
    __tasklet_hi_schedule(param_1 + 100);
  }
  return 0;
}

