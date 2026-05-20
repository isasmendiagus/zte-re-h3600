// module: mt7915.ko
// function: chip_show_dma_info @ 0x18fc2c
// size: 3456 bytes
//

void chip_show_dma_info(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  uint local_40;
  undefined4 local_3c;
  undefined4 local_38;
  uint local_34;
  undefined4 local_30;
  undefined4 local_2c;
  uint local_28;
  uint local_24;
  undefined4 local_20 [3];
  
  iVar1 = hc_get_hdev_privdata();
  if ((1 < *(int *)(iVar1 + 0x286280) - 4U) && (*(int *)(iVar1 + 0x286280) != 1)) {
    return;
  }
  hif_io_read32(param_1,0xd7010,&local_40);
  hif_io_read32(param_1,0xd7014,&local_3c);
  mac_io_read32(param_1,0x7c024200,&local_38);
  mac_io_read32(param_1,0x7c024204,&local_34);
  mac_io_read32(param_1,0x7c025200,&local_30);
  mac_io_read32(param_1,0x7c025204,&local_2c);
  mac_io_read32(param_1,0x7c024208,&local_28);
  mac_io_read32(param_1,0x7c025208,&local_24);
  if ((0 < DebugLevel) && (printk("HOST_DMA Configuration\n"), 0 < DebugLevel)) {
    pcVar4 = "Glocfg";
    pcVar5 = "Tx/RxEn";
    pcVar6 = "Tx/RxBusy";
    printk("%10s %10s %10s %10s %10s %10s\n",&_LC319,"IntCSR","IntMask","Glocfg","Tx/RxEn",
           "Tx/RxBusy");
    if ((0 < DebugLevel) &&
       ((printk("%10s %10x %10x\n","Merge",local_40,local_3c,pcVar4,pcVar5,pcVar6), 0 < DebugLevel
        && (printk("%10s %10x %10x %10x %4x/%5x %4x/%5x\n",&_LC328,local_38,local_34,local_28,
                   local_28 & 1,(local_28 << 0x1d) >> 0x1f,(local_28 << 0x1e) >> 0x1f,
                   (local_28 << 0x1c) >> 0x1f), 0 < DebugLevel)))) {
      printk("%10s %10x %10x %10x %4x/%5x %4x/%5x\n",&_LC329,local_30,local_2c,local_24,local_24 & 1
             ,(local_24 << 0x1d) >> 0x1f,(local_24 << 0x1e) >> 0x1f,(local_24 << 0x1c) >> 0x1f);
    }
  }
  hif_io_read32(param_1,0xd7088,&local_40);
  hif_io_read32(param_1,0xd708c,&local_3c);
  mac_io_read32(param_1,0x7c028200,&local_38);
  mac_io_read32(param_1,0x7c028204,&local_34);
  mac_io_read32(param_1,0x7c029200,&local_30);
  mac_io_read32(param_1,0x7c029204,&local_2c);
  mac_io_read32(param_1,0x7c028208,&local_28);
  mac_io_read32(param_1,0x7c029208,&local_24);
  if (((0 < DebugLevel) && (printk("%10s %10x %10x\n","MergeP1",local_40,local_3c), 0 < DebugLevel))
     && (printk("%10s %10x %10x %10x %4x/%5x %4x/%5x\n","DMA0P1",local_38,local_34,local_28,
                local_28 & 1,(local_28 << 0x1d) >> 0x1f,(local_28 << 0x1e) >> 0x1f,
                (local_28 << 0x1c) >> 0x1f), 0 < DebugLevel)) {
    uVar2 = (local_24 << 0x1e) >> 0x1f;
    uVar3 = (local_24 << 0x1c) >> 0x1f;
    printk("%10s %10x %10x %10x %4x/%5x %4x/%5x\n","DMA1P1",local_30,local_2c,local_24,local_24 & 1,
           (local_24 << 0x1d) >> 0x1f,uVar2,uVar3);
    if ((0 < DebugLevel) && (printk("HOST_DMA0 Ring Configuration\n"), 0 < DebugLevel)) {
      printk("%20s %10s %10s %10s %10s %10s\n",&_LC335,&_LC336,&_LC337,&_LC338,&_LC339,&_LC340,uVar2
             ,uVar3);
    }
  }
  FUN_00189a88(param_1,"R0:Data0(MAC2H)",0x7c024500);
  FUN_00189a88(param_1,"R1:Data1(MAC2H)",0x7c024510);
  if ((0 < DebugLevel) && (printk("HOST_DMA0 PCIe 1 Ring Configuration\n"), 0 < DebugLevel)) {
    printk("%20s %10s %10s %10s %10s %10s\n",&_LC335,&_LC336,&_LC337,&_LC338,&_LC339,&_LC340);
  }
  FUN_00189a88(param_1,"R1:Data1(MAC2H)",0x7c028510);
  if ((0 < DebugLevel) && (printk("HOST_DMA1 Ring Configuration\n"), 0 < DebugLevel)) {
    printk("%20s %10s %10s %10s %10s %10s\n",&_LC335,&_LC336,&_LC337,&_LC338,&_LC339,&_LC340);
  }
  FUN_001899dc(param_1,"T16:FWDL",0x7c025400);
  FUN_001899dc(param_1,"T17:Cmd(H2WM)",0x7c025410);
  FUN_001899dc(param_1,"T18:TXD0(H2WA)",0x7c025420);
  FUN_001899dc(param_1,"T19:TXD1(H2WA)",0x7c025430);
  FUN_001899dc(param_1,"T20:Cmd(H2WA)",0x7c025440);
  FUN_00189a88(param_1,"R0:Event(WM2H)",0x7c025500);
  FUN_00189a88(param_1,"R1:Event0(WA2H)",0x7c025510);
  FUN_00189a88(param_1,"R2:Event1(WA2H)",0x7c025520);
  if ((0 < DebugLevel) && (printk("HOST_DMA1 PCIe 1 Ring Configuration\n"), 0 < DebugLevel)) {
    printk("%20s %10s %10s %10s %10s %10s\n",&_LC335,&_LC336,&_LC337,&_LC338,&_LC339,&_LC340);
  }
  FUN_001899dc(param_1,"T19:TXD1(H2WA)",0x7c029330);
  FUN_00189a88(param_1,"R2:Event1(WA2H)",0x7c029520);
  mac_io_read32(param_1,0x54000208,&local_40);
  mac_io_read32(param_1,0x54000200,&local_3c);
  mac_io_read32(param_1,0x54000204,&local_38);
  mac_io_read32(param_1,0x55000208,&local_34);
  mac_io_read32(param_1,0x55000200,&local_30);
  mac_io_read32(param_1,0x55000204,&local_2c);
  mac_io_read32(param_1,0x59000208,&local_28);
  mac_io_read32(param_1,0x59000200,&local_24);
  mac_io_read32(param_1,0x59000204,local_20);
  if (0 < DebugLevel) {
    printk("MCU_DMA Configuration\n");
    if (0 < DebugLevel) {
      printk("%10s %10s %10s %10s %10s %10s\n",&_LC319,"IntCSR","IntMask","Glocfg","Tx/RxEn",
             "Tx/RxBusy");
      if (((DebugLevel < 1) ||
          (printk("%10s %10x %10x %10x %4x/%5x %4x/%5x\n",&_LC328,local_3c,local_38,local_40,
                  local_40 & 1,(local_40 << 0x1d) >> 0x1f,(local_40 << 0x1e) >> 0x1f,
                  (local_40 << 0x1c) >> 0x1f), DebugLevel < 1)) ||
         (printk("%10s %10x %10x %10x %4x/%5x %4x/%5x\n",&_LC329,local_30,local_2c,local_34,
                 local_34 & 1,(local_34 << 0x1d) >> 0x1f,(local_34 << 0x1e) >> 0x1f,
                 (local_34 << 0x1c) >> 0x1f), DebugLevel < 1)) goto LAB_00190000;
      printk("%10s %10x %10x %10x %4x/%5x %4x/%5x\n","DMA1P1",local_24,local_20[0],local_28,
             local_28 & 1,(local_28 << 0x1d) >> 0x1f,(local_28 << 0x1e) >> 0x1f,
             (local_28 << 0x1c) >> 0x1f);
    }
    if ((0 < DebugLevel) && (printk("MCU_DMA0 Ring Configuration\n"), 0 < DebugLevel)) {
      printk("%20s %10s %10s %10s %10s %10s\n",&_LC335,&_LC336,&_LC337,&_LC338,&_LC339,&_LC340);
    }
  }
LAB_00190000:
  FUN_001899dc(param_1,"T0:TXD(WM2MAC)",0x54000300);
  FUN_001899dc(param_1,"T1:TXCMD(WM2MAC)",0x54000310);
  FUN_001899dc(param_1,"T2:TXD(WA2MAC)",0x54000320);
  FUN_00189a88(param_1,"R0:Data(MAC2WM)",0x54000500);
  FUN_00189a88(param_1,"R1:TxDone(MAC2WM)",0x54000510);
  FUN_00189a88(param_1,"R2:SPL(MAC2WM)",0x54000520);
  FUN_00189a88(param_1,"R3:TxDone(MAC2WA)",0x54000530);
  FUN_00189a88(param_1,"R4:TXS(MAC2WA)",0x54000540);
  if ((0 < DebugLevel) && (printk("MCU_DMA1 Ring Configuration\n"), 0 < DebugLevel)) {
    printk("%20s %10s %10s %10s %10s %10s\n",&_LC335,&_LC336,&_LC337,&_LC338,&_LC339,&_LC340);
  }
  FUN_001899dc(param_1,"T0:Event(WM2H)",0x55000300);
  FUN_001899dc(param_1,"T1:Event0(WA2H)",0x55000310);
  FUN_001899dc(param_1,"T2:Event1(WA2H)",0x55000320);
  FUN_00189a88(param_1,"R0:FWDL",0x55000500);
  FUN_00189a88(param_1,"R1:Cmd(H2WM)",0x55000510);
  FUN_00189a88(param_1,"R2:TXD0(H2WA)",0x55000520);
  FUN_00189a88(param_1,"R3:TXD1(H2WA)",0x55000530);
  FUN_00189a88(param_1,"R4:Cmd(H2WA)",0x55000540);
  if ((0 < DebugLevel) && (printk("MCU_DMA1 PCIe 1 Ring Configuration\n"), 0 < DebugLevel)) {
    printk("%20s %10s %10s %10s %10s %10s\n",&_LC335,&_LC336,&_LC337,&_LC338,&_LC339,&_LC340);
  }
  FUN_001899dc(param_1,"T2:Event1(WA2H)",0x59000320);
  FUN_00189a88(param_1,"R3:TXD1(H2WA)",0x59000530);
  mac_io_read32(param_1,0x58000208,&local_40);
  mac_io_read32(param_1,0x58000200,&local_3c);
  mac_io_read32(param_1,0x58000204,&local_38);
  if (((0 < DebugLevel) && (printk("MEM_DMA Configuration\n"), 0 < DebugLevel)) &&
     (printk("%10s %10s %10s %10s %10s %10s\n",&_LC319,"IntCSR","IntMask","Glocfg","Tx/RxEn",
             "Tx/RxBusy"), 0 < DebugLevel)) {
    uVar2 = (local_40 << 0x1e) >> 0x1f;
    uVar3 = (local_40 << 0x1c) >> 0x1f;
    printk("%10s %10x %10x %10x %4x/%5x %4x/%5x\n",&_LC375,local_3c,local_38,local_40,local_40 & 1,
           (local_40 << 0x1d) >> 0x1f,uVar2,uVar3);
    if ((0 < DebugLevel) && (printk("MEM_DMA Ring Configuration\n"), 0 < DebugLevel)) {
      printk("%20s %10s %10s %10s %10s %10s\n",&_LC335,&_LC336,&_LC337,&_LC338,&_LC339,&_LC340,uVar2
             ,uVar3);
    }
  }
  FUN_001899dc(param_1,"T0:CmdEvent(WM2WA)",0x58000300);
  FUN_001899dc(param_1,"T1:CmdEvent(WA2WM)",0x58000310);
  FUN_00189a88(param_1,"R0:CmdEvent(WM2WA)",0x58000500);
  FUN_00189a88(param_1,"R1:CmdEvent(WA2WM)",0x58000510);
  return;
}

