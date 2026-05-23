// module: mt7915.ko
// function: byte_sub @ 0xb626c
// size: 44 bytes
//

void byte_sub(int param_1,int param_2)

{
  undefined1 *puVar1;
  byte *pbVar2;
  
  pbVar2 = (byte *)(param_1 + -1);
  puVar1 = (undefined1 *)(param_2 + -1);
  do {
    pbVar2 = pbVar2 + 1;
    puVar1 = puVar1 + 1;
    *puVar1 = SboxTable[*pbVar2];
  } while (pbVar2 != (byte *)(param_1 + 0xf));
  return;
}

