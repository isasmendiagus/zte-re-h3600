// module: mt7915.ko
// function: bssUpdateBssInfoBasic @ 0x1c2a5c
// size: 384 bytes
//

void bssUpdateBssInfoBasic(undefined4 param_1,int param_2,undefined4 param_3)

{
  ushort uVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined2 local_44;
  undefined2 local_42;
  undefined4 local_40;
  undefined4 local_3c;
  uint local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  local_40 = *(undefined4 *)(param_2 + 0x18);
  local_38 = 0;
  local_30 = 0;
  local_2c = 0;
  local_44 = 1;
  local_42 = 0x1c;
  local_3c = CONCAT22(*(undefined2 *)(param_2 + 0x58),(ushort)(1 < *(uint *)(param_2 + 4)));
  local_34 = (uint)*(byte *)(param_2 + 0x5a) << 0x18;
  os_move_mem(&local_38,(void *)(param_2 + 0xe),6);
  uVar3 = local_30;
  uVar2 = local_34;
  if (*(int *)(param_2 + 0x1c) == 0x10001) {
    uVar1 = *(ushort *)(param_2 + 0x16);
  }
  else {
    uVar1 = *(ushort *)(param_2 + 0x14);
  }
  uVar4 = (uint)uVar1 << 0x16;
  local_34._0_3_ = CONCAT12(*(undefined1 *)(param_2 + 0x21),(ushort)local_34);
  local_2c._0_2_ = CONCAT11((byte)(uVar4 >> 0x1e),(undefined1)local_2c);
  local_30._3_1_ = SUB41(uVar3,3);
  local_30._0_3_ =
       CONCAT12(*(undefined1 *)(param_2 + 0x22),
                CONCAT11(*(undefined1 *)(param_2 + 0x20),(char)uVar1));
  if (DebugLevel < 3) {
    local_30 = CONCAT13(*(undefined1 *)(param_2 + 0x104),(undefined3)local_30);
    local_2c = CONCAT31(local_2c._1_3_,*(undefined1 *)(param_2 + 0x105));
  }
  else {
    printk("%s, u4NetworkType = %d, ucActive = %d, u2BcnInterval = %d, ucWmmIdx = %d,ucDtimPeriod = %d, bmc_wlan_idx = %d, ucCipherSuit=%d, ucPhyMode=%x,BSSID = %02x:%02x:%02x:%02x:%02x:%02x\n"
           ,"bssUpdateBssInfoBasic",*(undefined4 *)(param_2 + 0x18),local_3c & 0xff,local_3c >> 0x10
           ,*(undefined1 *)(param_2 + 0x21),local_34._3_1_,uVar1 & 0xff | (uVar4 >> 0x1e) << 8,
           *(undefined1 *)(param_2 + 0x20),*(undefined1 *)(param_2 + 0x22),local_38 & 0xff,
           local_38 >> 8 & 0xff,local_38 >> 0x10 & 0xff,local_38 >> 0x18,(ushort)local_34 & 0xff,
           uVar2 >> 8 & 0xff);
    local_30 = CONCAT13(*(undefined1 *)(param_2 + 0x104),(undefined3)local_30);
    local_2c = CONCAT31(local_2c._1_3_,*(undefined1 *)(param_2 + 0x105));
    if (2 < DebugLevel) {
      printk("  uc11vMaxBssidIndicator = %d, uc11vBssidIdx = %d\n");
    }
  }
  AndesAppendCmdMsg(param_3,&local_44,0x1c);
  return;
}

