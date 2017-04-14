/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

// Include a header file from your module to test.
#include "ns3/rpl.h"
#include "ns3/rpl-header.h"
#include "ns3/rpl-objective-function.h"
#include "ns3/rpl-routing-table.h"
#include "ns3/rpl-neighbor.h"
#include "ns3/rpl-neighborset.h"
#include "ns3/csma-module.h"

// An essential include is test.h
#include "ns3/test.h"
#include "ns3/socket-factory.h"
#include "ns3/udp-socket-factory.h"
#include "ns3/simulator.h"
#include "ns3/simple-channel.h"
#include "ns3/simple-net-device.h"
#include "ns3/drop-tail-queue.h"
#include "ns3/socket.h"
#include "ns3/boolean.h"
#include "ns3/enum.h"
#include "ns3/log.h"
#include "ns3/node.h"

#include "ns3/inet6-socket-address.h"
#include "ns3/ipv6.h"
#include "ns3/ipv6-routing-protocol.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/ipv6-address-helper.h"
#include "ns3/ipv6-l3-protocol.h"
#include "ns3/icmpv6-l4-protocol.h"
#include "ns3/udp-l4-protocol.h"
#include "ns3/rpl-helper.h"
#include "ns3/node-container.h"
#include "ns3/ipv6-route.h"
#include "ns3/ipv6-address.h"
#include "ns3/ipv6-header.h"
#include "ns3/ipv6.h"

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/config-store-module.h"
#include "ns3/wifi-module.h"
#include "ns3/internet-module.h"
#include "ns3/ipv6-static-routing-helper.h"
#include "ns3/ipv6-routing-table-entry.h"
#include "ns3/rpl-module.h"
#include "ns3/internet-apps-module.h"

#include <fstream>
#include <vector>

#include <stdint.h>
#include <iostream>
#include <string>
#include <limits>

// Do not put your test classes in namespace ns3.  You may find it useful
// to use the using directive to access the ns3 namespace directly
using namespace ns3;
// This is an example TestCase.
class RplTestCase1 : public TestCase
{
public:
  RplTestCase1 ();
  virtual ~RplTestCase1 ();

private:
  virtual void DoRun (void);
};

// Add some help text to this case to describe what it is intended to test
RplTestCase1::RplTestCase1 ()
  : TestCase ("Rpl test case (does nothing)")
{
}

// This destructor does nothing but we include it as a reminder that
// the test case should clean up after itself
RplTestCase1::~RplTestCase1 ()
{
}

//
// This method is the pure virtual method from class TestCase that every
// TestCase must implement
//
void
RplTestCase1::DoRun (void)
{
  // A wide variety of test macros are available in src/core/test.h
  NS_TEST_ASSERT_MSG_EQ (true, true, "true doesn't equal true for some reason");
  // Use this one for floating point comparisons
  NS_TEST_ASSERT_MSG_EQ_TOL (0.01, 0.01, 0.001, "Numbers are not equal within tolerance");
}

struct TypeHeaderTest : public TestCase
{
  TypeHeaderTest () : TestCase ("RPL Header Tests") 
  {
  }
  virtual void DoRun ()
  {
    Icmpv6Header h;
    h.SetType(155);
    NS_TEST_EXPECT_MSG_EQ (h.GetType (), 155, "RPL Header Type");

    RplDisMessage dis;
    NS_TEST_EXPECT_MSG_EQ (dis.GetCode (), 0, "RPL DIS Header Code");
    RplDioMessage dio;
    NS_TEST_EXPECT_MSG_EQ (dio.GetCode (), 1, "RPL DIO Header Code");
    RplDaoMessage dao;
    NS_TEST_EXPECT_MSG_EQ (dao.GetCode (), 2, "RPL DAO Header Code");

    Ptr<Packet> p = Create<Packet> ();
    p->AddHeader (h);
    Icmpv6Header h2;
    h2.SetType(155);
//    NS_TEST_EXPECT_MSG_EQ (h, h2, "Round trip serialization works");
  }
};

struct DioHeaderTest : public TestCase
{
  DioHeaderTest () : TestCase ("RPL Dio Header Tests") 
  {
  }
  virtual void DoRun ()
  {
    RplDioMessage dio;
    NS_TEST_EXPECT_MSG_EQ (dio.GetCode (), 1, "RPL DIO Header Code");

    Ptr<Packet> p = Create<Packet> ();
    p->AddHeader (dio);
    RplDioMessage dio2;
    p->RemoveHeader (dio2);
    NS_TEST_EXPECT_MSG_EQ (dio2.GetCode (), 1, "RPL DIO Header Code");
  }
};

