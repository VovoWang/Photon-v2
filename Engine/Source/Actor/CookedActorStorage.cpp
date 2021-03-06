#include "Actor/CookedActorStorage.h"

namespace ph
{

CookedActorStorage::CookedActorStorage(CookedActorStorage&& other) : 
	CookedActorStorage()
{
	add(std::move(other));
}

void CookedActorStorage::clear()
{
	m_intersectables.clear();
	m_primitiveMetadatas.clear();
	m_emitters.clear();

	m_intersectables.shrink_to_fit();
	m_primitiveMetadatas.shrink_to_fit();
	m_emitters.shrink_to_fit();
}

void CookedActorStorage::add(std::unique_ptr<Intersectable> intersectable)
{
	if(intersectable != nullptr)
	{
		m_intersectables.push_back(std::move(intersectable));
	}
}

void CookedActorStorage::add(std::unique_ptr<PrimitiveMetadata> metadata)
{
	if(metadata != nullptr)
	{
		m_primitiveMetadatas.push_back(std::move(metadata));
	}
}

void CookedActorStorage::add(std::unique_ptr<Emitter> emitter)
{
	if(emitter != nullptr)
	{
		m_emitters.push_back(std::move(emitter));
	}
}

void CookedActorStorage::add(std::unique_ptr<Transform> transform)
{
	if(transform != nullptr)
	{
		m_transforms.push_back(std::move(transform));
	}
}

void CookedActorStorage::add(CookedUnit&& cookedActor)
{
	add(std::move(cookedActor.intersectables));
	add(std::move(cookedActor.primitiveMetadata));
	add(std::move(cookedActor.emitter));
	add(std::move(cookedActor.transforms));
}

void CookedActorStorage::add(std::vector<std::unique_ptr<Intersectable>>&& intersectables)
{
	for(auto& intersectable : intersectables)
	{
		add(std::move(intersectable));
	}
}

void CookedActorStorage::add(std::vector<std::unique_ptr<Transform>>&& transforms)
{
	for(auto& transform : transforms)
	{
		add(std::move(transform));
	}
}

void CookedActorStorage::add(CookedActorStorage&& other)
{
	m_intersectables.insert(m_intersectables.end(),
		std::make_move_iterator(other.m_intersectables.begin()),
		std::make_move_iterator(other.m_intersectables.end()));
	m_primitiveMetadatas.insert(m_primitiveMetadatas.end(),
		std::make_move_iterator(other.m_primitiveMetadatas.begin()),
		std::make_move_iterator(other.m_primitiveMetadatas.end()));
	m_emitters.insert(m_emitters.end(),
		std::make_move_iterator(other.m_emitters.begin()),
		std::make_move_iterator(other.m_emitters.end()));
	m_transforms.insert(m_transforms.end(),
		std::make_move_iterator(other.m_transforms.begin()),
		std::make_move_iterator(other.m_transforms.end()));
}

std::size_t CookedActorStorage::numIntersectables() const
{
	return m_intersectables.size();
}

}// end namespace ph