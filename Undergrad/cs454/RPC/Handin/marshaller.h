#include <vector>
#include <iostream>
#include <map>

struct message;

class marshaller {

	public:
	static std::vector<std::string> marshall(message msg);
	static message unmarshall(int type, std::vector<std::string> data);

	private:
	static std::vector<std::string> mRegister(message msg);
	static std::vector<std::string> mReturnCode(message msg);
	static std::vector<std::string> mLocRequest(message msg);
	static std::vector<std::string> mLocSuccess(message msg);
	static std::vector<std::string> mLocFailure(message msg);
	static std::vector<std::string> mExecute(message msg);
	static std::vector<std::string> mExecuteSuccess(message msg);
	static std::vector<std::string> mExecuteFailure(message msg);
	static std::vector<std::string> mTerminate(message msg);

	static message umRegister(std::vector<std::string> data);
	static message umReturnCode(std::vector<std::string> data);
	static message umLocRequest(std::vector<std::string> data);
	static message umLocSuccess(std::vector<std::string> data);
	static message umLocFailure(std::vector<std::string> data);
	static message umExecute(std::vector<std::string> data);
	static message umExecuteSuccess(std::vector<std::string> data);
	static message umExecuteFailure(std::vector<std::string> data);
	static message umTerminate(std::vector<std::string> data);


};
