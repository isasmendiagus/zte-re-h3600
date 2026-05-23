// module: idmfdb.ko
// function: create_led_proc_file @ 0x11ea4
// size: 100 bytes
//

undefined4 create_led_proc_file(undefined4 *param_1)

{
  char local_20 [20];
  
  local_20[0] = '\0';
  local_20[1] = '\0';
  local_20[2] = '\0';
  local_20[3] = '\0';
  local_20[4] = '\0';
  local_20[5] = '\0';
  local_20[6] = '\0';
  local_20[7] = '\0';
  local_20[8] = '\0';
  local_20[9] = '\0';
  local_20[10] = '\0';
  local_20[0xb] = '\0';
  local_20[0xc] = '\0';
  local_20[0xd] = '\0';
  local_20[0xe] = '\0';
  local_20[0xf] = '\0';
  snprintf(local_20,0xf,"led%d",*param_1);
  proc_create_data(local_20,0x1b6,proc_parent,idm_proc_led_file_ops,param_1);
  return 0;
}

