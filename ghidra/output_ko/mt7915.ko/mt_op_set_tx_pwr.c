// module: mt7915.ko
// function: mt_op_set_tx_pwr @ 0x2583dc
// size: 180 bytes
//

undefined4 mt_op_set_tx_pwr(int param_1,int param_2,undefined4 param_3,int *param_4)

{
  int iVar1;
  undefined4 uVar2;
  int local_40;
  int local_3c;
  uint local_38;
  undefined4 local_34;
  uint local_30;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  
  if (param_4 == (int *)0x0) {
    return 0x504;
  }
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x503;
  }
  else {
    local_40 = *param_4;
    local_38 = (uint)*(byte *)(param_2 + 0xc50);
    local_30 = (uint)*(byte *)(param_2 + 0xc51);
    local_3c = (int)*(char *)(param_2 + local_40 + 0xc98);
    local_34 = param_3;
    sys_ad_zero_mem(&local_2c,0x14);
    sys_ad_move_mem(&local_2c,&local_40,0x14);
    iVar1 = MtCmdSetTxPowerCtrl(iVar1,local_2c,uStack_28,uStack_24,uStack_20,uStack_1c);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0x501;
    }
  }
  return uVar2;
}

