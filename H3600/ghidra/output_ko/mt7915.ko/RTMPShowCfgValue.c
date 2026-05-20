// module: mt7915.ko
// function: RTMPShowCfgValue @ 0xea2f8
// size: 288 bytes
//

undefined4 RTMPShowCfgValue(undefined4 param_1,char *param_2,char *param_3,uint param_4)

{
  int iVar1;
  size_t sVar2;
  size_t sVar3;
  uint extraout_r3;
  uint uVar4;
  int *piVar5;
  char *pcVar6;
  undefined4 uVar7;
  uint uVar8;
  
  DAT_005f362c = (int *)&DAT_0032fffc;
  uVar4 = param_4;
  uVar8 = param_4;
  piVar5 = DAT_005f362c;
  pcVar6 = DAT_0032fffc;
  do {
    if (pcVar6 == (char *)0x0) {
      uVar7 = 0;
      DAT_005f362c = piVar5;
LAB_000ea39c:
      snprintf(param_3,param_4,"\n",uVar4,uVar8);
      DAT_005f362c = (int *)&DAT_0032fffc;
      pcVar6 = DAT_0032fffc;
      while( true ) {
        if (pcVar6 == (char *)0x0) {
          return uVar7;
        }
        sVar2 = strlen(param_3);
        sVar3 = strlen(pcVar6);
        if (param_4 <= sVar3 + sVar2) break;
        sprintf(param_3,"%s%s\n",param_3,pcVar6);
        pcVar6 = (char *)DAT_005f362c[2];
        DAT_005f362c = DAT_005f362c + 2;
      }
      return uVar7;
    }
    DAT_005f362c = piVar5;
    iVar1 = strcmp(param_2,pcVar6);
    if (iVar1 == 0) {
      iVar1 = (*(code *)piVar5[1])(param_1,param_3,param_4);
      if (iVar1 == 0) {
        uVar7 = 0;
      }
      else {
        uVar7 = 0xffffffea;
      }
      uVar4 = 0;
      if (*DAT_005f362c != 0) {
        return uVar7;
      }
      goto LAB_000ea39c;
    }
    piVar5 = piVar5 + 2;
    pcVar6 = (char *)*piVar5;
    uVar4 = extraout_r3;
  } while( true );
}

