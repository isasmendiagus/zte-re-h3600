// module: mt7915.ko
// function: Get_RBIST_IQ_Data_Proc @ 0xeb3d4
// size: 764 bytes
//

undefined4 Get_RBIST_IQ_Data_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  code *pcVar7;
  int local_2c;
  int *local_28;
  char *local_24 [2];
  
  uVar5 = 0;
  local_2c = 0;
  local_28 = (int *)0x0;
  local_24[0] = (char *)0x0;
  iVar1 = rstrtok(param_2,&_LC232);
  if (iVar1 == 0) {
    uVar5 = 0;
    iVar6 = 0;
  }
  else {
    iVar6 = 0;
    iVar4 = 0;
    do {
      if (iVar4 == 1) {
LAB_000eb450:
        uVar5 = simple_strtol(iVar1,0,10);
        iVar1 = rstrtok(0,&_LC232);
        if (iVar1 == 0) break;
LAB_000eb478:
        uVar2 = simple_strtol(iVar1,0,10);
        iVar4 = 2;
        *(undefined4 *)(param_1 + 0xa78a7c) = uVar2;
      }
      else {
        if (iVar4 == 2) goto LAB_000eb478;
        if (iVar4 == 0) {
          iVar6 = simple_strtol(iVar1,0,10);
          iVar1 = rstrtok(0,&_LC232);
          if (iVar1 != 0) goto LAB_000eb450;
          break;
        }
      }
      iVar4 = iVar4 + 1;
      iVar1 = rstrtok(0,&_LC232);
    } while (iVar1 != 0);
  }
  iVar1 = os_alloc_mem(param_1,local_24,0x20);
  if (iVar1 == 0) {
    os_zero_mem(local_24[0],0x20);
    iVar1 = os_alloc_mem(param_1,&local_2c,0x400);
    if (iVar1 == 0) {
      os_zero_mem(local_2c,0x400);
      iVar1 = os_alloc_mem(param_1,&local_28,4);
      if (iVar1 == 0) {
        os_zero_mem(local_28,4);
        if (iVar6 == 0) {
          sprintf(local_24[0],"Icap_%s%d",&_LC858,uVar5);
        }
        else if (iVar6 == 1) {
          sprintf(local_24[0],"Icap_%s%d",&_LC859,uVar5);
        }
        if (0 < DebugLevel) {
          printk(&_LC211,local_24[0]);
        }
        *(undefined4 *)(param_1 + 0xa78a68) = 0;
        while( true ) {
          iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
          pcVar7 = *(code **)(iVar1 + 0x198);
          if ((pcVar7 == (code *)0x0) && (pcVar7 = *(code **)(iVar1 + 0x194), pcVar7 == (code *)0x0)
             ) {
            if (-1 < DebugLevel) {
              printk("%s : The function is not hooked !!\n","Get_RBIST_IQ_Data_Proc");
            }
          }
          else {
            (*pcVar7)(param_1,local_2c,local_28,iVar6,uVar5);
          }
          if (*local_28 == 0) break;
          if (0 < *local_28) {
            iVar1 = 0;
            piVar3 = local_28;
            do {
              if (0 < DebugLevel) {
                printk(&_LC860,*(undefined4 *)(local_2c + iVar1 * 4));
                piVar3 = local_28;
              }
              iVar1 = iVar1 + 1;
            } while (iVar1 < *piVar3);
          }
        }
        goto LAB_000eb4e4;
      }
    }
  }
  if (-1 < DebugLevel) {
    printk("%s : Not enough memory for dynamic allocating !!\n","Get_RBIST_IQ_Data_Proc");
  }
LAB_000eb4e4:
  if (local_2c != 0) {
    os_free_mem();
  }
  if (local_28 != (int *)0x0) {
    os_free_mem();
  }
  if (local_24[0] != (char *)0x0) {
    os_free_mem();
  }
  return 1;
}

