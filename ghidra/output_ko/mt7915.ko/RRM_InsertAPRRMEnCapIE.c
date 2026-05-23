// module: mt7915.ko
// function: RRM_InsertAPRRMEnCapIE @ 0x21ce44
// size: 184 bytes
//

void RRM_InsertAPRRMEnCapIE(int param_1,undefined4 param_2,int *param_3,int param_4)

{
  int iVar1;
  undefined1 local_2e;
  undefined1 local_2d;
  int local_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  
  local_2d = 0x46;
  local_2e = 5;
  iVar1 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_4 < iVar1) {
    param_1 = param_4 * 0x5834 + param_1;
    local_28 = *(undefined4 *)
                ("The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n" +
                param_1 + 0x27);
    uStack_24 = *(undefined4 *)
                 ("The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n" +
                 param_1 + 0x2b);
    MakeOutgoingFrame(param_2,&local_2c,1,&local_2d,1,&local_2e,local_2e,&local_28,0xffffffff);
    *param_3 = *param_3 + local_2c;
  }
  return;
}

