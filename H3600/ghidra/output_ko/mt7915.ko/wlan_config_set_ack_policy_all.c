// module: mt7915.ko
// function: wlan_config_set_ack_policy_all @ 0x10646c
// size: 60 bytes
//

void wlan_config_set_ack_policy_all(int param_1,int param_2)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = param_1 + 0x680;
  do {
    iVar4 = *(int *)(param_1 + 8);
    puVar2 = (undefined1 *)(iVar4 + 5);
    puVar1 = (undefined1 *)(param_2 + -1);
    do {
      puVar1 = puVar1 + 1;
      puVar2 = puVar2 + 1;
      *puVar2 = *puVar1;
    } while (puVar2 != (undefined1 *)(iVar4 + 9));
    param_1 = param_1 + 0x10;
  } while (param_1 != iVar3);
  return;
}