struct DisHeaderTest : public TestCase
{
  DisHeaderTest () : TestCase ("RPL Dis Header Tests") 
  {
  }
  virtual void DoRun ()
  {
    RplDisMessage dis;
    NS_TEST_EXPECT_MSG_EQ (dis.GetCode (), 0, "RPL DIS Header Code");

    Ptr<Packet> p = Create<Packet> ();
    p->AddHeader (dis);
    RplDisMessage dis2;
    p->RemoveHeader (dis2);
    NS_TEST_EXPECT_MSG_EQ (dis2.GetCode (), 0, "RPL DIS Header Code");
  }
};

struct DaoHeaderTest : public TestCase
{
  DaoHeaderTest () : TestCase ("RPL Dao Header Tests") 
  {
  }
  virtual void DoRun ()
  {
    RplDaoMessage dao;
    NS_TEST_EXPECT_MSG_EQ (dao.GetCode (), 2, "RPL DAO Header Code");
    dao.SetDodagId("ff02::1a");
    NS_TEST_EXPECT_MSG_EQ (dao.GetDodagId (), "ff02::1a", "RPL DAO Header Code");

    Ptr<Packet> p = Create<Packet> ();
    p->AddHeader (dao);
    RplDaoMessage dao2;
    p->RemoveHeader (dao2);
    NS_TEST_EXPECT_MSG_EQ (dao2.GetCode (), 2, "RPL DAO Header Code");
  }
};

struct RplDodagConfigurationOptionTest : public TestCase
{
  RplDodagConfigurationOptionTest () : TestCase ("Rpl Dodag Configuration Option Tests") 
  {
  }
  virtual void DoRun ()
  {
    RplDodagConfigurationOption h;
    NS_TEST_EXPECT_MSG_EQ (h.GetLength (), 14, "Option Length");

    Ptr<Packet> p = Create<Packet> ();
    p->AddHeader (h);
    RplDodagConfigurationOption h2;
    p->RemoveHeader (h2);
    NS_TEST_EXPECT_MSG_EQ (h2.GetType (), 4, "Option Type Test");
    NS_TEST_EXPECT_MSG_EQ (h2.GetLifetimeUnit (), 0, "Option Type Test");
  }
};

struct RplSolicitedInformationOptionTest : public TestCase
{
  RplSolicitedInformationOptionTest () : TestCase ("Rpl Solicited Information Option Tests") 
  {
  }
  virtual void DoRun ()
  {
    RplSolicitedInformationOption h;
    NS_TEST_EXPECT_MSG_EQ (h.GetLength (), 19, "Option Length");

    Ptr<Packet> p = Create<Packet> ();
    p->AddHeader (h);
    RplSolicitedInformationOption h2;
    p->RemoveHeader (h2);
    NS_TEST_EXPECT_MSG_EQ (h2.GetType (), 7, "Option Type Test");
  }
};

struct RplObjectiveFunction0Test : public TestCase
{
  RplObjectiveFunction0Test () : TestCase ("Objective Function 0 Test")
  {
  }
  virtual void DoRun ()
  {
    NS_TEST_EXPECT_MSG_EQ (RplObjectiveFunctionOf0::ComputeRank (1), 769, "Computed Rank Test");
  }
};

struct RplRoutingTableEntryTest : public TestCase
{
  RplRoutingTableEntryTest () : TestCase ("Rpl Routing Table Entry")
  {
  }
  virtual void DoRun ()
  {
    Ipv6Address dodagParent;
    uint32_t interface = 1;

    RplRoutingTableEntry routingTableEntry (dodagParent, interface);
    NS_TEST_EXPECT_MSG_EQ (routingTableEntry.GetDodagParent (), dodagParent, "Dodag Parent");
    NS_TEST_EXPECT_MSG_EQ (routingTableEntry.GetInterface (), interface, "Interface");

    Ipv6Address daoSender;
    Ipv6Address nextHop;
    Ipv6Address dest;
    Ipv6Prefix destPrefix;

    RplRoutingTableEntry routingTableEntry1 (daoSender, interface, nextHop, dest, destPrefix);
    NS_TEST_EXPECT_MSG_EQ (routingTableEntry1.GetDaoSender (), daoSender, "Dao Sender");
    NS_TEST_EXPECT_MSG_EQ (routingTableEntry1.GetInterface (), interface, "Interface");
    NS_TEST_EXPECT_MSG_EQ (routingTableEntry1.GetNextHop (), nextHop, "Next Hop");
    NS_TEST_EXPECT_MSG_EQ (routingTableEntry1.GetDest (), dest, "Destination");
    NS_TEST_EXPECT_MSG_EQ (routingTableEntry1.GetDestNetworkPrefix (), destPrefix, "Destination Prefix");
  }
};

