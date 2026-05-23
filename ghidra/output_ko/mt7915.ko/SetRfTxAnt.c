// module: mt7915.ko
// function: SetRfTxAnt @ 0xbfe30
// size: 376 bytes
//

undefined4 SetRfTxAnt(undefined4 param_1,char *param_2)

{
  undefined1 uVar1;
  size_t sVar2;
  int iVar3;
  undefined4 uVar4;
  char cVar5;
  
  if (param_2 == (char *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: No parameters!!\n","SetRfTxAnt");
    }
  }
  else {
    sVar2 = strlen(param_2);
    if (sVar2 == 2) {
      iVar3 = rstrtok(param_2,&_LC156);
      if (iVar3 == 0) {
        uVar1 = 0;
      }
      else {
        uVar1 = 0;
        cVar5 = '\0';
        do {
          if (cVar5 == '\0') {
            uVar1 = simple_strtol(iVar3,0,10);
            iVar3 = rstrtok(0,&_LC156);
            cVar5 = '\x01';
            if (iVar3 == 0) break;
          }
          if (-1 < DebugLevel) {
            printk("%s: set wrong parameters\n","SetRfTxAnt");
          }
          cVar5 = cVar5 + '\x01';
          iVar3 = rstrtok(0,&_LC156);
        } while (iVar3 != 0);
      }
      if (0 < DebugLevel) {
        printk("%s: ucTxAntIdx: 0x%x\n","SetRfTxAnt",uVar1);
      }
      uVar4 = TxPowerRfTxAnt(param_1,uVar1);
      return uVar4;
    }
    if (-1 < DebugLevel) {
      printk("%s: Wrong parameter format!!\n","SetRfTxAnt");
      if (-1 < DebugLevel) {
        printk("%s: Please use input format with 2-digit.\n","SetRfTxAnt");
      }
    }
  }
  return 0;
}

