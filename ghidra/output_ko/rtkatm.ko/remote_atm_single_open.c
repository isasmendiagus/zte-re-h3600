// module: rtkatm.ko
// function: remote_atm_single_open @ 0x104bc
// size: 20 bytes
//

void remote_atm_single_open(undefined4 param_1,undefined4 param_2)

{
  single_open(param_2,remote_atm_read,0);
  return;
}

