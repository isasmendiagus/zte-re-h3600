// module: mt7915.ko
// function: bn_cmp_part_words @ 0x20dc04
// size: 108 bytes
//

undefined4 bn_cmp_part_words(int param_1,int param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  
  if (param_4 < 0) {
    piVar2 = (int *)(param_2 + (param_3 - param_4) * 4 + -4);
    iVar3 = *piVar2;
    while( true ) {
      if (iVar3 != 0) {
        return 0xffffffff;
      }
      param_4 = param_4 + 1;
      if (param_4 == 0) break;
      piVar2 = piVar2 + -1;
      iVar3 = *piVar2;
    }
  }
  else if (param_4 != 0) {
    piVar2 = (int *)(param_1 + (param_3 + param_4) * 4);
    do {
      piVar2 = piVar2 + -1;
      if (*piVar2 != 0) {
        return 1;
      }
      param_4 = param_4 + -1;
    } while (param_4 != 0);
  }
  uVar1 = bn_cmp_words();
  return uVar1;
}

