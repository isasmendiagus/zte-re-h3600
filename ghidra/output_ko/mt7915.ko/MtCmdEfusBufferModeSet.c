// module: mt7915.ko
// function: MtCmdEfusBufferModeSet @ 0x1b477c
// size: 608 bytes
//

void MtCmdEfusBufferModeSet(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined1 *local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  code *local_40;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  code *local_2c;
  
  local_54 = (undefined1 *)0x0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = (code *)0x0;
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  os_alloc_mem(param_1,&local_54,0x404);
  if (local_54 == (undefined1 *)0x0) {
LAB_001b49bc:
    uVar6 = 3;
  }
  else {
    uVar5 = 0;
    uVar3 = (uint)(*(ushort *)(iVar1 + 0xf6) >> 10);
    if ((*(ushort *)(iVar1 + 0xf6) & 0x3ff) != 0) {
      uVar3 = uVar3 + 1;
    }
    uVar4 = uVar3 - 1 & 0xff;
    do {
      iVar1 = AndesAllocCmdMsg(param_1,0x404);
      uVar6 = 1;
      if (iVar1 == 0) goto LAB_001b49bc;
      local_4c = CONCAT31(local_4c._1_3_,0xd);
      local_4c = CONCAT22(8,(undefined2)local_4c);
      local_50 = 0x21ed0000;
      local_48 = CONCAT22(local_48._2_2_,60000);
      local_44 = 0;
      local_40 = CmdEfuseBufferModeRsp;
      local_3c = 0x21ed0000;
      uStack_38 = local_4c;
      uStack_34 = local_48;
      uStack_30 = 0;
      local_2c = CmdEfuseBufferModeRsp;
      AndesInitCmdMsg(iVar1,0x21ed0000,local_4c,local_48,0,CmdEfuseBufferModeRsp);
      os_zero_mem(local_54,0x404);
      local_54[1] = 1;
      local_54[1] = (byte)((uVar3 - 1 & 7) << 5) | local_54[1];
      local_54[1] = (byte)((uVar5 & 7) << 2) | local_54[1];
      if (param_2 == 1) {
        *local_54 = 0;
        *(undefined2 *)(local_54 + 2) = 0;
        uVar5 = uVar4;
      }
      else {
        if (param_2 != 2) {
          AndesFreeCmdMsg(iVar1);
          break;
        }
        *local_54 = 1;
        if (*(code **)(iVar2 + 0xd4) == (code *)0x0) {
          *local_54 = 0;
          *(undefined2 *)(local_54 + 2) = 0;
        }
        else {
          (**(code **)(iVar2 + 0xd4))(param_1,local_54);
        }
      }
      AndesAppendCmdMsg(iVar1,local_54,0x404);
      uVar5 = uVar5 + 1 & 0xff;
      uVar6 = chip_cmd_tx(param_1,iVar1);
    } while (uVar5 <= uVar4);
  }
  if (local_54 != (undefined1 *)0x0) {
    os_free_mem();
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdEfusBufferModeSet",uVar6);
  }
  return;
}

