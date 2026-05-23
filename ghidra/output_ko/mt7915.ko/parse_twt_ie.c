// module: mt7915.ko
// function: parse_twt_ie @ 0x167660
// size: 24 bytes
//

void parse_twt_ie(void *param_1,int param_2)

{
  os_move_mem((void *)(param_2 + 0x22e),param_1,0x11);
  return;
}

