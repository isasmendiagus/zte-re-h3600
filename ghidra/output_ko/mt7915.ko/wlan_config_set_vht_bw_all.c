// module: mt7915.ko
// function: wlan_config_set_vht_bw_all @ 0x1069c8
// size: 28 bytes
//

void wlan_config_set_vht_bw_all(int param_1,undefined1 param_2)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = param_1 + 0x680;
  do {
    piVar1 = (int *)(param_1 + 8);
    param_1 = param_1 + 0x10;
    *(undefined1 *)(*piVar1 + 0x5c) = param_2;
  } while (param_1 != iVar2);
  return;
}

