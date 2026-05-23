// module: mt7915.ko
// function: SetATEReadRF @ 0x262428
// size: 20 bytes
//

bool SetATEReadRF(void)

{
  int iVar1;
  
  iVar1 = ShowAllRF();
  return iVar1 == 0;
}

