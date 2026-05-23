// module: mt7915.ko
// function: MtCmdThermalProtect @ 0x1b4c1c
// size: 452 bytes
//

undefined4
MtCmdThermalProtect(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                   byte param_5,char param_6,undefined4 param_7,undefined1 param_8,char param_9,
                   undefined1 param_10)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined1 local_64;
  undefined1 local_63;
  undefined1 local_62;
  undefined1 local_61;
  byte local_60;
  char local_5f;
  undefined4 local_5c;
  undefined1 local_58;
  char local_57;
  undefined1 local_56;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 local_2c;
  
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  iVar1 = (int)param_6;
  uVar3 = (uint)param_5;
  if ((0 < DebugLevel) &&
     (uVar2 = param_7,
     printk("%s: ucBand:%d, HighEn:%d, HighTempTh:%d, LowEn:%d, LowTempTh:%d, RechkTimer:%d\n",
            "MtCmdThermalProtect",param_2,param_3,param_4,uVar3,iVar1,param_7), 0 < DebugLevel)) {
    printk("%s: RFOffEn: %d, RFOffTh: %d, ucType: %d\n","MtCmdThermalProtect",param_8,(int)param_9,
           param_10,uVar3,iVar1,uVar2);
  }
  iVar1 = AndesAllocCmdMsg(param_1,0x14);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_50 = CONCAT13(0x23,CONCAT12(0xed,(undefined2)local_50));
    local_4c = CONCAT31(local_4c._1_3_,8);
    local_4c = CONCAT22(0xffff,(undefined2)local_4c);
    local_3c = local_50;
    uStack_38 = local_4c;
    uStack_34 = local_48;
    uStack_30 = local_44;
    local_2c = local_40;
    AndesInitCmdMsg(iVar1,local_50,local_4c,local_48,local_44,local_40);
    os_zero_mem(&local_64,0x14);
    local_64 = 0;
    local_63 = (undefined1)param_2;
    local_5f = param_6;
    local_62 = (undefined1)param_3;
    local_61 = (undefined1)param_4;
    local_5c = param_7;
    local_60 = param_5;
    local_56 = param_10;
    local_58 = param_8;
    local_57 = param_9;
    AndesAppendCmdMsg(iVar1,&local_64,0x14);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdThermalProtect",uVar2);
  }
  return uVar2;
}

