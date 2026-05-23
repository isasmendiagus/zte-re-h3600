// module: rtkatm.ko
// function: ptm_start_xmit @ 0x10a78
// size: 140 bytes
//

undefined4 ptm_start_xmit(int param_1)

{
  int iVar1;
  
  iVar1 = dev_get_by_name(&init_net,&_LC22);
  if (iVar1 != 0) {
    *(int *)(param_1 + 0x18) = iVar1;
    (**(code **)(*(int *)(iVar1 + 300) + 0x10))(param_1);
    return 0;
  }
  ProcKernLog("/home/ws/zx279128s/chip_zx279128s/kmodule/rtk_atm/rtk_atm.c",0x22d,"ptm_start_xmit",0
              ,7,0,"ptm_start_xmit eth_netdev=null\n");
  consume_skb(param_1);
  return 0;
}

