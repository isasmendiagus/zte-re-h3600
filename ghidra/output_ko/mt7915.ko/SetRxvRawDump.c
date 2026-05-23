// module: mt7915.ko
// function: SetRxvRawDump @ 0xc0928
// size: 244 bytes
//

undefined4 SetRxvRawDump(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  int iVar2;
  
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: no parameter.\n","SetRxvRawDump",param_3,DebugLevel,param_4);
      return 0;
    }
    return 0;
  }
  iVar2 = rstrtok(param_2,&_LC156);
  if (iVar2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = os_str_tol(iVar2,0,10);
    iVar2 = rstrtok(0,&_LC156);
    if (iVar2 != 0) {
      if (-1 < DebugLevel) {
        printk("%s(): number of parameters exceed expectation.\n","SetRxvRawDump");
        return 0;
      }
      return 0;
    }
  }
  if (0 < DebugLevel) {
    printk("%s(): band_idx: %d\n","SetRxvRawDump",uVar1,DebugLevel,param_4);
  }
  chip_dump_rxv_raw_data(param_1,uVar1);
  return 1;
}

