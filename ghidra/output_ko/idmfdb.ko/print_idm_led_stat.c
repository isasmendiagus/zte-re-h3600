// module: idmfdb.ko
// function: print_idm_led_stat @ 0x122b8
// size: 488 bytes
//

int print_idm_led_stat(int *param_1,char *param_2,size_t param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined *puVar6;
  int iVar7;
  undefined *apuStack_30 [5];
  
  apuStack_30[3] = &DAT_00012fa8;
  apuStack_30[2] = &DAT_00012fa0;
  apuStack_30[1] = &DAT_00012f9c;
  apuStack_30[0] = &DAT_00012f98;
  if ((int)param_3 < 1) {
    iVar1 = 0;
LAB_00012384:
    iVar7 = param_1[3];
    if (iVar7 < 1) goto LAB_00012404;
  }
  else {
    iVar7 = param_1[5];
    puVar6 = apuStack_30[param_1[0xd] & 3];
    iVar1 = snprintf(param_2,param_3,"led %d, en %d, stat %s, total thoughput %dkbps\n",*param_1,
                     (uint)*(byte *)(param_1 + 1),puVar6,iVar7);
    if ((int)param_3 <= iVar1) goto LAB_00012384;
    uVar4 = wifi_led_func_name;
    if (*param_1 != 0) {
      uVar4 = wifi_led2_func_name;
    }
    iVar7 = snprintf(param_2 + iVar1,param_3 - iVar1,"   hw_call: %s  = %p\n",uVar4,param_1[0xf],
                     puVar6,iVar7);
    iVar1 = iVar1 + iVar7;
    if (iVar1 < (int)param_3) {
      iVar7 = snprintf(param_2 + iVar1,param_3 - iVar1,"   bind devs:");
      iVar1 = iVar1 + iVar7;
      goto LAB_00012384;
    }
    iVar7 = param_1[3];
    if (iVar7 < 1) {
      return iVar1;
    }
  }
  iVar5 = 0;
  do {
    if (-1 < *(int *)(param_1[2] + iVar5 * 4)) {
      uVar2 = get_node_index();
      if (((uVar2 < 0x11) && ((&fdb_list)[uVar2 * 0x128] != '\0')) &&
         ((&DAT_0001341c)[uVar2 * 0x4a] != 0)) {
        if (iVar1 < (int)param_3) {
          uVar2 = *(uint *)((&DAT_0001341c)[uVar2 * 0x4a] + 0x30) & 1;
        }
        else {
          uVar2 = 0;
        }
        if (uVar2 != 0) {
          iVar3 = snprintf(param_2 + iVar1,param_3 - iVar1," %s");
          iVar7 = param_1[3];
          iVar1 = iVar1 + iVar3;
          goto LAB_000123f8;
        }
      }
      iVar7 = param_1[3];
    }
LAB_000123f8:
    iVar5 = iVar5 + 1;
  } while (iVar5 < iVar7);
LAB_00012404:
  if (iVar1 < (int)param_3) {
    iVar7 = snprintf(param_2 + iVar1,param_3 - iVar1,"\n idm_ps_mode: %d",idm_ps_mode);
    iVar1 = iVar1 + iVar7;
    if (iVar1 < (int)param_3) {
      iVar7 = snprintf(param_2 + iVar1,param_3 - iVar1,"\n");
      return iVar1 + iVar7;
    }
  }
  return iVar1;
}

