// module: mt7915.ko
// function: hif_cfg_dly_int @ 0x176aa4
// size: 672 bytes
//

undefined4 hif_cfg_dly_int(undefined4 param_1,code *param_2,int param_3,uint param_4)

{
  uint uVar1;
  uint local_14;
  
  if (param_2 == (code *)0xd5500) {
    mac_io_read32(param_1,0x7c0252f4,&local_14);
    uVar1 = 0x52f4;
    goto LAB_00176b1c;
  }
  if (param_2 < (code *)0xd5501) {
    if (param_2 != (code *)0xd4510) {
      if (param_2 < (code *)0xd4511) {
        if (param_2 != (code *)0xd4500) goto LAB_00176cc0;
        mac_io_read32(param_1,0x7c0242f0,&local_14);
        uVar1 = 0x42f0;
      }
      else {
        if (param_2 != (code *)0xd5420) {
          if (param_2 != (code *)0xd5430) goto LAB_00176cc0;
          mac_io_read32(param_1,0x7c0252f0,&local_14);
          uVar1 = 0x52f0;
          goto LAB_00176b9c;
        }
        mac_io_read32(param_1,0x7c0252f0,&local_14);
        uVar1 = 0x52f0;
      }
LAB_00176b1c:
      local_14 = param_3 << 8 | 0x8000U | (param_4 | local_14 & 0xffffff00) & 0xffff80ff;
      mac_io_write32(param_1,uVar1 | 0x7c020000);
      return 0;
    }
    mac_io_read32(param_1,0x7c0242f0,&local_14);
    uVar1 = 0x42f0;
  }
  else if (param_2 == (code *)0xd8510) {
    mac_io_read32(param_1,0x7c0282f0,&local_14);
    uVar1 = 0x82f0;
  }
  else if (param_2 < (code *)0xd8511) {
    if (param_2 != Show_WpsDeviceName_Proc) {
      if (param_2 == (code *)0xd5520) {
        mac_io_read32(param_1,0x7c0252f8,&local_14);
        uVar1 = 0x52f8;
        goto LAB_00176b1c;
      }
LAB_00176cc0:
      if (DebugLevel < 0) {
        return 0;
      }
      printk("Unknown rx ring delay int(0x%x) setting\n");
      return 0;
    }
    mac_io_read32(param_1,0x7c0252f4,&local_14);
    uVar1 = 0x52f4;
  }
  else {
    if (param_2 != (code *)0xd9330) {
      if (param_2 == (code *)0xd9520) {
        mac_io_read32(param_1,0x7c0292f0,&local_14);
        local_14 = param_3 << 8 | 0x8000U | (param_4 | local_14 & 0xffffff00) & 0xffff80ff;
        mac_io_write32(param_1,0x7c0292f0);
        return 0;
      }
      goto LAB_00176cc0;
    }
    mac_io_read32(param_1,0x7c0292f0,&local_14);
    uVar1 = 0x92f0;
  }
LAB_00176b9c:
  local_14 = param_3 << 0x18 | 0x80000000U | (local_14 & 0xff00ffff | param_4 << 0x10) & 0x80ffffff;
  mac_io_write32(param_1,uVar1 | 0x7c020000);
  return 0;
}

