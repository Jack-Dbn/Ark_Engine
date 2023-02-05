#include "System.h"

std::bitset<Ark::EntityController::MAX_COMPONENTS> System::GetFilterMask()
{
    return m_filterMask;
}

bool System::SetEntityList(std::vector<unsigned int> newEntityList)
{
    m_EntityList = newEntityList;

    return true;
}
