// module: mt7915.ko
// function: cntl_do_disassoc_now @ 0x10d7f4
// size: 20 bytes
//

bool cntl_do_disassoc_now(int param_1)

{
  return *(int *)(param_1 + 0xca8) == 6;
}

