// module: mt7915.ko
// function: hqa_set_tx_time @ 0x276a70
// size: 256 bytes
//

undefined4 hqa_set_tx_time(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int local_28;
  undefined4 local_24;
  int local_20;
  int local_1c [2];
  
  local_28 = param_3 + 0xc;
  local_24 = 0;
  local_20 = 0;
  local_1c[0] = 0;
  FUN_00276034(1,4,&local_28,&local_24);
  FUN_00276034(1,4,&local_28,&local_20);
  FUN_00276034(1,4,&local_28,local_1c);
  iVar1 = net_ad_wrap_service(param_1);
  iVar1 = local_20 * 0xd18 + iVar1;
  *(char *)(param_1 + 0xa3ae36) = (char)local_20;
  if (local_1c[0] == 1) {
    *(undefined1 *)(iVar1 + 0x10ec) = 1;
  }
  else {
    *(undefined1 *)(iVar1 + 0x10ec) = 0;
    *(undefined4 *)(iVar1 + 0x10f0) = 0;
  }
  *(undefined4 *)(param_3 + 0xe) = local_24;
  FUN_0026cdd0(param_3,param_2,6,0);
  if (0 < DebugLevel) {
    printk("%s: band_idx:%u, is_tx_time:%d\n","hqa_set_tx_time",local_20,local_1c[0]);
  }
  return 0;
}

