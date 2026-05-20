// module: mt7915.ko
// function: BN_GENCB_free @ 0x20e168
// size: 12 bytes
//

void BN_GENCB_free(int param_1)

{
  if (param_1 == 0) {
    return;
  }
  os_free_mem();
  return;
}

