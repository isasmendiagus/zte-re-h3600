// module: mt7915.ko
// function: CmdRFRegAccessReadCb @ 0x1abe50
// size: 16 bytes
//

void CmdRFRegAccessReadCb(int param_1,int param_2,int param_3)

{
  os_move_mem(*(void **)(param_1 + 0xc),(void *)(param_2 + 8),param_3 - 8);
  return;
}

