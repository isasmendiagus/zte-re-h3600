// module: mt7915.ko
// function: Set_IRR_TTGOnOff @ 0xec0f0
// size: 380 bytes
//

undefined4 Set_IRR_TTGOnOff(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = rstrtok(param_2,&_LC232);
  if (iVar4 == 0) {
    uVar2 = 0;
    uVar1 = 0;
    uVar3 = 0;
  }
  else {
    uVar2 = 0;
    uVar1 = 0;
    uVar3 = 0;
    iVar5 = 0;
    do {
      if (iVar5 == 1) {
LAB_000ec15c:
        uVar1 = os_str_tol(iVar4,0,10);
        iVar4 = rstrtok(0,&_LC232);
        if (iVar4 == 0) break;
LAB_000ec184:
        uVar2 = os_str_tol(iVar4,0,10);
        switch(uVar2) {
        case 1:
          iVar5 = 2;
          uVar2 = 0;
          break;
        case 2:
          iVar5 = 2;
          uVar2 = 1;
          break;
        default:
          iVar5 = 2;
          break;
        case 4:
          iVar5 = 2;
          uVar2 = 2;
          break;
        case 8:
          iVar5 = 2;
          uVar2 = 3;
        }
      }
      else {
        if (iVar5 == 2) goto LAB_000ec184;
        if (iVar5 == 0) {
          uVar3 = os_str_tol(iVar4,0,10);
          iVar4 = rstrtok(0,&_LC232);
          if (iVar4 != 0) goto LAB_000ec15c;
          break;
        }
      }
      iVar5 = iVar5 + 1;
      iVar4 = rstrtok(0,&_LC232);
    } while (iVar4 != 0);
  }
  if (2 < DebugLevel) {
    printk("%s: <SetTTGOnOff> Input Checking Log\n\t\t\t\t\t--------------------------------------------------------------\n\t\t\t\t\tTTGEnable = %d \n\t\t\t\t\tDbdcIdx = %d \n\t\t\t\t\tAntIndex = %d \n\n"
           ,"Set_IRR_TTGOnOff",uVar3,uVar1,uVar2);
  }
  MtCmdRfTestSetTTGOnOff(param_1,uVar3,uVar1,uVar2);
  return 1;
}

