// module: mt7915.ko
// function: EnqueueMeasurementRep @ 0x13ef1c
// size: 476 bytes
//

void EnqueueMeasurementRep
               (int param_1,undefined4 param_2,undefined1 param_3,undefined1 param_4,
               undefined1 param_5,undefined1 param_6,char param_7,int param_8)

{
  int iVar1;
  uint uVar2;
  byte *pbVar3;
  byte *pbVar4;
  undefined4 uVar5;
  undefined1 local_52;
  byte local_51 [3];
  undefined1 local_4e;
  undefined1 local_4d;
  void *local_4c;
  int local_48;
  int local_44;
  undefined1 auStack_40 [28];
  
  local_4c = (void *)0x0;
  MgtMacHeaderInit(param_1,auStack_40,0xd,0,param_2,param_1 + 0x794b5b,param_1 + 0x794b5b);
  iVar1 = os_alloc_mem(param_1,&local_4c,0x900);
  if (iVar1 != 0) {
    if (2 < DebugLevel) {
      printk("%s() allocate memory failed\n","EnqueueMeasurementRep");
    }
    return;
  }
  memmove(local_4c,auStack_40,0x18);
  local_48 = 0x18;
  InsertActField(param_1,(int)local_4c + 0x18,&local_48,0,1);
  local_52 = param_3;
  MakeOutgoingFrame((int)local_4c + local_48,&local_44,1,&local_52,0xffffffff);
  local_48 = local_48 + local_44;
  __memzero(local_51 + 2,3);
  local_51[0] = param_7 + 3;
  uVar2 = (uint)local_51[0];
  pbVar3 = local_51;
  iVar1 = (int)local_4c + local_48;
  pbVar4 = local_51 + 2;
  uVar5 = 0xffffffff;
  local_4d = param_6;
  local_4e = param_5;
  local_51[1] = 0x27;
  local_51[2] = param_4;
  MakeOutgoingFrame(iVar1,&local_44,1,local_51 + 1,1,pbVar3,uVar2,pbVar4,0xffffffff);
  local_48 = local_44 + local_48;
  if (param_7 != '\0' && param_8 != 0) {
    MakeOutgoingFrame(iVar1 + local_48,&local_44,param_7,param_8,0xffffffff,pbVar3,uVar2,pbVar4,
                      uVar5);
    local_48 = local_44 + local_48;
  }
  MiniportMMRequest(param_1,1,local_4c);
  os_free_mem(local_4c);
  return;
}

