// module: mt7915.ko
// function: Show_Adhoc_MacTable_Proc @ 0x5a6b4
// size: 928 bytes
//

undefined4 Show_Adhoc_MacTable_Proc(int *param_1,char *param_2,int param_3)

{
  int iVar1;
  size_t sVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined *puVar11;
  
  piVar4 = param_1 + 0x28787;
  iVar6 = 0;
  iVar1 = wlan_operate_get_addht(param_1 + *(int *)(*param_1 + 0x3c) * 0x84dec + 0xdb6d6);
  param_2[0] = '\n';
  param_2[1] = '\0';
  sprintf(param_2,"%sHT Operating Mode : %d\n",param_2,*(byte *)(iVar1 + 2) & 3);
  sVar2 = strlen(param_2);
  puVar8 = &_LC82;
  puVar9 = &_LC83;
  puVar10 = &_LC84;
  puVar11 = &_LC85;
  puVar7 = &_LC81;
  sprintf(param_2 + sVar2,"\n%-19s%-4s%-4s%-7s%-7s%-7s%-10s%-6s%-6s%-6s%-6s\n",&_LC75,&_LC76,&_LC77,
          "RSSI0","RSSI1","RSSI2",&_LC81,&_LC82,&_LC83,&_LC84,&_LC85);
  while ((iVar1 = HcGetMaxStaNum(param_1), iVar6 < iVar1 &&
         (sVar2 = strlen(param_2), sVar2 <= param_3 - 0x1eU))) {
    if ((piVar4[-0x3f] == 0x20001 || piVar4[-0x3f] == 2) && (*piVar4 == 2)) {
      sprintf(param_2 + sVar2,"%02x:%02x:%02x:%02x:%02x:%02x  ",(uint)*(byte *)(piVar4 + -4),
              (uint)*(byte *)((int)piVar4 + -0xf),(uint)*(byte *)((int)piVar4 + -0xe),
              (uint)*(byte *)((int)piVar4 + -0xd),(uint)*(byte *)(piVar4 + -3),
              (uint)*(byte *)((int)piVar4 + -0xb),puVar7,puVar8,puVar9,puVar10,puVar11);
      sVar2 = strlen(param_2);
      sprintf(param_2 + sVar2,"%-4d",(uint)*(ushort *)(piVar4 + -1));
      sVar2 = strlen(param_2);
      sprintf(param_2 + sVar2,"%-4d",(uint)*(byte *)(piVar4 + -6));
      sVar2 = strlen(param_2);
      sprintf(param_2 + sVar2,"%-7d",(int)(char)piVar4[4]);
      sVar2 = strlen(param_2);
      sprintf(param_2 + sVar2,"%-7d",(int)*(char *)((int)piVar4 + 0x11));
      sVar2 = strlen(param_2);
      sprintf(param_2 + sVar2,"%-7d",(int)*(char *)((int)piVar4 + 0x12));
      sVar2 = strlen(param_2);
      uVar3 = get_phymode_str(*(byte *)((int)param_1 + iVar6 * 0x14c0 + 0xa1ddd) >> 5);
      sprintf(param_2 + sVar2,"%-10s",uVar3);
      sVar2 = strlen(param_2);
      uVar3 = get_bw_str(((uint)*(ushort *)(param_1 + iVar6 * 0x530 + 0x28777) << 0x17) >> 0x1e);
      sprintf(param_2 + sVar2,"%-6s",uVar3);
      sVar2 = strlen(param_2);
      sprintf(param_2 + sVar2,"%-6d",*(byte *)(param_1 + iVar6 * 0x530 + 0x28777) & 0x3f);
      sVar2 = strlen(param_2);
      sprintf(param_2 + sVar2,"%-6d",
              ((uint)*(byte *)((int)param_1 + iVar6 * 0x14c0 + 0xa1ddd) << 0x1e) >> 0x1f);
      sVar2 = strlen(param_2);
      sprintf(param_2 + sVar2,"%-6d",
              ((uint)*(byte *)((int)param_1 + iVar6 * 0x14c0 + 0xa1ddd) << 0x1d) >> 0x1f);
      sVar2 = strlen(param_2);
      iVar1 = piVar4[0x29e];
      iVar5 = piVar4[0x29d];
      if (iVar1 == 0) {
        uVar3 = 0;
      }
      else {
        uVar3 = __aeabi_uidiv((iVar1 - iVar5) * 100,iVar1);
      }
      sprintf(param_2 + sVar2,"%-10d, %d, %d%%\n",iVar5,iVar1,uVar3);
      sVar2 = strlen(param_2);
      (param_2 + sVar2)[0] = '\n';
      (param_2 + sVar2)[1] = '\0';
    }
    iVar6 = iVar6 + 1;
    piVar4 = piVar4 + 0x530;
  }
  return 1;
}

