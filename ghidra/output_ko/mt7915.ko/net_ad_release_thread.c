// module: mt7915.ko
// function: net_ad_release_thread @ 0x25ae30
// size: 120 bytes
//

int net_ad_release_thread(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 extraout_r3;
  
  if ((param_1 * 0x54 == -0x5f63cc) || (iVar1 = sys_ad_kill_os_task(), iVar1 == 0)) {
    uVar2 = 0;
    iVar1 = 0;
    (&_LANCHOR2)[param_1 * 0x54] = 0;
  }
  else {
    printk("kill test mode tx task failed!\n");
    uVar2 = extraout_r3;
  }
  printk("%s: release thread_idx=%d\n","net_ad_release_thread",param_1,uVar2,param_4);
  return iVar1;
}

