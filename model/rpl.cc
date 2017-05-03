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

#define DEFAULT_DIO_INTERVAL_DOUBLINGS 16
#define DEFAULT_DIO_INTERVAL_MIN 3
#define DEFAULT_DIO_REDUNDANCY_CONSTANT 10

#define RPL_DEFAULT_INSTANCE 0
#define DEFAULT_PATH_CONTROL_SIZE 0
#define DEFAULT_DAO_DELAY 1

#define DEFAULT_STEP_OF_RANK 3
#define MINIMUM_STEP_OF_RANK 1
#define MAXIMUM_STEP_OF_RANK 9
#define DEFAULT_RANK_STRETCH 0
#define MAXIMUM_RANK_STRETCH 5
#define DEFAULT_RANK_FACTOR 1
#define MINIMUM_RANK_FACTOR 1
#define MAXIMUM_RANK_FACTOR 4
#define DEFAULT_MIN_HOP_RANK_INCREASE 256
#define ALL_RPL_NODES "ff02::1a"

#define BASE_RANK 0
#define RPL_PORT 521
#define ROOT_RANK 1 
#define INFINITE_RANK 0xffff
#define ROOT_ADDRESS "2001:1::"
//#define ROOT_ADDRESS "2001:1::200:ff:fe00:1"

#define MOP 1
#define OCP 0
#define trickle 0
#define DAO 1

#include <iostream>
#include <cmath>
#include "ns3/log.h"
#include "ns3/abort.h"
#include "ns3/assert.h"
#include "ns3/node.h"

#include "ns3/ipv6-route.h"
#include "ns3/ipv6-packet-info-tag.h"
#include "ns3/icmpv6-header.h"
#include "rpl.h"
#include "rpl-header.h"
#include "rpl-option.h"
#include "rpl-objective-function.h"
#include "ns3/simulator.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("Rpl");

NS_OBJECT_ENSURE_REGISTERED (Rpl);

Rpl::Rpl ()
  : m_k(DEFAULT_DIO_REDUNDANCY_CONSTANT), m_counter(0), m_dioReceived(0)
{
  m_rng = CreateObject<UniformRandomVariable> ();
}

Rpl::~Rpl ()
{ 
}

TypeId Rpl::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::Rpl")
    .SetParent<Ipv6RoutingProtocol> ()
    .SetGroupName ("Rpl")
    .AddConstructor<Rpl> ()
    .AddAttribute ("MinimumIntervalSize", "Minimum Interval Size",
                   TimeValue (MilliSeconds(pow(2, DEFAULT_DIO_INTERVAL_MIN))),
                   MakeTimeAccessor (&Rpl::m_iMin),
                   MakeTimeChecker ())
    .AddAttribute ("MaximumIntervalSize", "Maximum Interval Size",
                   TimeValue (MilliSeconds(pow(2, DEFAULT_DIO_INTERVAL_DOUBLINGS) * pow(2, DEFAULT_DIO_INTERVAL_MIN))),
                   MakeTimeAccessor (&Rpl::m_iMax),
                   MakeTimeChecker ())
    ;

  return tid;
}

