/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 The Boeing Company
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
 */

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

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("WifiSimpleAdhoc");


void ReceivePacket (Ptr<Socket> socket)
{
  while (socket->Recv ())
    {
      NS_LOG_UNCOND ("Received one packet!");
    }
}

static void GenerateTraffic (Ptr<Socket> socket, uint32_t pktSize, 
                             uint32_t pktCount, Time pktInterval )
{
  if (pktCount > 0)
    {
      socket->Send (Create<Packet> (pktSize));
      Simulator::Schedule (pktInterval, &GenerateTraffic, 
                           socket, pktSize,pktCount-1, pktInterval);
    }
  else
    {
      socket->Close ();
    }
}

void TearDownLink (Ptr<Node> nodeA, uint32_t interfaceA)
{
  nodeA->GetObject<Ipv6> ()->SetDown (interfaceA);
}



int main (int argc, char *argv[])
{
  std::string phyMode ("DsssRate1Mbps");
  double rss = -80;  // -dBm
  uint32_t packetSize = 1000; // bytes
  uint32_t numPackets = 1;
  double interval = 1.0; // seconds
  bool verbose = false;

  CommandLine cmd;

  cmd.AddValue ("phyMode", "Wifi Phy mode", phyMode);
  cmd.AddValue ("rss", "received signal strength", rss);
  cmd.AddValue ("packetSize", "size of application packet sent", packetSize);
  cmd.AddValue ("numPackets", "number of packets generated", numPackets);
  cmd.AddValue ("interval", "interval (seconds) between packets", interval);
  cmd.AddValue ("verbose", "turn on all WifiNetDevice log components", verbose);

  cmd.Parse (argc, argv);

  // disable fragmentation for frames below 2200 bytes
  Config::SetDefault ("ns3::WifiRemoteStationManager::FragmentationThreshold", StringValue ("2200"));
  // turn off RTS/CTS for frames below 2200 bytes
  Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold", StringValue ("2200"));
  // Fix non-unicast data rate to be the same as that of unicast
  Config::SetDefault ("ns3::WifiRemoteStationManager::NonUnicastMode", 
                      StringValue (phyMode));

  // Multiple roots
  NodeContainer root;
  root.Create (1);
  // Nodes
  NodeContainer c;
  c.Create (6);

  WifiHelper wifi;
  if (verbose)
    {
      wifi.EnableLogComponents ();  // Turn on all Wifi logging
    }
  wifi.SetStandard (WIFI_PHY_STANDARD_80211b);

  YansWifiPhyHelper wifiPhy =  YansWifiPhyHelper::Default ();
  wifiPhy.Set ("RxGain", DoubleValue (0) ); 
  wifiPhy.SetPcapDataLinkType (YansWifiPhyHelper::DLT_IEEE802_11_RADIO); 

  YansWifiChannelHelper wifiChannel;
  wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
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
  NetDeviceContainer devicesR = wifi.Install (wifiPhy, wifiMac, root);
  NetDeviceContainer devices = wifi.Install (wifiPhy, wifiMac, c);

  MobilityHelper mobility;
  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
  positionAlloc->Add (Vector (1000.0, 00.0, 2000.0));
  mobility.SetPositionAllocator (positionAlloc);
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (root);

  MobilityHelper mobility2;
  Ptr<ListPositionAllocator> positionAlloc2 = CreateObject<ListPositionAllocator> ();
  positionAlloc2->Add (Vector (1500.0, 1000.0, 500.0));
  positionAlloc2->Add (Vector (500.0, 1000.0, 3500.0));
  positionAlloc2->Add (Vector (1750.0, 2000.0, 0.0));
  positionAlloc2->Add (Vector (1250.0, 2000.0, 1100.0));
  positionAlloc2->Add (Vector (750.0, 2000.0, 2900.0));
  positionAlloc2->Add (Vector (250.0, 2000.0, 4000.0));

  mobility2.SetPositionAllocator (positionAlloc2);
  mobility2.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility2.Install (c);

  RplHelper RplRouting;

  Ipv6ListRoutingHelper listRH;
  listRH.Add (RplRouting, 0);

  InternetStackHelper internetv6routers;
  internetv6routers.SetIpv4StackInstall (false);
  internetv6routers.SetRoutingHelper (listRH);

  // Order matters for IP.
  internetv6routers.Install (root);
  internetv6routers.Install (c);

  Ipv6AddressHelper ipv6;
  ipv6.SetBase (Ipv6Address ("2001:1::"), Ipv6Prefix (64));
  Ipv6InterfaceContainer iic1 = ipv6.Assign (devicesR);
  ipv6.SetBase (Ipv6Address ("2002:1::"), Ipv6Prefix (64));
  Ipv6InterfaceContainer iic2 = ipv6.Assign (devices);
  iic1.SetForwarding (0, true);
  iic2.SetForwarding (0, true);

  //Simulator::Schedule (Seconds (100), &TearDownLink, c.Get(0), 1);

  // Tracing
  wifiPhy.EnablePcap ("rpl-adhoc-line", devices);

  // Output what we are doing
  NS_LOG_UNCOND ("Testing " << numPackets  << " packets sent with receiver rss " << rss );

  Simulator::Run ();
  Simulator::Destroy ();

  return 0;
}

