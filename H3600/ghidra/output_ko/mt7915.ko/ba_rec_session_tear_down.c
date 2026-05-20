// module: mt7915.ko
// function: ba_rec_session_tear_down @ 0xa6ce4
// size: 268 bytes
//

void ba_rec_session_tear_down(int param_1,uint param_2,undefined4 param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  void *local_28;
  undefined2 local_22;
  undefined4 local_20;
  undefined2 local_1c;
  undefined1 local_1a;
  undefined1 local_19;
  
  uVar1 = HcGetMaxStaNum();
  if (((param_2 < uVar1) && (iVar2 = ba_resrc_rec_del(param_1,param_2,param_3), iVar2 != 0)) &&
     (param_4 == 0)) {
    os_alloc_mem(0,&local_28,0x930);
    if (local_28 == (void *)0x0) {
      if (-1 < DebugLevel) {
        printk("%s():alloc memory failed!\n","ba_rec_session_tear_down");
      }
    }
    else {
      __memzero(&local_22,10);
      __memzero(local_28,0x930);
      iVar2 = param_2 * 0x14c0 + param_1;
      local_20 = *(undefined4 *)(iVar2 + 0xa1e0c);
      local_1c = *(undefined2 *)(iVar2 + 0xa1e10);
      *(undefined4 *)((int)local_28 + 0x908) = 10;
      local_22 = (undefined2)param_2;
      local_1a = (undefined1)param_3;
      local_19 = 0;
      memmove(local_28,&local_22,10);
      MlmeDELBAAction(param_1,local_28);
      os_free_mem(local_28);
    }
  }
  return;
}

