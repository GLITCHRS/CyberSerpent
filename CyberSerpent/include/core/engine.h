#pragma once

// forward decls
namespace CS
{
	class Shell;
}

namespace CS
{
	namespace CORE
	{
		class Engine
		{
		public:
			Engine() = delete;

		public:
			static void Run();

		public :
			static CS::Shell& m_Shell;
		};
	}
}