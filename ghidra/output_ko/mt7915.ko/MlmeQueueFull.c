// module: mt7915.ko
// function: MlmeQueueFull @ 0x12d58c
// size: 104 bytes
//

undefined4 MlmeQueueFull(uint *param_1,int param_2)

{
  undefined4 uVar1;
  
  _raw_spin_lock_bh(param_1 + 3);
  if (param_2 == 0) {
    if (0x7f < *param_1) {
LAB_0012d5ec:
      uVar1 = 1;
      goto LAB_0012d5d4;
    }
  }
  else if (*param_1 == 0x100) goto LAB_0012d5ec;
  uVar1 = 0;
  if (*(char *)((int)param_1 + (param_1[2] + 1) * 0x930 + 2) != '\0') {
    uVar1 = 1;
  }
LAB_0012d5d4:
  _raw_spin_unlock_bh(param_1 + 3);
  return uVar1;
}

