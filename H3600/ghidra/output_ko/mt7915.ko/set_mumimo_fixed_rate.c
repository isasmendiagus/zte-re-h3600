// module: mt7915.ko
// function: set_mumimo_fixed_rate @ 0x178570
// size: 276 bytes
//

undefined4 set_mumimo_fixed_rate(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 local_2c;
  undefined2 local_2a;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_2a = 0;
  local_28 = 0x11;
  local_2c = 10;
  if (param_2 != 0) {
    local_2a = os_str_tol(param_2,0,10);
    iVar1 = AndesAllocCmdMsg(param_1,8);
    if (iVar1 != 0) {
      local_20 = CONCAT31(local_20._1_3_,10);
      uVar2 = 1;
      local_24 = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_24));
      AndesInitCmdMsg(iVar1,local_24,local_20,local_1c,local_18,local_14);
      AndesAppendCmdMsg(iVar1,&local_28,4);
      AndesAppendCmdMsg(iVar1,&local_2c,2);
      AndesAppendCmdMsg(iVar1,&local_2a,2);
      AndesSendCmdMsg(param_1,iVar1);
      goto LAB_0017864c;
    }
  }
  uVar2 = 0;
LAB_0017864c:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d_\n","set_mumimo_fixed_rate",uVar2);
  }
  return uVar2;
}

