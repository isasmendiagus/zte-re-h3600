// module: mt7915.ko
// function: OcGetRepeaterEntry @ 0xad0c0
// size: 64 bytes
//

int OcGetRepeaterEntry(int param_1,uint param_2)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 0xc);
  while( true ) {
    if ((int *)(param_1 + 0xc) == piVar1) {
      return 0;
    }
    if (*(byte *)(piVar1 + -1) == param_2) break;
    piVar1 = (int *)*piVar1;
  }
  return (int)(piVar1 + -1);
}

