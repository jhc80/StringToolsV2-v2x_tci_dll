--复制列表中的所有文件--

--路径中要删除的前缀--
strip_prefix = "Z:\\temp\\VeTalk\\branch\\1609_facility_r3.5_main\\standard_GB\\v2x-lib\\src\\message\\ASN1 Source Code for TCSAE 53 2017\\";

--目标路径--
dest_folder = "Z:\\tmp\\asn";

--如果为true, 复制是就不带路径--
without_path = false;

--如果存在重名，是否自动重命名--
auto_rename = true;

--遇到错误时候是否结束--
stop_when_fail = false;

--复制的选项,如果为true就先检查是否相同--
check_same = false;

--如果文件存在是否覆盖--
overwrite = true;

