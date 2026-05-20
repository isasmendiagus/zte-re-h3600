// module: mt7915.ko
// function: RRM_EnqueuePeerBeaconRep @ 0x21e828
// size: 676 bytes
//

void RRM_EnqueuePeerBeaconRep
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined1 param_5,char param_6,undefined2 param_7,undefined4 param_8,
               undefined4 param_9,int param_10)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char cVar4;
  undefined1 local_67;
  undefined1 local_66;
  void *local_64;
  int local_60;
  undefined1 auStack_5a [24];
  char local_42;
  undefined1 local_41;
  undefined2 local_40;
  undefined2 local_3e;
  undefined2 local_3c;
  undefined2 local_3a;
  undefined2 local_38;
  undefined1 local_36;
  char local_35;
  undefined1 local_34;
  undefined4 local_33;
  undefined2 local_2f;
  undefined1 local_2d;
  int local_2c;
  
  local_64 = (void *)0x0;
  if (2 < DebugLevel) {
    printk("%s::\n","RRM_EnqueuePeerBeaconRep");
  }
  MgtMacHeaderInitExt(param_1,auStack_5a,0xd,0,param_2,param_3,param_2);
  iVar2 = os_alloc_mem(param_1,&local_64,0x900);
  if (iVar2 != 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s() allocate memory failed\n","RRM_EnqueuePeerBeaconRep");
    return;
  }
  memmove(local_64,auStack_5a,0x18);
  uVar3 = *(uint *)(param_10 + 0xac8);
  if (*(byte *)(param_10 + 0xc) < 0xf) {
    if ((uVar3 & 1) == 0) {
      if ((*(byte *)(param_10 + 0x34) & 1) != 0) {
        *(undefined1 *)(param_10 + 0x6c0) = 6;
        goto LAB_0021e8e0;
      }
      if (*(byte *)(param_10 + 0x26) < 5) goto LAB_0021e8e0;
      goto LAB_0021ea84;
    }
  }
  else {
    if ((uVar3 & 1) == 0) {
LAB_0021ea84:
      *(undefined1 *)(param_10 + 0x6c0) = 4;
      goto LAB_0021e8e0;
    }
    if ((uVar3 & 4) != 0) {
      *(undefined1 *)(param_10 + 0x6c0) = 9;
      goto LAB_0021e8e0;
    }
  }
  *(undefined1 *)(param_10 + 0x6c0) = 7;
LAB_0021e8e0:
  cVar4 = -0x14;
  __memzero(&local_42,0x1a);
  cVar1 = *(char *)(param_10 + 0x71);
  local_41 = *(undefined1 *)(param_10 + 0xc);
  local_36 = *(undefined1 *)(param_10 + 0x6c0);
  local_42 = *(char *)(param_10 + 0x6bf);
  if (*(char *)(param_10 + 0x6bf) == '\0') {
    local_42 = param_6;
  }
  local_38 = param_7;
  local_40 = 0;
  if (cVar1 == '\0') {
    cVar4 = -1;
  }
  local_3e = 0;
  local_3c = 0;
  local_3a = 0;
  if (cVar1 != '\0') {
    if (cVar1 < -0x6e) {
      cVar4 = '\0';
    }
    else if (cVar1 < '\x01') {
      cVar4 = (cVar1 + 'n') * '\x02';
    }
    else {
      cVar4 = -0x24;
    }
  }
  local_33 = *(undefined4 *)(param_10 + 6);
  local_34 = *(undefined1 *)(param_10 + 0x6c1);
  local_2f = *(undefined2 *)(param_10 + 10);
  local_2c = (uint)*(byte *)(param_10 + 0x4f8) * 0x10000 +
             (uint)*(byte *)(param_10 + 0x4f9) * 0x1000000 + (uint)*(byte *)(param_10 + 0x4f6) +
             (uint)*(byte *)(param_10 + 0x4f7) * 0x100;
  local_2d = 0;
  local_35 = cVar4;
  MakeOutgoingFrame((int)local_64 + 0x20,&local_60,0x1a,&local_42,0xffffffff);
  iVar2 = local_60;
  local_60 = 0x18;
  __memzero(&local_67,3);
  local_66 = 0;
  local_67 = param_5;
  MakeBeaconRepFrame(param_1,local_64,&local_60,0x1d,5,1,&local_67,param_4);
  MiniportMMRequest(param_1,0x81,local_64,iVar2 + 0x20);
  if (local_64 == (void *)0x0) {
    return;
  }
  os_free_mem();
  return;
}

