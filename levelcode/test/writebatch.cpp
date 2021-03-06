#include <iostream>
#include <string.h>
#include <leveldb/db.h>
#include <leveldb/write_batch.h>
using namespace std;
using namespace leveldb;
//将字符串数字自加１
void getnextnumber(char *num){
	int i = 0;
	while(num[i] != '\0'){
		if(num[i] >= '0' && num[i] < '9')
		{
			num[i] += 1;
			return;
		}
		num[i++] = '0';
	}
	num[i] = '1';
}

int main(int argc, char **argv){
	WriteBatch batch;
	DB *db;
	Options options;
	options.create_if_missing = true;
	string dbpath = "testdb";
	Status status = DB::Open(options, dbpath, &db);
	if(status.ok()){
		//使用WriteBatch批量删除数据
		if(argc == 2 && strcmp(argv[1], "del") == 0){
			Iterator *it = db->NewIterator(ReadOptions());
			for(it->SeekToFirst(); it->Valid(); it->Next()){
				batch.Delete(it->key());
			}
		}
		else{
		//使用WriteBatch批量添加数据
			//将key从0到1000000之间的数当做key添加到db中
			char num[10];
			bzero(num, sizeof(num));
			num[0] = '0';
			while(num[3] != '1'){
				batch.Put(num, num);
				getnextnumber(num);
			}
		}
		db->Write(WriteOptions(), &batch);
	}
	delete db;
	return 0;
}

