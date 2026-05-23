// module: mt7915.ko
// function: BigInteger_Add_DW @ 0x1ff810
// size: 148 bytes
//

void BigInteger_Add_DW(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  
  uVar1 = **(uint **)(param_1 + 0xc);
  **(uint **)(param_1 + 0xc) = param_2 + uVar1;
  puVar3 = *(uint **)(param_1 + 0xc);
  if ((*puVar3 < uVar1) && (1 < *(uint *)(param_1 + 0x14))) {
    uVar1 = puVar3[1];
    puVar3 = puVar3 + 1;
    if (uVar1 == 0xffffffff) {
      uVar2 = 1;
      do {
        *puVar3 = 0;
        uVar2 = uVar2 + 1 & 0xff;
        if (*(uint *)(param_1 + 0x14) <= uVar2) goto LAB_001ff898;
        puVar3 = (uint *)(*(int *)(param_1 + 0xc) + (short)uVar2 * 4);
        uVar1 = *(uint *)(*(int *)(param_1 + 0xc) + (short)uVar2 * 4);
      } while (uVar1 == 0xffffffff);
    }
    *puVar3 = uVar1 + 1;
    BigInteger_ClearHighBits();
    return;
  }
LAB_001ff898:
                    /* WARNING: Subroutine does not return */
  panic("BigInteger_Add_DW: todo: length update");
}