void Rpl::DoInitialize ()
{
  NS_LOG_FUNCTION (this);

  bool isRoot = 0;

  for (uint32_t i = 0 ; i < m_routingTable.GetIpv6()->GetNInterfaces (); i++)
  {
    for (uint32_t j = 0; j < m_routingTable.GetIpv6()->GetNAddresses (i); j++)
      {
         Ipv6InterfaceAddress address = m_routingTable.GetIpv6()->GetAddress (i, j);

         if (address.GetScope() == Ipv6InterfaceAddress::LINKLOCAL)
          {
            NS_LOG_LOGIC ("RPL: adding socket to " << address.GetAddress ());
            TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
            Ptr<Node> theNode = GetObject<Node> ();
            Ptr<Socket> socket = Socket::CreateSocket (theNode, tid);
            Inet6SocketAddress local = Inet6SocketAddress (address.GetAddress (), RPL_PORT);

            int ret = socket->Bind (local);
            NS_ASSERT_MSG (ret == 0, "Bind unsuccessful");
            socket->BindToNetDevice (m_routingTable.GetIpv6()->GetNetDevice (i));
            socket->SetRecvCallback (MakeCallback (&Rpl::Receive, this));
            socket->SetIpv6RecvHopLimit (true);
            socket->SetRecvPktInfo (true);
            m_sendSocketList[socket] = i;
          }
      }
  }

  for (uint32_t i = 0 ; i < m_routingTable.GetIpv6 ()->GetNInterfaces (); i++)
    {
      for (uint32_t j = 0; j < m_routingTable.GetIpv6 ()->GetNAddresses (i); j++)
        {
          Ipv6InterfaceAddress address =  m_routingTable.GetIpv6 ()->GetAddress (i, j);
          Ipv6Prefix networkMask = address.GetPrefix ();
          Ipv6Address networkAddress = address.GetAddress ().CombinePrefix (networkMask);
          
          //if (address.GetAddress() == (ROOT_ADDRESS))
            if (networkAddress == (ROOT_ADDRESS))
            {
              m_routingTable.SetRank (ROOT_RANK);
              m_routingTable.SetNodeType (true);
              m_routingTable.SetRplInstanceId (0);
              m_routingTable.SetDtsn (1);
              m_routingTable.SetVersionNumber (1);
              m_routingTable.SetDodagId ("2002:1::"); //Di pa ko sure kung paano nag-aaddressing.
              m_routingTable.SetFlagG (true);
              //SendDio ();
              isRoot = 1;
              StartTrickle ();
              break;
            }
        }
  }

  if (!m_recvSocket) 
    {
      NS_LOG_LOGIC ("RPL: adding receiving socket");
      TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
      Ptr<Node> theNode = GetObject<Node> ();
      m_recvSocket = Socket::CreateSocket (theNode, tid);
      Inet6SocketAddress local = Inet6SocketAddress (ALL_RPL_NODES, 521);
      m_recvSocket->Bind (local);
      m_recvSocket->SetRecvCallback (MakeCallback (&Rpl::Receive, this));
      m_recvSocket->SetIpv6RecvHopLimit (true);
      m_recvSocket->SetRecvPktInfo (true);
    }

  if (!isRoot)
  {
    Join ();
  }

  Ipv6RoutingProtocol::DoInitialize ();
}

int64_t Rpl::AssignStreams (int64_t stream)
{
  NS_LOG_FUNCTION (this << stream);

  m_rng->SetStream (stream);
  return 1;
}

Ptr<Ipv6Route> Rpl::RouteOutput (Ptr<Packet> p, const Ipv6Header &header, Ptr<NetDevice> oif, Socket::SocketErrno &sockerr)
{
  NS_LOG_FUNCTION (this << header << oif);
  Ipv6Address destination = header.GetDestinationAddress ();
  std::cout << "Route Output." <<std::endl << "Destination is " << destination << std::endl;
  std::cout << "This node's address is: " << m_routingTable.GetIpv6()->GetAddress(1,0) << std::endl;

  Ptr<Ipv6Route> rtentry = 0;
  if (destination.IsMulticast ())
    {
      NS_LOG_LOGIC ("RouteOutput (): Multicast destination");
      uint32_t outgoingInterface = m_routingTable.GetIpv6 ()->GetInterfaceForDevice (oif);
      Ptr<Ipv6MulticastRoute> multicastEntry = Create<Ipv6MulticastRoute> ();

      multicastEntry->SetGroup (destination);
      multicastEntry->SetOrigin (header.GetSourceAddress ());
      multicastEntry->SetOutputTtl (outgoingInterface, 255);
    }
  
  rtentry = m_routingTable.Lookup (destination, oif);
  if (rtentry)
    {
      std::cout << "Route found\n";
      sockerr = Socket::ERROR_NOTERROR;
    }
  else
    {
      std::cout << "Route not found\n";
      sockerr = Socket::ERROR_NOROUTETOHOST;
    }

  return rtentry;
}

bool Rpl::RouteInput (Ptr<const Packet> p, const Ipv6Header &header, Ptr<const NetDevice> idev, UnicastForwardCallback ucb, MulticastForwardCallback mcb,
                        LocalDeliverCallback lcb, ErrorCallback ecb)
{
  NS_LOG_FUNCTION (this << p << header << header.GetSourceAddress () << header.GetDestinationAddress () << idev);
  std::cout << "Enters Route Input" << std::endl;
  
  NS_ASSERT (m_routingTable.GetIpv6 () != 0);
  NS_ASSERT (m_routingTable.GetIpv6 ()->GetInterfaceForDevice (idev) >= 0);
  uint32_t iif = m_routingTable.GetIpv6 ()->GetInterfaceForDevice (idev);
  Ipv6Address dst = header.GetDestinationAddress ();

  if (dst.IsMulticast ())
    {
      Ptr<Ipv6MulticastRoute> multicastEntry = Create<Ipv6MulticastRoute> ();

      multicastEntry->SetGroup (dst);
      multicastEntry->SetOrigin (header.GetSourceAddress ());
      multicastEntry->SetParent (iif);

      mcb (idev, multicastEntry, p, header);
      return true; 
    }

  if (header.GetDestinationAddress ().IsLinkLocal () ||
      header.GetSourceAddress ().IsLinkLocal ())
    {
      NS_LOG_LOGIC ("Dropping packet not for me and with src or dst LinkLocal");
      if (!ecb.IsNull ())
        {
          ecb (p, header, Socket::ERROR_NOROUTETOHOST);
        }
      return false;
    }

  if (m_routingTable.GetIpv6 ()->IsForwarding (iif) == false)
    {
      NS_LOG_LOGIC ("Forwarding disabled for this interface");
      if (!ecb.IsNull ())
        {
          ecb (p, header, Socket::ERROR_NOROUTETOHOST);
        }
      return true;
    }

  NS_LOG_LOGIC ("Unicast destination");
  Ptr<Ipv6Route> rtentry = m_routingTable.Lookup (header.GetDestinationAddress ());
  if (rtentry != 0)
    {
      NS_LOG_LOGIC ("Found unicast destination - calling unicast callback");
      ucb (idev, rtentry, p, header);
      return true;
    }
  else
    {
      NS_LOG_LOGIC ("Did not find unicast destination - returning false");
      return false;
    }
}

