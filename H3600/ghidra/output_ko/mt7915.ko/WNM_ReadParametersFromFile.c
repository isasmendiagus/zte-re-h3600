// module: mt7915.ko
// function: WNM_ReadParametersFromFile @ 0x228320
// size: 344 bytes
//

void WNM_ReadParametersFromFile(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  
  iVar1 = RTMPGetKeyParameter("WNMEnable",param_2,0xff,param_3,1);
  if (iVar1 == 0) {
    pbVar4 = (byte *)(param_1 + 0x3678c7);
    iVar1 = 0;
    while( true ) {
      iVar2 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      if (iVar2 <= iVar1) break;
      pbVar4 = pbVar4 + 1;
      "RT_OID_WSC_SET_MODE::unknown WscMode = %d\n"[(uint)*pbVar4 * 0x5834 + param_1 + 0xe] = '\0';
      iVar1 = iVar1 + 1;
    }
  }
  else {
    iVar1 = rstrtok(param_2,&_LC70);
    if (iVar1 != 0) {
      pbVar4 = (byte *)(param_1 + 0x3678c7);
      iVar2 = 0;
      do {
        iVar3 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
        if (iVar3 <= iVar2) {
          return;
        }
        iVar3 = simple_strtol(iVar1,0,10);
        iVar1 = DebugLevel;
        pbVar4 = pbVar4 + 1;
        "RT_OID_WSC_SET_MODE::unknown WscMode = %d\n"[(uint)*pbVar4 * 0x5834 + param_1 + 0xe] =
             0 < iVar3;
        if (2 < iVar1) {
          printk("%s::(bDot11vWNMEnable[%d]=%d)\n","WNM_ReadParametersFromFile",iVar2);
        }
        iVar2 = iVar2 + 1;
        iVar1 = rstrtok(0,&_LC70);
      } while (iVar1 != 0);
    }
  }
  return;
}

