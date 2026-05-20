// module: mt7915.ko
// function: RTMPFindSection @ 0xeec78
// size: 56 bytes
//

int RTMPFindSection(undefined4 param_1)

{
  int iVar1;
  char local_28 [36];
  
  builtin_strncpy(local_28,"Default",8);
  iVar1 = rtstrstr(param_1,local_28);
  if (iVar1 != 0) {
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}

