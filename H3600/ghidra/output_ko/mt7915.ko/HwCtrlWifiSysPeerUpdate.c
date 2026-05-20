// module: mt7915.ko
// function: HwCtrlWifiSysPeerUpdate @ 0xaec20
// size: 64 bytes
//

undefined4 HwCtrlWifiSysPeerUpdate(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (*(code **)(param_1 + 0x285cf8) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000aec48. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(param_1 + 0x285cf8))(*(undefined4 *)(param_2 + 8));
    return uVar1;
  }
  AsicNotSupportFunc(param_1,"HwCtrlWifiSysPeerUpdate");
  return 0;
}

