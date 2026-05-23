// module: plat-zxylzb_9128S.ko
// function: VlanReadProc @ 0x16344
// size: 40 bytes
//

undefined4 VlanReadProc(void *param_1)

{
  undefined4 *in_stack_00000000;
  
  memcpy(param_1,
         "Usage: echo [OPTIONS] add/del/show > /proc/xxx/l2 \nexample -v 1 -p 0 add \n        show \nOptions:\n  -v,         set vlan id,default is 1\n  -p,         set uni port, default is 0\n  -t,         set memtag,default is 3,1 delete ,2 include,3 no change\n  -h,         help\n"
         ,0x10b);
  *in_stack_00000000 = 1;
  return 0x10a;
}

