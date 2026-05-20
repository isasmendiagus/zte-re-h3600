// module: mt7915.ko
// function: WpaShowAllsuite @ 0x118f9c
// size: 232 bytes
//

void WpaShowAllsuite(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  byte local_11 [5];
  
  hex_dump("RSNIE",param_1,param_2);
  iVar1 = WPA_ExtractSuiteFromRSNIE(param_1,param_2,0,local_11);
  if (iVar1 != 0) {
    hex_dump("group cipher",iVar1,(uint)local_11[0] << 2);
  }
  iVar1 = WPA_ExtractSuiteFromRSNIE(param_1,param_2,1,local_11);
  if (iVar1 != 0) {
    hex_dump("pairwise cipher",iVar1,(uint)local_11[0] << 2);
  }
  iVar1 = WPA_ExtractSuiteFromRSNIE(param_1,param_2,2,local_11);
  if (iVar1 != 0) {
    hex_dump("AKM suite",iVar1,(uint)local_11[0] << 2);
  }
  iVar1 = WPA_ExtractSuiteFromRSNIE(param_1,param_2,4,local_11);
  if (iVar1 != 0) {
    hex_dump("PMKID",iVar1,0x10);
  }
  return;
}

