// module: switch.ko
// function: ethdrv_recv_fin @ 0x10930
// size: 152 bytes
//

undefined4 ethdrv_recv_fin(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined2 uVar2;
  int *piVar3;
  
  if (param_2 == 0) {
    __dev_kfree_skb_any(param_1,1);
    return 0xffffffff;
  }
  piVar3 = (int *)ethdrv_port_dev_get_stats(param_2);
  *piVar3 = *piVar3 + 1;
  piVar3[2] = piVar3[2] + *(int *)(param_1 + 100);
  uVar2 = eth_type_trans(param_1,param_2);
  *(int *)(param_1 + 0x18) = param_2;
  uVar1 = jiffies;
  *(undefined2 *)(param_1 + 0xac) = uVar2;
  *(undefined4 *)(param_2 + 0x1d8) = uVar1;
  if ((*(byte *)(param_1 + 0x74) & 7) == 2) {
    piVar3[8] = piVar3[8] + 1;
  }
  netif_receive_skb_sk(*(undefined4 *)(param_1 + 0x14),param_1);
  return 0;
}

