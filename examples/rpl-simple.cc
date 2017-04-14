// Network topology
//
//   ROOT
//     |<=== source network
//     A-----B
// A, B are RPL routers

#include <fstream>
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/internet-apps-module.h"
#include "ns3/csma-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv6-static-routing-helper.h"
#include "ns3/ipv6-routing-table-entry.h"
#include "ns3/rpl-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("RplSimpleRoute");

int main (int argc, char **argv)
{
  bool verbose = false;

  CommandLine cmd;
  cmd.AddValue ("verbose", "turn on log components", verbose);
  cmd.Parse (argc, argv);

  if (verbose)
    {
    }

  NS_LOG_INFO ("Create nodes.");
  Ptr<Node> root = CreateObject<Node> ();
  Names::Add ("RootNode", root);
  Ptr<Node> a = CreateObject<Node> ();
  Names::Add ("RouterA", a);
  Ptr<Node> b = CreateObject<Node> ();
  Names::Add ("RouterB", b);
  NodeContainer net1 (root, a);
  NodeContainer net2 (a, b);
  NodeContainer routers (a, b);
  NodeContainer nodes (root);

  NS_LOG_INFO ("Create channels.");
  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate", DataRateValue (5000000));
  csma.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (2)));
  NetDeviceContainer ndc = csma.Install (net1);
  NetDeviceContainer ndc1 = csma.Install (net2);
  NS_LOG_INFO ("Create IPv6 and routing");
  RplHelper rplRouting;

  InternetStackHelper internetv6Nodes;
  internetv6Nodes.SetIpv4StackInstall (false);
  internetv6Nodes.Install (nodes);
  internetv6Nodes.Install (routers);

  Ipv6AddressHelper ipv6;
  ipv6.SetBase (Ipv6Address ("2001:1::"), Ipv6Prefix (64));
  Ipv6InterfaceContainer iic = ipv6.Assign (ndc);
  RplHelper routingHelper;

  Ptr<OutputStreamWrapper> routingStream = Create<OutputStreamWrapper> (&std::cout);

  routingHelper.PrintRoutingTableAt (Seconds (30.0), a, routingStream);

  //Set interfaces

  NS_LOG_INFO ("Create Applications.");
  uint32_t packetSize = 1024;
  uint32_t maxPacketCount = 100;
  Time interPacketInterval = Seconds (1.0);
  Ping6Helper ping6;
  ping6.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
  ping6.SetAttribute ("Interval", TimeValue (interPacketInterval));
  ping6.SetAttribute ("PacketSize", UintegerValue (packetSize));
  ApplicationContainer apps = ping6.Install (root);
  apps.Start (Seconds (1.0));
  apps.Stop (Seconds (110.0));

  ping6.SetLocal (iic1.GetAddress (0, 1));

  /* Now, do the actual simulation. */
  NS_LOG_INFO ("Run Simulation.");
  Simulator::Stop (Seconds (120));
  Simulator::Run ();
  Simulator::Destroy ();
  NS_LOG_INFO ("Done.");
}

