// module: mt7915.ko
// function: WfMcuInit @ 0xb2a28
// size: 812 bytes
//

int WfMcuInit(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint local_24;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar2 = WfMcuSysInit(param_1);
  if (iVar2 == 0) {
    iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
    iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
    DriverOwn(param_1);
    if (*(code **)(iVar2 + 0xe4) != (code *)0x0) {
      (**(code **)(iVar2 + 0xe4))(param_1);
    }
    if (*(code **)(iVar2 + 0x22c) != (code *)0x0) {
      (**(code **)(iVar2 + 0x22c))(param_1);
    }
    iVar2 = NICLoadRomPatch(param_1);
    if (iVar2 == 0) {
      if (0 < DebugLevel) {
        printk(&_LC3,"WfMcuHwInit",*(undefined1 *)(param_1 + 0xa78a54));
      }
      if (*(char *)(param_1 + 0xa78a54) == '\x01') {
        hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f23c,&local_24);
        local_24 = local_24 & 0xfffffffc | 2;
        hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f23c);
      }
      else {
        uVar4 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
        if (*(char *)(param_1 + 0xa78a54) == '\x02') {
          if (uVar4 == 0x7615) {
            hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x220c,&local_24);
            local_24 = local_24 | 0x10;
            hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x220c);
          }
          else if (uVar4 == 0x7622) {
            hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x260c,&local_24);
            local_24 = local_24 | 0x10;
            hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x260c);
          }
        }
        else if (uVar4 == 0x7615) {
          hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x220c,&local_24);
          local_24 = local_24 & 0xffffffef;
          hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x220c);
        }
        else if (uVar4 == 0x7622) {
          hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x260c,&local_24);
          local_24 = local_24 & 0xffffffef;
          hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x260c);
        }
        else {
          hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f23c,&local_24);
          local_24 = local_24 & 0xfffffffc;
          hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f23c);
        }
      }
      iVar2 = NICLoadFirmware(param_1);
      if (iVar2 == 0) {
        if ((*(uint *)(iVar3 + 0x3c) & 8) != 0) {
          asic_wa_update(param_1);
        }
        HWCtrlOpsReg(param_1);
        uVar4 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
        if (((uVar4 & 0x400) != 0) && (*(char *)(iVar1 + 0x21) != '\0')) {
          MtCmdCr4Set(param_1,0x20,1,0);
        }
        if (DebugLevel < 3) {
          return 0;
        }
        printk("<--%s(), Success!\n","WfMcuInit");
        return 0;
      }
      if (-1 < DebugLevel) {
        printk("%s: NICLoadFirmware failed, Status[=0x%08x]\n","WfMcuHwInit");
      }
    }
    else if (-1 < DebugLevel) {
      printk("%s: NICLoadRomPatch failed, Status[=0x%08x]\n","WfMcuHwInit");
    }
    iVar2 = 1;
  }
  WfMcuSysExit(param_1);
  if (2 < DebugLevel) {
    printk("<--%s(), Err! status=%d\n","WfMcuInit",iVar2);
  }
  return iVar2;
}

