
#include <list>
#include "ns3/ipv6-routing-protocol.h"
#include "ns3/ipv6-interface.h"
#include "rpl-neighbor.h"
#include "rpl-neighborset.h"  
#include "ns3/log.h"
#include <ostream>


namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("RplNeighborSet");

//NS_OBJECT_ENSURE_REGISTERED(RplNeighborSet);

bool SortByRank (const Neighbor &lhs, const Neighbor &rhs)
{
  return lhs.GetRank() < rhs.GetRank();
}


RplNeighborSet::RplNeighborSet()
{
//  NS_LOG_FUNCTION(this);
}

RplNeighborSet::~RplNeighborSet()
{
//  NS_LOG_FUNCTION(this);
}
/*
TypeId RplNeighborSet::GetTypeId ()
{
  static TypeId tid = TypeId ("ns3::RplNeighborSet")
//  .SetParent<Icmpv6OptionHeader> ()
    .SetGroupName ("Rpl")
    .AddConstructor<RplNeighborSet> ()
  ;
  return tid;
}

TypeId RplNeighborSet::GetInstanceTypeId () const
{
//  NS_LOG_FUNCTION (this);
  return GetTypeId ();
}
*/
//void RplNeighborSet::AddNeighbor(Ipv6Address address, Ipv6Address dodagId, uint8_t dtsn, uint16d _t rank, uint32_t interface)

void RplNeighborSet::AddNeighbor(Neighbor neighbor)
{
//  NS_LOG_FUNCTION (this << neighbor);
  m_neighborList.push_back (neighbor);
  m_neighborList.sort(SortByRank);
  for (NeighborList::iterator it = m_neighborList.begin ();
       it != m_neighborList.end (); it++)
    {
    std::cout << "Inserted : " << it->GetNeighborAddress() << std::endl;
  }
}

void RplNeighborSet::DeleteNeighbor(Ipv6Address address)
{
//  NS_LOG_FUNCTION (this << address);

  for (NeighborList::iterator it = m_neighborList.begin ();
       it != m_neighborList.end (); it++)
    {
      if (it->GetNeighborAddress() == address)
        {
          m_neighborList.erase (it);
          break;
        }
    }
}



Ptr<Neighbor> RplNeighborSet::FindNeighbor (Ipv6Address address)
{
//  NS_LOG_FUNCTION (this << address);
  Ptr<Neighbor> neighbor = 0;
  for (NeighborList::iterator it = m_neighborList.begin ();
       it != m_neighborList.end (); it++)
    {
      if (it->GetNeighborAddress() == address)
        {
          neighbor = (&(*it));
          return neighbor;
        }
    }
  return NULL;
}

void RplNeighborSet::UpdateNeighbor(Ipv6Address address, Ipv6Address dodagId, uint8_t dtsn, uint16_t rank, uint32_t interface)
{
 // NS_LOG_FUNCTION (this << address << dodagId << dtsn << rank << interface);
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
//  NS_LOG_FUNCTION (this);

  for (NeighborList::iterator it = m_neighborList.begin ();
       it != m_neighborList.end (); it++)
    {
        m_neighborList.erase (it);
    }
}

Ptr<Neighbor> RplNeighborSet::SelectParent(/*uint16_t rank*/)
{
  NS_LOG_FUNCTION (this);
  m_neighborList.sort(SortByRank);
  for (NeighborList::iterator it = m_neighborList.begin ();
       it != m_neighborList.end (); it++)
    {
    std::cout << "SelectParent ranks : " << it->GetNeighborAddress() << std::endl;
      if (it->GetReachable()/* && it->GetRank() < rank*/)
      {
        m_prefParent = &(*it);
        std::cout << "Rank is " << m_prefParent->GetRank() << std::endl;
        return m_prefParent;
      }
    }
  return NULL;
} 

Ipv6Address RplNeighborSet::GetParent()
{
  NS_LOG_FUNCTION (this);
  if (m_prefParent != NULL)
  {
    return m_prefParent->GetNeighborAddress();
  }
  return "::";
} 

}
