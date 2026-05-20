// module: mt7915.ko
// function: create_sku_file @ 0x150ce0
// size: 692 bytes
//

undefined4 create_sku_file(int param_1)

{
  byte bVar1;
  char *pcVar2;
  char cVar3;
  undefined1 uVar4;
  char *pcVar5;
  int iVar6;
  size_t sVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar10;
  char *pcVar11;
  int iVar12;
  char *local_34;
  undefined2 local_2e;
  undefined2 local_2c;
  undefined2 local_2a;
  
  local_2e = 0;
  local_2c = 0;
  local_2a = 0;
  local_34 = (char *)0x0;
  if (((sku == (char *)0x0) && (os_alloc_mem(param_1,&sku,42000), sku == (char *)0x0)) ||
     (os_alloc_mem(param_1,&local_34,42000), local_34 == (char *)0x0)) {
    uVar9 = 0xffffffff;
  }
  else {
    os_zero_mem(sku,42000);
    iVar12 = 0;
    os_zero_mem(local_34,42000);
    strcpy(local_34,Sku_01);
    pcVar11 = local_34;
    while (pcVar5 = os_str_chr(pcVar11,9), pcVar5 != (char *)0x0) {
      *pcVar5 = '\0';
      if (*pcVar11 == '#') {
        strcat(sku,pcVar11);
LAB_00150f10:
        pcVar11 = sku;
        sVar7 = strlen(sku);
        (pcVar11 + sVar7)[0] = '\t';
        (pcVar11 + sVar7)[1] = '\0';
      }
      else {
        iVar6 = strncmp(pcVar11,"Band: ",6);
        if (iVar6 == 0) {
          strcat(sku,pcVar11);
          pcVar2 = sku;
          sVar7 = strlen(sku);
          (pcVar2 + sVar7)[0] = '\t';
          (pcVar2 + sVar7)[1] = '\0';
          iVar6 = rstrtok(pcVar11 + 6,&_LC3);
          if (iVar6 != 0) {
            cVar3 = os_str_tol(iVar6,0,10);
            if (cVar3 == '\x02') {
              iVar12 = 2;
            }
            else if (cVar3 == '\x05') {
              iVar12 = 1;
            }
            goto LAB_00150d6c;
          }
        }
        else {
LAB_00150d6c:
          iVar6 = strncmp(pcVar11,"Ch",2);
          if ((iVar6 == 0) && (iVar6 = rstrtok(pcVar11 + 2,&_LC3), iVar6 != 0)) {
            strcat(sku,pcVar11);
            pcVar11 = sku;
            sVar7 = strlen(sku);
            (pcVar11 + sVar7)[0] = ' ';
            (pcVar11 + sVar7)[1] = '\0';
            uVar4 = os_str_tol(iVar6,0,10);
            if (iVar12 == 1) {
              iVar6 = GetChannelLimitPwr(param_1,uVar4);
              bVar1 = *(byte *)(param_1 + 0xa7d194);
              cVar3 = *(char *)(param_1 + 0xa7d195);
            }
            else {
              iVar6 = GetCountryLimtPwr(param_1);
              bVar1 = *(byte *)(param_1 + 0xa7d170);
              cVar3 = *(char *)(param_1 + 0xa7d171);
            }
            if (cVar3 == 0x7f) {
              iVar10 = 3;
            }
            else {
              iVar10 = (int)cVar3 / 2;
            }
            iVar8 = rstrtok(0,&_LC3);
            while (iVar8 != 0) {
              snprintf((char *)&local_2e,6,"%2d ",(iVar6 - (uint)(bVar1 >> 1)) - iVar10);
              strcat(sku,(char *)&local_2e);
              iVar8 = rstrtok(0,&_LC3);
            }
            goto LAB_00150f10;
          }
        }
      }
      pcVar11 = pcVar5 + 1;
    }
    os_free_mem(local_34);
    uVar9 = 0;
  }
  return uVar9;
}

