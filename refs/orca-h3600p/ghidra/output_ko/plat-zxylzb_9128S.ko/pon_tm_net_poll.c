// module: plat-zxylzb_9128S.ko
// function: pon_tm_net_poll @ 0x1d020
// size: 2356 bytes
//

/* WARNING: Restarted to delay deadcode elimination for space: ram */

int pon_tm_net_poll(int param_1,uint param_2)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  void *pvVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  void *pvVar12;
  undefined1 *puVar13;
  bool bVar14;
  uint local_58;
  uint local_4c;
  uint local_44;
  uint local_40;
  int local_3c;
  int local_30;
  
  *(int *)(param_1 + 0x78) = *(int *)(param_1 + 0x78) + 1;
  local_40 = param_2;
  if ((*(uint *)(param_1 + -100) & 3) == 0) {
    local_3c = 0;
LAB_0001d704:
    if (0 < (int)local_40) {
      napi_complete_done(param_1,0);
      disableIRQinterrupts();
      *(uint *)(tm_base + 0x104) = *(uint *)(tm_base + 0x104) & 0xfffffffc;
    }
    return local_3c;
  }
  local_30 = 4;
  *(int *)(param_1 + 0x7c) = *(int *)(param_1 + 0x7c) + 1;
  local_3c = 0;
  local_44 = 0xff;
