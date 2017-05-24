
#include <list>
#include "ns3/ipv6-routing-protocol.h"
#include "ns3/ipv6-interface.h"
#include "rpl-neighbor.h"
#include "rpl-neighborset.h"  
#include "ns3/log.h"
#include <ostream>


namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("RplNeighborSet");

bool SortByRank (const Neighbor &lhs, const Neighbor &rhs)
{
  return lhs.GetRank() < rhs.GetRank();
}


RplNeighborSet::RplNeighborSet()
{
}

RplNeighborSet::~RplNeighborSet()
{
}

void RplNeighborSet::AddNeighbor(Neighbor neighbor)
{
  m_neighborList.push_back (neighbor);
  m_neighborList.sort (SortByRank);
}

void RplNeighborSet::DeleteNeighbor(Ipv6Address address)
{

  for (NeighborList::iterator it = m_neighborList.begin ();
       it != m_neighborList.end (); it++)
    {
      if (it->GetNeighborAddress () == address)
        {
          m_neighborList.erase (it);
          break;
        }
    }
}



Ptr<Neighbor> RplNeighborSet::FindNeighbor (Ipv6Address address)
{
  Ptr<Neighbor> neighbor = 0;
  for (NeighborList::iterator it = m_neighborList.begin ();
       it != m_neighborList.end (); it++)
    {
      if (it->GetNeighborAddress () == address)
        {
          neighbor = (&(*it));
          return neighbor;
        }
    }
  return NULL;
}

void RplNeighborSet::UpdateNeighbor(Ipv6Address address, Ipv6Address dodagId, uint8_t dtsn, uint16_t rank, uint32_t interface)
{
  for (NeighborList::iterator it = m_neighborList.begin ();
       it != m_neighborList.end (); it++)
    {
      if (it->GetNeighborAddress() == address)
      {
        it->SetDodagId(dodagId);
        it->SetRank(rank);
        it->SetDtsn(dtsn);
        it->SetInterface(interface);    
        break;    
      }
    }
}

void RplNeighborSet::ClearNeighborSet()
{
  m_prefParent = NULL;
  m_neighborList.clear();
}

Ptr<Neighbor> RplNeighborSet::SelectParent(uint16_t rank)
{
  NS_LOG_FUNCTION (this);
  m_neighborList.sort(SortByRank);

  for (NeighborList::iterator it = m_neighborList.begin ();
       it != m_neighborList.end (); it++)
    {
      if (it->GetReachable() && it->GetRank() < rank)
        {
          m_prefParent = &(*it);
          return m_prefParent;
        }
    }

  m_prefParent = NULL;
  return nullptr;
} 

Ptr<Neighbor> RplNeighborSet::GetParent()
{
  NS_LOG_FUNCTION (this);
  if (m_prefParent)
  {
    return m_prefParent;
  }
  return nullptr;
} 

Ipv6Address RplNeighborSet::GetParentAddress()
{
  NS_LOG_FUNCTION (this);
  if (m_prefParent != NULL)
  {
    return m_prefParent->GetNeighborAddress();
  }
  return "::";
} 

}
