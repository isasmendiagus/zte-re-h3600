// module: mt7915.ko
// function: IsErrRecoveryInIdleStat @ 0xb144c
// size: 32 bytes
//

bool IsErrRecoveryInIdleStat(int param_1)

{
  bool bVar1;
  
  if (param_1 == 0) {
    bVar1 = true;
  }
  else {
    bVar1 = *(int *)(param_1 + 0xa7bf04) == 0;
  }
  return bVar1;
}

