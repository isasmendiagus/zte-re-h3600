// module: mt7915.ko
// function: sta_send_event_report @ 0xa3d9c
// size: 308 bytes
//

void sta_send_event_report(undefined4 param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 local_58;
  undefined4 local_54;
  undefined1 auStack_50 [24];
  undefined1 local_38;
  undefined1 local_37;
  undefined1 local_36;
  undefined1 local_35;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 auStack_28 [12];
  
  local_58 = 0;
  iVar2 = *param_2;
  iVar1 = os_alloc_mem(param_1,&local_58,0x900);
  if (iVar1 == 0) {
    os_zero_mem(auStack_50,0x30);
    iVar1 = iVar2 + 0x21;
    ActHeaderInit(param_1,auStack_50,iVar1,iVar2 + 0x1b,iVar1);
    local_31 = (undefined1)param_2[2];
    local_36 = (undefined1)param_2[1];
    local_35 = *(undefined1 *)((int)param_2 + 5);
    local_33 = *(undefined1 *)((int)param_2 + 6);
    local_32 = *(undefined1 *)((int)param_2 + 7);
    local_38 = 10;
    local_34 = 0x13;
    local_37 = 1;
    os_move_mem(auStack_28,(void *)((int)param_2 + 9),8);
    MakeOutgoingFrame(local_58,&local_54,0x30,auStack_50,0xffffffff);
    MiniportMMRequest(param_1,1,local_58,local_54);
    os_free_mem(local_58);
    if (2 < DebugLevel) {
      printk("WNM event report\n");
    }
  }
  else if (-1 < DebugLevel) {
    printk("WNM event report allocate memory failed\n");
  }
  return;
}

