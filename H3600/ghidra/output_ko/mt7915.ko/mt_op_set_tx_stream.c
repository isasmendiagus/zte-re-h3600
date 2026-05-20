// module: mt7915.ko
// function: mt_op_set_tx_stream @ 0x257268
// size: 136 bytes
//

undefined4 mt_op_set_tx_stream(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_5c;
  undefined1 local_5b;
  undefined1 local_58;
  undefined1 local_57;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x503;
  }
  else {
    sys_ad_zero_mem(&local_5c,0x4c);
    local_5c = 1;
    local_5b = 4;
    local_58 = (undefined1)param_2;
    local_57 = (undefined1)param_3;
    printk("%s: stream_nums=%u, band_idx=%u\n","mt_op_set_tx_stream",param_2,param_3);
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

