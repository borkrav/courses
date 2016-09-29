#include "marshaller.h"
#include "msgProtocol.h"
#include "rpc.h"

using namespace std;

map<int,int> typeMap = {
		{ARG_CHAR, sizeof(char)},
		{ARG_SHORT, sizeof(short)},
		{ARG_INT, sizeof(int)},
		{ARG_LONG, sizeof(long)},
		{ARG_DOUBLE, sizeof(double)},
		{ARG_FLOAT, sizeof(float)}
};

vector<string> marshaller::marshall(message msg){

	switch(msg.type){

		case REGISTER:
			return mRegister(msg);
		case RETURNCODE:
			return mReturnCode(msg);
		case LOC_REQUEST:
			return mLocRequest(msg);
		case LOC_SUCCESS:
			return mLocSuccess(msg);
		case LOC_FAILURE:
			return mLocFailure(msg);
		case EXECUTE:
			return mExecute(msg);
		case EXECUTE_SUCCESS:
			return mExecuteSuccess(msg);
		case EXECUTE_FAILURE:
			return mExecuteFailure(msg);
		case TERMINATE:
			return mTerminate(msg);

	}

}

vector<string> marshaller::mRegister(message msg){
	vector<string> result;
	result.push_back(to_string(msg.type));
	result.push_back(msg.host);
	result.push_back(msg.port);
	result.push_back(msg.name);

	char argTypes[msg.argTypes.size()*4];

	for (int i = 0; i<msg.argTypes.size(); i++){
		int type = msg.argTypes[i];
		memcpy(&(argTypes[i*4]), &type, 4);
	}

	result.push_back(string(reinterpret_cast<char*>(argTypes), msg.argTypes.size()*4));
	return result;
}

vector<string> marshaller::mReturnCode(message msg){
	vector<string> result;
	result.push_back(to_string(msg.type));
	result.push_back(to_string(msg.reasonCode));
	return result;
}

vector<string> marshaller::mLocRequest(message msg){
	vector<string> result;
	result.push_back(to_string(msg.type));

	result.push_back(msg.name);

	char argTypes[msg.argTypes.size()*4];

	for (int i = 0; i<msg.argTypes.size(); i++){
		int type = msg.argTypes[i];
		memcpy(&(argTypes[i*4]), &type, 4);
	}

	result.push_back(string(reinterpret_cast<char*>(argTypes), msg.argTypes.size()*4));

	return result;
}


std::vector<string> marshaller::mLocSuccess(message msg){
	vector<string> result;

	result.push_back(to_string(msg.type));
	result.push_back(msg.host);
	result.push_back(msg.port);

	return result;
}

vector<string> marshaller::mLocFailure(message msg){
	vector<string> result;
	result.push_back(to_string(msg.type));
	result.push_back(to_string(msg.reasonCode));
	return result;
}

vector<string> marshaller::mExecute(message msg){

	vector<string> result;
	result.push_back(to_string(msg.type));
	result.push_back(msg.name);

	//copies all the argtypes
	char argTypes[msg.argTypes.size()*4];

	for (int i = 0; i<msg.argTypes.size(); i++){
		int type = msg.argTypes[i];
		memcpy(&(argTypes[i*4]), &type, 4);
	}

	result.push_back(string(reinterpret_cast<char*>(argTypes), msg.argTypes.size()*4));

	//gets the size of the arguments
	int size = 0;
	for (int i = 0; i<msg.argTypes.size(); i++){
		int rawType = ((msg.argTypes[i] << 8) >> 24);
		int arrayLength = ((msg.argTypes[i] << 16) >> 16);
		if(arrayLength == 0){	
			size += typeMap[rawType];
		}
		else {
			size += typeMap[rawType]*arrayLength;
		}
	}

	char args[size];
	int offset = 0;

	for (int i = 0; i<msg.argTypes.size(); i++){
		int rawType = ((msg.argTypes[i] << 8) >> 24);
		int arrayLength = ((msg.argTypes[i] << 16) >> 16);	

		//valgrind complains about this, not a leak, results seem correct
		void* argument = msg.args[i];

		if(arrayLength == 0){
			memcpy(&(args[offset]), argument, typeMap[rawType]);
			offset += typeMap[rawType];
		}

		else {
			memcpy(&(args[offset]), argument, typeMap[rawType]*arrayLength);
			offset += typeMap[rawType]*arrayLength;
		}


	}

	result.push_back(string(reinterpret_cast<char*>(args), size));

	return result;
}

