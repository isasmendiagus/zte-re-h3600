// module: mt7915.ko
// function: AsicAutoBATrigger @ 0x198008
// size: 4 bytes
//

undefined4 AsicAutoBATrigger(undefined4 param_1,undefined1 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  
  uStack_3c = 0;
  uStack_38 = 0;
  uStack_30 = 0;
  uStack_2c = 0;
  uStack_28 = 0;
  uStack_24 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,8);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    uStack_30 = CONCAT31(uStack_30._1_3_,8);
    uStack_34 = 0x51ed0002;
    AndesInitCmdMsg(iVar1,0x51ed0002,uStack_30,uStack_2c,uStack_28,uStack_24);
    uStack_3c = CONCAT31((uint3)uStack_3c._2_2_ << 8,param_2);
    uStack_38 = param_3;
    AndesAppendCmdMsg(iVar1,&uStack_3c,8);
    uVar2 = AndesSendCmdMsg(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d)\n","CmdAutoBATrigger",uVar2);
  }
  return uVar2;
}

