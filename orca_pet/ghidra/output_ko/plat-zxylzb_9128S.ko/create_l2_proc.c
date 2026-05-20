// module: plat-zxylzb_9128S.ko
// function: create_l2_proc @ 0x17920
// size: 60 bytes
//

int create_l2_proc(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = proc_create_data(&_LC37,0x124,param_1,proc_l2_operations,0);
  return -(uint)(iVar1 == 0);
}

