// module: mt7915.ko
// function: SetTpcAlgoUlUtCfg @ 0xc1ea4
// size: 248 bytes
//

undefined4 SetTpcAlgoUlUtCfg(undefined4 param_1,int param_2)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint local_18;
  undefined4 local_14;
  
  uVar5 = 0;
  local_18 = 0;
  local_14 = 0;
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: No parameters!!\n","SetTpcAlgoUlUtCfg");
    }
    return 0;
  }
  iVar2 = rstrtok(param_2,&_LC156);
  if (iVar2 == 0) {
    uVar5 = 0;
    uVar4 = 0;
  }
  else {
    do {
      uVar1 = os_str_tol(iVar2,0,10);
      uVar4 = uVar5 & 0xff;
      uVar5 = uVar5 + 1;
      *(undefined2 *)((int)&local_18 + uVar4 * 2) = uVar1;
      iVar2 = rstrtok(0,&_LC156);
    } while (iVar2 != 0);
    uVar5 = local_18 & 0xff;
    uVar4 = local_18 >> 0x10 & 0xff;
    if (0x1f < uVar5) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("%s: Set wrong parameters! Entry index should be between 0~31 .\n","SetTpcAlgoUlUtCfg")
      ;
      return 0;
    }
  }
  uVar3 = TpcUlUtVarCfg(param_1,uVar5,uVar4,(int)(short)local_14);
  return uVar3;
}

