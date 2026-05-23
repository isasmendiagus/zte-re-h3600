// module: mt7915.ko
// function: rrm_send_beacon_req_param @ 0x21da48
// size: 556 bytes
//

bool rrm_send_beacon_req_param(int *param_1,undefined4 *param_2,int param_3)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  int iVar3;
  uint uVar4;
  char cVar5;
  undefined1 *local_24;
  
  local_24 = (undefined1 *)0x0;
  uVar4 = *(uint *)(*param_1 + 0x3c);
  if (2 < DebugLevel) {
    printk(&_LC4,"rrm_send_beacon_req_param");
  }
  if (*(char *)((int)param_1 + (uVar4 & 0xff) * 0x5834 + 0x2b7d69) == '\0') {
    if (-1 < DebugLevel) {
      printk("%s() rrm off\n","rrm_send_beacon_req_param");
      return true;
    }
  }
  else {
    if (param_3 == 0x8d) {
      os_alloc_mem(0,&local_24,0x97);
      if (local_24 == (undefined1 *)0x0) {
        if (-1 < DebugLevel) {
          printk("%s, allocate event memory failed \n","rrm_send_beacon_req_param");
          return (bool)3;
        }
        return (bool)3;
      }
      __memzero(local_24,0x97);
      cVar5 = _LANCHOR1 + '\x01';
      if (cVar5 == '\0') {
        cVar5 = '\x01';
      }
      _LANCHOR1 = cVar5;
      iVar3 = MeasureReqInsert(param_1,cVar5);
      puVar2 = local_24;
      if (iVar3 != 0) {
        *(int **)(iVar3 + 0x10) = param_1;
        uVar1 = (undefined1)uVar4;
        *(undefined1 *)(iVar3 + 0x4e) = uVar1;
        *(undefined1 *)(iVar3 + 0xd) = 1;
        *(undefined1 *)(iVar3 + 0xe) = 1;
        *(undefined4 *)(iVar3 + 0x48) = *param_2;
        *(undefined2 *)(iVar3 + 0x4c) = *(undefined2 *)(param_2 + 1);
        *local_24 = uVar1;
        local_24[1] = cVar5;
        RTMPMoveMemory(local_24 + 2,param_2,6);
        puVar2[8] = 0x8d;
        puVar2[9] = 0;
        memmove(puVar2 + 10,param_2,0x8d);
        iVar3 = MlmeEnqueue(param_1,0x31,0,0x97,local_24,0);
        if (iVar3 == 0) {
          MeasureReqDelete(param_1,cVar5);
        }
        os_free_mem(local_24);
        return iVar3 == 0;
      }
      if (-1 < DebugLevel) {
        printk("%s, Fail to Insert MesureReq Token(%d)!\n","rrm_send_beacon_req_param",cVar5);
      }
      os_free_mem(local_24);
      return true;
    }
    if (-1 < DebugLevel) {
      printk("%s, bcn req len check failed\n","rrm_send_beacon_req_param");
      return true;
    }
  }
  return true;
}

