// module: mt7915.ko
// function: hc_set_txcmd_mode @ 0xa9730
// size: 28 bytes
//

void hc_set_txcmd_mode(int param_1,int param_2)

{
  if (param_2 == 1) {
    if ((*(uint *)(param_1 + 0xb58) & 0x200000) != 0) {
      *(undefined1 *)(param_1 + 0x32d9) = 1;
    }
    return;
  }
  return;
}

