// module: mt7915.ko
// function: entrytb_aid_bitmap_init @ 0x14ac78
// size: 124 bytes
//

void entrytb_aid_bitmap_init(undefined4 param_1,int *param_2)

{
  int local_c;
  
  local_c = 0;
  os_alloc_mem(0,&local_c,0xfc);
  if (local_c == 0) {
    dump_stack();
    if (-1 < DebugLevel) {
      printk("%s(): Allocate memory size:%d for aid_bitmap failed!\n","entrytb_aid_bitmap_init",0xfc
            );
    }
  }
  else {
    *param_2 = local_c;
    os_zero_mem(local_c,0xfc);
    *(undefined2 *)((int)param_2 + 6) = 0x7d7;
  }
  return;
}

