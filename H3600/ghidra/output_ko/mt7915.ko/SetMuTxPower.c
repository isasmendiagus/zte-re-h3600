// module: mt7915.ko
// function: SetMuTxPower @ 0xc0d24
// size: 512 bytes
//

undefined4 SetMuTxPower(int *param_1,int param_2)

{
  char cVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  char cVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  
  iVar5 = *param_1;
  if ((uint)*(byte *)(iVar5 + 0x3c) < (uint)*(byte *)((int)param_1 + 0x2b7242)) {
    iVar7 = *(int *)(iVar5 + 0x38);
    if ((iVar7 - 0x100U & 0xfffffeff) == 0) {
      uVar6 = HcGetBandByWdev(param_1 + (uint)*(byte *)(iVar5 + 0x3c) * 0x160d + 0xadc92);
      iVar7 = *(int *)(iVar5 + 0x38);
    }
    else {
      uVar6 = 0;
    }
    if (iVar7 == 0x400) {
      uVar6 = HcGetBandByWdev(param_1 + 0xdb6d6);
    }
    if (0 < DebugLevel) {
      printk("%s: ucBandIdx = %d\n","SetMuTxPower",uVar6);
    }
    if (uVar6 < 2) {
      if (param_2 != 0) {
        iVar5 = rstrtok(param_2,&_LC156);
        if (iVar5 == 0) {
          cVar1 = '\0';
          uVar2 = 0;
        }
        else {
          cVar1 = '\0';
          uVar2 = 0;
          cVar4 = '\0';
          do {
            if (cVar4 == '\0') {
              uVar2 = os_str_tol(iVar5,0,10);
              iVar5 = rstrtok(0,&_LC156);
              if (iVar5 == 0) break;
LAB_000c0dc4:
              cVar1 = os_str_tol(iVar5,0,10);
              cVar4 = '\x02';
              iVar5 = rstrtok(0,&_LC156);
              if (iVar5 == 0) break;
            }
            else if (cVar4 == '\x01') goto LAB_000c0dc4;
            if (-1 < DebugLevel) {
              printk("%s: set wrong parameters\n","SetMuTxPower");
            }
            cVar4 = cVar4 + '\x01';
            iVar5 = rstrtok(0,&_LC156);
          } while (iVar5 != 0);
        }
        if (0 < DebugLevel) {
          printk("%s: fgMuTxPwrManEn: %d, cMuTxPwr: %d\n","SetMuTxPower",uVar2,(int)cVar1);
        }
        uVar3 = MuPwrCtrlCmd(param_1,uVar2,(int)cVar1,uVar6);
        return uVar3;
      }
      if (-1 < DebugLevel) {
        printk("%s: No parameters!!\n","SetMuTxPower");
      }
    }
  }
  return 0;
}

