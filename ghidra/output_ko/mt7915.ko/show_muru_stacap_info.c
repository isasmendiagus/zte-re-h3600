// module: mt7915.ko
// function: show_muru_stacap_info @ 0x181590
// size: 1224 bytes
//

void show_muru_stacap_info(int param_1,int param_2)

{
  char cVar1;
  char *__s;
  size_t __n;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 auStack_39 [29];
  
  if (param_2 == 0) {
    return;
  }
  cVar1 = delimitcnt(param_2,&_LC251);
  if (1 < (byte)(cVar1 + 1U)) {
    if (DebugLevel < 0) {
      return;
    }
    printk("Num of Input Parameters Wrong\n");
    return;
  }
  __s = (char *)rstrtok(param_2,&_LC251);
  iVar4 = 0;
  if (__s != (char *)0x0) {
    do {
      __n = strlen(__s);
      memcpy(auStack_39,__s,__n);
      uVar2 = os_str_tol(__s,0,10);
      __s = (char *)rstrtok(0,&_LC251);
    } while (__s != (char *)0x0);
    iVar4 = (uVar2 & 0xffff) * 0x18;
  }
  if (0 < DebugLevel) {
    printk("_Muru_StaCap_Info\n");
  }
  cVar1 = *(char *)(param_1 + 0x795a6c);
  uVar2 = iVar4 + *(int *)(param_1 + 0x795a68);
  if (0xdfffffff < uVar2) {
    FUN_0017f59c(param_1);
  }
  if (cVar1 != '\0') {
    return;
  }
  if (DebugLevel < 1) {
    return;
  }
  printk("|-(0x%08X) rDlOfdma\n",uVar2);
  if (DebugLevel < 1) {
LAB_00181764:
    if (0 < DebugLevel) {
      uVar3 = FUN_00174570(param_1,uVar2 + 4);
      printk("|-|-(0x%08X) u1Lt16SigB = %d\n",uVar2 + 4,uVar3);
      if (DebugLevel < 1) {
        return;
      }
      uVar3 = FUN_00174570(param_1,uVar2 + 5);
      printk("|-|-(0x%08X) u1RxSUCompSigB = %d\n",uVar2 + 5,uVar3);
      goto LAB_001817cc;
    }
LAB_00181880:
    if (0 < DebugLevel) {
      uVar3 = FUN_00174570(param_1,uVar2 + 10);
      printk("|-|-(0x%08X) u1UoRa = %d\n",uVar2 + 10,uVar3);
      if (DebugLevel < 1) {
        return;
      }
      uVar3 = FUN_00174570(param_1,uVar2 + 0xb);
      printk("|-|-(0x%08X) u12x996Tone = %d\n",uVar2 + 0xb,uVar3);
      goto LAB_001818e8;
    }
  }
  else {
    uVar3 = FUN_00174570(param_1,uVar2);
    printk("|-|-(0x%08X) u1PhyPunRx = %d\n",uVar2,uVar3);
    if (DebugLevel < 1) {
      return;
    }
    uVar3 = FUN_00174570(param_1,uVar2 + 1);
    printk("|-|-(0x%08X) u120MIn40M2G = %d\n",uVar2 + 1,uVar3);
    if (0 < DebugLevel) {
      uVar3 = FUN_00174570(param_1,uVar2 + 2);
      printk("|-|-(0x%08X) u120MIn160M = %d\n",uVar2 + 2,uVar3);
      if (DebugLevel < 1) {
        return;
      }
      uVar3 = FUN_00174570(param_1,uVar2 + 3);
      printk("|-|-(0x%08X) u180MIn160M = %d\n",uVar2 + 3,uVar3);
      goto LAB_00181764;
    }
LAB_001817cc:
    if (DebugLevel < 1) goto LAB_00181880;
    uVar3 = FUN_00174570(param_1,uVar2 + 6);
    printk("|-|-(0x%08X) u1RxSUNonCompSigB = %d\n",uVar2 + 6,uVar3);
    if (DebugLevel < 1) {
      return;
    }
    iVar4 = uVar2 + 8;
    printk("|-(0x%08X) rUlOfdma\n",iVar4);
    if (0 < DebugLevel) {
      uVar3 = FUN_00174570(param_1,iVar4);
      printk("|-|-(0x%08X) u1TrigFrmPad = %d\n",iVar4,uVar3);
      if (DebugLevel < 1) {
        return;
      }
      uVar3 = FUN_00174570(param_1,uVar2 + 9);
      printk("|-|-(0x%08X) u1MuCascading = %d\n",uVar2 + 9,uVar3);
      goto LAB_00181880;
    }
LAB_001818e8:
    if (0 < DebugLevel) {
      uVar3 = FUN_00174570(param_1,uVar2 + 0xc);
      printk("|-|-(0x%08X) u1RxTrgFrmBy11ac = %d\n",uVar2 + 0xc,uVar3);
      if (DebugLevel < 1) {
        return;
      }
      iVar4 = uVar2 + 0x10;
      printk("|-(0x%08X) rDlMimo\n",iVar4);
      if (DebugLevel < 1) goto LAB_001819f0;
      uVar3 = FUN_00174570(param_1,iVar4);
      printk("|-|-(0x%08X) fgVhtMuBfee = %d\n",iVar4,uVar3);
      if (DebugLevel < 1) {
        return;
      }
      uVar3 = FUN_00174570(param_1,uVar2 + 0x11);
      printk("|-|-(0x%08X) fgParBWDlMimo = %d\n",uVar2 + 0x11,uVar3);
    }
  }
  iVar4 = uVar2 + 0x14;
  if (DebugLevel < 1) {
    return;
  }
  printk("|-(0x%08X) rUlMimo\n",iVar4);
  if (DebugLevel < 1) {
    return;
  }
  uVar3 = FUN_00174570(param_1,iVar4);
  printk("|-|-(0x%08X) fgFullUlMimo = %d\n",iVar4,uVar3);
LAB_001819f0:
  if (DebugLevel < 1) {
    return;
  }
  uVar3 = FUN_00174570(param_1,uVar2 + 0x15);
  printk("|-|-(0x%08X) fgParUlMimo = %d\n",uVar2 + 0x15,uVar3);
  return;
}

