/* ============= FUNCTION: fpga_read_reg @ 00010000 ============= */

undefined4 fpga_read_reg(int param_1)

{
  return *(undefined4 *)(pon + param_1 * 4);
}


/* ============= FUNCTION: fpga_write_reg @ 00010014 ============= */

void fpga_write_reg(int param_1,undefined4 param_2)

{
  *(undefined4 *)(pon + param_1 * 4) = param_2;
  return;
}


/* ============= FUNCTION: fpga_open @ 00010028 ============= */

undefined4 fpga_open(void)

{
  return 0;
}


/* ============= FUNCTION: fpga_release @ 00010030 ============= */

undefined4 fpga_release(void)

{
  return 0;
}


/* ============= FUNCTION: fpga_ioctl @ 00010038 ============= */

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


/* ============= FUNCTION: fpga_read_reg_one @ 00010140 ============= */

undefined4 fpga_read_reg_one(int param_1)

{
  return *(undefined4 *)(pon + param_1 * 4);
}


/* ============= FUNCTION: fpga_write_reg_one @ 00010154 ============= */

void fpga_write_reg_one(int param_1,undefined4 param_2)

{
  *(undefined4 *)(pon + param_1 * 4) = param_2;
  return;
}


/* ============= FUNCTION: fpga_module_init @ 00010168 ============= */

undefined4 fpga_module_init(void)

{
  int iVar1;
  undefined4 uVar2;
  
  pon = 0xf4000000;
  iVar1 = __register_chrdev(0xde,0,0x100,&_LC3,&fpga_ops);
  if (iVar1 < 0) {
    printk("register fpga driver failed!\n");
    uVar2 = 0xffffffff;
  }
  else {
    printk("register fpga driver success, major=%d\n",0xde);
    uVar2 = 0;
  }
  return uVar2;
}


/* ============= FUNCTION: fpga_module_exit @ 000101dc ============= */

void fpga_module_exit(void)

{
  __arm_iounmap(pon);
  __unregister_chrdev(0xde,0,0x100,&_LC3);
  return;
}


/* ============= FUNCTION: __arm_iounmap @ 00011004 ============= */

/* WARNING: Control flow encountered bad instruction data */

void __arm_iounmap(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: printk @ 00011008 ============= */

/* WARNING: Control flow encountered bad instruction data */

void printk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __memzero @ 0001100c ============= */

/* WARNING: Control flow encountered bad instruction data */

void __memzero(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __register_chrdev @ 00011010 ============= */

/* WARNING: Control flow encountered bad instruction data */

void __register_chrdev(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __copy_from_user @ 00011014 ============= */

/* WARNING: Control flow encountered bad instruction data */

void __copy_from_user(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


/* ============= FUNCTION: __unregister_chrdev @ 00011018 ============= */

/* WARNING: Control flow encountered bad instruction data */

void __unregister_chrdev(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}


