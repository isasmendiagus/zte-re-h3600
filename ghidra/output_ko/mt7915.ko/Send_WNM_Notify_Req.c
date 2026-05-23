// module: mt7915.ko
// function: Send_WNM_Notify_Req @ 0x3fd6c
// size: 680 bytes
//

undefined4
Send_WNM_Notify_Req(int *param_1,void *param_2,void *param_3,size_t param_4,undefined2 param_5)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  uint uVar6;
  bool bVar7;
  int *piVar8;
  byte *local_30;
  int *local_2c [2];
  
  bVar1 = *(byte *)(*param_1 + 0x3c);
  uVar6 = (uint)bVar1;
  if (0 < DebugLevel) {
    printk(&_LC241,"Send_WNM_Notify_Req");
  }
  piVar5 = param_1 + uVar6 * 0x160d + 0xaefb5;
  down_interruptible(piVar5);
  piVar8 = (int *)param_1[uVar6 * 0x160d + 0xaefc2];
  do {
    local_2c[0] = piVar8;
    if (piVar8 == param_1 + uVar6 * 0x160d + 0xaefc2) {
      up(piVar5);
      os_alloc_mem(0,local_2c,0x4c);
      if (local_2c[0] == (int *)0x0) {
        if (DebugLevel < 0) {
          return 0;
        }
        printk("%s Not available memory\n","Send_WNM_Notify_Req");
        uVar4 = 0;
      }
      else {
        __memzero(local_2c[0],0x4c);
        piVar8 = local_2c[0];
        bVar7 = false;
        *(byte *)(local_2c[0] + 3) = bVar1;
        local_2c[0][2] = 0;
        memmove((void *)((int)local_2c[0] + 0xd),param_2,6);
        piVar8[5] = (int)param_1;
        *(undefined1 *)((int)piVar8 + 0x13) = 1;
        RTMPInitTimer(param_1,piVar8 + 6,rtmp_timer_WaitPeerWNMNotifyRspTimeout,piVar8,0);
        down_interruptible(piVar5);
        piVar8 = (int *)param_1[uVar6 * 0x160d + 0xaefc3];
        *local_2c[0] = *piVar8;
        local_2c[0][1] = (int)piVar8;
        *(int **)(*piVar8 + 4) = local_2c[0];
        *piVar8 = (int)local_2c[0];
        up(piVar5);
LAB_0003fe2c:
        iVar3 = param_4 + 0xc;
        os_alloc_mem(0,&local_30,iVar3);
        if (local_30 == (byte *)0x0) {
          if (-1 < DebugLevel) {
            printk("%s Not available memory\n","Send_WNM_Notify_Req");
          }
          if (bVar7) {
            return 0;
          }
          os_free_mem(local_2c[0]);
          uVar4 = 0;
        }
        else {
          if (iVar3 != 0) {
            __memzero(local_30,iVar3);
          }
          pbVar2 = local_30;
          *local_30 = bVar1;
          memmove(local_30 + 1,param_2,6);
          *(undefined2 *)(pbVar2 + 7) = param_5;
          bVar1 = *(byte *)((int)local_2c[0] + 0x13);
          *(short *)(pbVar2 + 10) = (short)param_4;
          pbVar2[9] = bVar1;
          memmove(pbVar2 + 0xc,param_3,param_4);
          MlmeEnqueue(param_1,0x29,0,iVar3,local_30,0);
          os_free_mem(local_30);
          uVar4 = 1;
        }
      }
      return uVar4;
    }
    iVar3 = memcmp((void *)((int)piVar8 + 0xd),param_2,6);
    if (iVar3 == 0) {
      bVar7 = true;
      up(piVar5);
      goto LAB_0003fe2c;
    }
    piVar8 = (int *)*piVar8;
  } while( true );
}

