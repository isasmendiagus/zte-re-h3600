// module: mt7915.ko
// function: operate_loader_cckin40 @ 0x1079c8
// size: 32 bytes
//

void operate_loader_cckin40(int param_1,uint param_2,int param_3)

{
  bool bVar1;
  
  bVar1 = param_2 == 0xd;
  if (param_2 < 0xe) {
    bVar1 = param_3 == 1;
  }
  *(byte *)(param_1 + 0x37) = *(byte *)(param_1 + 0x37) & 0xef | bVar1 << 4;
  return;
}

