// module: mt7915.ko
// function: AsicDevInfoUpdate @ 0x1346b0
// size: 204 bytes
//

undefined4 AsicDevInfoUpdate(int param_1,undefined4 param_2,undefined1 *param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (2 < DebugLevel) {
    printk("%s(): Set OwnMac=%02x:%02x:%02x:%02x:%02x:%02x\n","AsicDevInfoUpdate",*param_3,
           param_3[1],param_3[2],param_3[3],param_3[4],param_3[5]);
  }
  if (*(code **)(iVar1 + 0x24) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00134728. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (**(code **)(iVar1 + 0x24))(param_1,param_2,param_3,param_4);
    return uVar2;
  }
  AsicNotSupportFunc(param_1,"AsicDevInfoUpdate");
  return 0;
}

