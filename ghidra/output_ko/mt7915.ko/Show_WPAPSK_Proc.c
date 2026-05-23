// module: mt7915.ko
// function: Show_WPAPSK_Proc @ 0xd6240
// size: 200 bytes
//

undefined4 Show_WPAPSK_Proc(int *param_1,char *param_2,size_t param_3)

{
  int iVar1;
  size_t sVar2;
  byte *pbVar3;
  
  iVar1 = *(int *)(*param_1 + 0x3c) * 0x2137b0;
  if (0x37 < param_1[*(int *)(*param_1 + 0x3c) * 0x84dec + 0x16001d] - 8U) {
    snprintf(param_2,param_3,"\tWPAPSK = ");
    pbVar3 = (byte *)((int)param_1 + iVar1 + 0x580031);
    do {
      sVar2 = strlen(param_2);
      pbVar3 = pbVar3 + 1;
      snprintf(param_2 + sVar2,param_3 - sVar2,"%02X",(uint)*pbVar3);
    } while (pbVar3 != (byte *)((int)param_1 + iVar1 + 0x580051));
    return 0;
  }
  snprintf(param_2,param_3,"\tWPAPSK = %s",(int)param_1 + iVar1 + 0x580032);
  return 0;
}

