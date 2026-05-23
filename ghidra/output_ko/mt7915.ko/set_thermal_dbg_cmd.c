// module: mt7915.ko
// function: set_thermal_dbg_cmd @ 0xbb93c
// size: 748 bytes
//

undefined1 set_thermal_dbg_cmd(int param_1,char *param_2)

{
  undefined1 uVar1;
  byte bVar2;
  char *pcVar3;
  uint uVar4;
  char *local_1c;
  
  local_1c = param_2;
  if (0 < DebugLevel) {
    printk(":%s: arg = %s\n","set_thermal_dbg_cmd",param_2);
  }
  pcVar3 = strsep(&local_1c,":");
  if ((pcVar3 == (char *)0x0) || (local_1c == (char *)0x0)) {
    if (DebugLevel < 1) {
      return 0;
    }
    printk(":%s: Invalid parameters\n","set_thermal_dbg_cmd");
    return 0;
  }
  uVar1 = os_str_toul(pcVar3,0,10);
  bVar2 = os_str_toul(local_1c,0,10);
  uVar4 = (uint)bVar2;
  if (DebugLevel < 1) {
    switch(uVar1) {
    case 1:
switchD_000bb9bc_caseD_1:
      if (2 < uVar4) {
        if (DebugLevel < 1) {
          return 0;
        }
        printk(":%s: Unknown action = %d (0: thermal recal OFF; 1: thermal recal ON; 2: trigger thermal recal)\n"
               ,"set_thermal_dbg_cmd",uVar4);
        return 0;
      }
      if ((uVar4 == 2) && (*(char *)(param_1 + 0x79503d) == '\0')) {
        if (DebugLevel < 1) {
          return 0;
        }
        printk(":%s: Can\'t trigger recal in Thermal recal off mode\n","set_thermal_dbg_cmd");
        return 0;
      }
      *(byte *)(param_1 + 0x79503d) = bVar2;
      break;
    case 2:
switchD_000bb9bc_caseD_2:
      if (2 < uVar4) {
        if (DebugLevel < 1) {
          return 0;
        }
        printk(":%s: Unknown action = %d (0: Dynamic G0 OFF; 1: Dynamic G0 ON; 2: trigger Dynamic G0)\n"
               ,"set_thermal_dbg_cmd",uVar4);
        return 0;
      }
      if ((uVar4 == 2) && (*(char *)(param_1 + 0x79503e) == '\0')) {
        if (DebugLevel < 1) {
          return 0;
        }
        printk(":%s: Can\'t trigger G0 in Dynamic G0 off mode\n","set_thermal_dbg_cmd");
        return 0;
      }
      *(byte *)(param_1 + 0x79503e) = bVar2;
      break;
    case 3:
switchD_000bb9bc_caseD_3:
      if (uVar4 < 2) {
        *(byte *)(param_1 + 0x79503f) = bVar2;
        MtCmdThermalMode(param_1,uVar1,uVar4);
        return 1;
      }
      if (DebugLevel < 1) {
        return 0;
      }
      printk(":%s: Unknown action = %d (0: H-rate DPD OFF; 1: H-rate DPD ON;)\n",
             "set_thermal_dbg_cmd",uVar4);
      return 0;
    case 4:
switchD_000bb9bc_caseD_4:
      if (3 < uVar4) {
        if (DebugLevel < 1) {
          return 0;
        }
        printk(":%s: Unknown action = %d (NTLT 0:OFF; 1:ON; 2:trigger NT2LT; 3:trigger LT2NT)\n",
               "set_thermal_dbg_cmd",uVar4);
        return 0;
      }
      if ((*(char *)(param_1 + 0x795040) == '\0') && (uVar4 - 2 < 2)) {
        if (DebugLevel < 1) {
          return 0;
        }
        printk(":%s: Can\'t trigger NT2LT/LT2NT in NTLT off mode\n","set_thermal_dbg_cmd");
        return 0;
      }
      *(byte *)(param_1 + 0x795040) = bVar2;
      break;
    default:
      goto switchD_000bb9bc_default;
    }
    MtCmdThermalMode(param_1,uVar1,uVar4);
switchD_000bb9bc_default:
    return 1;
  }
  printk(":%s: mode(%d), action(%d))\n","set_thermal_dbg_cmd",uVar1,uVar4);
  switch(uVar1) {
  case 1:
    goto switchD_000bb9bc_caseD_1;
  case 2:
    goto switchD_000bb9bc_caseD_2;
  case 3:
    goto switchD_000bb9bc_caseD_3;
  case 4:
    goto switchD_000bb9bc_caseD_4;
  default:
    if (DebugLevel < 1) {
      return 1;
    }
    printk(":%s: Unknown mode(%d) (1: Thermal re-cal; 2: Dynamic G0) )\n","set_thermal_dbg_cmd",
           uVar1);
    return 1;
  }
}

