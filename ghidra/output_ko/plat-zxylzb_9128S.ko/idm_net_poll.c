// module: plat-zxylzb_9128S.ko
// function: idm_net_poll @ 0x15a00
// size: 1128 bytes
//

/* WARNING: Restarted to delay deadcode elimination for space: ram */

int idm_net_poll(int param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  undefined2 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  byte bVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  uint local_40;
  int local_3c;
  int local_34;
  
  uVar11 = *(uint *)(param_1 + -0x60);
  *(int *)(param_1 + 0x78) = *(int *)(param_1 + 0x78) + 1;
  if ((uVar11 & 0x10) != 0) {
    *(int *)(param_1 + 0x80) = *(int *)(param_1 + 0x80) + 1;
    idm_check_tx_done_lock();
  }
  if ((uVar11 & 4) != 0) {
    *(int *)(param_1 + 0x7c) = *(int *)(param_1 + 0x7c) + 1;
  }
  local_34 = 5;
  local_3c = 0;
  local_40 = param_2;
  do {
    uVar11 = *(uint *)(npp_base + 0x804c) & 0xffff;
    if (uVar11 == 0) break;
    if ((int)local_40 < 1) {
      if (idm_recv_cmpl == (code *)0x0) {
        return local_3c;
      }
      goto LAB_00015d18;
    }
    if ((int)local_40 <= (int)uVar11) {
      uVar11 = local_40;
    }
    if (0 < idm_net_debug) {
      printk("idm recv %u,jiffies %x\n",uVar11,jiffies);
    }
    uVar15 = 0;
    do {
      while( true ) {
        uVar2 = rx_desc;
        uVar1 = idm_rx_index;
        uVar15 = uVar15 + 1;
        uVar10 = idm_rx_index + 1;
        iVar13 = rx_desc + idm_rx_index * 8;
        uVar8 = rx_desc;
        if (0x7ff < uVar10) {
          uVar8 = 0;
        }
        iVar12 = *(int *)(skb_rq + ((int)(idm_rx_index * 8) >> 1));
        idm_rx_index = uVar10;
        if (0x7ff < uVar10) {
          idm_rx_index = uVar8;
        }
        uVar8 = (uint)(*(byte *)(iVar13 + 7) >> 7);
        iVar14 = *(int *)((int)&idm_netdev + uVar8 * 4);
        if (iVar12 == 0) break;
        uVar10 = *(ushort *)(iVar13 + 4) & 0x3fff;
        if (0 < idm_net_debug) {
          dump_idm_desc_rx(iVar13);
          dump_idm_data(*(undefined4 *)(iVar12 + 0xcc),*(undefined4 *)(iVar12 + 100));
          idm_net_debug = idm_net_debug + -1;
        }
        iVar5 = _idm_skb_stack_pop(0);
        if (iVar5 == 0) {
          iVar5 = __alloc_skbuff(0x6c4,0x20,0,0xffffffff);
          if (iVar5 != 0) {
            iVar7 = *(int *)(iVar5 + 0xcc) + 0x20;
            *(int *)(iVar5 + 0x18) = iVar14;
            iVar6 = *(int *)(iVar5 + 0xc0) + 0x20;
            *(int *)(iVar5 + 0xcc) = iVar7;
            *(int *)(iVar5 + 0xc0) = iVar6;
            goto LAB_00015ba4;
          }
          printk("idm failed to alloc skb\n");
          *(int *)(iVar14 + 0x4e4) = *(int *)(iVar14 + 0x4e4) + 1;
        }
        else {
          iVar7 = *(int *)(iVar5 + 0xcc);
          iVar6 = *(int *)(iVar5 + 0xc0);
LAB_00015ba4:
          uVar3 = rx_desc;
          *(int *)(iVar5 + 0xc0) = iVar6 + 0x20;
          *(int *)(iVar5 + 0xcc) = iVar7 + 0x20;
          *(int *)(uVar2 + uVar1 * 8) = iVar7 + -0x7fffffe0;
          *(int *)(skb_rq + ((int)(iVar13 - uVar3) >> 3) * 4) = iVar5;
          *(ushort *)(iVar5 + 0xbc) = *(ushort *)(iVar5 + 0xbc) | 0x10;
          skb_put(iVar12,uVar10);
          *(int *)(iVar12 + 0x18) = iVar14;
          if ((*(byte *)(iVar13 + 6) & 8) == 0) {
            bVar9 = 0xff;
          }
          else {
            bVar9 = (byte)(((uint)*(byte *)(iVar13 + 6) << 0x1d) >> 0x1d);
          }
          *(byte *)(iVar12 + 0xb7) = bVar9;
          if (idm_skb_recv == (code *)0x0) {
            uVar4 = eth_type_trans(iVar12,iVar14);
            *(undefined2 *)(iVar12 + 0xa4) = uVar4;
            netif_receive_skb_sk(*(undefined4 *)(iVar12 + 0x14),iVar12);
          }
          else {
            (*idm_skb_recv)(uVar8,iVar12);
          }
          *(uint *)(iVar14 + 0x4d4) = *(int *)(iVar14 + 0x4d4) + uVar10;
          *(int *)(iVar14 + 0x4cc) = *(int *)(iVar14 + 0x4cc) + 1;
        }
LAB_00015afc:
        if (uVar15 == uVar11) goto LAB_00015ca0;
      }
      *(int *)(iVar14 + 0x4e4) = *(int *)(iVar14 + 0x4e4) + 1;
      iVar12 = _idm_skb_stack_pop(0);
      if (iVar12 == 0) {
        iVar12 = __alloc_skbuff(0x6c4,0x20,0,0xffffffff);
        if (iVar12 == 0) {
          printk("idm failed to alloc skb\n");
          goto LAB_00015afc;
        }
        iVar5 = *(int *)(iVar12 + 0xcc) + 0x20;
        *(int *)(iVar12 + 0x18) = iVar14;
        iVar14 = *(int *)(iVar12 + 0xc0) + 0x20;
        *(int *)(iVar12 + 0xcc) = iVar5;
        *(int *)(iVar12 + 0xc0) = iVar14;
      }
      else {
        iVar5 = *(int *)(iVar12 + 0xcc);
        iVar14 = *(int *)(iVar12 + 0xc0);
      }
      uVar8 = rx_desc;
      *(int *)(iVar12 + 0xc0) = iVar14 + 0x20;
      *(int *)(iVar12 + 0xcc) = iVar5 + 0x20;
      *(int *)(uVar2 + uVar1 * 8) = iVar5 + -0x7fffffe0;
      *(int *)(skb_rq + ((int)(iVar13 - uVar8) >> 3) * 4) = iVar12;
      *(ushort *)(iVar12 + 0xbc) = *(ushort *)(iVar12 + 0xbc) | 0x10;
    } while (uVar15 != uVar11);
LAB_00015ca0:
    if (idm_skb_flush != (code *)0x0) {
      (*idm_skb_flush)();
    }
    *(uint *)(npp_base + 0x8048) = uVar11 & 0xffff | (uVar11 & 0xffff) << 0x10;
    local_34 = local_34 + -1;
    local_40 = local_40 - uVar11;
    local_3c = local_3c + uVar11;
  } while (local_34 != 0);
  if (idm_recv_cmpl != (code *)0x0) {
LAB_00015d18:
    (*idm_recv_cmpl)();
  }
  if (0 < (int)local_40) {
    napi_complete_done(param_1,0);
    disableIRQinterrupts();
    idm_int_mask = *(uint *)(npp_base + 0x8024) & 0xffffffeb;
    *(uint *)(npp_base + 0x8024) = idm_int_mask;
  }
  return local_3c;
}

