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
   * 
   *  Query routing cache for an existing route, for an outbound packet
   */
  Ptr<Ipv6Route> RouteOutput (Ptr<Packet> p, const Ipv6Header &header, Ptr<NetDevice> oif, 
                              Socket::SocketErrno &sockerr);
  
  /**
   * \brief from Ipv6RoutingProtocol
   *
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
   */
  void RecvDio (RplDioMessage dioMessage, RplDodagConfigurationOption dodagConfiguration, Ipv6Address senderAddress, uint32_t incomingInterface);

  /*
   * \brief Send Multicast DIS messages
   */
  void SendMulticastDis ();

  /*
   * \brief Send DIO message in response to DIS
   * \param senderAddress sender adress
   * \param senderPort sender port
   * \param incomingInterface incoming interface
   */
  void SendDio (Ipv6Address destAddress, uint32_t incomingInterface);

  /*
   * \brief Send DIO message in response to DIS
   * \param senderAddress sender adress
   * \param senderPort sender port
   * \param incomingInterface incoming interface
   */
  void SendDio (Ipv6Address destAddress, uint32_t incomingInterface, uint16_t senderPort);


  /*
   * \brief Insert to neighborSet
   * \param neighborAddress neighbor address
   * \param dodagID DODAg ID
   * \param dtsn DTSN
   * \param rank rank
   */
  void InsertNeighbor (Ipv6Address neighborAddress, Ipv6Address dodagID, uint8_t dtsn, uint16_t rank, uint32_t incomingInterface);

  /*
   * \brief Insert to neighborSet
   * \param neighborType neighbor type
   */
  void InsertNeighbor (neighborType type);

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
  uint8_t m_counter; //not sure sa size

  /**
   * \brief the current interval size
   */
  Time m_interval;

  /**
   * \brief the callback time
   */
  Time m_t; //not sure sa size

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