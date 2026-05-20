// module: mt7915.ko
// function: wext_send_proxy_arp_event @ 0x2250e0
// size: 336 bytes
//

void wext_send_proxy_arp_event
               (undefined4 param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,
               undefined4 *param_5,char param_6,undefined1 param_7,undefined1 param_8)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 *local_2c [2];
  
  if (param_6 == '\0') {
    uVar3 = 0x1d;
  }
  else if (param_6 == '\x01') {
    uVar3 = 0x35;
  }
  else {
    uVar3 = 0x15;
  }
  os_alloc_mem(0,local_2c,uVar3);
  if (local_2c[0] != (undefined4 *)0x0) {
    __memzero(local_2c[0],uVar3);
    puVar1 = local_2c[0];
    uVar2 = RtmpOsGetNetIfIndex(param_1);
    *(char *)(puVar1 + 1) = param_6;
    *(undefined1 *)((int)puVar1 + 5) = param_7;
    *puVar1 = uVar2;
    *(undefined1 *)((int)puVar1 + 6) = param_8;
    *(undefined4 *)((int)puVar1 + 7) = *param_2;
    *(undefined2 *)((int)puVar1 + 0xb) = *(undefined2 *)(param_2 + 1);
    *(undefined4 *)((int)puVar1 + 0xd) = *param_4;
    *(undefined2 *)((int)puVar1 + 0x11) = *(undefined2 *)(param_4 + 1);
    if (param_6 == '\0') {
      *(undefined4 *)((int)puVar1 + 0x13) = *param_3;
      *(undefined4 *)((int)puVar1 + 0x17) = *param_5;
    }
    else if (param_6 == '\x01') {
      uVar5 = param_3[2];
      uVar2 = param_3[3];
      uVar4 = *param_3;
      *(undefined4 *)((int)puVar1 + 0x17) = param_3[1];
      *(undefined4 *)((int)puVar1 + 0x13) = uVar4;
      *(undefined4 *)((int)puVar1 + 0x1b) = uVar5;
      *(undefined4 *)((int)puVar1 + 0x1f) = uVar2;
      uVar5 = param_5[1];
      uVar2 = param_5[2];
      uVar4 = param_5[3];
      *(undefined4 *)((int)puVar1 + 0x23) = *param_5;
      *(undefined4 *)((int)puVar1 + 0x27) = uVar5;
      *(undefined4 *)((int)puVar1 + 0x2b) = uVar2;
      *(undefined4 *)((int)puVar1 + 0x2f) = uVar4;
    }
    else {
      printk("error not such ip type packet\n");
    }
    RtmpOSWrielessEventSend(param_1,1,0x93b,0,local_2c[0],uVar3);
    os_free_mem(local_2c[0]);
  }
  return;
}

