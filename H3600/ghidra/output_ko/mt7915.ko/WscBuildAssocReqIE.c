// module: mt7915.ko
// function: WscBuildAssocReqIE @ 0x1e5038
// size: 496 bytes
//

void WscBuildAssocReqIE(int *param_1,int param_2,char *param_3)

{
  int iVar1;
  undefined1 local_35;
  int local_34;
  int local_30;
  int local_2c;
  undefined1 local_26;
  char local_25;
  undefined1 local_24;
  undefined1 local_23;
  undefined1 local_22;
  undefined1 local_21;
  
  local_34 = 0;
  local_2c = 0;
  local_35 = 0;
  if (param_1 == (int *)0x0) {
    if (-1 < DebugLevel) {
      printk("WscBuildAssocReqIE: pWscControl is NULL\n");
    }
  }
  else {
    if (2 < DebugLevel) {
      printk("-----> WscBuildAssocReqIE\n");
    }
    os_alloc_mem(0,&local_34,0x200);
    if (local_34 == 0) {
      if (-1 < DebugLevel) {
        printk("%s: Allocate memory fail!!!\n","WscBuildAssocReqIE");
      }
    }
    else {
      local_30 = local_34;
      local_26 = 0xdd;
      local_25 = '\x04';
      local_21 = 4;
      local_22 = 0xf2;
      local_24 = 0;
      local_2c = 0;
      local_23 = 0x50;
      iVar1 = AppendWSCTLV(0x104a,local_34,param_1 + 0x1c,0);
      if (*param_1 == 1) {
        local_35 = 0;
      }
      local_30 = local_30 + iVar1;
      local_2c = local_2c + iVar1;
      if (*param_1 != 1) {
        local_35 = 2;
      }
      iVar1 = AppendWSCTLV(0x103a,local_30,&local_35,0);
      local_30 = local_30 + iVar1;
      local_2c = iVar1 + local_2c;
      if (*(char *)((int)param_1 + 0x2b31) != '\0') {
        WscGenV2Msg(param_1,0,0,0,&local_30,&local_2c);
      }
      local_25 = (char)local_2c + local_25;
      RTMPMoveMemory(param_2,&local_26,6);
      RTMPMoveMemory(param_2 + 6,local_34,local_2c);
      *param_3 = (char)local_2c + '\x06';
      if (local_34 != 0) {
        os_free_mem();
      }
      if (2 < DebugLevel) {
        printk("<----- WscBuildAssocReqIE\n");
      }
    }
  }
  return;
}

