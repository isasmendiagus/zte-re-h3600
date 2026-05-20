// module: mt7915.ko
// function: Show_WmmCapable_Proc @ 0xd5fd4
// size: 216 bytes
//

undefined4 Show_WmmCapable_Proc(int *param_1,char *param_2,size_t param_3)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  
  cVar1 = *(char *)((int)param_1 + 0x286285);
  iVar3 = *param_1;
  if (cVar1 == '\x01') {
    pcVar2 = "TRUE";
    if ((char)param_1[*(int *)(iVar3 + 0x3c) * 0x160d + 0xadec7] == '\0') {
      pcVar2 = "FALSE";
    }
    snprintf(param_2,param_3,"\t%s",pcVar2);
    cVar1 = *(char *)((int)param_1 + 0x286285);
  }
  if (cVar1 == '\0') {
    pcVar2 = "TRUE";
    if ((char)param_1[*(int *)(iVar3 + 0x3c) * 0x84dec + 0xdb90b] == '\0') {
      pcVar2 = "FALSE";
    }
    snprintf(param_2,param_3,"\t%s",pcVar2);
  }
  return 0;
}

