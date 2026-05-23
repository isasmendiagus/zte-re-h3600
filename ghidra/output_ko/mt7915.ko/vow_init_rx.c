// module: mt7915.ko
// function: vow_init_rx @ 0x426d4
// size: 288 bytes
//

void vow_init_rx(int param_1)

{
  uint uVar1;
  uint uVar2;
  
  if ((*(uint *)(param_1 + 0xa7a2e8) & 0xff00ff) == 0) {
    *(undefined1 *)(param_1 + 0xa79826) = 0;
    vow_set_rx_airtime(param_1,1,1);
    return;
  }
  vow_set_rx_airtime(param_1,2,1);
  vow_set_rx_airtime(param_1,1,1);
  vow_set_rx_airtime(param_1,3,1);
  uVar2 = 0;
  vow_set_backoff_time(param_1,7);
  vow_set_backoff_time(param_1,6);
  vow_set_backoff_time(param_1,4);
  vow_set_backoff_time(param_1,5);
  do {
    uVar1 = uVar2 & 0xff;
    uVar2 = uVar2 + 1;
    vow_set_backoff_time(param_1,uVar1);
  } while (uVar2 != 4);
  uVar2 = 0;
  do {
    uVar1 = uVar2 & 0xff;
    uVar2 = uVar2 + 1;
    vow_set_mbss2wmm_map(param_1,uVar1);
  } while (uVar2 != 0x10);
  uVar2 = 0;
  do {
    uVar1 = uVar2 & 0xff;
    uVar2 = uVar2 + 1;
    vow_set_wmm_selection(param_1,uVar1);
  } while (uVar2 != 4);
  if ((*(uint *)(param_1 + 0xa797a8) & 2) == 0) {
    return;
  }
  uVar2 = 0;
  do {
    uVar1 = uVar2 & 0xff;
    uVar2 = uVar2 + 1;
    vow_set_at_estimator_group(param_1,3,uVar1);
  } while (uVar2 != 0x10);
  return;
}

