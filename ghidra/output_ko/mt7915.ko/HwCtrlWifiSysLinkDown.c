// module: mt7915.ko
// function: HwCtrlWifiSysLinkDown @ 0xaeda0
// size: 60 bytes
//

undefined4 HwCtrlWifiSysLinkDown(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (*(code **)(param_1 + 0x285cec) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000aedc8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(param_1 + 0x285cec))(*(undefined4 *)(param_2 + 8));
    return uVar1;
  }
  AsicNotSupportFunc(param_1,"HwCtrlWifiSysLinkDown");
  return 0;
}

