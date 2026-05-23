// module: mt7915.ko
// function: set_muru_mu_tx_pkt_cnt @ 0x23dd24
// size: 288 bytes
//

bool set_muru_mu_tx_pkt_cnt(undefined4 param_1,undefined1 *param_2)

{
  int iVar1;
  bool bVar2;
  undefined4 local_38;
  undefined1 local_34 [4];
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_2c = 0;
  local_38 = 0x69;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  os_zero_mem(local_34,8);
  local_34[0] = *param_2;
  local_30 = *(undefined4 *)(param_2 + 4);
  if (2 < DebugLevel) {
    printk("%s: u1BandIdx = %d, u4MuTxPktCnt = %d\n","set_muru_mu_tx_pkt_cnt");
  }
  iVar1 = AndesAllocCmdMsg(param_1,0xc);
  bVar2 = iVar1 != 0;
  if (bVar2) {
    local_2c = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_2c));
    local_28 = CONCAT31(local_28._1_3_,10);
    AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,local_20,local_1c);
    AndesAppendCmdMsg(iVar1,&local_38,4);
    AndesAppendCmdMsg(iVar1,local_34,8);
    AndesSendCmdMsg(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s: Ret = %d\n","set_muru_mu_tx_pkt_cnt",bVar2);
  }
  return bVar2;
}

