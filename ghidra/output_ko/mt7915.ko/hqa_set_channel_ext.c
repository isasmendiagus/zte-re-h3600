// module: mt7915.ko
// function: hqa_set_channel_ext @ 0x2774d4
// size: 1204 bytes
//

undefined4 hqa_set_channel_ext(int param_1,undefined4 param_2,int param_3)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 local_6c;
  undefined1 local_64;
  undefined1 local_60;
  int local_58;
  undefined4 local_54;
  undefined4 local_50;
  uint local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c [2];
  
  uVar1 = *(ushort *)(param_3 + 8);
  local_58 = param_3 + 0xc;
  iVar6 = *(int *)(param_1 + 0xa39fd4);
  FUN_00276034(1,4,&local_58,&local_54);
  FUN_00276034(1,4,&local_58,&local_50);
  FUN_00276034(1,4,&local_58,&local_4c);
  FUN_00276034(1,4,&local_58,&local_48);
  FUN_00276034(1,4,&local_58,&local_44);
  FUN_00276034(1,4,&local_58,&local_40);
  FUN_00276034(1,4,&local_58,&local_3c);
  FUN_00276034(1,4,&local_58,&local_38);
  FUN_00276034(1,4,&local_58,&local_34);
  FUN_00276034(1,4,&local_58,&local_30);
  FUN_00276034(1,4,&local_58,local_2c);
  uVar2 = local_4c;
  if (1 < local_4c) {
    uVar4 = 2;
    local_6c = 0;
    goto LAB_0027760c;
  }
  switch(local_40) {
  case 0:
    local_60 = 0;
    local_6c = 0;
    break;
  case 1:
    local_60 = 1;
    local_6c = 1;
    break;
  case 2:
    local_60 = 2;
    local_6c = 2;
    break;
  case 3:
    local_60 = 4;
    local_6c = 4;
    break;
  case 4:
    local_60 = 5;
    local_6c = 5;
    break;
  case 5:
    local_60 = 3;
    local_6c = 3;
    break;
  case 6:
    local_60 = 6;
    local_6c = 6;
    break;
  default:
    if (1 < DebugLevel) {
      local_60 = 0;
      printk("%s: Cannot find BW with param.sys_bw:%x, forced as 0x%x\n","hqa_set_channel_ext");
      local_6c = 0;
      break;
    }
    switch(local_3c) {
    case 1:
      local_60 = 0;
      local_6c = 0;
      goto switchD_00277690_caseD_1;
    case 2:
      local_60 = 0;
      local_6c = 0;
      goto switchD_00277690_caseD_2;
    case 3:
      local_60 = 0;
      local_6c = 0;
      goto switchD_00277690_caseD_3;
    case 4:
      local_60 = 0;
      local_6c = 0;
      goto switchD_00277690_caseD_4;
    case 5:
    case 6:
      local_60 = 0;
      local_6c = 0;
      goto switchD_00277690_caseD_5;
    default:
      local_60 = 0;
      local_64 = 0;
      local_6c = 0;
    }
    goto LAB_002776bc;
  }
  switch(local_3c) {
  case 0:
switchD_00277690_caseD_0:
    local_64 = 0;
    break;
  case 1:
switchD_00277690_caseD_1:
    local_64 = 1;
    break;
  case 2:
switchD_00277690_caseD_2:
    local_64 = 2;
    break;
  case 3:
switchD_00277690_caseD_3:
    local_64 = 4;
    break;
  case 4:
switchD_00277690_caseD_4:
    local_64 = 5;
    break;
  case 5:
  case 6:
switchD_00277690_caseD_5:
    local_64 = 3;
    break;
  default:
    if (DebugLevel < 2) goto switchD_00277690_caseD_0;
    local_64 = 0;
    printk("%s: Cannot find BW with param.sys_bw:%x\n, forced as 0x%x","hqa_set_channel_ext",
           local_40);
  }
LAB_002776bc:
  iVar3 = net_ad_wrap_service(param_1);
  uVar4 = 0;
  iVar5 = uVar2 * 0xd18;
  *(char *)(iVar3 + iVar5 + 0x1130) = (char)local_48;
  iVar3 = net_ad_wrap_service(param_1);
  *(char *)(iVar3 + iVar5 + 0x1143) = (char)local_44;
  iVar3 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar3 + iVar5 + 0x1137) = local_64;
  iVar3 = net_ad_wrap_service(param_1);
  *(undefined1 *)(iVar3 + iVar5 + 0x1136) = local_60;
  iVar3 = net_ad_wrap_service(param_1);
  *(char *)(iVar3 + iVar5 + 0x1133) = (char)local_38;
  iVar3 = net_ad_wrap_service(param_1);
  *(char *)(iVar3 + iVar5 + 0x1131) = (char)local_30;
  iVar3 = net_ad_wrap_service(param_1);
  *(undefined4 *)(iVar3 + iVar5 + 0x1144) = local_2c[0];
  *(char *)(param_1 + 0xa3ae36) = (char)uVar2;
  (**(code **)(iVar6 + 0x54))(param_1,(int)(short)local_48,local_38,local_34,local_30);
LAB_0027760c:
  iVar6 = DebugLevel;
  *(undefined4 *)(param_3 + 0xe) = local_54;
  if ((0 < iVar6) &&
     (printk("%s: len:%x, num_param:%x, band_idx:%x, ch0:%u, ch1:%u, sys_bw:%x, bw_conver:%x, ",
             "hqa_set_channel_ext",uVar1 << 8 | uVar1 >> 8,local_50,local_4c,local_48,local_44,
             local_40,local_6c), 0 < DebugLevel)) {
    printk("perpkt_bw:%x, pri_sel:%x, pri_ch:%u, ch_band:%u\n",local_3c,local_38,0,local_30,local_48
           ,local_44,local_40,local_6c);
  }
  FUN_0026cdd0(param_3,param_2,6,uVar4);
  return uVar4;
}

