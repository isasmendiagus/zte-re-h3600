// module: mt7915.ko
// function: Set_ConWpsApcliAutoPreferIface_Proc @ 0x2a850
// size: 92 bytes
//

undefined4 Set_ConWpsApcliAutoPreferIface_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = os_str_tol(param_2,0,10);
  iVar1 = DebugLevel;
  *(undefined4 *)(&DAT_0036da8c + param_1) = uVar2;
  if (0 < iVar1) {
    printk("%s Now: %s, PreferIface = %d\n","Set_ConWpsApcliAutoPreferIface_Proc",
           *(undefined4 *)(param_1 + 4),uVar2);
  }
  return 1;
}

