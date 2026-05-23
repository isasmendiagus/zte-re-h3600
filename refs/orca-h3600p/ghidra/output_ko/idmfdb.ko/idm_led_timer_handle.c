// module: idmfdb.ko
// function: idm_led_timer_handle @ 0x12118
// size: 740 bytes
//

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
  undefined4 local_3c [6];
  
  local_3c[0] = 0;
  local_3c[1] = 1;
  local_3c[2] = 3;
  local_3c[3] = 2;
  local_3c[4] = 4;
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
LAB_00012250:
        iVar5 = iVar5 + 1;
        if (iVar3 <= iVar5) goto LAB_00012288;
      }
      uVar2 = get_node_index();
      if ((((uVar2 < 0x11) && (iVar3 = uVar2 * 0x128, (&fdb_list)[uVar2 * 0x128] != '\0')) &&
          (iVar4 = (&DAT_000135bc)[uVar2 * 0x4a], iVar4 != 0)) &&
         ((*(uint *)(iVar4 + 0x30) & 1) != 0)) {
        iVar7 = iVar7 + 1;
        uVar2 = *(int *)(&DAT_000135e0 + iVar3) - *(int *)(&DAT_000135e8 + iVar3);
        iVar8 = *(int *)(&DAT_000135c8 + iVar3) - *(int *)(&DAT_000135d0 + iVar3);
        uVar2 = uVar2 & ~((int)uVar2 >> 0x1f);
        if (-1 < iVar8) {
          uVar2 = uVar2 + iVar8;
        }
        *(int *)(&DAT_000135e8 + iVar3) = *(int *)(&DAT_000135e0 + iVar3);
        uVar1 = ifd_debug;
        iVar8 = *(int *)(&DAT_000135f8 + iVar3) - *(int *)(&DAT_00013600 + iVar3);
        if (-1 < iVar8) {
          uVar2 = uVar2 + iVar8;
        }
        iVar8 = *(int *)(&DAT_00013658 + iVar3) - *(int *)(&DAT_00013660 + iVar3);
        *(int *)(&DAT_000135d0 + iVar3) = *(int *)(&DAT_000135c8 + iVar3);
        if (-1 < iVar8) {
          uVar2 = uVar2 + iVar8;
        }
        *(int *)(&DAT_00013660 + iVar3) = *(int *)(&DAT_00013658 + iVar3);
        *(int *)(&DAT_00013600 + iVar3) = *(int *)(&DAT_000135f8 + iVar3);
        *(undefined4 *)(&DAT_000135d4 + iVar3) = *(undefined4 *)(&DAT_000135cc + iVar3);
        *(undefined4 *)(&DAT_000135ec + iVar3) = *(undefined4 *)(&DAT_000135e4 + iVar3);
        *(undefined4 *)(&DAT_00013604 + iVar3) = *(undefined4 *)(&DAT_000135fc + iVar3);
        *(undefined4 *)(&DAT_00013664 + iVar3) = *(undefined4 *)(&DAT_0001365c + iVar3);
        if ((uVar1 & 4) != 0) {
          printk("led%d dev %s tp_total %d\n",*param_1,iVar4,uVar2);
        }
        iVar3 = param_1[3];
        iVar6 = iVar6 + uVar2;
        goto LAB_00012250;
      }
      iVar3 = param_1[3];
      iVar5 = iVar5 + 1;
    } while (iVar5 < iVar3);
LAB_00012288:
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
      goto LAB_000122f0;
    }
  }
  iVar6 = 0;
  param_1[0xd] = 0;
  iVar5 = 0;
  iVar7 = iVar6;
LAB_000122f0:
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

