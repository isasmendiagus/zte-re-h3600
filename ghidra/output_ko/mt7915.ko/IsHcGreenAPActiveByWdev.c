// module: mt7915.ko
// function: IsHcGreenAPActiveByWdev @ 0xa8fec
// size: 36 bytes
//

undefined1 IsHcGreenAPActiveByWdev(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0xabc);
  iVar2 = hdev_obj_state_ready(iVar3);
  uVar1 = 0;
  if (iVar2 != 0) {
    uVar1 = *(undefined1 *)(*(int *)(*(int *)(iVar3 + 8) + 4) + 0xc);
  }
  return uVar1;
}

