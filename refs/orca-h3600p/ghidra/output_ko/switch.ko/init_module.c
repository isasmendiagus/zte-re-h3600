// module: switch.ko
// function: init_module @ 0x2208c
// size: 88 bytes
//

undefined4 init_module(void)

{
  printk("Init switch module\n");
  sw_init_switch();
  public_capfun_register();
  private_capfun_register();
  proc_create_data("tcphy",0x1ff,0,tcphy_proc_fops,0);
  printk("Init personal switch module Success\n");
  return 0;
}

