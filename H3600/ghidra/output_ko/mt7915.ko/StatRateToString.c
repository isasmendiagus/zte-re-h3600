// module: mt7915.ko
// function: StatRateToString @ 0xbd674
// size: 1312 bytes
//

void StatRateToString(int param_1,char *param_2,int param_3,uint param_4)

{
  char cVar1;
  size_t sVar2;
  undefined4 uVar3;
  char *pcVar4;
  undefined4 *puVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  char *apcStack_60 [6];
  char *apcStack_48 [7];
  char *pcStack_2c;
  
  apcStack_48[0] = "CCK";
  apcStack_48[1] = &_LC7;
  apcStack_48[2] = &DAT_002d1c98;
  apcStack_48[3] = &DAT_002d1c9c;
  uVar9 = (param_4 << 0x17) >> 0x1e;
  apcStack_48[4] = &_LC10;
  apcStack_48[5] = "HE_SU";
  apcStack_48[6] = "HE_EXT_SU";
  pcStack_2c = "HE_MU";
  uVar8 = *(uint *)(param_1 + 0x795124);
  apcStack_60[0] = "BCC";
  apcStack_60[1] = &DAT_002d1c4c;
  uVar6 = (param_4 << 0x10) >> 0x1d;
  uVar7 = param_4 & 0x3f;
  apcStack_60[2] = &DAT_002d1c24;
  apcStack_60[3] = &DAT_002d1c2c;
  apcStack_60[4] = &DAT_002d1c34;
  apcStack_60[5] = "BW160/8080";
  if ((uVar9 == 0) || (uVar9 == 1)) {
    if (param_3 == 0) goto LAB_000bd860;
LAB_000bd714:
    sVar2 = strlen(param_2);
    builtin_strncpy(param_2 + sVar2,"Last RX Rate\t\t\t\t\t= ",0x14);
    if (uVar6 == 0) goto joined_r0x000bd8bc;
    if (uVar6 != 1) {
LAB_000bd8cc:
      if (uVar6 < 4) {
        sVar2 = strlen(param_2);
        sprintf(param_2 + sVar2,"MCS%d, ",uVar7);
      }
      else {
        sVar2 = strlen(param_2);
        sprintf(param_2 + sVar2,"NSS%d_MCS%d, ",((param_4 << 0x1a) >> 0x1e) + 1,param_4 & 0xf);
      }
      goto LAB_000bd7b0;
    }
LAB_000bd910:
    if (uVar7 == 0xb) {
      sVar2 = strlen(param_2);
      builtin_strncpy(param_2 + sVar2,"6M, ",5);
      goto LAB_000bd7b0;
    }
    if (uVar7 == 0xf) {
      sVar2 = strlen(param_2);
      builtin_strncpy(param_2 + sVar2,"9M, ",5);
      goto LAB_000bd7b0;
    }
    if (uVar7 == 10) {
      sVar2 = strlen(param_2);
      builtin_strncpy(param_2 + sVar2,"12M, ",6);
      goto LAB_000bd7b0;
    }
    if (uVar7 == 0xe) {
      sVar2 = strlen(param_2);
      builtin_strncpy(param_2 + sVar2,"18M, ",6);
      goto LAB_000bd7b0;
    }
    if (uVar7 == 9) {
      sVar2 = strlen(param_2);
      builtin_strncpy(param_2 + sVar2,"24M, ",6);
      goto LAB_000bd7b0;
    }
    if (uVar7 == 0xd) {
      sVar2 = strlen(param_2);
      builtin_strncpy(param_2 + sVar2,"36M, ",6);
      goto LAB_000bd7b0;
    }
    if (uVar7 == 8) {
      sVar2 = strlen(param_2);
      builtin_strncpy(param_2 + sVar2,"48M, ",6);
      goto LAB_000bd7b0;
    }
    if (uVar7 == 0xc) {
      sVar2 = strlen(param_2);
      builtin_strncpy(param_2 + sVar2,"54M, ",6);
      goto LAB_000bd7b0;
    }
LAB_000bd788:
    sVar2 = strlen(param_2);
    puVar5 = &_LC288;
    pcVar4 = param_2 + sVar2;
  }
  else {
    if (uVar9 == 2) {
      uVar9 = 2;
    }
    else {
      uVar9 = 3;
    }
    if (param_3 != 0) goto LAB_000bd714;
LAB_000bd860:
    sVar2 = strlen(param_2);
    builtin_strncpy(param_2 + sVar2,"Last TX Rate\t\t\t\t\t= ",0x14);
    if (uVar6 != 0) {
      if (uVar6 == 1) {
        uVar7 = (uint)*(byte *)((int)&tmi_rate_map_ofdm + uVar7);
        goto LAB_000bd910;
      }
      goto LAB_000bd8cc;
    }
    if ((uVar8 & 0x10) == 0) {
      puVar5 = &tmi_rate_map_cck_lp;
    }
    else {
      puVar5 = (undefined4 *)&tmi_rate_map_cck_sp;
    }
    uVar7 = (uint)*(byte *)((int)puVar5 + uVar7);
joined_r0x000bd8bc:
    if (uVar7 == 0) {
      sVar2 = strlen(param_2);
      builtin_strncpy(param_2 + sVar2,"1M LP, ",8);
      goto LAB_000bd7b0;
    }
    if (uVar7 == 1) {
      sVar2 = strlen(param_2);
      builtin_strncpy(param_2 + sVar2,"2M LP, ",8);
      goto LAB_000bd7b0;
    }
    if (uVar7 == 2) {
      sVar2 = strlen(param_2);
      builtin_strncpy(param_2 + sVar2,"5M LP, ",8);
      goto LAB_000bd7b0;
    }
    if (uVar7 == 3) {
      sVar2 = strlen(param_2);
      puVar5 = &_LC284;
      pcVar4 = param_2 + sVar2;
    }
    else {
      if (uVar7 == 5) {
        sVar2 = strlen(param_2);
        builtin_strncpy(param_2 + sVar2,"2M SP, ",8);
        goto LAB_000bd7b0;
      }
      if (uVar7 == 6) {
        sVar2 = strlen(param_2);
        builtin_strncpy(param_2 + sVar2,"5M SP, ",8);
        goto LAB_000bd7b0;
      }
      if (uVar7 != 7) goto LAB_000bd788;
      sVar2 = strlen(param_2);
      puVar5 = &_LC287;
      pcVar4 = param_2 + sVar2;
    }
  }
  uVar3 = puVar5[1];
  cVar1 = *(char *)(puVar5 + 2);
  *(undefined4 *)(param_2 + sVar2) = *puVar5;
  *(undefined4 *)(pcVar4 + 4) = uVar3;
  pcVar4[8] = cVar1;
LAB_000bd7b0:
  sVar2 = strlen(param_2);
  sprintf(param_2 + sVar2,"%s, ",apcStack_60[uVar9 + 2]);
  sVar2 = strlen(param_2);
  if ((int)(param_4 << 0x16) < 0) {
    uVar3 = 0x53;
  }
  else {
    uVar3 = 0x4c;
  }
  sprintf(param_2 + sVar2,"%cGI, ",uVar3);
  sVar2 = strlen(param_2);
  pcVar4 = ", STBC";
  if ((param_4 & 0x400) == 0) {
    pcVar4 = " ";
  }
  sprintf(param_2 + sVar2,"%s%s %s\n",apcStack_48[uVar6],pcVar4,
          apcStack_60[-((int)(param_4 << 0x19) >> 0x1f)]);
  return;
}

