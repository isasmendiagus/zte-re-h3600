// module: mt7915.ko
// function: sta_ifdown_fsm_reset_complete @ 0x68a34
// size: 16 bytes
//

void sta_ifdown_fsm_reset_complete(int param_1)

{
  complete(param_1 + 0x213234);
  return;
}

