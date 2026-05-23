// module: mt7915.ko
// function: RRM_EnqueueNeighborReq @ 0x21dc78
// size: 252 bytes
//

void RRM_EnqueueNeighborReq(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  void *local_38;
  undefined4 local_34;
  undefined1 auStack_30 [28];
  
  local_38 = (void *)0x0;
  uVar1 = RandomByte();
  iVar2 = os_alloc_mem(param_1,&local_38,0x900);
  if (iVar2 == 0) {
    MgtMacHeaderInit(param_1,auStack_30,0xd,0,param_2,&DAT_0036db73 + param_1,
                     &DAT_00371c92 + param_1);
    if (local_38 != (void *)0x0) {
      memmove(local_38,auStack_30,0x18);
      local_34 = 0x18;
      InsertDialogToken(param_1,(int)local_38 + 0x18,&local_34,uVar1);
      MiniportMMRequest(param_1,0x81,local_38,local_34);
      os_free_mem(local_38);
      return;
    }
  }
  else if (2 < DebugLevel) {
    printk("%s() allocate memory failed\n","RRM_EnqueueNeighborReq");
  }
  return;
}

