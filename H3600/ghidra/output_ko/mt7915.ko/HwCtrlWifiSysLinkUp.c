// module: mt7915.ko
// function: HwCtrlWifiSysLinkUp @ 0xaed60
// size: 60 bytes
//

undefined4 HwCtrlWifiSysLinkUp(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (*(code **)(param_1 + 0x285ce8) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000aed88. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(param_1 + 0x285ce8))(*(undefined4 *)(param_2 + 8));
    return uVar1;
  }
  AsicNotSupportFunc(param_1,"HwCtrlWifiSysLinkUp");
  return 0;
}

