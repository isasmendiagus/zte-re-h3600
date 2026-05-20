// module: plat-zxylzb_9128S.ko
// function: idm_net_tx @ 0x15ea8
// size: 640 bytes
//

undefined4 idm_net_tx(undefined4 *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  int local_30;
  undefined4 local_2c;
  
  if ((*(uint *)(((uint)&local_30 & 0xffffe000) + 4) & 0x1fff00) == 0) {
    local_2c = _raw_spin_lock_irqsave(&idm_lock_tx);
  }
  else {
    local_2c = 0;
    _raw_spin_lock();
  }
  if (param_1 != (undefined4 *)0x0) {
    iVar7 = 0;
    iVar8 = 0x2c5a4;
    do {
      while( true ) {
        puVar6 = (undefined4 *)*param_1;
        *param_1 = 0;
        if ((idm_skb_tx < 0x200) ||
           (local_30 = iVar8, idm_check_tx_done_nolock(), iVar8 = local_30,
           *(uint *)(local_30 + -0xf48) < 0x400)) break;
        if (*(uint *)(npp_base + 0x8044) < 0x4000000) {
          *(int *)(local_30 + -0xf54) = *(int *)(local_30 + -0xf54) + 1;
        }
        else {
          *(int *)(local_30 + -0xf58) = *(int *)(local_30 + -0xf58) + 1;
        }
LAB_00016034:
        local_30 = iVar8;
        __dev_kfree_skb_any(param_1,1);
        *(int *)(param_2 + 0x4e8) = *(int *)(param_2 + 0x4e8) + 1;
        param_1 = puVar6;
        iVar8 = local_30;
        if (puVar6 == (undefined4 *)0x0) goto LAB_00016060;
      }
      iVar1 = tx_desc;
      uVar2 = idm_tx_index;
      uVar3 = idm_tx_index + 1;
      iVar4 = tx_desc + idm_tx_index * 8;
      idm_tx_index = uVar3;
      if (0x3ff < uVar3) {
        idm_tx_index = 0;
      }
      if (iVar4 == 0) goto LAB_00016034;
      iVar5 = *(int *)(param_2 + 0x4c0);
      if ((uint)param_1[0x19] < 0x21) {
        param_1[0x19] = 0x21;
      }
      *(int *)(iVar1 + uVar2 * 8) = param_1[0x33] + -0x80000000;
      iVar1 = idm_net_debug;
      *(uint *)(iVar4 + 4) =
           param_1[0x19] | *(int *)(param_2 + 0x4c4) << 0x1f |
           (uint)*(byte *)((int)param_1 + 0xb7) << 0x1c;
      if (0 < iVar1) {
        local_30 = iVar8;
        printk("send len %u,data %x,head %x\n",param_1[0x19],param_1[0x33],param_1[0x32]);
        dump_idm_desc_tx(iVar4);
        dump_idm_data(param_1[0x33],param_1[0x19]);
        *(int *)(local_30 + 0xf4) = *(int *)(local_30 + 0xf4) + -1;
        iVar8 = local_30;
      }
      iVar7 = iVar7 + 1;
      iVar4 = iVar4 - tx_desc;
      *(int *)(iVar5 + 0x4d0) = *(int *)(iVar5 + 0x4d0) + 1;
      idm_skb_tx = idm_skb_tx + 1;
      *(int *)(iVar5 + 0x4d8) = *(int *)(iVar5 + 0x4d8) + param_1[0x19];
      *(undefined4 **)(skb_tq + (iVar4 >> 3) * 4) = param_1;
      param_1 = puVar6;
    } while (puVar6 != (undefined4 *)0x0);
LAB_00016060:
    if (iVar7 != 0) {
      DataSynchronizationBarrier(0xf);
      *(int *)(npp_base + 0x8040) = iVar7 << 0x10;
    }
  }
  if ((*(uint *)(((uint)&local_30 & 0xffffe000) + 4) & 0x1fff00) != 0) {
    _raw_spin_unlock(&idm_lock_tx);
    return 0;
  }
  _raw_spin_unlock_irqrestore(&idm_lock_tx,local_2c);
  return 0;
}

