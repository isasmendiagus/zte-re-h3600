// FUN_c027e00c @ c027e00c
// matched: couldn't add resources to dwc3 device, couldn't allocate dwc3 device, failed to register dwc3 device
//

int FUN_c027e00c(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 auStack_60 [9];
  undefined1 local_57;
  undefined1 local_54;
  byte local_53;
  byte local_52;
  undefined4 local_50;
  undefined4 local_4c;
  char *local_48;
  undefined4 local_44;
  undefined4 local_34;
  char *local_2c;
  undefined4 local_28;
  
  iVar1 = FUN_c01b9c54();
  iVar3 = param_1 + 0x68;
  if (iVar1 != 0) {
    FUN_c01e9794(iVar3,s_failed_to_enable_pci_device_c05b9de0);
    return -0x13;
  }
  FUN_c01b9a8c(param_1);
  iVar1 = FUN_c01ee13c(&DAT_c05b8b80,0xfffffffe);
  if (iVar1 == 0) {
    FUN_c01e9794(iVar3,s_couldn_t_allocate_dwc3_device_c05b9e00);
    return -0xc;
  }
  FUN_c0181880(&local_50,0x38);
  local_50 = *(undefined4 *)(param_1 + 0x1c8);
  local_4c = *(undefined4 *)(param_1 + 0x1cc);
  local_34 = *(undefined4 *)(param_1 + 0x1c4);
  local_48 = s_dwc_usb3_c05b9e20;
  local_2c = s_dwc_usb3_c05b9e20;
  local_44 = 0x200;
  local_28 = 0x400;
  iVar2 = FUN_c01ed8f4(iVar1,&local_50,2);
  if (iVar2 != 0) {
    FUN_c01e9794(iVar3,s_couldn_t_add_resources_to_dwc3_d_c05b9e2c);
    return iVar2;
  }
  *(int *)(param_1 + 0xc0) = iVar1;
  if (*(int *)(param_1 + 0x20) == 0x79121022) {
    FUN_c0181880(auStack_60,0x10);
    local_54 = 0xf;
    local_52 = local_52 & 0xc4 | 0x1f;
    local_53 = 0xff;
    iVar2 = FUN_c01ed94c(*(undefined4 *)(param_1 + 0xc0),auStack_60,0x10);
LAB_c027e154:
    if (iVar2 != 0) goto LAB_c027e15c;
  }
  else if ((*(short *)(param_1 + 0x20) == 0x16c3) &&
          ((ushort)(*(short *)(param_1 + 0x22) + 0x5433U) < 3)) {
    FUN_c0181880(auStack_60,0x10);
    local_57 = 1;
    local_53 = local_53 | 2;
    iVar2 = FUN_c01ed94c(*(undefined4 *)(param_1 + 0xc0),auStack_60,0x10);
    goto LAB_c027e154;
  }
  *(int *)(iVar1 + 0x10) = iVar3;
  iVar2 = FUN_c01ed998(iVar1);
  if (iVar2 == 0) {
    return 0;
  }
  FUN_c01e9794(iVar3,s_failed_to_register_dwc3_device_c05b9e54);
LAB_c027e15c:
  FUN_c01ed858(iVar1);
  return iVar2;
}

