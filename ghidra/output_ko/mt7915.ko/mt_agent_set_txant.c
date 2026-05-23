// module: mt7915.ko
// function: mt_agent_set_txant @ 0x24ce20
// size: 424 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 mt_agent_set_txant(int param_1,char *param_2)

{
  char *pcVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined *puStack_2c;
  uint local_28;
  uint local_24;
  uint local_20 [3];
  
  uVar4 = 0;
  puStack_2c = &DAT_005f5b58;
  local_28 = 0;
  local_24 = 0;
  sys_ad_zero_mem(&_LANCHOR1,0x80c);
  printk("%s: TX PATH = %s\n","mt_agent_set_txant",param_2);
  pcVar1 = strchr(param_2,0x3a);
  if (pcVar1 == (char *)0x0) {
    DAT_005f5b54 = 8;
    iVar2 = _kstrtol(param_2,10,&local_24);
    if (iVar2 != 0) {
      return 0x104;
    }
    local_28 = local_24;
    FUN_00246ac8(1,4,&local_28,&puStack_2c);
    local_28 = (uint)*(byte *)(param_1 + 0x4cc);
    FUN_00246ac8(1,4,&local_28,&puStack_2c);
    hqa_set_tx_path(param_1,&_LANCHOR1);
  }
  else {
    local_20[0] = 0;
    local_20[1] = 0;
    iVar2 = agent_trtok(param_2,&_LC90);
    if (iVar2 != 0) {
      do {
        iVar2 = _kstrtol(iVar2,10,&local_24);
        if (iVar2 != 0) {
          return 0x104;
        }
        local_20[uVar4] = local_24;
        iVar2 = agent_trtok(0,&_LC90);
        uVar3 = uVar4 & 0xff;
        uVar4 = uVar4 + 1;
      } while (uVar3 != 1 && iVar2 != 0);
    }
    if (local_20[0] != 0) {
      local_20[1] = local_20[1] | 0x80000000;
      DAT_005f5b54 = 8;
      FUN_00246ac8(1,4,local_20 + 1,&puStack_2c);
      local_28 = (uint)*(byte *)(param_1 + 0x4cc);
      FUN_00246ac8(1,4,&local_28,&puStack_2c);
      hqa_set_tx_path(param_1,&_LANCHOR1);
    }
  }
  return 0;
}

