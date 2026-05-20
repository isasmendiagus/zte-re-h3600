// module: mt7915.ko
// function: EnqueuePsPoll @ 0x1dd98c
// size: 120 bytes
//

void EnqueuePsPoll(int param_1,int param_2)

{
  if ((*(uint *)(param_1 + 0xa3ac14) & 1) != 0) {
    return;
  }
  if ((*(int *)(param_1 + 0xa77bb4) == 1) &&
     ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) != 0)) {
    return;
  }
  if (*(int *)(param_2 + 0x2124ac) == 3) {
    "BssEntrySet"[param_1 + 6] = "BssEntrySet"[param_1 + 6] | 0x10;
  }
  MiniportMMRequest(param_1,0,"BssEntrySet" + param_1 + 5,0x10);
  return;
}

