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

#ifndef RPL_ROUTING_TABLE_H
#define RPL_ROUTING_TABLE_H

#include <list>
#include <ostream>
#include <ns3/event-id.h>
#include <ns3/ipv6-routing-protocol.h>
#include <ns3/ipv6-interface.h>
#include <ns3/inet6-socket-address.h>
#include <ns3/ipv6-l3-protocol.h>
#include "ns3/ipv6.h"
#include "ns3/ipv6-route.h"
#include "ns3/ipv6-address.h"
#include "ns3/ipv6-header.h"
#include <ns3/log.h>

namespace ns3 {

/*
  .h file  - yung mga kulang na fields both sa entry at dodag table 
*/
class RplRoutingTableEntry 
{
public:

  /**
   * \brief Constructor
   */
  RplRoutingTableEntry (void);

  /**
   * \brief Constructor
   * \param network network address
   * \param networkPrefix network prefix
   * \param nextHop next hop address to route the packet
   * \param interface interface index
   * \param prefixToUse prefix that should be used for source address for this destination
   */
  RplRoutingTableEntry (Ipv6Address network, Ipv6Prefix networkPrefix, Ipv6Address nextHop, uint32_t interface, Ipv6Address prefixToUse);


  /**
   * \brief Constructor
   * \param network network address of the DAO sender
   * \param interface interface index
   * \param dest Ipv6 address of the destination
   */
  RplRoutingTableEntry (Ipv6Address daoSender, uint32_t interface, Ipv6Address nextHop, Ipv6Address dest);

  /**
   * \brief Constructor
   * \param network network address of the DODAG Parent
   * \param interface interface index
   * \param senderPort sender port
   */
  RplRoutingTableEntry (Ipv6Address dodagParent, uint32_t interface, uint16_t senderPort);

  /**
   * \brief Constructor
   * \param network network address of the DODAG Parent
   * \param interface interface index
   */
  RplRoutingTableEntry (Ipv6Address dodagParent, uint32_t interface);


  /**
   * \brief Destructor
   */
  virtual ~RplRoutingTableEntry ();

  /**
   * \brief Get DAO sender
   * \return the dao sender address
   */
  Ipv6Address GetDaoSender () const;

  /**
   * \brief Get DODAG Parent
   * \return the dodag parent address
   */
  Ipv6Address GetDodagParent () const;

  /**
   * \brief Get next hop
   * \return the next hop address
   */
  Ipv6Address GetNextHop () const;

  /**
   * \brief Get destination
   * \return the destination address
   */
  Ipv6Address GetDest () const;

  /**
   * \brief Get Interface
   * \return the interface 
   */
  uint32_t GetInterface () const;

  /**
   * \brief Set Path Sequence
   * \param pathSeqNo the Path Sequence value
   */
  void SetPathSequence (uint8_t pathSeqNo);

  /**
   * \brief Get Path Sequence
   * \return the Path Sequence value
   */
  uint8_t GetPathSequence () const;

  /**
   * \brief Set DAO Sequence
   * \param daoSeqNo the DAO Sequence value
   */
  void SetDaoSequence (uint8_t daoSeqNo);

  /**
   * \brief Get DAO Sequence
   * \return the DAO Sequence value
   */
  uint8_t GetDaoSequence () const;

  /**
   * \brief Set DAO Lifetime
   * \param daoLifetime the DAO Lifetime value
   */
  void SetDaoLifetime (uint8_t daoLifetime);

  /**
   * \brief Get DAO Lifetime
   * \return the DAO Lifetime value
   */
  uint8_t GetDaoLifetime () const;

  /**
   * \brief Set Path Control
   * \param pathControl the Path Control value
   */
  void SetPathControl (uint8_t pathControl);

  /**
   * \brief Get Path Control
   * \return the Path Control value
   */
  uint8_t GetPathControl () const;

  /**
   * \brief Set Retry Counter
   * \param retryCounter the retry counter
   */
  void SetRetryCounter (uint8_t retryCounter);

  /**
   * \brief Get Retry counter
   * \return the retry counter value
   */
  uint8_t GetRetryCounter () const;

