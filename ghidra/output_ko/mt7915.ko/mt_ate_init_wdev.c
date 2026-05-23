// module: mt7915.ko
// function: mt_ate_init_wdev @ 0x282b08
// size: 1440 bytes
//

int mt_ate_init_wdev(int param_1,int param_2)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined2 uVar5;
  uint *puVar6;
  uint *puVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  undefined4 *local_30;
  
  iVar3 = net_ad_wrap_service();
  iVar8 = param_2 * 0xd18;
  bVar1 = *(byte *)(iVar3 + iVar8 + 0x1130);
  iVar3 = net_ad_wrap_service(param_1);
  iVar3 = *(int *)(iVar3 + iVar8 + 0x504);
  if (iVar3 != 0) {
    iVar9 = param_1 + param_2 * 4;
    iVar4 = wdev_init(param_1,iVar3,0x4000,**(undefined4 **)(iVar9 + 0xc),(int)(char)param_2,0,
                      param_1);
    if (iVar4 == 0) {
joined_r0x00282dc0:
      if (DebugLevel < 0) goto LAB_00282b90;
      printk("Assign wdev idx for ATE failed, free net device!\n");
    }
    else {
      iVar4 = net_ad_wrap_service(param_1);
      *(undefined1 *)(iVar4 + iVar8 + 0x50c) = *(undefined1 *)(iVar3 + 0xc);
      if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x6867 ||
          (*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
        ate_wdev_ops._48_4_ = mt_ate_tx_v2;
        ate_wdev_ops._176_4_ = ate_conn_act;
        ate_wdev_ops._180_4_ = wifi_sys_disconn_act;
      }
      wdev_ops_register(iVar3,0x4000,ate_wdev_ops,0);
      if (0 < DebugLevel) {
        printk("%s: wdev_idx=%d, channel=%d\n","mt_ate_init_wdev",*(undefined1 *)(iVar3 + 0xc),bVar1
              );
      }
      *(byte *)(iVar3 + 0x1a) = bVar1;
      cVar2 = (char)(param_2 << 1);
      *(undefined1 *)(iVar3 + 0x8d4) = 1;
      *(char *)(iVar3 + 0x8d7) = cVar2;
      if (bVar1 < 0xf) {
        uVar5 = 0x4e;
      }
      else {
        uVar5 = 0xb1;
      }
      *(undefined2 *)(iVar3 + 0x18) = uVar5;
      if (*(char *)(param_1 + 0x286285) == '\x01') {
        iVar8 = net_ad_wrap_service(param_1);
        if (*(char *)(param_1 + 0x286285) == '\0') goto LAB_00282cb4;
        puVar10 = (undefined4 *)(param_2 * 0xd18 + iVar8 + 0x5f1);
LAB_00282cd4:
        if (puVar10 != (undefined4 *)0x0) {
          *(undefined4 *)(iVar3 + 0x1b) = *puVar10;
          *(undefined2 *)(iVar3 + 0x1f) = *(undefined2 *)(puVar10 + 1);
          iVar8 = wdev_do_open(iVar3);
          if (iVar8 != 0) {
            if (*(char *)(param_1 + 0x286285) == '\x01') {
              iVar8 = net_ad_wrap_service(param_1);
              if (*(char *)(param_1 + 0x286285) == '\0') goto LAB_00282d18;
              local_30 = (undefined4 *)(param_2 * 0xd18 + iVar8 + 0x591);
            }
            else {
              if (*(char *)(param_1 + 0x286285) != '\0') goto LAB_00282c5c;
LAB_00282d18:
              iVar8 = net_ad_wrap_service(param_1);
              local_30 = (undefined4 *)(param_2 * 0xd18 + iVar8 + 0x531);
            }
            if (local_30 != (undefined4 *)0x0) {
              *(undefined4 *)(iVar3 + 0x21) = *local_30;
              *(undefined2 *)(iVar3 + 0x25) = *(undefined2 *)(local_30 + 1);
              wifi_sys_linkup(iVar3,0);
              iVar3 = net_ad_wrap_service(param_1);
              iVar3 = *(int *)(iVar3 + param_2 * 0xd18 + 0x508);
              iVar8 = wdev_init(param_1,iVar3,0x2000,**(undefined4 **)(iVar9 + 0xc),
                                (int)(char)param_2,0,param_1);
              if (iVar8 == 0) goto joined_r0x00282dc0;
              iVar8 = net_ad_wrap_service(param_1);
              *(undefined1 *)(iVar8 + param_2 * 0xd18 + 0x50c) = *(undefined1 *)(iVar3 + 0xc);
              if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x6867 ||
                  (*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
                ate_wdev_ops._48_4_ = mt_ate_tx_v2;
                ate_wdev_ops._176_4_ = ate_conn_act;
                ate_wdev_ops._180_4_ = wifi_sys_disconn_act;
              }
              wdev_ops_register(iVar3,0x2000,ate_wdev_ops,0);
              if (0 < DebugLevel) {
                printk("%s: wdev_idx=%d, channel=%d\n","mt_ate_init_wdev",
                       *(undefined1 *)(iVar3 + 0xc),bVar1);
              }
              if (iVar3 != 0) {
                *(byte *)(iVar3 + 0x1a) = bVar1;
                *(char *)(iVar3 + 0x8d7) = cVar2 + '\x01';
                *(undefined1 *)(iVar3 + 0x8d4) = 1;
                if (bVar1 < 0xf) {
                  uVar5 = 0x4e;
                }
                else {
                  uVar5 = 0xb1;
                }
                *(undefined2 *)(iVar3 + 0x18) = uVar5;
                cVar2 = *(char *)(param_1 + 0x286285);
                if (cVar2 == '\x01') {
                  iVar8 = net_ad_wrap_service(param_1);
                  cVar2 = *(char *)(param_1 + 0x286285);
                  puVar10 = (undefined4 *)(param_2 * 0xd18 + iVar8 + 0x5f1);
                }
                if (cVar2 == '\0') {
                  iVar8 = net_ad_wrap_service(param_1);
                  puVar10 = (undefined4 *)(param_2 * 0xd18 + iVar8 + 0x591);
                }
                *(undefined4 *)(iVar3 + 0x1b) = *puVar10;
                *(undefined2 *)(iVar3 + 0x1f) = *(undefined2 *)(puVar10 + 1);
                iVar8 = wdev_do_open(iVar3);
                if (iVar8 == 0) goto LAB_00282c5c;
                cVar2 = *(char *)(param_1 + 0x286285);
                if (cVar2 == '\x01') {
                  iVar8 = net_ad_wrap_service(param_1);
                  cVar2 = *(char *)(param_1 + 0x286285);
                  local_30 = (undefined4 *)(param_2 * 0xd18 + iVar8 + 0x591);
                }
                if (cVar2 == '\0') {
                  iVar8 = net_ad_wrap_service(param_1);
                  local_30 = (undefined4 *)(param_2 * 0xd18 + iVar8 + 0x531);
                }
                *(undefined4 *)(iVar3 + 0x21) = *local_30;
                *(undefined2 *)(iVar3 + 0x25) = *(undefined2 *)(local_30 + 1);
                wlan_operate_set_he_bss_color(iVar3,param_2 + 1U & 0xff,0);
                wifi_sys_linkup(iVar3,0);
                if ((*(short *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) == 0x7626) &&
                   (iVar3 = wlan_config_get_tx_stream(iVar3), iVar3 == 2)) {
                  puVar6 = (uint *)ant_to_spe_idx_map;
                  do {
                    puVar7 = puVar6 + 2;
                    if (*puVar6 < 4) {
                      puVar6[1] = 0x18;
                    }
                    puVar6 = puVar7;
                  } while (puVar7 != (uint *)&DAT_005e2280);
                }
              }
              cVar2 = '\0';
              goto LAB_00282b94;
            }
          }
        }
      }
      else if (*(char *)(param_1 + 0x286285) == '\0') {
LAB_00282cb4:
        iVar8 = net_ad_wrap_service(param_1);
        puVar10 = (undefined4 *)(param_2 * 0xd18 + iVar8 + 0x591);
        goto LAB_00282cd4;
      }
    }
LAB_00282c5c:
    if (-1 < DebugLevel) {
      printk("%s: Cannot get wdev by idx:%d\n","mt_ate_init_wdev",*(undefined1 *)(iVar3 + 0xc));
      cVar2 = -1;
      goto LAB_00282b94;
    }
  }
LAB_00282b90:
  cVar2 = -1;
LAB_00282b94:
  return (int)cVar2;
}

