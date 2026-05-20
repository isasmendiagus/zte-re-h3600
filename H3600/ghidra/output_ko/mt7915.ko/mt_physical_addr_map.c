// module: mt7915.ko
// function: mt_physical_addr_map @ 0x1df1cc
// size: 512 bytes
//

uint mt_physical_addr_map(uint param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined1 *puVar2;
  uint uVar3;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_2 < 0x2000) {
    param_1 = param_2 + 0x80020000;
  }
  if (param_2 >= 0x2000) {
    if (param_2 - 0x2000 < 0x2000) {
      param_1 = param_2 + 0x7fffe000;
    }
    else if (param_2 - 0x4000 < 0x4000) {
      param_1 = param_2 + 0x4fffc000;
    }
    else if (param_2 - 0x8000 < 0x8000) {
      param_1 = param_2 + 0x9fff8000;
    }
    else if (param_2 - 0x10000 < 0x10000) {
      param_1 = param_2 + 0x601f0000;
    }
    else if (param_2 - 0x20000 < 0x20000) {
      if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
        iVar1 = 1;
        puVar2 = mt7915_mac_cr_range;
        uVar3 = mt7915_mac_cr_range._4_4_;
        do {
          if ((uVar3 <= param_2) && (param_2 < uVar3 + *(int *)(puVar2 + 8))) {
            iVar1 = iVar1 + 0x3fffffff;
            param_1 = (param_2 - uVar3) + *(int *)(mt7915_mac_cr_range + iVar1 * 4);
            if (uVar3 != 0) {
              return param_1;
            }
            break;
          }
          uVar3 = *(uint *)(puVar2 + 0x10);
          iVar1 = iVar1 + 3;
          param_1 = 0;
          puVar2 = puVar2 + 0xc;
        } while (uVar3 != 0);
        if (0 < DebugLevel) {
          printk("unknow addr range = %x\n",param_2,iVar1,DebugLevel,param_4);
        }
      }
      else if (DebugLevel < 1) {
        param_1 = 0;
      }
      else {
        printk("%s(): NotSupported Chip for this function!\n","mt_physical_addr_map",0x7915,
               DebugLevel,param_4);
        param_1 = 0;
      }
    }
    else {
      uVar3 = param_2 - 0x40000;
      if (uVar3 < 0x40000) {
        param_1 = *(int *)(iVar1 + 0x90) + -0x40000 + param_2;
        if (3 < DebugLevel) {
          printk("==>global_addr1=0x%x\n",param_1,&DebugLevel,DebugLevel,param_4);
        }
      }
      else if (param_2 - 0xc0000 < 0x100) {
        param_1 = param_2 + 0x80000000;
        if (3 < DebugLevel) {
          printk("==>global_addr2=0x%x\n",param_1,uVar3,DebugLevel,param_4);
        }
      }
      else {
        param_1 = param_2;
        if (3 < DebugLevel) {
          printk("==>global_addr3=0x%x\n",param_2,uVar3,DebugLevel,param_4);
        }
      }
    }
  }
  return param_1;
}

