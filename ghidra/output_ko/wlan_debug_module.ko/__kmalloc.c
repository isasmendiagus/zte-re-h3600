// module: wlan_debug_module.ko
// function: __kmalloc @ 0x6809c
// size: 1 bytes
//

/* WARNING: Control flow encountered bad instruction data */

void __kmalloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

