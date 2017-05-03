
#include "ns3/rpl-metric.h"

namespace ns3 {

//NS_LOG_COMPONENT_DEFINE ("RplMetric")

RplMetric::RplMetric ()
{

}

RplMetric::~RplMetric ()
{

}

//NS_LOG_COMPONENT_DEFINE ("RplHopCountMetric");

RplHopCountMetric::RplHopCountMetric (void)
{
  SetHopCount(0);
}

RplHopCountMetric::~RplHopCountMetric ()
{

}

uint8_t RplHopCountMetric::GetHopCount(void) const
{
  return m_hopCount;
}

void RplHopCountMetric::SetHopCount(uint8_t hopCount)
{
  m_hopCount = hopCount;
}
/*
void RplHopCountMetric::Print (std::ostream& os) const
{
  //NS_LOG_FUNCTION (this << &os);
}


uint32_t RplHopCountMetric::GetSerializedSize () const
{
//  NS_LOG_FUNCTION (this);
  return 1;
}


void RplHopCountMetric::Serialize (Buffer::Iterator start) const
{
//  NS_LOG_FUNCTION (this << &start);
  Buffer::Iterator i = start;

  i.WriteU8 (GetHopCount ());
}

uint32_t RplHopCountMetric::Deserialize (Buffer::Iterator start)
{
//  NS_LOG_FUNCTION (this << &start);
  Buffer::Iterator i = start;

  SetHopCount(i.ReadU8());

  return GetSerializedSize ();
}
*/
}
