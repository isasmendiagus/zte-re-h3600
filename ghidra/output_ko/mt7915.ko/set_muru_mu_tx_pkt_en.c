// module: mt7915.ko
// function: set_muru_mu_tx_pkt_en @ 0x23db54
// size: 268 bytes
//

bool set_muru_mu_tx_pkt_en(undefined4 param_1,undefined1 *param_2)

{
  int iVar1;
  bool bVar2;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_2c = 0;
  local_30 = 0x6a;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  if (2 < DebugLevel) {
    printk("%s: u1BandIdx = %d, u1MuTxEn = %d\n","set_muru_mu_tx_pkt_en",*param_2,param_2[1]);
  }
  iVar1 = AndesAllocCmdMsg(param_1,0xc);
  bVar2 = iVar1 != 0;
  if (bVar2) {
    local_2c = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_2c));
    local_28 = CONCAT31(local_28._1_3_,10);
    AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,local_20,local_1c);
    AndesAppendCmdMsg(iVar1,&local_30,4);
    AndesAppendCmdMsg(iVar1,param_2,8);
    AndesSendCmdMsg(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s: Ret = %d\n","set_muru_mu_tx_pkt_en",bVar2);
  }
  return bVar2;
}

