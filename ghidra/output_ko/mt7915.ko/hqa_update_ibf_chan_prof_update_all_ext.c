// module: mt7915.ko
// function: hqa_update_ibf_chan_prof_update_all_ext @ 0x247a20
// size: 256 bytes
//

/* WARNING: Type propagation algorithm not settling */

int hqa_update_ibf_chan_prof_update_all_ext(undefined4 param_1,int param_2)

{
  int iVar1;
  int local_20 [3];
  undefined1 auStack_14 [8];
  
  local_20[0] = param_2 + 0xc;
  local_20[1] = 0;
  FUN_002474f4(1,4,local_20,local_20 + 1);
  FUN_002474f4(1,4,local_20,local_20 + 2);
  FUN_002474f4(1,4,local_20,auStack_14);
  FUN_002474f4(1,4,local_20,auStack_14);
  FUN_002474f4(1,4,local_20,auStack_14);
  FUN_002474f4(1,4,local_20,auStack_14);
  iVar1 = mt_serv_set_txbf_profile_data_Write_20m_all(param_1,local_20[2] & 0xff,local_20[0]);
  if (iVar1 == 0) {
    printk("%s: str:%d\n","hqa_update_ibf_chan_prof_update_all_ext",local_20[2]);
  }
  else {
    printk(" hqa_update_ibf_chan_prof_update_all_ext is failed!!\n");
  }
  sys_ad_move_mem((void *)(param_2 + 0xe),local_20 + 1,4);
  FUN_00246b90(param_2,6,iVar1);
  return iVar1;
}

