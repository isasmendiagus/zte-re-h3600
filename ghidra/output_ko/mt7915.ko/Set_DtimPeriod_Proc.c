// module: mt7915.ko
// function: Set_DtimPeriod_Proc @ 0x33ee4
// size: 112 bytes
//

bool Set_DtimPeriod_Proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  bool bVar1;
  short sVar2;
  
  sVar2 = os_str_tol(param_2,0,10,param_4,param_4);
  bVar1 = (ushort)(sVar2 - 1U) < 0xff;
  if (bVar1) {
    (&DAT_0036b8a0)[param_1] = (char)sVar2;
  }
  if (2 < DebugLevel) {
    printk("Set_DtimPeriod_Proc::(DtimPeriod=%d)\n",(&DAT_0036b8a0)[param_1]);
  }
  return bVar1;
}

