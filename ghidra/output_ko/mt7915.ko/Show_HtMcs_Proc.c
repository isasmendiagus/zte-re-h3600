// module: mt7915.ko
// function: Show_HtMcs_Proc @ 0xd5c34
// size: 144 bytes
//

undefined4 Show_HtMcs_Proc(int *param_1,char *param_2,size_t param_3,undefined4 param_4)

{
  int iVar1;
  
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    iVar1 = *(int *)(*param_1 + 0x3c) * 0x160d + 0xadc92;
  }
  else {
    if (*(char *)((int)param_1 + 0x286285) != '\0') {
      return 0;
    }
    iVar1 = *(int *)(*param_1 + 0x3c) * 0x84dec + 0xdb6d6;
  }
  if (param_1 + iVar1 != (int *)0x0) {
    snprintf(param_2,param_3,"\t%u",*(byte *)((int)(param_1 + iVar1) + 0x8ae) & 0x7f,param_4);
  }
  return 0;
}

