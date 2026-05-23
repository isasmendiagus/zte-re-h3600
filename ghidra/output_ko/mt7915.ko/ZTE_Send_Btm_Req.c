// module: mt7915.ko
// function: ZTE_Send_Btm_Req @ 0x15c6e4
// size: 508 bytes
//

undefined4
ZTE_Send_Btm_Req(int *param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4,
                undefined4 *param_5)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int local_44;
  undefined4 local_3e;
  undefined4 local_3a;
  undefined4 local_36;
  undefined4 local_32;
  undefined4 local_2e;
  undefined2 local_2a;
  
  local_3e = 0xa001e07;
  *(undefined4 *)(*param_1 + 0x3c) = param_2;
  local_3a = 0x1034;
  local_36 = 0;
  local_32 = 0;
  local_2e = 0x3070000;
  local_2a = 0xff01;
  local_44 = 0;
  os_alloc_mem(0,&local_44,0x29);
  if (local_44 == 0) {
    if (DebugLevel < 0) {
      uVar3 = 0xffffffff;
    }
    else {
      printk("zte_btm_req mem alloc fail!\n");
      uVar3 = 0xffffffff;
    }
  }
  else {
    __memzero(local_44,0x29);
    *(undefined4 *)(local_44 + 4) = *param_3;
    uVar1 = *(undefined2 *)(param_3 + 1);
    *(undefined4 *)(local_44 + 0x13) = local_3e;
    *(undefined2 *)(local_44 + 8) = uVar1;
    *(undefined2 *)(local_44 + 0x27) = local_2a;
    *(undefined4 *)(local_44 + 0x1b) = local_36;
    *(undefined4 *)(local_44 + 0x17) = local_3a;
    *(undefined4 *)(local_44 + 0x23) = local_2e;
    *(undefined4 *)(local_44 + 0x1f) = local_32;
    iVar2 = DebugLevel;
    *(undefined4 *)(local_44 + 0x19) = *param_5;
    uVar1 = *(undefined2 *)(param_5 + 1);
    *(char *)(local_44 + 0x24) = (char)param_4;
    *(undefined1 *)(local_44 + 0x10) = 0;
    *(undefined2 *)(local_44 + 0x1d) = uVar1;
    *(undefined1 *)(local_44 + 0x11) = 0;
    *(undefined1 *)(local_44 + 0x12) = 0;
    *(undefined1 *)(local_44 + 0xf) = 0x16;
    if ((0 < iVar2) &&
       (printk("(%s)sta_mac=%02x:%02x:%02x:%02x:%02x:%02x\n","ZTE_Send_Btm_Req",
               *(undefined1 *)param_3,*(undefined1 *)((int)param_3 + 1),
               *(undefined1 *)((int)param_3 + 2),*(undefined1 *)((int)param_3 + 3),
               *(undefined1 *)(param_3 + 1),*(undefined1 *)((int)param_3 + 5)), 0 < DebugLevel)) {
      uVar4 = (uint)*(byte *)((int)param_5 + 3);
      uVar5 = (uint)*(byte *)((int)param_5 + 2);
      uVar7 = (uint)*(byte *)(param_5 + 1);
      uVar6 = (uint)*(byte *)((int)param_5 + 5);
      printk("(%s)target_bssid=%02x:%02x:%02x:%02x:%02x:%02x\n","ZTE_Send_Btm_Req",
             *(undefined1 *)param_5,*(undefined1 *)((int)param_5 + 1),uVar5,uVar4,uVar7,uVar6);
      if (0 < DebugLevel) {
        printk("(%s)channel=%d\n","ZTE_Send_Btm_Req",param_4,DebugLevel,uVar5,uVar4,uVar7,uVar6);
      }
    }
    send_btm_req_ie(param_1,local_44,0x29);
    os_free_mem(local_44);
    uVar3 = 0;
  }
  return uVar3;
}

