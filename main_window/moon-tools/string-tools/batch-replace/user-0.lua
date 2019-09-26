--替换表，例如{"Hello","world"},--
replace_table={
{"LOG_LEVEL_QUIET","XLOG_LEVEL_QUIET"},
{"LOG_LEVEL_ERROR","XLOG_LEVEL_ERROR"},
{"LOG_LEVEL_WARNING","XLOG_LEVEL_WARNING"},
{"LOG_LEVEL_INFO","XLOG_LEVEL_INFO"},
{"LOG_LEVEL_DEBUG","XLOG_LEVEL_DEBUG"},
{"LOG_MODULE_ROOT","XLOG_MODULE_ROOT"},
{"LOG_MODULE_COMMON","XLOG_MODULE_COMMON"},
{"LOG_MODULE_MESSAGEPEER","XLOG_MODULE_MESSAGEPEER"},
{"LOG_MODULE_USER","XLOG_MODULE_USER"},
};

--是否大小写敏感--
case_sensitive = true;

--只替换单字--
word_only = false;

--是否在文件中进行替换，如果是true，则替换在
--编辑框中列表的所有文件。
replace_in_files = true;
