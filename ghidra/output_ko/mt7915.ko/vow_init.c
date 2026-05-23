// module: mt7915.ko
// function: vow_init @ 0x42990
// size: 256 bytes
//

void vow_init(int param_1)

{
  uint uVar1;
  uint uVar2;
  undefined1 *puVar3;
  bool bVar4;
  
  pvow_pad = param_1;
  if (2 < DebugLevel) {
    printk(&_LC47,"vow_init");
  }
  uVar2 = 0;
  *(undefined4 *)(param_1 + 0xa797a8) = 3;
  puVar3 = (undefined1 *)(param_1 + 0xa7bea7);
  if (*(char *)(param_1 + 0xa797a4) == '\x02') {
    *(undefined4 *)(param_1 + 0xa797a8) = 7;
  }
  *(undefined2 *)(param_1 + 0xa7bec8) = 0x10;
  vow_init_CR_offset(param_1);
  vow_init_sta(param_1);
  vow_init_group(param_1);
  vow_init_rx(param_1);
  vow_init_misc(param_1);
  vow_set_feature_all(param_1);
  os_zero_mem(param_1 + 0xa7bea8,0x20);
  while( true ) {
    uVar1 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    bVar4 = 0x1f < uVar2;
    if (uVar2 != 0x20) {
      bVar4 = uVar1 <= uVar2;
    }
    uVar2 = uVar2 + 1;
    if (bVar4) break;
    puVar3 = puVar3 + 1;
    *puVar3 = 0;
  }
  if (2 < DebugLevel) {
    printk(&_LC48,"vow_init");
    return;
  }
  return;
}

