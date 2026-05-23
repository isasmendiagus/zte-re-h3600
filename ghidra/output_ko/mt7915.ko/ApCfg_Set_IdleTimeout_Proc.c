// module: mt7915.ko
// function: ApCfg_Set_IdleTimeout_Proc @ 0x3ef98
// size: 108 bytes
//

undefined4 ApCfg_Set_IdleTimeout_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = os_str_tol(param_2,0,10);
  if (iVar1 < 0x3c) {
    *(undefined4 *)(&DAT_0036b90c + param_1) = 0x3c;
  }
  else {
    *(int *)(&DAT_0036b90c + param_1) = iVar1;
  }
  if (2 < DebugLevel) {
    printk("%s : IdleTimeout=%d\n","ApCfg_Set_IdleTimeout_Proc",
           *(undefined4 *)(&DAT_0036b90c + param_1));
  }
  return 1;
}

