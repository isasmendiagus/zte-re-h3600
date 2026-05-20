// module: mt7915.ko
// function: rtmp_read_pmf_parameters_from_file @ 0x21b36c
// size: 1080 bytes
//

void rtmp_read_pmf_parameters_from_file(int *param_1,undefined4 param_2,undefined4 param_3)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  char cVar6;
  int iVar7;
  undefined1 *puVar8;
  
  cVar6 = *(char *)((int)param_1 + 0x286285);
  if (cVar6 == '\x01') {
    iVar2 = *param_1;
    bVar1 = *(byte *)((int)param_1 + 0x2b7242);
    if (bVar1 != 0) {
      puVar8 = (undefined1 *)((int)param_1 + 0x2b7655);
      do {
        *puVar8 = 0;
        puVar8[2] = 0;
        puVar8[4] = 0;
        puVar8 = puVar8 + 0x5834;
      } while (puVar8 != (undefined1 *)((int)param_1 + (uint)bVar1 * 0x5834 + 0x2b7655));
    }
    iVar7 = RTMPGetKeyParameter("PMFMFPC",param_2,0x80,param_3,1);
    if (((iVar7 != 0) && (iVar7 = rstrtok(param_2,&_LC48), iVar7 != 0)) &&
       (*(char *)((int)param_1 + 0x2b7242) != '\0')) {
      iVar7 = 0;
      do {
        *(int *)(iVar2 + 0x3c) = iVar7;
        Set_PMFMFPC_Proc(param_1);
        iVar3 = rstrtok(0,&_LC48);
        iVar7 = iVar7 + 1;
        if (iVar3 == 0) break;
      } while (iVar7 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
    }
    iVar7 = RTMPGetKeyParameter("PMFMFPR",param_2,0x80,param_3,1);
    if (((iVar7 != 0) && (iVar7 = rstrtok(param_2,&_LC48), iVar7 != 0)) &&
       (*(char *)((int)param_1 + 0x2b7242) != '\0')) {
      iVar7 = 0;
      do {
        *(int *)(iVar2 + 0x3c) = iVar7;
        Set_PMFMFPR_Proc(param_1);
        iVar3 = rstrtok(0,&_LC48);
        iVar7 = iVar7 + 1;
        if (iVar3 == 0) break;
      } while (iVar7 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
    }
    iVar7 = RTMPGetKeyParameter("PMFSHA256",param_2,0x80,param_3,1);
    if (((iVar7 != 0) && (iVar7 = rstrtok(param_2,&_LC48), iVar7 != 0)) &&
       (*(char *)((int)param_1 + 0x2b7242) != '\0')) {
      iVar7 = 0;
      do {
        *(int *)(iVar2 + 0x3c) = iVar7;
        Set_PMFSHA256_Proc(param_1);
        iVar3 = rstrtok(0,&_LC48);
        iVar7 = iVar7 + 1;
        if (iVar3 == 0) break;
      } while (iVar7 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
    }
    cVar6 = *(char *)((int)param_1 + 0x286285);
  }
  if (cVar6 == '\0') {
    iVar7 = *param_1;
    iVar2 = rstrtok(param_2,&_LC48);
    if (iVar2 != 0) {
      *(undefined1 *)((int)param_1 + 0x36df65) = 0;
      *(undefined1 *)((int)param_1 + 0x36df67) = 0;
      *(undefined1 *)((int)param_1 + 0x36df69) = 0;
      iVar2 = rstrtok(0,&_LC48);
      if (iVar2 != 0) {
        *(undefined1 *)((int)param_1 + 0x581715) = 0;
        *(undefined1 *)((int)param_1 + 0x581717) = 0;
        *(undefined1 *)((int)param_1 + 0x581719) = 0;
        rstrtok(0,&_LC48);
      }
    }
    iVar2 = RTMPGetKeyParameter("PMFMFPC",param_2,0x80,param_3,1);
    if ((iVar2 != 0) && (iVar2 = rstrtok(param_2,&_LC48), iVar2 != 0)) {
      uVar5 = 0;
      do {
        *(uint *)(iVar7 + 0x3c) = uVar5;
        Set_PMFMFPC_Proc(param_1,iVar2);
        iVar2 = rstrtok(0,&_LC48);
        uVar4 = uVar5 ^ 1;
        uVar5 = 1;
        if (iVar2 == 0) {
          uVar4 = 0;
        }
      } while (uVar4 != 0);
    }
    iVar2 = RTMPGetKeyParameter("PMFMFPR",param_2,0x80,param_3,1);
    if ((iVar2 != 0) && (iVar2 = rstrtok(param_2,&_LC48), iVar2 != 0)) {
      uVar5 = 0;
      do {
        *(uint *)(iVar7 + 0x3c) = uVar5;
        Set_PMFMFPR_Proc(param_1,iVar2);
        iVar2 = rstrtok(0,&_LC48);
        uVar4 = uVar5 ^ 1;
        uVar5 = 1;
        if (iVar2 == 0) {
          uVar4 = 0;
        }
      } while (uVar4 != 0);
    }
    iVar2 = RTMPGetKeyParameter("PMFSHA256",param_2,0x80,param_3,1);
    if ((iVar2 != 0) && (iVar2 = rstrtok(param_2,&_LC48), iVar2 != 0)) {
      uVar5 = 0;
      do {
        *(uint *)(iVar7 + 0x3c) = uVar5;
        Set_PMFSHA256_Proc(param_1,iVar2);
        iVar2 = rstrtok(0,&_LC48);
        uVar4 = uVar5 ^ 1;
        uVar5 = 1;
        if (iVar2 == 0) {
          uVar4 = 0;
        }
      } while (uVar4 != 0);
      return;
    }
  }
  return;
}

