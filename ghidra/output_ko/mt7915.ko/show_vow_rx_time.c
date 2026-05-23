// module: mt7915.ko
// function: show_vow_rx_time @ 0x46fb4
// size: 156 bytes
//

undefined4 show_vow_rx_time(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  uVar1 = vow_get_rx_time_counter(param_1,1,0);
  uVar2 = vow_get_rx_time_counter(param_1,1,1);
  uVar3 = vow_get_rx_time_counter(param_1,2,0);
  uVar4 = vow_get_rx_time_counter(param_1,2,1);
  if (-1 < DebugLevel) {
    printk("%s: nonwifi %u/%u, obss %u/%u.\n","show_vow_rx_time",uVar1,uVar2,uVar3,uVar4);
  }
  return 1;
}

