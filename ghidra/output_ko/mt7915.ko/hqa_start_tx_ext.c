// module: mt7915.ko
// function: hqa_start_tx_ext @ 0x276b74
// size: 1172 bytes
//

undefined4 hqa_start_tx_ext(int param_1,undefined4 param_2,int param_3)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  int local_80;
  undefined1 auStack_7c [4];
  undefined4 local_78;
  uint local_74;
  int local_70;
  uint local_6c;
  undefined4 local_68;
  undefined1 auStack_64 [4];
  int local_60;
  int local_5c;
  uint local_58;
  int local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c [2];
  
  local_80 = param_3 + 0xc;
  iVar9 = *(int *)(param_1 + 0xa39fd4);
  FUN_00276034(1,4,&local_80,&local_68);
  FUN_00276034(1,4,&local_80,auStack_64);
  FUN_00276034(1,4,&local_80,&local_60);
  FUN_00276034(1,4,&local_80,&local_5c);
  FUN_00276034(1,4,&local_80,&local_58);
  FUN_00276034(1,4,&local_80,&local_54);
  FUN_00276034(1,4,&local_80,&local_50);
  FUN_00276034(1,4,&local_80,&local_4c);
  FUN_00276034(1,4,&local_80,&local_48);
  FUN_00276034(1,4,&local_80,&local_44);
  FUN_00276034(1,4,&local_80,&local_40);
  FUN_00276034(1,4,&local_80,&local_3c);
  FUN_00276034(1,4,&local_80,&local_38);
  FUN_00276034(1,4,&local_80,&local_34);
  FUN_00276034(1,4,&local_80,&local_30);
  FUN_00276034(1,4,&local_80,local_2c);
  iVar5 = local_60;
  if (local_5c == 0) {
    local_5c = -0x70000001;
  }
  iVar6 = net_ad_wrap_service(param_1);
  iVar7 = iVar5 * 0xd18;
  *(int *)(iVar6 + iVar7 + 0x1118) = local_5c;
  iVar6 = net_ad_wrap_service(param_1);
  *(char *)(iVar6 + iVar7 + 0x1135) = (char)local_58;
  iVar6 = net_ad_wrap_service(param_1);
  *(char *)(iVar6 + iVar7 + 0x1138) = (char)local_54;
  iVar6 = net_ad_wrap_service(param_1);
  *(char *)(iVar6 + iVar7 + 0x113a) = (char)local_4c;
  iVar6 = net_ad_wrap_service(param_1);
  *(char *)(iVar6 + iVar7 + 0x113b) = (char)local_48;
  iVar6 = net_ad_wrap_service(param_1);
  *(char *)(iVar6 + iVar7 + 0x11cc) = (char)local_44;
  iVar6 = net_ad_wrap_service(param_1);
  *(char *)(iVar6 + iVar7 + 0x11cd) = (char)local_40;
  *(short *)(param_1 + 0xa3b008) = (short)local_3c;
  iVar6 = net_ad_wrap_service(param_1);
  *(undefined4 *)(iVar6 + iVar7 + 0x10f4) = local_38;
  iVar6 = net_ad_wrap_service(param_1);
  *(char *)(iVar6 + iVar7 + 0x113c) = (char)local_34;
  iVar6 = net_ad_wrap_service(param_1);
  *(undefined4 *)(iVar6 + iVar7 + 0x1128) = local_30;
  iVar6 = net_ad_wrap_service(param_1);
  *(char *)(iVar6 + iVar7 + 0x1139) = (char)local_2c[0];
  iVar6 = net_ad_wrap_service(param_1);
  bVar1 = *(byte *)(iVar6 + iVar7 + 0x1130);
  iVar6 = net_ad_wrap_service(param_1);
  bVar2 = *(byte *)(iVar6 + iVar7 + 0x1131);
  iVar6 = net_ad_wrap_service(param_1);
  cVar3 = *(char *)(iVar6 + iVar7 + 0x1137);
  iVar6 = net_ad_wrap_service(param_1);
  cVar4 = *(char *)(iVar6 + iVar7 + 0x1136);
  iVar6 = net_ad_wrap_service(param_1);
  uVar8 = *(undefined4 *)(iVar6 + iVar7 + 0x10f4);
  *(char *)(param_1 + 0xa3ae36) = (char)iVar5;
  if (((local_58 < 4) && (local_54 == 0x20)) && (cVar3 != '\x01' && cVar4 != '\x01')) {
    if (DebugLevel < 1) {
      uVar8 = 0xffffffff;
    }
    else {
      uVar8 = 0xffffffff;
      printk("%s: Bandwidth must to be 40 at MCS 32\n","hqa_start_tx_ext");
    }
  }
  else {
    os_zero_mem(auStack_7c,0x14);
    local_78 = local_50;
    local_70 = iVar5;
    local_74 = (uint)bVar1;
    local_6c = (uint)bVar2;
    (**(code **)(iVar9 + 0x68))(param_1,uVar8);
    (**(code **)(iVar9 + 8))(param_1);
    uVar8 = (**(code **)(iVar9 + 0x10))(param_1);
  }
  *(undefined4 *)(param_3 + 0xe) = local_68;
  FUN_0026cdd0(param_3,param_2,6,uVar8);
  if ((0 < DebugLevel) &&
     (printk("%s: band_idx:%u, pkt_cnt:%u, phy:%u, mcs:%u, stbc:%u, ldpc:%u\n","hqa_start_tx_ext",
             local_60,local_5c,local_58,local_54,local_4c,local_48), 0 < DebugLevel)) {
    printk("%s: ibf:%u, ebf:%u, wlan_id:%u, aifs:%u, gi:%u, tx_path:%x, nss:%x\n","hqa_start_tx_ext"
           ,local_44,local_40,local_3c,local_38,local_34,local_30,local_2c[0]);
  }
  return uVar8;
}

