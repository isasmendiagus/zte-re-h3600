// module: mt7915.ko
// function: WNMCtrlInit @ 0x2285cc
// size: 440 bytes
//

void WNMCtrlInit(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  char cVar8;
  
  uVar7 = 0;
  cVar8 = '\x01';
  while( true ) {
    uVar3 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    uVar4 = uVar7 & 0xff;
    iVar5 = uVar4 * 0x5834;
    uVar7 = uVar7 + 1;
    iVar6 = param_1 + iVar5;
    if (uVar3 <= uVar4) break;
    cVar2 = "RT_OID_WSC_SET_MODE::unknown WscMode = %d\n"[iVar6 + 0xe];
    if (cVar2 != '\0') {
      cVar8 = cVar2;
    }
    __memzero("RT_OID_WSC_SET_CONF_MODE:: WscConfMode = %d\n" + iVar6 + 0x10,0x5c,0x5834,cVar2,
              param_4);
    pcVar1 = "RT_OID_WSC_SET_CONF_MODE:: WscConfMode = %d\n" + iVar6 + 0x20;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    pcVar1 = "RT_OID_WSC_SET_CONF_MODE:: WscConfMode = %d\n" + iVar6 + 0x24;
    pcVar1[0] = '\x01';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    *(char **)("RT_OID_WSC_SET_CONF_MODE:: WscConfMode = %d\n" + iVar6 + 0x28) =
         "RT_OID_WSC_SET_CONF_MODE:: WscConfMode = %d\n" + param_1 + iVar5 + 0x28;
    *(char **)("RT_OID_WSC_SET_CONF_MODE:: WscConfMode = %d\n" + iVar6 + 0x2c) =
         "RT_OID_WSC_SET_CONF_MODE:: WscConfMode = %d\n" + param_1 + iVar5 + 0x28;
    pcVar1 = "RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar6 + 0x10;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    pcVar1 = "RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar6 + 0x14;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    *(char **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar6 + 0x28) =
         "RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + param_1 + iVar5 + 0x28;
    *(char **)("RT_OID_WSC_SET_MODE::WscMode = %d\n" + iVar6) =
         "RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + param_1 + iVar5 + 0x28;
    *(char **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar6 + 0x18) =
         "RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + param_1 + iVar5 + 0x18;
    *(char **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar6 + 0x1c) =
         "RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + param_1 + iVar5 + 0x18;
    *(char **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar6 + 0x20) =
         "RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + param_1 + iVar5 + 0x20;
    *(char **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar6 + 0x24) =
         "RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + param_1 + iVar5 + 0x20;
    "RT_OID_WSC_SET_MODE::unknown WscMode = %d\n"[iVar6 + 0xe] = cVar8;
  }
  __memzero(param_1 + 0x580ddc,0x5c,0x5834,uVar4,param_4);
  (&DAT_00580e0e)[param_1] = cVar8;
  *(undefined4 *)(&DAT_00580dec + param_1) = 0;
  *(undefined4 *)(&DAT_00580df0 + param_1) = 1;
  *(undefined **)(&DAT_00580df4 + param_1) = &DAT_00580df4 + param_1;
  *(undefined **)(&DAT_00580df8 + param_1) = &DAT_00580df4 + param_1;
  *(undefined **)(&DAT_00580e28 + param_1) = &DAT_00580e28 + param_1;
  *(undefined **)(&DAT_00580e2c + param_1) = &DAT_00580e28 + param_1;
  __memzero(param_1 + 0x79458c,0x5c);
  *(undefined4 *)(param_1 + 0x79459c) = 0;
  *(undefined4 *)(param_1 + 0x7945a0) = 1;
  *(char *)(param_1 + 0x7945be) = cVar8;
  *(int *)(param_1 + 0x7945a4) = param_1 + 0x7945a4;
  *(int *)(param_1 + 0x7945a8) = param_1 + 0x7945a4;
  *(int *)(param_1 + 0x7945d8) = param_1 + 0x7945d8;
  *(int *)(param_1 + 0x7945dc) = param_1 + 0x7945d8;
  return;
}

