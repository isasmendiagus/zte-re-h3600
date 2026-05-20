// module: mt7915.ko
// function: TxBfProfileTag_RmsdThd @ 0x86908
// size: 8 bytes
//

void TxBfProfileTag_RmsdThd(int param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0xb) = param_2;
  return;
}

