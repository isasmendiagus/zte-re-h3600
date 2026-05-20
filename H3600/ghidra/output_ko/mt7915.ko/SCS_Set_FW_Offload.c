// module: mt7915.ko
// function: SCS_Set_FW_Offload @ 0x238880
// size: 248 bytes
//

bool SCS_Set_FW_Offload(int param_1,uint param_2)

{
  int iVar1;
  bool bVar2;
  undefined2 local_2c [2];
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_2c[0] = (undefined2)param_2;
  (&DAT_00a7c241)[param_1 + (param_2 & 0xff)] = (char)(param_2 >> 8);
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_28 = 3;
  iVar1 = AndesAllocCmdMsg(param_1,6);
  bVar2 = iVar1 != 0;
  if (bVar2) {
    local_24 = CONCAT13(0x82,CONCAT12(0xed,(undefined2)local_24));
    local_20 = CONCAT31(local_20._1_3_,10);
    AndesInitCmdMsg(iVar1,local_24,local_20,local_1c,local_18,local_14);
    AndesAppendCmdMsg(iVar1,&local_28,4);
    AndesAppendCmdMsg(iVar1,local_2c,2);
    AndesSendCmdMsg(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d_\n","SCS_Set_FW_Offload",bVar2);
  }
  return bVar2;
}

