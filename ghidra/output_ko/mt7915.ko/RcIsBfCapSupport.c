// module: mt7915.ko
// function: RcIsBfCapSupport @ 0xac98c
// size: 20 bytes
//

undefined1 RcIsBfCapSupport(int param_1)

{
  undefined1 uVar1;
  
  uVar1 = 0;
  if (*(int *)(param_1 + 8) != 0) {
    uVar1 = *(undefined1 *)(*(int *)(*(int *)(param_1 + 8) + 4) + 10);
  }
  return uVar1;
}

