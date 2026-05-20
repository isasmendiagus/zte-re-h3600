// module: mt7915.ko
// function: MtShowPwrLimitTable @ 0x151588
// size: 996 bytes
//

undefined4 MtShowPwrLimitTable(int param_1,uint param_2,int param_3)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  byte local_32 [2];
  undefined4 *local_30;
  int local_2c [2];
  
  local_30 = (undefined4 *)0x0;
  local_2c[0] = 0;
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  local_32[0] = *(byte *)(iVar2 + 0x1fa);
  local_32[1] = *(undefined1 *)(iVar2 + 0x1fe);
  MtPwrGetPwrLimitInstance(param_1,param_2,1,local_2c);
  if (local_2c[0] == 0) {
    if (0 < DebugLevel) {
      printk("%s: null pointer for parameter related to show power limit table !!\n",
             "MtShowPwrLimitTable");
    }
    return 1;
  }
  MtPwrGetPwrLimitInstance(param_1,param_2,0,&local_30);
  if (local_30 == (undefined4 *)0x0) {
    if (DebugLevel < 1) {
      return 1;
    }
    printk("%s: null pointer for list of power limit table to show power limit info !!\n",
           "MtShowPwrLimitTable");
    return 1;
  }
  if (DebugLevel < param_3) {
    puVar8 = (undefined4 *)*local_30;
    puVar1 = (undefined4 *)*puVar8;
    iVar2 = DebugLevel;
    if (local_30 == puVar8) {
      return 0;
    }
  }
  else {
    printk("-----------------------------------------------------------------\n");
    if (DebugLevel < param_3) {
      puVar8 = (undefined4 *)*local_30;
      puVar1 = (undefined4 *)*puVar8;
      iVar2 = DebugLevel;
      if (local_30 == puVar8) {
        return 0;
      }
    }
    else {
      printk("SKU table index: %d \n",*(undefined1 *)(param_1 + 0x794eac));
      puVar8 = (undefined4 *)*local_30;
      puVar1 = (undefined4 *)*puVar8;
      iVar2 = DebugLevel;
      if (puVar8 == local_30) goto LAB_001517b0;
    }
  }
  do {
    puVar7 = puVar1;
    if (((iVar2 < param_3) ||
        (printk("start channel: %d, ChListNum: %d\n",*(undefined1 *)(puVar8 + 2),
                *(undefined1 *)((int)puVar8 + 9)), iVar2 = DebugLevel, DebugLevel < param_3)) ||
       (printk("Band: %d \n",*(undefined1 *)(puVar8 + 4)), iVar2 = DebugLevel, DebugLevel < param_3)
       ) {
      uVar4 = (uint)*(byte *)((int)puVar8 + 9);
      if (uVar4 != 0) goto LAB_00151650;
    }
    else {
      printk("Channel: ");
      uVar4 = (uint)*(byte *)((int)puVar8 + 9);
      iVar2 = DebugLevel;
      if (uVar4 != 0) {
LAB_00151650:
        uVar5 = 0;
        do {
          if (param_3 <= iVar2) {
            printk(&_LC20,*(undefined1 *)(puVar8[3] + uVar5));
            uVar4 = (uint)*(byte *)((int)puVar8 + 9);
            iVar2 = DebugLevel;
          }
          uVar5 = uVar5 + 1 & 0xff;
        } while (uVar5 < uVar4);
      }
      if (param_3 <= iVar2) {
        printk(&_LC21);
        iVar2 = DebugLevel;
      }
    }
    if (1 < param_2) {
      if (iVar2 < 1) {
        return 1;
      }
      printk("%s: u1Type out of range !!\n","MtShowPwrLimitTable");
      return 1;
    }
    if (local_32[param_2] != 0) {
      uVar5 = 0;
      uVar4 = uVar5;
      do {
        if (param_2 == 0) {
          if (iVar2 < param_3) goto LAB_001516a8;
          printk(&_LC23,cSkuParseTypeName + uVar5 * 8);
LAB_001518a4:
          iVar3 = local_2c[0];
          iVar2 = DebugLevel;
          if (*(char *)(local_2c[0] + uVar5) != '\0') {
LAB_001516b8:
            uVar6 = 0;
            iVar3 = local_2c[0];
            do {
              if (param_3 <= iVar2) {
                printk(&_LC20,*(undefined1 *)(puVar8[5] + uVar6 + uVar4));
                iVar3 = local_2c[0];
                iVar2 = DebugLevel;
              }
              uVar6 = uVar6 + 1 & 0xff;
            } while (uVar6 < *(byte *)(iVar3 + uVar5));
          }
          if (iVar2 < param_3) {
            uVar6 = (uint)*(byte *)(iVar3 + uVar5);
          }
          else {
            printk(&_LC21);
            uVar6 = (uint)*(byte *)(local_2c[0] + uVar5);
            iVar2 = DebugLevel;
          }
        }
        else {
          if (param_3 <= iVar2) {
            printk(&_LC23,"BFOFF_CCK" + uVar5 * 0xe);
            goto LAB_001518a4;
          }
LAB_001516a8:
          uVar6 = 0;
          if (*(char *)(local_2c[0] + uVar5) != '\0') goto LAB_001516b8;
        }
        uVar5 = uVar5 + 1 & 0xff;
        uVar4 = uVar6 + uVar4 & 0xff;
      } while (uVar5 < local_32[param_2]);
    }
    puVar1 = (undefined4 *)*puVar7;
    puVar8 = puVar7;
  } while (puVar7 != local_30);
LAB_001517b0:
  if (param_3 <= iVar2) {
    printk("-----------------------------------------------------------------\n");
  }
  return 0;
}

