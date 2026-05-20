// module: mt7915.ko
// function: MT_ATESetTxPower3 @ 0x27fb04
// size: 120 bytes
//

undefined4
MT_ATESetTxPower3(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  undefined4 uVar1;
  
  uVar1 = MT_ATESetTxPowerX(param_1,3,param_3,param_4,param_5,param_6);
  if (2 < DebugLevel) {
    printk(&_LC65,"MT_ATESetTxPower3");
  }
  return uVar1;
}

