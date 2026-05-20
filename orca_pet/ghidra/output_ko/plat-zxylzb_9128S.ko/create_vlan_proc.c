// module: plat-zxylzb_9128S.ko
// function: create_vlan_proc @ 0x17960
// size: 60 bytes
//

int create_vlan_proc(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = proc_create_data(&_LC38,0x124,param_1,proc_vlan_operations,0);
  return -(uint)(iVar1 == 0);
}

