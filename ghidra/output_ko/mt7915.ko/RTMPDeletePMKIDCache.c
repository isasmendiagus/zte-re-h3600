// module: mt7915.ko
// function: RTMPDeletePMKIDCache @ 0x19c18
// size: 96 bytes
//

void RTMPDeletePMKIDCache(int param_1,uint param_2,int param_3)

{
  uint uVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  
  iVar2 = param_1 + param_3 * 0x60;
  if (*(char *)(iVar2 + 0x5c) == '\0') {
    return;
  }
  uVar1 = (uint)*(byte *)(param_1 + param_3 * 0x60);
  if (uVar1 != param_2) {
    return;
  }
  *(undefined1 *)(iVar2 + 0x5c) = 0;
                    /* WARNING: Could not recover jumptable at 0x00019c60. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  if (DebugLevel < 0) {
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  printk("%s():(IF(%d), del PMKID CacheIdx=%d\n","RTMPDeletePMKIDCache",uVar1,param_3);
  return;
}

