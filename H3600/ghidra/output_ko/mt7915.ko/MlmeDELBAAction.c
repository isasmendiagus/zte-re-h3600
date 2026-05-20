// module: mt7915.ko
// function: MlmeDELBAAction @ 0xa2a04
// size: 428 bytes
//

void MlmeDELBAAction(int param_1,ushort *param_2)

{
  int iVar1;
  undefined4 local_48;
  int local_44;
  undefined1 auStack_3e [24];
  undefined1 local_26;
  undefined1 local_25;
  byte local_23;
  undefined2 local_22;
  
  local_48 = 0;
  if (2 < DebugLevel) {
    printk(&_LC27,"MlmeDELBAAction");
  }
  iVar1 = MlmeDelBAReqSanity(param_1,param_2,*(undefined4 *)(param_2 + 0x484));
  if (iVar1 == 1) {
    __memzero(auStack_3e,0x1e);
    local_44 = os_alloc_mem(param_1,&local_48,0x900);
    if (local_44 == 0) {
      iVar1 = *(int *)(param_1 + (uint)*param_2 * 0x14c0 + 0xa1d28);
      if (iVar1 == 0) {
        if (-1 < DebugLevel) {
          printk("%s():No binding wdev for wcid(%d)\n","MlmeDELBAAction");
        }
        os_free_mem(local_48);
      }
      else {
        ActHeaderInit(param_1,auStack_3e,param_1 + (uint)*param_2 * 0x14c0 + 0xa1e0c,iVar1 + 0x1b,
                      iVar1 + 0x21);
        local_23 = local_23 & 7 | (*(byte *)((int)param_2 + 9) & 1) << 3 | (char)param_2[4] << 4;
        local_26 = 3;
        local_25 = 2;
        local_22 = 0x27;
        MakeOutgoingFrame(local_48,&local_44,0x1e,auStack_3e,0xffffffff);
        MiniportMMRequest(param_1,1,local_48,local_44);
        os_free_mem(local_48);
        if (2 < DebugLevel) {
          printk("%s Initiator = %d DELBA sent\n","MlmeDELBAAction",
                 *(undefined1 *)((int)param_2 + 9));
        }
      }
    }
    else if (-1 < DebugLevel) {
      printk("BA - MlmeDELBAAction() allocate memory failed.\n");
    }
  }
  return;
}

