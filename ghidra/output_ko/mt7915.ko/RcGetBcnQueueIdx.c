// module: mt7915.ko
// function: RcGetBcnQueueIdx @ 0xabe9c
// size: 28 bytes
//

undefined4 RcGetBcnQueueIdx(int param_1)

{
  undefined4 uVar1;
  
  if (**(char **)(*(int *)(param_1 + 8) + 4) == '\0') {
    uVar1 = 0x12;
  }
  else {
    uVar1 = 0x16;
  }
  return uVar1;
}

