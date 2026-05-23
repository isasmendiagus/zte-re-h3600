// module: mt7915.ko
// function: MtAsicUpdateRxWCIDTableByFw @ 0x198198
// size: 1564 bytes
//

void MtAsicUpdateRxWCIDTableByFw
               (int param_1,uint param_2,uint param_3,uint param_4,uint param_5,undefined4 param_6,
               undefined4 param_7,int param_8,undefined4 param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,char param_13)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined1 local_d1;
  int local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  uint local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  uint3 local_68;
  undefined1 uStack_65;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined2 uStack_a;
  undefined1 local_7;
  char local_6;
  undefined1 local_5;
  undefined1 local_4;
  undefined1 local_3;
  char local_2;
  
  local_d0 = 0;
  local_cc = 0;
  local_d1 = 0;
  local_78 = 0;
  local_74 = 0;
  local_70 = 0;
  local_6c = 0;
  _local_68 = 0;
  local_90 = 0;
  local_8c = 0;
  local_88 = 0;
  local_c8 = 0;
  local_c4 = 0;
  local_c0 = 0;
  local_bc = 0;
  local_b8 = 0;
  local_b4 = 0;
  local_b0 = 0;
  local_ac = 0;
  local_64 = 0;
  local_60 = 0;
  local_5c = 0;
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_a8 = 0;
  local_a4 = 0;
  local_84 = 0;
  local_80 = 0;
  local_7c = 0;
  local_a0 = 0;
  local_9c = 0;
  local_98 = 0;
  local_94 = 0;
  iVar3 = os_alloc_mem(param_1,&local_d0,0xf8);
  uStack_a = (undefined2)(param_2 >> 0x10);
  if (DebugLevel < 3) {
    if (iVar3 != 0) {
      return;
    }
  }
  else {
    printk("%s(): %d,%d,%d,%d,%d,%d,%d,%d,%d,(%02x:%02x:%02x:%02x:%02x:%02x),%d,%d,%d,%d,%d,%d)\n",
           "MtAsicUpdateRxWCIDTableByFw",param_2 & 0xffff,uStack_a,param_3 & 0xff,
           param_3 >> 8 & 0xff,param_3 >> 0x10 & 0xff,param_3 >> 0x18,param_4 & 0xff,param_5,
           param_4 >> 8 & 0xff,(undefined1)param_6,param_6._1_1_,param_6._2_1_,param_6._3_1_,
           (undefined1)param_7,param_7._1_1_,param_8,(undefined1)param_9,param_11._1_1_,
           param_11._2_1_,param_11._3_1_,(char)param_12);
    if (iVar3 != 0) goto LAB_00198688;
  }
  if (local_d0 == 0) goto LAB_00198688;
  local_8c._0_3_ = CONCAT12(param_9._3_1_,(undefined2)local_8c);
  local_8c = CONCAT13((undefined1)param_10,(undefined3)local_8c);
  if (param_5 == 4) {
    if ((*(byte *)(param_1 + 0x286294) & 3) == 3) {
      iVar5 = HcGetWcidLinkType(param_1,param_2 & 0xffff);
      if (iVar5 == 2) {
        local_8c = CONCAT31(local_8c._1_3_,1);
      }
      goto LAB_00198378;
    }
LAB_00198380:
    uVar2 = local_60;
    local_7 = (undefined1)(param_3 >> 8);
    local_3 = (undefined1)(param_4 >> 8);
    local_6c._0_2_ = CONCAT11((char)param_12 != '\0',(undefined1)local_6c);
    local_70._0_3_ = CONCAT12(local_7,(undefined2)local_70);
    _local_68 = CONCAT22(stack0xffffff9a,uStack_a);
    if (param_5 - 4 < 2 || (param_5 & 0xfffffffd) == 0) {
      local_8c._0_2_ = CONCAT11(1,(undefined1)local_8c);
    }
    _local_68 = CONCAT13(local_3,local_68);
    local_8c._0_3_ = CONCAT12(1,(undefined2)local_8c);
    local_8c = CONCAT13(1,(undefined3)local_8c);
    local_60 = CONCAT13((char)param_8,(undefined3)local_60);
    local_60._0_2_ = CONCAT11(param_8 != 0,(char)uVar2);
    uVar1 = local_ac._2_2_;
    switch(param_5) {
    case 0:
      local_ac = (uint)local_ac._2_2_ << 0x10;
      local_ac = CONCAT31(local_ac._1_3_,1);
      break;
    case 1:
      local_ac = CONCAT22(local_ac._2_2_,0x100);
      if (param_12._3_1_ != '\0') goto LAB_00198428;
      break;
    case 2:
    case 5:
      local_ac = (uint)local_ac._2_2_ << 0x10;
      local_ac = CONCAT31(local_ac._1_3_,1);
      if (param_12._3_1_ != '\0') {
        local_ac = CONCAT22(uVar1,0x101);
      }
      break;
    default:
      if (2 < DebugLevel) {
        printk("%s: Unknown entry type(%d) do not support header translation\n",
               "MtAsicUpdateRxWCIDTableByFw");
      }
      break;
    case 6:
LAB_00198428:
      local_ac = CONCAT22(local_ac._2_2_,0x100);
      local_ac = CONCAT31(local_ac._1_3_,1);
    }
    uVar4 = local_bc;
    local_ac._0_3_ = CONCAT12(param_12._1_1_ != '\0',(undefined2)local_ac);
    if (param_11._1_1_ != '\0') {
      local_6c._0_2_ = CONCAT11(1,(undefined1)local_6c);
      local_c4 = CONCAT31(local_c4._1_3_,1);
      if (param_11._3_1_ != '\0') {
        local_a4 = CONCAT22(local_a4._2_2_,0x100);
        local_a4 = CONCAT31(local_a4._1_3_,1);
      }
      local_6 = (char)(param_3 >> 0x10);
      local_4 = (undefined1)param_4;
      local_5 = (undefined1)(param_3 >> 0x18);
      local_68 = (uint3)(ushort)local_68;
      local_9c = CONCAT31(local_9c._1_3_,local_6 == '\x01');
      local_c4 = CONCAT13(local_4,CONCAT12(local_5,(undefined2)local_c4));
      if (param_11._2_1_ != '\0') {
        local_2 = (char)(param_4 >> 0x10);
        local_bc = CONCAT13(local_bc._3_1_,0x10000);
        local_bc._0_2_ = CONCAT11(local_2 == '\x02',(char)uVar4);
      }
    }
  }
  else {
LAB_00198378:
    if (param_5 != 3) goto LAB_00198380;
    local_70._0_3_ = CONCAT12(0xe,(undefined2)local_70);
    local_8c._0_2_ = CONCAT11(1,(undefined1)local_8c);
    local_8c._0_3_ = CONCAT12(1,(undefined2)local_8c);
    local_8c = CONCAT13(1,(undefined3)local_8c);
    local_60 = local_60 & 0xffffff;
    if (*(char *)(param_1 + 0x286285) == '\x01') {
      local_ac = (uint)CONCAT21(local_ac._2_2_,1) << 8;
    }
  }
  os_move_mem(&local_74,&param_6,6);
  local_7c = CONCAT31(CONCAT21(local_7c._2_2_,(undefined1)param_9),param_9._2_1_);
  local_94 = CONCAT31(local_94._1_3_,param_9._1_1_);
  local_b4 = local_b4 & 0xffffff00;
  local_80._0_2_ = CONCAT11(param_10._2_1_,param_10._1_1_);
  local_80 = CONCAT13((undefined1)param_11,CONCAT12(param_10._3_1_,(undefined2)local_80));
  uVar4 = pTlvAppend(local_d0,0,0x14,&local_78,&local_cc,&local_d1);
  uVar4 = pTlvAppend(uVar4,1,0xc,&local_90,&local_cc,&local_d1);
  uVar4 = pTlvAppend(uVar4,2,8,&local_c8,&local_cc,&local_d1);
  uVar4 = pTlvAppend(uVar4,9,8,&local_a8,&local_cc,&local_d1);
  uVar4 = pTlvAppend(uVar4,0xd,8,&local_a0,&local_cc,&local_d1);
  uVar4 = pTlvAppend(uVar4,3,8,&local_c0,&local_cc,&local_d1);
  uVar4 = pTlvAppend(uVar4,5,8,&local_b8,&local_cc,&local_d1);
  uVar4 = pTlvAppend(uVar4,6,8,&local_b0,&local_cc,&local_d1);
  if (param_13 == '\0') {
    uVar4 = pTlvAppend(uVar4,7,0x2c,&local_64,&local_cc,&local_d1);
  }
  if (*(short *)(param_1 + 0xa78698) != -1) {
    uVar4 = pTlvAppend(uVar4,0xc,0xc,&local_84,&local_cc,&local_d1);
  }
  pTlvAppend(uVar4,0x10,8,&local_98,&local_cc,&local_d1);
  if ((param_13 == '\0') || (param_12._2_1_ == '\x01')) {
    CmdExtWtblUpdate(param_1,param_2 & 0xffff,1,local_d0,local_cc);
  }
  else {
    CmdExtWtblUpdate(param_1,param_2 & 0xffff,2,local_d0,local_cc);
  }
  if (local_d0 != 0) {
    os_free_mem();
  }
LAB_00198688:
  if (2 < DebugLevel) {
    printk("%s:(Ret = %d)\n","MtAsicUpdateRxWCIDTableByFw",iVar3);
  }
  return;
}

