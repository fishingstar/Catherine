#include <Client.h>
#include <log.h>

using namespace Catherine;

int main()
{
	Client * tmp_client = Client::Instance();
	if (tmp_client == nullptr)
	{
		LogModule::Instance()->LogError("Get Client Instance Failed...");
		return -1;
	}

	bool tmp_initialized = tmp_client->Initialize();
	if (!tmp_initialized)
	{
		LogModule::Instance()->LogError("Client Initialize Failed...");
		return -1;
	}

	// Main Loop
	tmp_client->Run();

	tmp_client->Uninitialize();

	return 0;
}
