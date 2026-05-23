// module: mt7915.ko
// function: mt_AsicClientBfCap @ 0x86830
// size: 32 bytes
//

void mt_AsicClientBfCap(int param_1,int param_2)

{
  if (*(char *)(param_1 + 0xa786f7) != '\x01') {
    return;
  }
  AsicTxBfApClientCluster
            (param_1,*(undefined1 *)(param_2 + 0xe0),*(undefined1 *)(param_1 + 0xa786f5));
  return;
}