void Rpl::Receive (Ptr<Socket> socket)
{
  NS_LOG_FUNCTION (this << socket);
  
  Address sender;
  Ptr<Packet> packet = socket->RecvFrom (sender);
  Inet6SocketAddress senderAddr = Inet6SocketAddress::ConvertFrom (sender);

  Ipv6Address senderAddress = senderAddr.GetIpv6 ();
  uint16_t senderPort = senderAddr.GetPort ();

  // std::cout <<"Sender Address is " << senderAddress << ", " << senderAddr << std::endl;
  // std::cout <<"Node Address is " << m_routingTable.GetIpv6()->GetAddress(1,0) << std::endl;
  
  Ipv6PacketInfoTag interfaceInfo;
  if (!packet->RemovePacketTag (interfaceInfo))
    {
      NS_ABORT_MSG ("No incoming interface on RPL message, aborting...");
    }

  uint32_t incomingIf = interfaceInfo.GetRecvIf ();
  Ptr<Node> node = this->GetObject<Node> ();
  Ptr<NetDevice> dev = node->GetDevice (incomingIf);
  uint32_t ipInterfaceIndex = m_routingTable.GetIpv6 ()->GetInterfaceForDevice (dev);

  int32_t interfaceForAddress = m_routingTable.GetIpv6 ()->GetInterfaceForAddress (senderAddress);
  if (interfaceForAddress != -1)
    {
      NS_LOG_LOGIC ("Ignoring a packet sent by myself.");
      std::cout << "Got packet from myself." << std::endl;
      return;
    }

  Icmpv6Header rplMessage;
  packet->RemoveHeader (rplMessage);

  if (rplMessage.GetType () == 155)
    {
      if ( (uint32_t)rplMessage.GetCode () == 0) //DIS 
        {
          RplDisMessage disMessage;
          RplSolicitedInformationOption solicitedInformation;
          packet->RemoveHeader (disMessage);
          packet->RemoveHeader (solicitedInformation);

          RecvDis (disMessage, solicitedInformation, senderAddress, ipInterfaceIndex, senderPort);
        }
      else if ((uint32_t)rplMessage.GetCode () == 1) //DIO
        {
          RplDioMessage dioMessage;
          RplDodagConfigurationOption dodagConfiguration;
          packet->RemoveHeader (dioMessage);
          packet->RemoveHeader (dodagConfiguration);

          if (m_dioReceived == 1)
            {
              m_multicastDis.Cancel ();
              m_multicastDis = EventId ();
              m_dioReceived = 0;
            }

          RecvDio (dioMessage, dodagConfiguration, senderAddress, ipInterfaceIndex, senderPort);
        }
      else if ((uint32_t)rplMessage.GetCode () == 2) //DAO
        {
          RplDaoMessage daoMessage;
          RplTargetOption targetOption;
          RplTransitInformationOption transitInformation;

          packet->RemoveHeader (daoMessage);
          packet->RemoveHeader (targetOption);
          packet->RemoveHeader (transitInformation);

          RecvDao (daoMessage, targetOption, transitInformation);
        }
    }
  else
    {
      NS_ABORT_MSG ("Not a RPL message, aborting...");
    }  

  return;
}

void Rpl::Join ()
{
  Time delay = Seconds (1);
  m_dioReceived = 1;
  SendMulticastDis ();
}

