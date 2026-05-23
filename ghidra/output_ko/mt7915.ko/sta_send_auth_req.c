// module: mt7915.ko
// function: sta_send_auth_req @ 0x76678
// size: 1104 bytes
//

undefined4
sta_send_auth_req(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined2 param_5,
                 int param_6,int param_7)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined2 *puVar5;
  undefined4 uVar6;
  undefined2 *puVar7;
  undefined4 uVar8;
  short *psVar9;
  undefined4 uVar10;
  undefined1 uStack_5f;
  undefined2 local_5e;
  undefined2 local_5c;
  short local_5a;
  undefined4 local_58;
  int local_54;
  int local_50;
  int local_4c;
  undefined4 local_46;
  undefined2 local_42;
  undefined1 auStack_40 [28];
  
  iVar4 = *(int *)(param_2 + 0x92c);
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  iVar2 = GetStaCfgByWdev(param_1,iVar4);
  bVar1 = *(byte *)(iVar4 + 0xe);
  if (iVar2 == 0) {
    printk(&_LC3,0x43);
    dump_stack();
  }
  if (iVar4 == 0) {
    printk(&_LC1,0x44);
    dump_stack();
  }
  if (2 < DebugLevel) {
    printk(&_LC0,"sta_send_auth_req");
  }
  if ((iVar2 == 0) ||
     (((*(char *)(param_1 + 0x286285) == '\x01' && (*(int *)(iVar4 + 0x14) == 2)) &&
      (iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0)),
      *(byte *)(iVar3 + 0x14a) <= bVar1)))) {
    return 0;
  }
  if (*(char *)(iVar2 + 0x2127b8) == '\x01') {
    if (2 < DebugLevel) {
      printk("%s - Block Auth request durning WPA block period!\n",param_4);
    }
    auth_fsm_state_transition(iVar4,0,"sta_send_auth_req");
    local_5a = 0x53;
  }
  else {
    iVar3 = MlmeAuthReqSanity(param_1,*(undefined4 *)(param_2 + 0x92c),param_2,
                              *(undefined4 *)(param_2 + 0x908),&local_46,&local_58,&local_5e);
    if (iVar3 == 0) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("%s(): %s sanity check fail\n","sta_send_auth_req",param_4);
      return 0;
    }
    RTMPCancelTimer(param_3,&uStack_5f);
    *(undefined4 *)(iVar2 + 0x413a) = local_46;
    *(undefined2 *)(iVar2 + 0x413e) = local_42;
    *(undefined2 *)(iVar2 + 0x4162) = local_5e;
    local_5c = param_5;
    local_5a = 0;
    iVar3 = os_alloc_mem(param_1,&local_54,0x900);
    if (iVar3 == 0) {
      if ((iVar4 != 0) && (*(int *)(iVar4 + 0x14) == 2)) {
        if (*(byte *)(iVar4 + 0x1a) < 0xf) {
          __ZTE_STA_Assoc_Process
                    (param_1,0x14,&local_46,0xffffffff,local_5a + 200,0,0,"sta_send_auth_req",0x6d);
        }
        else {
          __ZTE_STA_Assoc_Process
                    (param_1,0x14,&local_46,0xfffffffb,local_5a + 200,0,0,"sta_send_auth_req",0x71);
        }
      }
      if (2 < DebugLevel) {
        printk("%s - Send AUTH request seq#1 (Alg=%d)...\n",param_4,local_5e);
      }
      MgtMacHeaderInitExt(param_1,auStack_40,0xb,0,&local_46,iVar4 + 0x1b,iVar2 + 0x413a);
      puVar7 = &local_5c;
      psVar9 = &local_5a;
      puVar5 = &local_5e;
      uVar6 = 2;
      uVar8 = 2;
      uVar10 = 0xffffffff;
      MakeOutgoingFrame(local_54,&local_50,0x18,auStack_40,2,puVar5,2,puVar7,2,psVar9,0xffffffff);
      if (param_6 != 0 && param_7 != 0) {
        MakeOutgoingFrame(local_54 + local_50,&local_4c,param_7,param_6,0xffffffff,puVar5,uVar6,
                          puVar7,uVar8,psVar9,uVar10);
        local_50 = local_4c + local_50;
      }
      MiniportMMRequest(param_1,0,local_54,local_50);
      os_free_mem(local_54);
      if (2 < DebugLevel) {
        printk("%s:Set auth Timeout(%ld)ms\n","sta_send_auth_req",local_58);
      }
      RTMPSetTimer(param_3,local_58);
      return 1;
    }
    if (2 < DebugLevel) {
      printk("%s - MlmeAuthReqAction(Alg:%d) allocate memory failed\n",param_4,local_5e);
    }
    auth_fsm_state_transition(iVar4,0,"sta_send_auth_req");
    local_5a = 0x52;
  }
  cntl_auth_assoc_conf(*(undefined4 *)(param_2 + 0x92c),2,local_5a);
  return 0;
}

