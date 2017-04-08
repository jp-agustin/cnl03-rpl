
#include "ns3/rpl-neighbor.h"

namespace ns3 {

//NS_LOG_COMPONENT_DEFINE ("RplNeigbor");

Ipv6Address Neighbor::GetNeighborAddress(void) const
{
//  NS_LOG_FUNCTION (this);
  return m_address;
}

void Neighbor::SetNeighborAddress(Ipv6Address address)
{
//  NS_LOG_FUNCTION (this << address);
  m_address = address;
}

Ipv6Address Neighbor::GetDodagId(void) const
{
//  NS_LOG_FUNCTION (this);
  return m_dodagId;
}

void Neighbor::SetDodagId(Ipv6Address dodagId)
{
//  NS_LOG_FUNCTION (this << dodagId);
  m_dodagId = dodagId;
}

uint8_t Neighbor::GetDtsn(void) const
 {
//  NS_LOG_FUNCTION (this);
  return m_dtsn;
}

void Neighbor::SetDtsn(uint8_t dtsn)
{
//  NS_LOG_FUNCTION (this << dtsn);
  m_dtsn = dtsn;
}

uint16_t Neighbor::GetRank(void) const
{
//  NS_LOG_FUNCTION (this);
  return m_rank;
}

void Neighbor::SetRank(uint16_t rank)
{
//  NS_LOG_FUNCTION (this << rank);
  m_rank = rank;
}

uint32_t Neighbor::GetInterface(void) const
{
//  NS_LOG_FUNCTION (this);
  return m_interface;
}

void Neighbor::SetInterface(uint32_t interface)
{
//  NS_LOG_FUNCTION (this << interface);
  m_interface = interface;
}

uint32_t Neighbor::GetNeighborType(void) const
{
//  NS_LOG_FUNCTION (this);
  return m_type;
}

void Neighbor::SetNeighborType(neighborType type)
{
//  NS_LOG_FUNCTION (this << type);
  m_type = type;
}

bool Neighbor::GetReachable(void) const
{
//  NS_LOG_FUNCTION (this);
  return m_reachability;
}

void Neighbor::SetReachable(bool reach)
{
//  NS_LOG_FUNCTION (this << type);
  m_reachability = reach;
}

}