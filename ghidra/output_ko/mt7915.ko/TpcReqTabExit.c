// module: mt7915.ko
// function: TpcReqTabExit @ 0x13eb10
// size: 40 bytes
//

void TpcReqTabExit(int param_1)

{
  if (*(int *)(param_1 + 0x795980) == 0) {
    return;
  }
  os_free_mem();
  *(undefined4 *)(param_1 + 0x795980) = 0;
  return;
}

