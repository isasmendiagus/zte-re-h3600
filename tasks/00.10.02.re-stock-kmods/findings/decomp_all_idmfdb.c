/* ============= FUNCTION: idm_fdb_recv_handle @ 00010000 ============= */

undefined4 idm_fdb_recv_handle(char *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  
  if (param_2 == 0 || param_1 == (char *)0x0) {
    return 0xffffffff;
  }
  iVar1 = ffe_get_npu_enable();
  if (iVar1 != 0) {
    *(char *)(param_2 + 0xb7) = param_1[3];
    uVar4 = *(uint *)(param_1 + 0xa8);
    uVar3 = *(uint *)(param_1 + 0xb0);
    *(uint *)(param_1 + 0xa8) = uVar4 + 1;
    *(uint *)(param_1 + 0xac) = *(int *)(param_1 + 0xac) + (uint)(0xfffffffe < uVar4);
    uVar4 = *(uint *)(param_2 + 100);
    *(uint *)(param_1 + 0xb0) = uVar3 + uVar4;
    *(uint *)(param_1 + 0xb4) = *(int *)(param_1 + 0xb4) + (uint)CARRY4(uVar3,uVar4);
    uVar4 = ifd_debug;
    if (((*param_1 != '\0') && (*(int *)(param_1 + 0x10) != 0)) && (*(int *)(param_1 + 8) == 0)) {
      *(undefined4 *)(param_2 + 0x18) = *(undefined4 *)(param_1 + 0x14);
      if ((uVar4 & 0x11) == 0x11) {
        printk("%s:from dev:%s, would forward to %s\n","wlan_recv_idm_handle",
               *(undefined4 *)(param_1 + 0x14),*(undefined4 *)(param_1 + 0x10));
        printk("skb->head:\t%p\nskb->data:\t%p\nskb->mac_head:\t%p\nskb->cloned:\t%d\nref:\t%d\n",
               *(undefined4 *)(param_2 + 200),*(undefined4 *)(param_2 + 0xcc),
               *(undefined2 *)(param_2 + 0xaa),*(byte *)(param_2 + 0x72) & 1,
               *(undefined4 *)(*(int *)(param_2 + 0xc4) + 0x20));
        if (*(int *)(param_2 + 100) != 0) {
          printk("%02x ",**(undefined1 **)(param_2 + 0xcc));
          uVar4 = 0;
          while (uVar4 = uVar4 + 1, uVar4 < *(uint *)(param_2 + 100)) {
            printk("%02x ",*(undefined1 *)(*(int *)(param_2 + 0xcc) + uVar4));
            uVar3 = uVar4 & 0x8000000f;
            if ((int)uVar3 < 0) {
              uVar3 = ~(~((uVar3 - 1) * 0x10000000) >> 0x1c) + 1;
            }
            if (uVar3 == 0xf) {
              printk(&_LC14);
            }
          }
        }
        printk(&_LC14);
      }
                    /* WARNING: Could not recover jumptable at 0x000100b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 300) + 0x10))(param_2);
      return uVar2;
    }
  }
  return 0xffffffff;
}


/* ============= FUNCTION: idm_fdb_forward @ 00010190 ============= */

undefined4 idm_fdb_forward(uint param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  undefined1 *in_r12;
  
  if (param_2 == 0) {
    return 0xffffffff;
  }
  if (param_1 < 2) {
    uVar2 = (uint)*(byte *)(param_2 + 0xb7);
    bVar3 = **(byte **)(param_2 + 0xcc);
    uVar1 = bVar3 & 1;
    if ((bVar3 & 1) == 0) {
      if (uVar2 < 8) {
        iVar4 = uVar2 + param_1 * 8;
        in_r12 = &fdb_list + iVar4 * 0x128;
        iVar5 = (&DAT_0001341c)[iVar4 * 0x4a];
        if (iVar5 == 0) {
          bVar3 = 0;
        }
        else {
          bVar3 = (&fdb_list)[iVar4 * 0x128] & 1;
        }
        if ((bVar3 != 0) && ((*(uint *)(iVar5 + 0x30) & 1) != 0)) {
          *(int *)(param_2 + 0x18) = iVar5;
          if ((ifd_debug & 9) == 9) {
            printk("%s:from idm:%d ssid%d, send to %s\n",DAT_000103f0,param_1,uVar2,
                   (&DAT_0001341c)[iVar4 * 0x4a]);
            printk("skb->head:\t%p\nskb->data:\t%p\nskb->mac_head:\t%p\nskb->cloned:\t%d\nref:\t%d\n"
                   ,*(undefined4 *)(param_2 + 200),*(undefined4 *)(param_2 + 0xcc),
                   *(undefined2 *)(param_2 + 0xaa),*(byte *)(param_2 + 0x72) & 1,
                   *(undefined4 *)(*(int *)(param_2 + 0xc4) + 0x20));
            if (*(int *)(param_2 + 100) != 0) {
              printk("%02x ",**(undefined1 **)(param_2 + 0xcc));
              while (uVar1 = uVar1 + 1, uVar1 < *(uint *)(param_2 + 100)) {
                printk("%02x ",*(undefined1 *)(*(int *)(param_2 + 0xcc) + uVar1));
                if ((uVar1 & 0xf) == 0xf) {
                  printk(&_LC14);
                }
              }
            }
            printk(&_LC14);
          }
          iVar5 = (**(code **)(*(int *)(iVar5 + 300) + 0x10))(param_2,iVar5);
          if (iVar5 == 0) {
            iVar4 = iVar4 * 0x128;
            uVar1 = *(uint *)(&DAT_00013420 + iVar4);
            uVar2 = *(uint *)(&DAT_00013428 + iVar4);
            *(uint *)(&DAT_00013420 + iVar4) = uVar1 + 1;
            *(uint *)(&DAT_00013424 + iVar4) =
                 *(int *)(&DAT_00013424 + iVar4) + (uint)(0xfffffffe < uVar1);
            uVar1 = *(uint *)(param_2 + 100);
            *(uint *)(&DAT_00013428 + iVar4) = uVar2 + uVar1;
            *(uint *)(&DAT_0001342c + iVar4) =
                 *(int *)(&DAT_0001342c + iVar4) + (uint)CARRY4(uVar2,uVar1);
            return 0;
          }
          iVar4 = iVar4 * 0x128;
          uVar2 = *(uint *)(&DAT_000134c8 + iVar4);
          uVar1 = *(uint *)(&DAT_000134d0 + iVar4);
          *(uint *)(&DAT_000134c8 + iVar4) = uVar2 + 1;
          *(uint *)(&DAT_000134cc + iVar4) =
               *(int *)(&DAT_000134cc + iVar4) + (uint)(0xfffffffe < uVar2);
          uVar2 = *(uint *)(param_2 + 100);
          *(uint *)(&DAT_000134d0 + iVar4) = uVar1 + uVar2;
          *(uint *)(&DAT_000134d4 + iVar4) =
               *(int *)(&DAT_000134d4 + iVar4) + (uint)CARRY4(uVar1,uVar2);
          __dev_kfree_skb_any(param_2,1);
          return 0;
        }
        goto LAB_000101b0;
      }
    }
    else if (bVar3 == 0xff) {
      uVar1 = 2;
    }
    else {
      uVar1 = 1;
    }
    idm_fdb_multi_send_handle(param_1,uVar2,param_2,uVar1);
  }
  else {
LAB_000101b0:
    if (in_r12 != (undefined1 *)0x0) {
      uVar1 = *(uint *)(in_r12 + 0xc0);
      uVar2 = *(uint *)(in_r12 + 200);
      *(uint *)(in_r12 + 0xc0) = uVar1 + 1;
      *(uint *)(in_r12 + 0xc4) = *(int *)(in_r12 + 0xc4) + (uint)(0xfffffffe < uVar1);
      uVar1 = *(uint *)(param_2 + 100);
      *(uint *)(in_r12 + 200) = uVar2 + uVar1;
      *(uint *)(in_r12 + 0xcc) = *(int *)(in_r12 + 0xcc) + (uint)CARRY4(uVar2,uVar1);
    }
    __dev_kfree_skb_any(param_2,1);
  }
  return 0;
}


/* ============= FUNCTION: idm_fdb_hook_xmit @ 000103f4 ============= */

void idm_fdb_hook_xmit(int param_1)

{
  uint uVar1;
  uint uVar2;
  
  if ((*(ushort *)(param_1 + 0xbc) & 0x10) != 0) {
    return;
  }
  if ((ifd_debug & 1) != 0) {
    printk(&_LC17,DAT_00010528);
    if (*(int *)(param_1 + 0x18) != 0) {
      printk("skb->dev->name:%s\n");
    }
    printk("skb->head:\t%p\nskb->data:\t%p\nskb->mac_head:\t%p\nskb->cloned:\t%d\nref:\t%d\n",
           *(undefined4 *)(param_1 + 200),*(undefined4 *)(param_1 + 0xcc),
           *(undefined2 *)(param_1 + 0xaa),*(byte *)(param_1 + 0x72) & 1,
           *(undefined4 *)(*(int *)(param_1 + 0xc4) + 0x20));
    if (*(int *)(param_1 + 100) != 0) {
      uVar2 = 0;
      printk("%02x ",**(undefined1 **)(param_1 + 0xcc));
      while (uVar2 = uVar2 + 1, uVar2 < *(uint *)(param_1 + 100)) {
        printk("%02x ",*(undefined1 *)(*(int *)(param_1 + 0xcc) + uVar2));
        uVar1 = uVar2 & 0x8000000f;
        if ((int)uVar1 < 0) {
          uVar1 = ~(~((uVar1 - 1) * 0x10000000) >> 0x1c) + 1;
        }
        if (uVar1 == 0xf) {
          printk(&_LC14);
        }
      }
    }
    printk(&_LC14);
  }
  if (*(int *)(param_1 + 0x18) == 0) {
    return;
  }
  ffe_learn_skb(param_1,3);
  return;
}


/* ============= FUNCTION: get_node_index @ 0001052c ============= */

int get_node_index(void)

{
  int iVar1;
  
  iVar1 = WlanIndex2WlanIdmMap();
  if (iVar1 == 0) {
    iVar1 = 0xff;
  }
  else {
    iVar1 = (uint)*(byte *)(iVar1 + 0x26) + (uint)*(byte *)(iVar1 + 0x25) * 8;
  }
  return iVar1;
}


/* ============= FUNCTION: idm_fdb_idm_isolate_handle @ 0001054c ============= */

void idm_fdb_idm_isolate_handle(void)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  uint uVar6;
  int iStack_4c;
  int local_48 [17];
  
  pcVar4 = &fdb_list;
  uVar6 = 0;
  iVar2 = 0;
  do {
    if (((*pcVar4 != '\0') && (iVar5 = *(int *)(pcVar4 + 0x14), pcVar4[1] == '\0')) &&
       (*(uint *)(pcVar4 + 8) = *(uint *)(pcVar4 + 8) & 0xfffffffe, iVar5 != 0)) {
      if (((*(uint *)(iVar5 + 0x30) & 1) == 0) || (pcVar4[4] != '\x02')) {
        if (((*(uint *)(iVar5 + 0x30) & 1) != 0) && (pcVar4[4] == '\0')) {
          local_48[uVar6] = (int)pcVar4;
          uVar6 = uVar6 + 1;
        }
      }
      else {
        iVar2 = iVar2 + 1;
      }
    }
    pcVar4 = pcVar4 + 0x128;
  } while (pcVar4 != &__this_module);
  if (uVar6 != 0 || iVar2 == 0) {
    if ((iVar2 == 0 && uVar6 != 0) || (uVar6 == 0 || iVar2 == 0)) {
      sw_set_idm_isolate(0,0);
      return;
    }
    piVar1 = &iStack_4c;
    uVar3 = 0;
    do {
      piVar1 = piVar1 + 1;
      uVar3 = uVar3 + 1;
      *(uint *)(*piVar1 + 8) = *(uint *)(*piVar1 + 8) | 1;
    } while (uVar3 < uVar6);
  }
  sw_set_idm_isolate(0,1);
  return;
}


/* ============= FUNCTION: register_idm_fdb_node @ 00010674 ============= */

undefined1 * register_idm_fdb_node(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  char local_20 [16];
  
  local_20[0] = '\0';
  local_20[1] = '\0';
  local_20[2] = '\0';
  local_20[3] = '\0';
  local_20[4] = '\0';
  local_20[5] = '\0';
  local_20[6] = '\0';
  local_20[7] = '\0';
  local_20[8] = '\0';
  local_20[9] = '\0';
  local_20[10] = '\0';
  local_20[0xb] = '\0';
  local_20[0xc] = '\0';
  local_20[0xd] = '\0';
  local_20[0xe] = '\0';
  local_20[0xf] = '\0';
  if ((param_2 != 0) && (iVar2 = get_node_index(), iVar2 < 0x10)) {
    iVar1 = iVar2 * 0x128;
    (&fdb_list)[iVar1] = 1;
    snprintf(local_20,0xf,"idm%d",(uint)(byte)(&DAT_00013409)[iVar1]);
    uVar3 = __dev_get_by_name(&init_net,local_20);
    (&DAT_0001341c)[iVar2 * 0x4a] = param_2;
    *(undefined4 *)(&DAT_00013418 + iVar1) = uVar3;
    iVar2 = WlanIndex2WlanIdmMap(param_1);
    if (iVar2 != 0) {
      (&DAT_0001340c)[iVar1] = *(undefined1 *)(iVar2 + 0x22);
    }
    create_idm_proc_file(&fdb_list + iVar1);
    idm_fdb_idm_isolate_handle();
    return &fdb_list + iVar1;
  }
  return (undefined1 *)0x0;
}


/* ============= FUNCTION: idm_netdev_event @ 00010734 ============= */

undefined4 idm_netdev_event(undefined4 param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  
  iVar1 = IfName2WlanIdmMap(*param_3);
  if (((iVar1 != 0) && (param_2 - 1U < 2)) && (*(char *)(iVar1 + 0x25) == '\0')) {
    idm_fdb_idm_isolate_handle();
    return 0;
  }
  return 0;
}


/* ============= FUNCTION: print_idm_node_stat @ 00010778 ============= */

int print_idm_node_stat(byte *param_1,char *param_2,size_t param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int unaff_r5;
  bool bVar4;
  bool bVar5;
  undefined4 auStack_54 [12];
  
  bVar4 = param_1 != (byte *)0x0;
  bVar5 = param_2 != (char *)0x0;
  if (!bVar4 || !bVar5) {
    unaff_r5 = 1;
  }
  if (bVar4 && bVar5) {
    unaff_r5 = 0;
  }
  auStack_54[0] = *DAT_0001095c;
  auStack_54[1] = DAT_0001095c[1];
  auStack_54[2] = DAT_0001095c[2];
  auStack_54[3] = DAT_0001095c[3];
  auStack_54[4] = DAT_0001095c[4];
  auStack_54[5] = DAT_0001095c[5];
  auStack_54[6] = DAT_0001095c[6];
  auStack_54[7] = DAT_0001095c[7];
  auStack_54[8] = DAT_0001095c[8];
  auStack_54[9] = DAT_0001095c[9];
  auStack_54[10] = DAT_0001095c[10];
  if (bVar4 && bVar5) {
    if ((0 < (int)param_3) &&
       (unaff_r5 = snprintf(param_2,param_3,"en:\t%d\n",(uint)*param_1), unaff_r5 < (int)param_3)) {
      iVar1 = snprintf(param_2 + unaff_r5,param_3 - unaff_r5,"idm:\t%d\n",(uint)param_1[1]);
      unaff_r5 = unaff_r5 + iVar1;
      if (unaff_r5 < (int)param_3) {
        iVar1 = snprintf(param_2 + unaff_r5,param_3 - unaff_r5,"ssid:\t%d\n",(uint)param_1[3]);
        unaff_r5 = unaff_r5 + iVar1;
        if (unaff_r5 < (int)param_3) {
          iVar1 = snprintf(param_2 + unaff_r5,param_3 - unaff_r5,"dev:\t%s\n",
                           *(undefined4 *)(param_1 + 0x14));
          unaff_r5 = unaff_r5 + iVar1;
          if (unaff_r5 < (int)param_3) {
            iVar1 = snprintf(param_2 + unaff_r5,param_3 - unaff_r5,"running:\t%d\n",
                             *(uint *)(*(int *)(param_1 + 0x14) + 0x30) & 1);
            unaff_r5 = unaff_r5 + iVar1;
            if (unaff_r5 < (int)param_3) {
              iVar1 = snprintf(param_2 + unaff_r5,param_3 - unaff_r5,"cnt:\n");
              unaff_r5 = unaff_r5 + iVar1;
            }
          }
        }
      }
    }
    uVar2 = 0;
    do {
      while ((int)param_3 <= unaff_r5) {
        uVar2 = uVar2 + 1;
        param_1 = param_1 + 0x18;
        if (uVar2 == 0xb) goto LAB_00010928;
      }
      uVar3 = uVar2 + 1;
      iVar1 = snprintf(param_2 + unaff_r5,param_3 - unaff_r5,"%20s: %10lld pkt, %10lld bytes\n",
                       auStack_54[uVar2 % 0xb],*(undefined4 *)(param_1 + 0x18),
                       *(undefined4 *)(param_1 + 0x1c),*(undefined4 *)(param_1 + 0x20),
                       *(undefined4 *)(param_1 + 0x24));
      unaff_r5 = unaff_r5 + iVar1;
      uVar2 = uVar3;
      param_1 = param_1 + 0x18;
    } while (uVar3 != 0xb);
LAB_00010928:
    if (unaff_r5 < (int)param_3) {
      iVar1 = snprintf(param_2 + unaff_r5,param_3 - unaff_r5,"\n");
      return unaff_r5 + iVar1;
    }
  }
  else {
    unaff_r5 = 0;
  }
  return unaff_r5;
}


/* ============= FUNCTION: print_idm_map @ 00010960 ============= */

int print_idm_map(undefined4 param_1,char *param_2,size_t param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  int iVar7;
  byte bVar8;
  
  if ((int)param_3 < 1) {
    iVar7 = 0;
  }
  else {
    iVar7 = snprintf(param_2,param_3,"wlan_dev_map:\n");
    if (iVar7 < (int)param_3) {
      iVar4 = snprintf(param_2 + iVar7,param_3 - iVar7,"fdb_list:\n");
      iVar7 = iVar7 + iVar4;
    }
  }
  iVar4 = 0;
  pbVar6 = &fdb_list;
  do {
    while( true ) {
      if (iVar7 < (int)param_3) {
        bVar8 = *pbVar6 & 1;
      }
      else {
        bVar8 = 0;
      }
      if (bVar8 == 0) break;
      pbVar1 = pbVar6 + 1;
      pbVar2 = pbVar6 + 3;
      pbVar3 = pbVar6 + 0x14;
      pbVar6 = pbVar6 + 0x128;
      iVar5 = snprintf(param_2 + iVar7,param_3 - iVar7,"%d: idm:%d ssid:%d dev:%s\n",iVar4,
                       (uint)*pbVar1,(uint)*pbVar2,*(undefined4 *)pbVar3);
      iVar4 = iVar4 + 1;
      iVar7 = iVar7 + iVar5;
      if (pbVar6 == &__this_module) goto LAB_00010a30;
    }
    pbVar6 = pbVar6 + 0x128;
    iVar4 = iVar4 + 1;
  } while (pbVar6 != &__this_module);
LAB_00010a30:
  if (iVar7 < (int)param_3) {
    iVar4 = snprintf(param_2 + iVar7,param_3 - iVar7,"\n");
    iVar7 = iVar4 + iVar7;
  }
  return iVar7;
}


/* ============= FUNCTION: print_idm_flood_status @ 00010a5c ============= */

int print_idm_flood_status(undefined4 param_1,char *param_2,size_t param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  if ((int)param_3 < 1) {
    iVar2 = 0;
  }
  else {
    iVar2 = snprintf(param_2,param_3,"idm_flood_status:\n");
  }
  iVar3 = 0;
  do {
    if (iVar2 < (int)param_3) {
      iVar1 = snprintf(param_2 + iVar2,param_3 - iVar2,"idm%d:\n",iVar3);
      iVar2 = iVar2 + iVar1;
      if (iVar2 < (int)param_3) {
        iVar1 = snprintf(param_2 + iVar2,param_3 - iVar2,"  UNICAST   %10lld\n");
        iVar2 = iVar2 + iVar1;
        if (iVar2 < (int)param_3) {
          iVar1 = snprintf(param_2 + iVar2,param_3 - iVar2,"  MULTICAST %10lld\n");
          iVar2 = iVar2 + iVar1;
          if (iVar2 < (int)param_3) {
            iVar1 = snprintf(param_2 + iVar2,param_3 - iVar2,"  BROADCAST %10lld\n");
            iVar2 = iVar2 + iVar1;
            if (iVar2 < (int)param_3) {
              iVar1 = snprintf(param_2 + iVar2,param_3 - iVar2,"  DROP      %10lld\n");
              iVar2 = iVar2 + iVar1;
            }
          }
        }
      }
    }
    bVar4 = iVar3 != 1;
    iVar3 = 1;
  } while (bVar4);
  if (iVar2 < (int)param_3) {
    iVar3 = snprintf(param_2 + iVar2,param_3 - iVar2,"\n");
    return iVar2 + iVar3;
  }
  return iVar2;
}


/* ============= FUNCTION: wlan_recv_idm_handle @ 00010ba8 ============= */

undefined4 wlan_recv_idm_handle(char *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  
  if (param_2 == 0 || param_1 == (char *)0x0) {
    return 0xffffffff;
  }
  iVar1 = ffe_get_npu_enable();
  if (iVar1 != 0) {
    *(char *)(param_2 + 0xb7) = param_1[3];
    uVar4 = *(uint *)(param_1 + 0xa8);
    uVar3 = *(uint *)(param_1 + 0xb0);
    *(uint *)(param_1 + 0xa8) = uVar4 + 1;
    *(uint *)(param_1 + 0xac) = *(int *)(param_1 + 0xac) + (uint)(0xfffffffe < uVar4);
    uVar4 = *(uint *)(param_2 + 100);
    *(uint *)(param_1 + 0xb0) = uVar3 + uVar4;
    *(uint *)(param_1 + 0xb4) = *(int *)(param_1 + 0xb4) + (uint)CARRY4(uVar3,uVar4);
    uVar4 = ifd_debug;
    if (((*param_1 != '\0') && (*(int *)(param_1 + 0x10) != 0)) && (*(int *)(param_1 + 8) == 0)) {
      *(undefined4 *)(param_2 + 0x18) = *(undefined4 *)(param_1 + 0x14);
      if ((uVar4 & 0x11) == 0x11) {
        printk("%s:from dev:%s, would forward to %s\n","wlan_recv_idm_handle",
               *(undefined4 *)(param_1 + 0x14),*(undefined4 *)(param_1 + 0x10));
        printk("skb->head:\t%p\nskb->data:\t%p\nskb->mac_head:\t%p\nskb->cloned:\t%d\nref:\t%d\n",
               *(undefined4 *)(param_2 + 200),*(undefined4 *)(param_2 + 0xcc),
               *(undefined2 *)(param_2 + 0xaa),*(byte *)(param_2 + 0x72) & 1,
               *(undefined4 *)(*(int *)(param_2 + 0xc4) + 0x20));
        if (*(int *)(param_2 + 100) != 0) {
          printk("%02x ",**(undefined1 **)(param_2 + 0xcc));
          uVar4 = 0;
          while (uVar4 = uVar4 + 1, uVar4 < *(uint *)(param_2 + 100)) {
            printk("%02x ",*(undefined1 *)(*(int *)(param_2 + 0xcc) + uVar4));
            uVar3 = uVar4 & 0x8000000f;
            if ((int)uVar3 < 0) {
              uVar3 = ~(~((uVar3 - 1) * 0x10000000) >> 0x1c) + 1;
            }
            if (uVar3 == 0xf) {
              printk(&_LC14);
            }
          }
        }
        printk(&_LC14);
      }
                    /* WARNING: Could not recover jumptable at 0x00010c58. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar2 = (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 300) + 0x10))(param_2);
      return uVar2;
    }
  }
  return 0xffffffff;
}


/* ============= FUNCTION: idm_fdb_exit @ 00010d38 ============= */

void idm_fdb_exit(void)

{
  idm_skb_recv = 0;
  return;
}


/* ============= FUNCTION: INC_MTRANS_CNT @ 00010d4c ============= */

void INC_MTRANS_CNT(uint param_1,byte *param_2,byte *param_3,int param_4)

{
  int iVar1;
  undefined2 uVar2;
  uint uVar3;
  undefined1 *puVar4;
  uint uVar5;
  
  uVar5 = ((uint)param_2[1] << 8 | (uint)*param_2 << 0x10 | (uint)param_2[2]) ^ param_1 ^
          ~((uint)param_2[4] << 8 | (uint)param_2[3] << 0x10 | (uint)param_2[5]) ^
          ((uint)param_3[1] << 8 | (uint)*param_3 << 0x10 | (uint)param_3[2]) ^
          ~((uint)param_3[4] << 8 | (uint)param_3[3] << 0x10 | (uint)param_3[5]);
  iVar1 = (uVar5 & 0x7f) * 0x30;
  puVar4 = &g_mtrans_dbg_cnt + iVar1;
  if ((&g_mtrans_dbg_cnt)[iVar1] != '\0') {
    if (*(uint *)(&DAT_00014b6c + iVar1) == uVar5) goto LAB_00010e2c;
    iVar1 = ((uVar5 & 0x3f) + 0x80) * 0x30;
    puVar4 = &g_mtrans_dbg_cnt + iVar1;
    if ((&g_mtrans_dbg_cnt)[iVar1] != '\0') {
      if (*(uint *)(&DAT_00014b6c + iVar1) != uVar5) {
        return;
      }
      goto LAB_00010e2c;
    }
  }
  *(uint *)(puVar4 + 4) = uVar5;
  *puVar4 = 1;
  *(undefined4 *)(puVar4 + 8) = *(undefined4 *)param_2;
  *(undefined2 *)(puVar4 + 0xc) = *(undefined2 *)(param_2 + 4);
  *(undefined4 *)(puVar4 + 0xe) = *(undefined4 *)param_3;
  uVar2 = *(undefined2 *)(param_3 + 4);
  *(uint *)(puVar4 + 0x18) = param_1;
  *(undefined2 *)(puVar4 + 0x12) = uVar2;
LAB_00010e2c:
  uVar5 = *(uint *)(puVar4 + 0x20);
  uVar3 = *(uint *)(puVar4 + 0x28);
  *(uint *)(puVar4 + 0x20) = uVar5 + 1;
  *(uint *)(puVar4 + 0x24) = *(int *)(puVar4 + 0x24) + (uint)(0xfffffffe < uVar5);
  uVar5 = *(uint *)(param_4 + 100);
  *(uint *)(puVar4 + 0x28) = uVar3 + uVar5;
  *(uint *)(puVar4 + 0x2c) = *(int *)(puVar4 + 0x2c) + (uint)CARRY4(uVar3,uVar5);
  return;
}


/* ============= FUNCTION: __idm_fdb_create_items.constprop.0 @ 00010e88 ============= */

void __idm_fdb_create_items_constprop_0(int param_1,int param_2,int param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  char *pcVar4;
  int iVar5;
  
  if (0 < param_2) {
    iVar2 = *param_4;
    if (iVar2 < 1) {
      iVar1 = 0;
    }
    else {
      puVar3 = (undefined4 *)(param_1 + -4);
      iVar1 = 0;
      iVar5 = 0;
      do {
        puVar3 = puVar3 + 1;
        pcVar4 = (char *)*puVar3;
        iVar5 = iVar5 + 1;
        if (((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) &&
           ((*(uint *)(*(int *)(pcVar4 + 0x14) + 0x30) & 1) != 0)) {
          *(undefined4 *)(param_3 + 0xc) = 0;
          *(char **)(param_3 + 8) = pcVar4;
          iVar1 = iVar1 + 1;
          iVar2 = *param_4;
          param_3 = param_3 + 0x18;
        }
      } while ((iVar5 != param_2) && (iVar1 < iVar2));
    }
    *param_4 = iVar2 - iVar1;
    return;
  }
  *param_4 = *param_4;
  return;
}


/* ============= FUNCTION: print_idm_multicast_cnt @ 00010f34 ============= */

int print_idm_multicast_cnt(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  
  pcVar2 = &g_mtrans_dbg_cnt;
  iVar3 = 0;
  do {
    if (*pcVar2 != '\0') {
      if (0 < param_3) {
        iVar1 = snprintf((char *)(param_2 + iVar3),param_3 - iVar3,
                         "%10s: mcast %02x:%02x:%02x:%02x:%02x:%02x to %02x:%02x:%02x:%02x:%02x:%02x\n\t  %10lld pkt, %10lld bytes\n"
                         ,*(undefined4 *)(*(int *)(pcVar2 + 0x18) + 0x14),(uint)(byte)pcVar2[0xe],
                         (uint)(byte)pcVar2[0xf],(uint)(byte)pcVar2[0x10],(uint)(byte)pcVar2[0x11],
                         (uint)(byte)pcVar2[0x12],(uint)(byte)pcVar2[0x13],(uint)(byte)pcVar2[8],
                         (uint)(byte)pcVar2[9],(uint)(byte)pcVar2[10],(uint)(byte)pcVar2[0xb],
                         (uint)(byte)pcVar2[0xc],(uint)(byte)pcVar2[0xd],
                         *(undefined4 *)(pcVar2 + 0x20),*(undefined4 *)(pcVar2 + 0x24),
                         *(undefined4 *)(pcVar2 + 0x28),*(undefined4 *)(pcVar2 + 0x2c));
        iVar3 = iVar3 + iVar1;
      }
    }
    pcVar2 = pcVar2 + 0x30;
  } while (pcVar2 != g_PortMacInfo);
  if (0 < param_3) {
    iVar1 = snprintf((char *)(param_2 + iVar3),param_3 - iVar3,"\n");
    iVar3 = iVar3 + iVar1;
  }
  return iVar3;
}


/* ============= FUNCTION: idm_fdb_multi_send_handle @ 00011038 ============= */

undefined4 idm_fdb_multi_send_handle(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined1 **ppuVar4;
  undefined **ppuVar5;
  ushort uVar7;
  undefined4 uVar8;
  uint uVar9;
  undefined4 *puVar10;
  char *pcVar11;
  ushort uVar12;
  undefined1 *puVar13;
  undefined1 *puVar14;
  undefined1 *puVar15;
  int iVar16;
  int iVar17;
  uint uVar18;
  int local_37c;
  undefined **local_378;
  undefined4 local_36c;
  undefined1 *local_368;
  uint local_364;
  uint local_360;
  ushort local_35c;
  int local_358 [3];
  undefined4 local_34c;
  undefined4 uStack_348;
  undefined4 uStack_344;
  undefined4 uStack_340;
  undefined4 local_33c;
  undefined4 uStack_338;
  undefined4 uStack_334;
  undefined4 uStack_330;
  ushort local_32c;
  undefined1 auStack_328 [12];
  uint local_31c [190];
  undefined **ppuVar6;
  
  local_36c = 0x20;
  local_368 = (undefined1 *)0x0;
  if (1 < param_1 || param_3 == 0) {
    if (param_3 == 0) {
      return 0;
    }
    goto LAB_0001120c;
  }
  if ((ifd_debug & 1) != 0) {
    printk("%s original pkt:from idm:%d, ssid:%d\n","idm_fdb_multi_send_handle",param_1,param_2);
    printk("skb->head:\t%p\nskb->data:\t%p\nskb->mac_head:\t%p\nskb->cloned:\t%d\nref:\t%d\n",
           *(undefined4 *)(param_3 + 200),*(undefined4 *)(param_3 + 0xcc),
           *(undefined2 *)(param_3 + 0xaa),*(byte *)(param_3 + 0x72) & 1,
           *(undefined4 *)(*(int *)(param_3 + 0xc4) + 0x20));
    if (*(int *)(param_3 + 100) != 0) {
      printk("%02x ",**(undefined1 **)(param_3 + 0xcc));
      uVar3 = 0;
      while (uVar3 = uVar3 + 1, uVar3 < *(uint *)(param_3 + 100)) {
        printk("%02x ",*(undefined1 *)(*(int *)(param_3 + 0xcc) + uVar3));
        uVar9 = uVar3 & 0x8000000f;
        if ((int)uVar9 < 0) {
          uVar9 = ~(~((uVar9 - 1) * 0x10000000) >> 0x1c) + 1;
        }
        if (uVar9 == 0xf) {
          printk(&_LC1);
        }
      }
    }
    printk(&_LC1);
  }
  iVar1 = DAT_00011938;
  if (param_4 == 1) {
    if (param_1 == 0) {
      local_37c = 4;
      local_378 = &mcast_flood_group_idm0;
    }
    else {
      if (param_1 != 1) goto LAB_0001120c;
      local_378 = DAT_00011934;
      local_37c = 5;
    }
    iVar2 = param_1 * 0x108;
    uVar3 = 0;
    local_358[0] = 0;
    iVar16 = *(int *)(&DAT_00014974 + iVar2) + (uint)(0xfffffffe < *(uint *)(&DAT_00014970 + iVar2))
    ;
    *(uint *)(&DAT_00014970 + iVar2) = *(uint *)(&DAT_00014970 + iVar2) + 1;
    *(int *)(&DAT_00014974 + iVar2) = iVar16;
    uVar9 = *(uint *)(&DAT_00014978 + iVar2);
    uVar18 = *(uint *)(param_3 + 100);
    *(uint *)(&DAT_00014978 + iVar2) = uVar9 + uVar18;
    *(uint *)(&DAT_0001497c + iVar2) = *(int *)(&DAT_0001497c + iVar2) + (uint)CARRY4(uVar9,uVar18);
    __memzero(iVar1,0xf00);
    iVar2 = *(int *)(param_3 + 0xcc);
    local_358[2] = iVar1;
    local_358[1] = 0x20;
    uVar7 = *(ushort *)(iVar2 + 0xc) << 8 | *(ushort *)(iVar2 + 0xc) >> 8;
    if (uVar7 == 0x8100) {
      uVar3 = (uint)*(ushort *)(iVar2 + 0x10);
      uVar9 = (uVar3 & 0xff) << 8 | (uint)(*(ushort *)(iVar2 + 0x10) >> 8);
      if (uVar3 != 0x81) {
        iVar16 = iVar2 + 0x12;
      }
      uVar12 = (*(ushort *)(iVar2 + 0xe) & 0xf) << 8 | *(ushort *)(iVar2 + 0xe) >> 8;
      if (uVar3 == 0x81) {
        uVar3 = (uint)*(ushort *)(iVar2 + 0x14);
        iVar16 = iVar2 + 0x16;
        uVar9 = (uVar3 & 0xff) << 8 | (uint)(*(ushort *)(iVar2 + 0x14) >> 8);
      }
      if ((ifd_debug & 2) != 0) goto LAB_000117d8;
LAB_0001137c:
      if (uVar9 == 0x800) goto LAB_00011498;
      if ((uVar7 == 0x86dd) || (uVar9 == 0x86dd)) {
        local_34c = *(undefined4 *)(iVar16 + 0x18);
        uStack_348 = *(undefined4 *)(iVar16 + 0x1c);
        uStack_344 = *(undefined4 *)(iVar16 + 0x20);
        uStack_340 = *(undefined4 *)(iVar16 + 0x24);
        local_33c = *(undefined4 *)(iVar16 + 8);
        uStack_338 = *(undefined4 *)(iVar16 + 0xc);
        uStack_334 = *(undefined4 *)(iVar16 + 0x10);
        uStack_330 = *(undefined4 *)(iVar16 + 0x14);
        local_32c = uVar12;
        iVar1 = br_lookup_mfd(0,&local_34c,local_358,2);
        goto LAB_000114c8;
      }
LAB_0001139c:
      iVar1 = __idm_fdb_create_items_constprop_0(local_378,local_37c,auStack_328,&local_36c);
      goto LAB_000110e8;
    }
    iVar16 = iVar2 + 0xe;
    if ((ifd_debug & 2) == 0) {
      uVar12 = 0;
      uVar3 = 0;
    }
    else {
      uVar12 = 0;
      uVar9 = 0;
LAB_000117d8:
      printk("ethh->h_proto:%x\nvlan_tagged_proto:%x\n",uVar7,uVar9);
      uVar7 = *(ushort *)(iVar2 + 0xc) << 8 | *(ushort *)(iVar2 + 0xc) >> 8;
    }
    if (uVar7 != 0x800) {
      uVar9 = (uVar3 & 0xff) << 8 | uVar3 >> 8;
      goto LAB_0001137c;
    }
LAB_00011498:
    local_35c = uVar12;
    uVar9 = *(uint *)(iVar16 + 0x10);
    uVar3 = *(uint *)(iVar16 + 0xc);
    local_364 = uVar9 << 0x18 | (uVar9 >> 8 & 0xff) << 0x10 | (uVar9 >> 0x10 & 0xff) << 8 |
                uVar9 >> 0x18;
    local_360 = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
                uVar3 >> 0x18;
    iVar1 = br_lookup_mfd(&local_364,0,local_358,2);
LAB_000114c8:
    if (iVar1 == 0) {
      if (0 < local_358[0]) {
        puVar14 = auStack_328;
        iVar1 = 0;
        iVar2 = 0;
        do {
          ppuVar5 = local_378;
          iVar16 = iVar1;
          do {
            ppuVar6 = ppuVar5 + 1;
            pcVar11 = *ppuVar5;
            iVar1 = iVar16;
            if (((*pcVar11 != '\0') &&
                (iVar17 = local_358[2] + iVar2 * 0x78,
                *(int *)(pcVar11 + 0x14) == *(int *)(iVar17 + 0x10))) &&
               (0 < *(int *)(iVar17 + 0x14))) {
              puVar10 = (undefined4 *)(iVar17 + 0x18);
              puVar13 = puVar14;
              do {
                *(char **)(puVar13 + 8) = pcVar11;
                *(undefined4 *)(puVar13 + 0xc) = 1;
                iVar1 = iVar1 + 1;
                puVar14 = puVar13 + 0x18;
                *(undefined4 *)(puVar13 + 0x12) = *puVar10;
                *(undefined2 *)(puVar13 + 0x16) = *(undefined2 *)(puVar10 + 1);
                puVar10 = (undefined4 *)((int)puVar10 + 6);
                puVar13 = puVar14;
              } while (iVar1 - iVar16 < *(int *)(iVar17 + 0x14));
            }
            ppuVar5 = ppuVar6;
            iVar16 = iVar1;
          } while (ppuVar6 != local_378 + local_37c);
          iVar2 = iVar2 + 1;
        } while (iVar2 != local_358[0]);
        goto LAB_000110e8;
      }
    }
    else if (iVar1 == 1) goto LAB_0001139c;
  }
  else {
    if (param_2 == 0xff) {
      ppuVar4 = DAT_00011940;
      if ((param_1 != 0) && (ppuVar4 = DAT_0001193c, param_1 != 1)) goto LAB_0001120c;
      uVar8 = 5;
      iVar1 = param_1 * 0x108 + param_4 * 0x18;
      uVar3 = *(uint *)(&idm_flood_cnt + iVar1);
      uVar9 = *(uint *)(&DAT_00014960 + iVar1);
      *(uint *)(&idm_flood_cnt + iVar1) = uVar3 + 1;
      *(uint *)(&DAT_0001495c + iVar1) =
           *(int *)(&DAT_0001495c + iVar1) + (uint)(0xfffffffe < uVar3);
      uVar3 = *(uint *)(param_3 + 100);
      *(uint *)(&DAT_00014960 + iVar1) = uVar9 + uVar3;
      *(uint *)(&DAT_00014964 + iVar1) = *(int *)(&DAT_00014964 + iVar1) + (uint)CARRY4(uVar9,uVar3)
      ;
    }
    else {
      if (7 < param_2) goto LAB_0001120c;
      uVar8 = 1;
      local_368 = &fdb_list + (param_2 + param_1 * 8) * 0x128;
      ppuVar4 = &local_368;
    }
    iVar1 = __idm_fdb_create_items_constprop_0(ppuVar4,uVar8,auStack_328,&local_36c);
LAB_000110e8:
    if (0 < iVar1) {
      puVar13 = (undefined1 *)0x0;
      puVar14 = puVar13;
      do {
        if (puVar13 == (undefined1 *)0x0) {
          puVar15 = puVar14 + 1;
LAB_00011164:
          if (local_31c[(int)puVar14 * 6] < 2) {
            puVar13 = auStack_328 + (int)puVar14 * 0x18;
          }
          else {
            puVar13 = (undefined1 *)0x0;
          }
        }
        else {
          local_368 = *(undefined1 **)(puVar13 + 8);
          iVar16 = *(int *)(local_368 + 0x14);
          iVar2 = skb_copy(param_3,0x20);
          if (iVar2 != 0) {
            *(int *)(iVar2 + 0x18) = iVar16;
            uVar3 = ifd_debug;
            if (*(int *)(puVar13 + 0xc) == 1) {
              puVar10 = *(undefined4 **)(iVar2 + 0xcc);
              *puVar10 = *(undefined4 *)(puVar13 + 0x12);
              uVar3 = ifd_debug;
              uVar9 = ifd_debug & 2;
              *(undefined2 *)(puVar10 + 1) = *(undefined2 *)(puVar13 + 0x16);
              if (uVar9 != 0) {
                INC_MTRANS_CNT(local_368,puVar13 + 0x12,puVar10,iVar2);
                uVar3 = ifd_debug;
              }
            }
            if ((uVar3 & 1) == 0) {
              puVar15 = puVar14 + 1;
            }
            else {
              printk("%s:from idm:%d, ssid:%d, multi send to %s\n","idm_fdb_multi_send_handle",
                     local_368[1],param_2,iVar16);
              printk("skb->head:\t%p\nskb->data:\t%p\nskb->mac_head:\t%p\nskb->cloned:\t%d\nref:\t%d\n"
                     ,*(undefined4 *)(iVar2 + 200),*(undefined4 *)(iVar2 + 0xcc),
                     *(undefined2 *)(iVar2 + 0xaa),*(byte *)(iVar2 + 0x72) & 1,
                     *(undefined4 *)(*(int *)(iVar2 + 0xc4) + 0x20));
              if (*(int *)(iVar2 + 100) == 0) {
                puVar15 = (undefined1 *)0x1;
                puVar14 = (undefined1 *)0x0;
              }
              else {
                printk("%02x ",**(undefined1 **)(iVar2 + 0xcc));
                puVar15 = (undefined1 *)0x0;
                while (puVar14 = puVar15 + 1, puVar14 < *(undefined1 **)(iVar2 + 100)) {
                  printk("%02x ",puVar14[*(int *)(iVar2 + 0xcc)]);
                  uVar3 = (uint)puVar14 & 0x8000000f;
                  if ((int)uVar3 < 0) {
                    uVar3 = ~(~((uVar3 - 1) * 0x10000000) >> 0x1c) + 1;
                  }
                  puVar15 = puVar14;
                  if (uVar3 == 0xf) {
                    printk(&_LC1);
                  }
                }
                puVar15 = puVar15 + 2;
              }
              printk(&_LC1);
            }
            iVar16 = (**(code **)(*(int *)(iVar16 + 300) + 0x10))(iVar2,iVar16);
            if (iVar16 < 0) {
              uVar3 = *(uint *)(local_368 + 0xc0);
              uVar9 = *(uint *)(local_368 + 200);
              *(uint *)(local_368 + 0xc0) = uVar3 + 1;
              *(uint *)(local_368 + 0xc4) = *(int *)(local_368 + 0xc4) + (uint)(0xfffffffe < uVar3);
              uVar3 = *(uint *)(iVar2 + 100);
              *(uint *)(local_368 + 200) = uVar9 + uVar3;
              *(uint *)(local_368 + 0xcc) = *(int *)(local_368 + 0xcc) + (uint)CARRY4(uVar9,uVar3);
              __dev_kfree_skb_any(iVar2,1);
            }
            goto LAB_00011164;
          }
          puVar15 = puVar14 + 1;
        }
        puVar14 = puVar15;
      } while ((int)puVar15 < iVar1);
      if (puVar13 == (undefined1 *)0x0) {
        return 0;
      }
      local_368 = *(undefined1 **)(puVar13 + 8);
      iVar1 = *(int *)(local_368 + 0x14);
      *(int *)(param_3 + 0x18) = iVar1;
      uVar3 = ifd_debug;
      if (*(int *)(puVar13 + 0xc) == 1) {
        puVar10 = *(undefined4 **)(param_3 + 0xcc);
        *puVar10 = *(undefined4 *)(puVar13 + 0x12);
        uVar3 = ifd_debug;
        uVar9 = ifd_debug & 2;
        *(undefined2 *)(puVar10 + 1) = *(undefined2 *)(puVar13 + 0x16);
        if (uVar9 != 0) {
          INC_MTRANS_CNT(local_368,puVar13 + 0x12,puVar10,param_3);
          uVar3 = ifd_debug;
        }
      }
      if ((uVar3 & 1) != 0) {
        printk("%s:from idm:%d, ssid:%d, multi send to %s\n","idm_fdb_multi_send_handle",
               local_368[1],param_2,iVar1);
        printk("skb->head:\t%p\nskb->data:\t%p\nskb->mac_head:\t%p\nskb->cloned:\t%d\nref:\t%d\n",
               *(undefined4 *)(param_3 + 200),*(undefined4 *)(param_3 + 0xcc),
               *(undefined2 *)(param_3 + 0xaa),*(byte *)(param_3 + 0x72) & 1,
               *(undefined4 *)(*(int *)(param_3 + 0xc4) + 0x20));
        if (*(int *)(param_3 + 100) != 0) {
          uVar3 = 0;
          printk("%02x ",**(undefined1 **)(param_3 + 0xcc));
          while (uVar3 = uVar3 + 1, uVar3 < *(uint *)(param_3 + 100)) {
            printk("%02x ",*(undefined1 *)(*(int *)(param_3 + 0xcc) + uVar3));
            uVar9 = uVar3 & 0x8000000f;
            if ((int)uVar9 < 0) {
              uVar9 = ~(~((uVar9 - 1) * 0x10000000) >> 0x1c) + 1;
            }
            if (uVar9 == 0xf) {
              printk(&_LC1);
            }
          }
        }
        printk(&_LC1);
      }
      iVar1 = (**(code **)(*(int *)(iVar1 + 300) + 0x10))(param_3,iVar1);
      if (-1 < iVar1) {
        return 0;
      }
      uVar3 = *(uint *)(local_368 + 0xc0);
      uVar9 = *(uint *)(local_368 + 200);
      *(uint *)(local_368 + 0xc0) = uVar3 + 1;
      *(uint *)(local_368 + 0xc4) = *(int *)(local_368 + 0xc4) + (uint)(0xfffffffe < uVar3);
      uVar3 = *(uint *)(param_3 + 100);
      *(uint *)(local_368 + 200) = uVar9 + uVar3;
      *(uint *)(local_368 + 0xcc) = *(int *)(local_368 + 0xcc) + (uint)CARRY4(uVar9,uVar3);
      goto LAB_0001120c;
    }
  }
  if (param_2 == 0xff) {
    param_1 = param_1 * 0x108;
    uVar3 = *(uint *)(&DAT_00014a48 + param_1);
    uVar9 = *(uint *)(&DAT_00014a50 + param_1);
    *(uint *)(&DAT_00014a48 + param_1) = uVar3 + 1;
    *(uint *)(&DAT_00014a4c + param_1) =
         *(int *)(&DAT_00014a4c + param_1) + (uint)(0xfffffffe < uVar3);
    uVar3 = *(uint *)(param_3 + 100);
    *(uint *)(&DAT_00014a50 + param_1) = uVar9 + uVar3;
    *(uint *)(&DAT_00014a54 + param_1) =
         *(int *)(&DAT_00014a54 + param_1) + (uint)CARRY4(uVar9,uVar3);
  }
  else if (local_368 != (undefined1 *)0x0) {
    uVar3 = *(uint *)(local_368 + 0x108);
    uVar9 = *(uint *)(local_368 + 0x110);
    *(uint *)(local_368 + 0x108) = uVar3 + 1;
    *(uint *)(local_368 + 0x10c) = *(int *)(local_368 + 0x10c) + (uint)(0xfffffffe < uVar3);
    uVar3 = *(uint *)(param_3 + 100);
    *(uint *)(local_368 + 0x110) = uVar9 + uVar3;
    *(uint *)(local_368 + 0x114) = *(int *)(local_368 + 0x114) + (uint)CARRY4(uVar9,uVar3);
  }
LAB_0001120c:
  __dev_kfree_skb_any(param_3,1);
  return 0;
}


/* ============= FUNCTION: idm_multicast_init @ 00011944 ============= */

undefined4
idm_multicast_init(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  __memzero(&g_mtrans_dbg_cnt,0x2400,param_3,param_4,param_4);
  return 0;
}


/* ============= FUNCTION: idm_multicast_exit @ 00011960 ============= */

void idm_multicast_exit(void)

{
  return;
}


/* ============= FUNCTION: idm_proc_dbg_write @ 00011964 ============= */

undefined4 idm_proc_dbg_write(undefined4 param_1,int param_2,undefined4 param_3)

{
  byte *pbVar1;
  
  pbVar1 = (byte *)(param_2 + -1);
  ifd_debug = 0;
  while( true ) {
    pbVar1 = pbVar1 + 1;
    if (9 < *pbVar1 - 0x30) break;
    ifd_debug = (*pbVar1 - 0x30) + ifd_debug * 10;
  }
  return param_3;
}


/* ============= FUNCTION: idm_proc_stat_write @ 000119a0 ============= */

undefined4 idm_proc_stat_write(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  return param_3;
}


/* ============= FUNCTION: idm_proc_led_write @ 000119a8 ============= */

undefined4 idm_proc_led_write(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  return param_3;
}


/* ============= FUNCTION: idm_proc_idm_map_write @ 000119b0 ============= */

undefined4 idm_proc_idm_map_write(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  return param_3;
}


/* ============= FUNCTION: idm_proc_flood_status_write @ 000119b8 ============= */

undefined4 idm_proc_flood_status_write(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  return param_3;
}


/* ============= FUNCTION: idm_proc_multicast_write @ 000119c0 ============= */

undefined4 idm_proc_multicast_write(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  return param_3;
}


/* ============= FUNCTION: idm_proc_stat_open @ 000119c8 ============= */

void idm_proc_stat_open(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = PDE_DATA();
  single_open(param_2,idm_proc_stat_seq_show,uVar1);
  return;
}


/* ============= FUNCTION: idm_proc_forbidIdm_open @ 000119ec ============= */

void idm_proc_forbidIdm_open(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = PDE_DATA();
  single_open(param_2,idm_proc_forbidIdm_seq_show,uVar1);
  return;
}


/* ============= FUNCTION: idm_proc_led_open @ 00011a10 ============= */

void idm_proc_led_open(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = PDE_DATA();
  single_open(param_2,idm_proc_led_seq_show,uVar1);
  return;
}


/* ============= FUNCTION: idm_proc_dbg_open @ 00011a34 ============= */

void idm_proc_dbg_open(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = PDE_DATA();
  single_open(param_2,idm_proc_dbg_seq_show,uVar1);
  return;
}


/* ============= FUNCTION: idm_proc_idm_map_open @ 00011a58 ============= */

void idm_proc_idm_map_open(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = PDE_DATA();
  single_open(param_2,idm_proc_idm_map_seq_show,uVar1);
  return;
}


/* ============= FUNCTION: idm_proc_flood_status_open @ 00011a7c ============= */

void idm_proc_flood_status_open(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = PDE_DATA();
  single_open(param_2,idm_proc_flood_status_seq_show,uVar1);
  return;
}


/* ============= FUNCTION: idm_proc_multicast_open @ 00011aa0 ============= */

void idm_proc_multicast_open(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = PDE_DATA();
  single_open(param_2,idm_proc_multicast_seq_show,uVar1);
  return;
}


/* ============= FUNCTION: idm_proc_forbidIdm_seq_show @ 00011ac4 ============= */

undefined4
idm_proc_forbidIdm_seq_show(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  seq_printf(param_1,&_LC0,*(undefined4 *)(*(int *)(param_1 + 0x50) + 8),*(int *)(param_1 + 0x50),
             param_4);
  return 0;
}


/* ============= FUNCTION: idm_proc_dbg_seq_show @ 00011ae4 ============= */

undefined4 idm_proc_dbg_seq_show(undefined4 param_1)

{
  seq_printf(param_1,&_LC0,ifd_debug);
  seq_printf(param_1,
             "#define IFD_DBG_PKT (1 << 0)\n#define IFD_DBG_MUL (1 << 1)\n#define IFD_DBG_LED (1 << 2)\n#define IFD_DBG_TX  (1 << 3)\n#define IFD_DBG_RX  (1 << 4)\n"
            );
  return 0;
}


/* ============= FUNCTION: idm_proc_stat_seq_show @ 00011b1c ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 idm_proc_stat_seq_show(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_1 + 0x50);
  iVar1 = kmem_cache_alloc(_DAT_000180cc,0x80d0);
  if (iVar1 != 0) {
    print_idm_node_stat(uVar2,iVar1,0xfff);
    seq_printf(param_1,iVar1);
    kfree(iVar1);
  }
  return 0;
}


/* ============= FUNCTION: idm_proc_forbidIdm_write @ 00011b70 ============= */

uint idm_proc_forbidIdm_write(int param_1,uint param_2,uint param_3)

{
  int iVar1;
  byte *pbVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  byte local_20 [8];
  
  local_20[0] = 0;
  local_20[1] = 0;
  local_20[2] = 0;
  local_20[3] = 0;
  local_20[4] = 0;
  local_20[5] = 0;
  local_20[6] = 0;
  local_20[7] = 0;
  iVar1 = PDE_DATA(*(undefined4 *)(param_1 + 0x10));
  uVar6 = *(uint *)(((uint)local_20 & 0xffffe000) + 8);
  if (param_3 < 8) {
    uVar3 = param_2 + param_3;
    uVar4 = uVar3;
    if (!CARRY4(param_2,param_3)) {
      uVar4 = uVar3 - (uVar6 + 1);
    }
    if (!CARRY4(param_2,param_3) && uVar3 <= uVar6) {
      uVar6 = 0;
    }
    if (uVar6 != 0) {
      if (param_3 != 0) {
        __memzero(local_20,param_3,uVar4);
      }
      goto LAB_00011c04;
    }
  }
  else {
    uVar3 = param_2 + 7;
    uVar4 = uVar3;
    if (param_2 < 0xfffffff9) {
      uVar4 = uVar3 - (uVar6 + 1);
    }
    if (param_2 < 0xfffffff9 && uVar3 <= uVar6) {
      uVar6 = 0;
    }
    param_3 = 7;
    if (uVar6 != 0) {
      __memzero(local_20,7,uVar4);
      goto LAB_00011c04;
    }
  }
  __copy_from_user(local_20,param_2,param_3);
LAB_00011c04:
  iVar5 = 0;
  pbVar2 = local_20;
  while( true ) {
    if (9 < *pbVar2 - 0x30) break;
    iVar5 = (*pbVar2 - 0x30) + iVar5 * 10;
    pbVar2 = pbVar2 + 1;
  }
  *(int *)(iVar1 + 8) = iVar5;
  return param_3;
}


/* ============= FUNCTION: idm_proc_led_seq_show @ 00011c6c ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 idm_proc_led_seq_show(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_1 + 0x50);
  iVar1 = kmem_cache_alloc(_DAT_000180cc,0x80d0);
  if (iVar1 != 0) {
    print_idm_led_stat(uVar2,iVar1,0xfff);
    seq_printf(param_1,iVar1);
    kfree(iVar1);
  }
  return 0;
}


/* ============= FUNCTION: idm_proc_idm_map_seq_show @ 00011cc0 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 idm_proc_idm_map_seq_show(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_1 + 0x50);
  iVar1 = kmem_cache_alloc(_DAT_000180cc,0x80d0);
  if (iVar1 != 0) {
    print_idm_map(uVar2,iVar1,0xfff);
    seq_printf(param_1,iVar1);
    kfree(iVar1);
  }
  return 0;
}


/* ============= FUNCTION: idm_proc_flood_status_seq_show @ 00011d14 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 idm_proc_flood_status_seq_show(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_1 + 0x50);
  iVar1 = kmem_cache_alloc(_DAT_000180cc,0x80d0);
  if (iVar1 != 0) {
    print_idm_flood_status(uVar2,iVar1,0xfff);
    seq_printf(param_1,iVar1);
    kfree(iVar1);
  }
  return 0;
}


/* ============= FUNCTION: idm_proc_multicast_seq_show @ 00011d68 ============= */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 idm_proc_multicast_seq_show(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_1 + 0x50);
  iVar1 = kmem_cache_alloc(_DAT_000180cc,0x80d0);
  if (iVar1 != 0) {
    print_idm_multicast_cnt(uVar2,iVar1,0xfff);
    seq_printf(param_1,iVar1);
    kfree(iVar1);
  }
  return 0;
}


/* ============= FUNCTION: create_idm_proc_file @ 00011dbc ============= */

undefined4 create_idm_proc_file(int param_1)

{
  int iVar1;
  char *__src;
  char local_20 [16];
  
  __src = *(char **)(param_1 + 0x14);
  local_20[0] = '\0';
  local_20[1] = '\0';
  local_20[2] = '\0';
  local_20[3] = '\0';
  local_20[4] = '\0';
  local_20[5] = '\0';
  local_20[6] = '\0';
  local_20[7] = '\0';
  local_20[8] = '\0';
  local_20[9] = '\0';
  local_20[10] = '\0';
  local_20[0xb] = '\0';
  local_20[0xc] = '\0';
  local_20[0xd] = '\0';
  local_20[0xe] = '\0';
  local_20[0xf] = '\0';
  if ((__src == (char *)0x0) || (*__src == '\0')) {
    snprintf(local_20,0xf,"idm%d_ssid%d",(uint)*(byte *)(param_1 + 1),(uint)*(byte *)(param_1 + 3));
  }
  else {
    strncpy(local_20,__src,0xf);
  }
  remove_proc_subtree(local_20,proc_parent);
  iVar1 = proc_mkdir(local_20,proc_parent);
  *(int *)(param_1 + 0x120) = iVar1;
  if (iVar1 != 0) {
    proc_create_data(&_LC3,0x1b6,iVar1,&idm_proc_stat_file_ops,param_1);
    proc_create_data("forbidIdm",0x1b6,*(undefined4 *)(param_1 + 0x120),DAT_00011ea0,param_1);
  }
  return 0;
}


/* ============= FUNCTION: create_led_proc_file @ 00011ea4 ============= */

undefined4 create_led_proc_file(undefined4 *param_1)

{
  char local_20 [20];
  
  local_20[0] = '\0';
  local_20[1] = '\0';
  local_20[2] = '\0';
  local_20[3] = '\0';
  local_20[4] = '\0';
  local_20[5] = '\0';
  local_20[6] = '\0';
  local_20[7] = '\0';
  local_20[8] = '\0';
  local_20[9] = '\0';
  local_20[10] = '\0';
  local_20[0xb] = '\0';
  local_20[0xc] = '\0';
  local_20[0xd] = '\0';
  local_20[0xe] = '\0';
  local_20[0xf] = '\0';
  snprintf(local_20,0xf,"led%d",*param_1);
  proc_create_data(local_20,0x1b6,proc_parent,DAT_00011f08,param_1);
  return 0;
}


/* ============= FUNCTION: idm_proc_init @ 00011f0c ============= */

undefined4 idm_proc_init(void)

{
  proc_parent = proc_mkdir("idm_fdb",0);
  proc_dbg = proc_create_data("debug",0x1b6,proc_parent,idm_proc_dbg_file_ops,0);
  proc_create_data("idm_map",0x1b6,proc_parent,idm_proc_idm_map_file_ops,0);
  proc_create_data("flood_status",0x1b6,proc_parent,idm_proc_flood_status_file_ops,0);
  proc_create_data("multicast",0x1b6,proc_parent,idm_proc_multicast_file_ops,0);
  return 0;
}


/* ============= FUNCTION: idm_proc_exit @ 00011fc0 ============= */

void idm_proc_exit(void)

{
  proc_remove(proc_parent);
  return;
}


/* ============= FUNCTION: idm_led_timer_handle @ 00011fd0 ============= */

void idm_led_timer_handle(undefined4 *param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 local_3c [4];
  undefined4 local_2c;
  
  local_3c[0] = _LANCHOR1;
  local_3c[1] = DAT_00012868;
  local_3c[2] = DAT_0001286c;
  local_3c[3] = DAT_00012870;
  local_2c = DAT_00012874;
  if ((param_1 == (undefined4 *)0x0) || (*(char *)(param_1 + 1) == '\0')) {
    printk("idm led does not work\n");
    return;
  }
  iVar3 = param_1[3];
  if (iVar3 < 1) {
    iVar3 = jiffies - param_1[0xe];
    param_1[0xe] = jiffies;
    jiffies_to_msecs(iVar3);
    iVar3 = param_1[0xd];
  }
  else {
    iVar6 = 0;
    iVar7 = 0;
    iVar5 = 0;
    do {
      while (*(int *)(param_1[2] + iVar5 * 4) < 0) {
LAB_00012208:
        iVar5 = iVar5 + 1;
        if (iVar3 <= iVar5) goto LAB_00012130;
      }
      uVar2 = get_node_index();
      if ((((0x10 < uVar2) || (iVar3 = uVar2 * 0x128, iVar3 == -0x13408)) ||
          ((&fdb_list)[uVar2 * 0x128] == '\0')) ||
         ((iVar4 = (&DAT_0001341c)[uVar2 * 0x4a], iVar4 == 0 || ((*(uint *)(iVar4 + 0x30) & 1) == 0)
          ))) {
        iVar3 = param_1[3];
        goto LAB_00012208;
      }
      iVar7 = iVar7 + 1;
      uVar2 = *(int *)(&DAT_00013440 + iVar3) - *(int *)(&DAT_00013448 + iVar3);
      iVar8 = *(int *)(&DAT_00013428 + iVar3) - *(int *)(&DAT_00013430 + iVar3);
      uVar2 = uVar2 & ~((int)uVar2 >> 0x1f);
      if (-1 < iVar8) {
        uVar2 = uVar2 + iVar8;
      }
      *(int *)(&DAT_00013448 + iVar3) = *(int *)(&DAT_00013440 + iVar3);
      uVar1 = ifd_debug;
      iVar8 = *(int *)(&DAT_00013458 + iVar3) - *(int *)(&DAT_00013460 + iVar3);
      if (-1 < iVar8) {
        uVar2 = uVar2 + iVar8;
      }
      iVar8 = *(int *)(&DAT_000134b8 + iVar3) - *(int *)(&DAT_000134c0 + iVar3);
      *(int *)(&DAT_00013430 + iVar3) = *(int *)(&DAT_00013428 + iVar3);
      if (-1 < iVar8) {
        uVar2 = uVar2 + iVar8;
      }
      *(int *)(&DAT_000134c0 + iVar3) = *(int *)(&DAT_000134b8 + iVar3);
      *(int *)(&DAT_00013460 + iVar3) = *(int *)(&DAT_00013458 + iVar3);
      *(undefined4 *)(&DAT_00013434 + iVar3) = *(undefined4 *)(&DAT_0001342c + iVar3);
      *(undefined4 *)(&DAT_0001344c + iVar3) = *(undefined4 *)(&DAT_00013444 + iVar3);
      *(undefined4 *)(&DAT_00013464 + iVar3) = *(undefined4 *)(&DAT_0001345c + iVar3);
      *(undefined4 *)(&DAT_000134c4 + iVar3) = *(undefined4 *)(&DAT_000134bc + iVar3);
      if ((uVar1 & 4) != 0) {
        printk("led%d dev %s tp_total %d\n",*param_1,iVar4,uVar2);
      }
      iVar3 = param_1[3];
      iVar5 = iVar5 + 1;
      iVar6 = iVar6 + uVar2;
    } while (iVar5 < iVar3);
LAB_00012130:
    iVar3 = jiffies - param_1[0xe];
    param_1[0xe] = jiffies;
    iVar5 = jiffies_to_msecs(iVar3);
    iVar3 = param_1[0xd];
    if (iVar7 != 0) {
      if (iVar5 == 0) {
        iVar5 = 1;
      }
      iVar5 = __aeabi_uidiv(iVar6 << 3,iVar5);
      param_1[4] = iVar7;
      param_1[5] = iVar5;
      if (iVar5 < 1) {
        iVar6 = 1;
        param_1[0xd] = 1;
      }
      else {
        if (iVar5 < 0x2800) {
          iVar6 = 2;
        }
        else {
          iVar6 = 3;
        }
        param_1[0xd] = iVar6;
      }
      goto LAB_00012198;
    }
  }
  iVar6 = 0;
  param_1[0xd] = 0;
  iVar5 = 0;
  iVar7 = iVar6;
LAB_00012198:
  if ((iVar6 != iVar3) && ((code *)param_1[0xf] != (code *)0x0)) {
    if (idm_ps_mode == 0 || iVar6 != 0) {
      (*(code *)param_1[0xf])(local_3c[iVar6]);
    }
    else {
      printk("idm_ps_mode = %d status %d,avoid closing led\n",idm_ps_mode,0);
    }
  }
  if ((ifd_debug & 4) != 0) {
    printk("led%d ap_cnt %d tp %dkbps status %d\n",*param_1,iVar7,iVar5,param_1[0xd]);
  }
  mod_timer(param_1 + 6,jiffies + 100);
  return;
}


/* ============= FUNCTION: print_idm_led_stat @ 000122b8 ============= */

int print_idm_led_stat(int *param_1,char *param_2,size_t param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 auStack_30 [5];
  
  auStack_30[3] = DAT_000124a0[3];
  auStack_30[2] = DAT_000124a0[2];
  auStack_30[1] = DAT_000124a0[1];
  auStack_30[0] = *DAT_000124a0;
  if ((int)param_3 < 1) {
    iVar1 = 0;
LAB_00012384:
    iVar7 = param_1[3];
    if (iVar7 < 1) goto LAB_00012404;
  }
  else {
    iVar7 = param_1[5];
    uVar6 = auStack_30[param_1[0xd] & 3];
    iVar1 = snprintf(param_2,param_3,"led %d, en %d, stat %s, total thoughput %dkbps\n",*param_1,
                     (uint)*(byte *)(param_1 + 1),uVar6,iVar7);
    if ((int)param_3 <= iVar1) goto LAB_00012384;
    uVar4 = wifi_led_func_name;
    if (*param_1 != 0) {
      uVar4 = wifi_led2_func_name;
    }
    iVar7 = snprintf(param_2 + iVar1,param_3 - iVar1,"   hw_call: %s  = %p\n",uVar4,param_1[0xf],
                     uVar6,iVar7);
    iVar1 = iVar1 + iVar7;
    if (iVar1 < (int)param_3) {
      iVar7 = snprintf(param_2 + iVar1,param_3 - iVar1,"   bind devs:");
      iVar1 = iVar1 + iVar7;
      goto LAB_00012384;
    }
    iVar7 = param_1[3];
    if (iVar7 < 1) {
      return iVar1;
    }
  }
  iVar5 = 0;
  do {
    if (-1 < *(int *)(param_1[2] + iVar5 * 4)) {
      uVar2 = get_node_index();
      if (((uVar2 < 0x11) && ((&fdb_list)[uVar2 * 0x128] != '\0')) &&
         ((&DAT_0001341c)[uVar2 * 0x4a] != 0)) {
        if (iVar1 < (int)param_3) {
          uVar2 = *(uint *)((&DAT_0001341c)[uVar2 * 0x4a] + 0x30) & 1;
        }
        else {
          uVar2 = 0;
        }
        if (uVar2 != 0) {
          iVar3 = snprintf(param_2 + iVar1,param_3 - iVar1," %s");
          iVar7 = param_1[3];
          iVar1 = iVar1 + iVar3;
          goto LAB_000123f8;
        }
      }
      iVar7 = param_1[3];
    }
LAB_000123f8:
    iVar5 = iVar5 + 1;
  } while (iVar5 < iVar7);
LAB_00012404:
  if (iVar1 < (int)param_3) {
    iVar7 = snprintf(param_2 + iVar1,param_3 - iVar1,"\n idm_ps_mode: %d",idm_ps_mode);
    iVar1 = iVar1 + iVar7;
    if (iVar1 < (int)param_3) {
      iVar7 = snprintf(param_2 + iVar1,param_3 - iVar1,"\n");
      return iVar1 + iVar7;
    }
  }
  return iVar1;
}


/* ============= FUNCTION: print_idm_led @ 000124a4 ============= */

void print_idm_led(void)

{
  char cVar1;
  undefined1 *puVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar5 = 0;
  puVar2 = &led_handle;
  cVar1 = DAT_00017e74;
  while( true ) {
    if (cVar1 != '\0') {
      printk("led %d, en %d, stat %d, total thoughput %dkbps\n",iVar5,1,
             *(undefined4 *)(puVar2 + 0x34),*(undefined4 *)(puVar2 + 0x14));
      printk("   bind devs:");
      iVar4 = *(int *)(puVar2 + 0xc);
      if (0 < iVar4) {
        iVar6 = 0;
        do {
          if (-1 < *(int *)(*(int *)(puVar2 + 8) + iVar5 * 4)) {
            uVar3 = get_node_index();
            if ((((uVar3 < 0x11) && ((&fdb_list)[uVar3 * 0x128] != '\0')) &&
                ((&DAT_0001341c)[uVar3 * 0x4a] != 0)) &&
               ((*(uint *)((&DAT_0001341c)[uVar3 * 0x4a] + 0x30) & 1) != 0)) {
              printk(&_LC14);
            }
            iVar4 = *(int *)(puVar2 + 0xc);
          }
          iVar6 = iVar6 + 1;
        } while (iVar6 < iVar4);
      }
      printk(&_LC16);
    }
    if (iVar5 == 1) break;
    cVar1 = puVar2[0x44];
    iVar5 = 1;
    puVar2 = puVar2 + 0x40;
  }
  return;
}


/* ============= FUNCTION: idm_led_exit @ 000125ac ============= */

void idm_led_exit(void)

{
  if (DAT_00017e74 != '\0') {
    DAT_00017e74 = '\0';
    del_timer_sync(&DAT_00017e88);
  }
  if (DAT_00017eb4 == '\0') {
    return;
  }
  DAT_00017eb4 = 0;
  del_timer_sync(&DAT_00017ec8);
  return;
}


/* ============= FUNCTION: init_module @ 00012600 ============= */

undefined4 init_module(void)

{
  idm_fdb_init();
  idm_proc_init();
  idm_multicast_init();
  idm_led_init();
  return 0;
}


/* ============= FUNCTION: idm_fdb_init @ 0001261c ============= */

undefined4 idm_fdb_init(void)

{
  undefined4 in_r3;
  
  idm_skb_recv = idm_fdb_forward;
  __memzero(&idm_flood_cnt,0x210,idm_fdb_forward,&idm_skb_recv,in_r3);
  register_netdevice_notifier(&idm_netdev_notifier);
  return 0;
}


/* ============= FUNCTION: idm_led_init @ 00012658 ============= */

undefined4 idm_led_init(void)

{
  int iVar1;
  int iVar2;
  
  __memzero(&led_handle,0x80);
  iVar1 = kallsyms_lookup_name(wifi_led_func_name);
  iVar2 = kallsyms_lookup_name(wifi_led2_func_name);
  if (iVar2 == 0 || iVar1 == 0) {
    if (iVar1 != 0) {
      register_idm_led(0,wlan_array_group_all,10,iVar1);
    }
  }
  else {
    register_idm_led(0,wlan_array_group_band0,5,iVar1);
    register_idm_led(1,wlan_array_group_band1,5,iVar2);
  }
  return 0;
}


/* ============= FUNCTION: cleanup_module @ 000126f8 ============= */

void cleanup_module(void)

{
  idm_fdb_exit();
  idm_proc_exit();
  idm_multicast_exit();
  idm_led_exit();
  return;
}


/* ============= FUNCTION: register_idm_led @ 00012710 ============= */

undefined4 register_idm_led(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_1 * 0x40;
  *(int *)(&led_handle + param_1 * 0x40) = param_1;
  *(undefined4 *)(&DAT_00017e78 + iVar1) = param_2;
  (&DAT_00017e74)[iVar1] = 1;
  *(undefined4 *)(&DAT_00017e7c + iVar1) = param_3;
  *(undefined4 *)(&DAT_00017eac + iVar1) = param_4;
  (&DAT_00017ea4)[param_1 * 0x10] = 0;
  init_timer_key(&DAT_00017e88 + iVar1,0,0,0);
  iVar2 = jiffies;
  *(code **)(&DAT_00017e98 + iVar1) = idm_led_timer_handle;
  *(undefined1 **)(&DAT_00017e9c + iVar1) = &led_handle + iVar1;
  mod_timer(&DAT_00017e88 + iVar1,iVar2 + 500);
  create_led_proc_file(&led_handle + iVar1);
  return 0;
}


/* ============= FUNCTION: ffe_get_npu_enable @ 00018000 ============= */

/* WARNING: Control flow encountered bad instruction data */

void ffe_get_npu_enable(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: snprintf @ 00018004 ============= */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int snprintf(char *__s,size_t __maxlen,char *__format,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: kfree @ 0001800c ============= */

/* WARNING: Control flow encountered bad instruction data */

void kfree(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: proc_create_data @ 00018014 ============= */

/* WARNING: Control flow encountered bad instruction data */

void proc_create_data(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: remove_proc_subtree @ 00018018 ============= */

/* WARNING: Control flow encountered bad instruction data */

void remove_proc_subtree(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __dev_get_by_name @ 0001801c ============= */

/* WARNING: Control flow encountered bad instruction data */

void __dev_get_by_name(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: kmem_cache_alloc @ 00018020 ============= */

/* WARNING: Control flow encountered bad instruction data */

void kmem_cache_alloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: kallsyms_lookup_name @ 00018028 ============= */

/* WARNING: Control flow encountered bad instruction data */

void kallsyms_lookup_name(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: sw_set_idm_isolate @ 0001802c ============= */

/* WARNING: Control flow encountered bad instruction data */

void sw_set_idm_isolate(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: mod_timer @ 00018030 ============= */

/* WARNING: Control flow encountered bad instruction data */

void mod_timer(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: strncpy @ 00018038 ============= */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * strncpy(char *__dest,char *__src,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: printk @ 0001803c ============= */

/* WARNING: Control flow encountered bad instruction data */

void printk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: jiffies_to_msecs @ 00018040 ============= */

/* WARNING: Control flow encountered bad instruction data */

void jiffies_to_msecs(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: proc_mkdir @ 00018044 ============= */

/* WARNING: Control flow encountered bad instruction data */

void proc_mkdir(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: br_lookup_mfd @ 00018048 ============= */

/* WARNING: Control flow encountered bad instruction data */

void br_lookup_mfd(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: del_timer_sync @ 0001804c ============= */

/* WARNING: Control flow encountered bad instruction data */

void del_timer_sync(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __memzero @ 00018050 ============= */

/* WARNING: Control flow encountered bad instruction data */

void __memzero(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __aeabi_uidiv @ 00018058 ============= */

/* WARNING: Control flow encountered bad instruction data */

void __aeabi_uidiv(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: PDE_DATA @ 0001805c ============= */

/* WARNING: Control flow encountered bad instruction data */

void PDE_DATA(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: proc_remove @ 00018060 ============= */

/* WARNING: Control flow encountered bad instruction data */

void proc_remove(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: init_timer_key @ 0001806c ============= */

/* WARNING: Control flow encountered bad instruction data */

void init_timer_key(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __dev_kfree_skb_any @ 00018070 ============= */

/* WARNING: Control flow encountered bad instruction data */

void __dev_kfree_skb_any(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: WlanIndex2WlanIdmMap @ 00018074 ============= */

/* WARNING: Control flow encountered bad instruction data */

void WlanIndex2WlanIdmMap(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: ffe_learn_skb @ 00018078 ============= */

/* WARNING: Control flow encountered bad instruction data */

void ffe_learn_skb(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: register_netdevice_notifier @ 0001807c ============= */

/* WARNING: Control flow encountered bad instruction data */

void register_netdevice_notifier(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: seq_printf @ 00018080 ============= */

/* WARNING: Control flow encountered bad instruction data */

void seq_printf(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: skb_copy @ 00018084 ============= */

/* WARNING: Control flow encountered bad instruction data */

void skb_copy(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: IfName2WlanIdmMap @ 00018090 ============= */

/* WARNING: Control flow encountered bad instruction data */

void IfName2WlanIdmMap(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: single_open @ 00018094 ============= */

/* WARNING: Control flow encountered bad instruction data */

void single_open(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __copy_from_user @ 00018098 ============= */

/* WARNING: Control flow encountered bad instruction data */

void __copy_from_user(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


