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

#ifndef RPL_H
#define RPL_H

#include <ns3/log.h>
#include <ns3/ipv6-interface.h>
#include <ns3/ipv6-l3-protocol.h>
#include <ns3/ipv6-routing-protocol.h>
#include <ns3/inet6-socket-address.h>
#include <ns3/rpl-routing-table.h>
#include <ns3/rpl-neighbor.h>
#include <ns3/rpl-neighborset.h>
#include <ns3/rpl-header.h>
#include <ns3/rpl-option.h>
#include <ns3/random-variable-stream.h>

namespace ns3 {

class Rpl : public Ipv6RoutingProtocol
{
public:

  /**
   * \brief Constructor
   */
  Rpl (void);

  /**
   * \brief Destructor
   */
  virtual ~Rpl ();

  /**
   * \brief Get the type ID
   * \return type ID
   */
  static TypeId GetTypeId (void);

  /**
   * \param stream first stream index to use
   * \return the number of stream indices assigned by this model
   */
  int64_t AssignStreams (int64_t stream);
  
  /**
   * \brief from Ipv6RoutingProtocol
   *  Query routing cache for an existing route, for an outbound packet
   */
  Ptr<Ipv6Route> RouteOutput (Ptr<Packet> p, const Ipv6Header &header, Ptr<NetDevice> oif, 
                              Socket::SocketErrno &sockerr);
  
  /**
   * \brief from Ipv6RoutingProtocol
   *  Route an input packet (to be forwarded or locally delivered)
   */
  bool RouteInput (Ptr<const Packet> p, const Ipv6Header &header, Ptr<const NetDevice> idev,
                   UnicastForwardCallback ucb, MulticastForwardCallback mcb,
                   LocalDeliverCallback lcb, ErrorCallback ecb);

  /**
   * \brief Receive RPL packets.
   * \param socket the socket the packet was received to.
   */
  void Receive (Ptr<Socket> socket);

  /**
   * \brief DODAG join
   */
  void Join ();

  /**
   * \brief DIS receive
   * \param disMessage Received DIS message
   * \param solicitedInformation Solicited Information option
   * \param senderAddress sender adress
   * \param senderPort sender port
   * \param incomingInterface incoming interface
   */
  void RecvDis (RplDisMessage disMessage, RplSolicitedInformationOption solicitedInformation, Ipv6Address senderAddress, uint32_t incomingInterface, uint16_t senderPort);

  /**
   * \brief DIO receive
   * \param dioMessage Received DIO message
   * \param dodagConfiguration DODAG configuration option
   * \param senderAddress sender adress
   * \param incomingInterface incoming interface
   * \param senderPort sender port
   */
  void RecvDio (RplDioMessage dioMessage, RplDodagConfigurationOption dodagConfiguration, Ipv6Address senderAddress, uint32_t incomingInterface, uint16_t senderPort);

  /*
   * \brief Send Multicast DIS messages
   */
  void SendMulticastDis ();

  /*
   * \brief Send scheduled DIO message
   * \param infiniteRank Infinite rank for poisoning DIO
   */
  void SendDio (uint16_t infiniteRank = 0);

  /*
   * \brief Send DIO message in response to DIS
   * \param senderAddress sender adress
   * \param senderPort sender port
   * \param incomingInterface incoming interface
   */
  void SendDio (Ipv6Address destAddress, uint32_t incomingInterface, uint16_t senderPort);

  /*
   * \brief Send DAO messages
   */
  void SendDao ();

  /*
   * \brief Receive DAO messages
   * \param daoMessage DAO Message
   * \param targetOption Target Option
   * \param transitInformation Transit Information Option
   * \param rplOption RPL Option
   * \param senderAddress the Sender Address
   * \param incomingInterface incoming interface
   * \param senderPort sender port
   */
  void RecvDao (RplDaoMessage daoMessage, RplTargetOption targetOption, RplTransitInformationOption transitInformation, RplOption rplOption, Ipv6Address senderAddress, uint32_t incomingInterface, uint16_t senderPort);

  /**
   * \brief Receive DAO-ACK messages
   * \param daoAckMessage DAO-ACK Message
   * \param rplOption RPL Option
   */
  void RecvDaoAck (RplDaoAckMessage daoAckMessage, RplOption rplOption);

  /**
   * \brief Check for DAO-ACK
   */
  void DaoAckCheck ();

  /*
   * \brief DODAG Disjoin
   */
  void DodagDisjoin ();

  /**
   * \brief Reboot network
   */
  void Reboot ();

