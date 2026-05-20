// module: mt7915.ko
// function: HwCtrlWifiSysPeerLinkUp @ 0xaec60
// size: 60 bytes
//

undefined4 HwCtrlWifiSysPeerLinkUp(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (*(code **)(param_1 + 0x285cf0) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000aec88. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(param_1 + 0x285cf0))(*(undefined4 *)(param_2 + 8));
    return uVar1;
  }
  AsicNotSupportFunc(param_1,"HwCtrlWifiSysPeerLinkUp");
  return 0;
}

