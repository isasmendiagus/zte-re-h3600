// module: mt7915.ko
// function: rt_ioctl_iwaplist @ 0x6dd74
// size: 628 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 rt_ioctl_iwaplist(undefined4 param_1,undefined4 param_2,int param_3,undefined4 *param_4)

{
  undefined1 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  size_t __n;
  undefined2 uVar7;
  undefined4 *puVar8;
  uint uVar9;
  undefined4 *puVar10;
  undefined1 *puVar11;
  undefined4 uVar12;
  int local_138 [3];
  int local_12c;
  undefined1 auStack_128 [260];
  
  local_138[0] = 0;
  uVar2 = RtmpOsGetNetDevPriv();
  __memzero(auStack_128,0x100);
  iVar3 = RTMP_COM_IoctlHandle(uVar2,0,0x5011,0,0,0);
  if (iVar3 == 0) {
    os_alloc_mem(0,&local_12c,0x300);
    if (local_12c != 0) {
      os_alloc_mem(0,local_138,0x400);
      if (local_138[0] == 0) {
        if (-1 < DebugLevel) {
          printk("%s: Allocate memory fail!!!\n","rt_ioctl_iwaplist");
        }
      }
      else {
        local_138[1] = 0x40;
        iVar3 = DetermineCallerInterface(param_1,uVar2);
        if (iVar3 != 0) {
          os_free_mem(local_138[0]);
          os_free_mem(local_12c);
          return 0xfffffff2;
        }
        uVar4 = RtmpDevPrivFlagsGet(param_1);
        RTMP_STA_IoctlHandle(uVar2,0,0xa006,0,local_138 + 1,0,uVar4);
        iVar3 = local_138[0];
        uVar9 = 0;
        puVar10 = param_4;
        puVar11 = auStack_128;
        do {
          iVar5 = uVar9 * 0x10;
          if ((uint)local_138[2] <= uVar9) {
            uVar7 = (undefined2)uVar9;
            iVar5 = uVar9 << 4;
            __n = uVar9 << 2;
            goto LAB_0006df28;
          }
          *(undefined2 *)(local_138[0] + iVar5) = 1;
          puVar6 = (undefined4 *)(local_12c + uVar9 * 9);
          *(undefined4 *)(local_138[0] + iVar5 + 2) = *puVar6;
          puVar8 = (undefined4 *)(local_138[0] + iVar5);
          *(undefined2 *)(local_138[0] + iVar5 + 6) = *(undefined2 *)(puVar6 + 1);
          uVar12 = puVar8[1];
          uVar2 = puVar8[2];
          uVar4 = puVar8[3];
          *puVar10 = *puVar8;
          puVar10[1] = uVar12;
          puVar10[2] = uVar2;
          puVar10[3] = uVar4;
          auStack_128[uVar9 * 4] = *(undefined1 *)((int)puVar6 + 6);
          uVar9 = uVar9 + 1;
          puVar11[1] = *(undefined1 *)((int)puVar6 + 7);
          uVar1 = *(undefined1 *)(puVar6 + 2);
          puVar11[3] = 0xf;
          puVar11[2] = uVar1;
          puVar10 = puVar10 + 4;
          puVar11 = puVar11 + 4;
        } while (uVar9 != 0x40);
        uVar7 = 0x40;
        __n = 0x100;
        iVar5 = 0x400;
LAB_0006df28:
        *(undefined2 *)(param_3 + 4) = uVar7;
        *(undefined2 *)(param_3 + 6) = 1;
        memcpy((void *)((int)param_4 + iVar5),auStack_128,__n);
        os_free_mem(iVar3);
      }
      os_free_mem(local_12c);
      return 0;
    }
    if (-1 < DebugLevel) {
      printk("%s: Allocate memory fail!!!\n","rt_ioctl_iwaplist");
    }
  }
  else {
    if (2 < DebugLevel) {
      printk("INFO::Network is down!\n");
    }
    *(undefined2 *)(param_3 + 4) = 0;
  }
  return 0;
}

