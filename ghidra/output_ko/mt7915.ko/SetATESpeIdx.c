// module: mt7915.ko
// function: SetATESpeIdx @ 0x26814c
// size: 364 bytes
//

undefined4 SetATESpeIdx(undefined4 param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  size_t sVar1;
  int iVar2;
  char cVar3;
  undefined4 uVar4;
  
  if (param_2 == (char *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: No parameters!!\n","SetATESpeIdx",param_3,DebugLevel,param_4);
      return 0;
    }
    return 0;
  }
  sVar1 = strlen(param_2);
  if (sVar1 != 1) {
    if (-1 < DebugLevel) {
      printk("%s: Wrong parameter format!!\n","SetATESpeIdx");
      return 0;
    }
    return 0;
  }
  iVar2 = rstrtok(param_2,&_LC2);
  uVar4 = 1;
  if (iVar2 != 0) {
    cVar3 = '\0';
    do {
      if (cVar3 == '\0') {
        BF_ON_certification = simple_strtol(iVar2,0,10);
        iVar2 = rstrtok(0,&_LC2);
        cVar3 = '\x01';
        if (iVar2 == 0) break;
      }
      uVar4 = 0;
      if (-1 < DebugLevel) {
        printk("%s: Set wrong parameters\n","SetATESpeIdx");
      }
      cVar3 = cVar3 + '\x01';
      iVar2 = rstrtok(0,&_LC2);
    } while (iVar2 != 0);
  }
  if (-1 < DebugLevel) {
    printk("%s: BF_ON_certification = %d !!!!!\n","SetATESpeIdx",BF_ON_certification,
           &BF_ON_certification,param_4);
  }
  return uVar4;
}

