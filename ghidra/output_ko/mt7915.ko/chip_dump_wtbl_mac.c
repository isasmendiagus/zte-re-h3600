// module: mt7915.ko
// function: chip_dump_wtbl_mac @ 0x190d6c
// size: 152 bytes
//

void chip_dump_wtbl_mac(undefined4 param_1,undefined4 param_2)

{
  undefined1 local_90;
  undefined1 local_8f;
  undefined1 local_8c;
  undefined1 local_8b;
  undefined1 local_8a;
  undefined1 local_89;
  
  memset(&local_90,0,0x80);
  halWtblReadRaw(param_1,param_2,0,0,0x20,&local_90);
  if (0 < DebugLevel) {
    printk("WLAN_IDX: %d Mac Addr: %02x:%02x:%02x:%02x:%02x:%02x\n",param_2,local_8c,local_8b,
           local_8a,local_89,local_90,local_8f);
  }
  return;
}

