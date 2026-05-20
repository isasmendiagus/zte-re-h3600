// module: mt7915.ko
// function: is_rsne_pmkid_cache_match @ 0x19d14
// size: 80 bytes
//

bool is_rsne_pmkid_cache_match
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined4 *param_6)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_11 [5];
  
  iVar1 = WPA_ExtractSuiteFromRSNIE(param_1,param_2,4,auStack_11);
  if (iVar1 != 0) {
    uVar2 = RTMPValidatePMKIDCache(param_3,param_4,param_5);
    *param_6 = uVar2;
  }
  return iVar1 != 0;
}

