// module: mt7915.ko
// function: MacTableLookup2 @ 0x148e90
// size: 204 bytes
//

int * MacTableLookup2(int param_1,byte *param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = *(int **)(param_1 +
                    ((byte)(*param_2 ^ param_2[1] ^ param_2[2] ^ param_2[3] ^ param_2[4] ^
                           param_2[5]) + 0x28648) * 4);
  if (param_3 == 0) {
    while (((piVar2 != (int *)0x0 && (*piVar2 != 0)) &&
           (iVar1 = memcmp(piVar2 + 0x3b,param_2,6), iVar1 != 0))) {
      piVar2 = (int *)piVar2[4];
    }
  }
  else {
    for (; ((piVar2 != (int *)0x0 && (*piVar2 != 0)) &&
           ((iVar1 = memcmp(piVar2 + 0x3b,param_2,6), iVar1 != 0 || (piVar2[2] != param_3))));
        piVar2 = (int *)piVar2[4]) {
    }
  }
  return piVar2;
}

