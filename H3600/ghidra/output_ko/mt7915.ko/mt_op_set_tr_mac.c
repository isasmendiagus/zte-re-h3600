// module: mt7915.ko
// function: mt_op_set_tr_mac @ 0x2571cc
// size: 156 bytes
//

undefined4 mt_op_set_tr_mac(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_64;
  undefined1 local_63;
  undefined1 local_61;
  undefined1 local_60;
  undefined1 local_5f;
  undefined1 local_5e;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x503;
  }
  else {
    sys_ad_zero_mem(&local_64,0x4c);
    local_64 = 1;
    local_63 = 1;
    local_61 = 0xf;
    local_60 = (undefined1)param_2;
    local_5f = (undefined1)param_3;
    local_5e = (undefined1)param_4;
    printk("%s: op_type=%d, enable=%u, band_idx=%u\n","mt_op_set_tr_mac",param_2,param_3,param_4);
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

