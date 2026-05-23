// module: mt7915.ko
// function: MacTableLookup @ 0x148e0c
// size: 132 bytes
//

int * MacTableLookup(int param_1,byte *param_2)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = *(int **)(param_1 +
                    ((byte)(*param_2 ^ param_2[1] ^ param_2[2] ^ param_2[3] ^ param_2[4] ^
                           param_2[5]) + 0x28648) * 4);
  while (((piVar2 != (int *)0x0 && (*piVar2 != 0)) &&
         (iVar1 = memcmp(piVar2 + 0x3b,param_2,6), iVar1 != 0))) {
    piVar2 = (int *)piVar2[4];
  }
  return piVar2;
}

