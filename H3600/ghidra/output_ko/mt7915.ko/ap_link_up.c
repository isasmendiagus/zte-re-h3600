// module: mt7915.ko
// function: ap_link_up @ 0x16c04
// size: 56 bytes
//

undefined4 ap_link_up(int param_1)

{
  if (*(int *)(param_1 + 0x990) == 0) {
    wifi_sys_linkup();
    APStartRekeyTimer(*(undefined4 *)(param_1 + 8),param_1);
  }
  *(uint *)(param_1 + 0xb18) = *(uint *)(param_1 + 0xb18) | 0x200000;
  return 1;
}

