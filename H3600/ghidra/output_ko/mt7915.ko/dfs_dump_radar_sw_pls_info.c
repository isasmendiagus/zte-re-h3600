// module: mt7915.ko
// function: dfs_dump_radar_sw_pls_info @ 0x230d4c
// size: 1860 bytes
//

void dfs_dump_radar_sw_pls_info(int param_1,undefined1 *param_2)

{
  bool bVar1;
  undefined1 *puVar2;
  undefined1 *extraout_r1;
  undefined1 *extraout_r1_00;
  undefined1 *extraout_r1_01;
  undefined1 *extraout_r1_02;
  undefined1 *extraout_r1_03;
  undefined1 *extraout_r1_04;
  undefined1 *extraout_r1_05;
  undefined1 *extraout_r1_06;
  undefined1 *extraout_r1_07;
  undefined1 *extraout_r1_08;
  undefined1 *extraout_r1_09;
  undefined1 *extraout_r1_10;
  undefined1 *extraout_r1_11;
  undefined1 *extraout_r1_12;
  undefined1 *extraout_r1_13;
  undefined1 *extraout_r1_14;
  undefined1 *extraout_r1_15;
  undefined1 *extraout_r1_16;
  undefined1 *extraout_r1_17;
  undefined1 *extraout_r1_18;
  undefined1 *extraout_r1_19;
  undefined1 *extraout_r1_20;
  undefined1 *extraout_r1_21;
  undefined1 *extraout_r1_22;
  undefined1 *extraout_r1_23;
  undefined1 *extraout_r1_24;
  undefined1 *extraout_r1_25;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  
  if (param_2 == (undefined1 *)0x0) {
    return;
  }
  puVar2 = param_2;
  if ((param_2[2] == '\x01') || (param_2[3] == '\x01')) {
    if (param_2[1] != '\x01') {
      bVar1 = true;
      goto LAB_00230d9c;
    }
    bVar1 = true;
LAB_00230f30:
    if (DebugLevel < 1) goto LAB_00230db0;
    printk("===> RDD-%d: Long pulse radar is detected\n",*param_2);
    puVar2 = extraout_r1_01;
LAB_00230f54:
    if (DebugLevel < 1) goto LAB_00230db0;
    printk("LPN = %d (FCC5_LPN = %d)\n",param_2[8],*(undefined2 *)(param_1 + 0x795434));
    uVar4 = (uint)(byte)param_2[6];
    puVar2 = extraout_r1_02;
    if (uVar4 != 0) {
      if (DebugLevel < 1) goto LAB_00230dbc;
      printk("\n----------------------Long pulse buffer----------------------\n");
      if (0 < DebugLevel) {
        printk("Index\t| ST(us)\t | PW(us)\t | Power(dBm)\t | PRI(us)\n");
        uVar4 = (uint)(byte)param_2[6];
        iVar3 = DebugLevel;
        puVar2 = extraout_r1_04;
        if (uVar4 != 0) goto LAB_00230dbc;
        goto LAB_00230e30;
      }
      uVar4 = (uint)(byte)param_2[6];
      puVar2 = extraout_r1_03;
      if (uVar4 != 0) goto LAB_00230dbc;
      goto LAB_00230e38;
    }
LAB_00230f08:
    if (bVar1) {
      if (0 < DebugLevel) {
        printk("===> RDD-%d: Periodic radar (RT-%d, RT_STGR = %d) is detected\n",*param_2,param_2[4]
               ,param_2[3]);
        puVar2 = extraout_r1_05;
      }
LAB_00230ff0:
      uVar4 = (uint)(byte)param_2[4];
      if (param_1 + uVar4 * 0x1c == -0x795468) {
        return;
      }
      if (0 < DebugLevel) {
        printk("SPN = %d\n",param_2[9]);
        puVar2 = extraout_r1_06;
        if (DebugLevel < 1) {
LAB_002310ec:
          if (DebugLevel < 1) {
LAB_002311c0:
            if ((0 < DebugLevel) &&
               (printk("PRI_DIFF12 = %d\n",*(undefined4 *)(param_2 + 0x20)), puVar2 = extraout_r1_15
               , 0 < DebugLevel)) {
              iVar3 = uVar4 * 0x1c + param_1;
              printk("STGPW = %d \t(RT_PW_MIN = %d, RT_PW_MAX = %d)\n",param_2[0xe],
                     *(undefined1 *)(iVar3 + 0x79546e),*(undefined1 *)(iVar3 + 0x79546f));
              puVar2 = extraout_r1_16;
LAB_0023121c:
              if (0 < DebugLevel) {
                param_1 = uVar4 * 0x1c + param_1;
                printk("STGPN = %d \t(RT_STGPN_MIN = %d, RT_STGPN_MAX = %d)\n",param_2[0xd],
                       *(undefined1 *)(param_1 + 0x79547a),*(undefined1 *)(param_1 + 0x79547b));
                puVar2 = extraout_r1_17;
                if (0 < DebugLevel) {
                  printk("STGPR = %d/%d \t(RT_STGPR_MIN = %d/%d)\n",param_2[0xd],param_2[5],
                         *(undefined1 *)(param_1 + 0x79547c),0x20);
                  puVar2 = extraout_r1_18;
                }
              }
            }
          }
          else {
            iVar3 = uVar4 * 0x1c + param_1;
            printk("CRBN = %d \t(RT_CRBN_MIN = %d, RT_CRBN_MAX = %d)\n",param_2[0xc],
                   *(undefined1 *)(iVar3 + 0x795478),*(undefined1 *)(iVar3 + 0x795479));
            puVar2 = extraout_r1_11;
            if (0 < DebugLevel) {
              printk("PRI_STG1 = %d \t(RT_PRI_MIN = %d, RT_PRI_MAX*3 = %d)\n",
                     *(undefined4 *)(param_2 + 0x14),*(undefined4 *)(iVar3 + 0x795470),
                     *(int *)(iVar3 + 0x795474) * 3);
              puVar2 = extraout_r1_12;
LAB_00231160:
              if (DebugLevel < 1) goto LAB_0023121c;
              iVar3 = uVar4 * 0x1c + param_1;
              printk("PRI_STG2 = %d \t(RT_PRI_MIN = %d, RT_PRI_MAX*3 = %d)\n",
                     *(undefined4 *)(param_2 + 0x18),*(undefined4 *)(iVar3 + 0x795470),
                     *(int *)(iVar3 + 0x795474) * 3);
              puVar2 = extraout_r1_13;
              if (0 < DebugLevel) {
                printk("PRI_STG3 = %d\n",*(undefined4 *)(param_2 + 0x1c));
                puVar2 = extraout_r1_14;
                goto LAB_002311c0;
              }
            }
          }
        }
        else {
          iVar3 = uVar4 * 0x1c + param_1;
          printk("CRPN = %d \t(RT_CRPN_MIN = %d, RT_CRPN_MAX = %d)\n",param_2[10],
                 *(undefined1 *)(iVar3 + 0x79546b),*(undefined1 *)(iVar3 + 0x79546c));
          puVar2 = extraout_r1_07;
          if (0 < DebugLevel) {
            uVar7 = 0x20;
            printk("CRPR = %d/%d \t(RT_CRPR_MIN = %d/%d)\n",param_2[10],param_2[5],
                   *(undefined1 *)(iVar3 + 0x79546d),0x20);
            puVar2 = extraout_r1_08;
            if (DebugLevel < 1) goto LAB_00231160;
            printk("CRPW = %d \t(RT_PW_MIN = %d, RT_PW_MAX = %d)\n",param_2[0xb],
                   *(undefined1 *)(iVar3 + 0x79546e),*(undefined1 *)(iVar3 + 0x79546f),uVar7);
            puVar2 = extraout_r1_09;
            if (0 < DebugLevel) {
              printk("PRI_CONST = %d \t(RT_PRI_MIN = %d, RT_PRI_MAX = %d)\n",
                     *(undefined4 *)(param_2 + 0x10),*(undefined4 *)(iVar3 + 0x795470),
                     *(undefined4 *)(iVar3 + 0x795474),uVar7);
              puVar2 = extraout_r1_10;
              goto LAB_002310ec;
            }
          }
        }
      }
    }
    else if (0 < DebugLevel) {
      printk("===> RDD-%d: No periodic radar is detected\n",*param_2);
      puVar2 = extraout_r1_00;
    }
  }
  else {
    if (param_2[1] == '\x01') {
      bVar1 = false;
      goto LAB_00230f30;
    }
    bVar1 = false;
    if (*(char *)(param_1 + 0x795438) != '\0') {
      return;
    }
LAB_00230d9c:
    if (0 < DebugLevel) {
      printk("===> RDD-%d: No Long pulse radar is detected\n",*param_2);
      puVar2 = extraout_r1_25;
      goto LAB_00230f54;
    }
LAB_00230db0:
    uVar4 = (uint)(byte)param_2[6];
    if (uVar4 == 0) goto LAB_00230f08;
LAB_00230dbc:
    uVar5 = 0;
    iVar3 = DebugLevel;
    do {
      if (iVar3 < 1) {
        if (uVar5 != 0) {
          iVar6 = uVar5 << 1;
          goto LAB_00230de4;
        }
      }
      else {
        iVar6 = uVar5 * 2;
        printk("%u\t%u\t\t",uVar5,(uint)(*(int *)(param_2 + uVar5 * 0xc + 0x24) << 2) / 10);
        if (DebugLevel < 1) {
          iVar3 = DebugLevel;
          puVar2 = extraout_r1_21;
          if (uVar5 != 0) goto LAB_00230de4;
        }
        else {
          iVar3 = *(short *)(param_2 + uVar5 * 0xc + 0x2a) + -0x400;
          if (iVar3 < 0) {
            iVar3 = *(short *)(param_2 + uVar5 * 0xc + 0x2a) + -0x3fd;
          }
          printk("%u\t\t%d\t\t",((uint)*(ushort *)(param_2 + uVar5 * 0xc + 0x28) << 2) / 10,
                 iVar3 >> 2);
          iVar3 = DebugLevel;
          if (uVar5 == 0) {
            puVar2 = (undefined1 *)0x0;
          }
          else {
LAB_00230de4:
            puVar2 = (undefined1 *)
                     (((*(int *)(param_2 + (iVar6 + uVar5) * 4 + 0x24) -
                        *(int *)(param_2 + (uVar5 - 1) * 0xc + 0x24) & 0x3ffffffU) << 2) / 10);
          }
          if (0 < iVar3) {
            printk(&_LC39,puVar2);
            iVar3 = DebugLevel;
            puVar2 = extraout_r1_22;
          }
        }
        uVar4 = (uint)(byte)param_2[6];
      }
      uVar5 = uVar5 + 1 & 0xff;
    } while (uVar5 < uVar4);
LAB_00230e30:
    if (0 < iVar3) {
      printk("-----------------------------------------------------------\n",puVar2);
      puVar2 = extraout_r1;
      goto LAB_00230f08;
    }
LAB_00230e38:
    if (bVar1) goto LAB_00230ff0;
  }
  uVar4 = (uint)(byte)param_2[5];
  if (uVar4 == 0) {
    return;
  }
  if (0 < DebugLevel) {
    printk("\n----------------------Short pulse buffer----------------------\n");
    if (DebugLevel < 1) {
      uVar4 = (uint)(byte)param_2[5];
      puVar2 = extraout_r1_23;
      if (uVar4 == 0) {
        return;
      }
    }
    else {
      printk("Index\t| ST(us)\t | PW(us)\t | Power(dBm)\t | PRI(us)\n");
      uVar4 = (uint)(byte)param_2[5];
      iVar3 = DebugLevel;
      puVar2 = extraout_r1_24;
      if (uVar4 == 0) goto LAB_00230ed4;
    }
  }
  uVar5 = 0;
  iVar3 = DebugLevel;
  do {
    if (iVar3 < 1) {
      if (uVar5 != 0) {
        iVar6 = uVar5 << 1;
        goto LAB_00230e88;
      }
    }
    else {
      iVar6 = uVar5 * 2;
      printk("%u\t%u\t\t",uVar5,(uint)(*(int *)(param_2 + uVar5 * 0xc + 0x1a4) << 2) / 10);
      if (DebugLevel < 1) {
        iVar3 = DebugLevel;
        puVar2 = extraout_r1_20;
        if (uVar5 != 0) goto LAB_00230e88;
      }
      else {
        iVar3 = (int)(short)(*(short *)(param_2 + uVar5 * 0xc + 0x1aa) + -0x400);
        if (iVar3 < 0) {
          iVar3 = iVar3 + 3;
        }
        printk("%u\t\t%d\t\t",((uint)*(ushort *)(param_2 + uVar5 * 0xc + 0x1a8) << 2) / 10,
               iVar3 >> 2);
        iVar3 = DebugLevel;
        if (uVar5 == 0) {
          puVar2 = (undefined1 *)0x0;
        }
        else {
LAB_00230e88:
          puVar2 = (undefined1 *)
                   (((*(int *)(param_2 + (iVar6 + uVar5) * 4 + 0x1a4) -
                      *(int *)(param_2 + (uVar5 - 1) * 0xc + 0x1a4) & 0x3ffffffU) << 2) / 10);
        }
        if (0 < iVar3) {
          printk(&_LC39,puVar2);
          iVar3 = DebugLevel;
          puVar2 = extraout_r1_19;
        }
      }
      uVar4 = (uint)(byte)param_2[5];
    }
    uVar5 = uVar5 + 1 & 0xff;
  } while (uVar5 < uVar4);
LAB_00230ed4:
  if (iVar3 < 1) {
    return;
  }
  printk("--------------------------------------------------------------\n",puVar2);
  return;
}