struct RplRoutingTableTest : public TestCase
{
  RplRoutingTableTest () : TestCase ("Rpl Routing Table")
  {
  }
  virtual void DoRun ()
  {
    RplRoutingTable routingTable;

    Ptr<Ipv6> ipv6;
    routingTable.GetIpv6 () = ipv6;
    NS_TEST_EXPECT_MSG_EQ (routingTable.GetIpv6 (), ipv6, "m_ipv6");

    Ipv6Address dodagParent;
    uint32_t interface = 1;
    NS_TEST_EXPECT_MSG_EQ (routingTable.AddNetworkRouteTo (dodagParent, interface), true, "Add Network");

    // Ptr<Ipv6Route> rtentry = 0;
    // rtentry = routingTable.Lookup(dodagParent);
    // Ipv6Address address = rtentry->GetDestination ();
    // NS_TEST_EXPECT_MSG_EQ (address, dodagParent, "Check parent");

    Ipv6Address daoSender;
    Ipv6Address nextHop;
    Ipv6Address dest;
    Ipv6Prefix destPrefix;
    NS_TEST_EXPECT_MSG_EQ (routingTable.AddNetworkRouteTo (daoSender, interface, nextHop, dest, destPrefix), true, "Add Network");

    NS_TEST_EXPECT_MSG_EQ (routingTable.ClearRoutingTable (), true, "Clear Routing Table");
  }
};

struct RplNeighborTest : public TestCase
{
  RplNeighborTest () : TestCase ("Rpl Neighbor Test")
  {
  }
  virtual void DoRun ()
  {
    Neighbor neighbor;
    neighbor.SetNeighborAddress ("2001:1::db8");
    neighbor.SetDodagId ("2001:1::db8");
    neighbor.SetDtsn (1);
    neighbor.SetRank (256);
    neighbor.SetInterface (1);
    
    neighbor.SetNeighborType (subDodag);
    NS_TEST_EXPECT_MSG_EQ (neighbor.GetNeighborType (), 1, "Neighbor Type");
    
    neighbor.SetReachable (true);

  }
};

struct RplNeighborSetTest : public TestCase
{
  RplNeighborSetTest () : TestCase ("Rpl Neighbor Set Test")
  {
  }
  virtual void DoRun ()
  {

  }
};

struct MultipleRootTest : public TestCase
{
  MultipleRootTest () : TestCase ("Multiple Root Test")
  {
  }
  virtual void DoRun ()
  {
  std::string phyMode ("DsssRate1Mbps");
//  double rss = -80;  // -dBm
//  uint32_t packetSize = 1000; // bytes
//  uint32_t numPackets = 1;
  double interval = 1.0; // seconds

  Time interPacketInterval = Seconds (interval);

  // disable fragmentation for frames below 2200 bytes
  Config::SetDefault ("ns3::WifiRemoteStationManager::FragmentationThreshold", StringValue ("2200"));
  // turn off RTS/CTS for frames below 2200 bytes
  Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold", StringValue ("2200"));
  // Fix non-unicast data rate to be the same as that of unicast
  Config::SetDefault ("ns3::WifiRemoteStationManager::NonUnicastMode", 
                      StringValue (phyMode));

  NodeContainer c;
  c.Create (4);

  // The below set of helpers will help us to put together the wifi NICs we want
  WifiHelper wifi;
  wifi.SetStandard (WIFI_PHY_STANDARD_80211b);

  YansWifiPhyHelper wifiPhy =  YansWifiPhyHelper::Default ();
  // This is one parameter that matters when using FixedRssLossModel
  // set it to zero; otherwise, gain will be added
  wifiPhy.Set ("RxGain", DoubleValue (0) ); 
  // ns-3 supports RadioTap and Prism tracing extensions for 802.11b
  wifiPhy.SetPcapDataLinkType (YansWifiPhyHelper::DLT_IEEE802_11_RADIO); 

  YansWifiChannelHelper wifiChannel;
  wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
  // The below FixedRssLossModel will cause the rss to be fixed regardless
  // of the distance between the two stations, and the transmit power
  wifiChannel.AddPropagationLoss ("ns3::FriisPropagationLossModel");
  wifiPhy.SetChannel (wifiChannel.Create ());

  // Add a mac and disable rate control
  WifiMacHelper wifiMac;
  wifi.SetStandard (WIFI_PHY_STANDARD_80211b);
  wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
                                "DataMode",StringValue (phyMode),
                                "ControlMode",StringValue (phyMode));
  // Set it to adhoc mode
  wifiMac.SetType ("ns3::AdhocWifiMac");
  NetDeviceContainer devices = wifi.Install (wifiPhy, wifiMac, c);

