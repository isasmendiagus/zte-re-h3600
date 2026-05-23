// module: mt7915.ko
// function: HW_AP_TXBF_TX_APPLY @ 0xb1ce8
// size: 44 bytes
//

void HW_AP_TXBF_TX_APPLY(undefined4 param_1,undefined1 param_2)

{
  undefined1 local_9 [5];
  
  local_9[0] = param_2;
  FUN_000b0a74(param_1,0,0x16,1,local_9);
  return;
}

