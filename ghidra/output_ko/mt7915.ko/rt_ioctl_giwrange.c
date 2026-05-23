// module: mt7915.ko
// function: rt_ioctl_giwrange @ 0x6d7d0
// size: 948 bytes
//

undefined4 rt_ioctl_giwrange(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 *puVar5;
  int *piVar6;
  undefined1 uVar7;
  uint uVar8;
  undefined1 *puVar9;
  int local_30;
  int local_2c;
  int local_28;
  int local_24 [2];
  
  iVar1 = RtmpOsGetNetDevPriv();
  if (iVar1 != 0) {
    iVar2 = RTMP_COM_IoctlHandle(iVar1,0,0x5011,0,0,0);
    if (iVar2 == 0) {
      if (2 < DebugLevel) {
        printk("===>rt_ioctl_giwrange\n");
      }
      *(undefined2 *)(param_3 + 4) = 0x238;
      __memzero(param_4);
      *(undefined2 *)(param_4 + 0xf2) = 0;
      iVar2 = DetermineCallerInterface(param_1,iVar1);
      if (iVar2 == 0) {
        uVar3 = RtmpDevPrivFlagsGet(param_1);
        RTMP_STA_IoctlHandle(iVar1,0,0xa00a,0,&local_30,0,uVar3);
        if (local_30 - 1U < 2) {
          *(undefined4 *)(param_4 + 200) = 0x400;
          *(undefined4 *)(param_4 + 0xcc) = 0x3fffc00;
          *(undefined4 *)(param_4 + 0xd0) = 0x400;
          *(undefined4 *)(param_4 + 0xd4) = 0xfa000;
          *(undefined2 *)(param_4 + 0xd8) = 0x1000;
          *(undefined2 *)(param_4 + 0xda) = 0x2000;
          *(undefined2 *)(param_4 + 0xdc) = 0x3300;
        }
        *(undefined2 *)(param_4 + 0x11a) = 0x1000;
        *(undefined1 *)(param_4 + 0x118) = 0x16;
        *(undefined1 *)(param_4 + 0x119) = 0xe;
        *(undefined2 *)(param_4 + 0x11c) = 0x1000;
        *(undefined4 *)(param_4 + 0x120) = 0;
        *(undefined4 *)(param_4 + 0x124) = 0xff;
        iVar2 = DetermineCallerInterface(param_1,iVar1);
        if (iVar2 == 0) {
          uVar3 = RtmpDevPrivFlagsGet(param_1);
          RTMP_STA_IoctlHandle(iVar1,0,0x5033,0,&local_2c,0,uVar3);
          *(ushort *)(param_4 + 0x130) = (ushort)local_2c;
          os_alloc_mem(0,&local_28);
          if (local_28 == 0) {
            return 0xfffffff4;
          }
          os_alloc_mem(0,local_24,local_2c << 2);
          if (local_24[0] == 0) {
            os_free_mem(local_28);
            return 0xfffffff4;
          }
          iVar4 = DetermineCallerInterface(param_1,iVar1);
          iVar2 = local_28;
          if (iVar4 != 0) {
            os_free_mem(local_28);
            os_free_mem(local_24[0]);
            return 0xfffffff2;
          }
          uVar3 = RtmpDevPrivFlagsGet(param_1);
          RTMP_STA_IoctlHandle(iVar1,0,0x5034,0,iVar2,0,uVar3);
          iVar2 = local_24[0];
          uVar3 = RtmpDevPrivFlagsGet(param_1);
          RTMP_STA_IoctlHandle(iVar1,0,0x5035,0,iVar2,0,uVar3);
          uVar8 = (uint)*(ushort *)(param_4 + 0x130);
          if (uVar8 == 0) {
            uVar7 = 0;
          }
          else {
            puVar9 = (undefined1 *)(param_4 + 0x13a);
            puVar5 = (undefined1 *)(local_28 + -1);
            piVar6 = (int *)(local_24[0] + -4);
            iVar1 = 1;
            do {
              iVar2 = iVar1;
              puVar5 = puVar5 + 1;
              *puVar9 = *puVar5;
              piVar6 = piVar6 + 1;
              iVar1 = *piVar6;
              *(undefined2 *)(puVar9 + -2) = 1;
              *(int *)(puVar9 + -6) = iVar1 * 100;
              if (iVar2 == 0x20) {
                uVar7 = 0x20;
                goto LAB_0006da38;
              }
              iVar1 = iVar2 + 1;
              puVar9 = puVar9 + 8;
            } while (iVar1 != 0x20 && iVar1 <= (int)uVar8);
            uVar7 = (undefined1)iVar2;
          }
LAB_0006da38:
          os_free_mem();
          os_free_mem(local_24[0]);
          *(undefined1 *)(param_4 + 0x2c) = 100;
          *(undefined1 *)(param_4 + 0x2d) = 0;
          *(undefined1 *)(param_4 + 0x2e) = 0;
          *(undefined4 *)(param_4 + 0xb8) = 0;
          *(undefined1 *)(param_4 + 0x30) = 0x14;
          *(undefined1 *)(param_4 + 0x31) = 0xc4;
          *(undefined1 *)(param_4 + 0x32) = 0xa1;
          *(undefined4 *)(param_4 + 0x28) = 3;
          *(undefined1 *)(param_4 + 0xef) = 4;
          *(undefined1 *)(param_4 + 0xee) = 2;
          *(undefined2 *)(param_4 + 0xde) = 5;
          *(undefined2 *)(param_4 + 0xe0) = 0xd;
          *(undefined4 *)(param_4 + 0xbc) = 0x92b;
          *(undefined1 *)(param_4 + 0x132) = uVar7;
          *(undefined4 *)(param_4 + 0xc0) = 0x100;
          *(undefined4 *)(param_4 + 0xc4) = 0x92a;
          *(undefined4 *)(param_4 + 0x234) = 0xf;
          return 0;
        }
      }
      return 0xfffffff2;
    }
    if (2 < DebugLevel) {
      printk("INFO::Network is down!\n");
      return 0xffffff9c;
    }
  }
  return 0xffffff9c;
}

