// module: mt7915.ko
// function: BN_POOL_release @ 0x20ef2c
// size: 60 bytes
//

void BN_POOL_release(int param_1,int param_2)

{
  uint uVar1;
  bool bVar2;
  
  uVar1 = *(int *)(param_1 + 0xc) - 1U & 0xf;
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) - param_2;
  while (bVar2 = param_2 != 0, param_2 = param_2 + -1, bVar2) {
    bVar2 = uVar1 == 0;
    uVar1 = uVar1 - 1;
    if (bVar2) {
      uVar1 = 0xf;
      *(undefined4 *)(param_1 + 4) = *(undefined4 *)(*(int *)(param_1 + 4) + 0x140);
    }
  }
  return;
}

