// module: mt7915.ko
// function: HwCtrlGreenAPOnOff @ 0xaf054
// size: 28 bytes
//

undefined4 HwCtrlGreenAPOnOff(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 *puVar1;
  
  puVar1 = *(undefined1 **)(param_2 + 8);
  AsicGreenAPOnOffCtrl(param_1,*puVar1,puVar1[1],puVar1,param_4);
  return 0;
}

