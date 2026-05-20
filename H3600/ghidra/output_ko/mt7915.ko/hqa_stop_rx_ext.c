// module: mt7915.ko
// function: hqa_stop_rx_ext @ 0x2762c4
// size: 228 bytes
//

undefined4 hqa_stop_rx_ext(int param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  int local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_28 = param_3 + 0xc;
  iVar2 = *(int *)(param_1 + 0xa39fd4);
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  FUN_00276034(1,4,&local_28,&local_24);
  FUN_00276034(1,4,&local_28,&local_20);
  FUN_00276034(1,4,&local_28,&local_1c);
  *(char *)(param_1 + 0xa3ae36) = (char)local_1c;
  uVar1 = (**(code **)(iVar2 + 0x1c))(param_1);
  *(undefined4 *)(param_3 + 0xe) = local_24;
  FUN_0026cdd0(param_3,param_2,6,uVar1);
  if (2 < DebugLevel) {
    printk("%s: band_idx:%u\n","hqa_stop_rx_ext",local_1c);
  }
  return uVar1;
}

