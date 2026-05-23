// module: mt7915.ko
// function: ShowPseData @ 0xe1560
// size: 220 bytes
//

undefined4 ShowPseData(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  
  iVar3 = hc_get_chip_dbg(*(undefined4 *)(param_1 + 0xa797a0));
  iVar4 = rstrtok(param_2,&_LC274);
  if (iVar4 != 0) {
    uVar1 = os_str_tol(iVar4,0,10);
    iVar4 = rstrtok(0,&_LC274);
    if (iVar4 != 0) {
      uVar2 = os_str_tol(iVar4,0,10);
      if (*(code **)(iVar3 + 0x1c) == (code *)0x0) {
        return 0;
      }
                    /* WARNING: Could not recover jumptable at 0x000e15e8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar5 = (**(code **)(iVar3 + 0x1c))(*(undefined4 *)(param_1 + 0xa797a0),uVar1,uVar2);
      return uVar5;
    }
  }
  if ((0 < DebugLevel) &&
     (printk("%s: param = %s not correct\n","ShowPseData",param_2), 0 < DebugLevel)) {
    printk("%s: iwpriv ra0 show psedata=startfid,framenums\n","ShowPseData");
  }
  return 0;
}

