// module: mt7915.ko
// function: Set_BeaconLostTime_Proc @ 0x57c18
// size: 152 bytes
//

undefined4
Set_BeaconLostTime_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(*param_1 + 0x3c);
  iVar1 = os_str_tol(param_2,0,10,*param_1,param_4);
  if (iVar1 - 1U < 0x3c) {
    param_1[iVar2 * 0x84dec + 0x15ffec] = iVar1 * 100;
  }
  if (2 < DebugLevel) {
    printk("IF Set_BeaconLostTime_Proc::(BeaconLostTime=%ld)\n",param_1[iVar2 * 0x84dec + 0x15ffec])
    ;
  }
  return 1;
}