void Rpl::RecvDis (RplDisMessage disMessage, RplSolicitedInformationOption solicitedInformation, Ipv6Address senderAddress, uint32_t incomingInterface, uint16_t senderPort)
{
  std::cout << "Recv DIS - sender" << senderAddress << "\n"; 
  if (m_routingTable.GetNodeType () == true) //Only routers can receive DIS messages
    {
      m_routingTable.AddNetworkRouteTo (senderAddress, incomingInterface, senderPort);
      SendDio(senderAddress, incomingInterface, senderPort);
      
      if(m_routingTable.GetVersionNumber () != 0)
        {
          ResetTrickle ();
        }

    }
  else
    {
      NS_ABORT_MSG ("Node Type: Leaf");
    }

  Ptr<Ipv6Route> rtentry = 0;
  rtentry = m_routingTable.Lookup (senderAddress);

  if (rtentry)
    { 
      std::cout << "Delete route: " << rtentry << "\n";
      m_routingTable.DeleteRoute (rtentry);
    }
}

void Rpl::RecvDio (RplDioMessage dioMessage, RplDodagConfigurationOption dodagConfiguration, Ipv6Address senderAddress, uint32_t incomingInterface, uint16_t senderPort)
{
  std::cout << "Received DIO from " << senderAddress <<std::endl << " Rank is " << dioMessage.GetRank() << "\n";
  
  //Not included yung poison na DIO for disjoin
  if (dioMessage.GetVersionNumber () == m_routingTable.GetVersionNumber ())
    {
      m_counter += 1;
      if (dioMessage.GetDtsn () != m_routingTable.GetDtsn ())
        {
          //Schedule DAO
        }
    }
  else
    {
      if (dioMessage.GetRank() < m_routingTable.GetRank() || m_routingTable.GetRank () == 0)
       {
        m_routingTable.ClearRoutingTable ();
        m_neighborSet.ClearNeighborSet ();
        
        m_routingTable.SetRplInstanceId (dioMessage.GetRplInstanceId ());
        m_routingTable.SetDodagId (dioMessage.GetDodagId ());
        m_routingTable.SetObjectiveCodePoint (dodagConfiguration.GetObjectiveCodePoint ());
        m_routingTable.SetDtsn (dioMessage.GetDtsn ()); 

        if (dodagConfiguration.GetObjectiveCodePoint () == 0)
          {
            uint16_t computedRank = RplObjectiveFunctionOf0::ComputeRank (dioMessage.GetRank ());
            m_routingTable.SetRank (computedRank);
          }

        //Assume all nodes are routers (no leaf nodes)

        if (m_routingTable.GetVersionNumber () != 0)
          {
            ResetTrickle ();
          }
        else
          { 
            StartTrickle ();
            m_routingTable.SetVersionNumber (dioMessage.GetVersionNumber ());
          }
        }
    }

  if (!m_neighborSet.FindNeighbor(senderAddress))
    {
      InsertNeighbor (senderAddress, dioMessage.GetDodagId (), dioMessage.GetDtsn (), dioMessage.GetRank (), incomingInterface);
      m_neighborSet.SelectParent (m_routingTable.GetRank());
      std::cout << "Parent is " << m_neighborSet.GetParent() << " : " << dioMessage.GetRank () << std::endl;

      //non storing mode
      if (m_neighborSet.GetParent () != "::" && dioMessage.GetRank () < m_routingTable.GetRank ())
        {
          m_routingTable.AddNetworkRouteTo (senderAddress, incomingInterface, senderPort);
        }
    }
  
  Time delay = Seconds (25);
  if (DAO)
    {
      m_sendDao = Simulator::Schedule (delay, &Rpl::SendDao, this);
    }

  std::cout << "This node's rank is now " << m_routingTable.GetRank() << std::endl;
}

void Rpl::SendMulticastDis ()
{
  if (m_dioReceived == 1)
    {
      Ptr<Packet> p = Create<Packet>();
      Ptr<Socket> sendingSocket;
      
      Icmpv6Header dis;
      std::cout << "Sending DIS." << std::endl;

      dis.SetType (155);
      dis.SetCode (0);

      RplDisMessage disMessage;
      RplSolicitedInformationOption solicitedInformation;

      p->AddHeader (solicitedInformation);
      p->AddHeader (disMessage);
      p->AddHeader (dis);

      SocketListI iter = m_sendSocketList.begin ();
      sendingSocket = iter->first;
      sendingSocket->SendTo(p, 0, Inet6SocketAddress (ALL_RPL_NODES, RPL_PORT));

      Time delay = Seconds (1);
      m_multicastDis = Simulator::Schedule (delay, &Rpl::SendMulticastDis, this);
    } 
}