  /*
   * \brief Insert to neighborSet
   * \param neighborAddress neighbor address
   * \param dodagID DODAg ID
   * \param dtsn DTSN
   * \param rank rank
   * \param incomingInterface incoming interface
   */
  void InsertNeighbor (Ipv6Address neighborAddress, Ipv6Address dodagID, uint8_t dtsn, uint16_t rank, uint32_t incomingInterface);

  /*
   * \brief Insert to neighborSet
   * \param neighborType neighbor type
   */
  void InsertNeighbor (neighborType type);

  /*
   * \brief Compute rank with selected parent
   */
  void SelectParent ();

  /**
   * \brief Resets the timer
   */
  void ResetTrickle ();

  /**
   * \brief Starts the timer
   */
  void StartTrickle ();  

  /**
   * \brief Restarts the interval
   */
  void RestartInterval ();

  /**
   * \brief Transmit scheduled DIO
   */
  void TrickleTransmit ();

  /**
   * \brief Disable Trickle timer
   */
  void DisableTrickle ();

  virtual void NotifyInterfaceUp (uint32_t interface);
  virtual void NotifyInterfaceDown (uint32_t interface);
  virtual void NotifyAddAddress (uint32_t interface, Ipv6InterfaceAddress address);
  virtual void NotifyRemoveAddress (uint32_t interface, Ipv6InterfaceAddress address);
  virtual void NotifyAddRoute (Ipv6Address dst, Ipv6Prefix mask, Ipv6Address nextHop, uint32_t interface, Ipv6Address prefixToUse = Ipv6Address::GetZero ());
  virtual void NotifyRemoveRoute (Ipv6Address dst, Ipv6Prefix mask, Ipv6Address nextHop, uint32_t interface, Ipv6Address prefixToUse = Ipv6Address::GetZero ());
  virtual void SetIpv6 (Ptr<Ipv6> ipv6);
  virtual void PrintRoutingTable (Ptr<OutputStreamWrapper> stream) const;

private:

  /**
   * \brief the Rng stream
   */
  Ptr<UniformRandomVariable> m_rng;
  
  /// Socket list type
  typedef std::map< Ptr<Socket>, uint32_t> SocketList;
  /// Socket list type iterator
  typedef std::map<Ptr<Socket>, uint32_t>::iterator SocketListI;
  /// Socket list type const iterator
  typedef std::map<Ptr<Socket>, uint32_t>::const_iterator SocketListCI;

  /**
   * \brief Interface address
   */
  Ipv6InterfaceAddress m_address;

  /**
   * \brief Network address of the node
   */ 
  Ipv6Address m_networkAddress;

  /**
   * \brief socket list
   */
  SocketList m_sendSocketList;

  /*
   * \brief receive socket
   */
  Ptr<Socket> m_recvSocket;

  /*
   * \brief Routing Table
   */
  RplRoutingTable m_routingTable;

  /*
   * \brief Neighbor Set
   */
  RplNeighborSet m_neighborSet;

  /**
   * \brief the redundancy constant
   */
  uint8_t m_k;

  /**
   * \brief the maximum interval size
   */
  Time m_iMax;

  /**
   * \brief the minimum interval size
   */
  Time m_iMin;

  /**
   * \brief the counter
   */
  uint8_t m_counter;

  /**
   * \brief the current interval size
   */
  Time m_interval;

  /**
   * \brief the callback time
   */
  Time m_t;

  /**
   * \brief Send DAO
   */
  EventId m_sendDao;

  /**
   * \brief DIO schedule event
   */
  EventId m_dioSchedule;

  /**
   * \brief Restart interval value
   */
  EventId m_restartInterval;

  /**
   * \brief DIO receive marker for Join ()
   */
  uint8_t m_dioReceived;

  /**
   * \brief DIS schedule event
   */
  EventId m_multicastDis;

  /**
   * \brief parent select schedule event
   */
  EventId m_selectParent;

  /**
   * \brief DODAG disjoin schedule event
   */
  EventId m_disjoin;

  /**
   * \brief Network Reboot
   */
  EventId m_reboot;

  /**
   * \brief Node type: 1 - root
   */
  bool m_isRoot;

  /**
   * \brief DAO-ACK receive
   */
  bool m_daoAck;

  /**
   * \brief DAO-ACK count
   */
  uint32_t m_daoAckCount;

  /**
   * \brief Check for DAO-ACK
   */
  EventId m_daoAckCheck;

  /**
   * \brief Notify node if down
   */  
  bool m_notifyDown;

  /**
   * \brief Rank error count
   */
  uint32_t m_rankErrorCount;

protected:
  /**
   * \brief Dispose this object.
   */
  virtual void DoDispose ();

  /**
   * Start protocol operation
   */
  void DoInitialize ();
};

}
#endif /* RPL_H */