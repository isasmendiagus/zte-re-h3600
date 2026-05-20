// module: mt7915.ko
// function: AsicExtPwrMgtBitWifi @ 0x134924
// size: 40 bytes
//

void AsicExtPwrMgtBitWifi(undefined4 param_1,undefined2 param_2,undefined1 param_3)

{
  undefined4 local_c;
  
  local_c = (uint)CONCAT12(param_3,param_2);
  MtCmdExtPwrMgtBitWifi(param_1,local_c);
  return;
}

