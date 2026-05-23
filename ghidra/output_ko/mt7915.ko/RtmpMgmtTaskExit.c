// module: mt7915.ko
// function: RtmpMgmtTaskExit @ 0xc4e54
// size: 148 bytes
//

void RtmpMgmtTaskExit(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined8 uVar1;
  
  if (*(int *)(param_1 + 0x285c84) != 0) {
    _raw_spin_lock_bh((int)&DAT_00285c64 + param_1);
    *(undefined4 *)(param_1 + 0x285c60) = 4;
    _raw_spin_unlock_bh((int)&DAT_00285c64 + param_1);
    uVar1 = RtmpOSTaskKill(mt_ate_ampdu_frame + param_1);
    param_2 = (undefined4)((ulonglong)uVar1 >> 0x20);
    param_3 = extraout_r2;
    if (((int)uVar1 == 1) && (-1 < DebugLevel)) {
      printk("kill command task failed!\n");
      param_2 = extraout_r1;
      param_3 = extraout_r2_00;
    }
    *(undefined4 *)(param_1 + 0x285c60) = 0;
  }
  WscThreadExit(param_1,param_2,param_3,param_4);
  return;
}

