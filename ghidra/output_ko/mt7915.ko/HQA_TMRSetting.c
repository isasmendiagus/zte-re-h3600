// module: mt7915.ko
// function: HQA_TMRSetting @ 0x27a7e8
// size: 388 bytes
//

undefined4 HQA_TMRSetting(undefined4 param_1,undefined4 param_2,int param_3)

{
  int local_3c;
  undefined4 local_38;
  int local_34;
  uint local_30;
  uint local_2c;
  char acStack_28 [8];
  char acStack_20 [12];
  
  local_3c = param_3 + 0xc;
  local_38 = 0;
  local_34 = 0;
  FUN_00276034(1,4,&local_3c,&local_38);
  FUN_00276034(1,4,&local_3c,&local_34);
  FUN_00276034(1,4,&local_3c,&local_30);
  FUN_00276034(1,4,&local_3c,&local_2c);
  if (0 < DebugLevel) {
    printk("%s: TMR setting: %u, TMR version: %u TMR throughold: %d TMR iter:%d\n","HQA_TMRSetting",
           local_38,local_34,local_30,local_2c);
  }
  if (local_34 == 100) {
    local_34 = 0;
  }
  else if (local_34 == 0x96) {
    local_34 = 1;
  }
  else {
    if (local_34 != 200) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("%s: Wrong version %d!!\n","HQA_TMRSetting",local_34);
      return 0;
    }
    local_34 = 2;
  }
  snprintf(acStack_28,8,"%d",local_38);
  snprintf(acStack_20,8,"%d",local_34);
  TmrUpdateParameter(param_1,local_30 & 0xff,local_2c & 0xff);
  setTmrVerProc(param_1,acStack_20);
  setTmrEnableProc(param_1,acStack_28);
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}

