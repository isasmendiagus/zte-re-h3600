// module: mt7915.ko
// function: wdev_ops_register @ 0x14dbac
// size: 56 bytes
//

undefined4 wdev_ops_register(int param_1,undefined4 param_2,int param_3,uint param_4)

{
  bool bVar1;
  
  bVar1 = param_4 == 1;
  if (bVar1) {
    param_4 = 0x7edc;
  }
  *(int *)(param_1 + 0x904) = param_3;
  if (bVar1) {
    *(uint *)(param_3 + 0x84) = param_4 & 0xffff | 0xc0000;
  }
  else if (param_4 == 2) {
    *(code **)(param_3 + 0x84) = detect_wmm_traffic;
  }
  wifi_mlme_ops_register();
  return 1;
}

