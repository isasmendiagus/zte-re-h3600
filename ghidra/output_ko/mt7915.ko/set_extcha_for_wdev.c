// module: mt7915.ko
// function: set_extcha_for_wdev @ 0xde0a0
// size: 52 bytes
//

undefined4 set_extcha_for_wdev(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  if (param_3 == 0) {
    uVar1 = 3;
  }
  else {
    uVar1 = 1;
  }
  wlan_config_set_ext_cha(param_2,uVar1,param_3,param_4,param_4);
  SetCommonHtVht(param_1,param_2);
  return 1;
}

