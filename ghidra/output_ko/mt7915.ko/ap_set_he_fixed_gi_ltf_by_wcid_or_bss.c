// module: mt7915.ko
// function: ap_set_he_fixed_gi_ltf_by_wcid_or_bss @ 0xcf74c
// size: 644 bytes
//

void ap_set_he_fixed_gi_ltf_by_wcid_or_bss
               (int param_1,uint param_2,int param_3,uint param_4,int param_5)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int *piVar4;
  undefined2 local_3a;
  undefined1 local_38;
  undefined2 local_37;
  undefined1 local_35;
  char *apcStack_34 [4];
  
  local_38 = 0xaa;
  local_3a = 0x5500;
  apcStack_34[2] = "GI_32_US + LTF_4x";
  apcStack_34[1] = "GI_16_US + LTF_2x";
  apcStack_34[0] = "GI_08_US + LTF_2x";
  local_37 = 0x5555;
  local_35 = 0xaa;
  if (2 < DebugLevel) {
    printk("%s:: Enter.\n","ap_set_he_fixed_gi_ltf_by_wcid_or_bss");
  }
  if (param_1 != 0) {
    if (param_2 < 3) {
      if (param_3 == 0) {
        uVar1 = HcGetMaxStaNum(param_1);
        if (param_4 < uVar1) {
          snd_ra_fw_cmd(0xb,param_1,param_4,(int)&local_3a + param_2);
          snd_ra_fw_cmd(7,param_1,param_4,(int)&local_37 + param_2);
          if (2 < DebugLevel) {
            printk("%s:: Set %s by wcid success.\n","ap_set_he_fixed_gi_ltf_by_wcid_or_bss",
                   apcStack_34[param_2]);
          }
        }
        else if (2 < DebugLevel) {
          printk("%s:: Invalid wcid value(%d)!!!.\n","ap_set_he_fixed_gi_ltf_by_wcid_or_bss",param_4
                );
        }
      }
      else if (param_3 == 1) {
        if (param_5 == 0) {
          if (-1 < DebugLevel) {
            printk("%s:: Invalid wdev!!!.\n","ap_set_he_fixed_gi_ltf_by_wcid_or_bss");
          }
        }
        else {
          uVar1 = HcGetMaxStaNum(param_1);
          piVar4 = (int *)(param_1 + 0xa1d28);
          for (uVar3 = 0; (uVar2 = HcGetMaxStaNum(param_1), uVar3 < uVar2 && (uVar3 <= uVar1));
              uVar3 = uVar3 + 1) {
            if ((piVar4[-2] == 0x20001) && (*piVar4 == param_5 && *piVar4 != 0)) {
              snd_ra_fw_cmd(0xb,param_1,uVar3,(int)&local_3a + param_2);
              snd_ra_fw_cmd(7,param_1,param_4,(int)&local_37 + param_2);
            }
            piVar4 = piVar4 + 0x530;
          }
          if (2 < DebugLevel) {
            printk("%s:: Set %s by BSS success.\n","ap_set_he_fixed_gi_ltf_by_wcid_or_bss",
                   apcStack_34[param_2]);
          }
        }
      }
      else if (-1 < DebugLevel) {
        printk("%s:: Wrong gi mode(%d)!!!.\n","ap_set_he_fixed_gi_ltf_by_wcid_or_bss",param_3);
      }
    }
    else if (-1 < DebugLevel) {
      printk("%s:: Wrong gi value(%d)!!!.\n","ap_set_he_fixed_gi_ltf_by_wcid_or_bss",param_2);
    }
  }
  return;
}

