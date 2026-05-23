// module: mt7915.ko
// function: ZTE_Set_Bhbss_SSID @ 0x161ae4
// size: 160 bytes
//

undefined4 ZTE_Set_Bhbss_SSID(int *param_1,char *param_2)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = *param_1;
  iVar4 = *(int *)(iVar3 + 0x3c);
  iVar1 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]);
  if (((iVar4 < iVar1) && (*(int *)(iVar3 + 0x3c) < 0x20)) &&
     (sVar2 = strlen(param_2), sVar2 < 0x21)) {
    __memzero(param_1 + 0x29f301,0x20);
    sVar2 = strlen(param_2);
    memmove(param_1 + 0x29f301,param_2,sVar2);
    sVar2 = strlen(param_2);
    *(char *)((int)param_1 + 0xa7cc25) = (char)sVar2;
    return 1;
  }
  return 0;
}