vector<string> marshaller::mExecuteSuccess(message msg){
	vector<string> result = mExecute(msg);
	result[0] = to_string(EXECUTE_SUCCESS);
	return result;
}

vector<string> marshaller::mExecuteFailure(message msg){
	vector<string> result = mLocFailure(msg);
	result[0] = to_string(EXECUTE_FAILURE);
	return result;
}

vector<string> marshaller::mTerminate(message msg){
	vector<string> result;
	result.push_back(to_string(msg.type));
	return result;
}




message marshaller::unmarshall(int type, vector<string> data){

	switch(type){

		case REGISTER:
			return umRegister(data);
		case RETURNCODE:
			return umReturnCode(data);
		case LOC_REQUEST:
			return umLocRequest(data);
		case LOC_SUCCESS:
			return umLocSuccess(data);
		case LOC_FAILURE:
			return umLocFailure(data);
		case EXECUTE:
			return umExecute(data);
		case EXECUTE_SUCCESS:
			return umExecuteSuccess(data);
		case EXECUTE_FAILURE:
			return umExecuteFailure(data);
		case TERMINATE:
			return umTerminate(data);

	}




}

message marshaller::umExecute(vector<string> data){
	message result;
	result.type = EXECUTE;
	result.name = data[0];

	vector<int> argTypesVector;
	const char* argTypesString = data[1].c_str();

	int type = 0;

	for(int i = 0; i < data[1].length(); i+=4){
		memcpy(&type, argTypesString+i, 4);
		argTypesVector.push_back(type);
	}

	result.argTypes = argTypesVector;

	result.args = (void **)malloc(argTypesVector.size() * sizeof(void *));

	int offset = 0;

	const char* argsString = data[2].c_str();

	for (int i = 0; i<result.argTypes.size(); i++){
		int rawType = ((result.argTypes[i] << 8) >> 24);
		int arrayLength = ((result.argTypes[i] << 16) >> 16);	
		void* argument;
		if(arrayLength == 0){
			argument = malloc(typeMap[rawType]);
			memcpy(argument, &argsString[offset], typeMap[rawType]);
			offset += typeMap[rawType];
		}

		else {
			argument = malloc(typeMap[rawType]*arrayLength);
			memcpy(argument, &argsString[offset], typeMap[rawType]*arrayLength);
			offset += typeMap[rawType]*arrayLength;
		}

		result.args[i] = argument;

	}
	return result;

}

message marshaller::umReturnCode(vector<string> data){
	message result;
	result.type = RETURNCODE;
	result.reasonCode = atoi(data[0].c_str());
	return result;
}

message marshaller::umRegister(vector<string> data){
	message result;
	result.type = REGISTER;
	result.host = data[0];
	result.port = data[1];
	result.name = data[2];

	vector<int> argTypesVector;
	const char* argTypesString = data[3].c_str();

	int type = 0;


	for(int i = 0; i < data[3].length(); i+=4){
		memcpy(&type, argTypesString+i, 4);
		argTypesVector.push_back(type);
	}

	result.argTypes = argTypesVector;

	return result;
}

message marshaller::umLocRequest(vector<string> data){
	message result;
	result.type = LOC_REQUEST;
	result.name = data[0];

	vector<int> argTypesVector;
	const char* argTypesString = data[1].c_str();

	int type = 0;

	for(int i = 0; i < data[1].length(); i+=4){
		memcpy(&type, argTypesString+i, 4);
		argTypesVector.push_back(type);
	}

	result.argTypes = argTypesVector;

	return result;
}

message marshaller::umLocSuccess(vector<string> data){

	message result;

	result.type = LOC_SUCCESS;
	result.host = data[0];
	result.port = data[1];
	return result;

}


message marshaller::umLocFailure(vector<string> data){
	message result;
	result.type = LOC_FAILURE;
	result.reasonCode = atoi(data[0].c_str());
	return result;
}

message marshaller::umExecuteSuccess(vector<string> data){
	message result = umExecute(data);
	result.type = EXECUTE_SUCCESS;
	return result;
}

message marshaller::umExecuteFailure(vector<string> data){
	message result = umLocFailure(data);
	result.type = EXECUTE_FAILURE;
	return result;
}

message marshaller::umTerminate(vector<string> data){
	message result;
	result.type = TERMINATE;
	return result;
}
