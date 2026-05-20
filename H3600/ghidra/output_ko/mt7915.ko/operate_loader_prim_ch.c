// module: mt7915.ko
// function: operate_loader_prim_ch @ 0x10705c
// size: 12 bytes
//

void operate_loader_prim_ch(int param_1)

{
  *(undefined1 *)(param_1 + 0x20) = *(undefined1 *)(param_1 + 1);
  return;
}

