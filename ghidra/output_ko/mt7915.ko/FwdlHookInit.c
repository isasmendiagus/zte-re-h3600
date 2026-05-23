// module: mt7915.ko
// function: FwdlHookInit @ 0x1c81e8
// size: 4 bytes
//

undefined4 FwdlHookInit(int param_1)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(int *)(iVar1 + 0xfc) == 0) {
    bVar2 = false;
    if (*(int *)(iVar1 + 0x100) == 0) {
      *(code **)(param_1 + 0xa7852c) = ctrl_fw_state_v2;
      return 0;
    }
LAB_001c17ec:
    if (*(int *)(iVar1 + 0x108) == 0) {
      *(code **)(param_1 + 0xa7851c) = load_fw_v1;
      iVar1 = *(int *)(iVar1 + 0x110);
    }
    else {
      if (*(int *)(iVar1 + 0x108) == 1) {
        *(code **)(param_1 + 0xa7851c) = load_fw_v2_compressimg;
      }
      else {
        bVar2 = true;
      }
      iVar1 = *(int *)(iVar1 + 0x110);
    }
    if (iVar1 == 0) {
      *(code **)(param_1 + 0xa78524) = parse_fw_v1;
    }
    else if (iVar1 == 1) {
      *(code **)(param_1 + 0xa78524) = parse_fw_v2;
    }
    else {
      if (iVar1 != 2) goto LAB_001c18b4;
      *(code **)(param_1 + 0xa78524) = parse_fw_v3;
    }
  }
  else {
    bVar2 = *(int *)(iVar1 + 0x104) == 0;
    if (bVar2) {
      *(code **)(param_1 + 0xa78520) = load_patch_v1;
    }
    bVar2 = !bVar2;
    if (*(int *)(iVar1 + 0x10c) != 0) {
      if (*(int *)(iVar1 + 0x10c) == 1) {
        *(code **)(param_1 + 0xa78528) = parse_patch_v2;
        goto LAB_001c17e0;
      }
      if (*(int *)(iVar1 + 0x100) != 0) {
        bVar2 = true;
        goto LAB_001c17ec;
      }
LAB_001c18b4:
      *(code **)(param_1 + 0xa7852c) = ctrl_fw_state_v2;
      goto LAB_001c1844;
    }
    *(code **)(param_1 + 0xa78528) = parse_patch_v1;
LAB_001c17e0:
    if (*(int *)(iVar1 + 0x100) != 0) goto LAB_001c17ec;
  }
  *(code **)(param_1 + 0xa7852c) = ctrl_fw_state_v2;
  if (!bVar2) {
    return 0;
  }
LAB_001c1844:
  if (0 < DebugLevel) {
    printk("%s: FWDL hook fail\n","mt_fwdl_hook_init");
  }
  return 1;
}