  /**
   * \brief Set sender port
   * \param senderPort the sender port
   */
  void SetSenderPort (uint16_t senderPort);

  /**
   * \brief Get sender port
   * \return the sender port value
   */
  uint16_t GetSenderPort () const;

private:

  /**
   * \brief IPv6 address of the DAO Sender
   */
  Ipv6Address m_daoSender;

  /**
   * \brief IPv6 address of the DODAG Parent
   */
  Ipv6Address m_dodagParent;

  /**
   * \brief IPv6 address of the next hop
   */
  Ipv6Address m_nextHop;

  /**
   * \brief IPv6 address of the destination
   */
  Ipv6Address m_dest;

  /**
   * \brief The interface index.
   */
  uint32_t m_interface;

  /**
   * \brief the path sequence
   */
	uint8_t m_pathSeqNo;

  /**
   * \brief the DAO sequence
   */
	uint8_t m_daoSeqNo;

  /**
   * \brief the DAO lifetime
   */
	uint8_t m_daoLifetime;

  /**
   * \brief the path control
   */
	uint8_t m_pathControl;

  /**
   * \brief the retry counter
   */
  uint8_t m_retryCounter;

  /**
   * \brief the sender port
   */
  uint16_t m_senderPort;

};

class RplRoutingTable
{
public:

  /**
   * \brief Constructor
   */
	RplRoutingTable (void);

  /**
   * \brief Destructor
   */  // m_dioSchedule = Simulator::Schedule (m_t, &Rpl::TrickleTransmit (), this);

	virtual ~RplRoutingTable ();

  /**
   * \brief Lookup in the forwarding table for destination.
   * \param dest destination address
   * \param interface output interface if any (put 0 otherwise)
   * \return Ipv6Route to route the packet to reach dest address
   */
  Ptr<Ipv6Route> Lookup (Ipv6Address dest, Ptr<NetDevice> = 0);

  /**
   * \brief Add route to network.
   * \param network network address
   * \param networkPrefix network prefix
   * \param nextHop next hop address to route the packet.
   * \param interface interface index
   * \param prefixToUse prefix that should be used for source address for this destination
   */
  void AddNetworkRouteTo (Ipv6Address network, Ipv6Prefix networkPrefix, Ipv6Address nextHop, uint32_t interface, Ipv6Address prefixToUse);

  /**
   * \brief Add route to network.
   * \param network network address
   * \param interface interface index
   * \param dest Destination address
   * \return true if succesful
   */
  bool AddNetworkRouteTo (Ipv6Address network, uint32_t interface, Ipv6Address nextHop, Ipv6Address dest);

  /**
   * \brief Add route to network.
   * \param network network address
   * \param interface interface index
   * \param senderPort sender port
   * \return true if succesful
   */
  bool AddNetworkRouteTo (Ipv6Address network, uint32_t interface, uint16_t senderPort);

  /**
   * \brief Add route to network.
   * \param network network address
   * \param interface interface index
   * \return true if succesful
   */
  bool AddNetworkRouteTo (Ipv6Address network, uint32_t interface);

  /**
   * \brief Delete a route.
   * \param route the route to be removed
   * \return true if succesful
   */
  bool DeleteRoute (RplRoutingTableEntry *route);

  /**
   * \brief Delete a route.
   * \param route the route to be removed
   * \return true if succesful
   */
  bool DeleteRoute (Ptr<Ipv6Route> route);

  /**
   * \brief Clears the routing table
   * \return true if succesful
   */
  bool ClearRoutingTable ();

  /**
   * \brief 
   * \param interface the interface
   */
  void InvalidateRoute (uint32_t interface);

  /**
   * \brief Prints the routing table
   */
  void PrintRoutingTable ();

	/**
   * \brief Set RPL Instance ID
   * \param rplInstanceId the RPL Instance ID value
   */
  void SetRplInstanceId (uint8_t rplInstanceId);

  /**
   * \brief Get RPL Instance ID
   * \return the RPL Instance ID value
   */
  uint8_t GetRplInstanceId () const;

  /**
   * \brief Set DODAG ID
   * \param dodagId the DODAG ID value
   */
  void SetDodagId (Ipv6Address dodagId);

