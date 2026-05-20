// module: mt7915.ko
// function: sae_handle_auth @ 0x20b44c
// size: 2280 bytes
//

undefined4
sae_handle_auth(undefined4 param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5,
               undefined4 param_6,undefined1 param_7,short param_8,short param_9,int *param_10)

{
  uint *puVar1;
  uint *puVar2;
  undefined4 uVar3;
  void *__dest;
  byte bVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  void *local_84;
  size_t local_80;
  undefined4 local_7c;
  short local_78 [42];
  
  iVar6 = param_3 + 4;
  iVar7 = param_3 + 10;
  puVar1 = (uint *)search_sae_instance(param_2,iVar6,iVar7);
  local_84 = (void *)0x0;
  local_80 = 0;
  local_7c = 0;
  if (2 < DebugLevel) {
    printk("==>%s(): receive seq #%d with status code %d, instance %p, own mac addr = %02x:%02x:%02x:%02x:%02x:%02x, peer mac addr = %02x:%02x:%02x:%02x:%02x:%02x\n"
           ,"sae_handle_auth",param_8,param_9,puVar1,*(undefined1 *)(param_3 + 4),
           *(undefined1 *)(param_3 + 5),*(undefined1 *)(param_3 + 6),*(undefined1 *)(param_3 + 7),
           *(undefined1 *)(param_3 + 8),*(undefined1 *)(param_3 + 9),*(undefined1 *)(param_3 + 10),
           *(undefined1 *)(param_3 + 0xb),*(undefined1 *)(param_3 + 0xc),
           *(undefined1 *)(param_3 + 0xd),*(undefined1 *)(param_3 + 0xe),
           *(undefined1 *)(param_3 + 0xf));
  }
  if (puVar1 == (uint *)0x0) {
    if (param_8 == 1) goto LAB_0020b58c;
    if (param_8 == 2) goto LAB_0020b654;
    iVar8 = 0xe;
    goto LAB_0020b520;
  }
  if ((*(byte *)(param_3 + 1) & 8) == 0) {
    *(ushort *)(puVar1 + 0x61) =
         (ushort)*(byte *)(param_3 + 0x17) << 4 | (ushort)(*(byte *)(param_3 + 0x16) >> 4);
  }
  else if ((ushort)puVar1[0x61] ==
           (ushort)((ushort)*(byte *)(param_3 + 0x17) << 4 |
                   (ushort)(*(byte *)(param_3 + 0x16) >> 4))) goto LAB_0020b564;
  sae_clear_retransmit_timer(puVar1);
  if (2 < DebugLevel) {
    printk("%s(): state = %d\n","sae_handle_auth",*puVar1);
  }
  if (param_8 == 1) {
LAB_0020b58c:
    if (param_9 != 0) {
      if (puVar1 == (uint *)0x0) goto LAB_0020b654;
      uVar5 = *puVar1;
      if (uVar5 == 0 || uVar5 == 3) {
LAB_0020b650:
        delete_sae_instance(puVar1);
        goto LAB_0020b654;
      }
      if (uVar5 == 2) {
        iVar6 = sae_check_big_sync(puVar1);
        if (iVar6 != 0) goto LAB_0020b564;
      }
      else {
        if (param_9 != 0x4c) {
          if (param_9 == 0x4d) {
            local_78[0] = *(short *)(param_3 + 0x1e);
            if (local_78[0] == (short)puVar1[0xb]) {
              bVar4 = *(char *)((int)puVar1 + 0x2f) + 1;
              *(byte *)((int)puVar1 + 0x2f) = bVar4;
              if ((((1 < bVar4) || (*(char *)(param_2 + (uint)bVar4 + 0x1b900) == '\0')) ||
                  (iVar6 = sae_group_allowed(puVar1,param_2 + 0x1b900), iVar6 != 0)) ||
                 (iVar6 = sae_prepare_commit(puVar1), iVar6 != 0)) {
                delete_sae_instance(puVar1);
                uVar3 = 0;
                goto LAB_0020b8dc;
              }
              sae_send_auth_commit(param_1,puVar1);
            }
            sae_set_retransmit_timer(puVar1);
            uVar3 = 1;
            goto LAB_0020b8dc;
          }
          if (param_9 == 0x7b) goto LAB_0020b650;
          goto LAB_0020b6a4;
        }
        iVar8 = sae_parse_commit(param_2,puVar1,param_3,param_4,&local_84,&local_80,1);
        if (iVar8 != 0) goto LAB_0020b738;
        if ((local_84 == (void *)0x0) || (local_80 == 0)) {
          if (-1 < DebugLevel) {
            printk("%s:AntiClogging Request token empty fail\n","sae_handle_auth");
          }
        }
        else {
          if (-1 < DebugLevel) {
            printk("%s:AntiClogging Request token found,token_len = %d\n","sae_handle_auth");
          }
          os_alloc_mem(param_1,puVar1 + 0x1f,local_80);
          __dest = (void *)puVar1[0x1f];
          if (__dest != (void *)0x0) {
            if (local_80 != 0) {
              __memzero();
              __dest = (void *)puVar1[0x1f];
            }
            puVar1[0x20] = local_80;
            memmove(__dest,local_84,local_80);
            sae_send_auth_commit(param_1,puVar1);
            sae_set_retransmit_timer(puVar1);
            goto LAB_0020b564;
          }
          if (-1 < DebugLevel) {
            printk("%s:AntiClogging token allocation fail\n","sae_handle_auth");
          }
        }
      }
      sae_set_retransmit_timer(puVar1);
      goto LAB_0020b564;
    }
    if (puVar1 == (uint *)0x0) {
      puVar1 = (uint *)create_sae_instance(param_1,param_2,iVar6,iVar7,param_3 + 0x10,param_5,
                                           param_6,param_7);
      if (puVar1 != (uint *)0x0) {
        *(ushort *)(puVar1 + 0x61) =
             (ushort)*(byte *)(param_3 + 0x17) << 4 | (ushort)(*(byte *)(param_3 + 0x16) >> 4);
        puVar1[0x5f] = 0;
        goto LAB_0020b5b8;
      }
      iVar8 = sae_parse_commit(param_2,0,param_3,param_4,&local_84,&local_80,0);
      if (iVar8 == 0x4d) goto LAB_0020b654;
LAB_0020b5dc:
      if (iVar8 != 0x7b) {
        if (iVar8 == 0xffff) {
          sae_set_retransmit_timer(puVar1);
          uVar3 = 0;
          if (puVar1 != (uint *)0x0) {
            uVar3 = 1;
          }
LAB_0020b8dc:
          *param_10 = 0;
          return uVar3;
        }
        if (iVar8 != 0) {
          if (puVar1 == (uint *)0x0) goto LAB_0020b614;
          if (*puVar1 < 2) goto LAB_0020b60c;
          goto LAB_0020b738;
        }
        goto LAB_0020b6ac;
      }
      delete_sae_instance(puVar1);
      puVar1 = (uint *)0x0;
LAB_0020b520:
      sae_send_auth(param_1,iVar6,iVar7,param_3 + 0x10,3,param_8,iVar8,local_78,local_7c);
    }
    else {
      if (*puVar1 == 3) {
        puVar2 = (uint *)create_sae_instance(param_1,param_2,iVar6,iVar7,param_3 + 0x10,param_5,
                                             param_6,param_7);
        if (puVar2 != (uint *)0x0) {
          *(ushort *)(puVar2 + 0x61) =
               (ushort)*(byte *)(param_3 + 0x17) << 4 | (ushort)(*(byte *)(param_3 + 0x16) >> 4);
          puVar2[0x5f] = (uint)puVar1;
        }
        puVar1[0x5f] = (uint)puVar2;
        iVar8 = sae_parse_commit(param_2,puVar2,param_3,param_4,&local_84,&local_80,0);
        puVar1 = puVar2;
        if (iVar8 != 0x4d) goto LAB_0020b5dc;
        if (puVar2 == (uint *)0x0) goto LAB_0020b654;
      }
      else {
LAB_0020b5b8:
        iVar8 = sae_parse_commit(param_2,puVar1,param_3,param_4,&local_84,&local_80,0);
        if (iVar8 != 0x4d) goto LAB_0020b5dc;
      }
      uVar5 = *puVar1;
      if (uVar5 == 0) {
        iVar8 = 0x4d;
        delete_sae_instance(puVar1);
        puVar1 = (uint *)0x0;
        goto LAB_0020b520;
      }
      if (uVar5 == 1) {
        iVar8 = sae_check_big_sync(puVar1);
        if (iVar8 != 0) goto LAB_0020b564;
        uVar5 = *puVar1;
        if (uVar5 == 1) {
          sae_set_retransmit_timer(puVar1);
          uVar5 = *puVar1;
        }
      }
      if (uVar5 == 2) {
LAB_0020b6a4:
        sae_set_retransmit_timer(puVar1);
        goto LAB_0020b564;
      }
LAB_0020b6ac:
      if (local_84 != (void *)0x0) {
        iVar8 = sae_check_token(puVar1,local_84,local_80);
        if (iVar8 != 0) {
          if (local_84 == (void *)0x0) goto LAB_0020b75c;
          goto LAB_0020b76c;
        }
        if (-1 < DebugLevel) {
          printk("%s(): check token fail with peer mac %02x:%02x:%02x:%02x:%02x:%02x\n",
                 "sae_handle_auth",*(undefined1 *)((int)puVar1 + 0x166),
                 *(undefined1 *)((int)puVar1 + 0x167),(char)puVar1[0x5a],
                 *(undefined1 *)((int)puVar1 + 0x169),*(undefined1 *)((int)puVar1 + 0x16a),
                 *(undefined1 *)((int)puVar1 + 0x16b));
        }
        iVar8 = 1;
        delete_sae_instance(puVar1);
        puVar1 = (uint *)0x0;
        goto LAB_0020b520;
      }
LAB_0020b75c:
      iVar8 = sae_using_anti_clogging(param_2);
      if (iVar8 != 0) {
        iVar8 = 0x4c;
        sae_build_token_req(param_1,puVar1,local_78,&local_7c);
        goto LAB_0020b520;
      }
LAB_0020b76c:
      iVar8 = sae_sm_step(param_1,puVar1,1);
      if (3 < DebugLevel) {
        printk("%s(): SAE_COMMIT_SEQ, res(sae_sm_step) = %d\n","sae_handle_auth",iVar8);
      }
      if ((iVar8 - 1U & 0xffff) < 0xfffe) goto LAB_0020b520;
    }
    if (puVar1 == (uint *)0x0) {
LAB_0020b654:
      *param_10 = 0;
      return 0;
    }
  }
  else {
    if (param_8 != 2) {
      iVar8 = 0xe;
      delete_sae_instance(puVar1);
      puVar1 = (uint *)0x0;
      goto LAB_0020b520;
    }
    if (*puVar1 == 0) goto LAB_0020b564;
    if (param_9 != 0) {
      if (-1 < DebugLevel) {
        printk("%s(): receive error status auth confirm msg, so delete the instance\n",
               "sae_handle_auth");
      }
      goto LAB_0020b650;
    }
    if ((*puVar1 - 2 < 2) && (iVar8 = sae_parse_confirm(puVar1,param_3,param_4), iVar8 != 0)) {
      if (*puVar1 == 3) {
        sae_check_big_sync(puVar1);
        goto LAB_0020b564;
      }
      if (-1 < DebugLevel) {
        printk("%s(): verify confirm fail, remove instance\n","sae_handle_auth");
      }
LAB_0020b60c:
      delete_sae_instance(puVar1);
LAB_0020b614:
      if (iVar8 == 0xffff) goto LAB_0020b654;
      puVar1 = (uint *)0x0;
      goto LAB_0020b520;
    }
    iVar8 = sae_sm_step(param_1,puVar1,2);
    if (2 < DebugLevel) {
      printk("%s(): SAE_CONFIRM_SEQ, res(sae_sm_step) = %d\n","sae_handle_auth",iVar8);
    }
LAB_0020b738:
    if ((iVar8 - 1U & 0xffff) < 0xfffe) goto LAB_0020b520;
  }
  if (*puVar1 == 3) {
    store_time_log_by_tag(1,puVar1 + 0x27);
    BigInteger_dump_time();
    ecc_point_dump_time();
    *param_10 = (int)(puVar1 + 2);
    hex_dump_with_lvl("sae success, pmk:",puVar1 + 2,0x20,3);
    return 1;
  }
LAB_0020b564:
  *param_10 = 0;
  return 1;
}

