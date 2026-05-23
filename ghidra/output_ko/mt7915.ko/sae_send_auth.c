// module: mt7915.ko
// function: sae_send_auth @ 0x20a060
// size: 364 bytes
//

void sae_send_auth(undefined4 param_1,undefined1 *param_2,undefined1 *param_3,undefined4 param_4,
                  undefined4 param_5,undefined2 param_6,undefined2 param_7,undefined4 param_8,
                  undefined4 param_9)

{
  int iVar1;
  undefined4 local_48;
  undefined4 local_44;
  undefined1 auStack_40 [28];
  
  local_48 = 0;
  local_44 = 0;
  if (2 < DebugLevel) {
    printk("==> %s(), seq = %d, statuscode = %d, own mac addr = %02x:%02x:%02x:%02x:%02x:%02x, peer mac addr = %02x:%02x:%02x:%02x:%02x:%02x\n"
           ,"sae_send_auth",param_6,param_7,*param_2,param_2[1],param_2[2],param_2[3],param_2[4],
           param_2[5],*param_3,param_3[1],param_3[2],param_3[3],param_3[4],param_3[5]);
  }
  iVar1 = os_alloc_mem(param_1,&local_44,0x900);
  if (iVar1 != 0) {
    return;
  }
  MgtMacHeaderInitExt(param_1,auStack_40,0xb,0,param_3,param_2,param_4);
  MakeOutgoingFrame(local_44,&local_48,0x18,auStack_40,2,&param_5,2,&param_6,2,&param_7,param_9,
                    param_8,0xffffffff);
  MiniportMMRequest(param_1,0,local_44,local_48);
  os_free_mem(local_44);
  return;
}

