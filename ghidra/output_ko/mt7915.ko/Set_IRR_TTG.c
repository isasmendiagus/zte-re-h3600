// module: mt7915.ko
// function: Set_IRR_TTG @ 0xebf9c
// size: 316 bytes
//

undefined4 Set_IRR_TTG(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  iVar4 = rstrtok(param_2,&_LC232);
  if (iVar4 == 0) {
    uVar1 = 0;
    uVar3 = 0;
    uVar6 = 0;
    uVar7 = 0;
    uVar2 = 0;
  }
  else {
    uVar1 = 0;
    uVar2 = 0;
    uVar3 = 0;
    uVar6 = 0;
    uVar7 = 0;
    iVar5 = 0;
    do {
      switch(iVar5) {
      case 0:
        uVar3 = os_str_tol(iVar4,0,10);
        break;
      case 1:
        uVar6 = os_str_tol(iVar4,0,10);
        break;
      case 2:
        uVar7 = os_str_tol(iVar4,0,10);
        break;
      case 3:
        uVar2 = os_str_tol(iVar4,0,10);
        break;
      case 4:
        uVar1 = os_str_tol(iVar4,0,10);
      }
      iVar5 = iVar5 + 1;
      iVar4 = rstrtok(0,&_LC232);
    } while (iVar4 != 0);
  }
  if (2 < DebugLevel) {
    printk("%s: <SetTTG> Input Checking Log\n\t\t\t\t\t--------------------------------------------------------------\n\t\t\t\t\tChannelFreq = %d \n\t\t\t\t\tToneFreq = %d \n\t\t\t\t\tTTGPwrIdx = %d \n\t\t\t\t\tDbdcIdx= %d \n\n"
           ,"Set_IRR_TTG",uVar7,uVar6,uVar3,uVar1);
  }
  MtCmdRfTestSetTTG(param_1,uVar7,uVar6,uVar3,uVar2,uVar1);
  return 1;
}

