// module: mt7915.ko
// function: Set_ConWpsApDisabled_Proc @ 0x29854
// size: 92 bytes
//

undefined4 Set_ConWpsApDisabled_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = simple_strtol(param_2,0,10);
  iVar1 = DebugLevel;
  (&DAT_0036da52)[param_1] = (char)uVar2;
  if (0 < iVar1) {
    printk("%s Now: %s, Ap Disabled = %d\n","Set_ConWpsApDisabled_Proc",*(undefined4 *)(param_1 + 4)
           ,uVar2);
  }
  return 1;
}

