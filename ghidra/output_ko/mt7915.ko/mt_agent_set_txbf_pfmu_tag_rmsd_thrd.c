// module: mt7915.ko
// function: mt_agent_set_txbf_pfmu_tag_rmsd_thrd @ 0x24de04
// size: 68 bytes
//

undefined4 mt_agent_set_txbf_pfmu_tag_rmsd_thrd(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_c [4];
  
  iVar1 = _kstrtol(param_2,10,local_c);
  if (iVar1 == 0) {
    uVar2 = mt_serv_set_txbf_pfmu_tag_rmsd_thrd(param_1,local_c[0]);
    return uVar2;
  }
  return 0x104;
}

