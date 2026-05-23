// module: mt7915.ko
// function: rc_radio_equal @ 0xac9a0
// size: 112 bytes
//

bool rc_radio_equal(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 4);
  if ((((*(char *)(iVar1 + 9) != '\x01') && (*(char *)(iVar1 + 4) == *(char *)(param_2 + 5))) &&
      (*(char *)(iVar1 + 7) == *(char *)(param_2 + 3))) &&
     ((*(char *)(iVar1 + 6) == *(char *)(param_2 + 6) &&
      (*(char *)(iVar1 + 5) == *(char *)(param_2 + 7))))) {
    return *(char *)(iVar1 + 0xd) == *(char *)(param_2 + 8);
  }
  return false;
}

