// module: mt7915.ko
// function: mt_op_set_clean_persta_txq @ 0x2573bc
// size: 164 bytes
//

undefined4
mt_op_set_clean_persta_txq
          (int param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined1 param_5)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_64;
  undefined1 local_63;
  undefined1 local_60;
  undefined1 local_5f;
  undefined1 local_5e;
  undefined1 local_5d;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x503;
  }
  else {
    sys_ad_zero_mem(&local_64,0x4c);
    local_5f = (undefined1)*(undefined2 *)(param_3 + 0xe0);
    local_64 = 1;
    local_63 = 0x1c;
    local_60 = (undefined1)param_2;
    local_5e = param_5;
    local_5d = (undefined1)param_4;
    printk("%s: wcid[%d], pause=%u, band_idx=%u, reserved[0]=%u\n","mt_op_set_clean_persta_txq",
           *(undefined2 *)(param_3 + 0xe0),param_2,param_5,param_4);
    iVar1 = MtCmdATETest(iVar1,&local_64);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0x501;
    }
  }
  return uVar2;
}

