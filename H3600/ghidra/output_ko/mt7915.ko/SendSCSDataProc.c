// module: mt7915.ko
// function: SendSCSDataProc @ 0xbe2cc
// size: 332 bytes
//

undefined4 SendSCSDataProc(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined1 local_24;
  undefined1 local_23;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_3c = 0;
  if (param_1 != -0xa7c240) {
    if ((&DAT_00a7c241)[param_1] == '\x01') {
      local_18 = *(undefined4 *)(param_1 + 0xa7c258);
      local_20 = *(undefined4 *)(param_1 + 0xa7c250);
      local_24 = *(undefined1 *)(param_1 + 0xa7c245);
    }
    if (*(char *)(param_1 + 0xa7c242) == '\x01') {
      local_14 = *(undefined4 *)(param_1 + 0xa7c25c);
      local_1c = *(undefined4 *)(param_1 + 0xa7c254);
      local_23 = *(undefined1 *)(param_1 + 0xa7c246);
    }
    iVar1 = AndesAllocCmdMsg(param_1,0x18);
    if (iVar1 != 0) {
      uVar2 = 1;
      local_38 = CONCAT13(0x82,CONCAT12(0xed,(undefined2)local_38));
      local_34 = CONCAT31(local_34._1_3_,10);
      AndesInitCmdMsg(iVar1,local_38,local_34,local_30,local_2c,local_28);
      AndesAppendCmdMsg(iVar1,&local_3c,4);
      AndesAppendCmdMsg(iVar1,&local_24,0x14);
      AndesSendCmdMsg(param_1,iVar1);
      goto LAB_000be3a0;
    }
  }
  uVar2 = 0;
LAB_000be3a0:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d_\n","SendSCSDataProc",uVar2);
  }
  return uVar2;
}

