// module: mt7915.ko
// function: Set_RadarDetectStop_Proc @ 0x235030
// size: 272 bytes
//

undefined4 Set_RadarDetectStop_Proc(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_1b [3];
  char local_18;
  
  iVar1 = hc_radio_query_by_rf(param_1,2,auStack_1b);
  if (iVar1 == 0) {
    iVar1 = os_str_tol(param_2,0,10);
    if (2 < DebugLevel) {
      printk("In Set_RadarDetectStop_Proc:\n");
    }
    if (iVar1 == 0) {
      mtRddControl(param_1,0,0,0,0);
      uVar2 = 1;
    }
    else {
      if (iVar1 != 1) {
        if (iVar1 != 2) {
          return 1;
        }
        mtRddControl(param_1,0,0,0,0);
        if (local_18 != '\x06' && local_18 != '\x03') {
          if (DebugLevel < 3) {
            return 1;
          }
          printk("In Set_RadarDetectStop_Proc: Bandwidth not 80+80 or 160\n");
          return 1;
        }
      }
      mtRddControl(param_1,0,1,0,0);
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

