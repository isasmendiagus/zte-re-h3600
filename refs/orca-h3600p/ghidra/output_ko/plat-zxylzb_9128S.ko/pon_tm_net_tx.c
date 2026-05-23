// module: plat-zxylzb_9128S.ko
// function: pon_tm_net_tx @ 0x1a2a4
// size: 1000 bytes
//

undefined4 pon_tm_net_tx(int param_1,int param_2)

{
  code *pcVar1;
  char cVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  undefined1 auStack_28 [4];
  undefined4 local_24 [2];
  
  if (*(int *)(param_2 + 0x4c8) == 0) {
    ffe_learn_skb(param_1,3);
  }
  if ((*(uint *)(((uint)auStack_28 & 0xffffe000) + 4) & 0x1fff00) == 0) {
    uVar5 = _raw_spin_lock_irqsave(&net_lock_tx);
    iVar4 = *(int *)(param_2 + 0x4c8);
    if (iVar4 == 0) goto LAB_0001a360;
LAB_0001a2fc:
    if (iVar4 == 1) {
      if ((*(short *)(*(int *)(param_1 + 0xcc) + 2) != 0) || (*(int *)(param_1 + 0x68) != 0)) {
        pp_net_gso_tx(param_1,param_2,1);
        goto LAB_0001a310;
      }
      puVar3 = (undefined4 *)pon_tm_get_next_txdesc(1);
      if (puVar3 == (undefined4 *)0x0) {
        __dev_kfree_skb_any(param_1,1);
        *(int *)(param_2 + 0x4ec) = *(int *)(param_2 + 0x4ec) + 1;
        printk("get dn tx desc failed\n");
        goto LAB_0001a310;
      }
      *puVar3 = 0x80;
      iVar4 = test_da_unknown;
      puVar3[2] = 0x1000000;
      puVar3[1] = 0x10000;
      if (iVar4 == 0) {
        puVar3[3] = 3;
        *(ushort *)((int)puVar3 + 2) =
             *(ushort *)((int)puVar3 + 2) & 0xfc0f | (*(byte *)(param_1 + 0xbc) + 0x28 & 0x3f) << 4;
      }
      else {
        puVar3[3] = 2;
      }
      if (dev_qos_select_queue == (code *)0x0) {
        *(byte *)((int)puVar3 + 3) = *(byte *)((int)puVar3 + 3) & 0x1f;
      }
      else {
        *(byte *)((int)puVar3 + 3) =
             *(byte *)((int)puVar3 + 3) & 0x1f | (byte)((*(ushort *)(param_1 + 0x7a) & 7) << 5);
      }
      if (*(char *)(param_1 + 0xbd) != '\0') {
        *(byte *)((int)puVar3 + 0xe) = *(byte *)((int)puVar3 + 0xe) | 1;
        *(ushort *)((int)puVar3 + 0xe) =
             *(ushort *)((int)puVar3 + 0xe) & 1 | *(short *)(param_1 + 0xc2) << 1;
        puVar3[2] = puVar3[2] & 0xff8001ff | (uint)*(byte *)(param_1 + 0xbe) << 9;
      }
      iVar4 = pon_tm_data_raw_send(param_1,puVar3,1);
      if (iVar4 == 0) goto LAB_0001a5a0;
      if (net_txq._40_4_ == 0) {
        net_txq._40_4_ = 0x3ff;
      }
      else {
        net_txq._40_4_ = net_txq._40_4_ + -1;
      }
LAB_0001a494:
      *(int *)(param_2 + 0x4ec) = *(int *)(param_2 + 0x4ec) + 1;
    }
  }
  else {
    _raw_spin_lock();
    iVar4 = *(int *)(param_2 + 0x4c8);
    uVar5 = 0;
    if (iVar4 != 0) goto LAB_0001a2fc;
LAB_0001a360:
    local_24[0] = 0;
    iVar4 = pon_is_registered();
    if (iVar4 == 0) goto LAB_0001a494;
    if ((*(short *)(*(int *)(param_1 + 0xcc) + 2) != 0) || (*(int *)(param_1 + 0x68) != 0)) {
      pp_net_gso_tx(param_1,param_2,0);
      goto LAB_0001a310;
    }
    puVar3 = (undefined4 *)pon_tm_get_next_txdesc(0);
    if (puVar3 == (undefined4 *)0x0) {
      __dev_kfree_skb_any(param_1,1);
      *(int *)(param_2 + 0x4ec) = *(int *)(param_2 + 0x4ec) + 1;
      printk("get up tx desc failed\n");
      goto LAB_0001a310;
    }
    *puVar3 = 0x80;
    *(undefined1 *)puVar3 = 0xc9;
    pcVar1 = dev_qos_get_queue;
    puVar3[3] = 0;
    puVar3[1] = 0x10000;
    puVar3[2] = 0x1000000;
    if (pcVar1 != (code *)0x0) {
      (*pcVar1)(*(undefined4 *)(param_1 + 0x84),local_24);
    }
    pcVar1 = dev_qos_select_queue;
    if (lan_up == 1) {
      *(undefined2 *)(puVar3 + 1) = 0;
      if (pcVar1 == (code *)0x0) {
        *(byte *)((int)puVar3 + 3) = *(byte *)((int)puVar3 + 3) & 0x1f;
      }
      else {
        cVar2 = (*pcVar1)(param_1,param_2);
        *(byte *)((int)puVar3 + 3) = *(byte *)((int)puVar3 + 3) & 0x1f | cVar2 << 5;
      }
      *(ushort *)((int)puVar3 + 2) =
           *(ushort *)((int)puVar3 + 2) & 0xfc0f | (ushort)((lan_up_port + 0x28U & 0x3f) << 4);
    }
    if (*(char *)(param_1 + 0xbd) != '\0') {
      *(byte *)((int)puVar3 + 0xe) = *(byte *)((int)puVar3 + 0xe) | 1;
      *(ushort *)((int)puVar3 + 0xe) =
           *(ushort *)((int)puVar3 + 0xe) & 1 | *(short *)(param_1 + 0xc2) << 1;
      puVar3[2] = puVar3[2] & 0xff8001ff | (uint)*(byte *)(param_1 + 0xbe) << 9;
    }
    iVar4 = pon_tm_data_raw_send(param_1,puVar3,0);
    if (iVar4 != 0) {
      if (net_txq._12_4_ == 0) {
        net_txq._12_4_ = 0x3ff;
      }
      else {
        net_txq._12_4_ = net_txq._12_4_ + -1;
      }
      goto LAB_0001a494;
    }
LAB_0001a5a0:
    *(int *)(param_2 + 0x4d4) = *(int *)(param_2 + 0x4d4) + 1;
    *(int *)(param_2 + 0x4dc) = *(int *)(param_2 + 0x4dc) + *(int *)(param_1 + 100);
  }
  __dev_kfree_skb_any(param_1,1);
LAB_0001a310:
  if ((*(uint *)(((uint)auStack_28 & 0xffffe000) + 4) & 0x1fff00) == 0) {
    _raw_spin_unlock_irqrestore(&net_lock_tx,uVar5);
    return 0;
  }
  _raw_spin_unlock(&net_lock_tx);
  return 0;
}

