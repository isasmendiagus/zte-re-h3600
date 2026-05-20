// module: mt7915.ko
// function: wlan_config_set_ack_policy @ 0x106448
// size: 36 bytes
//

void wlan_config_set_ack_policy(int param_1,int param_2)

{
  undefined1 *puVar1;
  int iVar2;
  undefined1 *puVar3;
  
  iVar2 = *(int *)(param_1 + 0xb10);
  puVar1 = (undefined1 *)(param_2 + -1);
  puVar3 = (undefined1 *)(iVar2 + 5);
  do {
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
    *puVar3 = *puVar1;
  } while (puVar3 != (undefined1 *)(iVar2 + 9));
  return;
}

