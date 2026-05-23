// module: mt7915.ko
// function: rtmp_twt_agrt_update @ 0xb10bc
// size: 104 bytes
//

void rtmp_twt_agrt_update
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 local_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  local_c = param_2;
  uStack_8 = param_3;
  uStack_4 = param_4;
  iVar1 = FUN_000b0a74(param_1,4,0x3d,0x2c,&local_c);
  if ((iVar1 != 0) && (-1 < DebugLevel)) {
    printk("%s::Failed to enqueue cmd\n","rtmp_twt_agrt_update");
  }
  return;
}

