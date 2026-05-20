// module: mt7915.ko
// function: Set_ConWpsApCliDisabled_Proc @ 0x2a8b0
// size: 92 bytes
//

undefined4 Set_ConWpsApCliDisabled_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = os_str_tol(param_2,0,10);
  iVar1 = DebugLevel;
  (&DAT_0036da51)[param_1] = (char)uVar2;
  if (0 < iVar1) {
    printk("%s Now: %s, ApClient Disabled = %d\n","Set_ConWpsApCliDisabled_Proc",
           *(undefined4 *)(param_1 + 4),uVar2);
  }
  return 1;
}

