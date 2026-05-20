// module: mt7915.ko
// function: Set_ConWpsApCliMode_Proc @ 0x2a7dc
// size: 112 bytes
//

undefined4 Set_ConWpsApCliMode_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = os_str_tol(param_2,0,10);
  iVar1 = DebugLevel;
  if (2 < uVar2) {
    return 0;
  }
  *(uint *)(&DAT_0036da4c + param_1) = uVar2;
  if (iVar1 < 1) {
    return 1;
  }
  printk("%s Now: %s, Mode = %d\n","Set_ConWpsApCliMode_Proc",*(undefined4 *)(param_1 + 4),uVar2);
  return 1;
}

