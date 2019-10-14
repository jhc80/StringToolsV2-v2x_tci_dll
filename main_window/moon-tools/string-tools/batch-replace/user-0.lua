--替换表，例如{"Hello","world"},--
replace_table={
{"ERROR_NONE","C_TASK_LINKRPC_ERROR_NONE"},
{"ERROR_LINKRPC_READER_STOPPED","C_TASK_LINKRPC_ERROR_LINKRPC_READER_STOPPED"},
{"ERROR_LINKRPC_WRITER_STOPPED","C_TASK_LINKRPC_ERROR_LINKRPC_WRITER_STOPPED"},
{"ERROR_EXCEED_MAX_RETRIES","C_TASK_LINKRPC_ERROR_EXCEED_MAX_RETRIES"},
{"ERROR_SOCKET_ERROR","C_TASK_LINKRPC_ERROR_SOCKET_ERROR"},
{"ERROR_CONNECT_ERROR","C_TASK_LINKRPC_ERROR_CONNECT_ERROR"},
{"ERROR_WRONG_HEADER_FORMAT","C_TASK_LINKRPC_ERROR_WRONG_HEADER_FORMAT"},
{"MALLOC","X_MALLOC"},
{"FREE","X_FREE"},
{"this","self"},
{"CTaskLinkRpc::","tasklinkrpc_"},
{"mSocket","socket"},
{"mSocketRwer","socket_rw"},
{"mTaskReader","task_reader"},
{"mTaskWriter","task_writer"},
{"mReader","reader"},
{"mWriter","writer"},
{"iHeaderBuf","header_buf"},
{"iDataBuf","data_buf"},
{"mStep","step"},
{"mRetries","retries"},
{"mMaxRetries","max_retries"},

};

--是否大小写敏感--
case_sensitive = true;

--只替换单字--
word_only = false;

--是否在文件中进行替换，如果是true，则替换在
--编辑框中列表的所有文件。
replace_in_files = false;
