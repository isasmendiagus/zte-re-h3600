// module: mt7915.ko
// function: StaRecUpdateBasic @ 0x1c34c0
// size: 468 bytes
//

undefined4 StaRecUpdateBasic(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  uint local_28;
  undefined4 local_24;
  
  iVar3 = *(int *)(param_3 + 0x9c);
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  iVar1 = GetStaCfgByWdev(param_1,*(undefined4 *)
                                   (param_1 + (uint)*(ushort *)(param_3 + 2) * 0x620 + 0x2f6a4));
  local_30 = *(undefined4 *)(param_3 + 8);
  local_24 = CONCAT22(1,(undefined2)local_24);
  if (*(char *)(param_3 + 0x10) != '\0') {
    local_24 = CONCAT22(3,(undefined2)local_24);
  }
  local_2c = CONCAT31(local_2c._1_3_,*(undefined1 *)(param_3 + 4));
  local_34 = 0x140000;
  if (iVar3 == 0) {
    if (iVar1 != 0) {
      puVar2 = (undefined1 *)HcGetEdca(param_1,iVar1);
      if (puVar2 == (undefined1 *)0x0) {
        local_2c = CONCAT22(*(undefined2 *)(iVar1 + 0x40b0),(undefined2)local_2c);
      }
      else {
        local_2c._0_2_ = CONCAT11(*puVar2,(undefined1)local_2c);
        local_2c = CONCAT22(*(undefined2 *)(iVar1 + 0x40b0),(undefined2)local_2c);
      }
    }
    os_move_mem(&local_28,&BROADCAST_ADDR,6);
  }
  else {
    local_2c = CONCAT22(*(undefined2 *)(iVar3 + 0xf8),
                        CONCAT11((char)*(undefined4 *)(iVar3 + 0xb4),*(undefined1 *)(param_3 + 4)))
               & 0xffff01ff;
    if (iVar1 != 0) {
      puVar2 = (undefined1 *)HcGetEdca(param_1,iVar1);
      if (puVar2 == (undefined1 *)0x0) {
        local_2c = CONCAT22(*(undefined2 *)(iVar1 + 0x40b0),(undefined2)local_2c);
      }
      else {
        local_2c._0_2_ = CONCAT11(*puVar2,(undefined1)local_2c);
        local_2c = CONCAT22(*(undefined2 *)(iVar1 + 0x40b0),(undefined2)local_2c);
      }
    }
    os_move_mem(&local_28,(void *)(iVar3 + 0xec),6);
  }
  if (3 < DebugLevel) {
    printk("%s(CMD_STAREC_COMMON_T), u4ConnectionType = %d, ucConnectionState = %d, ucIsQBSS = %d, u2AID = %d, aucPeerMacAddr = %02x:%02x:%02x:%02x:%02x:%02x\n"
           ,"StaRecUpdateBasic",local_30,local_2c & 0xff,local_2c >> 8 & 0xff,local_2c >> 0x10,
           local_28 & 0xff,local_28 >> 8 & 0xff,local_28 >> 0x10 & 0xff,local_28 >> 0x18,
           local_24 & 0xff,local_24 >> 8 & 0xff);
  }
  AndesAppendCmdMsg(param_2,&local_34,0x14);
  return 0;
}

