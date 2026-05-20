// module: mt7915.ko
// function: rtmp_read_cp_parms_from_file @ 0xf1f64
// size: 200 bytes
//

void rtmp_read_cp_parms_from_file(int param_1,char *param_2,undefined4 param_3)

{
  undefined1 uVar1;
  int iVar2;
  
  if (3 < DebugLevel) {
    printk("%s: begin -->\n","rtmp_read_cp_parms_from_file");
  }
  __memzero(param_2,0x800);
  iVar2 = RTMPGetKeyParameter("CP_SUPPORT",param_2,0x80,param_3,1);
  if ((iVar2 != 0) && (*param_2 != '\0')) {
    uVar1 = os_str_tol(param_2,0,10);
    iVar2 = DebugLevel;
    *(undefined1 *)(param_1 + 0xa7beca) = uVar1;
    if (3 < iVar2) {
      printk("CP_SUPPORT --> %d\n",uVar1);
      return;
    }
  }
  return;
}

