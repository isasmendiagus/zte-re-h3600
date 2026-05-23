// module: mt7915.ko
// function: assoc_fsm_msg_checker @ 0x10c714
// size: 104 bytes
//

bool assoc_fsm_msg_checker(int param_1,int param_2)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = *(int *)(param_2 + 0x92c);
  if (iVar1 != 0) {
    bVar2 = *(char *)(iVar1 + 0xaa8) == '\0';
    if (((*(byte *)(param_1 + 0x286294) & 3) == 3) && (*(int *)(iVar1 + 0x14) == 2)) {
      iVar1 = isValidApCliIf(*(undefined1 *)(iVar1 + 0xe));
      bVar2 = iVar1 == 0 || bVar2;
    }
    return bVar2;
  }
  return false;
}

