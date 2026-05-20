// module: mt7915.ko
// function: Set_IRR_RxGain @ 0xebdc8
// size: 416 bytes
//

undefined4 Set_IRR_RxGain(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  
  iVar5 = rstrtok(param_2,&_LC232);
  if (iVar5 == 0) {
    uVar4 = 0;
    uVar3 = 0;
    uVar2 = 0;
    uVar1 = 0;
  }
  else {
    uVar4 = 0;
    uVar3 = 0;
    uVar2 = 0;
    uVar1 = 0;
    iVar6 = 0;
    do {
      switch(iVar6) {
      case 0:
        uVar1 = os_str_tol(iVar5,0,10);
        iVar5 = rstrtok(0,&_LC232);
        if (iVar5 == 0) goto LAB_000ebee4;
        break;
      case 1:
        break;
      case 2:
        goto switchD_000ebe04_caseD_2;
      case 3:
        goto switchD_000ebe04_caseD_3;
      default:
        goto switchD_000ebe04_default;
      }
      uVar2 = os_str_tol(iVar5,0,10);
      iVar5 = rstrtok(0,&_LC232);
      if (iVar5 == 0) break;
switchD_000ebe04_caseD_2:
      uVar3 = os_str_tol(iVar5,0,10);
      iVar5 = rstrtok(0,&_LC232);
      if (iVar5 == 0) break;
switchD_000ebe04_caseD_3:
      uVar4 = os_str_tol(iVar5,0,10);
      switch(uVar4) {
      case 1:
        iVar6 = 3;
        uVar4 = 0;
        break;
      case 2:
        iVar6 = 3;
        uVar4 = 1;
        break;
      default:
        iVar6 = 3;
        break;
      case 4:
        iVar6 = 3;
        uVar4 = 2;
        break;
      case 8:
        iVar6 = 3;
        uVar4 = 3;
      }
switchD_000ebe04_default:
      iVar6 = iVar6 + 1;
      iVar5 = rstrtok(0,&_LC232);
    } while (iVar5 != 0);
  }
LAB_000ebee4:
  if (2 < DebugLevel) {
    printk("%s: <SetRxGain> Input Checking Log\n\t\t\t\t\t--------------------------------------------------------------\n\t\t\t\t\tLPFG = %d \n\t\t\t\t\tLNA = %d \n\t\t\t\t\tDbdcIdx = %d \n\t\t\t\t\tAntIndex= %d \n\n"
           ,"Set_IRR_RxGain",uVar1,uVar2,uVar3,uVar4);
  }
  MtCmdRfTestSetRxGain(param_1,uVar1,uVar2,uVar3,uVar4);
  return 1;
}

