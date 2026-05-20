// module: mt7915.ko
// function: mac_entry_lookup @ 0x14ab8c
// size: 148 bytes
//

void mac_entry_lookup(int param_1,byte *param_2,undefined4 param_3,undefined4 *param_4)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = *(int **)(param_1 +
                    ((byte)(*param_2 ^ param_2[1] ^ param_2[2] ^ param_2[3] ^ param_2[4] ^
                           param_2[5]) + 0x28648) * 4);
  if ((piVar2 != (int *)0x0) && (*piVar2 != 0)) {
    while (iVar1 = memcmp(piVar2 + 0x3b,param_2,6), iVar1 != 0) {
      piVar2 = (int *)piVar2[4];
      if ((piVar2 == (int *)0x0) || (*piVar2 == 0)) break;
    }
  }
  *param_4 = piVar2;
  return;
}

