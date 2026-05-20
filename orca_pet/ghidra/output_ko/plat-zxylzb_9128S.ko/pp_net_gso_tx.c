// module: plat-zxylzb_9128S.ko
// function: pp_net_gso_tx @ 0x1a234
// size: 112 bytes
//

undefined4 pp_net_gso_tx(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  
  pp_gso_tx._0_4_ = pp_gso_tx._0_4_ + 1;
  if ((*(byte *)(param_1 + 0x77) & 0x20) == 0) {
    iVar1 = *(int *)(param_2 + 0x4ec) + 1;
    *(int *)(param_2 + 0x4ec) = iVar1;
  }
  else {
    pp_net_tcp_gso_tx_upload();
    *(int *)(param_2 + 0x4d4) = *(int *)(param_2 + 0x4d4) + 1;
    param_3 = *(int *)(param_1 + 100);
    iVar1 = *(int *)(param_2 + 0x4dc) + param_3;
    *(int *)(param_2 + 0x4dc) = iVar1;
  }
  __dev_kfree_skb_any(param_1,1,param_3,iVar1,param_4);
  return 0;
}

