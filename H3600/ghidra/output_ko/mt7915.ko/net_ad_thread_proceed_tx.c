// module: mt7915.ko
// function: net_ad_thread_proceed_tx @ 0x25ac9c
// size: 96 bytes
//

void net_ad_thread_proceed_tx(int param_1,int param_2)

{
  byte bVar1;
  
  _raw_spin_lock_bh(&DAT_005f63fc);
  if (*(char *)(param_1 + 0x34) == '\0' || param_2 != 1) {
    bVar1 = 1;
  }
  else {
    bVar1 = 2;
  }
  DAT_005f6400 = bVar1 | DAT_005f6400;
  _raw_spin_unlock_bh(&DAT_005f63fc);
  sys_ad_wakeup_os_task(&DAT_005f63cc);
  return;
}

