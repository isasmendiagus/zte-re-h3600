// module: mt7915.ko
// function: ap_cls3_err_action @ 0x1e6c0
// size: 360 bytes
//

void ap_cls3_err_action(int param_1,int param_2)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined2 local_3a;
  undefined4 local_38;
  undefined4 local_34;
  undefined1 auStack_30 [28];
  
  uVar1 = *(ushort *)(param_2 + 0x4e);
  local_38 = 0;
  local_34 = 0;
  local_3a = 7;
  uVar2 = HcGetMaxStaNum();
  if ((uVar1 < uVar2) &&
     (iVar3 = (uint)*(ushort *)(param_2 + 0x4e) * 0x14c0 + param_1 + 0xa1d20, iVar3 != 0)) {
    __ZTE_STA_Assoc_Process(param_1,0x11,0,0,local_3a,0,iVar3,"ap_cls3_err_action",0xc38);
    mac_entry_delete(param_1,iVar3);
  }
  iVar3 = os_alloc_mem(param_1,&local_38,0x900);
  if (iVar3 == 0) {
    if (2 < DebugLevel) {
      puVar4 = *(undefined1 **)(param_2 + 0x2c);
      printk("ASSOC - Class 3 Error, Send DISASSOC frame to %02x:%02x:%02x:%02x:%02x:%02x\n",*puVar4
             ,puVar4[1],puVar4[2],puVar4[3],puVar4[4],puVar4[5]);
    }
    MgtMacHeaderInit(param_1,auStack_30,10,0,*(undefined4 *)(param_2 + 0x2c),
                     *(undefined4 *)(param_2 + 0x28),*(undefined4 *)(param_2 + 0x28));
    MakeOutgoingFrame(local_38,&local_34,0x18,auStack_30,2,&local_3a,0xffffffff);
    MiniportMMRequest(param_1,0,local_38,local_34);
    os_free_mem(local_38);
  }
  return;
}

