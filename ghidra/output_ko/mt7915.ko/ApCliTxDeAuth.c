// module: mt7915.ko
// function: ApCliTxDeAuth @ 0x3131c
// size: 440 bytes
//

undefined4 ApCliTxDeAuth(int *param_1)

{
  int iVar1;
  uint uVar2;
  undefined *puVar3;
  undefined2 local_3a;
  undefined4 local_38;
  undefined4 local_34;
  undefined1 auStack_30 [28];
  
  local_3a = 3;
  local_38 = 0;
  local_34 = 0;
  if (*(int *)(*param_1 + 0x38) == 0x400) {
    uVar2 = (uint)*(byte *)(*param_1 + 0x3c);
    if (2 < DebugLevel) {
      printk("%s : ifIndex=%u\n","ApCliTxDeAuth",uVar2);
    }
    if ((uVar2 < 2) && (iVar1 = os_alloc_mem(param_1,&local_38,0x900), iVar1 == 0)) {
      if (uVar2 == 0) {
        puVar3 = &DAT_00371c92 + (int)param_1;
        __ZTE_STA_Assoc_Process(param_1,0x11,puVar3,0xffffffff,local_3a,0,0,"ApCliTxDeAuth",0x3ff5);
      }
      else {
        puVar3 = &DAT_00371c92 + (int)(param_1 + uVar2 * 0x84dec);
        __ZTE_STA_Assoc_Process(param_1,0x11,puVar3,0xfffffffb,local_3a,0,0,"ApCliTxDeAuth",0x3ff9);
      }
      if (2 < DebugLevel) {
        printk("%s: DE-AUTH request (Reason=%d)...\n","ApCliTxDeAuth",local_3a);
      }
      ApCliMgtMacHeaderInit(param_1,auStack_30,0xc,0,puVar3,puVar3,uVar2);
      MakeOutgoingFrame(local_38,&local_34,0x18,auStack_30,2,&local_3a,0xffffffff);
      MiniportMMRequest(param_1,0,local_38,local_34);
      os_free_mem(local_38);
      return 1;
    }
  }
  return 0;
}

