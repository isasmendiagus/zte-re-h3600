// module: mt7915.ko
// function: Set_Lp_Proc @ 0xbaf68
// size: 200 bytes
//

undefined4 Set_Lp_Proc(int *param_1,undefined4 param_2)

{
  char cVar1;
  int *piVar2;
  
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    piVar2 = param_1 + *(int *)(*param_1 + 0x3c) * 0x160d + 0xadc92;
  }
  else {
    piVar2 = (int *)0x0;
  }
  cVar1 = os_str_tol(param_2,0,10);
  if (cVar1 == '\0') {
    MlmeLpExit(param_1);
    if (*(char *)((int)param_1 + 0x286285) == '\x01') {
      APStartUp(param_1,piVar2);
    }
    if (2 < DebugLevel) {
      printk("==>Set_Lp_Proc (Exit)\n");
    }
  }
  else {
    MlmeLpEnter();
    if (2 < DebugLevel) {
      printk("==>Set_Lp_Proc (Enetr)\n");
    }
  }
  return 1;
}

