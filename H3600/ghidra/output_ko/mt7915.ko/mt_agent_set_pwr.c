// module: mt7915.ko
// function: mt_agent_set_pwr @ 0x24bd8c
// size: 264 bytes
//

undefined4 mt_agent_set_pwr(int param_1,undefined4 param_2)

{
  uint uVar1;
  uint local_24;
  uint local_20;
  undefined *local_1c;
  
  local_1c = &DAT_005f5b58;
  local_24 = 0;
  local_20 = 0;
  uVar1 = _kstrtol(param_2,10,&local_24);
  if (uVar1 == 0) {
    local_20 = local_24;
    FUN_00246ac8(1,4,&local_20,&local_1c);
    local_20 = (uint)*(byte *)(param_1 + 0x4cc);
    FUN_00246ac8(1,4,&local_20,&local_1c);
    local_20 = (uint)*(byte *)((uint)*(byte *)(param_1 + 0x4cc) * 0xd18 + param_1 + 0x1130);
    FUN_00246ac8(1,4,&local_20,&local_1c);
    local_20 = (uint)*(byte *)((uint)*(byte *)(param_1 + 0x4cc) * 0xd18 + param_1 + 0x1131);
    FUN_00246ac8(1,4,&local_20,&local_1c);
    local_20 = uVar1;
    FUN_00246ac8(1,4,&local_20,&local_1c);
    hqa_set_tx_power_ext(param_1,&_LANCHOR1);
    return 0;
  }
  return 0x104;
}

