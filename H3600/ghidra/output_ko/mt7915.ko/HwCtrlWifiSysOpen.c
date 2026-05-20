// module: mt7915.ko
// function: HwCtrlWifiSysOpen @ 0xaed20
// size: 60 bytes
//

undefined4 HwCtrlWifiSysOpen(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (*(code **)(param_1 + 0x285ce0) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000aed48. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(param_1 + 0x285ce0))(*(undefined4 *)(param_2 + 8));
    return uVar1;
  }
  AsicNotSupportFunc(param_1,"HwCtrlWifiSysOpen");
  return 0;
}

