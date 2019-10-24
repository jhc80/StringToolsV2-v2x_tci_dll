--替换表，例如{"Hello","world"},--
replace_table={
{"sensor_image","gnss_event"},
{"SENSOR_IMAGE","GNSS_EVENT"},
{"sensorImage","gnssEvent"},
{"SENSORIMAGE","GNSSEVENT"},
{"sensorimage","gnssevent"},
{"SensorImage","GnssEvent"},
};

--是否大小写敏感--
case_sensitive = true;

--只替换单字--
word_only = false;

--是否在文件中进行替换，如果是true，则替换在
--编辑框中列表的所有文件。
replace_in_files = false;
