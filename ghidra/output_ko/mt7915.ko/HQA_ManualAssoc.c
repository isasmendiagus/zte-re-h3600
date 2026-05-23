// module: mt7915.ko
// function: HQA_ManualAssoc @ 0x27a238
// size: 1424 bytes
//

undefined4 HQA_ManualAssoc(int param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  int local_d4;
  undefined1 auStack_cd [3];
  undefined1 local_ca;
  undefined1 local_c9;
  undefined1 local_c8;
  uint local_c4;
  uint local_c0;
  uint local_bc;
  uint local_b8;
  uint local_b4;
  uint local_b0;
  uint local_ac;
  uint local_a8;
  undefined4 local_a2;
  undefined2 local_9e;
  undefined1 local_9c [4];
  undefined1 local_98 [4];
  undefined1 local_94 [4];
  int local_90;
  undefined4 local_8c;
  undefined2 local_88 [2];
  undefined1 local_84 [4];
  undefined4 local_80 [2];
  undefined1 local_78 [12];
  undefined2 local_6c [2];
  char acStack_68 [68];
  
  local_d4 = param_3 + 0xc;
  FUN_00276034(1,4,&local_d4,local_9c);
  FUN_00276034(1,4,&local_d4,local_98);
  FUN_00276034(1,4,&local_d4,local_94);
  FUN_00276034(1,4,&local_d4,&local_90);
  FUN_00276034(1,4,&local_d4,&local_8c);
  FUN_00276034(1,4,&local_d4,local_88);
  FUN_00276034(1,4,&local_d4,local_84);
  FUN_00276034(1,4,&local_d4,local_80);
  FUN_00276034(1,4,&local_d4,local_78);
  FUN_00276034(1,4,&local_d4,local_6c);
  FUN_00276034(0,6,&local_d4,&local_a2);
  *(undefined1 *)(param_1 + 0xa7865b) = local_9c[0];
  *(undefined1 *)(param_1 + 0xa7865d) = local_98[0];
  *(undefined1 *)(param_1 + 0xa7865c) = local_94[0];
  if (local_90 == 1) {
    *(undefined1 *)(param_1 + 0xa7865e) = 0x1e;
  }
  else if ((local_90 == 0) || (local_90 != 2)) {
    *(undefined1 *)(param_1 + 0xa7865e) = 0x3f;
  }
  else {
    *(undefined1 *)(param_1 + 0xa7865e) = 0x31;
  }
  iVar2 = DebugLevel;
  switch(local_8c) {
  case 0:
    *(undefined1 *)(param_1 + 0xa7865f) = 0;
    break;
  case 1:
    *(undefined1 *)(param_1 + 0xa7865f) = 1;
    break;
  case 2:
    *(undefined1 *)(param_1 + 0xa7865f) = 2;
    break;
  case 3:
    *(undefined1 *)(param_1 + 0xa7865f) = 4;
    break;
  case 4:
    *(undefined1 *)(param_1 + 0xa7865f) = 5;
    break;
  case 5:
    *(undefined1 *)(param_1 + 0xa7865f) = 3;
    break;
  case 6:
    *(undefined1 *)(param_1 + 0xa7865f) = 6;
    break;
  default:
    if (1 < DebugLevel) {
      printk("%s: Cannot find BW with manual_conn.bw:%x\n","HQA_ManualAssoc");
    }
    iVar2 = DebugLevel;
    *(char *)(param_1 + 0xa7865f) = (char)local_8c;
  }
  *(undefined2 *)(param_1 + 0xa78662) = local_88[0];
  *(undefined1 *)(param_1 + 0xa7866a) = local_84[0];
  *(undefined4 *)(param_1 + 0xa7866c) = local_80[0];
  *(undefined1 *)(param_1 + 0xa78664) = local_78[0];
  *(undefined2 *)(param_1 + 0xa78666) = local_6c[0];
  *(undefined4 *)(param_1 + 0xa78654) = local_a2;
  *(undefined1 *)(param_1 + 0xa78660) = 1;
  *(undefined2 *)(param_1 + 0xa78658) = local_9e;
  if (iVar2 < 1) goto LAB_0027a418;
  printk("%s:User manual configured peer STA info:\n","HQA_ManualAssoc");
  if (DebugLevel < 1) {
LAB_0027a66c:
    if (0 < DebugLevel) {
      printk("\tOperationType=>%d\n",*(undefined1 *)(param_1 + 0xa7865b));
      if (DebugLevel < 1) goto LAB_0027a418;
      printk("\tPhyMode=>%d\n",*(undefined1 *)(param_1 + 0xa7865e));
      goto LAB_0027a6ac;
    }
LAB_0027a6ec:
    if (0 < DebugLevel) {
      printk("\tPfmuId=>%d\n",*(undefined2 *)(param_1 + 0xa78662));
      if (DebugLevel < 1) goto LAB_0027a418;
      printk("\tAid=>%d\n",*(undefined2 *)(param_1 + 0xa78666));
      goto LAB_0027a734;
    }
  }
  else {
    printk("\tMAC=>0x%02x:%02x:%02x:%02x:%02x:%02x\n",*(undefined1 *)(param_1 + 0xa78654),
           *(undefined1 *)(param_1 + 0xa78655),*(undefined1 *)(param_1 + 0xa78656),
           *(undefined1 *)(param_1 + 0xa78657),*(undefined1 *)(param_1 + 0xa78658),
           *(undefined1 *)(param_1 + 0xa78659));
    if (DebugLevel < 1) goto LAB_0027a418;
    printk("\tBAND=>%d\n",*(undefined1 *)(param_1 + 0xa7865a));
    if (0 < DebugLevel) {
      printk("\tOwnMacIdx=>%d\n",*(undefined1 *)(param_1 + 0xa7865c));
      if (DebugLevel < 1) goto LAB_0027a418;
      printk("\tWTBL_Idx=>%d\n",*(undefined1 *)(param_1 + 0xa7865d));
      goto LAB_0027a66c;
    }
LAB_0027a6ac:
    if (0 < DebugLevel) {
      printk("\tBandWidth=>%d\n",*(undefined1 *)(param_1 + 0xa7865f));
      if (DebugLevel < 1) goto LAB_0027a418;
      printk("\tNSS=>%d\n",*(undefined1 *)(param_1 + 0xa78660));
      goto LAB_0027a6ec;
    }
LAB_0027a734:
    if ((DebugLevel < 1) ||
       (printk("\tSpe_idx=>%d\n",*(undefined1 *)(param_1 + 0xa78664)), DebugLevel < 1))
    goto LAB_0027a418;
    printk("\tMaxRate_Mode=>%d\n",*(undefined1 *)(param_1 + 0xa7866a));
  }
  if ((0 < DebugLevel) &&
     (printk("\tMaxRate_MCS=>%d\n",*(undefined4 *)(param_1 + 0xa7866c)), 0 < DebugLevel)) {
    printk("Now apply it to hardware!\n");
  }
LAB_0027a418:
  SetATEApplyStaToMacTblEntry(param_1);
  __memzero(acStack_68,0x40);
  sprintf(acStack_68,"%d-%d-%d-%d-%d-%d-%d-%d-%d-%d",(uint)*(byte *)(param_1 + 0xa7865d),
          (uint)*(byte *)(param_1 + 0xa7866a),(uint)*(byte *)(param_1 + 0xa7865f),
          *(undefined4 *)(param_1 + 0xa7866c),(uint)*(byte *)(param_1 + 0xa78660),0,0,0,0,0);
  if (0 < DebugLevel) {
    printk("\tSet fixed RateInfo string as %s\n",acStack_68);
  }
  uVar1 = asic_get_nsts_by_mcs
                    (param_1,*(undefined1 *)(param_1 + 0xa7866a),*(undefined1 *)(param_1 + 0xa7866c)
                     ,0,*(undefined1 *)(param_1 + 0xa78660));
  local_c4 = asic_tx_rate_to_tmi_rate
                       (param_1,*(undefined1 *)(param_1 + 0xa7866a),
                        *(undefined1 *)(param_1 + 0xa7866c),uVar1,0,0);
  local_c4 = local_c4 & 0xfff;
  local_c0 = local_c4;
  local_bc = local_c4;
  local_b8 = local_c4;
  local_b4 = local_c4;
  local_b0 = local_c4;
  local_ac = local_c4;
  local_a8 = local_c4;
  os_zero_mem(auStack_cd,9);
  local_c9 = *(undefined1 *)(param_1 + 0xa7865f);
  local_ca = 0;
  local_c8 = 0;
  AsicTxCapAndRateTableUpdate(param_1,*(undefined1 *)(param_1 + 0xa7865d),auStack_cd,&local_c4,0);
  SetATEApplyStaToAsic(param_1);
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}

