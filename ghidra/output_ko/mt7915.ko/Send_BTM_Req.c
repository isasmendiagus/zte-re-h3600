// module: mt7915.ko
// function: Send_BTM_Req @ 0x3fab8
// size: 688 bytes
//

undefined4 Send_BTM_Req(int *param_1,void *param_2,void *param_3,size_t param_4)

{
  byte bVar1;
  byte *pbVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  bool bVar6;
  int *piVar7;
  byte *local_30;
  int *local_2c [2];
  
  bVar1 = *(byte *)(*param_1 + 0x3c);
  uVar5 = (uint)bVar1;
  if (0 < DebugLevel) {
    printk(&_LC241,"Send_BTM_Req");
  }
  piVar3 = param_1 + uVar5 * 0x160d + 0xaefb1;
  down_interruptible(piVar3);
  for (piVar7 = (int *)param_1[uVar5 * 0x160d + 0xaefc0]; local_2c[0] = piVar7,
      piVar7 != param_1 + uVar5 * 0x160d + 0xaefc0; piVar7 = (int *)*piVar7) {
    iVar4 = memcmp((void *)((int)piVar7 + 0xd),param_2,6);
    if (iVar4 == 0) {
      bVar6 = true;
      goto LAB_0003fb70;
    }
  }
  bVar6 = false;
LAB_0003fb70:
  iVar4 = param_4 + 0xc;
  up(piVar3);
  os_alloc_mem(0,&local_30,iVar4);
  if (local_30 == (byte *)0x0) {
    if (DebugLevel < 0) {
      return 0;
    }
  }
  else {
    if (iVar4 != 0) {
      __memzero(local_30,iVar4);
    }
    if (bVar6) {
LAB_0003fba8:
      pbVar2 = local_30;
      *local_30 = bVar1;
      memmove(local_30 + 1,param_2,6);
      pbVar2[7] = 2;
      pbVar2[8] = 0;
      bVar1 = *(byte *)((int)local_2c[0] + 0x13);
      *(short *)(pbVar2 + 10) = (short)param_4;
      pbVar2[9] = bVar1;
      memmove(pbVar2 + 0xc,param_3,param_4);
      if (-1 < DebugLevel) {
        printk("\nbefore adding BSS Transition Candidate List Entries::BTMReqLen=%d, Len=%d\n",
               param_4,iVar4);
      }
      MlmeEnqueue(param_1,0x28,2,iVar4,local_30,0);
      os_free_mem(local_30);
      return 1;
    }
    os_alloc_mem(0,local_2c,0xb8);
    if (local_2c[0] != (int *)0x0) {
      __memzero(local_2c[0],0xb8);
      piVar7 = local_2c[0];
      local_2c[0][2] = 2;
      *(byte *)(local_2c[0] + 3) = bVar1;
      memmove((void *)((int)local_2c[0] + 0xd),param_2,6);
      piVar7[5] = (int)param_1;
      *(undefined1 *)((int)piVar7 + 0x13) = 1;
      RTMPInitTimer(param_1,piVar7 + 6,rtmp_timer_WaitPeerBTMRspTimeout,piVar7,0);
      down_interruptible(piVar3);
      piVar7 = (int *)param_1[uVar5 * 0x160d + 0xaefc1];
      *local_2c[0] = *piVar7;
      local_2c[0][1] = (int)piVar7;
      *(int **)(*piVar7 + 4) = local_2c[0];
      *piVar7 = (int)local_2c[0];
      up(piVar3);
      goto LAB_0003fba8;
    }
    if (DebugLevel < 0) goto LAB_0003fd14;
  }
  printk("%s Not available memory\n","Send_BTM_Req");
LAB_0003fd14:
  if (local_30 != (byte *)0x0) {
    os_free_mem();
  }
  return 0;
}

