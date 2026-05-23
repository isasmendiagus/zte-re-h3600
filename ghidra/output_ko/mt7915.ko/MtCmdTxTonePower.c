// module: mt7915.ko
// function: MtCmdTxTonePower @ 0x1aee40
// size: 164 bytes
//

void MtCmdTxTonePower(undefined4 param_1,undefined4 param_2,undefined4 param_3,uint param_4,
                     undefined1 param_5)

{
  uint local_c8 [18];
  undefined4 local_80;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 uStack_6c;
  undefined1 auStack_68 [76];
  
  os_zero_mem(&local_74,0x54);
  if (2 < DebugLevel) {
    local_c8[0] = param_4;
    printk("%s, type:%d, dec:%d, TxAntennaSel: %d\n","MtCmdTxTonePower",param_2,param_3);
  }
  if (4 < param_4) {
    param_4 = param_4 - 1;
  }
  local_70._0_3_ = CONCAT12(param_5,CONCAT11((char)param_3,(char)param_4));
  local_80 = 8;
  local_74 = param_2;
  memcpy(local_c8,auStack_68,0x48);
  FUN_001ac150(param_1,local_74,local_70,uStack_6c);
  return;
}

