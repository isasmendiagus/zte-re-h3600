// module: mt7915.ko
// function: SetTpcWlanIdCtrl @ 0xc1778
// size: 460 bytes
//

undefined4 SetTpcWlanIdCtrl(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  byte bVar2;
  byte bVar3;
  undefined2 uVar4;
  int iVar5;
  undefined4 uVar6;
  
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: No parameters!!\n","SetTpcWlanIdCtrl");
    return 0;
  }
  iVar5 = rstrtok(param_2,&_LC156);
  if (iVar5 == 0) {
    bVar3 = 0;
    bVar2 = 0;
    uVar4 = 0;
    uVar1 = 0;
  }
  else {
    uVar1 = os_str_tol(iVar5,0,10);
    iVar5 = rstrtok(0,&_LC156);
    if (iVar5 == 0) {
      bVar3 = 0;
      bVar2 = 0;
      uVar4 = 0;
    }
    else {
      bVar2 = os_str_tol(iVar5,0,10);
      if (0x1f < bVar2) {
        if (DebugLevel < 0) {
          return 0;
        }
        printk("%s: Set wrong parameters! Entry index should be between 0~31 .\n","SetTpcWlanIdCtrl"
              );
        return 0;
      }
      iVar5 = rstrtok(0,&_LC156);
      if (iVar5 == 0) {
        bVar3 = 0;
        uVar4 = 0;
      }
      else {
        uVar4 = os_str_tol(iVar5,0,10);
        iVar5 = rstrtok(0,&_LC156);
        bVar3 = 0;
        if (iVar5 != 0) {
          bVar3 = os_str_tol(iVar5,0,10);
          if (bVar3 < 2) {
            iVar5 = rstrtok(0,&_LC156);
            if (iVar5 == 0) goto LAB_000c18b0;
            if (-1 < DebugLevel) {
              printk("%s: set wrong parameters\n","SetTpcWlanIdCtrl");
            }
          }
          else if (-1 < DebugLevel) {
            printk("%s: Set wrong parameters! Down-link Tx Type 0: MU-MIMO, 1: OFDMA. \n",
                   "SetTpcWlanIdCtrl");
            return 0;
          }
          return 0;
        }
      }
    }
  }
LAB_000c18b0:
  uVar6 = TpcWlanIdCtrl(param_1,uVar1,bVar2,uVar4,bVar3);
  return uVar6;
}

