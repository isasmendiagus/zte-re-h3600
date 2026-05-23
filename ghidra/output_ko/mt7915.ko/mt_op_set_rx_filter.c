// module: mt7915.ko
// function: mt_op_set_rx_filter @ 0x257304
// size: 180 bytes
//

undefined4 mt_op_set_rx_filter(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_70;
  undefined4 uStack_6c;
  undefined1 local_64 [4];
  char local_60;
  undefined1 local_5e;
  undefined1 local_5c;
  undefined1 local_5b;
  undefined1 local_58;
  undefined1 local_56;
  
  local_70 = param_2;
  uStack_6c = param_3;
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x503;
  }
  else {
    sys_ad_zero_mem(local_64,8);
    sys_ad_move_mem(local_64,&local_70,8);
    sys_ad_zero_mem(&local_5c,0x4c);
    local_5c = 1;
    local_5b = 3;
    if (local_60 != '\0') {
      local_58 = 1;
    }
    local_56 = local_5e;
    printk("%s: band_idx=%u\n","mt_op_set_rx_filter");
    iVar1 = MtCmdATETest(iVar1,&local_5c);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0x501;
    }
  }
  return uVar2;
}

