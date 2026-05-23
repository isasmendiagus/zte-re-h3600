// module: mt7915.ko
// function: wext_send_owe_trans_chan_event @ 0x21ca78
// size: 344 bytes
//

void wext_send_owe_trans_chan_event
               (undefined4 param_1,undefined1 param_2,undefined4 *param_3,void *param_4,
               byte *param_5,char *param_6,char *param_7)

{
  undefined1 *puVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 *local_2c [2];
  
  local_2c[0] = (undefined1 *)0x0;
  os_alloc_mem(0,local_2c,0x3e);
  if (local_2c[0] != (undefined1 *)0x0) {
    __memzero(local_2c[0],0x3e);
    puVar1 = local_2c[0];
    local_2c[0][1] = 0x39;
    *local_2c[0] = param_2;
    local_2c[0][2] = 0;
    local_2c[0][3] = 0;
    local_2c[0][4] = 0;
    puVar2 = (undefined4 *)RtmpOsGetNetDevName(param_1);
    uVar5 = puVar2[1];
    uVar3 = puVar2[2];
    uVar4 = puVar2[3];
    *(undefined4 *)(puVar1 + 5) = *puVar2;
    *(undefined4 *)(puVar1 + 9) = uVar5;
    *(undefined4 *)(puVar1 + 0xd) = uVar3;
    *(undefined4 *)(puVar1 + 0x11) = uVar4;
    puVar2 = (undefined4 *)RtmpOsGetNetDevName(param_1);
    uVar5 = puVar2[1];
    uVar3 = puVar2[2];
    uVar4 = puVar2[3];
    *(undefined4 *)(puVar1 + 5) = *puVar2;
    *(undefined4 *)(puVar1 + 9) = uVar5;
    *(undefined4 *)(puVar1 + 0xd) = uVar3;
    *(undefined4 *)(puVar1 + 0x11) = uVar4;
    if (param_3 != (undefined4 *)0x0) {
      *(undefined4 *)(puVar1 + 0x15) = *param_3;
      *(undefined2 *)(puVar1 + 0x19) = *(undefined2 *)(param_3 + 1);
    }
    if (param_4 != (void *)0x0) {
      memcpy(puVar1 + 0x1b,param_4,(uint)*param_5);
    }
    if (param_5 != (byte *)0x0) {
      puVar1[0x3b] = *param_5;
    }
    if ((param_6 != (char *)0x0) && (*param_6 != '\0')) {
      puVar1[0x3c] = *param_6;
    }
    if ((param_7 != (char *)0x0) && (*param_7 != '\0')) {
      puVar1[0x3d] = *param_7;
    }
    RtmpOSWrielessEventSend(param_1,1,0x991,0,local_2c[0],0x3e);
    os_free_mem(local_2c[0]);
  }
  return;
}

