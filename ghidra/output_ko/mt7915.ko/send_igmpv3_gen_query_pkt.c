// module: mt7915.ko
// function: send_igmpv3_gen_query_pkt @ 0x242b2c
// size: 352 bytes
//

void send_igmpv3_gen_query_pkt(undefined4 param_1,int param_2)

{
  undefined *local_72;
  undefined2 local_6e;
  undefined4 local_6c;
  undefined2 local_68;
  undefined2 local_66;
  undefined4 local_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 local_54;
  undefined4 uStack_50;
  undefined4 local_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  
  local_64 = 0x24000046;
  uStack_60 = 0x100;
  uStack_5c = 0xd2440201;
  uStack_58 = 0;
  local_54 = 0x10000e0;
  uStack_50 = 0x494;
  local_72 = (undefined *)0x0;
  local_6e = 0;
  local_6c = 0;
  local_68 = 0;
  local_66 = 0;
  if (3 < DebugLevel) {
    printk("send_igmpv3_gen_query_pkt---->\n");
  }
  __memzero(&local_72,0xe);
  local_6c = *(undefined4 *)(*(int *)(param_2 + 8) + 0x1b);
  local_68 = *(undefined2 *)(*(int *)(param_2 + 8) + 0x1f);
  local_4c = local_64;
  uStack_48 = uStack_60;
  uStack_44 = uStack_5c;
  uStack_40 = uStack_58;
  local_66 = TYPEIPV4;
  local_3c = local_54;
  uStack_38 = uStack_50;
  local_72 = &DAT_005e0001;
  local_6e = 0x100;
  local_34 = 0xf5ee0a11;
  uStack_30 = 0;
  uStack_2c = 0;
  RTMPToWirelessSta(param_1,param_2,&local_72,0xe,&local_4c,0x24,0);
  if (3 < DebugLevel) {
    printk("<----- send_igmpv3_gen_query_pkt\n");
  }
  return;
}

