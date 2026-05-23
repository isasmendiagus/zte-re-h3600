// module: mt7915.ko
// function: AsicSwitchChannel @ 0x132178
// size: 456 bytes
//

void AsicSwitchChannel(int param_1,undefined4 param_2,char *param_3,undefined1 param_4)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  char cVar5;
  uint uVar6;
  byte bVar7;
  bool bVar8;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  iVar3 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  iVar4 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  if (iVar4 != 2) {
    return;
  }
  os_zero_mem(&local_3c,0x14);
  bVar7 = "SetPartProfileParameters"[param_1 + 0x18];
  uVar6 = bVar7 & 0xf;
  local_34 = CONCAT31(local_34._1_3_,(char)param_2);
  local_38 = CONCAT31(CONCAT21(CONCAT11(local_38._3_1_,param_4),
                               (byte)(((uint)bVar7 << 0x1c) >> 0x1c)),bVar7 >> 4);
  local_3c._0_3_ = CONCAT12(param_3[6],(undefined2)local_3c);
  local_2c._0_2_ = CONCAT11(param_3[10],(undefined1)local_2c);
  if (2 < DebugLevel) {
    printk(&_LC3,"AsicSwitchChannel",uVar6,uVar6);
  }
  if (*(char *)(param_1 + 0x79504d) != '\0') {
    if ((char)local_34 == '\0') {
      cVar1 = "SetPartProfileParameters"[param_1 + 0x1a];
      cVar5 = "SetPartProfileParameters"[param_1 + 0x1b];
    }
    else {
      cVar1 = "rtmp_read_vow_parms_from_file"[param_1];
      cVar5 = "rtmp_read_vow_parms_from_file"[param_1 + 1];
    }
    local_38._0_2_ = CONCAT11(cVar5,cVar1);
    if (DebugLevel < 3) goto LAB_00132258;
    printk(&_LC4,"AsicSwitchChannel");
  }
  cVar5 = local_38._1_1_;
LAB_00132258:
  param_3[8] = cVar5;
  bVar7 = param_3[6] - 0x24;
  local_34._0_2_ = CONCAT11(*param_3,(char)local_34);
  bVar8 = bVar7 == 0x81;
  if (bVar7 < 0x82) {
    bVar8 = *param_3 == '\0';
  }
  local_3c = CONCAT13(param_3[3],(undefined3)local_3c);
  if (bVar8) {
    local_34._0_2_ = CONCAT11(1,(char)local_34);
    if (2 < DebugLevel) {
      printk(&_LC5,"AsicSwitchChannel",param_3[6]);
    }
  }
  local_30 = 0;
  local_2c = CONCAT31(local_2c._1_3_,param_3[9]);
  local_3c._0_2_ = CONCAT11(param_3[7],param_3[5]);
  uVar2 = DfsSwitchCheck(param_1,param_3[5],param_2);
  local_38 = CONCAT13(uVar2,(undefined3)local_38);
  if (*(code **)(iVar3 + 0x20) == (code *)0x0) {
    return;
  }
  (**(code **)(iVar3 + 0x20))(param_1,local_3c,local_38,local_34,local_30,local_2c);
  return;
}

