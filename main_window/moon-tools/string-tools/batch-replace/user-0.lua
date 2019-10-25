--替换表，例如{"Hello","world"},--
replace_table={
{"GBmsg-rsm.h","ETSImsg-rsm.h"},
{"GBmsg-bsm.h","ETSImsg-bsm.h"},
{"GBd-full-position-vector.h","ETSId-full-position-vector.h"},
{"GBmsg-map.h","ETSImsg-map.h"},
{"GBmsg-spat.h","ETSImsg-spat.h"},
{"GBmsg-rsi.h","ETSImsg-rsi.h"},
{"GB-common.h","ETSI-common.h"},
{"GBmsg-frame.h","ETSImsg-frame.h"},
{"GB-vse.h","ETSI-vse.h"},
{"GBrsi_in.h","ETSIrsi_in.h"},
{"GB_srm_in.h","ETSI_srm_in.h"},
{"GB_rrfunc_in.h","ETSI_rrfunc_in.h"},
{"GB_rsm_in.h","ETSI_rsm_in.h"},
{"GBmap_in.h","ETSImap_in.h"},
{"GB_set_msg_callback.h","ETSI_set_msg_callback.h"},
{"GB_spat_in.h","ETSI_spat_in.h"},
{"GB_RawData_in.h","ETSI_RawData_in.h"},
{"GB_bstypes_in.h","ETSI_bstypes_in.h"},
};

--是否大小写敏感--
case_sensitive = true;

--只替换单字--
word_only = false;

--是否在文件中进行替换，如果是true，则替换在
--编辑框中列表的所有文件。
replace_in_files = true;
