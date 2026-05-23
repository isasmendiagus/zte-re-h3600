// module: mt7915.ko
// function: Set_AP_WpaMixPairCipher_Proc @ 0x281b4
// size: 36 bytes
//

undefined4 Set_AP_WpaMixPairCipher_Proc(undefined4 param_1,undefined4 param_2)

{
  Set_SecAuthMode_Proc();
  Set_SecEncrypType_Proc(param_1,param_2);
  return 1;
}