  /**
   * \brief Get DODAG ID
   * \return the DODAG ID value
   */
  Ipv6Address GetDodagId () const;

  /**
   * \brief Set DODAG version number
   * \param version the DODAG version number value
   */
  void SetVersionNumber (uint8_t version);

  /**
   * \brief Get DODAG version number
   * \return the DODAG version number value
   */
  uint8_t GetVersionNumber () const;

  /**
   * \brief Set rank
   * \param rank the rank value
   */
  void SetRank (uint16_t rank);

  /**
   * \brief Get rank
   * \return the rank value
   */
  uint16_t GetRank () const;

  /**
   * \brief Set Objective Code Point
   * \param ocp the Objective code point value
   */
  void SetObjectiveCodePoint (uint16_t ocp);

  /**
   * \brief Get Objective code point
   * \return the objective code point value
   */
  uint16_t GetObjectiveCodePoint () const;

  /*
   * \param A set of DODAG parents
   * \param A set of prefixes offered Upward along the DODAG
   * \param Trickle timers
   * \param List of DAO parents
   */

  /*
   * \brief Set Node type
   * \param the node type - True if router; False if leaf
   */
  void SetNodeType (bool nodeType);

  /*
   * \brief Get Node type
   * \return the node type - True if router; False if leaf
   */
  bool GetNodeType ();

  /**
   * \brief Set dtsn.
   * \param dtsn the dtsn value
   */
  void SetDtsn (uint8_t dtsn);

  /**
   * \brief Get dtsn.
   * \return the dtsn value
   */
  uint8_t GetDtsn () const;

  /**
   * \brief Set minimum path cost
   * \param cmp the minimum path cost value
   */
  void SetCurMinPathCost (uint16_t cmp);

  /**
   * \brief Get minimum path cost
   * \return the minimum path cost value
   */
  uint16_t GetCurMinPathCost () const;
  /**
   * \brief Set metric.
   * \param metric the metric value
   */
  void SetMetric (uint8_t metric);

  /**
   * \brief Get metric.
   * \return the metric value
   */
  uint8_t GetMetric () const;

  /**
   * \brief G FLag.
   * \param flagG the G flag value
   */
  void SetFlagG (bool flagG);

  /**
   * \brief Get G Flag.
   * \return the G Flag value
   */
  bool GetFlagG ();

  /**
   * \brief Set IPv6 reference
   * \param the ipv6 reference
   */
  void SetIpv6 (Ptr<Ipv6> ipv6);

  /**
   * \brief Get IPv6 reference
   * \return the ipv6 reference
   */
  Ptr<Ipv6> GetIpv6 ();

private:
  /// Container for the network routes - pair RplRoutingTableEntry *, EventId (update event)
  typedef std::list<std::pair <RplRoutingTableEntry *, EventId> > Routes;

  /// Const Iterator for container for the network routes
  typedef std::list<std::pair <RplRoutingTableEntry *, EventId> >::const_iterator RoutesCI;

  /// Iterator for container for the network routes
  typedef std::list<std::pair <RplRoutingTableEntry *, EventId> >::iterator RoutesI;
  
  /**
   * \brief the forwarding table for network
   */
  Routes m_routes;

  /**
   * \brief the IPv6 reference
   */
  Ptr<Ipv6> m_ipv6;

  /**
   * \brief the RPL instance ID
   */
  uint8_t m_rplInstanceId;

  /**
   * \brief the DODAG ID value
   */
  Ipv6Address m_dodagId;

  /**
   * \brief the DODAG version number
   */
  uint8_t m_version;

  /**
   * \brief the rank
   */
  uint16_t m_rank;

  /**
   * \brief the Objective code point
   */
  uint16_t m_ocp;

  /**
   * \brief the node type
   */
  bool m_nodeType;

  /**
   * \brief the dtsn value
   */
  uint8_t m_dtsn;

  /**
   * \brief the G flag
   */
  bool m_flagG;

  /**
   * \brief current minimum path cost
   */
  uint16_t m_curMinPathCost;

  /**
   * \brief current minimum path cost
   */
  uint8_t m_metric;

};

}
#endif /* RPL_ROUTING_TABLE_H */