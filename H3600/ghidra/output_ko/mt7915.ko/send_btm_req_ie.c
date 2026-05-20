// module: mt7915.ko
// function: send_btm_req_ie @ 0x2278b4
// size: 1100 bytes
//

undefined4 send_btm_req_ie(int *param_1,int param_2,uint param_3)

{
  undefined1 uVar1;
  bool bVar2;
  undefined1 *puVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int *piVar8;
  int *piVar9;
  undefined1 uStack_31;
  int *local_30;
  undefined1 *local_2c [2];
  
  local_30 = (int *)0x0;
  uVar6 = *(uint *)(*param_1 + 0x3c);
  local_2c[0] = (undefined1 *)0x0;
  if (2 < DebugLevel) {
    printk(&_LC4,"send_btm_req_ie");
  }
  uVar7 = uVar6 & 0xff;
  if (*(char *)((int)param_1 + uVar7 * 0x5834 + 0x2bbee6) == '\0') {
    if (-1 < DebugLevel) {
      printk("%s() btm off\n","send_btm_req_ie");
      return 1;
    }
  }
  else if (param_3 < 0x3e9) {
    iVar5 = param_3 + 0xc;
    os_alloc_mem(0,local_2c,iVar5);
    if (local_2c[0] == (undefined1 *)0x0) {
      if (-1 < DebugLevel) {
        printk("%s Not available memory for btm req msg\n","send_btm_req_ie");
        return 1;
      }
    }
    else {
      piVar8 = param_1 + uVar7 * 0x160d + 0xaefb1;
      down_interruptible(piVar8);
      piVar9 = (int *)param_1[uVar7 * 0x160d + 0xaefc0];
      uVar1 = (undefined1)uVar6;
      local_30 = piVar9;
      if (piVar9 != param_1 + uVar7 * 0x160d + 0xaefc0) {
        do {
          local_30 = piVar9;
          iVar4 = memcmp((void *)((int)piVar9 + 0xd),(void *)(param_2 + 4),6);
          if (iVar4 == 0) {
            if (0 < DebugLevel) {
              printk("%s() found BTMPeerEntry in BTMEntrylist that say receive btm query before\n",
                     "send_btm_req_ie");
            }
            bVar2 = true;
            local_30[2] = 2;
            local_30[0x2d] = *(int *)(param_2 + 0xb) * 1000;
            up(piVar8);
            goto LAB_00227a30;
          }
          piVar9 = (int *)*piVar9;
          local_30 = piVar9;
        } while (param_1 + uVar7 * 0x160d + 0xaefc0 != piVar9);
      }
      up(piVar8);
      os_alloc_mem(0,&local_30,0xb8);
      if (local_30 != (int *)0x0) {
        __memzero(local_30,0xb8);
        piVar9 = local_30;
        local_30[2] = 2;
        *(undefined1 *)(local_30 + 3) = uVar1;
        memmove((void *)((int)local_30 + 0xd),(void *)(param_2 + 4),6);
        if (*(char *)(param_2 + 10) == '\0') {
          _LANCHOR1 = _LANCHOR1 + '\x01';
          if (_LANCHOR1 == '\0') {
            _LANCHOR1 = '\x01';
          }
          *(char *)((int)piVar9 + 0x13) = _LANCHOR1;
          *(char *)(param_2 + 10) = _LANCHOR1;
        }
        else {
          *(char *)((int)piVar9 + 0x13) = *(char *)(param_2 + 10);
        }
        piVar9[5] = (int)param_1;
        bVar2 = false;
        piVar9[0x2d] = *(int *)(param_2 + 0xb) * 1000;
        down_interruptible(piVar8);
        piVar9 = (int *)param_1[uVar7 * 0x160d + 0xaefc1];
        *local_30 = *piVar9;
        local_30[1] = (int)piVar9;
        *(int **)(*piVar9 + 4) = local_30;
        *piVar9 = (int)local_30;
        up(piVar8);
LAB_00227a30:
        __memzero(local_2c[0],iVar5);
        puVar3 = local_2c[0];
        *local_2c[0] = uVar1;
        memmove(local_2c[0] + 1,(void *)(param_2 + 4),6);
        puVar3[7] = 3;
        puVar3[8] = 0;
        puVar3[9] = *(undefined1 *)(param_2 + 10);
        *(short *)(puVar3 + 10) = (short)*(undefined4 *)(param_2 + 0xf);
        memmove(puVar3 + 0xc,(void *)(param_2 + 0x13),*(size_t *)(param_2 + 0xf));
        iVar5 = MlmeEnqueue(param_1,0x28,3,iVar5,local_2c[0],0);
        if (iVar5 == 0) {
          if (-1 < DebugLevel) {
            printk("%s() mlme enqueue failed","send_btm_req_ie");
          }
          if (!bVar2) {
            down_interruptible(piVar8);
            if (*local_30 != 0) {
              *(int *)(*local_30 + 4) = local_30[1];
            }
            if ((int *)local_30[1] != (int *)0x0) {
              *(int *)local_30[1] = *local_30;
            }
            *local_30 = 0;
            local_30[1] = 0;
            up(piVar8);
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
      if (-1 < DebugLevel) {
        printk("%s Not available memory for BTMPeerEntry\n","send_btm_req_ie");
      }
      os_free_mem(local_2c[0]);
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s BTM Req ie len(%d) is too long","send_btm_req_ie");
    return 1;
  }
  return 1;
}

