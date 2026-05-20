// module: mt7915.ko
// function: lookup_rept_entry @ 0x8143c
// size: 60 bytes
//

void lookup_rept_entry(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = RTMPLookupRepeaterCliEntry(param_1,0,param_2,1);
  if (iVar1 != 0) {
    return;
  }
  RTMPLookupRepeaterCliEntry(param_1,1,param_2,1);
  return;
}

