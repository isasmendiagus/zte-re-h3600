// module: switch.ko
// function: tcphy_proc_read @ 0x131f0
// size: 124 bytes
//

int tcphy_proc_read(undefined4 param_1,undefined4 param_2,undefined4 param_3,int *param_4)

{
  int iVar1;
  char local_28 [20];
  
  iVar1 = 0;
  local_28[0] = '\0';
  local_28[1] = '\0';
  local_28[2] = '\0';
  local_28[3] = '\0';
  local_28[4] = '\0';
  local_28[5] = '\0';
  local_28[6] = '\0';
  local_28[7] = '\0';
  local_28[8] = '\0';
  local_28[9] = '\0';
  local_28[10] = '\0';
  local_28[0xb] = '\0';
  local_28[0xc] = '\0';
  local_28[0xd] = '\0';
  local_28[0xe] = '\0';
  local_28[0xf] = '\0';
  if (*param_4 == 0 && param_4[1] == 0) {
    iVar1 = sprintf(local_28,"%d\n",loopback_status);
    simple_read_from_buffer(param_2,param_3,param_4,local_28,0x10);
  }
  return iVar1;
}

