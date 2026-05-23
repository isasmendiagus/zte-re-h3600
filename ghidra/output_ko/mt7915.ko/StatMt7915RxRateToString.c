// module: mt7915.ko
// function: StatMt7915RxRateToString @ 0xbdb98
// size: 1324 bytes
//

void StatMt7915RxRateToString(undefined4 param_1,char *param_2,uint param_3)

{
  char cVar1;
  undefined2 uVar2;
  size_t sVar3;
  int iVar4;
  char *__src;
  int iVar5;
  undefined4 uVar6;
  undefined4 *puVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  bool bVar14;
  bool bVar15;
  char *apcStack_80 [4];
  undefined *puStack_70;
  char *pcStack_6c;
  char *apcStack_68 [4];
  char *apcStack_58 [13];
  
  apcStack_58[0] = "CCK";
  apcStack_58[1] = &_LC7;
  apcStack_58[2] = "HT_MM";
  apcStack_58[3] = "HT_GF";
  uVar10 = (param_3 << 10) >> 0x18;
  uVar11 = (param_3 << 0x10) >> 0x18;
  uVar12 = (param_3 << 0x18) >> 0x1d;
  apcStack_58[4] = &_LC10;
  apcStack_58[5] = &_LC25;
  apcStack_58[6] = &DAT_002d1c64;
  apcStack_58[7] = &DAT_002d1c6c;
  uVar8 = (param_3 << 0xc) >> 0x1c;
  iVar13 = -((int)(param_3 << 0x1b) >> 0x1f);
  apcStack_58[8] = "HE_SU";
  apcStack_58[9] = "HE_EXT_SU";
  apcStack_58[10] = "HE_TRIG";
  apcStack_58[0xb] = "HE_MU";
  apcStack_80[0] = "BCC";
  apcStack_80[1] = &DAT_002d1c4c;
  apcStack_80[2] = &DAT_002d1c24;
  apcStack_80[3] = &DAT_002d1c2c;
  puStack_70 = &DAT_002d1c34;
  pcStack_6c = "BW160/8080";
  apcStack_68[0] = "0.8us";
  apcStack_68[1] = "1.6us";
  apcStack_68[2] = "3.2us";
  apcStack_68[3] = &_LC35;
  sVar3 = strlen(param_2);
  builtin_strncpy(param_2 + sVar3,"Last RX Rate\t\t\t\t\t= ",0x14);
  if (0xb < uVar8) {
    sprintf(param_2 + sVar3 + 0x13,"Undefined for %d\n",uVar8);
    return;
  }
  if (uVar8 == 0) {
    uVar11 = uVar11 & 7;
    if (uVar11 == 0) {
      builtin_strncpy(param_2 + sVar3 + 0x13,"1M LP, ",8);
    }
    else if (uVar11 == 1) {
      builtin_strncpy(param_2 + sVar3 + 0x13,"2M LP, ",8);
    }
    else if (uVar11 == 2) {
      builtin_strncpy(param_2 + sVar3 + 0x13,"5M LP, ",8);
    }
    else if (uVar11 == 3) {
      puVar7 = &_LC284;
LAB_000bde9c:
      uVar6 = puVar7[1];
      cVar1 = *(char *)(puVar7 + 2);
      *(undefined4 *)(param_2 + sVar3 + 0x13) = *puVar7;
      *(undefined4 *)(param_2 + sVar3 + 0x17) = uVar6;
      param_2[sVar3 + 0x1b] = cVar1;
    }
    else if (uVar11 == 5) {
      builtin_strncpy(param_2 + sVar3 + 0x13,"2M SP, ",8);
    }
    else if (uVar11 == 6) {
      builtin_strncpy(param_2 + sVar3 + 0x13,"5M SP, ",8);
    }
    else {
      if (uVar11 == 7) {
        puVar7 = &_LC287;
        goto LAB_000bde9c;
      }
LAB_000bdca4:
      builtin_strncpy(param_2 + sVar3 + 0x13,"unknown, ",10);
    }
LAB_000bdcc8:
    sVar3 = strlen(param_2);
    sprintf(param_2 + sVar3,"%s, ",apcStack_80[uVar12 + 2]);
LAB_000bdcf0:
    sVar3 = strlen(param_2);
    strcpy(param_2 + sVar3,apcStack_58[uVar8]);
    if (uVar8 < 2) goto LAB_000bdd5c;
  }
  else {
    if (uVar8 == 1) {
      uVar11 = uVar11 & 0xf;
      if (uVar11 == 0xb) {
        puVar7 = &_LC289;
      }
      else {
        if (uVar11 != 0xf) {
          if (uVar11 == 10) {
            puVar7 = &_LC291;
          }
          else if (uVar11 == 0xe) {
            puVar7 = &_LC292;
          }
          else if (uVar11 == 9) {
            puVar7 = &_LC293;
          }
          else if (uVar11 == 0xd) {
            puVar7 = &_LC294;
          }
          else if (uVar11 == 8) {
            puVar7 = &_LC295;
          }
          else {
            if (uVar11 != 0xc) goto LAB_000bdca4;
            puVar7 = &_LC296;
          }
          uVar2 = *(undefined2 *)(puVar7 + 1);
          *(undefined4 *)(param_2 + sVar3 + 0x13) = *puVar7;
          *(undefined2 *)(param_2 + sVar3 + 0x17) = uVar2;
          goto LAB_000bdcc8;
        }
        puVar7 = &_LC290;
      }
      cVar1 = *(char *)(puVar7 + 1);
      *(undefined4 *)(param_2 + sVar3 + 0x13) = *puVar7;
      param_2[sVar3 + 0x17] = cVar1;
      goto LAB_000bdcc8;
    }
    uVar9 = uVar8 - 2 & 0xff;
    if (uVar9 < 2) {
      sprintf(param_2 + sVar3 + 0x13,"MCS%d, ",uVar11 & 0x3f);
      sVar3 = strlen(param_2);
      sprintf(param_2 + sVar3,"%s, ",apcStack_80[uVar12 + 2]);
LAB_000bdefc:
      sVar3 = strlen(param_2);
      if ((uVar10 & 1) == 0) {
        uVar6 = 0x4c;
      }
      else {
        uVar6 = 0x53;
      }
      sprintf(param_2 + sVar3,"%cGI, ",uVar6);
      goto LAB_000bdcf0;
    }
    iVar4 = (param_3 & 7) + 1;
    uVar11 = uVar11 & 0xf;
    iVar5 = iVar13 + 1;
    if (uVar8 == 4 && 9 < uVar11) {
LAB_000bddd8:
      uVar6 = __aeabi_idiv(iVar4,iVar5);
      sprintf(param_2 + sVar3 + 0x13,"Incorrect NSS%d_MCS%d, ",uVar6,uVar11);
    }
    else {
      bVar15 = 10 < uVar11;
      bVar14 = uVar11 == 0xb;
      if (0xb < uVar11) {
        bVar15 = 3 < uVar8;
        bVar14 = uVar8 == 4;
      }
      if (bVar15 && !bVar14) goto LAB_000bddd8;
      uVar6 = __aeabi_idiv(iVar4,iVar5);
      sprintf(param_2 + sVar3 + 0x13,"NSS%d_MCS%d, ",uVar6,uVar11);
    }
    sVar3 = strlen(param_2);
    sprintf(param_2 + sVar3,"%s, ",apcStack_80[uVar12 + 2]);
    if (uVar9 < 3) goto LAB_000bdefc;
    sVar3 = strlen(param_2);
    sprintf(param_2 + sVar3,"%s GI, ",apcStack_68[uVar10 & 3]);
    sVar3 = strlen(param_2);
    strcpy(param_2 + sVar3,apcStack_58[uVar8]);
  }
  sVar3 = strlen(param_2);
  __src = ", STBC, ";
  if (iVar13 == 0) {
    __src = ", ";
  }
  strcpy(param_2 + sVar3,__src);
  sVar3 = strlen(param_2);
  strcpy(param_2 + sVar3,apcStack_80[-((int)(param_3 << 0x1c) >> 0x1f)]);
LAB_000bdd5c:
  sVar3 = strlen(param_2);
  (param_2 + sVar3)[0] = '\n';
  (param_2 + sVar3)[1] = '\0';
  return;
}

