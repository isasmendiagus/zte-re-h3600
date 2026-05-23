// module: mt7915.ko
// function: RT28xx_get_ether_stats @ 0x245d78
// size: 232 bytes
//

undefined4 * RT28xx_get_ether_stats(int param_1)

{
  int iVar1;
  int local_48;
  undefined4 *local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_18;
  undefined4 local_14;
  
  if (param_1 == 0) {
    return (undefined4 *)0x0;
  }
  iVar1 = RtmpOsGetNetDevPriv();
  if (iVar1 == 0) {
    local_44 = (undefined4 *)0x0;
  }
  else {
    local_48 = param_1;
    RTMP_COM_IoctlHandle(iVar1,0,0x503c,0,&local_48,0);
    local_44[10] = 0;
    *local_44 = local_40;
    local_44[0xc] = 0;
    local_44[0xf] = 0;
    local_44[1] = local_3c;
    local_44[0x10] = 0;
    local_44[0x11] = 0;
    local_44[2] = local_38;
    local_44[0x12] = 0;
    local_44[0x13] = 0;
    local_44[3] = local_34;
    local_44[0x14] = 0;
    local_44[4] = local_30;
    local_44[6] = 0;
    local_44[7] = 0;
    local_44[5] = local_2c;
    local_44[8] = local_28;
    local_44[9] = local_24;
    local_44[0xb] = local_20;
    local_44[0xd] = local_18;
    local_44[0xe] = local_14;
    local_44[0x15] = 0;
    local_44[0x16] = 0;
  }
  return local_44;
}

