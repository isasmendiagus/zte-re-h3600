// module: mt7915.ko
// function: hqa_start_rx_ext @ 0x277b10
// size: 772 bytes
//

undefined4 hqa_start_rx_ext(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int local_50;
  undefined4 local_4c;
  uint local_48;
  uint local_44;
  undefined4 local_40;
  uint local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined1 local_2a;
  undefined1 local_29;
  
  iVar6 = *(int *)(param_1 + 0xa39fd4);
  local_50 = param_3 + 0xc;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  __memzero(&local_2e,6);
  FUN_00276034(1,4,&local_50,&local_4c);
  FUN_00276034(1,4,&local_50,&local_48);
  FUN_00276034(1,4,&local_50,&local_44);
  FUN_00276034(0,6,&local_50,&local_2e);
  FUN_00276034(1,4,&local_50,&local_40);
  *(char *)(param_1 + 0xa3ae36) = (char)local_44;
  iVar3 = net_ad_wrap_service(param_1);
  FUN_00276034(1,4,&local_50,local_44 * 0xd18 + iVar3 + 0x1110);
  if (3 < local_48) {
    FUN_00276034(1,4,&local_50,&local_38);
    FUN_00276034(1,4,&local_50,&local_34);
    FUN_00276034(1,4,&local_50,&local_3c);
    if (0 < DebugLevel) {
      printk("%s: param num:%d, tx_mode:%d, ltf_gi:%d, user_idx:%d\n","hqa_start_rx_ext",local_48,
             local_38,local_34,local_3c);
    }
  }
  iVar3 = net_ad_wrap_service(param_1);
  iVar4 = net_ad_wrap_service(param_1);
  *(char *)((uint)*(byte *)(iVar4 + 0x4cc) * 0xd18 + iVar3 + 0x1135) = (char)local_38;
  iVar3 = net_ad_wrap_service(param_1);
  iVar4 = net_ad_wrap_service(param_1);
  *(char *)((uint)*(byte *)(iVar4 + 0x4cc) * 0xd18 + iVar3 + 0x113c) = (char)local_34;
  iVar3 = net_ad_wrap_service(param_1);
  iVar4 = net_ad_wrap_service(param_1);
  *(undefined2 *)((uint)*(byte *)(iVar4 + 0x4cc) * 0xd18 + iVar3 + 0x1160) = (undefined2)local_3c;
  (**(code **)(iVar6 + 0x28))(param_1,local_44 & 0xff,local_3c & 0xffff);
  (**(code **)(iVar6 + 0x48))(param_1,local_40);
  (**(code **)(iVar6 + 0xd8))(param_1,&local_2e,1);
  uVar5 = (**(code **)(iVar6 + 0x14))(param_1);
  uVar2 = local_40;
  uVar1 = local_48;
  if (0 < DebugLevel) {
    iVar3 = net_ad_wrap_service(param_1);
    printk("%s: param num:%u, band_sel:%u, rx_path:%x, mac:%02x:%02x:%02x:%02x:%02x:%02x, MU Aid:%d\n"
           ,"hqa_start_rx_ext",uVar1,local_44,uVar2,local_2e,local_2d,local_2c,local_2b,local_2a,
           local_29,*(undefined4 *)(local_44 * 0xd18 + iVar3 + 0x1110));
  }
  *(undefined4 *)(param_3 + 0xe) = local_4c;
  FUN_0026cdd0(param_3,param_2,6,uVar5);
  return uVar5;
}

