// module: mt7915.ko
// function: GetEDCCASupport @ 0x1410e4
// size: 52 bytes
//

bool GetEDCCASupport(int param_1)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = GetChRegion(param_1 + 0x794c31);
  if (*(char *)(iVar2 + 3) == '\x01') {
    bVar1 = false;
  }
  else {
    bVar1 = *(char *)(iVar2 + 4) == '\x01';
  }
  return bVar1;
}

