// module: switch.ko
// function: init_module @ 0x21fb4
// size: 48 bytes
//

undefined4 init_module(void)

{
  printk("Init switch module\n");
  sw_init_switch();
  public_capfun_register();
  private_capfun_register();
  printk("Init personal switch module Success\n");
  return 0;
}

