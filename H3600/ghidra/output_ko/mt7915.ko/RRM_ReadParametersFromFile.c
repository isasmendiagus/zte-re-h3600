// module: mt7915.ko
// function: RRM_ReadParametersFromFile @ 0x21f1f0
// size: 784 bytes
//

void RRM_ReadParametersFromFile(int param_1,char *param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined *puVar6;
  byte *pbVar7;
  
  iVar2 = RTMPGetKeyParameter("RRMEnable",param_2,0xff,param_3,1);
  if (iVar2 == 0) {
    pbVar7 = (byte *)(param_1 + 0x3678c7);
    iVar2 = 0;
    while( true ) {
      iVar3 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      if (iVar3 <= iVar2) break;
      pbVar7 = pbVar7 + 1;
      "%u-%02x:%02x:%02x:%02x:%02x:%02x"[(uint)*pbVar7 * 0x5834 + param_1 + 0x11] = '\0';
      iVar2 = iVar2 + 1;
    }
  }
  else {
    iVar2 = rstrtok(param_2,&_LC15);
    if (iVar2 != 0) {
      pbVar7 = (byte *)(param_1 + 0x3678c7);
      iVar3 = 0;
      do {
        iVar4 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
        if (iVar4 <= iVar3) break;
        iVar4 = os_str_tol(iVar2,0,10);
        iVar2 = DebugLevel;
        pbVar7 = pbVar7 + 1;
        iVar5 = (uint)*pbVar7 * 0x5834 + param_1;
        "%u-%02x:%02x:%02x:%02x:%02x:%02x"[iVar5 + 0x10] = '\x01';
        "%u-%02x:%02x:%02x:%02x:%02x:%02x"[iVar5 + 0x11] = 0 < iVar4;
        if (2 < iVar2) {
          printk("%s::(bDot11kRRMEnable[%d]=%d)\n","RRM_ReadParametersFromFile",iVar3,
                 "%u-%02x:%02x:%02x:%02x:%02x:%02x"[iVar5 + 0x11]);
        }
        iVar3 = iVar3 + 1;
        iVar2 = rstrtok(0,&_LC15);
      } while (iVar2 != 0);
    }
  }
  iVar2 = RTMPGetKeyParameter("RRMEnable",param_2,0xff,param_3,1);
  if (iVar2 == 0) {
    cVar1 = *(char *)(param_1 + 0x794ab8);
    if ((cVar1 != '\0') && ((&DAT_0036e679)[param_1] = 0, cVar1 != '\x01')) {
      (&DAT_00581e29)[param_1] = 0;
    }
  }
  else {
    iVar2 = rstrtok(param_2,&_LC15);
    if ((iVar2 != 0) && (*(char *)(param_1 + 0x794ab8) != '\0')) {
      puVar6 = &DAT_0036e678 + param_1;
      iVar3 = 0;
      do {
        iVar2 = os_str_tol(iVar2,0,10);
        *puVar6 = 1;
        puVar6[1] = 0 < iVar2;
        if (2 < DebugLevel) {
          printk("%s::(bDot11kRRMEnable[%d]=%d)\n","RRM_ReadParametersFromFile",iVar3,puVar6[1]);
        }
        iVar2 = rstrtok(0,&_LC15);
        iVar3 = iVar3 + 1;
        puVar6 = puVar6 + 0x2137b0;
      } while ((iVar2 != 0) && (iVar3 < (int)(uint)*(byte *)(param_1 + 0x794ab8)));
    }
  }
  iVar2 = RTMPGetKeyParameter("RegDomain",param_2,0xff,param_3,1);
  if (iVar2 != 0) {
    iVar2 = strncmp(param_2,"Global",6);
    if (iVar2 == 0) {
      *(undefined1 *)(param_1 + 0xa7cc26) = 1;
    }
    else {
      *(undefined1 *)(param_1 + 0xa7cc26) = 0;
    }
    if (0 < DebugLevel) {
      printk("pAd->reg_domain = %u\n",*(undefined1 *)(param_1 + 0xa7cc26));
      return;
    }
  }
  return;
}

