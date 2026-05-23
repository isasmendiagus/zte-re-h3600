// module: mt7915.ko
// function: SyncMuruSramCheckAddr @ 0x187f48
// size: 12 bytes
//

void SyncMuruSramCheckAddr(undefined4 param_1,uint param_2)

{
  if (param_2 < 0xe0000000) {
    return;
  }
  FUN_0017f59c();
  return;
}

