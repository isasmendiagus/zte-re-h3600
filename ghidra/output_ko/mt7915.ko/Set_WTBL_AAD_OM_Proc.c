// module: mt7915.ko
// function: Set_WTBL_AAD_OM_Proc @ 0x34600
// size: 164 bytes
//

undefined4 Set_WTBL_AAD_OM_Proc(undefined4 param_1,char *param_2)

{
  undefined1 uVar1;
  char *pcVar2;
  undefined4 uVar3;
  char *local_14 [2];
  
  local_14[0] = param_2;
  pcVar2 = strsep(local_14,":");
  if ((pcVar2 == (char *)0x0) || (local_14[0] == (char *)0x0)) {
    if (DebugLevel < 1) {
      uVar3 = 0;
    }
    else {
      printk(":%s: Invalid parameters\n","Set_WTBL_AAD_OM_Proc");
      uVar3 = 0;
    }
  }
  else {
    uVar3 = os_str_toul(pcVar2,0,10);
    uVar1 = os_str_toul(local_14[0],0,10);
    HW_SET_ASIC_WCID_AAD_OM(param_1,uVar3,uVar1);
    uVar3 = 1;
  }
  return uVar3;
}