  // Note that with FixedRssLossModel, the positions below are not 
  // used for received signal strength. 
  MobilityHelper mobility;
  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
  positionAlloc->Add (Vector (120.0, 50.0, 0.0));
  positionAlloc->Add (Vector (140.0, 50.0, 0.0));
  positionAlloc->Add (Vector (120.0, 50.0, 1500.0));
  positionAlloc->Add (Vector (140.0, 50.0, 1500.0));
  mobility.SetPositionAllocator (positionAlloc);
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (c);

  RplHelper RplRouting;
  InternetStackHelper internetv6routers;
  internetv6routers.SetIpv4StackInstall (false);
  internetv6routers.SetRoutingHelper (RplRouting);
  internetv6routers.Install (c);

  Ipv6AddressHelper ipv6;
  ipv6.SetBase (Ipv6Address ("2001:1::"), Ipv6Prefix (64));
  Ipv6InterfaceContainer iic1 = ipv6.Assign (devices);
  iic1.SetForwarding (0, true);


  // Tracing
//  wifiPhy.EnablePcap ("rpl-adhoc-line", devices);

  Simulator::Stop (Seconds (10));
  Simulator::Run ();
  Simulator::Destroy ();


  }
};


struct RplTest : public TestCase
{
  RplTest () : TestCase ("Rpl Test") 
  {
  }
  virtual void DoRun ()
  {
    Ptr<Node> txNode = CreateObject<Node> ();
    Ptr<Node> rxNode = CreateObject<Node> ();

    NodeContainer nodes (txNode, rxNode);
    NodeContainer all (nodes);

    CsmaHelper csma;
    csma.SetChannelAttribute ("DataRate", DataRateValue (5000000));
    csma.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (2)));
    NetDeviceContainer ndc = csma.Install (nodes);

    RplHelper RplRouting;
    InternetStackHelper internetv6routers;
    internetv6routers.SetIpv4StackInstall (false);
    internetv6routers.SetRoutingHelper (RplRouting);
    internetv6routers.Install (nodes);

    Ipv6AddressHelper ipv6;
    ipv6.SetBase (Ipv6Address ("2001:1::"), Ipv6Prefix (64));
    Ipv6InterfaceContainer iic1 = ipv6.Assign (ndc);
    iic1.SetForwarding (0, true);
//    iic1.SetDefaultRouteInAllNodes (0);

    Simulator::Stop (Seconds (30));
    Simulator::Run ();
    Simulator::Destroy ();
  }
};

