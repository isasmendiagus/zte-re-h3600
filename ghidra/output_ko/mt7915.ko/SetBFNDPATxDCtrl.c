// module: mt7915.ko
// function: SetBFNDPATxDCtrl @ 0xc0f28
// size: 412 bytes
//

undefined4 SetBFNDPATxDCtrl(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  int iVar6;
  undefined4 uVar7;
  char cVar8;
  
  if (param_2 == 0) {
    uVar7 = 0;
    if (-1 < DebugLevel) {
      printk("%s: No parameters!!\n","SetBFNDPATxDCtrl");
    }
  }
  else {
    iVar6 = rstrtok(param_2,&_LC156);
    if (iVar6 == 0) {
      uVar1 = 0;
      uVar3 = 0;
      uVar4 = 0;
      uVar5 = 0;
      uVar2 = 0;
    }
    else {
      cVar8 = '\0';
      uVar1 = 0;
      uVar2 = 0;
      uVar3 = 0;
      uVar4 = 0;
      uVar5 = 0;
      do {
        switch(cVar8) {
        case '\0':
          uVar5 = os_str_tol(iVar6,0,10);
          break;
        case '\x01':
          uVar4 = os_str_tol(iVar6,0,10);
          break;
        case '\x02':
          uVar3 = os_str_tol(iVar6,0,10);
          break;
        case '\x03':
          uVar2 = os_str_tol(iVar6,0,10);
          break;
        case '\x04':
          uVar1 = os_str_tol(iVar6,0,10);
          break;
        default:
          if (-1 < DebugLevel) {
            printk("%s: set wrong parameters\n","SetBFNDPATxDCtrl");
          }
        }
        cVar8 = cVar8 + '\x01';
        iVar6 = rstrtok(0,&_LC156);
      } while (iVar6 != 0);
    }
    if (0 < DebugLevel) {
      printk("%s: fgNDPA_ManualMode = %d, ucNDPA_TxMode = %d, ucNDPA_Rate = %d, ucNDPA_BW = %d, ucNDPA_PowerOffset = %d\n"
             ,"SetBFNDPATxDCtrl",uVar5,uVar4,uVar3,uVar2,uVar1);
    }
    uVar7 = BFNDPATxDCtrlCmd(param_1,uVar5,uVar4,uVar3,uVar2,uVar1);
  }
  return uVar7;
}