void Rpl::SendDio (Ipv6Address destAddress, uint32_t incomingInterface, uint16_t senderPort) 
{
  if (m_routingTable.GetVersionNumber () !=0) 
    {
      Ptr<Packet> p = Create<Packet>();
      Ptr<Socket> sendingSocket;
      SocketIpv6HopLimitTag tag;
      tag.SetHopLimit (255);

      Icmpv6Header dio;
      dio.SetType (155);
      dio.SetCode (1);

      RplDioMessage dioMessage;
      dioMessage.SetFlagG (m_routingTable.GetFlagG ());
      dioMessage.SetMop (MOP);
      dioMessage.SetPrf (0);
      dioMessage.SetRplInstanceId (m_routingTable.GetRplInstanceId ());
      dioMessage.SetDtsn (m_routingTable.GetDtsn ());
      dioMessage.SetVersionNumber (m_routingTable.GetVersionNumber ());
      dioMessage.SetRank (m_routingTable.GetRank ());
      dioMessage.SetDodagId (m_routingTable.GetDodagId ());
      
      RplDodagConfigurationOption dodagConfiguration;
      dodagConfiguration.SetPathControlSize (DEFAULT_PATH_CONTROL_SIZE);
      dodagConfiguration.SetDioIntervalDoublings (DEFAULT_DIO_INTERVAL_DOUBLINGS);
      dodagConfiguration.SetDioIntervalMin (DEFAULT_DIO_INTERVAL_MIN);
      dodagConfiguration.SetDioRedundancyConstant (DEFAULT_DIO_REDUNDANCY_CONSTANT);
      dodagConfiguration.SetMaxRankIncrease (0);
      dodagConfiguration.SetMinHopRankIncrease (DEFAULT_MIN_HOP_RANK_INCREASE);
      dodagConfiguration.SetObjectiveCodePoint (OCP);
      //dodagConfiguration.SetDefaultLifetime ();
      //dodagConfiguration.SetLifetimeUnit ();
      
      p->AddHeader (dodagConfiguration);
      p->AddHeader (dioMessage);
      p->AddHeader (dio);

      if (!m_recvSocket) 
        {
          NS_LOG_LOGIC ("RPL: adding receiving socket");
          TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
          Ptr<Node> theNode = GetObject<Node> ();
          m_recvSocket = Socket::CreateSocket (theNode, tid);
          Inet6SocketAddress local = Inet6SocketAddress (ALL_RPL_NODES, RPL_PORT);
          m_recvSocket->Bind (local);
          m_recvSocket->SetRecvCallback (MakeCallback (&Rpl::Receive, this));
          m_recvSocket->SetIpv6RecvHopLimit (true);
          m_recvSocket->SetRecvPktInfo (true);
        }

      for (SocketListI iter = m_sendSocketList.begin (); iter != m_sendSocketList.end (); iter++ )
        {
          if (iter->second == incomingInterface)
            {
              sendingSocket = iter->first;
            }
          else
            {
              sendingSocket = m_recvSocket;
            }
        }

      std::cout << "Proceed to send DIO. " << std::endl;
      NS_LOG_DEBUG ("SendTo: " << *p);
      sendingSocket->SendTo (p, 0, Inet6SocketAddress (destAddress, senderPort));
    }
  else 
    {
      std::cout << "Not yet in DODAG\n";
    }
}

void Rpl::SendDio () 
{
  if (m_routingTable.GetVersionNumber () !=0) 
    {
      Ptr<Packet> p = Create<Packet>();
      Ptr<Socket> sendingSocket;
      SocketIpv6HopLimitTag tag;
      tag.SetHopLimit (255);

      Icmpv6Header dio;
      dio.SetType (155);
      dio.SetCode (1);

      RplDioMessage dioMessage;
      dioMessage.SetFlagG (m_routingTable.GetFlagG ());
      dioMessage.SetMop (MOP);
      dioMessage.SetPrf (0);
      dioMessage.SetRplInstanceId (m_routingTable.GetRplInstanceId ());
      dioMessage.SetDtsn (m_routingTable.GetDtsn ());
      dioMessage.SetVersionNumber (m_routingTable.GetVersionNumber ());
      dioMessage.SetRank (m_routingTable.GetRank ());
      dioMessage.SetDodagId (m_routingTable.GetDodagId ());
      
      RplDodagConfigurationOption dodagConfiguration;
      dodagConfiguration.SetPathControlSize (DEFAULT_PATH_CONTROL_SIZE);
      dodagConfiguration.SetDioIntervalDoublings (DEFAULT_DIO_INTERVAL_DOUBLINGS);
      dodagConfiguration.SetDioIntervalMin (DEFAULT_DIO_INTERVAL_MIN);
      dodagConfiguration.SetDioRedundancyConstant (DEFAULT_DIO_REDUNDANCY_CONSTANT);
      dodagConfiguration.SetMaxRankIncrease (0);
      dodagConfiguration.SetMinHopRankIncrease (DEFAULT_MIN_HOP_RANK_INCREASE);
      dodagConfiguration.SetObjectiveCodePoint (OCP);
      //dodagConfiguration.SetDefaultLifetime ();
      //dodagConfiguration.SetLifetimeUnit ();
      
      p->AddHeader (dodagConfiguration);
      p->AddHeader (dioMessage);
      p->AddHeader (dio);

      if (!m_recvSocket) 
        {
          NS_LOG_LOGIC ("RPL: adding receiving socket");
          TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
          Ptr<Node> theNode = GetObject<Node> ();
          m_recvSocket = Socket::CreateSocket (theNode, tid);
          Inet6SocketAddress local = Inet6SocketAddress (ALL_RPL_NODES, RPL_PORT);
          m_recvSocket->Bind (local);
          m_recvSocket->SetRecvCallback (MakeCallback (&Rpl::Receive, this));
          m_recvSocket->SetIpv6RecvHopLimit (true);
          m_recvSocket->SetRecvPktInfo (true);
        }

      SocketListI iter = m_sendSocketList.begin ();
      sendingSocket = iter->first;

      NS_LOG_DEBUG ("SendTo: " << *p);

      sendingSocket->SendTo (p, 0, Inet6SocketAddress (ALL_RPL_NODES, RPL_PORT));
    }
  else 
    {
      std::cout << "Not yet in DODAG\n";
    }
}

