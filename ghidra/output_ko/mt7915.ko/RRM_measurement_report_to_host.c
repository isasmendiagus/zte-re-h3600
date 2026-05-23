// module: mt7915.ko
// function: RRM_measurement_report_to_host @ 0x220a30
// size: 224 bytes
//

void RRM_measurement_report_to_host(int param_1,int param_2)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined1 *local_2c [2];
  
  iVar3 = *(int *)(param_2 + 0x908);
  uVar1 = *(undefined1 *)(param_2 + 0x1a);
  os_alloc_mem(0,local_2c,iVar3 + -7);
  puVar2 = local_2c[0];
  if (local_2c[0] == (undefined1 *)0x0) {
    if (0 < DebugLevel) {
      printk("!!!(%s) : no memory!!!\n","RRM_measurement_report_to_host");
    }
  }
  else {
    *local_2c[0] = 1;
    *(int *)(local_2c[0] + 1) = iVar3 + -0xc;
    local_2c[0][5] = uVar1;
    local_2c[0][6] = 1;
    *(size_t *)(local_2c[0] + 0x10) = iVar3 - 0x1bU;
    local_2c[0][7] = 0;
    local_2c[0][8] = 0;
    local_2c[0][9] = 0;
    *(undefined4 *)(local_2c[0] + 10) = *(undefined4 *)(param_2 + 10);
    *(undefined2 *)(local_2c[0] + 0xe) = *(undefined2 *)(param_2 + 0xe);
    memcpy(local_2c[0] + 0x14,(void *)(param_2 + 0x1b),iVar3 - 0x1bU);
    RtmpOSWrielessEventSend(*(undefined4 *)(param_1 + 4),1,0x94d,0,puVar2,iVar3 + -7);
    os_free_mem(local_2c[0]);
  }
  return;
}

