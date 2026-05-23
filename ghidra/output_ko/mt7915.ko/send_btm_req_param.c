// module: mt7915.ko
// function: send_btm_req_param @ 0x227d04
// size: 1156 bytes
//

undefined4 send_btm_req_param(int *param_1,void *param_2,size_t param_3)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  byte *pbVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  int iVar8;
  int *piVar9;
  undefined1 uStack_31;
  int *local_30;
  byte *local_2c [2];
  
  bVar1 = *(byte *)(*param_1 + 0x3c);
  uVar6 = (uint)bVar1;
  local_30 = (int *)0x0;
  local_2c[0] = (byte *)0x0;
  if (*(char *)((int)param_1 + uVar6 * 0x5834 + 0x2bbee6) == '\0') {
    if (-1 < DebugLevel) {
      printk("%s() btm off\n","send_btm_req_param");
      return 1;
    }
  }
  else {
    bVar2 = *(byte *)((int)param_2 + 0x42);
    if (param_3 == (short)(ushort)bVar2 * 0x12 + 0x43U) {
      if (bVar2 < 6) {
        iVar8 = param_3 + 0xc;
        os_alloc_mem(0,local_2c,iVar8);
        if (local_2c[0] == (byte *)0x0) {
          if (-1 < DebugLevel) {
            printk("%s Not available memory for btm req msg\n","send_btm_req_param");
            return 3;
          }
          return 3;
        }
        piVar7 = param_1 + uVar6 * 0x160d + 0xaefb1;
        down_interruptible(piVar7);
        piVar9 = (int *)param_1[uVar6 * 0x160d + 0xaefc0];
        do {
          local_30 = piVar9;
          if (piVar9 == param_1 + uVar6 * 0x160d + 0xaefc0) {
            up(piVar7);
            os_alloc_mem(0,&local_30,0xb8);
            if (local_30 == (int *)0x0) {
              if (-1 < DebugLevel) {
                printk("%s Not available memory for BTMPeerEntry\n","send_btm_req_param");
              }
              os_free_mem(local_2c[0]);
              return 3;
            }
            __memzero(local_30,0xb8);
            piVar9 = local_30;
            local_30[2] = 2;
            *(byte *)(local_30 + 3) = bVar1;
            memmove((void *)((int)local_30 + 0xd),param_2,6);
            if (*(char *)((int)param_2 + 6) == '\0') {
              DAT_005e006e = DAT_005e006e + '\x01';
              if (DAT_005e006e == '\0') {
                DAT_005e006e = '\x01';
              }
              *(char *)((int)piVar9 + 0x13) = DAT_005e006e;
              *(char *)((int)param_2 + 6) = DAT_005e006e;
            }
            else {
              *(char *)((int)piVar9 + 0x13) = *(char *)((int)param_2 + 6);
            }
            piVar9[5] = (int)param_1;
            bVar3 = false;
            piVar9[0x2d] = *(int *)((int)param_2 + 0xb) * 1000;
            down_interruptible(piVar7);
            piVar9 = (int *)param_1[uVar6 * 0x160d + 0xaefc1];
            *local_30 = *piVar9;
            local_30[1] = (int)piVar9;
            *(int **)(*piVar9 + 4) = local_30;
            *piVar9 = (int)local_30;
            up(piVar7);
LAB_00227ed8:
            __memzero(local_2c[0],iVar8);
            pbVar4 = local_2c[0];
            *local_2c[0] = bVar1;
            memmove(local_2c[0] + 1,param_2,6);
            pbVar4[7] = 4;
            pbVar4[8] = 0;
            bVar1 = *(byte *)((int)param_2 + 6);
            *(short *)(pbVar4 + 10) = (short)param_3;
            pbVar4[9] = bVar1;
            memmove(pbVar4 + 0xc,param_2,param_3);
            iVar8 = MlmeEnqueue(param_1,0x28,4,iVar8,local_2c[0],0);
            if (iVar8 == 0) {
              if (-1 < DebugLevel) {
                printk("%s() mlme enqueue failed","send_btm_req_param");
              }
              if (!bVar3) {
                down_interruptible(piVar7);
                if (*local_30 != 0) {
                  *(int *)(*local_30 + 4) = local_30[1];
                }
                if ((int *)local_30[1] != (int *)0x0) {
                  *(int *)local_30[1] = *local_30;
                }
                *local_30 = 0;
                local_30[1] = 0;
                up(piVar7);
                RTMPCancelTimer(local_30 + 0x13,&uStack_31);
                RTMPReleaseTimer(local_30 + 0x13,&uStack_31);
                RTMPCancelTimer(local_30 + 6,&uStack_31);
                RTMPReleaseTimer(local_30 + 6,&uStack_31);
                os_free_mem(local_30);
              }
            }
            os_free_mem(local_2c[0]);
            return 0;
          }
          iVar5 = memcmp((void *)((int)piVar9 + 0xd),param_2,6);
          if (iVar5 == 0) {
            if (0 < DebugLevel) {
              printk("%s() found BTMPeerEntry in BTMEntrylist that say receive btm query before\n",
                     "send_btm_req_param");
            }
            bVar3 = true;
            local_30[2] = 2;
            local_30[0x2d] = *(int *)((int)param_2 + 0xb) * 1000;
            up(piVar7);
            goto LAB_00227ed8;
          }
          piVar9 = (int *)*piVar9;
        } while( true );
      }
      if (-1 < DebugLevel) {
        printk("%s the num of candidate(%d) excceed %d","send_btm_req_param",bVar2,5);
        return 1;
      }
    }
    else if (-1 < DebugLevel) {
      printk("%s() length check failed btm_req_data_len=%d, Len=%d\n","send_btm_req_param");
      return 1;
    }
  }
  return 1;
}

