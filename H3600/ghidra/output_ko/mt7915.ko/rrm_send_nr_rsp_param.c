// module: mt7915.ko
// function: rrm_send_nr_rsp_param @ 0x220b14
// size: 444 bytes
//

undefined4 rrm_send_nr_rsp_param(int *param_1,void *param_2,size_t param_3)

{
  byte bVar1;
  undefined1 *puVar2;
  uint uVar3;
  int iVar4;
  undefined1 *local_24;
  
  uVar3 = *(uint *)(*param_1 + 0x3c);
  local_24 = (undefined1 *)0x0;
  if (*(char *)((int)param_1 + (uVar3 & 0xff) * 0x5834 + 0x2b7d69) == '\0') {
    if (-1 < DebugLevel) {
      printk("%s() rrm off\n","rrm_send_nr_rsp_param");
      return 1;
    }
  }
  else {
    bVar1 = *(byte *)((int)param_2 + 7);
    if (param_3 == (short)(ushort)bVar1 * 0x12 + 8U) {
      if (bVar1 < 6) {
        iVar4 = param_3 + 10;
        os_alloc_mem(0,&local_24,iVar4);
        if (local_24 != (undefined1 *)0x0) {
          __memzero(local_24,iVar4);
          puVar2 = local_24;
          *local_24 = (char)uVar3;
          local_24[1] = *(undefined1 *)((int)param_2 + 6);
          memmove(local_24 + 2,param_2,6);
          *(short *)(puVar2 + 8) = (short)param_3;
          memmove(puVar2 + 10,param_2,param_3);
          MlmeEnqueue(param_1,0x30,1,iVar4,local_24,0);
          os_free_mem(local_24);
          return 0;
        }
        if (-1 < DebugLevel) {
          printk("%s() allocate event memory failed \n","rrm_send_nr_rsp_param");
          return 3;
        }
        return 3;
      }
      if (-1 < DebugLevel) {
        printk("%s the num of candidate(%d) excceed %d\n","rrm_send_nr_rsp_param",bVar1,5);
        return 1;
      }
    }
    else if (-1 < DebugLevel) {
      printk("%s() length check failed nr_rsp_data_len=%d, Len=%d\n","rrm_send_nr_rsp_param");
      return 1;
    }
  }
  return 1;
}

