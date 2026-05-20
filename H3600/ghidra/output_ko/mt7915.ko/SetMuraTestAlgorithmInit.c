// module: mt7915.ko
// function: SetMuraTestAlgorithmInit @ 0x9515c
// size: 192 bytes
//

undefined4 SetMuraTestAlgorithmInit(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  if (uVar2 != 0x7626 && (uVar2 != 0x7663 && uVar2 != 0x7615)) {
    if (-1 < DebugLevel) {
      printk("%s: Not Supported (Ret = %d_\n","SetMuraTestAlgorithmInit",0);
      return 0;
    }
    return 0;
  }
  if (param_2 != 0) {
    iVar1 = os_str_tol(param_2,0,10);
    if (iVar1 == 0) {
      SetMuraTestAlgorithmProc(param_1,&_LC69);
      return 1;
    }
    return 1;
  }
  return 0;
}

