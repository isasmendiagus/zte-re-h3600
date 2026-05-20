// module: mt7915.ko
// function: MtParsePwrLimitTable @ 0x151cb8
// size: 924 bytes
//

undefined4 MtParsePwrLimitTable(int param_1,char *param_2,int param_3)

{
  undefined1 uVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  undefined4 uVar5;
  char *pcVar6;
  int *piVar7;
  uint unaff_r7;
  char local_33;
  undefined1 local_32 [2];
  void *local_30;
  int *local_2c [2];
  
  piVar7 = (int *)0x0;
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_2 != (char *)0x0) {
    unaff_r7 = 0;
  }
  local_32[0] = *(undefined1 *)(iVar2 + 0x1fb);
  local_32[1] = *(undefined1 *)(iVar2 + 0x1ff);
  local_2c[0] = (int *)0x0;
  if (param_2 != (char *)0x0) {
    while (pcVar3 = os_str_chr(param_2,9), pcVar3 != (char *)0x0) {
      *pcVar3 = '\0';
      if (*param_2 != '#') {
        iVar2 = strncmp(param_2,"Band: ",6);
        if (iVar2 == 0) {
          iVar2 = rstrtok(param_2 + 6,&_LC3);
          if (iVar2 == 0) goto LAB_00151d24;
          uVar4 = os_str_tol(iVar2,0,10);
          unaff_r7 = uVar4 & 0xff;
          if (unaff_r7 == 2) {
            unaff_r7 = 0;
            if (3 < DebugLevel) {
              pcVar6 = "CH_G_BAND";
              goto LAB_00151dd0;
            }
          }
          else if (unaff_r7 == 5) {
            if (3 < DebugLevel) {
              unaff_r7 = 1;
              pcVar6 = "CH_A_BAND";
              goto LAB_00151dd0;
            }
            unaff_r7 = 1;
          }
          else if (3 < DebugLevel) {
            pcVar6 = "CH_G_BAND";
            if (unaff_r7 != 0) {
              pcVar6 = "CH_A_BAND";
            }
LAB_00151dd0:
            printk("ChBand: %s\n",pcVar6);
          }
        }
        iVar2 = strncmp(param_2,"Ch",2);
        if (iVar2 == 0) {
          os_alloc_mem(param_1,local_2c,0x18);
          if (local_2c[0] == (int *)0x0) goto LAB_00151fd8;
          os_zero_mem(local_2c[0],0x18);
          uVar1 = local_32[param_3];
          os_alloc_mem(param_1,local_2c[0] + 5,uVar1);
          if (local_2c[0][5] == 0) {
            os_free_mem(local_2c[0]);
            goto LAB_00151fd8;
          }
          os_zero_mem(local_2c[0][5],uVar1);
          iVar2 = rstrtok(param_2 + 2,&_LC3);
          if (iVar2 == 0) {
            os_free_mem(local_2c[0][5]);
            os_free_mem(local_2c[0]);
            goto LAB_00151d24;
          }
          uVar1 = os_str_tol(iVar2,0,10);
          *(char *)(local_2c[0] + 4) = (char)unaff_r7;
          *(undefined1 *)(local_2c[0] + 2) = uVar1;
          MtPwrLimitParse(param_1,local_2c[0][5],unaff_r7,param_3);
          if (piVar7 == (int *)0x0) {
            if (param_3 == 0) goto LAB_00151ee0;
LAB_00151f6c:
            piVar7 = local_2c[0];
            if (param_3 != 1) goto LAB_00151f00;
            piVar7 = *(int **)(param_1 + 0xa78638);
LAB_00151eec:
            *local_2c[0] = *piVar7;
            local_2c[0][1] = (int)piVar7;
            *(int **)(*piVar7 + 4) = local_2c[0];
            *piVar7 = (int)local_2c[0];
            piVar7 = local_2c[0];
          }
          else {
            local_33 = '\x01';
            MtPwrLimitSimilarCheck(param_1,piVar7[5],local_2c[0][5],&local_33,unaff_r7,param_3);
            if (local_33 == '\0') {
LAB_00151ed8:
              if (param_3 != 0) goto LAB_00151f6c;
LAB_00151ee0:
              piVar7 = *(int **)(param_1 + 0xa78630);
              goto LAB_00151eec;
            }
            if ((char)piVar7[4] != (char)local_2c[0][4]) {
              local_33 = '\0';
              goto LAB_00151ed8;
            }
            os_free_mem(local_2c[0][5]);
            os_free_mem(local_2c[0]);
          }
LAB_00151f00:
          *(char *)((int)piVar7 + 9) = *(char *)((int)piVar7 + 9) + '\x01';
          os_alloc_mem(param_1,&local_30);
          if (local_30 == (void *)0x0) {
            os_free_mem(local_2c[0][5]);
            os_free_mem(local_2c[0]);
            goto LAB_00151fd8;
          }
          if ((void *)piVar7[3] != (void *)0x0) {
            os_move_mem(local_30,(void *)piVar7[3],*(byte *)((int)piVar7 + 9) - 1);
            os_free_mem(piVar7[3]);
          }
          piVar7[3] = (int)local_30;
          *(undefined1 *)((int)local_30 + (*(byte *)((int)piVar7 + 9) - 1)) = uVar1;
        }
      }
LAB_00151d24:
      param_2 = pcVar3 + 1;
    }
    uVar5 = 0;
  }
  else {
LAB_00151fd8:
    if (DebugLevel < 0) {
      uVar5 = 1;
    }
    else {
      printk("%s: null pointer when parsing power limit table !!\n","MtParsePwrLimitTable");
      uVar5 = 1;
    }
  }
  return uVar5;
}

