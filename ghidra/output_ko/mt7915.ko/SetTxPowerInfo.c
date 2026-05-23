// module: mt7915.ko
// function: SetTxPowerInfo @ 0xbffb0
// size: 756 bytes
//

undefined4 SetTxPowerInfo(int *param_1,int param_2)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  char cVar5;
  bool bVar6;
  
  iVar3 = *(int *)(*param_1 + 0x38);
  uVar4 = *(uint *)(*param_1 + 0x3c);
  if ((iVar3 - 0x100U & 0xfffffeff) == 0) {
    uVar4 = HcGetBandByWdev(param_1 + (uVar4 & 0xff) * 0x160d + 0xadc92);
    if (DebugLevel < 0) goto LAB_000c0034;
    printk("%s: AP Band = %d !!\n","SetTxPowerInfo",uVar4);
LAB_000c0148:
    if (1 < uVar4) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("%s: Invalid Band Index!!\n","SetTxPowerInfo");
      goto LAB_000c0040;
    }
  }
  else {
    if ((iVar3 != 0x400) && (iVar3 != 0x800)) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("[SetTxPowerInfo]: pObj->ioctl_if_type = %d!!\n");
      return 0;
    }
    uVar4 = HcGetBandByWdev(param_1 + (uVar4 & 0xff) * 0x84dec + 0xdb6d6);
    if (-1 < DebugLevel) {
      printk("%s: STA Band = %d !!\n","SetTxPowerInfo",uVar4);
      goto LAB_000c0148;
    }
LAB_000c0034:
    if (1 < uVar4) goto LAB_000c0040;
  }
  if (param_2 != 0) {
    iVar3 = rstrtok(param_2,&_LC156);
    if (iVar3 == 0) {
      bVar1 = 0;
    }
    else {
      cVar5 = '\0';
      bVar1 = 0;
      do {
        bVar6 = cVar5 == '\0';
        cVar5 = cVar5 + '\x01';
        if (bVar6) {
          bVar1 = simple_strtol(iVar3,0,10);
        }
        iVar3 = rstrtok(0,&_LC156);
      } while (iVar3 != 0);
      if (4 < bVar1) {
        if (DebugLevel < 0) {
          return 0;
        }
        printk("%s: parameter out of range!!\n","SetTxPowerInfo");
        goto LAB_000c0040;
      }
    }
    if (0 < DebugLevel) {
      printk("%s: BandIdx: %d, ucTxPowerInfoCatg: %d\n","SetTxPowerInfo",uVar4,bVar1);
    }
    uVar2 = TxPowerShowInfo(param_1,bVar1,uVar4);
    return uVar2;
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("%s: No parameters!!\n","SetTxPowerInfo");
LAB_000c0040:
  if (0 < DebugLevel) {
    printk("iwpriv <interface> set TxPowerInfo=[param1]\n");
    if (0 < DebugLevel) {
      printk("\tparam1: Tx Power Info Category (0~3)\n");
      if (DebugLevel < 1) {
        return 0;
      }
      printk("\t\t\t0: Tx Power Basic Info\n");
      if (DebugLevel < 1) {
        return 0;
      }
      printk("\t\t\t1: Backup Power Table\n");
      if (DebugLevel < 1) {
        return 0;
      }
      printk("\t\t\t2: Tx Power Rate Power Info\n");
    }
    if ((0 < DebugLevel) && (printk("\t\t\t3: Thermal Compensation Table\n"), 0 < DebugLevel)) {
      printk("\t\t\t4: TXV/BBP Power Value (per packet)\n");
    }
  }
  return 0;
}

