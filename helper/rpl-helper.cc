/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ns3/node.h"
#include "ns3/node-list.h"
#include "ns3/ipv6-list-routing.h"
#include "ns3/rpl.h"
#include "ns3/rpl-option.h"     
#include "rpl-helper.h"

namespace ns3 {

RplHelper::RplHelper ()
{
  m_factory.SetTypeId ("ns3::Rpl");
}

RplHelper::~RplHelper ()
{
}

RplHelper*
RplHelper::Copy (void) const
{
  return new RplHelper (*this);
}

void
RplHelper::Set (std::string name, const AttributeValue &value)
{
  m_factory.Set (name, value);
}

int64_t
RplHelper::AssignStreams (NodeContainer c, int64_t stream)
{
  int64_t currentStream = stream;
  Ptr<Node> node;
  for (NodeContainer::Iterator i = c.Begin (); i != c.End (); ++i)
    {
      node = (*i);
      Ptr<Ipv6> ipv6 = node->GetObject<Ipv6> ();
      NS_ASSERT_MSG (ipv6, "Ipv6 not installed on node");
      Ptr<Ipv6RoutingProtocol> proto = ipv6->GetRoutingProtocol ();
      NS_ASSERT_MSG (proto, "Ipv6 routing not installed on node");
      Ptr<Rpl> rpl = DynamicCast<Rpl> (proto);
      if (rpl)
        {
          currentStream += rpl->AssignStreams (currentStream);
          continue;
        }
      // RIPng may also be in a list
      Ptr<Ipv6ListRouting> list = DynamicCast<Ipv6ListRouting> (proto);
      if (list)
        {
          int16_t priority;
          Ptr<Ipv6RoutingProtocol> listProto;
          Ptr<Rpl> listRpl;
          for (uint32_t i = 0; i < list->GetNRoutingProtocols (); i++)
            {
              listProto = list->GetRoutingProtocol (i, priority);
              listRpl = DynamicCast<Rpl> (listProto);
              if (listRpl)
                {
                  currentStream += listRpl->AssignStreams (currentStream);
                  break;
                }
            }
        }
    }
  return (currentStream - stream);
}

Ptr<Ipv6RoutingProtocol>
RplHelper::Create (Ptr<Node> node) const
{
  Ptr<Rpl> rpl = m_factory.Create<Rpl> ();
  node->AggregateObject (rpl);
  return rpl;
}


}

