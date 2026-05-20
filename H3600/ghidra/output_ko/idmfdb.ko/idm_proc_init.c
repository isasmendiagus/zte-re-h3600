// module: idmfdb.ko
// function: idm_proc_init @ 0x11f0c
// size: 180 bytes
//

undefined4 idm_proc_init(void)

{
  proc_parent = proc_mkdir("idm_fdb",0);
  proc_dbg = proc_create_data("debug",0x1b6,proc_parent,idm_proc_dbg_file_ops,0);
  proc_create_data("idm_map",0x1b6,proc_parent,idm_proc_idm_map_file_ops,0);
  proc_create_data("flood_status",0x1b6,proc_parent,idm_proc_flood_status_file_ops,0);
  proc_create_data("multicast",0x1b6,proc_parent,idm_proc_multicast_file_ops,0);
  return 0;
}

