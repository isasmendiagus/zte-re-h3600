// module: mt7915.ko
// function: mt_agent_set_bw @ 0x24c8cc
// size: 304 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 mt_agent_set_bw(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int local_28;
  undefined *local_24;
  int local_20 [3];
  
  uVar3 = 0;
  local_28 = 0;
  local_24 = &DAT_005f5b58;
  local_20[0] = 0;
  local_20[1] = 0;
  sys_ad_zero_mem(&_LANCHOR1,0x80c);
  printk("%s: Bw = %s\n","mt_agent_set_bw",param_2);
  iVar1 = agent_trtok(param_2,&_LC90);
  if (iVar1 != 0) {
    do {
      iVar1 = _kstrtol(iVar1,10,&local_28);
      if (iVar1 != 0) {
        return 0x104;
      }
      local_20[uVar3] = local_28;
      iVar1 = agent_trtok(0,&_LC90);
      uVar2 = uVar3 & 0xff;
      uVar3 = uVar3 + 1;
    } while (uVar2 != 1 && iVar1 != 0);
  }
  if (local_20[1] == 0) {
    local_20[1] = local_20[0];
    printk("%s: DBW is not specified, alligned with CBW = %d\n","mt_agent_set_bw",local_20[0]);
  }
  FUN_00246ac8(1,4,local_20,&local_24);
  hqa_set_system_bw(param_1,&_LANCHOR1);
  local_24 = &DAT_005f5b58;
  FUN_00246ac8(1,4,local_20 + 1,&local_24);
  hqa_set_per_pkt_bw(param_1,&_LANCHOR1);
  return 0;
}

