// module: mt7915.ko
// function: printWcid @ 0x154a74
// size: 712 bytes
//

undefined4 printWcid(int param_1,char *param_2)

{
  ushort uVar1;
  int iVar2;
  size_t sVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  uint uVar7;
  int iVar8;
  int *piVar9;
  char *pcVar10;
  char acStack_8a [30];
  undefined1 auStack_6c [49];
  byte local_3b;
  byte local_39;
  char local_38;
  byte local_37;
  char local_36;
  byte local_35;
  byte local_34;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  sVar3 = strlen(param_2);
  pcVar10 = "====================";
  sprintf(param_2 + sVar3,"%s%-16s%s\n","===================="," WCID ","====================");
  uVar1 = *(ushort *)(param_1 + 0xa7c2ea);
  if (uVar1 == 0) {
    piVar6 = (int *)(param_1 + 0xa1d20);
    iVar8 = 0;
    piVar9 = (int *)0x0;
    while( true ) {
      iVar4 = HcGetMaxStaNum(param_1);
      if ((iVar4 <= iVar8) || ((piVar9 = piVar6, *piVar6 == 0x20001 && (piVar6[0x3f] == 2)))) break;
      piVar6 = piVar6 + 0x530;
      iVar8 = iVar8 + 1;
    }
  }
  else {
    uVar7 = HcGetMaxStaNum(param_1);
    if (uVar7 <= uVar1) {
      return 1;
    }
    piVar9 = (int *)((uint)*(ushort *)(param_1 + 0xa7c2ea) * 0x14c0 + param_1 + 0xa1d20);
  }
  if ((piVar9 != (int *)0x0) && ((*piVar9 == 0x20001 && (piVar9[0x3f] == 2)))) {
    sVar3 = strlen(param_2);
    sprintf(param_2 + sVar3,"%-32s= %d\n",&_LC63,(uint)*(ushort *)(piVar9 + 0x3e),pcVar10);
    sVar3 = strlen(param_2);
    sprintf(param_2 + sVar3,"%-32s= %02x:%02x:%02x:%02x:%02x:%02x\n","MAC Addr ",
            (uint)*(byte *)(piVar9 + 0x3b),(uint)*(byte *)((int)piVar9 + 0xed),
            (uint)*(byte *)((int)piVar9 + 0xee),(uint)*(byte *)((int)piVar9 + 0xef),
            (uint)*(byte *)(piVar9 + 0x3c),(uint)*(byte *)((int)piVar9 + 0xf1));
    snprintf(acStack_8a,0x1e,"%d %d %d %d",(int)(char)piVar9[0x43],
             (int)*(char *)((int)piVar9 + 0x10d),(int)*(char *)((int)piVar9 + 0x10e),
             (int)*(char *)((int)piVar9 + 0x10f));
    sVar3 = strlen(param_2);
    sprintf(param_2 + sVar3,"%-32s= %s\n","RSSI0/1/2/3 ",acStack_8a);
    iVar8 = piVar9[0x4e];
    uVar7 = piVar9[0x4d];
    if ((*(char *)(iVar2 + 0x150) == '\x01') && (*(char *)((int)piVar9 + 0xb7e) == '\x01')) {
      MtCmdGetTxStatistic(param_1,4,0,(short)piVar9[0x38],auStack_6c);
      uVar7 = (local_3b & 7) << 0xd | (local_37 & 3) << 7 | (uint)(local_36 != '\0') << 6 |
              (uint)(local_38 != '\0') << 9 | (local_39 & 1) << 10;
      if (((uVar7 << 0x10) >> 0x18 & 0xe0) == 0x80) {
        uVar5 = (uint)local_35 + (local_34 - 1 & 3) * 0x10;
      }
      else {
        uVar5 = (uint)local_35;
      }
      uVar7 = uVar7 | uVar5 & 0x3f;
    }
    iVar2 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
    if (iVar2 == 2) {
      StatRateToString(param_1,param_2,0,uVar7);
      StatRateToString(param_1,param_2,1,iVar8);
    }
  }
  return 1;
}

