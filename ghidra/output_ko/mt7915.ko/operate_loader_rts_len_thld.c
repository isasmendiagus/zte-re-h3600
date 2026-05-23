// module: mt7915.ko
// function: operate_loader_rts_len_thld @ 0x1079e8
// size: 8 bytes
//

void operate_loader_rts_len_thld(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x18) = param_2;
  return;
}

