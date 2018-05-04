
#include "Export.h"
#include "Types.h"

namespace NetCom
{
	class ResourceManager;
	class NETCOMMUNICATION_EXPORT UserInterface
	{
	public:
		UserInterface();
		~UserInterface();

		void Push(UInt8 * data, UInt32 len);

		void Init();
		static UserInterface & GetInstance();
	private:
		ResourceManager * m_ResourceManager;
	};


}


