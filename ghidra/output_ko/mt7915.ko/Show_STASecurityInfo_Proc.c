// module: mt7915.ko
// function: Show_STASecurityInfo_Proc @ 0x56850
// size: 596 bytes
//

undefined4 Show_STASecurityInfo_Proc(int param_1)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  undefined1 *puVar4;
  byte *pbVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  int iVar9;
  
  if (((DebugLevel < 1) || (printk("Security Infomation:\n"), DebugLevel < 1)) ||
     (printk("AuthMode\tPairwiseCipher\n"), DebugLevel < 1)) {
    if ((*(uint *)(&DAT_0036dccc + param_1) & 0xe) == 0) goto LAB_000569cc;
  }
  else {
    printk("0x%x\t\t0x%x\n",*(undefined4 *)(&DAT_0036db84 + param_1),
           *(undefined4 *)(&DAT_0036dccc + param_1));
    if ((*(uint *)(&DAT_0036dccc + param_1) & 0xe) == 0) {
      if (0 < DebugLevel) {
        printk(&_LC8);
      }
LAB_000569cc:
      puVar4 = (undefined1 *)(param_1 + 0x36dd12);
      iVar6 = DebugLevel;
      do {
        if (0 < iVar6) {
          printk(&_LC6,*puVar4);
          iVar6 = DebugLevel;
        }
        puVar4 = puVar4 + 1;
      } while (puVar4 != (undefined1 *)(param_1 + 0x36dd32));
      if (iVar6 < 1) {
        return 1;
      }
      printk(&_LC7);
      return 1;
    }
    if (0 < DebugLevel) {
      printk("Key ID=%d\n",(&DAT_0036dcd0)[param_1]);
    }
  }
  iVar7 = 1;
  pbVar5 = &DAT_0036db88 + param_1;
  bVar1 = true;
  iVar6 = 0;
  do {
    if (0 < DebugLevel) {
      printk("Key%d",iVar7);
    }
    uVar2 = (uint)pbVar5[0x50];
    iVar9 = DebugLevel;
    if (uVar2 == 0) {
      if (!bVar1) goto LAB_0005693c;
LAB_000568f8:
      if (0 < DebugLevel) {
        printk(&_LC5,pbVar5);
        iVar9 = DebugLevel;
        goto LAB_00056940;
      }
    }
    else {
      if (*pbVar5 - 0x20 < 0x5f) {
        pbVar8 = pbVar5;
        do {
          if (pbVar8 == (byte *)(param_1 + iVar6 + 0x36db87 + uVar2)) {
            if (bVar1) goto LAB_000568f8;
            break;
          }
          pbVar8 = pbVar8 + 1;
        } while (*pbVar8 - 0x20 < 0x5f);
      }
      iVar3 = 0;
      pbVar8 = pbVar5;
      do {
        iVar3 = iVar3 + 1;
        if (0 < iVar9) {
          printk(&_LC6,*pbVar8);
          uVar2 = (uint)pbVar5[0x50];
          iVar9 = DebugLevel;
        }
        pbVar8 = pbVar8 + 1;
      } while (iVar3 < (int)uVar2);
LAB_0005693c:
      bVar1 = false;
LAB_00056940:
      if (0 < iVar9) {
        printk(&_LC7);
      }
    }
    iVar6 = iVar6 + 0x51;
    pbVar5 = pbVar5 + 0x51;
    iVar7 = iVar7 + 1;
    if (iVar6 == 0x144) {
      return 1;
    }
  } while( true );
}

