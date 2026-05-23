// module: mt7915.ko
// function: _SetSKUCtrl @ 0xbef28
// size: 580 bytes
//

undefined4 _SetSKUCtrl(int param_1,uint param_2,char *param_3)

{
  byte bVar1;
  size_t sVar2;
  int iVar3;
  undefined4 uVar4;
  char cVar5;
  
  if (*(char *)(param_1 + 0x286285) == '\x01') {
LAB_000befdc:
    if (0 < DebugLevel) goto LAB_000bf128;
  }
  else {
    if (*(char *)(param_1 + 0x286285) == '\0') {
      param_2 = HcGetBandByWdev(&DAT_0036db58 + param_1);
      goto LAB_000befdc;
    }
    param_2 = 0;
    if (DebugLevel < 1) goto LAB_000bef6c;
LAB_000bf128:
    printk("%s: ucBandIdx = %d\n","_SetSKUCtrl",param_2);
  }
  if (1 < param_2) {
    return 0;
  }
LAB_000bef6c:
  if (param_3 == (char *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: No parameters!!\n","_SetSKUCtrl");
    }
  }
  else {
    sVar2 = strlen(param_3);
    if (sVar2 == 1) {
      iVar3 = rstrtok(param_3,&_LC156);
      if (iVar3 == 0) {
        bVar1 = 0;
      }
      else {
        bVar1 = 0;
        cVar5 = '\0';
        do {
          if (cVar5 == '\0') {
            bVar1 = simple_strtol(iVar3,0,10);
            iVar3 = rstrtok(0,&_LC156);
            cVar5 = '\x01';
            if (iVar3 == 0) break;
          }
          if (-1 < DebugLevel) {
            printk("%s: set wrong parameters\n","_SetSKUCtrl");
          }
          cVar5 = cVar5 + '\x01';
          iVar3 = rstrtok(0,&_LC156);
        } while (iVar3 != 0);
        if (1 < bVar1) {
          if (DebugLevel < 0) {
            return 0;
          }
          printk("%s: Please input 1(Enable) or 0(Disable)!!\n","_SetSKUCtrl");
          return 0;
        }
      }
      if (0 < DebugLevel) {
        printk("%s: TxPowerSKUEn: %d\n","_SetSKUCtrl",bVar1);
      }
      *(byte *)(param_1 + param_2 + 0x794eaa) = bVar1;
      if (param_2 == 0) {
        *(byte *)(param_1 + 0xa3ba8c) = bVar1;
      }
      else {
        *(byte *)(param_1 + 0xa3abb4) = bVar1;
      }
      uVar4 = TxPowerSKUCtrl(param_1,bVar1,param_2);
      return uVar4;
    }
    if ((-1 < DebugLevel) &&
       (printk("%s: Wrong parameter format!!\n","_SetSKUCtrl"), -1 < DebugLevel)) {
      printk("%s: Please use input format like X (X = 0,1)!!\n","_SetSKUCtrl");
    }
  }
  return 0;
}