LAB_0001d088:
  puVar13 = queue_ctrl;
  bVar14 = false;
  local_58 = 7;
  do {
    if (((int)local_44 >> (local_58 & 0xff) & 1U) == 0) {
joined_r0x0001d394:
      if (local_58 == 0) break;
    }
    else {
      uVar6 = *(uint *)(tm_base + (local_58 + 0x4040) * 4);
      uVar7 = uVar6;
      if (0 < (int)uVar6) {
        uVar7 = local_40;
      }
      if (0 < (int)uVar7) {
        iVar10 = 0x400 - *(int *)(puVar13 + 0x7c);
        iVar9 = (int)local_40 >> 1;
        if ((int)uVar6 >> 0x10 < (int)local_40 >> 1) {
          iVar9 = (int)uVar6 >> 0x10;
        }
        iVar2 = *(int *)(puVar13 + 0x78) + *(int *)(puVar13 + 0x7c) * 0x10;
        if (iVar10 < iVar9) {
          net_invalid_cache(iVar2,iVar10 * 0x10);
          net_invalid_cache(*(undefined4 *)(puVar13 + 0x78),(iVar9 - iVar10) * 0x10);
        }
        else {
          net_invalid_cache(iVar2,iVar9 << 4);
        }
        iVar10 = (int)pon_tm_netdev;
        if (iVar9 != 0) {
          iVar2 = 0;
          local_4c = 0;
          do {
            while( true ) {
              iVar4 = *(uint *)(puVar13 + 0x78) + *(int *)(puVar13 + 0x7c) * 0x10;
              HintPreloadData(iVar4);
              uVar7 = *(int *)(puVar13 + 0x7c) + 1;
              *(uint *)(puVar13 + 0x7c) = uVar7;
              if (0x3ff < uVar7) {
                *(undefined4 *)(puVar13 + 0x7c) = 0;
              }
              uVar8 = (uint)(*(byte *)(iVar4 + 7) >> 1) | (uint)*(byte *)(iVar4 + 8) << 7;
              bVar14 = (*(byte *)(iVar4 + 6) & 1) != 0;
              uVar7 = *(uint *)(puVar13 + 0x78);
              if (bVar14) {
                uVar7 = local_4c;
              }
              if (bVar14) {
                uVar7 = uVar7 + 1;
              }
              if (bVar14) {
                local_4c = uVar7;
              }
              if (*(uint *)((int)&bp_max_number + (*(byte *)(iVar4 + 9) & 1) * 4) <= uVar8) break;
              bmu_status._20_4_ = bmu_status._20_4_ + 1;
              if ((*(byte *)(iVar4 + 9) & 1) == 0) {
                pvVar12 = (void *)(u32_BP_SIZE * uVar8 +
                                  pdt_mem_size + -0x3fadfff0 + ZX_RESERVE_MEM_SIZE * -0x100000);
              }
              else {
                pvVar12 = (void *)(u32_JUMBO_BP_SIZE * uVar8 +
                                  u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + -0x3fadfff0 +
                                  ZX_RESERVE_MEM_SIZE * -0x100000);
              }
              uVar7 = (uint)(*(ushort *)(iVar4 + 0xc) >> 2);
              net_invalid_cache(pvVar12,uVar7);
              if (0 < pon_tm_net_debug) {
                dump_desc(iVar4);
                printk("recv gem %d,addr %x\n",*(ushort *)(iVar4 + 4) & 0xfff,pvVar12);
                dump_net_data(pvVar12,uVar7);
                pon_tm_net_debug = pon_tm_net_debug + -1;
              }
              if ((*(byte *)(iVar4 + 6) & 4) == 0) {
                iVar3 = __netdev_alloc_skb(iVar10,uVar7 + 0x12,0x20);
                if (iVar3 != 0) {
                  *(uint *)(iVar10 + 0x4d8) = *(int *)(iVar10 + 0x4d8) + uVar7;
                  *(int *)(iVar10 + 0x4d0) = *(int *)(iVar10 + 0x4d0) + 1;
                  pvVar5 = (void *)(*(int *)(iVar3 + 0xd4) + 2);
                  *(void **)(iVar3 + 0xd4) = pvVar5;
                  *(int *)(iVar3 + 200) = *(int *)(iVar3 + 200) + 2;
                  memcpy(pvVar5,pvVar12,uVar7);
                  skb_put(iVar3,uVar7);
                  *(int *)(iVar3 + 0x18) = iVar10;
                  if ((*(byte *)(iVar4 + 9) & 1) != 0) {
                    *(ushort *)(iVar3 + 0xc4) = *(ushort *)(iVar3 + 0xc4) | 2;
                  }
                  if (switch_skb_recv == (code *)0x0) {
                    uVar1 = eth_type_trans(iVar3,iVar10);
                    *(undefined2 *)(iVar3 + 0xac) = uVar1;
                    netif_receive_skb_sk(*(undefined4 *)(iVar3 + 0x14),iVar3);
                  }
                  else {
                    *(ushort *)(iVar3 + 0xc4) = *(ushort *)(iVar3 + 0xc4) | 8;
                    if ((*(byte *)(iVar4 + 0xe) & 2) == 0) {
                      *(byte *)(iVar3 + 0xbc) = (*(byte *)(iVar4 + 6) >> 3) - 1;
                    }
                    (*switch_skb_recv)(iVar3);
                  }
                  goto LAB_0001d278;
                }
                iVar4 = pp_bmu_free_bp(uVar8,0,*(byte *)(iVar4 + 9) & 1);
                if (iVar4 < 0) {
                  printk("failed to rls bp\n");
                }
                *(int *)(iVar10 + 0x4e8) = *(int *)(iVar10 + 0x4e8) + 1;
              }
              else {
LAB_0001d278:
                iVar4 = pp_bmu_free_bp(uVar8,0,*(byte *)(iVar4 + 9) & 1);
                if (iVar4 < 0) {
                  printk("failed to rls bp\n");
                }
              }
              iVar2 = iVar2 + 1;
              if (iVar2 == iVar9) goto LAB_0001d3e4;
            }
            *(int *)(iVar10 + 0x4e0) = *(int *)(iVar10 + 0x4e0) + 1;
            iVar2 = iVar2 + 1;
            printk("rxq %d,invalid bp %u\n",local_58,uVar8);
            dump_desc(iVar4);
          } while (iVar2 != iVar9);
LAB_0001d3e4:
          if (iVar9 - local_4c != 0) {
            soft_release_rx_desc(1,local_58 & 0xff,0,iVar9 - local_4c & 0xffff);
          }
          if (local_4c != 0) {
            soft_release_rx_desc(1,local_58 & 0xff,1,local_4c & 0xffff);
          }
        }
        iVar2 = 0x400 - *(int *)(puVar13 + 0x3c);
        iVar10 = *(int *)(puVar13 + 0x38) + *(int *)(puVar13 + 0x3c) * 0x10;
        uVar7 = (int)(local_40 - iVar9) / 2;
        if ((int)(uVar6 & 0xffff) <= (int)uVar7) {
          uVar7 = uVar6 & 0xffff;
        }
        if (iVar2 < (int)uVar7) {
          net_invalid_cache(iVar10,iVar2 * 0x10);
          net_invalid_cache(*(undefined4 *)(puVar13 + 0x38),(uVar7 - iVar2) * 0x10);
          if ((int)uVar7 < 1) goto LAB_0001d79c;
LAB_0001d454:
          iVar10 = pon_tm_netdev._4_4_;
          local_4c = 0;
          uVar6 = 0;
          do {
            iVar2 = *(uint *)(puVar13 + 0x38) + *(int *)(puVar13 + 0x3c) * 0x10;
            HintPreloadData(iVar2);
            uVar8 = *(int *)(puVar13 + 0x3c) + 1;
            *(uint *)(puVar13 + 0x3c) = uVar8;
            if (0x3ff < uVar8) {
              *(undefined4 *)(puVar13 + 0x3c) = 0;
            }
            uVar11 = (uint)(*(byte *)(iVar2 + 7) >> 1) | (uint)*(byte *)(iVar2 + 8) << 7;
            bVar14 = (*(byte *)(iVar2 + 6) & 1) != 0;
            uVar8 = *(uint *)(puVar13 + 0x38);
            if (bVar14) {
              uVar8 = local_4c;
            }
            if (bVar14) {
              uVar8 = uVar8 + 1;
            }
            if (bVar14) {
              local_4c = uVar8;
            }
            if (uVar11 < *(uint *)((int)&bp_max_number + (*(byte *)(iVar2 + 9) & 1) * 4)) {
              bmu_status._20_4_ = bmu_status._20_4_ + 1;
              if ((*(byte *)(iVar2 + 9) & 1) == 0) {
                pvVar12 = (void *)(u32_BP_SIZE * uVar11 +
                                  pdt_mem_size + -0x3fadfff0 + ZX_RESERVE_MEM_SIZE * -0x100000);
              }
              else {
                pvVar12 = (void *)(u32_JUMBO_BP_SIZE * uVar11 +
                                  u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + -0x3fadfff0 +
                                  ZX_RESERVE_MEM_SIZE * -0x100000);
              }
              uVar8 = (uint)(*(ushort *)(iVar2 + 0xc) >> 2);
              net_invalid_cache(pvVar12,uVar8);
              if (0 < pon_tm_net_debug) {
                dump_desc(iVar2);
                printk("recv gem %d,addr %x\n",*(ushort *)(iVar2 + 4) & 0xfff,pvVar12);
                dump_net_data(pvVar12,uVar8);
                pon_tm_net_debug = pon_tm_net_debug + -1;
              }
              if ((*(byte *)(iVar2 + 6) & 4) == 0) {
                iVar4 = __netdev_alloc_skb(iVar10,uVar8 + 0x12,0x20);
                if (iVar4 == 0) {
                  iVar2 = pp_bmu_free_bp(uVar11,0,*(byte *)(iVar2 + 9) & 1);
                  if (iVar2 < 0) {
                    printk("failed to rls bp\n");
                  }
                  *(int *)(iVar10 + 0x4e8) = *(int *)(iVar10 + 0x4e8) + 1;
                  goto LAB_0001d5bc;
                }
                *(uint *)(iVar10 + 0x4d8) = *(int *)(iVar10 + 0x4d8) + uVar8;
                *(int *)(iVar10 + 0x4d0) = *(int *)(iVar10 + 0x4d0) + 1;
                pvVar5 = (void *)(*(int *)(iVar4 + 0xd4) + 2);
                *(void **)(iVar4 + 0xd4) = pvVar5;
                *(int *)(iVar4 + 200) = *(int *)(iVar4 + 200) + 2;
                memcpy(pvVar5,pvVar12,uVar8);
                skb_put(iVar4,uVar8);
                *(int *)(iVar4 + 0x18) = iVar10;
                if ((*(byte *)(iVar2 + 9) & 1) != 0) {
                  *(ushort *)(iVar4 + 0xc4) = *(ushort *)(iVar4 + 0xc4) | 2;
                }
                if (switch_skb_recv == (code *)0x0) {
                  uVar1 = eth_type_trans(iVar4,iVar10);
                  *(undefined2 *)(iVar4 + 0xac) = uVar1;
                  netif_receive_skb_sk(*(undefined4 *)(iVar4 + 0x14),iVar4);
                }
                else {
                  *(ushort *)(iVar4 + 0xc4) = *(ushort *)(iVar4 + 0xc4) | 8;
                  if ((*(byte *)(iVar2 + 0xe) & 2) == 0) {
                    *(byte *)(iVar4 + 0xbc) = (*(byte *)(iVar2 + 6) >> 3) - 1;
                  }
                  (*switch_skb_recv)(iVar4);
                }
              }
              iVar2 = pp_bmu_free_bp(uVar11,0,*(byte *)(iVar2 + 9) & 1);
              if (iVar2 < 0) {
                printk("failed to rls bp\n");
              }
            }
            else {
              *(int *)(iVar10 + 0x4e0) = *(int *)(iVar10 + 0x4e0) + 1;
              printk("rxq %d,invalid bp %u\n",local_58,uVar11);
              dump_desc(iVar2);
            }
LAB_0001d5bc:
            uVar6 = uVar6 + 1;
          } while (uVar6 != uVar7);
          uVar6 = uVar7 - local_4c;
          if (uVar7 - local_4c != 0) {
LAB_0001d7a8:
            soft_release_rx_desc(0,local_58 & 0xff,0,uVar6 & 0xffff);
          }
          if (local_4c != 0) {
            soft_release_rx_desc(0,local_58 & 0xff,1,local_4c & 0xffff);
          }
        }
        else {
          net_invalid_cache(iVar10,uVar7 << 4);
          if (0 < (int)uVar7) goto LAB_0001d454;
LAB_0001d79c:
          if (uVar7 != 0) {
            local_4c = 0;
            uVar6 = uVar7;
            goto LAB_0001d7a8;
          }
        }
        bVar14 = true;
        local_40 = (local_40 - iVar9) - uVar7;
        local_3c = local_3c + uVar7;
        goto joined_r0x0001d394;
      }
      if (local_58 != 7) {
        local_44 = local_44 & ~(1 << (local_58 & 0xff));
        goto joined_r0x0001d394;
      }
    }
    puVar13 = puVar13 + -8;
    local_58 = local_58 - 1;
  } while( true );
  if ((!bVar14) || (local_30 = local_30 + -1, local_30 == 0)) goto LAB_0001d704;
  goto LAB_0001d088;
}

