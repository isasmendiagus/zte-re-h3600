// module: zx_ponreg.ko
// function: fpga_ioctl @ 0x10038
// size: 264 bytes
//

undefined4 fpga_ioctl(undefined4 param_1,int param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  int local_90;
  undefined4 local_8c;
  uint local_88;
  
  uVar2 = *(uint *)(((uint)&local_90 & 0xffffe000) + 8);
  if (param_3 < 0xfffffff4 && param_3 + 0xc <= uVar2) {
    uVar2 = 0;
  }
  if (uVar2 == 0) {
    iVar1 = __copy_from_user(&local_90,param_3,0xc);
    if (iVar1 == 0) {
      if (param_2 == 0) {
        if (local_88 != 0) {
          uVar2 = 0;
          do {
            iVar1 = uVar2 + local_90;
            uVar2 = uVar2 + 1;
            printk("fpga read: reg=0x%08x, value=0x%08x\n",iVar1,*(undefined4 *)(pon + iVar1 * 4));
          } while (uVar2 < local_88);
        }
        return 0;
      }
      if (param_2 == 1) {
        *(undefined4 *)(pon + local_90 * 4) = local_8c;
        printk("fpga write: reg=0x%08x, data=0x%08x\n",local_90,local_8c);
        return 0;
      }
      return 0;
    }
  }
  else {
    __memzero(&local_90,0xc);
  }
  printk("copy_from_user failed!\n");
  return 0xffffffff;
}

