#include <Client.h>
#include <LogUtility.h>

int main()
{
	using namespace Catherine;

	Client * tmp_client = Client::Instance();
	if (tmp_client == nullptr)
	{
		LogError("Get Client Instance Failed...");
		return -1;
	}

	bool tmp_initialized = tmp_client->Initialize();
	if (!tmp_initialized)
	{
		LogError("Client Initialize Failed...");
		return -1;
	}

	// Main Loop
	tmp_client->Run();

	tmp_client->Uninitialize();

	return 0;
}
