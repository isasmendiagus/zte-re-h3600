// module: mt7915.ko
// function: MtCmdRfTestGetTxTonePower @ 0x1aeee8
// size: 160 bytes
//

void MtCmdRfTestGetTxTonePower
               (undefined4 param_1,undefined4 param_2,uint param_3,undefined1 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 auStack_c8 [76];
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined1 auStack_64 [76];
  
  if (2 < DebugLevel) {
    printk("%s, TxAntennaSel: %d\n","MtCmdRfTestGetTxTonePower");
  }
  os_zero_mem(&local_70,0x58);
  uVar1 = local_68;
  if (4 < param_3) {
    param_3 = param_3 - 1;
  }
  local_70 = CONCAT31(local_70._1_3_,1);
  local_6c = 0x13;
  local_68 = CONCAT31(local_68._1_3_,(char)param_3);
  uVar2 = local_68;
  local_68._3_1_ = SUB41(uVar1,3);
  local_68._0_3_ = CONCAT12(param_4,(short)uVar2);
  local_78 = 8;
  local_7c = param_2;
  memcpy(auStack_c8,auStack_64,0x4c);
  FUN_001abb34(param_1,local_70,local_6c,local_68);
  return;
}

