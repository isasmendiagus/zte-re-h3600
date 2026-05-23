// module: rtkatm.ko
// function: isPpp @ 0x10b08
// size: 20 bytes
//

void isPpp(int param_1,int param_2)

{
  memcmp(&pppllc,(void *)(*(int *)(param_1 + 0xcc) + param_2),4);
  return;
}