/*
class RplTest : public TestCase
{
  Ptr<Packet> m_receivedPacket;
  void DoSendData (Ptr<Socket> socket, std::string to);
  void SendData (Ptr<Socket> socket, std::string to);

public:
  virtual void DoRun (void);
  RplTest ();

  void ReceivePkt (Ptr<Socket> socket);
};


RplTest::RplTest ()
  : TestCase ("Rpl")
{
}

void RplTest::ReceivePkt (Ptr<Socket> socket)
{
  uint32_t availableData;
  availableData = socket->GetRxAvailable ();
  m_receivedPacket = socket->Recv (std::numeric_limits<uint32_t>::max (), 0);
  NS_ASSERT (availableData == m_receivedPacket->GetSize ());
  //cast availableData to void, to suppress 'availableData' set but not used
  //compiler warning
  (void) availableData;
}

void
RplTest::DoSendData (Ptr<Socket> socket, std::string to)
{
  Address realTo = Inet6SocketAddress (Ipv6Address (to.c_str ()), 1234);
  NS_TEST_EXPECT_MSG_EQ (socket->SendTo (Create<Packet> (123), 0, realTo),
                         123, "100");
}

void
RplTest::SendData (Ptr<Socket> socket, std::string to)
{
  m_receivedPacket = Create<Packet> ();
  Simulator::ScheduleWithContext (socket->GetNode ()->GetId (), Seconds (60),
                                  &RplTest::DoSendData, this, socket, to);
  Simulator::Stop (Seconds (66));
  Simulator::Run ();
}

void
RplTest::DoRun (void)
{
  // Create topology

  Ptr<Node> txNode = CreateObject<Node> ();
  Ptr<Node> rxNode = CreateObject<Node> ();
  Ptr<Node> routerA = CreateObject<Node> ();
  Ptr<Node> routerB = CreateObject<Node> ();
  Ptr<Node> routerC = CreateObject<Node> ();

  NodeContainer nodes (txNode, rxNode);
  NodeContainer routers (routerA, routerB, routerC);
  NodeContainer all (nodes, routers);

  RplHelper RplRouting;
  InternetStackHelper internetv6routers;
  internetv6routers.SetRoutingHelper (RplRouting);
  internetv6routers.Install (routers);

  InternetStackHelper internetv6nodes;
  internetv6nodes.Install (nodes);

  NetDeviceContainer net1;
  NetDeviceContainer net2;
  NetDeviceContainer net3;
  NetDeviceContainer net4;

  // Sender Node
  Ptr<SimpleNetDevice> txDev;
  {
    txDev = CreateObject<SimpleNetDevice> ();
    txDev->SetAddress (Mac48Address ("00:00:00:00:00:01"));
    txNode->AddDevice (txDev);
  }
  net1.Add (txDev);

  // Router A
  Ptr<SimpleNetDevice> fwDev1routerA, fwDev2routerA;
  { // first interface
    fwDev1routerA = CreateObject<SimpleNetDevice> ();
    fwDev1routerA->SetAddress (Mac48Address ("00:00:00:00:00:02"));
    routerA->AddDevice (fwDev1routerA);
  }
  net1.Add (fwDev1routerA);

  { // second interface
    fwDev2routerA = CreateObject<SimpleNetDevice> ();
    fwDev2routerA->SetAddress (Mac48Address ("00:00:00:00:00:03"));
    routerA->AddDevice (fwDev2routerA);
  }
  net2.Add (fwDev2routerA);

  // Router B
  Ptr<SimpleNetDevice> fwDev1routerB, fwDev2routerB;
  { // first interface
    fwDev1routerB = CreateObject<SimpleNetDevice> ();
    fwDev1routerB->SetAddress (Mac48Address ("00:00:00:00:00:04"));
    routerB->AddDevice (fwDev1routerB);
  }
  net2.Add (fwDev1routerB);

  { // second interface
    fwDev2routerB = CreateObject<SimpleNetDevice> ();
    fwDev2routerB->SetAddress (Mac48Address ("00:00:00:00:00:05"));
    routerB->AddDevice (fwDev2routerB);
  }
  net3.Add (fwDev2routerB);

  // Router C
  Ptr<SimpleNetDevice> fwDev1routerC, fwDev2routerC;
  { // first interface
    fwDev1routerC = CreateObject<SimpleNetDevice> ();
    fwDev1routerC->SetAddress (Mac48Address ("00:00:00:00:00:06"));
    routerC->AddDevice (fwDev1routerC);
  }
  net3.Add (fwDev1routerC);

  { // second interface
    fwDev2routerC = CreateObject<SimpleNetDevice> ();
    fwDev2routerC->SetAddress (Mac48Address ("00:00:00:00:00:07"));
    routerC->AddDevice (fwDev2routerC);
  }
  net4.Add (fwDev2routerC);

  // Rx node
  Ptr<SimpleNetDevice> rxDev;
  { // first interface
    rxDev = CreateObject<SimpleNetDevice> ();
    rxDev->SetAddress (Mac48Address ("00:00:00:00:00:08"));
    rxNode->AddDevice (rxDev);
  }
  net4.Add (rxDev);

  // link the channels
  Ptr<SimpleChannel> channel1 = CreateObject<SimpleChannel> ();
  txDev->SetChannel (channel1);
  fwDev1routerA->SetChannel (channel1);

  Ptr<SimpleChannel> channel2 = CreateObject<SimpleChannel> ();
  fwDev2routerA->SetChannel (channel2);
  fwDev1routerB->SetChannel (channel2);

  Ptr<SimpleChannel> channel3 = CreateObject<SimpleChannel> ();
  fwDev2routerB->SetChannel (channel3);
  fwDev1routerC->SetChannel (channel3);

  Ptr<SimpleChannel> channel4 = CreateObject<SimpleChannel> ();
  fwDev2routerC->SetChannel (channel4);
  rxDev->SetChannel (channel4);

  // Setup IPv6 addresses and forwarding
  Ipv6AddressHelper ipv6;

  ipv6.SetBase (Ipv6Address ("2001:1::"), Ipv6Prefix (64));
  Ipv6InterfaceContainer iic1 = ipv6.Assign (net1);
  iic1.SetForwarding (1, true);
  iic1.SetDefaultRouteInAllNodes (1);

  Ipv6InterfaceContainer iic2 = ipv6.AssignWithoutAddress (net2);
  iic2.SetForwarding (0, true);
  iic2.SetForwarding (1, true);

  Ipv6InterfaceContainer iic3 = ipv6.AssignWithoutAddress (net3);
  iic3.SetForwarding (0, true);
  iic3.SetForwarding (1, true);

  ipv6.SetBase (Ipv6Address ("2001:2::"), Ipv6Prefix (64));
  Ipv6InterfaceContainer iic4 = ipv6.Assign (net4);
  iic4.SetForwarding (0, true);
  iic4.SetDefaultRouteInAllNodes (0);

  // Create the UDP sockets
  Ptr<SocketFactory> rxSocketFactory = rxNode->GetObject<UdpSocketFactory> ();
  Ptr<Socket> rxSocket = rxSocketFactory->CreateSocket ();
  NS_TEST_EXPECT_MSG_EQ (rxSocket->Bind (Inet6SocketAddress (Ipv6Address ("2001:2::200:ff:fe00:8"), 1234)), 0, "trivial");
  rxSocket->SetRecvCallback (MakeCallback (&RplTest::ReceivePkt, this));

  Ptr<SocketFactory> txSocketFactory = txNode->GetObject<UdpSocketFactory> ();
  Ptr<Socket> txSocket = txSocketFactory->CreateSocket ();
  txSocket->SetAllowBroadcast (true);

  // ------ Now the tests ------------

  // Unicast test
  SendData (txSocket, "2001:2::200:ff:fe00:8");
  NS_TEST_EXPECT_MSG_EQ (m_receivedPacket->GetSize (), 123, "IPv6 Rpl should work.");

  m_receivedPacket->RemoveAllByteTags ();

  Simulator::Destroy ();
}*/

