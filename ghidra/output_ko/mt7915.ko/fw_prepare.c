// module: mt7915.ko
// function: fw_prepare @ 0x174154
// size: 552 bytes
//

void fw_prepare(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  bool bVar2;
  
  if ("Get_RBIST_IQ_Data_Proc"[param_1 + 0x14] == '\0') {
    bVar2 = DebugLevel < 0;
    *(undefined **)(param_1 + 0xa785ac) = &mt7915_rom_patch_e1;
    *(undefined4 *)(param_1 + 0xa785b0) = 0x1f4d0;
    *(char **)(param_1 + 0xa785b4) = "mt7915_patch_e1_hdr.bin";
    if (bVar2) {
      *(undefined4 *)(param_1 + 0xa78538) = 0x100d40;
      *(char **)(param_1 + 0xa7853c) = "WIFI_RAM_CODE_MT7915.bin";
      *(undefined **)(param_1 + 0xa78534) = &MT7915_FirmwareImage_E1;
      goto LAB_001741cc;
    }
    printk("%s():using E1 ROM patch\n","fw_prepare",&mt7915_rom_patch_e1,"mt7915_patch_e1_hdr.bin",
           param_4);
    cVar1 = "Get_RBIST_IQ_Data_Proc"[param_1 + 0x14];
  }
  else if ("Get_RBIST_IQ_Data_Proc"[param_1 + 0x14] == '\x01') {
    bVar2 = DebugLevel < 0;
    *(undefined **)(param_1 + 0xa785ac) = &mt7915_rom_patch_e2;
    *(undefined4 *)(param_1 + 0xa785b0) = 0x232a0;
    *(char **)(param_1 + 0xa785b4) = "mt7915_patch_e2_hdr.bin";
    if (bVar2) goto LAB_0017422c;
    printk("%s():using E2 ROM patch\n","fw_prepare",0x232a0,"mt7915_patch_e2_hdr.bin",param_4);
    cVar1 = "Get_RBIST_IQ_Data_Proc"[param_1 + 0x14];
  }
  else {
    bVar2 = DebugLevel < 0;
    *(undefined **)(param_1 + 0xa785ac) = &mt7915_rom_patch_e2;
    *(undefined4 *)(param_1 + 0xa785b0) = 0x232a0;
    *(char **)(param_1 + 0xa785b4) = "mt7915_patch_e2_hdr.bin";
    if (bVar2) {
LAB_0017422c:
      *(undefined4 *)(param_1 + 0xa78538) = 0x133da8;
      *(char **)(param_1 + 0xa7853c) = "WIFI_RAM_CODE_MT7915_E2.bin";
      *(undefined **)(param_1 + 0xa78534) = &MT7915_FirmwareImage_E2;
      goto LAB_001741cc;
    }
    printk("%s():Rom patch is not E1 or E2, so using the default E2 ROM patch\n","fw_prepare",
           0x232a0,"mt7915_patch_e2_hdr.bin",param_4);
    cVar1 = "Get_RBIST_IQ_Data_Proc"[param_1 + 0x14];
  }
  if (cVar1 == '\0') {
    bVar2 = -1 < DebugLevel;
    *(undefined4 *)(param_1 + 0xa78538) = 0x100d40;
    *(char **)(param_1 + 0xa7853c) = "WIFI_RAM_CODE_MT7915.bin";
    *(undefined **)(param_1 + 0xa78534) = &MT7915_FirmwareImage_E1;
    if (bVar2) {
      printk("%s():using E1 RAM\n","fw_prepare",0x100d40,"WIFI_RAM_CODE_MT7915.bin",param_4);
    }
  }
  else if (cVar1 == '\x01') {
    bVar2 = -1 < DebugLevel;
    *(char **)(param_1 + 0xa7853c) = "WIFI_RAM_CODE_MT7915_E2.bin";
    *(undefined4 *)(param_1 + 0xa78538) = 0x133da8;
    *(undefined **)(param_1 + 0xa78534) = &MT7915_FirmwareImage_E2;
    if (bVar2) {
      printk("%s():using E2 RAM\n","fw_prepare",0x133da8,"WIFI_RAM_CODE_MT7915_E2.bin",param_4);
    }
  }
  else {
    bVar2 = -1 < DebugLevel;
    *(char **)(param_1 + 0xa7853c) = "WIFI_RAM_CODE_MT7915_E2.bin";
    *(undefined4 *)(param_1 + 0xa78538) = 0x133da8;
    *(undefined **)(param_1 + 0xa78534) = &MT7915_FirmwareImage_E2;
    if (bVar2) {
      printk("%s():RAM is not E1 or E2, so using the default E2 RAM\n","fw_prepare",0x133da8,
             "WIFI_RAM_CODE_MT7915_E2.bin",param_4);
    }
  }
LAB_001741cc:
  *(undefined **)(param_1 + 0xa78570) = &MT7915_WA_FirmwareImage;
  *(undefined4 *)(param_1 + 0xa78574) = 0x195e0;
  *(char **)(param_1 + 0xa78578) = "7915_WACPU_RAM_CODE_release.bin";
  return;
}

