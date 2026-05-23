// module: mt7915.ko
// function: rrm_send_nr_rsp_ie @ 0x221418
// size: 428 bytes
//

undefined4 rrm_send_nr_rsp_ie(int *param_1,int param_2,int param_3)

{
  undefined1 *puVar1;
  uint uVar2;
  uint __n;
  int iVar3;
  undefined1 *local_24;
  
  uVar2 = *(uint *)(*param_1 + 0x3c);
  __n = *(uint *)(param_2 + 0xb);
  local_24 = (undefined1 *)0x0;
  if (*(char *)((int)param_1 + (uVar2 & 0xff) * 0x5834 + 0x2b7d69) == '\0') {
    if (-1 < DebugLevel) {
      printk("%s() rrm off\n","rrm_send_nr_rsp_ie");
      return 1;
    }
  }
  else if (param_3 == __n + 0xf) {
    if (__n < 0x3e9) {
      iVar3 = __n + 10;
      os_alloc_mem(0,&local_24,iVar3);
      if (local_24 != (undefined1 *)0x0) {
        __memzero(local_24,iVar3);
        puVar1 = local_24;
        *local_24 = (char)uVar2;
        local_24[1] = *(undefined1 *)(param_2 + 4);
        memmove(local_24 + 2,(void *)(param_2 + 5),6);
        *(short *)(puVar1 + 8) = (short)__n;
        memmove(puVar1 + 10,(void *)(param_2 + 0xf),__n);
        MlmeEnqueue(param_1,0x30,0,iVar3,local_24,0);
        os_free_mem(local_24);
        return 0;
      }
      if (-1 < DebugLevel) {
        printk("%s() allocate event memory failed \n","rrm_send_nr_rsp_ie");
        return 3;
      }
      return 3;
    }
    if (-1 < DebugLevel) {
      printk("%s nr rsp ie len(%d) is too long","rrm_send_nr_rsp_ie",__n);
      return 1;
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s() length check failed nr_rsp_data_len=%d, Len=%d\n","rrm_send_nr_rsp_ie");
    return 1;
  }
  return 1;
}

