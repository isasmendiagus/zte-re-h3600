// module: mt7915.ko
// function: operate_loader_greenfield @ 0x107960
// size: 16 bytes
//

void operate_loader_greenfield(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0x36) = *(byte *)(param_1 + 0x36) & 0xef | (param_2 & 1) << 4;
  return;
}

