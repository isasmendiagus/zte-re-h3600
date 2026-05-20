// module: mt7915.ko
// function: RoutingTabARPLookupUpdate @ 0xa1228
// size: 36 bytes
//

void RoutingTabARPLookupUpdate(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_3 == 0) {
    return;
  }
  iVar1 = RoutingTabGetEntryCount();
  if (iVar1 != 0) {
    *(undefined4 *)(param_3 + 0x14) = param_4;
  }
  return;
}

