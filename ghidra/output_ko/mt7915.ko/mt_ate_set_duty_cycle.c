// module: mt7915.ko
// function: mt_ate_set_duty_cycle @ 0x27c120
// size: 96 bytes
//

undefined4
mt_ate_set_duty_cycle(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  
  bVar1 = *(byte *)(param_1 + 0xa3ae36);
  iVar3 = net_ad_wrap_service();
  iVar2 = DebugLevel;
  *(undefined4 *)((uint)bVar1 * 0xd18 + iVar3 + 0x10e8) = param_2;
  if (2 < iVar2) {
    printk("%s: Duty cycle=%d%%, control_band_idx=%d\n","mt_ate_set_duty_cycle",param_2,(uint)bVar1,
           param_4);
  }
  return 0;
}

