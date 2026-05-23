// module: mt7915.ko
// function: mt_serv_set_system_bw @ 0x252784
// size: 100 bytes
//

int mt_serv_set_system_bw(undefined4 *param_1)

{
  int unaff_r4;
  
  if (*(char *)(param_1 + 0x7d1) == '\0') {
    unaff_r4 = 0;
  }
  if ((*(char *)(param_1 + 0x7d1) != '\0') &&
     (unaff_r4 = (**(code **)(param_1[0x7c4] + 0x84))
                           (*param_1,*(undefined1 *)
                                      ((int)param_1 +
                                      (uint)*(byte *)(param_1 + 0x133) * 0xd18 + 0x1136)),
     unaff_r4 != 0)) {
    printk("%s: err=0x%08x\n","mt_serv_set_system_bw",unaff_r4);
  }
  return unaff_r4;
}

