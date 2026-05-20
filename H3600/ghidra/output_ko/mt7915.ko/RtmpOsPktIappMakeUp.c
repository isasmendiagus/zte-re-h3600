// module: mt7915.ko
// function: RtmpOsPktIappMakeUp @ 0x244ea4
// size: 324 bytes
//

int RtmpOsPktIappMakeUp(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 local_42;
  undefined2 uStack_3e;
  undefined2 local_3c;
  undefined2 uStack_3a;
  undefined2 local_38;
  undefined4 local_36;
  undefined4 local_32;
  undefined4 local_2e;
  undefined2 local_2a;
  
  if (param_1 == 0) {
    return 0;
  }
  iVar1 = RtmpOSNetPktAlloc(0,0x1a);
  if (iVar1 == 0) {
    if (DebugLevel < 0) {
      iVar1 = 0;
    }
    else {
      printk("Error! Can\'t allocate a skb.\n");
    }
  }
  else {
    __memzero(&local_42,0x1a);
    memset(&local_42,0xff,6);
    uVar3 = *param_2;
    local_38 = *(undefined2 *)(param_2 + 1);
    local_2e = *(undefined4 *)(*(int *)(param_1 + 0x4c4) + 0x21);
    local_2a = *(undefined2 *)(*(int *)(param_1 + 0x4c4) + 0x25);
    *(int *)(iVar1 + 0xcc) = *(int *)(iVar1 + 0xcc) + 2;
    *(int *)(iVar1 + 0xc0) = *(int *)(iVar1 + 0xc0) + 2;
    *(int *)(iVar1 + 0x18) = param_1;
    local_3c = (undefined2)uVar3;
    uStack_3a = (undefined2)((uint)uVar3 >> 0x10);
    local_36 = 0x1000600;
    local_32 = 0x20181af;
    puVar2 = (undefined4 *)skb_put(iVar1,0x1a);
    *puVar2 = local_42;
    puVar2[1] = CONCAT22(local_3c,uStack_3e);
    puVar2[2] = CONCAT22(local_38,uStack_3a);
    puVar2[3] = local_36;
    puVar2[5] = local_2e;
    puVar2[4] = local_32;
    *(undefined2 *)(puVar2 + 6) = local_2a;
  }
  return iVar1;
}