void Rpl::SendDao ()
{
  std::cout << "Sending DAO\n";
  Ptr<Packet> p = Create<Packet>();
  Ptr<Socket> sendingSocket;

  RplDaoMessage daoMessage;
  RplTargetOption targetOption;
  RplTransitInformationOption transitInformation;

  Icmpv6Header dao;
  dao.SetType (155);
  dao.SetCode (2);

  daoMessage.SetRplInstanceId (m_routingTable.GetRplInstanceId ());
  daoMessage.SetDodagId (m_routingTable.GetDodagId ());

  Ipv6InterfaceAddress address = m_routingTable.GetIpv6()->GetAddress(1,0);
  Ipv6Prefix networkMask = address.GetPrefix ();
  Ipv6Address networkAddress = address.GetAddress ();

  if (!m_recvSocket)
    {
      NS_LOG_LOGIC ("RPL: adding receiving socket");
      TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
      Ptr<Node> theNode = GetObject<Node> ();
      m_recvSocket = Socket::CreateSocket (theNode, tid);
      Inet6SocketAddress local = Inet6SocketAddress (ALL_RPL_NODES, RPL_PORT);
      m_recvSocket->Bind (local);
      m_recvSocket->SetRecvCallback (MakeCallback (&Rpl::Receive, this));
      m_recvSocket->SetIpv6RecvHopLimit (true);
      m_recvSocket->SetRecvPktInfo (true);
    }

  for (SocketListI iter = m_sendSocketList.begin (); iter != m_sendSocketList.end (); iter++ )
    {
      if (iter->second == 1)
        {
          sendingSocket = iter->first;
        }
      else
        {
          sendingSocket = m_recvSocket;
        }
    }

  if (MOP == 1) //Non-storing mode
    {
      std::cout << "Non storing DAO\n";
      targetOption.SetPrefixLength (networkMask.GetPrefixLength ());
      targetOption.SetTargetPrefix (networkAddress);

      // transitInformation.SetPathControl ();
      // transitInformation.SetPathLifetime ();
      transitInformation.SetPathSequence (1);
      transitInformation.SetParentAddress (m_neighborSet.GetParent ());

      p->AddHeader (transitInformation);
      p->AddHeader (targetOption);
      p->AddHeader (daoMessage);
      p->AddHeader (dao);

      sendingSocket->SendTo (p, 0, Inet6SocketAddress (m_neighborSet.GetParent (), 521));
    }
  else if (MOP == 3) //Storing with multicast
    {

    }
  else
    {
      std::cout << "Downward route not supported\n";
    }

}

