/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 *
 * Authors: John Patrick Agustin <jcagustin3@up.edu.ph>
 *          Joshua Jacinto <jhjacinto@up.edu.ph>
 */

#include "ns3/random-variable-stream.h"
#include "ns3/ipv6-route.h"
#include "ns3/log.h"
#include "rpl-routing-table.h"

#include <iostream>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("RplRoutingTable");

//NS_OBJECT_ENSURE_REGISTERED (Rpl);

/*
 * RplRoutingTableEntry
 */

RplRoutingTableEntry::RplRoutingTableEntry ()
  : m_pathSeqNo(0), m_daoSeqNo(0), m_daoLifetime(0), m_pathControl(0), m_retryCounter(0), m_senderPort(0)
{
}

RplRoutingTableEntry::RplRoutingTableEntry (Ipv6Address network, uint32_t interface, Ipv6Address nextHop, Ipv6Address dest)
  : m_daoSender(network), m_nextHop(nextHop), m_dest(dest), m_interface(interface)
{
}

RplRoutingTableEntry::RplRoutingTableEntry (Ipv6Address network, uint32_t interface, uint16_t senderPort)
  : m_dodagParent(network), m_dest(network), m_interface(interface), m_pathSeqNo(0), m_daoSeqNo(0), m_daoLifetime(0), 
    m_pathControl(0), m_retryCounter(0), m_senderPort(senderPort)
{
}

RplRoutingTableEntry::RplRoutingTableEntry (Ipv6Address network, uint32_t interface)
  : m_dodagParent(network), m_dest(network), m_interface(interface), m_pathSeqNo(0), m_daoSeqNo(0), m_daoLifetime(0), 
    m_pathControl(0), m_retryCounter(0), m_senderPort(0)
{
}

RplRoutingTableEntry::~RplRoutingTableEntry ()
{
}

Ipv6Address RplRoutingTableEntry::GetDaoSender () const
{
  return m_daoSender;
}

Ipv6Address RplRoutingTableEntry::GetDodagParent () const
{
  return m_dodagParent;
}

Ipv6Address RplRoutingTableEntry::GetNextHop () const
{
  return m_nextHop;
}

Ipv6Address RplRoutingTableEntry::GetDest () const
{
  return m_dest;
}

uint32_t RplRoutingTableEntry::GetInterface () const
{
  return m_interface;
}

void RplRoutingTableEntry::SetPathSequence (uint8_t pathSeqNo)
{
  m_pathSeqNo = pathSeqNo;
}

uint8_t RplRoutingTableEntry::GetPathSequence () const
{
  return m_pathSeqNo;
}

void RplRoutingTableEntry::SetDaoSequence (uint8_t daoSeqNo)
{
  m_daoSeqNo = daoSeqNo;
}

uint8_t RplRoutingTableEntry::GetDaoSequence () const
{
  return m_daoSeqNo;
}

void RplRoutingTableEntry::SetDaoLifetime (uint8_t daoLifetime)
{
  m_daoLifetime = daoLifetime;
}

uint8_t RplRoutingTableEntry::GetDaoLifetime () const
{
  return m_daoLifetime;
}

void RplRoutingTableEntry::SetPathControl (uint8_t pathControl)
{
  m_pathControl = pathControl;
}

uint8_t RplRoutingTableEntry::GetPathControl () const
{
  return m_pathControl;
}

void RplRoutingTableEntry::SetRetryCounter (uint8_t retryCounter)
{
  m_retryCounter = retryCounter;
}

uint8_t RplRoutingTableEntry::GetRetryCounter () const
{
  return m_retryCounter;
}

void RplRoutingTableEntry::SetSenderPort (uint16_t senderPort)
{
  m_senderPort = senderPort;
}

uint16_t RplRoutingTableEntry::GetSenderPort () const
{
  return m_senderPort;
}

/*
 * RplRoutingTable
 */

RplRoutingTable::RplRoutingTable ()
  : m_ipv6 (0), m_rplInstanceId(0), m_dodagId("::"), m_version(0), m_rank(0), m_ocp(0), m_nodeType(true), m_dtsn(0), m_flagG(true), m_metric(0)
{

}

RplRoutingTable::~RplRoutingTable ()
{	
}

void RplRoutingTable::SetRplInstanceId (uint8_t rplInstanceId)
{
  m_rplInstanceId = rplInstanceId;
}

uint8_t RplRoutingTable::GetRplInstanceId () const
{
  return m_rplInstanceId;
}

void RplRoutingTable::SetDodagId (Ipv6Address dodagId)
{
  m_dodagId = dodagId;
}

Ipv6Address RplRoutingTable::GetDodagId () const
{
  return m_dodagId;
}

void RplRoutingTable::SetVersionNumber (uint8_t version)
{
  m_version = version;
}

uint8_t RplRoutingTable::GetVersionNumber () const
{
  return m_version;
}

void RplRoutingTable::SetRank (uint16_t rank)
{
  m_rank = rank;
}

uint16_t RplRoutingTable::GetRank () const
{
  return m_rank;
}

void RplRoutingTable::SetObjectiveCodePoint (uint16_t ocp)
{
  m_ocp = ocp;
}

uint16_t RplRoutingTable::GetObjectiveCodePoint () const
{
  return m_ocp;
}

void RplRoutingTable::SetNodeType (bool nodeType)
{
  m_nodeType = nodeType;
}

bool RplRoutingTable::GetNodeType ()
{
  return m_nodeType;
}

void RplRoutingTable::SetDtsn (uint8_t dtsn)
{
  m_dtsn = dtsn;
}

uint8_t RplRoutingTable::GetDtsn () const
{
  return m_dtsn;
}

