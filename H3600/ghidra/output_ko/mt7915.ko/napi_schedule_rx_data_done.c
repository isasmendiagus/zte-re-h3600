// module: mt7915.ko
// function: napi_schedule_rx_data_done @ 0x1cb984
// size: 68 bytes
//

undefined4 napi_schedule_rx_data_done(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x568) << 0x1e < 0) {
    return 0;
  }
  iVar1 = _test_and_set_bit(0,param_1 + 0x568);
  if (iVar1 == 0) {
    __napi_schedule(param_1 + 0x560);
  }
  return 0;
}