void Rpl::RecvDao (RplDaoMessage daoMessage, RplTargetOption targetOption, RplTransitInformationOption transitInformation)
{
  std::cout << "Receive DAO\n";
  Ptr<Packet> p = Create<Packet>();
  Ptr<Socket> sendingSocket;

  Icmpv6Header dao;
  dao.SetType (155);
  dao.SetCode (2);

  Ipv6InterfaceAddress address = m_routingTable.GetIpv6()->GetAddress(1,0);
  Ipv6Prefix networkMask = address.GetPrefix ();
  Ipv6Address networkAddress = address.GetAddress ();

  if (!m_recvSocket)
    {
      NS_LOG_LOGIC ("RPL: adding receiving socket");
      TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
      Ptr<Node> theNode = GetObject<Node> ();
      m_recvSocket = Socket::CreateSocket (theNode, tid);
      Inet6SocketAddress local = Inet6SocketAddress (ALL_RPL_NODES, RPL_PORT);
      m_recvSocket->Bind (local);
      m_recvSocket->SetRecvCallback (MakeCallback (&Rpl::Receive, this));
      m_recvSocket->SetIpv6RecvHopLimit (true);
      m_recvSocket->SetRecvPktInfo (true);
    }

  for (SocketListI iter = m_sendSocketList.begin (); iter != m_sendSocketList.end (); iter++ )
    {
      if (iter->second == 1)
        {
          sendingSocket = iter->first;
        }
      else
        {
          sendingSocket = m_recvSocket;
        }
    }

  if (MOP == 1)
    {
      if (m_neighborSet.GetParent () == "::")
        {
          std::cout << "DAO - now in root node\n";

          if ((uint32_t)daoMessage.GetRplInstanceId () == (uint32_t)m_routingTable.GetRplInstanceId () && daoMessage.GetDodagId () == m_routingTable.GetDodagId ())
            {
              Ipv6Address dest = targetOption.GetTargetPrefix ();

              Ptr<Ipv6Route> rtentry = 0;
              rtentry = m_routingTable.Lookup (dest);

              if (!rtentry)
                { 
                  m_routingTable.AddNetworkRouteTo (dest, 1, transitInformation.GetParentAddress (), dest); 
                }              
            }
          else
            {
              std::cout << "Not in the same DODAG\n";
            }
        }
      else
        {
          p->AddHeader (transitInformation);
          p->AddHeader (targetOption);
          p->AddHeader (daoMessage);
          p->AddHeader (dao);

          sendingSocket->SendTo (p, 0, Inet6SocketAddress (m_neighborSet.GetParent (), 521));
        }
    }
  else if (MOP == 3)
    { 

    }
  else
    {
      std::cout << "Downward route not supported\n";
    }
}

void Rpl::InsertNeighbor (Ipv6Address neighborAddress, Ipv6Address dodagID, uint8_t dtsn, uint16_t rank, 
                          uint32_t incomingInterface)
{
  Neighbor neighbor;
  neighbor.SetNeighborAddress (neighborAddress);
  neighbor.SetDodagId (dodagID);
  neighbor.SetDtsn (dtsn);
  neighbor.SetRank (rank);
  neighbor.SetInterface (incomingInterface);
  neighbor.SetReachable(true);      

  std::cout << "Inserting Neighbor: " << neighbor.GetNeighborAddress ()
  << neighbor.GetRank ()
  << neighbor.GetReachable()      
  << std::endl;

  m_neighborSet.AddNeighbor(neighbor);
}

void Rpl::InsertNeighbor (neighborType type)
{
  Neighbor neighbor;
  neighbor.SetNeighborType (type);

  m_neighborSet.AddNeighbor(neighbor);
}

void Rpl::ResetTrickle ()
{
  if (m_interval != m_iMin.GetMilliSeconds ())
    {     
      if (m_dioSchedule.IsRunning ())
        {
          m_dioSchedule.Cancel ();
        }

      if (m_restartInterval.IsRunning ())
        {
          m_restartInterval.Cancel ();
        }

      m_interval = MilliSeconds(m_iMin.GetMilliSeconds ());
      m_counter = 0;
      m_t = MilliSeconds (m_rng->GetValue (((m_interval.GetMilliSeconds ())/2), m_interval.GetMilliSeconds ()));
      
      std::cout << "----------ResetTrickle-----------\n";    
      if(trickle)
        { 
          m_dioSchedule = Simulator::Schedule (m_t, &Rpl::TrickleTransmit, this);
          m_restartInterval = Simulator::Schedule (m_interval, &Rpl::RestartInterval, this);
        }
    }

}

void Rpl::StartTrickle ()
{
  m_interval = MilliSeconds (m_rng->GetValue (m_iMin.GetMilliSeconds (), m_iMax.GetMilliSeconds ()) );
  m_counter = 0;
  m_t = MilliSeconds (m_rng->GetValue (((m_interval.GetMilliSeconds ())/2), m_interval.GetMilliSeconds ()));
  
  std::cout << "-----------StartTrickle-----------\n";
  if(trickle) 
    {
      m_dioSchedule = Simulator::Schedule (m_t, &Rpl::TrickleTransmit, this);
      m_restartInterval = Simulator::Schedule (m_interval, &Rpl::RestartInterval, this);
    }
}

