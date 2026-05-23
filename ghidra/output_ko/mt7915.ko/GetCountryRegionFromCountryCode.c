// module: mt7915.ko
// function: GetCountryRegionFromCountryCode @ 0x141118
// size: 16 bytes
//

undefined1 GetCountryRegionFromCountryCode(void)

{
  int iVar1;
  
  iVar1 = GetChRegion();
  return *(undefined1 *)(iVar1 + 3);
}

