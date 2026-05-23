// module: mt7915.ko
// function: CmdInitAccessRegReadCb @ 0x1c2984
// size: 16 bytes
//

void CmdInitAccessRegReadCb(int param_1,int param_2,int param_3)

{
  os_move_mem(*(void **)(param_1 + 0xc),(void *)(param_2 + 4),param_3 - 4);
  return;
}

