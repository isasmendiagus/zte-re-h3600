// module: mt7915.ko
// function: RTMP_HANDLE_PRETBTT_INT_EVENT @ 0xb1170
// size: 32 bytes
//

void RTMP_HANDLE_PRETBTT_INT_EVENT(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = get_default_wdev();
  UpdateBeaconHandler(param_1,uVar1,4);
  return;
}

