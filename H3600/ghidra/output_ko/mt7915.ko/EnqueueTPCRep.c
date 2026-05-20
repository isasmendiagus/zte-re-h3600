// module: mt7915.ko
// function: EnqueueTPCRep @ 0x13f25c
// size: 320 bytes
//

void EnqueueTPCRep(int param_1,undefined4 param_2,undefined1 param_3,undefined4 param_4,
                  undefined1 param_5)

{
  int iVar1;
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
      printk("%s() allocate memory failed\n","EnqueueTPCRep");
    }
    return;
  }
  memmove(local_3c,auStack_30,0x18);
  local_38 = 0x18;
  InsertActField(param_1,(int)local_3c + 0x18,&local_38,0,3);
  local_3d = param_3;
  MakeOutgoingFrame((int)local_3c + local_38,&local_34,1,&local_3d,0xffffffff);
  local_38 = local_34 + local_38;
  InsertTpcReportIE(param_1,(int)local_3c + local_38,&local_38,param_4,param_5);
  MiniportMMRequest(param_1,1,local_3c,local_38);
  os_free_mem(local_3c);
  return;
}

