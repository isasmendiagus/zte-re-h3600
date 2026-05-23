// module: mt7915.ko
// function: EnqueueTPCReq @ 0x13f0fc
// size: 348 bytes
//

void EnqueueTPCReq(int param_1,undefined4 param_2,undefined1 param_3)

{
  int iVar1;
  undefined1 local_3f;
  undefined1 local_3e;
  undefined1 local_3d;
  void *local_3c;
  int local_38;
  int local_34;
  undefined1 auStack_30 [24];
  
  local_3c = (void *)0x0;
  MgtMacHeaderInit(param_1,auStack_30,0xd,0,param_2,param_1 + 0x794b5b,param_1 + 0x794b5b);
  iVar1 = os_alloc_mem(param_1,&local_3c,0x900);
  if (iVar1 != 0) {
    if (2 < DebugLevel) {
      printk("%s() allocate memory failed\n","EnqueueTPCReq");
    }
    return;
  }
  memmove(local_3c,auStack_30,0x18);
  local_38 = 0x18;
  InsertActField(param_1,(int)local_3c + 0x18,&local_38,0,2);
  local_3f = param_3;
  MakeOutgoingFrame((int)local_3c + local_38,&local_34,1,&local_3f,0xffffffff);
  local_38 = local_34 + local_38;
  local_3d = 0x22;
  local_3e = 0;
  MakeOutgoingFrame((int)local_3c + local_38,&local_34,1,&local_3d,1,&local_3e,0xffffffff);
  local_38 = local_34 + local_38;
  MiniportMMRequest(param_1,1,local_3c);
  os_free_mem(local_3c);
  return;
}

