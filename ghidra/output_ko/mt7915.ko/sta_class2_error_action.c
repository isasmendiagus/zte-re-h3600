// module: mt7915.ko
// function: sta_class2_error_action @ 0x76c54
// size: 288 bytes
//

void sta_class2_error_action(int param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined2 local_3a;
  undefined4 local_38;
  undefined4 local_34;
  undefined1 auStack_30 [28];
  
  uVar3 = *(undefined4 *)(param_1 + 8);
  local_38 = 0;
  local_34 = 0;
  local_3a = 6;
  iVar1 = GetStaCfgByWdev(uVar3,param_1);
  iVar2 = os_alloc_mem(uVar3,&local_38,0x900);
  if (iVar2 == 0) {
    if (2 < DebugLevel) {
      printk("AUTH - Class 2 error, Send DEAUTH frame...\n");
    }
    MgtMacHeaderInitExt(uVar3,auStack_30,0xc,0,param_2,iVar1 + 0x1b,iVar1 + 0x413a);
    MakeOutgoingFrame(local_38,&local_34,0x18,auStack_30,2,&local_3a,0xffffffff);
    MiniportMMRequest(uVar3,0,local_38,local_34);
    os_free_mem(local_38);
    *(undefined2 *)(iVar1 + 0x2131f8) = local_3a;
    *(undefined4 *)(iVar1 + 0x2131fa) = *param_2;
    *(undefined2 *)(iVar1 + 0x2131fe) = *(undefined2 *)(param_2 + 1);
  }
  return;
}

