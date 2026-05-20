// module: mt7915.ko
// function: hqa_update_ibf_chan_prof_update_ext @ 0x24e6b8
// size: 520 bytes
//

/* WARNING: Type propagation algorithm not settling */

int hqa_update_ibf_chan_prof_update_ext(undefined4 param_1,int param_2)

{
  int iVar1;
  int local_60 [3];
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  char *local_2c [2];
  
  local_60[0] = param_2 + 0xc;
  local_60[1] = 0;
  iVar1 = sys_ad_alloc_mem(local_2c,0x200);
  if (iVar1 == 0) {
    sys_ad_zero_mem(local_2c[0],0x200);
    FUN_002474f4(1,4,local_60,local_60 + 1);
    FUN_002474f4(1,4,local_60,local_60 + 2);
    FUN_002474f4(1,4,local_60,&local_54);
    FUN_002474f4(1,4,local_60,&local_50);
    FUN_002474f4(1,4,local_60,&local_4c);
    FUN_002474f4(1,4,local_60,&local_48);
    FUN_002474f4(1,4,local_60,&local_44);
    FUN_002474f4(1,4,local_60,&local_40);
    FUN_002474f4(1,4,local_60,&local_3c);
    FUN_002474f4(1,4,local_60,&local_38);
    FUN_002474f4(1,4,local_60,&local_34);
    FUN_002474f4(1,4,local_60,&local_30);
    sprintf(local_2c[0],"%03x:%03x:%03x:%03x:%03x:%03x:%03x:%03x:%03x:%03x:%03x",local_60[2],
            local_54,local_50,local_4c,local_48,local_44,local_40,local_3c,local_38,local_34,
            local_30);
    iVar1 = mt_agent_set_txbf_chan_profile_update(param_1,local_2c[0]);
    if (iVar1 == 0) {
      printk(" hqa_update_ibf_chan_prof_update_ext is failed!!\n");
    }
  }
  else {
    printk("CMD can\'t be created!!\n");
  }
  sys_ad_move_mem((void *)(param_2 + 0xe),local_60 + 1,4);
  FUN_00246b90(param_2,6,iVar1);
  if (local_2c[0] != (char *)0x0) {
    sys_ad_free_mem();
  }
  return iVar1;
}

