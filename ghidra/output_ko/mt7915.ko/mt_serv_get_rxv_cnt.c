// module: mt7915.ko
// function: mt_serv_get_rxv_cnt @ 0x2519a0
// size: 96 bytes
//

void mt_serv_get_rxv_cnt(undefined4 *param_1,undefined4 *param_2)

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined4 local_14 [2];
  
  uVar1 = *(undefined1 *)(param_1 + 0x133);
  local_14[0] = 0;
  if (*(char *)(param_1 + 0x7d1) != '\0') {
    (**(code **)(param_1[0x7c4] + 0x11c))(*param_1);
    return;
  }
  uVar2 = *param_1;
  *param_2 = 1;
  net_ad_get_rxv_cnt(uVar2,uVar1,local_14);
  return;
}

