// module: mt7915.ko
// function: HwCtrlUpdateBssInfo @ 0xaf658
// size: 68 bytes
//

void HwCtrlUpdateBssInfo(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r2;
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(param_2 + 8);
  if (2 < DebugLevel) {
    printk("%s::CmdThread\n","HwCtrlUpdateBssInfo");
    param_3 = extraout_r2;
  }
  AsicBssInfoUpdate(param_1,uVar1,param_3,param_4);
  return;
}

