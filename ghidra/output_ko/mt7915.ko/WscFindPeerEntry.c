// module: mt7915.ko
// function: WscFindPeerEntry @ 0x1eddbc
// size: 68 bytes
//

int WscFindPeerEntry(int *param_1,void *param_2)

{
  int iVar1;
  
  param_1 = (int *)*param_1;
  while ((param_1 != (int *)0x0 && (iVar1 = memcmp(param_1 + 2,param_2,6), iVar1 != 0))) {
    param_1 = (int *)*param_1;
  }
  return (int)param_1;
}

