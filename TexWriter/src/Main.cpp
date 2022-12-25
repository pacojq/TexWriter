#include "twpch.h"
#include "Core/Log.h"
#include "Core/Application.h"


int main(int argc, char** argv)
{
	TexWriter::Log::Init();

	TW_LOG_TRACE("TextureForge v{0}.{1}.{2}", TW_VERSION_MAJOR, TW_VERSION_MINOR, TW_VERSION_PATCH);
	TW_LOG_TRACE("Initializing...");

	auto app = new TexWriter::Application();
	TW_ASSERT(app, "Client Application is null!");

	app->Run();

	delete app;

	TW_LOG_TRACE("Shutting down...");
}