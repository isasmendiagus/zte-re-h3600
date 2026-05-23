// module: mt7915.ko
// function: VIRTUAL_IF_INC @ 0xec574
// size: 92 bytes
//

int VIRTUAL_IF_INC(int param_1)

{
  int iVar1;
  undefined4 local_14;
  
  local_14 = 0;
  OS_SPIN_LOCK_IRQSAVE(param_1 + 0x794c2c,&local_14);
  iVar1 = *(int *)(param_1 + 0x794c28);
  *(int *)(param_1 + 0x794c28) = iVar1 + 1;
  OS_SPIN_UNLOCK_IRQRESTORE(param_1 + 0x794c2c,&local_14);
  return iVar1;
}

