// module: mt7915.ko
// function: set_mec_ctrl @ 0xe938c
// size: 972 bytes
//

undefined4 set_mec_ctrl(undefined4 param_1,undefined4 param_2)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  ushort local_2e;
  undefined2 local_2c;
  undefined2 local_2a;
  undefined2 local_28;
  undefined2 local_26;
  ushort local_24 [2];
  undefined2 local_20;
  undefined2 local_1e;
  undefined2 local_1c;
  
  uVar4 = 0;
  local_2e = 0;
  local_2c = 0;
  local_2a = 0;
  local_28 = 0;
  local_26 = 0;
  iVar2 = rstrtok(param_2,&_LC547);
  if (iVar2 == 0) {
switchD_000e9578_default:
    if (((((((0 < DebugLevel) && (printk("Wrong Cmd Format. Plz input:\n"), 0 < DebugLevel)) &&
           (printk("iwpriv ra0 set mec_ctrl=[0]-[1]-[2]-[3]-[4]\n"), 0 < DebugLevel)) &&
          ((printk("  [0]=0: Read Info: =0-[1]\n"), 0 < DebugLevel &&
           (printk(
                  "                 , [1]: Read Type (Optional, 0 for all, BIT(1) for Algo En, BIT(2) for Algo Thr)\n"
                  ), 0 < DebugLevel)))) &&
         ((printk("  [0]=1: Set AMSDU Algo Enable: =1-[1]-[2] \n"), 0 < DebugLevel &&
          ((printk("                 , [1]: Wlan Idx (65535 for all)\n"), 0 < DebugLevel &&
           (printk("                 , [2]: Enable (0, 1 for Disable, Enable)\n"), 0 < DebugLevel)))
          ))) && (printk("  [0]=2: Set WTBL AMSDU Parameters: =2-[1]-[2]-[3]-[4]\n"), 0 < DebugLevel
                 )) &&
       ((((printk("                 , [1]: Wlan Idx (65535 for all)\n"), 0 < DebugLevel &&
          (printk("                 , [2]: Enable (0, 1 for Disable, Enable)\n"), 0 < DebugLevel))
         && (printk("                 , [3]: Number (0-7 for AMSDU Num 1-8)\n"), 0 < DebugLevel)) &&
        (((printk("                 , [4]: Length (1-31 for 255-7935 Bytes, unit 256 Bytes)\n"),
          0 < DebugLevel &&
          (printk("  [0]=3: Set PHY Rate Threshold of AMSDU Length: =3-[1]-[2]-[3]\n"),
          0 < DebugLevel)) &&
         ((printk("                 , [1]: BA Numer (0, 1 for BA 64, 256)\n"), 0 < DebugLevel &&
          ((printk("                 , [2]: Amsdu Number (1-3 for AMSDU Num 2-4)\n"), 0 < DebugLevel
           && (printk(
                     "                 , [3]: Threshold of PHY Rate (1-65535, unit: Mbps, 0 for reset default)\n"
                     ), 0 < DebugLevel)))))))))) {
      printk(
            "                 e.g. =3-1-300 means if current PHY rate > 300Mbps, then set AMSDU Len of 2 num\n"
            );
    }
switchD_000e9458_default:
    uVar3 = 0;
  }
  else {
    do {
      uVar1 = os_str_toul(iVar2,0,10);
      (&local_2e)[uVar4] = uVar1;
      iVar2 = rstrtok(0,&_LC547);
      uVar1 = local_2e;
      uVar4 = uVar4 + 1 & 0xff;
    } while (iVar2 != 0);
    if ((uVar4 == 0) || (7 < local_2e)) goto switchD_000e9578_default;
    os_zero_mem(local_24,0xc);
    local_24[0] = uVar1;
    if (0 < DebugLevel) {
      printk("%s: u2Action=%u\n","set_mec_ctrl",uVar1);
      switch(local_24[0]) {
      case 0:
        local_20 = local_2c;
        if (0 < DebugLevel) {
          printk("%s: u2ReadType=%u\n","set_mec_ctrl");
        }
        goto LAB_000e94a0;
      case 1:
        if (uVar4 == 3) goto LAB_000e9508;
        break;
      case 2:
        if (uVar4 == 5) goto LAB_000e94bc;
        break;
      case 3:
        if (uVar4 == 4) goto LAB_000e9480;
      }
      goto switchD_000e9578_default;
    }
    switch(uVar1) {
    case 0:
      local_20 = local_2c;
      break;
    case 1:
      if (uVar4 != 3) goto switchD_000e9458_default;
LAB_000e9508:
      local_20 = local_2c;
      local_1e = CONCAT11(local_1e._1_1_,(undefined1)local_2a);
      if (0 < DebugLevel) {
        printk("%s: u2WlanIdx=%u, u1AmsduAlgoEn=%u\n","set_mec_ctrl");
      }
      break;
    case 2:
      if (uVar4 != 5) goto switchD_000e9458_default;
LAB_000e94bc:
      local_20 = local_2c;
      local_1c = local_26;
      local_1e = CONCAT11((undefined1)local_28,(undefined1)local_2a);
      if (0 < DebugLevel) {
        printk("%s: u2WlanIdx=%u, u1AmsduEn=%u, u1AmsduNum=%u, u2AmsduLen=%u\n","set_mec_ctrl",
               local_2c,(undefined1)local_2a,(undefined1)local_28,local_26);
      }
      break;
    case 3:
      if (uVar4 != 4) goto switchD_000e9458_default;
LAB_000e9480:
      local_1e = local_28;
      local_20 = CONCAT11((undefined1)local_2a,(undefined1)local_2c);
      if (0 < DebugLevel) {
        printk("%s: u1BaNum=%u, u1AmsduNum=%u, u2AmsduRateThr=%u\n","set_mec_ctrl",
               (undefined1)local_2c,(undefined1)local_2a,local_28);
      }
      break;
    default:
      goto switchD_000e9458_default;
    }
LAB_000e94a0:
    CmdMecCtrl(param_1,local_24);
    uVar3 = 1;
  }
  return uVar3;
}

