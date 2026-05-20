// module: mt7915.ko
// function: Set_RadarDetectStart_Proc @ 0x234de0
// size: 588 bytes
//

undefined4 Set_RadarDetectStart_Proc(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 auStack_33 [3];
  char local_30;
  
  iVar2 = os_str_tol(param_2,0,10);
  iVar3 = hc_radio_query_by_rf(param_1,2,auStack_33);
  if (iVar3 == 0) {
    if (2 < DebugLevel) {
      printk("In Set_RadarDetectStart_Proc:\n");
    }
    uVar1 = *(undefined1 *)(param_1 + 0x795075);
    if (iVar2 == 0) {
      mtRddControl(param_1,0,0,0,0);
      mtRddControl(param_1,1,0,0,uVar1);
      mtRddControl(param_1,2,0,0,1);
      *(undefined1 *)(param_1 + 0x7953ee) = 1;
      return 1;
    }
    if (iVar2 == 1) {
      mtRddControl(param_1,0,1,0,0);
      mtRddControl(param_1,1,1,0,uVar1);
      mtRddControl(param_1,2,1,0,1);
      *(undefined1 *)(param_1 + 0x7953ee) = 1;
      uVar4 = 1;
    }
    else if (iVar2 == 2) {
      mtRddControl(param_1,0,0,0,0);
      mtRddControl(param_1,1,0,0,uVar1);
      mtRddControl(param_1,2,0,0,1);
      if (local_30 == '\x06' || local_30 == '\x03') {
        mtRddControl(param_1,0,1,0,0);
        mtRddControl(param_1,1,1,0,uVar1);
        mtRddControl(param_1,2,1,0,1);
      }
      else if (2 < DebugLevel) {
        printk("In Set_RadarDetectStart_Proc: Bandwidth not 80+80 or 160\n");
      }
      uVar4 = 1;
      *(undefined1 *)(param_1 + 0x7953ee) = 1;
    }
    else {
      uVar4 = 1;
    }
  }
  else if (DebugLevel < 0) {
    uVar4 = 0;
  }
  else {
    printk("%s(): cannot get info\n","Set_RadarDetectStart_Proc");
    uVar4 = 0;
  }
  return uVar4;
}

