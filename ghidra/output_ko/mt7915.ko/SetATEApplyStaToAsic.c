// module: mt7915.ko
// function: SetATEApplyStaToAsic @ 0x264748
// size: 516 bytes
//

undefined4 SetATEApplyStaToAsic(int param_1)

{
  byte bVar1;
  undefined2 uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 local_50;
  undefined4 uStack_4c;
  uint local_48;
  uint local_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  bVar1 = *(byte *)(param_1 + 0xa7865d);
  uVar4 = (uint)bVar1;
  if (*(ushort *)("Get_System_CapNode_Info" + param_1 + 8) == 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: PSE not init yet!\n","SetATEApplyStaToAsic");
    return 0;
  }
  if (uVar4 < *(ushort *)("Get_System_CapNode_Info" + param_1 + 8)) {
    os_zero_mem(&local_50,0x30);
    local_50 = CONCAT22(local_50._2_2_,(ushort)bVar1);
    os_move_mem(&uStack_40,(void *)(param_1 + 0xa78654),6);
    if ((uVar4 != 0) &&
       (uVar3 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0)), uVar4 != uVar3)) {
      local_44 = (uint)(*(char *)(param_1 + 0xa7865b) != '\x01');
      uStack_4c._0_2_ = CONCAT11(*(undefined1 *)(param_1 + 0xa7865c),(undefined1)uStack_4c);
      local_28 = CONCAT31(local_28._1_3_,1);
      if ((*(byte *)(param_1 + 0xa7865e) & 0x18) != 0) {
        uStack_2c._0_2_ = CONCAT11(1,(undefined1)uStack_2c);
        uVar2 = (undefined2)uStack_2c;
        local_48 = local_48 & 0xffffff00;
        uStack_4c._0_3_ = (uint3)(ushort)uStack_4c;
        uStack_4c = CONCAT13(3,(uint3)uStack_4c);
        if ((*(byte *)(param_1 + 0xa7865e) & 0x20) != 0) {
          uStack_2c._0_3_ = CONCAT12(1,uVar2);
        }
        uStack_2c = CONCAT13(1,(undefined3)uStack_2c);
      }
      goto LAB_002647d4;
    }
  }
  else {
    os_zero_mem(&local_50,0x30);
    uVar4 = 0;
    local_50 = (uint)local_50._2_2_ << 0x10;
    os_move_mem(&uStack_40,(void *)(param_1 + 0xa78654),6);
  }
  uStack_4c._0_2_ = CONCAT11(0xe,(undefined1)uStack_4c);
  local_44 = 3;
LAB_002647d4:
  local_38 = 0;
  local_50 = CONCAT22(*(undefined2 *)(param_1 + 0xa78666),(undefined2)local_50);
  local_34._0_2_ =
       CONCAT11(*(undefined1 *)(param_1 + 0xa78664),(char)*(undefined2 *)(param_1 + 0xa78662));
  if (2 < DebugLevel) {
    printk("%s: Update WTBL table, WCID=%d, Addr=%02x:%02x:%02x:%02x:%02x:%02x, WtblInfo.MacAddrIdx=%d\n"
           ,"SetATEApplyStaToAsic",uVar4,*(undefined1 *)(param_1 + 0xa78654),
           *(undefined1 *)(param_1 + 0xa78655),*(undefined1 *)(param_1 + 0xa78656),
           *(undefined1 *)(param_1 + 0xa78657),*(undefined1 *)(param_1 + 0xa78658),
           *(undefined1 *)(param_1 + 0xa78659),uStack_4c >> 8 & 0xff);
  }
  AsicUpdateRxWCIDTableDetail
            (param_1,local_50,uStack_4c,local_48,local_44,uStack_40,uStack_3c,local_38,local_34,
             uStack_30,uStack_2c,local_28,local_24);
  return 1;
}

