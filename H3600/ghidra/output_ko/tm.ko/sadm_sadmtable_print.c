// module: tm.ko
// function: sadm_sadmtable_print @ 0x26e54
// size: 1372 bytes
//

undefined4 sadm_sadmtable_print(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  bool bVar11;
  int local_30;
  uint local_2c [2];
  
  local_30 = 0;
  if (param_1 == 0) {
    printk("tmtst -sport_ing_rate_limit port en band\n");
    printk("%-5s%-18s%-16s%-18s%-20s\n",&_LC211,"port_bucket_mode","port_bucket_en",
           "port_bucket_fill","port_bucket_capacity");
  }
  else if (param_1 == 1) {
    printk("tmtst -sport_cast_rate_limit port en band 0\n");
    printk("%-5s%-18s%-16s%-18s%-20s\n",&_LC211,"uc_bucket_mode","uc_bucket_en","uc_bucket_fill",
           "uc_bucket_capacity");
  }
  else if (param_1 == 2) {
    printk("tmtst -sport_cast_rate_limit port en band 1\n");
    printk("%-5s%-18s%-16s%-18s%-20s\n",&_LC211,"bc_bucket_mode","bc_bucket_en","bc_bucket_fill",
           "bc_bucket_capacity");
  }
  else if (param_1 == 3) {
    printk("tmtst -sport_cast_rate_limit port en band 2\n");
    printk("%-5s%-18s%-16s%-18s%-20s\n",&_LC211,"mc_bucket_mode","mc_bucket_en","mc_bucket_fill",
           "mc_bucket_capacity");
  }
  else if (param_1 == 4) {
    printk("tmtst -sport_cast_rate_limit port en band 3\n");
    printk("%-5s%-18s%-16s%-18s%-20s\n",&_LC211,"us_bucket_mode","us_bucket_en","us_bucket_fill",
           "us_bucket_capacity");
  }
  else if (param_1 == 5) {
    printk("tmtst -sport_cast_rate_limit port en band 4\n");
    printk("%-5s%-18s%-16s%-18s%-20s\n",&_LC211,"uud_bucket_mode","uud_bucket_en","uud_bucket_fill",
           "uud_bucket_capacity");
  }
  else if (param_1 == 6) {
    printk("tmtst -sport_cast_rate_limit port en band 5\n");
    printk("%-5s%-18s%-16s%-18s%-20s\n",&_LC211,"mud_bucket_mode","mud_bucket_en","mud_bucket_fill",
           "mud_bucket_capacity");
  }
  else {
    if (param_1 != 7) {
      return 0xffffffff;
    }
    printk("tmtst -s_wifi_rate ssid en band\n");
    printk("%-5s%-18s%-16s%-18s%-20s\n",&_LC211,"wifi_bucket_mode","wifi__bucket_en",
           "wifi__bucket_fill","wifi_bucket_capacity");
  }
  iVar8 = 8;
LAB_00026efc:
  iVar9 = 3;
  iVar7 = 1;
  iVar6 = 0;
  iVar2 = iVar8 + -8;
  do {
    if (local_30 == 0) {
      uVar4 = 0;
      uVar10 = 0;
      do {
        uVar1 = tmOnuRegRead(7,&local_30,0,sadmRegTable);
        uVar4 = uVar4 + 1;
        uVar10 = uVar1 | uVar10;
        bVar11 = uVar4 == 0x13;
        if (uVar4 < 0x14) {
          bVar11 = local_30 == 0;
        }
      } while (bVar11);
      if (0x13 < uVar4) {
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        iVar8 = ___ratelimit(_rs_14846,"sadm_sadmtable_print");
        goto joined_r0x00027360;
      }
      if (uVar10 != 0) {
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        iVar8 = ___ratelimit(_rs_14849,"sadm_sadmtable_print");
        goto joined_r0x00027324;
      }
    }
    iVar5 = iVar6;
    iVar3 = iVar2;
    switch(param_1) {
    case 0:
      iVar3 = iVar8;
      break;
    case 1:
      iVar5 = iVar9;
      break;
    case 2:
      iVar5 = iVar9;
      iVar3 = iVar8;
      break;
    case 3:
      iVar5 = iVar9;
      iVar3 = iVar8 + 8;
      break;
    case 4:
      iVar5 = iVar6 + 6;
      break;
    case 5:
      iVar5 = iVar6 + 9;
      break;
    case 6:
      iVar5 = iVar6 + 9;
      iVar3 = iVar8;
      break;
    case 7:
      break;
    default:
      return 1;
    }
    tmOnuRegWrite(6,iVar3 + 0x8000000 + iVar5 * 0x400000,0,sadmRegTable);
    if (local_30 == 0) {
      iVar5 = 0;
      while( true ) {
        tmOnuRegRead(7,&local_30,0,sadmRegTable);
        iVar5 = iVar5 + 1;
        if (local_30 != 0) break;
        if (iVar5 == 0x14) goto LAB_00026fe8;
      }
      if (iVar5 == 0x14) {
LAB_00026fe8:
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        iVar8 = ___ratelimit(_rs_14864,"sadm_sadmtable_print");
joined_r0x00027360:
        if (iVar8 == 0) {
          return 0xffffffff;
        }
        printk("[TM][sadm_sadmtable_print]indirect access time out\n");
        return 0xffffffff;
      }
    }
    iVar5 = tmOnuRegRead(8,local_2c,0,sadmRegTable);
    if (iVar5 != 0) {
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      iVar8 = ___ratelimit(_rs_14866,"sadm_sadmtable_print");
joined_r0x00027324:
      if (iVar8 == 0) {
        return 0xffffffff;
      }
      printk("[TM][sadm_sadmtable_print]indirect access failed\n");
      return 0xffffffff;
    }
    if (iVar6 == 0) {
      printk("%-5d%-18d%-16d",iVar2,(local_2c[0] << 0x1e) >> 0x1f,local_2c[0] & 1);
    }
    else if (iVar6 == 1) {
      printk("%-18d",local_2c[0] & 0x1fffffff);
    }
    else {
      printk("%-20d\n",local_2c[0] & 0x1fffff);
      if (iVar7 == 3) break;
    }
    iVar7 = iVar7 + 1;
    iVar6 = iVar6 + 1;
    iVar9 = iVar9 + 1;
  } while( true );
  iVar8 = iVar8 + 1;
  if (iVar8 == 0x10) {
    return 0;
  }
  goto LAB_00026efc;
}

