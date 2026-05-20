// module: mt7915.ko
// function: Set_IRR_ADC @ 0xebbd0
// size: 440 bytes
//

undefined4 Set_IRR_ADC(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  
  iVar7 = rstrtok(param_2,&_LC232);
  if (iVar7 == 0) {
    uVar1 = 0;
    uVar6 = 0;
    uVar5 = 0;
    uVar2 = 0;
    uVar9 = 0;
    uVar3 = 0;
    uVar4 = 0;
  }
  else {
    uVar1 = 0;
    uVar2 = 0;
    uVar3 = 0;
    uVar4 = 0;
    uVar5 = 0;
    uVar6 = 0;
    uVar9 = 0;
    iVar8 = 0;
    do {
      switch(iVar8) {
      case 0:
        uVar6 = os_str_tol(iVar7,0,10);
        switch(uVar6) {
        case 1:
          uVar6 = 0;
          break;
        case 2:
          uVar6 = 1;
          break;
        default:
          break;
        case 4:
          uVar6 = 2;
          break;
        case 8:
          uVar6 = 3;
        }
        break;
      case 1:
        uVar9 = os_str_tol(iVar7,0,10);
        break;
      case 2:
        uVar5 = os_str_tol(iVar7,0,10);
        break;
      case 3:
        uVar4 = os_str_tol(iVar7,0,10);
        break;
      case 4:
        uVar3 = os_str_tol(iVar7,0,10);
        break;
      case 5:
        uVar2 = os_str_tol(iVar7,0,10);
        break;
      case 6:
        uVar1 = os_str_tol(iVar7,0,10);
      }
      iVar8 = iVar8 + 1;
      iVar7 = rstrtok(0,&_LC232);
    } while (iVar7 != 0);
  }
  if (2 < DebugLevel) {
    printk("%s: <SetADC> Input Checking Log\n\t\t\t\t\t--------------------------------------------------------------\n\t\t\t\t\tChannelFreq = %d \n\t\t\t\t\tAntIndex = %d \n\t\t\t\t\tBW = %d \n\t\t\t\t\tSX= %d \n\t\t\t\t\tDbdcIdx = %d \n\t\t\t\t\tRunType = %d \n\t\t\t\t\tFType = %d \n\n"
           ,"Set_IRR_ADC",uVar9,uVar6,uVar5,uVar4,uVar3,uVar2,uVar1);
  }
  MtCmdRfTestSetADC(param_1,uVar9,uVar6,uVar5,uVar4,uVar3,uVar2,uVar1);
  return 1;
}

