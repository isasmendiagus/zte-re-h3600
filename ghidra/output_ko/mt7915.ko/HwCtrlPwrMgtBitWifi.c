// module: mt7915.ko
// function: HwCtrlPwrMgtBitWifi @ 0xaef64
// size: 28 bytes
//

undefined4 HwCtrlPwrMgtBitWifi(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined2 *puVar1;
  
  puVar1 = *(undefined2 **)(param_2 + 8);
  AsicExtPwrMgtBitWifi(param_1,*puVar1,*(undefined1 *)(puVar1 + 1),puVar1,param_4);
  return 0;
}

