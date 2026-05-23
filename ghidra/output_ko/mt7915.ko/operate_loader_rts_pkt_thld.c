// module: mt7915.ko
// function: operate_loader_rts_pkt_thld @ 0x1079f8
// size: 8 bytes
//

void operate_loader_rts_pkt_thld(int param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0x14) = param_2;
  return;
}

