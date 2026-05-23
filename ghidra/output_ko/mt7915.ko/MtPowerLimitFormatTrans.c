// module: mt7915.ko
// function: MtPowerLimitFormatTrans @ 0x151970
// size: 408 bytes
//

undefined4 MtPowerLimitFormatTrans(undefined4 param_1,char *param_2,char *param_3)

{
  undefined4 uVar1;
  char cVar2;
  byte bVar3;
  size_t sVar4;
  char *pcVar5;
  int iVar6;
  undefined4 uVar7;
  
  if (param_2 == (char *)0x0) {
    if (DebugLevel < 1) {
      return 1;
    }
    printk("%s: null pointer for buffer to update transform result !!\n","MtPowerLimitFormatTrans");
    uVar7 = 1;
  }
  else if (param_3 == (char *)0x0) {
    if (DebugLevel < 1) {
      return 1;
    }
    printk("%s: null pointer for raw data buffer !!\n","MtPowerLimitFormatTrans");
    uVar7 = 1;
  }
  else {
    sVar4 = strspn(param_3," ");
    param_3 = param_3 + sVar4;
    pcVar5 = strchr(param_3,0x2e);
    uVar1 = __rstrtok;
    if (pcVar5 == (char *)0x0) {
      cVar2 = os_str_tol(param_3,0,10);
      *param_2 = cVar2 << 1;
      uVar7 = 0;
    }
    else {
      iVar6 = rstrtok(param_3,&_LC26);
      if (iVar6 == 0) {
        if (DebugLevel < 1) {
          return 1;
        }
        printk("%s: null pointer for integer value parsing !!\n","MtPowerLimitFormatTrans");
        uVar7 = 1;
      }
      else {
        cVar2 = os_str_tol(iVar6,0,10);
        *param_2 = cVar2 << 1;
        iVar6 = rstrtok(0,&_LC26);
        if (iVar6 == 0) {
          if (0 < DebugLevel) {
            printk("%s: null pointer for decimal value parsing !!\n","MtPowerLimitFormatTrans");
          }
          return 1;
        }
        bVar3 = os_str_tol(iVar6,0,10);
        if (4 < bVar3) {
          *param_2 = *param_2 + '\x01';
        }
        uVar7 = 0;
        __rstrtok = uVar1;
      }
    }
  }
  return uVar7;
}

