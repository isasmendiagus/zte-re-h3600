// module: tm.ko
// function: adm_get_pkt_stastc @ 0x2c56c
// size: 512 bytes
//

undefined4 adm_get_pkt_stastc(int param_1,uint param_2,undefined4 *param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  bool bVar8;
  bool bVar9;
  int local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][adm_get_pkt_stastc]input:dir = %d, wlan_id = %d\n",param_1,param_2);
  }
  bVar9 = 0x1e < param_2;
  bVar8 = param_2 == 0x1f;
  if (param_2 < 0x20) {
    bVar9 = param_1 != 0;
    bVar8 = param_1 == 1;
  }
  if (bVar9 && !bVar8) {
    if ((g_tm_debug_level != 0) && (iVar7 = ___ratelimit(_rs_7384,"adm_get_pkt_stastc"), iVar7 != 0)
       ) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp_adm.c",0x664);
    }
    return 1;
  }
  uVar5 = 0;
  if (local_30 == 0) {
    uVar5 = 0;
    uVar6 = 0;
    do {
      uVar6 = uVar6 + 1;
      uVar1 = adm_get_ind_acc_done(&local_30);
      uVar5 = uVar5 | uVar1;
      bVar8 = uVar6 == 0x13;
      if (uVar6 < 0x14) {
        bVar8 = local_30 == 0;
      }
    } while (bVar8);
    if (0x13 < uVar6) goto LAB_0002c5f8;
  }
  if (param_1 == 0) {
    uVar4 = 2;
  }
  else {
    uVar4 = 3;
  }
  uVar6 = adm_set_indirect_rw_cmd(1,uVar4,param_2);
  uVar6 = uVar6 | uVar5;
  if (local_30 != 0) {
LAB_0002c684:
    iVar7 = adm_get_ind_acc_data(2,&local_24);
    iVar2 = adm_get_ind_acc_data(1,&local_28);
    iVar3 = adm_get_ind_acc_data(0,&local_2c);
    if (((iVar7 == 0 && uVar6 == 0) && iVar2 == 0) && iVar3 == 0) {
      *param_3 = local_2c;
      uVar5 = g_tm_debug_level;
      param_3[1] = local_28;
      if (6 < uVar5) {
        printk("[TM][adm_get_pkt_stastc]output:  pass_pkts = %ld, pass_bytes = %ld\n");
      }
      return 0;
    }
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    printk("ERROR:(%s:%d)indirect access  write failed!\n","pp_adm.c",0x695);
    return 0xffffffff;
  }
  iVar7 = 0;
  do {
    iVar7 = iVar7 + 1;
    uVar5 = adm_get_ind_acc_done(&local_30);
    uVar6 = uVar6 | uVar5;
    if (local_30 != 0) {
      if (iVar7 != 0x14) goto LAB_0002c684;
      break;
    }
  } while (iVar7 != 0x14);
LAB_0002c5f8:
  if (6 < g_tm_debug_level) {
    printk("[TM][adm_get_pkt_stastc]indirect access time out\n");
  }
  return 0xffffffff;
}

