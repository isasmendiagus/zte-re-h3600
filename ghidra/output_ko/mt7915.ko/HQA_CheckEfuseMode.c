// module: mt7915.ko
// function: HQA_CheckEfuseMode @ 0x26f1fc
// size: 132 bytes
//

undefined4 HQA_CheckEfuseMode(int param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_CheckEfuseMode");
  }
  if ("Set_IRR_TTGOnOff"[param_1 + 1] == '\0') {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x1000000;
  }
  *(undefined4 *)(param_3 + 0xe) = uVar1;
  FUN_0026cdd0(param_3,param_2,6);
  return 0;
}

