// module: mt7915.ko
// function: WscRandomGen4digitPinCode @ 0x1e548c
// size: 72 bytes
//

uint WscRandomGen4digitPinCode(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = RandomByte2();
  iVar2 = RandomByte2(param_1);
  iVar3 = RandomByte2(param_1);
  return (uint)(iVar3 + (iVar2 + iVar1 * 0x100) * 0x100) % 10000;
}