// The TestSuite class names the TestSuite, identifies what type of TestSuite,
// and enables the TestCases to be run.  Typically, only the constructor for
// this class must be defined
//
class RplTestSuite : public TestSuite
{
public:
  RplTestSuite ();
};

RplTestSuite::RplTestSuite ()
  : TestSuite ("rpl", UNIT)
{
  // TestDuration for TestCase can be QUICK, EXTENSIVE or TAKES_FOREVER
  AddTestCase (new RplTestCase1, TestCase::QUICK);
  AddTestCase (new TypeHeaderTest, TestCase::QUICK);
  AddTestCase (new DioHeaderTest, TestCase::QUICK);
  AddTestCase (new DisHeaderTest, TestCase::QUICK);
  AddTestCase (new DaoHeaderTest, TestCase::QUICK);
  AddTestCase (new RplDodagConfigurationOptionTest, TestCase::QUICK);
  AddTestCase (new RplSolicitedInformationOptionTest, TestCase::QUICK);
  AddTestCase (new RplObjectiveFunction0Test, TestCase::QUICK);
  AddTestCase (new RplRoutingTableEntryTest, TestCase::QUICK);
  AddTestCase (new RplRoutingTableTest, TestCase::QUICK);
  AddTestCase (new RplNeighborTest, TestCase::QUICK);
  AddTestCase (new RplTest, TestCase::QUICK);
  AddTestCase (new MultipleRootTest, TestCase::QUICK);
}

// Do not forget to allocate an instance of this TestSuite
static RplTestSuite rplTestSuite;

