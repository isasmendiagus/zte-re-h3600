// module: mt7915.ko
// function: xor_128 @ 0xb6120
// size: 48 bytes
//

void xor_128(int param_1,int param_2,int param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  byte *pbVar3;
  
  pbVar3 = (byte *)(param_1 + -1);
  pbVar1 = (byte *)(param_2 + -1);
  pbVar2 = (byte *)(param_3 + -1);
  do {
    pbVar3 = pbVar3 + 1;
    pbVar1 = pbVar1 + 1;
    pbVar2 = pbVar2 + 1;
    *pbVar2 = *pbVar3 ^ *pbVar1;
  } while (pbVar3 != (byte *)(param_1 + 0xf));
  return;
}

