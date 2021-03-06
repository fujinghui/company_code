#include <iostream>
#include <leveldb/db.h>

using namespace std;
using namespace leveldb;

int main(void){
	DB *db;
	Options options;
	options.create_if_missing = true;
	string dbpath = "testdb";
	Status status = DB::Open(options, dbpath, &db);
	if(status.ok()){
		Iterator *it = db->NewIterator(ReadOptions());
		cout<<"all data:"<<endl;
		for(it->SeekToFirst(); it->Valid(); it->Next()){
			cout<<it->key().ToString()<<":"
			    <<it->value().ToString()<<endl;
		}
		if(!it->status().ok()){
			cout<<"error"<<endl;
		}
		delete it;
	}
	delete db;
	return 0;
}

