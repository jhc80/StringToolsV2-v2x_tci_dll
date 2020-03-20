[CodeSwitch code_mark=true]

[Sqlite3 of StudentTable]
class Student{
	int id;
	string name;
	int age;
	double score;
	array<uint8_t> data;	
}


基本的Sqlite的类型就4个分别是 
INTEGER, REAL, TEXT, BLOB

C类型中，
字符串对应 TEXT类型
基本数组类型对应的是 BLOB类型
浮点数对应的是 REAL类型
其他类型的整数都对应的是 INTEGER类型


