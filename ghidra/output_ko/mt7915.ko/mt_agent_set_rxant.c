// module: mt7915.ko
// function: mt_agent_set_rxant @ 0x24c3dc
// size: 208 bytes
//

undefined4 mt_agent_set_rxant(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined *local_24;
  uint local_20;
  uint local_1c [2];
  
  local_1c[0] = 0;
  local_20 = 0;
  local_24 = &DAT_005f5b58;
  sys_ad_zero_mem(&_LANCHOR1,0x80c);
  printk("%s: RX PATH = %s\n","mt_agent_set_rxant",param_2);
  DAT_005f5b54 = 8;
  iVar1 = _kstrtol(param_2,10,local_1c);
  if (iVar1 == 0) {
    local_20 = local_1c[0];
    FUN_00246ac8(1,4,&local_20,&local_24);
    local_20 = (uint)*(byte *)(param_1 + 0x4cc);
    FUN_00246ac8(1,4,&local_20,&local_24);
    hqa_set_rx_path(param_1,&_LANCHOR1);
    return 0;
  }
  return 0x104;
}

