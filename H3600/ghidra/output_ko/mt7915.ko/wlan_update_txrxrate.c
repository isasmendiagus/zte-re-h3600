// module: mt7915.ko
// function: wlan_update_txrxrate @ 0x1570dc
// size: 536 bytes
//

void wlan_update_txrxrate(int param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  undefined1 auStack_a8 [64];
  undefined1 auStack_68 [68];
  
  if (*param_2 != 0x20001 && *param_2 != 0x4001) {
    return;
  }
  if (param_2[0x3f] != 2) {
    return;
  }
  uVar4 = param_2[0x4c4];
  uVar5 = param_2[0x4c5];
  uVar1 = param_2[0x4ce];
  uVar3 = param_2[0x4cf];
  bVar6 = uVar3 <= uVar5;
  if (uVar5 == uVar3) {
    bVar6 = uVar1 <= uVar4;
  }
  if (bVar6) {
    uVar2 = uVar4 - uVar1;
    uVar1 = uVar5 - (uVar3 + (uVar4 < uVar1));
  }
  else {
    uVar2 = (uVar4 - 1) - uVar1;
    uVar1 = (uVar5 - (uVar4 == 0)) - (uVar3 + (uVar4 - 1 < uVar1));
  }
  param_2[0x4d3] = uVar1 >> 7;
  param_2[0x4d2] = uVar2 >> 7 | uVar1 << 0x19;
  uVar1 = param_2[0x4d0];
  uVar3 = param_2[0x4d1];
  param_2[0x4ce] = uVar4;
  param_2[0x4cf] = uVar5;
  uVar4 = param_2[0x4c6];
  uVar5 = param_2[0x4c7];
  bVar6 = uVar3 <= uVar5;
  if (uVar5 == uVar3) {
    bVar6 = uVar1 <= uVar4;
  }
  if (bVar6) {
    uVar3 = uVar5 - (uVar3 + (uVar4 < uVar1));
    param_2[0x4d4] = uVar4 - uVar1 >> 7 | uVar3 * 0x2000000;
    param_2[0x4d5] = uVar3 >> 7;
  }
  else {
    uVar3 = (uVar5 - (uVar4 == 0)) - (uVar3 + (uVar4 - 1 < uVar1));
    param_2[0x4d4] = (uVar4 - 1) - uVar1 >> 7 | uVar3 * 0x2000000;
    param_2[0x4d5] = uVar3 >> 7;
  }
  param_2[0x4d0] = uVar4;
  param_2[0x4d1] = uVar5;
  if (*(char *)(param_1 + 0xa7d164) != '\0') {
    DataRateToString(param_1,auStack_a8,0x40,0,param_2);
    DataRateToString(param_1,auStack_68,0x40,1,param_2);
    printk("[%-7s#%-2d] %02x:%02x:%02x:%02x:%02x:%02x TX:%s(%uMbps) %8llu(Kbps) RX:%s(%uMbps) %8llu(Kbps) RSSI:(%d %d %d %d)\n"
           ,*(undefined4 *)param_2[2],(short)param_2[0x3e],(char)param_2[0x3b],
           *(undefined1 *)((int)param_2 + 0xed),*(undefined1 *)((int)param_2 + 0xee),
           *(undefined1 *)((int)param_2 + 0xef),(char)param_2[0x3c],
           *(undefined1 *)((int)param_2 + 0xf1),auStack_a8,param_2[0x50]);
  }
  return;
}

