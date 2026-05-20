// module: mt7915.ko
// function: rrm_send_beacon_req @ 0x220780
// size: 684 bytes
//

bool rrm_send_beacon_req(int *param_1,void *param_2,size_t param_3)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined1 *local_2c [2];
  
  local_2c[0] = (undefined1 *)0x0;
  uVar4 = *(uint *)(*param_1 + 0x3c);
  if (2 < DebugLevel) {
    printk(&_LC50,"rrm_send_beacon_req");
  }
  uVar5 = uVar4 & 0xff;
  if (*(char *)((int)param_1 + uVar5 * 0x5834 + 0x2b7d69) == '\0') {
    if (-1 < DebugLevel) {
      printk("%s() AP(%02x:%02x:%02x:%02x:%02x:%02x) not support rrm\n","rrm_send_beacon_req",
             *(undefined1 *)((int)param_1 + uVar5 * 0x5834 + 0x2b7269),
             *(undefined1 *)((int)param_1 + uVar5 * 0x5834 + 0x2b726a),
             *(undefined1 *)((int)param_1 + uVar5 * 0x5834 + 0x2b726b),
             (char)param_1[uVar5 * 0x160d + 0xadc9b],
             *(undefined1 *)((int)param_1 + uVar5 * 0x5834 + 0x2b726d),
             *(undefined1 *)((int)param_1 + uVar5 * 0x5834 + 0x2b726e));
      return true;
    }
  }
  else {
    if (param_3 == *(int *)((int)param_2 + 0xb) + 0xfU) {
      iVar6 = *(int *)((int)param_2 + 0xb) + 0x19;
      os_alloc_mem(0,local_2c,iVar6);
      if (local_2c[0] == (undefined1 *)0x0) {
        if (-1 < DebugLevel) {
          printk("%s, allocate event memory failed \n","rrm_send_beacon_req");
          return (bool)3;
        }
        return (bool)3;
      }
      if (iVar6 != 0) {
        __memzero(local_2c[0],iVar6);
      }
      if (*(char *)((int)param_2 + 4) == '\0') {
        if (-1 < DebugLevel) {
          printk("%s, invalid MesureReq Token(0)!\n","rrm_send_beacon_req");
        }
      }
      else {
        iVar3 = MeasureReqInsert(param_1);
        puVar2 = local_2c[0];
        if (iVar3 != 0) {
          *(int **)(iVar3 + 0x10) = param_1;
          uVar1 = (undefined1)uVar4;
          *(undefined1 *)(iVar3 + 0x4e) = uVar1;
          *(undefined1 *)(iVar3 + 0xd) = 1;
          *(undefined1 *)(iVar3 + 0xe) = 1;
          *local_2c[0] = uVar1;
          local_2c[0][1] = *(undefined1 *)((int)param_2 + 4);
          RTMPMoveMemory(local_2c[0] + 2,(int)param_2 + 5,6);
          *(short *)(puVar2 + 8) = (short)param_3;
          memmove(puVar2 + 10,param_2,param_3);
          iVar6 = MlmeEnqueue(param_1,0x31,1,iVar6,local_2c[0],0);
          if (iVar6 == 0) {
            MeasureReqDelete(param_1,*(undefined1 *)((int)param_2 + 4));
          }
          os_free_mem(local_2c[0]);
          return iVar6 == 0;
        }
        if (-1 < DebugLevel) {
          printk("%s, Fail to Insert MesureReq Token(%d)!\n","rrm_send_beacon_req",
                 *(undefined1 *)((int)param_2 + 4));
        }
      }
      os_free_mem(local_2c[0]);
      return true;
    }
    if (-1 < DebugLevel) {
      printk("%s, bcn req len check failed len1=%d, len2=%d\n","rrm_send_beacon_req",param_3);
      return true;
    }
  }
  return true;
}