void RplRoutingTable::SetFlagG (bool flagG)
{
  m_flagG = flagG;
}

bool RplRoutingTable::GetFlagG ()
{
  return m_flagG;
}

void RplRoutingTable::SetIpv6 (Ptr<Ipv6> ipv6)
{
  m_ipv6 = ipv6;
}

Ptr<Ipv6> RplRoutingTable::GetIpv6 ()
{
  return m_ipv6;
}

void RplRoutingTable::SetCurMinPathCost (uint16_t cmp)
{
  m_curMinPathCost = cmp;
}

uint16_t RplRoutingTable::GetCurMinPathCost () const
{
  return m_curMinPathCost;
}

void RplRoutingTable::SetMetric (uint8_t metric)
{
  m_metric = metric;
}
 
uint8_t RplRoutingTable::GetMetric () const
{
  return m_metric;
}

Ptr<Ipv6Route> RplRoutingTable::Lookup (Ipv6Address dst, Ptr<NetDevice> interface)
{
  NS_LOG_FUNCTION (this << dst);

  Ptr<Ipv6Route> rtentry = 0;

  if (dst.IsLinkLocalMulticast ())
    {
      std::cout << "Multicast Lookup\n";
      NS_ASSERT_MSG (interface, "Try to send on link-local multicast address, and no interface index is given!");
      rtentry = Create<Ipv6Route> ();
      rtentry->SetSource (m_ipv6->SourceAddressSelection (m_ipv6->GetInterfaceForDevice (interface), dst));
      rtentry->SetDestination (dst);
      rtentry->SetGateway (Ipv6Address::GetZero ());
      rtentry->SetOutputDevice (interface);
      return rtentry;      
    }

  std::cout << "Unicast Lookup\n";
  for (RoutesI it = m_routes.begin (); it != m_routes.end (); it++)
    {
      RplRoutingTableEntry* j = it->first;

      if (j->GetDest () == dst)
        { 
          RplRoutingTableEntry* route = j;
          uint32_t interfaceIdx = route->GetInterface ();
          rtentry = Create<Ipv6Route> ();

          rtentry->SetSource (m_ipv6->SourceAddressSelection (interfaceIdx, route->GetDest ()));
          rtentry->SetDestination (route->GetDest ());
          rtentry->SetOutputDevice (m_ipv6->GetNetDevice (interfaceIdx));
        }
    }

  if (rtentry)
    {
      NS_LOG_LOGIC ("Matching route via " << rtentry->GetDestination ());
    }

  return rtentry;
}

bool RplRoutingTable::AddNetworkRouteTo (Ipv6Address network, uint32_t interface, Ipv6Address nextHop, Ipv6Address dest)
{
  NS_LOG_FUNCTION (this << network << interface << dest);

  RplRoutingTableEntry* route = new RplRoutingTableEntry (network, interface, nextHop, dest);

  m_routes.push_back (std::make_pair (route, EventId ()));
  return true;
}

bool RplRoutingTable::AddNetworkRouteTo (Ipv6Address network, uint32_t interface, uint16_t senderPort)
{
  NS_LOG_FUNCTION (this << network << interface);

  RplRoutingTableEntry* route = new RplRoutingTableEntry (network, interface, senderPort);

  m_routes.push_back (std::make_pair (route, EventId ()));
  return true;
}

bool RplRoutingTable::AddNetworkRouteTo (Ipv6Address network, uint32_t interface)
{
  NS_LOG_FUNCTION (this << network << interface);

  RplRoutingTableEntry* route = new RplRoutingTableEntry (network, interface);

  m_routes.push_back (std::make_pair (route, EventId ()));
  return true;
}

bool RplRoutingTable::DeleteRoute (RplRoutingTableEntry *route)
{
  //NS_LOG_FUNCTION (this << *route);

  for (RoutesI it = m_routes.begin (); it != m_routes.end (); it++)
    {
      if (it->first == route)
        {
          delete route;
          m_routes.erase (it);
          return true;
        }
    }
  NS_ABORT_MSG ("RplRoutingTable::DeleteRoute - cannot find the route to delete");
  return false;
}

bool RplRoutingTable::DeleteRoute (Ptr<Ipv6Route> route)
{
  //NS_LOG_FUNCTION (this << *route);
  Ipv6Address dest = route->GetDestination ();

  for (RoutesI it = m_routes.begin (); it != m_routes.end (); it++)
    {
      RplRoutingTableEntry* j = it->first;

      if (j->GetDest () == dest)
        {
          // delete j;
          m_routes.erase (it);
          return true;
        }
    }
  NS_ABORT_MSG ("RplRoutingTable::DeleteRoute - cannot find the route to delete");
  return false;
}

bool RplRoutingTable::ClearRoutingTable ()
{
  for (RoutesI j = m_routes.begin ();  j != m_routes.end (); j = m_routes.erase (j))
    {
      delete j->first;
    }
  m_routes.clear();
  
  SetRplInstanceId (0);
  SetDodagId ("::");
  SetVersionNumber (0);
  SetRank (0);
  SetObjectiveCodePoint (0);
  SetNodeType (true);
  SetDtsn (0);

  return true;
}

void RplRoutingTable::InvalidateRoute (uint32_t interface)
{
  for (RoutesI it = m_routes.begin (); it != m_routes.end (); it++)
    {
      if (it->first->GetInterface () == interface)
        {
          //DeleteRoute (it->first);
        }
    }
}

void RplRoutingTable::PrintRoutingTable ()
{
  for (RoutesI it = m_routes.begin (); it != m_routes.end (); it++)
    {
      RplRoutingTableEntry* j = it->first;
      Ipv6Address dest = j->GetDest ();

      std::cout << "Routing Table Entry destination: " << dest << "\n";
    }
}

}