void Rpl::RestartInterval ()
{
  if (m_dioSchedule.IsRunning ())
    {
      m_dioSchedule.Cancel ();
    }

  if (m_restartInterval.IsRunning ())
    {
      m_restartInterval.Cancel ();
    }

  if ((m_interval*2) > m_iMax)
    { 
      m_interval = MilliSeconds(m_iMax.GetMilliSeconds ());
    }
  else
    { 
      m_interval = 2*MilliSeconds(m_interval.GetMilliSeconds ());
    }

  m_counter = 0;
  m_t = MilliSeconds (m_rng->GetValue (((m_interval.GetMilliSeconds ())/2), m_interval.GetMilliSeconds ()));

  std::cout << "-----------RestartInterval-----------\n";
  if(trickle)
    {
      m_dioSchedule = Simulator::Schedule (m_t, &Rpl::TrickleTransmit, this);
      m_restartInterval = Simulator::Schedule (m_interval, &Rpl::RestartInterval, this);
    }
}

void Rpl::TrickleTransmit ()
{
  std::cout << "-----------TrickleTransmit-----------\n";
  if (m_counter < DEFAULT_DIO_REDUNDANCY_CONSTANT || DEFAULT_DIO_REDUNDANCY_CONSTANT == 0)
    {
      SendDio();
    }
}

void Rpl::DoDispose ()
{
  NS_LOG_FUNCTION (this);

  std::cout << "----------------------\n\n";

  m_routingTable.PrintRoutingTable ();
  m_routingTable.ClearRoutingTable ();

  for (SocketListI iter = m_sendSocketList.begin (); iter != m_sendSocketList.end (); iter++ )
    {
      iter->first->Close ();
    }

  m_sendSocketList.clear ();

  m_recvSocket->Close ();
  m_recvSocket = 0;

  m_routingTable.SetIpv6 (0);

  Ipv6RoutingProtocol::DoDispose ();
}

void Rpl::NotifyInterfaceUp (uint32_t i)
{
  std::cout << "Enters Interface Up." << std::endl;
  NS_LOG_FUNCTION (this << i);

  for (uint32_t j = 0; j < m_routingTable.GetIpv6()->GetNAddresses (i); j++)
    {
      Ipv6InterfaceAddress address = m_routingTable.GetIpv6()->GetAddress (i, j);
      Ipv6Prefix networkMask = address.GetPrefix ();
      Ipv6Address networkAddress = address.GetAddress ();
      std::cout << "Address #" << j << ": " << networkAddress << " Mask: " <<networkMask << std::endl;

      if (address.GetScope () == Ipv6InterfaceAddress::GLOBAL)
        {
          m_routingTable.AddNetworkRouteTo (networkAddress, i);
        }   
    }
  return;
}

void Rpl::NotifyInterfaceDown (uint32_t interface)
{
  std::cout <<"Interface down." << std::endl;
}

void Rpl::NotifyAddAddress (uint32_t interface, Ipv6InterfaceAddress address)
{
  std::cout << "Enters Notify Add." << std::endl;
  std::cout << "Address is: " << address << std::endl;
  NS_LOG_FUNCTION (this << interface << address);
  if (!m_routingTable.GetIpv6()->IsUp (interface))
    {
      return;
    }

  Ipv6Address networkAddress = address.GetAddress ().CombinePrefix (address.GetPrefix ());
  Ipv6Prefix networkMask = address.GetPrefix ();

  if (address.GetScope () == Ipv6InterfaceAddress::GLOBAL)
    {
      m_routingTable.AddNetworkRouteTo (networkAddress, interface);
    }
  std::cout << "Address added: " << networkAddress << std::endl;

}

void Rpl::NotifyRemoveAddress (uint32_t interface, Ipv6InterfaceAddress address)
{
  std::cout <<"Remove address." << std::endl;
}

void Rpl::NotifyAddRoute (Ipv6Address dst, Ipv6Prefix mask, Ipv6Address nextHop, uint32_t interface, Ipv6Address prefixToUse)
{
  std::cout << "Enters Notify Add Route." << std::endl;
  std::cout << dst << std::endl;
}

void Rpl::NotifyRemoveRoute (Ipv6Address dst, Ipv6Prefix mask, Ipv6Address nextHop, uint32_t interface, Ipv6Address prefixToUse)
{
  
}

void Rpl::SetIpv6 (Ptr<Ipv6> ipv6)
{
  NS_LOG_FUNCTION (this << ipv6);

  NS_ASSERT (m_routingTable.GetIpv6 () == 0 && ipv6 != 0);
  uint32_t i = 0;
  m_routingTable.SetIpv6 (ipv6);

  if(!m_routingTable.GetIpv6 ())
    {
      std::cout << "Marker\n";
    }

  for (i = 0; i < m_routingTable.GetIpv6 ()->GetNInterfaces (); i++)
    {
      if (m_routingTable.GetIpv6 ()->IsUp (i))
        {
          NotifyInterfaceUp (i);
        }
      else
        {
          NotifyInterfaceDown (i);
        }
    }
}

void Rpl::PrintRoutingTable (Ptr<OutputStreamWrapper> stream) const
{
  std::cout << "Printing Routing Table\n";
}


}