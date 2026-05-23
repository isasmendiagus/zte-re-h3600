// module: mt7915.ko
// function: wdev_search_by_netdev @ 0x14e1d0
// size: 60 bytes
//

int * wdev_search_by_netdev(int param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  
  if (param_2 == 0) {
    return (int *)0x0;
  }
  piVar2 = (int *)(param_1 + 8);
  while( true ) {
    piVar2 = piVar2 + 1;
    piVar1 = (int *)*piVar2;
    if ((piVar1 != (int *)0x0) && (param_2 == *piVar1)) break;
    if (piVar2 == (int *)(param_1 + 0x1a8)) {
      return piVar1;
    }
  }
  return piVar1;
}

