// module: mt7915.ko
// function: Set_SCSEnable_Proc @ 0xbe89c
// size: 456 bytes
//

bool Set_SCSEnable_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  char cVar3;
  uint uVar4;
  bool bVar5;
  undefined2 local_32;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  bVar5 = false;
  uVar4 = *(uint *)(*param_1 + 0x3c);
  local_30 = 3;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_32 = 0;
  iVar1 = os_str_tol(param_2,0,10);
  uVar4 = uVar4 & 0xff;
  if (uVar4 < *(byte *)((int)param_1 + 0x2b7242)) {
    iVar2 = HcGetBandByWdev(param_1 + uVar4 * 0x160d + 0xadc92);
    cVar3 = (char)iVar1;
    if ((param_1[0xa5b19] & 0xffffU) == 0x7915) {
      cVar3 = cVar3 + '\x01';
    }
    local_32 = CONCAT11(cVar3,(char)iVar2);
    if (0 < DebugLevel) {
      printk("%s(): BandIdx=%d, SCSEnable=%d\n","Set_SCSEnable_Proc",iVar2,iVar1);
    }
    if (iVar1 == 0) {
      (&DAT_00a7c241)[(int)param_1 + iVar2] = 0;
      *(undefined1 *)((int)param_1 + iVar2 + 0xa7c243) = 0;
    }
    else if (iVar1 == 1) {
      (&DAT_00a7c241)[(int)param_1 + iVar2] = 1;
    }
    iVar1 = AndesAllocCmdMsg(param_1,6);
    bVar5 = iVar1 != 0;
    if (bVar5) {
      local_2c = CONCAT13(0x82,CONCAT12(0xed,(undefined2)local_2c));
      local_28 = CONCAT31(local_28._1_3_,10);
      AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,local_20,local_1c);
      AndesAppendCmdMsg(iVar1,&local_30,4);
      AndesAppendCmdMsg(iVar1,&local_32,2);
      AndesSendCmdMsg(param_1,iVar1);
    }
    if (3 < DebugLevel) {
      printk("%s:(Ret = %d_\n","Set_SCSEnable_Proc",bVar5);
    }
  }
  return bVar5;
}

