// module: mt7915.ko
// function: WscRandomGeneratePinCode @ 0x1e54d4
// size: 100 bytes
//

int WscRandomGeneratePinCode(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined8 uVar5;
  
  iVar1 = RandomByte();
  iVar2 = RandomByte(param_1);
  uVar5 = RandomByte(param_1);
  uVar3 = (int)uVar5 + (iVar2 + iVar1 * 0x100) * 0x100;
  uVar4 = uVar3 % 10000000;
  iVar1 = ComputeChecksum(uVar4,(int)((ulonglong)uVar5 >> 0x20),uVar3 * 0x6b5fca6b);
  return iVar1 + uVar4 * 10;
}

