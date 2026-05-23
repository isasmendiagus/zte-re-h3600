// module: mt7915.ko
// function: SetCCKTxStream @ 0xbfc7c
// size: 432 bytes
//

undefined4 SetCCKTxStream(int *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  
  if ((uint)*(byte *)((int)param_1 + 0x2b7242) <= (uint)*(byte *)(*param_1 + 0x3c)) {
    return 0;
  }
  HcGetBandByWdev(param_1 + (uint)*(byte *)(*param_1 + 0x3c) * 0x160d + 0xadc92);
  uVar1 = HcGetBandByWdev(param_1 + 0xdb6d6);
  if (uVar1 < 2) {
    if (param_2 == 0) {
      if (-1 < DebugLevel) {
        printk("%s: No parameters!!\n","SetCCKTxStream");
      }
    }
    else {
      iVar2 = rstrtok(param_2,&_LC156);
      if (iVar2 != 0) {
        uVar5 = 0;
        uVar3 = uVar5;
        do {
          if (uVar5 == 0) {
            uVar3 = simple_strtol(iVar2,0,10);
            uVar3 = uVar3 & 0xff;
            iVar2 = rstrtok(0,&_LC156);
            uVar5 = 1;
            if (iVar2 == 0) break;
          }
          if (-1 < DebugLevel) {
            printk("%s: set wrong parameters\n","SetCCKTxStream");
          }
          iVar2 = rstrtok(0,&_LC156);
          uVar5 = uVar5 + 1 & 0xff;
        } while (iVar2 != 0);
        if (uVar3 - 1 < 3) {
          *(char *)((int)param_1 + uVar1 + 0x795039) = (char)uVar3;
          uVar4 = TxCCKStreamCtrl(param_1,uVar3,uVar1);
          return uVar4;
        }
      }
      if ((-1 < DebugLevel) &&
         (printk("%s: set wrong parameters\n","SetCCKTxStream"), -1 < DebugLevel)) {
        printk("EX. iwpriv <interface> set CCKTxStream=1 (1~4)\n");
      }
    }
  }
  return 0;
}

