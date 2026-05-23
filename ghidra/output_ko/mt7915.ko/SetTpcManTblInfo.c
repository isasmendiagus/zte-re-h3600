// module: mt7915.ko
// function: SetTpcManTblInfo @ 0xc1de8
// size: 184 bytes
//

undefined4 SetTpcManTblInfo(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: No parameters!!\n","SetTpcManTblInfo");
    }
    return 0;
  }
  iVar2 = rstrtok(param_2,&_LC156);
  uVar1 = 0;
  if (iVar2 != 0) {
    uVar1 = os_str_tol(iVar2,0,10);
    iVar2 = rstrtok(0,&_LC156);
    if (iVar2 != 0) {
      if (-1 < DebugLevel) {
        printk("%s: set wrong parameters\n","SetTpcManTblInfo");
        return 0;
      }
      return 0;
    }
  }
  uVar3 = TpcManTblInfo(param_1,uVar1);
  return uVar3;
}

