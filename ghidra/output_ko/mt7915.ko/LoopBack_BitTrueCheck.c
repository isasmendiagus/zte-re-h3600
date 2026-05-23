// module: mt7915.ko
// function: LoopBack_BitTrueCheck @ 0x28d584
// size: 1036 bytes
//

void LoopBack_BitTrueCheck(int param_1)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  size_t sVar4;
  uint uVar5;
  undefined1 *puVar6;
  
  if (*(char *)(param_1 + 0xa77b5c) == '\0') {
    sVar4 = *(size_t *)(param_1 + 0xa59b54);
    if (sVar4 != *(size_t *)(param_1 + 0xa59b4c)) {
      LoopBack_Fail(param_1,3);
      if (DebugLevel < 3) {
        return;
      }
      printk("%s, ####################### TX/RX Length not equal ####################\n",
             "LoopBack_BitTrueCheck");
      if (2 < DebugLevel) {
        printk("%s, ExpectRxLen = %d, RxRawLen = %d\n","LoopBack_BitTrueCheck",
               *(undefined4 *)(param_1 + 0xa59b54),*(undefined4 *)(param_1 + 0xa59b4c));
        return;
      }
      return;
    }
    puVar6 = (undefined1 *)(param_1 + 0xa68b58);
    puVar3 = (undefined1 *)(param_1 + 0xa4ab45);
    iVar1 = memcmp(puVar6,puVar3,sVar4);
    if (iVar1 == 0) {
      *(undefined4 *)(param_1 + 0xa3bb00) = 0;
      return;
    }
    if (*(char *)(param_1 + 0xa3baf8) == '\0') goto LAB_0028d72c;
    if (DebugLevel < 1) {
      iVar1 = DebugLevel;
      if (sVar4 != 0) {
LAB_0028d6d0:
        uVar5 = 0;
        iVar1 = DebugLevel;
        do {
          uVar5 = uVar5 + 1;
          if (0 < iVar1) {
            printk(&_LC36,*puVar6);
            iVar1 = DebugLevel;
          }
          puVar6 = puVar6 + 1;
        } while (uVar5 < *(uint *)(param_1 + 0xa59b4c));
        goto LAB_0028d6f0;
      }
LAB_0028d6f8:
      if (*(int *)(param_1 + 0xa59b4c) == 0) goto LAB_0028d72c;
LAB_0028d704:
      uVar5 = 0;
      do {
        uVar5 = uVar5 + 1;
        if (0 < iVar1) {
          printk(&_LC36,*puVar3);
          iVar1 = DebugLevel;
        }
        puVar3 = puVar3 + 1;
      } while (uVar5 < *(uint *)(param_1 + 0xa59b4c));
    }
    else {
      printk("RxExpect Dump(%u): ",sVar4);
      iVar1 = DebugLevel;
      if (*(int *)(param_1 + 0xa59b4c) != 0) goto LAB_0028d6d0;
LAB_0028d6f0:
      if ((iVar1 < 1) || (printk(&_LC37), iVar1 = DebugLevel, DebugLevel < 1)) goto LAB_0028d6f8;
      printk("RxBackRaw Dump: ");
      iVar1 = DebugLevel;
      if (*(int *)(param_1 + 0xa59b4c) != 0) goto LAB_0028d704;
    }
    if (iVar1 < 1) goto LAB_0028d72c;
  }
  else {
    sVar4 = *(size_t *)(param_1 + 0xa59b48);
    if (sVar4 != *(size_t *)(param_1 + 0xa59b4c)) {
      LoopBack_Fail(param_1,3);
      if (DebugLevel < 3) {
        return;
      }
      printk("%s, ####################### TX/RX Length not equal ####################\n",
             "LoopBack_BitTrueCheck");
      if (2 < DebugLevel) {
        printk("%s, TxRawLen = %d, RxRawLen = %d\n","LoopBack_BitTrueCheck",
               *(undefined4 *)(param_1 + 0xa59b48),*(undefined4 *)(param_1 + 0xa59b4c));
        return;
      }
      return;
    }
    puVar6 = (undefined1 *)(param_1 + 0xa3bb45);
    puVar3 = (undefined1 *)(param_1 + 0xa4ab45);
    iVar2 = memcmp(puVar6,puVar3,sVar4);
    iVar1 = DebugLevel;
    if (iVar2 == 0) {
      *(undefined4 *)(param_1 + 0xa3bb00) = 0;
      if (2 < iVar1) {
        printk("%s, ####################### BIT_TRUE OK ####################\n",
               "LoopBack_BitTrueCheck");
        return;
      }
      return;
    }
    if (*(char *)(param_1 + 0xa3baf8) == '\0') goto LAB_0028d72c;
    if (DebugLevel < 3) {
      if (sVar4 != 0) {
LAB_0028d7b8:
        uVar5 = 0;
        iVar1 = DebugLevel;
        do {
          uVar5 = uVar5 + 1;
          if (2 < iVar1) {
            printk(&_LC36,*puVar6);
            iVar1 = DebugLevel;
          }
          puVar6 = puVar6 + 1;
        } while (uVar5 < *(uint *)(param_1 + 0xa59b4c));
        goto LAB_0028d7d8;
      }
LAB_0028d7e0:
      if (*(int *)(param_1 + 0xa59b4c) == 0) goto LAB_0028d72c;
LAB_0028d7ec:
      uVar5 = 0;
      do {
        uVar5 = uVar5 + 1;
        if (2 < iVar1) {
          printk(&_LC36,*puVar3);
          iVar1 = DebugLevel;
        }
        puVar3 = puVar3 + 1;
      } while (uVar5 < *(uint *)(param_1 + 0xa59b4c));
    }
    else {
      printk("TxExpect Dump(%u): ",sVar4);
      iVar1 = DebugLevel;
      if (*(int *)(param_1 + 0xa59b4c) != 0) goto LAB_0028d7b8;
LAB_0028d7d8:
      if ((iVar1 < 3) || (printk(&_LC37), iVar1 = DebugLevel, DebugLevel < 3)) goto LAB_0028d7e0;
      printk("RxBackRaw Dump: ");
      iVar1 = DebugLevel;
      if (*(int *)(param_1 + 0xa59b4c) != 0) goto LAB_0028d7ec;
    }
    if (iVar1 < 3) goto LAB_0028d72c;
  }
  printk(&_LC37);
LAB_0028d72c:
  LoopBack_Fail(param_1,3);
  if (2 < DebugLevel) {
    printk("%s, ####################### BIT_TRUE_FAIL ####################\n",
           "LoopBack_BitTrueCheck");
    return;
  }
  return;
}

