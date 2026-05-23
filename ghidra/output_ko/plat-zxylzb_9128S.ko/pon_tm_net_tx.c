// module: plat-zxylzb_9128S.ko
// function: pon_tm_net_tx @ 0x19c80
// size: 1124 bytes
//

undefined4 pon_tm_net_tx(int param_1,int param_2)

{
  code *pcVar1;
  char cVar2;
  undefined4 *puVar3;
  int iVar4;
  ushort uVar5;
  int iVar6;
  undefined4 uVar7;
  undefined1 auStack_28 [4];
  undefined4 local_24 [2];
  
  if (*(int *)(param_2 + 0x4c8) == 0) {
    ffe_learn_skb(param_1,3);
  }
  if ((*(uint *)(((uint)auStack_28 & 0xffffe000) + 4) & 0x1fff00) == 0) {
    uVar7 = _raw_spin_lock_irqsave(&net_lock_tx);
    iVar6 = *(int *)(param_2 + 0x4c8);
    if (iVar6 != 0) goto LAB_00019cd8;
LAB_00019d3c:
    local_24[0] = 0;
    iVar6 = pon_is_registered();
    if (iVar6 != 0) {
      puVar3 = (undefined4 *)pon_tm_get_next_txdesc(0);
      if (puVar3 == (undefined4 *)0x0) {
        __dev_kfree_skb_any(param_1,1);
        *(int *)(param_2 + 0x4ec) = *(int *)(param_2 + 0x4ec) + 1;
        printk("get up tx desc failed\n");
        goto LAB_00019cec;
      }
      *puVar3 = 0x80;
      *(undefined1 *)puVar3 = 0xc9;
      pcVar1 = dev_qos_get_queue;
      puVar3[3] = 0;
      puVar3[1] = 0x10000;
      puVar3[2] = 0x1000000;
      if (pcVar1 != (code *)0x0) {
        (*pcVar1)(*(undefined4 *)(param_1 + 0x80),local_24);
      }
      uVar5 = *(ushort *)(*(int *)(param_1 + 0xcc) + 0xc);
      uVar5 = uVar5 << 8 | uVar5 >> 8;
      if (uVar5 == 0x884c || uVar5 == 0x8899) {
        if (uVar5 != 0x8899 && uVar5 != 0x884c) goto LAB_00019e8c;
      }
      else {
        iVar6 = dev_get_by_name(&init_net,&_LC17);
        if (iVar6 != 0) {
          if ((*(uint *)(iVar6 + 0x138) & 1) != 0) {
            disableIRQinterrupts();
            iVar4 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
            *(int *)(iVar4 + *(int *)(iVar6 + 0x280)) =
                 *(int *)(iVar4 + *(int *)(iVar6 + 0x280)) + -1;
            if (dev_qos_select_queue == (code *)0x0) {
              *(byte *)((int)puVar3 + 3) = *(byte *)((int)puVar3 + 3) & 0x1f;
            }
            else {
              cVar2 = (*dev_qos_select_queue)(param_1,param_2);
              *(byte *)((int)puVar3 + 3) = *(byte *)((int)puVar3 + 3) & 0x1f | cVar2 << 5;
            }
            goto LAB_00019ea0;
          }
          disableIRQinterrupts();
          iVar4 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
          *(int *)(iVar4 + *(int *)(iVar6 + 0x280)) = *(int *)(iVar4 + *(int *)(iVar6 + 0x280)) + -1
          ;
        }
LAB_00019e8c:
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
      }
LAB_00019ea0:
      if (*(char *)(param_1 + 0xb5) != '\0') {
        *(byte *)((int)puVar3 + 0xe) = *(byte *)((int)puVar3 + 0xe) | 1;
        *(ushort *)((int)puVar3 + 0xe) =
             *(ushort *)((int)puVar3 + 0xe) & 1 | *(short *)(param_1 + 0xba) << 1;
        puVar3[2] = puVar3[2] & 0xff8001ff | (uint)*(byte *)(param_1 + 0xb6) << 9;
      }
      iVar6 = pon_tm_data_raw_send(param_1,puVar3,0);
      if (iVar6 == 0) {
LAB_00019ef0:
        *(int *)(param_2 + 0x4d4) = *(int *)(param_2 + 0x4d4) + 1;
        *(int *)(param_2 + 0x4dc) = *(int *)(param_2 + 0x4dc) + *(int *)(param_1 + 100);
        goto LAB_00019ce0;
      }
      if (net_txq._12_4_ == 0) {
        net_txq._12_4_ = 0x3ff;
      }
      else {
        net_txq._12_4_ = net_txq._12_4_ + -1;
      }
    }
LAB_00019d4c:
    *(int *)(param_2 + 0x4ec) = *(int *)(param_2 + 0x4ec) + 1;
  }
  else {
    _raw_spin_lock();
    iVar6 = *(int *)(param_2 + 0x4c8);
    uVar7 = 0;
    if (iVar6 == 0) goto LAB_00019d3c;
LAB_00019cd8:
    if (iVar6 == 1) {
      puVar3 = (undefined4 *)pon_tm_get_next_txdesc(1);
      if (puVar3 == (undefined4 *)0x0) {
        __dev_kfree_skb_any(param_1,1);
        *(int *)(param_2 + 0x4ec) = *(int *)(param_2 + 0x4ec) + 1;
        printk("get dn tx desc failed\n");
        goto LAB_00019cec;
      }
      *puVar3 = 0x80;
      iVar6 = test_da_unknown;
      puVar3[2] = 0x1000000;
      puVar3[1] = 0x10000;
      if (iVar6 == 0) {
        puVar3[3] = 3;
        *(ushort *)((int)puVar3 + 2) =
             *(ushort *)((int)puVar3 + 2) & 0xfc0f | (*(byte *)(param_1 + 0xb4) + 0x28 & 0x3f) << 4;
      }
      else {
        puVar3[3] = 2;
      }
      if (dev_qos_select_queue == (code *)0x0) {
        *(byte *)((int)puVar3 + 3) = *(byte *)((int)puVar3 + 3) & 0x1f;
      }
      else {
        *(byte *)((int)puVar3 + 3) =
             *(byte *)((int)puVar3 + 3) & 0x1f | (byte)((*(ushort *)(param_1 + 0x78) & 7) << 5);
      }
      if (*(char *)(param_1 + 0xb5) != '\0') {
        *(byte *)((int)puVar3 + 0xe) = *(byte *)((int)puVar3 + 0xe) | 1;
        *(ushort *)((int)puVar3 + 0xe) =
             *(ushort *)((int)puVar3 + 0xe) & 1 | *(short *)(param_1 + 0xba) << 1;
        puVar3[2] = puVar3[2] & 0xff8001ff | (uint)*(byte *)(param_1 + 0xb6) << 9;
      }
      iVar6 = pon_tm_data_raw_send(param_1,puVar3,1);
      if (iVar6 != 0) {
        if (net_txq._40_4_ == 0) {
          net_txq._40_4_ = 0x3ff;
        }
        else {
          net_txq._40_4_ = net_txq._40_4_ + -1;
        }
        goto LAB_00019d4c;
      }
      goto LAB_00019ef0;
    }
  }
LAB_00019ce0:
  __dev_kfree_skb_any(param_1,1);
LAB_00019cec:
  if ((*(uint *)(((uint)auStack_28 & 0xffffe000) + 4) & 0x1fff00) != 0) {
    _raw_spin_unlock(&net_lock_tx);
    return 0;
  }
  _raw_spin_unlock_irqrestore(&net_lock_tx,uVar7);
  return 0;
}

