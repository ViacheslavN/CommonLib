

#include "../crypto.h"

namespace CommonLib
{
	namespace crypto
	{
		namespace openssllib
		{
			class COpenSSlLIb
			{
			public:
				~COpenSSlLIb();
				static COpenSSlLIb& Instance();
			private:
				COpenSSlLIb();
				static COpenSSlLIb inst;
			};
		}
	}
}