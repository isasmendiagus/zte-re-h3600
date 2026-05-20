// module: mt7915.ko
// function: mt_agent_set_txbf_pfmu_tag_smart_ant @ 0x24dd7c
// size: 68 bytes
//

undefined4 mt_agent_set_txbf_pfmu_tag_smart_ant(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_c;
  
  iVar1 = _kstrtol(param_2,10,&local_c);
  if (iVar1 == 0) {
    uVar2 = mt_serv_set_txbf_pfmu_tag_smart_ant(param_1,local_c);
    return uVar2;
  }
  return 0x104;
}

