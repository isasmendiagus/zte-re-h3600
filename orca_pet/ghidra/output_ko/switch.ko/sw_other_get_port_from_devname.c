// module: switch.ko
// function: sw_other_get_port_from_devname @ 0x1738c
// size: 56 bytes
//

undefined4 sw_other_get_port_from_devname(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_c;
  
  local_c = 0;
  iVar1 = get_sw_port_from_devname(param_1,&local_c,1);
  if (iVar1 == 0) {
    *param_1 = local_c;
    uVar2 = 0;
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

