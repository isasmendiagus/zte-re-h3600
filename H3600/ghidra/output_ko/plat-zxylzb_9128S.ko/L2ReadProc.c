// module: plat-zxylzb_9128S.ko
// function: L2ReadProc @ 0x16708
// size: 40 bytes
//

undefined4 L2ReadProc(void *param_1)

{
  undefined4 *in_stack_00000000;
  
  memcpy(param_1,
         "Usage: echo [OPTIONS] add/del/show/hash/cls > /proc/xxx/l2 \nexample -m xx:xx:xx:xx:xx:xx -v 1 -p 0 add \n        show \nOptions:\n  -m,         set mac address\n  -v,         set vlan id,default is 1\n  -p,         set uni port, default is 0\n  -h,         help\n"
         ,0x101);
  *in_stack_00000000 = 1;
  return 0x100;
}

