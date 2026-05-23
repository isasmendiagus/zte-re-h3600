// module: mt7915.ko
// function: bn_cmp_words @ 0x20db7c
// size: 136 bytes
//

undefined4 bn_cmp_words(int param_1,int param_2,int param_3)

{
  uint *puVar1;
  undefined4 uVar2;
  uint *puVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  bool bVar7;
  
  iVar4 = param_3 + 0x3fffffff;
  uVar6 = *(uint *)(param_1 + iVar4 * 4);
  uVar5 = *(uint *)(param_2 + iVar4 * 4);
  if (uVar6 != uVar5) {
    if (uVar5 <= uVar6) {
      return 1;
    }
    return 0xffffffff;
  }
  param_3 = param_3 + -2;
  if (param_3 < 0) {
    return 0;
  }
  iVar4 = iVar4 * 4 + -4;
  uVar6 = *(uint *)(param_1 + iVar4);
  uVar5 = *(uint *)(param_2 + iVar4);
  if (uVar6 == uVar5) {
    puVar1 = (uint *)(param_1 + iVar4);
    puVar3 = (uint *)(param_2 + iVar4);
    do {
      bVar7 = param_3 == 0;
      param_3 = param_3 + -1;
      if (bVar7) {
        return 0;
      }
      puVar1 = puVar1 + -1;
      uVar6 = *puVar1;
      puVar3 = puVar3 + -1;
      uVar5 = *puVar3;
    } while (uVar6 == uVar5);
  }
  if (uVar5 < uVar6) {
    uVar2 = 1;
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

