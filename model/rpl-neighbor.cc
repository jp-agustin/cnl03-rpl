
#include "ns3/rpl-neighbor.h"

namespace ns3 {


Ipv6Address Neighbor::GetNeighborAddress(void) const
{
  return m_address;
}

void Neighbor::SetNeighborAddress(Ipv6Address address)
{
  m_address = address;
}

Ipv6Address Neighbor::GetDodagId(void) const
{
  return m_dodagId;
}

void Neighbor::SetDodagId(Ipv6Address dodagId)
{
  m_dodagId = dodagId;
}

uint8_t Neighbor::GetDtsn(void) const
 {
  return m_dtsn;
}

void Neighbor::SetDtsn(uint8_t dtsn)
{
  m_dtsn = dtsn;
}

uint16_t Neighbor::GetRank(void) const
{
  return m_rank;
}

void Neighbor::SetRank(uint16_t rank)
{
  m_rank = rank;
}

uint32_t Neighbor::GetInterface(void) const
{
  return m_interface;
}

void Neighbor::SetInterface(uint32_t interface)
{
  m_interface = interface;
}

uint32_t Neighbor::GetNeighborType(void) const
{
  return m_type;
}

void Neighbor::SetNeighborType(neighborType type)
{
  m_type = type;
}

bool Neighbor::GetReachable(void) const
{
  return m_reachability;
}

void Neighbor::SetReachable(bool reach)
{
  m_reachability = reach;
}

}