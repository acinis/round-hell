#include "loaders/animation_data_loader.hpp"

#include "utils.hpp"

namespace rh {

auto AnimationDataLoader::operator()(std::optional<Error>& error, const AnimationData& data) const noexcept -> result_type
{
	RH_UNUSED(error);
	return std::make_shared<AnimationData>(data);
}

} // namespace rh

