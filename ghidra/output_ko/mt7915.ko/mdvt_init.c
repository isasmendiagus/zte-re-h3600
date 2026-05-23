// module: mt7915.ko
// function: mdvt_init @ 0x1d780c
// size: 68 bytes
//

undefined4 mdvt_init(int param_1)

{
  if (param_1 != 0) {
    os_zero_mem(param_1 + 0xa7c23e,2);
    *(undefined1 *)(param_1 + 0xa7c23e) = 1;
    return 0;
  }
  return 0;
}

