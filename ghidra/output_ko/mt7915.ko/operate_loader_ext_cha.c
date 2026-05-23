// module: mt7915.ko
// function: operate_loader_ext_cha @ 0x10789c
// size: 20 bytes
//

void operate_loader_ext_cha(int param_1)

{
  *(byte *)(param_1 + 0x21) = *(byte *)(param_1 + 0x21) & 0xfc | *(byte *)(param_1 + 8) & 3;
  return;
}

