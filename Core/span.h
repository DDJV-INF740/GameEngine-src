#include <gsl/span>

namespace engine
{
	template <class ElementType, std::ptrdiff_t Extent = gsl::dynamic_extent>
	using span = gsl::span<ElementType, Extent>;
}
