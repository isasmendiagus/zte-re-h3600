// module: mt7915.ko
// function: SendBTMRsp @ 0x2240d4
// size: 468 bytes
//

void SendBTMRsp(int param_1,byte *param_2)

{
  int iVar1;
  ushort uVar2;
  int iVar3;
  int *piVar4;
  undefined *puVar5;
  undefined1 uStack_25;
  int local_24;
  
  uVar2 = *(ushort *)(param_2 + 10);
  iVar1 = (uint)*param_2 * 0x2137b0;
  puVar5 = &DAT_00580dec + param_1 + iVar1;
  down_interruptible(puVar5);
  piVar4 = *(int **)(&DAT_00580e28 + param_1 + iVar1);
  if (piVar4 != (int *)(&DAT_00580e28 + param_1 + iVar1)) {
    do {
      iVar3 = memcmp((void *)((int)piVar4 + 0xd),param_2 + 1,6);
      if (iVar3 == 0) break;
      piVar4 = (int *)*piVar4;
    } while (piVar4 != (int *)(&DAT_00580e28 + param_1 + iVar1));
  }
  up(puVar5);
  os_alloc_mem(0,&local_24,uVar2 + 0x1c);
  if (local_24 == 0) {
    if (-1 < DebugLevel) {
      printk("%s Not available memory\n","SendBTMRsp");
    }
  }
  else {
    __memzero(local_24,uVar2 + 0x1c);
    iVar1 = local_24;
    ActHeaderInit(param_1,local_24,param_2 + 1,&DAT_0036db73 + param_1 + (uint)*param_2 * 0x2137b0,
                  param_2 + 1);
    *(undefined1 *)(iVar1 + 0x18) = 10;
    *(undefined1 *)(iVar1 + 0x19) = 8;
    *(byte *)(iVar1 + 0x1a) = param_2[9];
    memmove((void *)(iVar1 + 0x1b),param_2 + 0xc,(uint)*(ushort *)(param_2 + 10));
    MiniportMMRequest(param_1,0x81,local_24,*(ushort *)(param_2 + 10) + 0x1b);
    RTMPCancelTimer(piVar4 + 0x20,&uStack_25);
    RTMPReleaseTimer(piVar4 + 0x20,&uStack_25);
    down_interruptible(puVar5);
    if (*piVar4 != 0) {
      *(int *)(*piVar4 + 4) = piVar4[1];
    }
    if ((int *)piVar4[1] != (int *)0x0) {
      *(int *)piVar4[1] = *piVar4;
    }
    *piVar4 = 0;
    piVar4[1] = 0;
    up(puVar5);
    os_free_mem(piVar4);
    os_free_mem(local_24);
  }
  return;
}

